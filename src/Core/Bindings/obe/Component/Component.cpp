#include <Bindings/obe/Component/Component.hpp>

#include <Component/Component.hpp>

#include <Bindings/Config.hpp>

namespace obe::component::bindings
{
    void load_class_component_base(sol::state_view state)
    {
        sol::table Component_namespace = state["obe"]["component"].get<sol::table>();
        sol::usertype<obe::component::ComponentBase> bind_component_base
            = Component_namespace.new_usertype<obe::component::ComponentBase>("ComponentBase",
                sol::base_classes,
                sol::bases<obe::types::Identifiable, obe::types::Serializable>());
        bind_component_base["remove"] = &obe::component::ComponentBase::remove;
        bind_component_base["dump"] = &obe::component::ComponentBase::dump;
        bind_component_base["load"] = &obe::component::ComponentBase::load;
        bind_component_base["type"] = &obe::component::ComponentBase::type;
        bind_component_base["cast"] = &obe::component::ComponentBase::cast;
    }
};