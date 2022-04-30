#pragma once

#include <algorithm>
#include <any>
#include <string_view>
#include <vector>

#include <Types/Identifiable.hpp>
#include <Types/Serializable.hpp>

namespace obe::Component
{
    class ComponentRegistrationBehaviour
    {
    public:
        LuaEventListener(sol::protected_function callback);
        template <class EventType>
        void operator()(const EventType& event) const;
    };

    class ComponentBase : public Types::Identifiable, public Types::Serializable
    {
    public:
        template <class DerivedComponent>
        using ComponentCaster = std::function<DerivedComponent*(ComponentBase*)>;
        using TypeErasedComponentCaster = std::any;
        template <class DerivedComponent>
        using OnRegisterBehaviour
            = std::function<void(std::string_view, ComponentCaster<DerivedComponent>)>;
        template <class DerivedComponent>
        static void OnRegister(OnRegisterBehaviour<DerivedComponent> behaviour);
    protected:
        static std::vector<ComponentBase*> Components;
        static void AddComponent(ComponentBase* component);
        static void RemoveComponent(ComponentBase* component);


        static std::vector<TypeErasedComponentCaster> m_on_register_behaviours;

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
    };

    /**
     * \hook{Inherit, Register}
     */
    template <class DerivedComponent>
    class Component : public ComponentBase
    {
    private:
        
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

    template <class BehaviourFunction>
    void ComponentBase::OnRegister(BehaviourFunction behaviour)
    {
        OnRegisterBehaviour<DerivedComponent> bundled_behaviour = behaviour;
        m_on_register_behaviours.push_back(behaviour);
    }

    template <class DerivedComponent>
    void Component<DerivedComponent>::Register()
    {
        auto caster = [](ComponentBase* component) -> DerivedComponent*
        { return static_cast<DerivedComponent*>(component); };
        for (std::any& untyped_behaviour : m_on_register_behaviours)
        {
            OnRegisterBehaviour<DerivedComponent> behaviour
                = std::any_cast<OnRegisterBehaviour<DerivedComponent>>(untyped_behaviour);
            behaviour(DerivedComponent::ComponentType, caster);
        }
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
