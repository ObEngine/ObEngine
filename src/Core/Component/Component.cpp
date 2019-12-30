#include <algorithm>

#include <Component/Component.hpp>

namespace obe::Component
{
    std::vector<ComponentBase*> ComponentBase::Components;

    void ComponentBase::AddComponent(ComponentBase* component)
    {
        for (ComponentBase* comp : Components)
        {
            if (comp->getId() == component->getId())
            {
                throw aube::ErrorHandler::Raise(
                    "obe.Component.ComponentBase.IdAlreadyExists", { { "id", comp->getId() } });
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
} // namespace obe::Component
