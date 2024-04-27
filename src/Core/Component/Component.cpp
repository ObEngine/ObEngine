#include <algorithm>

#include <Component/Component.hpp>
#include <Component/Exceptions.hpp>

namespace obe::component
{
    std::vector<ComponentBase*> ComponentBase::Components;

    void ComponentBase::AddComponent(ComponentBase* component)
    {
        for (ComponentBase* comp : Components)
        {
            if (comp->get_id() == component->get_id())
            {
                throw exceptions::ComponentIdAlreadyTaken(comp->get_id());
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

    ComponentBase::ComponentBase(const ComponentBase& other)
        : Identifiable(other.get_id())
    {
    }

    ComponentBase& ComponentBase::operator=(const ComponentBase& other)
    {
        return *this;
    }
} // namespace obe::component
