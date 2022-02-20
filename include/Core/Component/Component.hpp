#pragma once

#include <algorithm>
#include <vector>

#include <Types/Identifiable.hpp>
#include <Types/Serializable.hpp>

namespace obe::Component
{
    class ComponentBase : public Types::Identifiable, public Types::Serializable
    {
    public:
        using Caster = std::function<sol::lua_value(ComponentBase*)>;
    protected:
        static std::vector<ComponentBase*> Components;
        static void AddComponent(ComponentBase* component);
        static void RemoveComponent(ComponentBase* component);

        static std::unordered_map<std::string_view, Caster> ComponentCasters;

    public:
        /**
         * \nobind
         */
        static constexpr std::string_view ComponentType = "ComponentBase";
        ComponentBase(const std::string& id);
        virtual void remove() = 0;

        [[nodiscard]] vili::node dump() const override = 0;
        void load(const vili::node& data) override = 0;

        [[nodiscard]] virtual std::string_view type() const = 0;
        [[nodiscard]] sol::lua_value cast();
    };

    /**
     * \hook{OnInherit, Register}
     */
    template <class DerivedComponent>
    class Component : public ComponentBase
    {
    public:
        static void Register();
        /**
         * \nobind
         */
        static constexpr std::string_view ComponentType = "Component";
        explicit Component(const std::string& id);
        ~Component() override;

        static std::vector<DerivedComponent*> Pool;

        void remove() override;

        [[nodiscard]] vili::node dump() const override = 0;
        void load(const vili::node& data) override = 0;

        [[nodiscard]] std::string_view type() const override;
        using Ref = std::reference_wrapper<DerivedComponent>;
        using Ptr = DerivedComponent*;
    };

    template <class DerivedComponent>
    void Component<DerivedComponent>::Register()
    {
        ComponentCasters[DerivedComponent::ComponentType] = [](ComponentBase* component) -> sol::lua_value {
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
                       [&](DerivedComponent* ptr) -> bool { return (this == ptr); }),
            Pool.end());
    }

    template <class DerivedComponent>
    std::string_view Component<DerivedComponent>::type() const
    {
        return ComponentType;
    }

    template <class DerivedComponent>
    void Component<DerivedComponent>::remove()
    {
        RemoveComponent(this);
        DerivedComponent::Pool.erase(
            std::remove_if(DerivedComponent::Pool.begin(), DerivedComponent::Pool.end(),
                          [&](auto& elem) { return (this == elem); }),
            DerivedComponent::Pool.end());
    }

    template <class DerivedComponent>
    std::vector<DerivedComponent*> Component<DerivedComponent>::Pool;
} // namespace obe::Component
