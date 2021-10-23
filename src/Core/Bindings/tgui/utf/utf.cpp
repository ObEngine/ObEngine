#include <Bindings/tgui/utf/utf.hpp>

#include <TGUI/Utf.hpp>

#include <Bindings/Config.hpp>

namespace tgui::utf::Bindings
{
    void LoadFunctionEncodeCharUtf8(sol::state_view state)
    {
    }
    void LoadFunctionDecodeCharUtf8(sol::state_view state)
    {
    }
    void LoadFunctionConvertUtf8toUtf32(sol::state_view state)
    {
    }
    void LoadFunctionConvertUtf16toUtf32(sol::state_view state)
    {
    }
    void LoadFunctionConvertWidetoUtf32(sol::state_view state)
    {
    }
    void LoadFunctionConvertUtf32toLatin1(sol::state_view state)
    {
        sol::table utfNamespace = state["tgui"]["utf"].get<sol::table>();
        utfNamespace.set_function(
            "convertUtf32toLatin1", tgui::utf::convertUtf32toLatin1);
    }
    void LoadFunctionConvertUtf32toStdStringUtf8(sol::state_view state)
    {
        sol::table utfNamespace = state["tgui"]["utf"].get<sol::table>();
        utfNamespace.set_function(
            "convertUtf32toStdStringUtf8", tgui::utf::convertUtf32toStdStringUtf8);
    }
    void LoadFunctionConvertUtf32toWide(sol::state_view state)
    {
        sol::table utfNamespace = state["tgui"]["utf"].get<sol::table>();
        utfNamespace.set_function("convertUtf32toWide", tgui::utf::convertUtf32toWide);
    }
    void LoadFunctionConvertUtf32toUtf16(sol::state_view state)
    {
        sol::table utfNamespace = state["tgui"]["utf"].get<sol::table>();
        utfNamespace.set_function("convertUtf32toUtf16", tgui::utf::convertUtf32toUtf16);
    }
};