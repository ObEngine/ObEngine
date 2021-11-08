#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Layout.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumOperation(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::Layout::Operation>("Operation",
            { { "Value", tgui::Layout::Operation::Value },
                { "Plus", tgui::Layout::Operation::Plus },
                { "Minus", tgui::Layout::Operation::Minus },
                { "Multiplies", tgui::Layout::Operation::Multiplies },
                { "Divides", tgui::Layout::Operation::Divides },
                { "Minimum", tgui::Layout::Operation::Minimum },
                { "Maximum", tgui::Layout::Operation::Maximum },
                { "BindingPosX", tgui::Layout::Operation::BindingPosX },
                { "BindingPosY", tgui::Layout::Operation::BindingPosY },
                { "BindingLeft", tgui::Layout::Operation::BindingLeft },
                { "BindingTop", tgui::Layout::Operation::BindingTop },
                { "BindingWidth", tgui::Layout::Operation::BindingWidth },
                { "BindingHeight", tgui::Layout::Operation::BindingHeight },
                { "BindingInnerWidth", tgui::Layout::Operation::BindingInnerWidth },
                { "BindingInnerHeight", tgui::Layout::Operation::BindingInnerHeight },
                { "BindingString", tgui::Layout::Operation::BindingString } });
    }
};