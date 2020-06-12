#include <Bindings/obe/Component/Component.hpp>

#include <Component/Component.hpp>

#include <Bindings/Config.hpp>

namespace obe::Component::Bindings
{
    void LoadClassComponentBase(sol::state_view state)
    {
        sol::table ComponentNamespace = state["obe"]["Component"].get<sol::table>();
        sol::usertype<obe::Component::ComponentBase> bindComponentBase
            = ComponentNamespace.new_usertype<obe::Component::ComponentBase>(
                "ComponentBase", sol::base_classes,
                sol::bases<obe::Types::Identifiable, obe::Types::Serializable>());
        bindComponentBase["inject"] = &obe::Component::ComponentBase::inject;
        bindComponentBase["remove"] = &obe::Component::ComponentBase::remove;
        bindComponentBase["dump"] = &obe::Component::ComponentBase::dump;
        bindComponentBase["load"] = &obe::Component::ComponentBase::load;
        bindComponentBase["type"] = &obe::Component::ComponentBase::type;
    }
};