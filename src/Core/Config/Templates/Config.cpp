#include <Config/Templates/Config.hpp>

namespace obe::Config::Templates
{
    vili::parser::state getConfigTemplates()
    {
        vili::parser::state state;
        // Debug templates
        state.push_template("trace", 0);
        state.push_template("debug", 1);
        state.push_template("info", 2);
        state.push_template("warning", 3);
        state.push_template("error", 4);
        state.push_template("critical", 5);
        state.push_template("none", 6);

        // Window templates
        state.push_template("fill", "fill");
        return state;
    }
}