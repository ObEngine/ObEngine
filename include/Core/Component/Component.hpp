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
        // using Caster = std::function<sol::lua_value(ComponentBase*)>;
    protected:
        static std::vector<ComponentBase*> Components;
        static void AddComponent(ComponentBase* component);
        static void RemoveComponent(ComponentBase* component);

        // static std::unordered_map<std::string_view, Caster> ComponentCasters;

    public:
        /**
         * \nobind
         */
        static constexpr std::string_view ComponentType = "ComponentBase";
        ComponentBase(const std::string& id);
        virtual void inject(unsigned int envIndex) = 0;
        virtual void remove() = 0;

        vili::node dump() const override = 0;
        void load(const vili::node& data) override = 0;

        [[nodiscard]] virtual std::string_view type() const = 0;

        // sol::lua_value cast();
    };

    template <class DerivedComponent>
    class Component : public ComponentBase
    {
    public:
        // static void Register();
        /**
         * \nobind
         */
        static constexpr std::string_view ComponentType = "Component";
        explicit Component(const std::string& id);
        ~Component() override;

        static std::vector<DerivedComponent*> Pool;
        // static T& create(const std::string& id);

        void remove() override;
        void inject(unsigned int envIndex) override;

        vili::node dump() const override = 0;
        void load(const vili::node& data) override = 0;

        [[nodiscard]] std::string_view type() const override;
        using Ref = std::reference_wrapper<DerivedComponent>;
        using Ptr = DerivedComponent*;
    };

    /* template <class DerivedComponent>
    void Component<DerivedComponent>::Register()
    {
        ComponentCasters[DerivedComponent::ComponentType] = [](ComponentBase* component) -> sol::lua_value {
            return static_cast<DerivedComponent*>(component);
        };
    }*/

    template <class DerivedComponent>
    Component<DerivedComponent>::Component(const std::string& id)
        : ComponentBase(id)
    {
        Pool.emplace_back(static_cast<DerivedComponent*>(this));
    }

    template <class T>
    Component<T>::~Component()
    {
        Pool.erase(
            std::remove_if(Pool.begin(), Pool.end(), [&](T* ptr) -> bool { return (this == ptr); }),
            Pool.end());
    }

    /*template<class T>
    inline T& Component<T>::create(const std::string& id)
    {
        T* ref = Pool.emplace_back(std::make_unique<T>(id)).get();
        AddComponent(ref);
        return *ref;
    }*/

    template <class T>
    void Component<T>::inject(unsigned int envIndex)
    {
        /*Script::ScriptEngine["__ENVIRONMENTS"][envIndex]["Components"][m_id]
            = static_cast<T*>(this);*/
    }

    template <class T>
    std::string_view Component<T>::type() const
    {
        return Component::ComponentType;
    }

    template <class T>
    void Component<T>::remove()
    {
        RemoveComponent(this);
        T::Pool.erase(std::remove_if(T::Pool.begin(), T::Pool.end(),
                          [&](auto& elem) { return (this == elem); }),
            T::Pool.end());
    }

    template <class T>
    std::vector<T*> Component<T>::Pool;
} // namespace obe::Component
