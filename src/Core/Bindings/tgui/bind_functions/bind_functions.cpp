#include <Bindings/tgui/bind_functions/bind_functions.hpp>

#include <TGUI/Layout.hpp>

#include <Bindings/Config.hpp>

namespace tgui::bind_functions::Bindings
{
    void LoadFunctionBindPosX(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function("bindPosX", tgui::bind_functions::bindPosX);
    }
    void LoadFunctionBindPosY(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function("bindPosY", tgui::bind_functions::bindPosY);
    }
    void LoadFunctionBindLeft(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function("bindLeft", tgui::bind_functions::bindLeft);
    }
    void LoadFunctionBindTop(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function("bindTop", tgui::bind_functions::bindTop);
    }
    void LoadFunctionBindWidth(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function("bindWidth",
            sol::overload(
                static_cast<TGUI_API gui::Layout (*)(std::shared_ptr<gui::Widget>)>(
                    tgui::bind_functions::bindWidth),
                static_cast<TGUI_API gui::Layout (*)(gui::GuiBase&)>(
                    tgui::bind_functions::bindWidth)));
    }
    void LoadFunctionBindHeight(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function("bindHeight",
            sol::overload(
                static_cast<TGUI_API gui::Layout (*)(std::shared_ptr<gui::Widget>)>(
                    tgui::bind_functions::bindHeight),
                static_cast<TGUI_API gui::Layout (*)(gui::GuiBase&)>(
                    tgui::bind_functions::bindHeight)));
    }
    void LoadFunctionBindInnerWidth(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function(
            "bindInnerWidth", tgui::bind_functions::bindInnerWidth);
    }
    void LoadFunctionBindInnerHeight(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function(
            "bindInnerHeight", tgui::bind_functions::bindInnerHeight);
    }
    void LoadFunctionBindRight(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function(
            "bindRight", tgui::bind_functions::bindRight);
    }
    void LoadFunctionBindBottom(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function(
            "bindBottom", tgui::bind_functions::bindBottom);
    }
    void LoadFunctionBindPosition(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function(
            "bindPosition", tgui::bind_functions::bindPosition);
    }
    void LoadFunctionBindSize(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function("bindSize",
            sol::overload(
                static_cast<TGUI_API gui::Layout2d (*)(std::shared_ptr<gui::Widget>)>(
                    tgui::bind_functions::bindSize),
                static_cast<TGUI_API gui::Layout2d (*)(gui::GuiBase&)>(
                    tgui::bind_functions::bindSize)));
    }
    void LoadFunctionBindInnerSize(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function(
            "bindInnerSize", tgui::bind_functions::bindInnerSize);
    }
    void LoadFunctionBindMin(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function("bindMin", tgui::bind_functions::bindMin);
    }
    void LoadFunctionBindMax(sol::state_view state)
    {
        sol::table bind_functionsNamespace
            = state["tgui"]["bind_functions"].get<sol::table>();
        bind_functionsNamespace.set_function("bindMax", tgui::bind_functions::bindMax);
    }
};