#include <Config/Templates/Mount.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::Config::Templates
{
    vili::parser::state getMountTemplates()
    {
        vili::parser::state state;

        vili::node project = vili::object { { "type", "Project" }, { "path", "" } };
        state.push_template("Project", project);

        vili::node package = vili::object { { "type", "Package" }, { "path", "" } };
        state.push_template("Package", package);

        vili::node path = vili::object { { "type", "Path" }, { "path", "" } };
        state.push_template("Path", path);

        vili::node executable = vili::object { { "type", "Path" },
            { "path", Utils::File::getExecutableDirectory() } };
        state.push_template("Executable", executable);

        return state;
    }
}
