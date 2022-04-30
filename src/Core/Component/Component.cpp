#include <algorithm>

#include <Component/Component.hpp>
#include <Component/Exceptions.hpp>

namespace obe::Component
{
    std::vector<ComponentBase*> ComponentBase::Components;
    std::vector<ComponentBase::TypeErasedComponentCaster> ComponentBase::m_on_register_behaviours;

    void ComponentBase::AddComponent(ComponentBase* component)
    {
        for (ComponentBase* comp : Components)
        {
            if (comp->getId() == component->getId())
            {
                throw Exceptions::ComponentIdAlreadyTaken(comp->getId(), EXC_INFO);
            }
        }
        Components.push_back(component);
    }

    void ComponentBase::RemoveComponent(ComponentBase* component)
    {
        Components.erase(
            std::remove(Components.begin(), Components.end(), component), Components.end());
    }

    ComponentBase::ComponentBase(const std::string& id)
        : Identifiable(id)
    {
    }

    sol::lua_value ComponentBase::cast()
    {
        if (!ComponentCasters.count(this->type()))
        {
            throw Exceptions::UnknownComponentType(this->type(), EXC_INFO);
        }
        return ComponentCasters.at(this->type())(this);
    }
} // namespace obe::Component
