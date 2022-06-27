#include <Bindings/obe/Component/Component.hpp>

#include <Component/Component.hpp>

#include <Bindings/Config.hpp>

namespace obe::Component::bindings
{
    void load_class_component_base(sol::state_view state)
    {
        sol::table Component_namespace = state["obe"]["Component"].get<sol::table>();
        sol::usertype<obe::Component::ComponentBase> bind_component_base
            = Component_namespace.new_usertype<obe::Component::ComponentBase>("ComponentBase",
                sol::base_classes,
                sol::bases<obe::Types::Identifiable, obe::Types::Serializable>());
        bind_component_base["remove"] = &obe::Component::ComponentBase::remove;
        bind_component_base["dump"] = &obe::Component::ComponentBase::dump;
        bind_component_base["load"] = &obe::Component::ComponentBase::load;
        bind_component_base["type"] = &obe::Component::ComponentBase::type;
        bind_component_base["cast"] = &obe::Component::ComponentBase::cast;
    }
};