#pragma once

#include <algorithm>
#include <vector>

#include <sol/sol.hpp>

#include <Types/Identifiable.hpp>
#include <Types/Serializable.hpp>
#include <Types/UniqueIdentifiable.hpp>

namespace obe::component
{
    class ComponentBase : public types::Identifiable,
                          public types::Serializable,
                          public types::UniqueIdentifiable
    {
    public:
        using Caster = std::function<sol::lua_value(ComponentBase*)>;

    protected:
        static std::vector<ComponentBase*> Components;
        static std::unordered_map<std::string_view, Caster> ComponentCasters;
        static void AddComponent(ComponentBase* component);
        static void RemoveComponent(ComponentBase* component);

    public:
        explicit ComponentBase(const std::string& id);
        ComponentBase(const ComponentBase& other);
        ComponentBase& operator=(const ComponentBase& other);
        virtual void remove() = 0;

        [[nodiscard]] vili::node dump() const override = 0;
        void load(const vili::node& data) override = 0;

        [[nodiscard]] virtual std::string_view type() const = 0;
        [[nodiscard]] sol::lua_value cast();
    };

    /**
     * \hook{Inherit, %childclass%::Register();}
     */
    template <class DerivedComponent>
    class Component : public ComponentBase
    {
    private:
    public:
        static void Register();

        explicit Component(const std::string& id);
        ~Component() override;

        static std::vector<DerivedComponent*> Pool;

        void remove() override;

        [[nodiscard]] vili::node dump() const override = 0;
        void load(const vili::node& data) override = 0;

        using Ref = std::reference_wrapper<DerivedComponent>;
        using Ptr = DerivedComponent*;
    };

    template <class DerivedComponent>
    void Component<DerivedComponent>::Register()
    {
        ComponentCasters[DerivedComponent::ComponentType]
            = [](ComponentBase* component) -> sol::lua_value
        {
            return static_cast<DerivedComponent*>(component);
        };
    }

    template <class DerivedComponent>
    Component<DerivedComponent>::Component(const std::string& id)
        : ComponentBase(id)
    {
        Pool.emplace_back(static_cast<DerivedComponent*>(this));
    }

    template <class DerivedComponent>
    Component<DerivedComponent>::~Component()
    {
        Pool.erase(std::remove_if(Pool.begin(), Pool.end(),
                       [&](DerivedComponent* ptr) -> bool
                       {
                           return (this == ptr);
                       }),
            Pool.end());
    }

    template <class DerivedComponent>
    void Component<DerivedComponent>::remove()
    {
        RemoveComponent(this);
        DerivedComponent::Pool.erase(
            std::remove_if(DerivedComponent::Pool.begin(), DerivedComponent::Pool.end(),
                [&](auto& elem)
                {
                    return (this == elem);
                }),
            DerivedComponent::Pool.end());
    }

    template <class DerivedComponent>
    std::vector<DerivedComponent*> Component<DerivedComponent>::Pool;
} // namespace obe::component
