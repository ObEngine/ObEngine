#include <algorithm>

#include <Component/Component.hpp>
#include <Component/Exceptions.hpp>

namespace obe::Component
{
    std::vector<ComponentBase*> ComponentBase::Components;

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
        Components.erase(std::remove(Components.begin(), Components.end(), component),
            Components.end());
    }

    ComponentBase::ComponentBase(const std::string& id)
        : Identifiable(id)
    {
    }
} // namespace obe::Component
