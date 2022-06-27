#include <Bindings/obe/animation/schemas/Schemas.hpp>

#include <Animation/Schemas.hpp>

#include <Bindings/Config.hpp>

namespace obe::animation::schemas::bindings
{
    void load_global_animation_schema_str(sol::state_view state)
    {
        sol::table schemas_namespace = state["obe"]["animation"]["schemas"].get<sol::table>();
        schemas_namespace["AnimationSchemaStr"] = obe::animation::schemas::AnimationSchemaStr;
    }
    void load_global_animation_schema(sol::state_view state)
    {
        sol::table schemas_namespace = state["obe"]["animation"]["schemas"].get<sol::table>();
        schemas_namespace["AnimationSchema"] = obe::animation::schemas::AnimationSchema;
    }
};