#include <vld8/templates.hpp>

namespace vili::validator
{
    vili::parser::state templates()
    {
        vili::parser::state state;

        // Base types
        const vili::node object_tpl = vili::object { { "type", "object" } };
        state.push_template("object", object_tpl);

        const vili::node list_tpl = vili::object { { "type", "array" } };
        state.push_template("array", list_tpl);

        const vili::node string_tpl = vili::object { { "type", "string" } };
        state.push_template("string", string_tpl);

        const vili::node integer_tpl = vili::object { { "type", "integer" } };
        state.push_template("integer", integer_tpl);

        const vili::node float_tpl = vili::object { { "type", "float" } };
        state.push_template("float", float_tpl);

        const vili::node boolean_tpl = vili::object { { "type", "boolean" } };
        state.push_template("boolean", boolean_tpl);

        // Advanced types
        const vili::node any_tpl = vili::object { { "type", "any" } };
        state.push_template("any", any_tpl);

        const vili::node union_tpl = vili::object { { "type", "union" } };
        state.push_template("union", union_tpl);

        return state;
    }
}
