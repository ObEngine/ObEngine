#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Global.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadFunctionReadFileToMemory(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function(
            "readFileToMemory", [](const tgui::String& filename, std::size_t fileSize) {
                readFileToMemory(filename, fileSize);
            });
    }
};