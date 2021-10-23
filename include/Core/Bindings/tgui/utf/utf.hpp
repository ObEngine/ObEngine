#pragma once

namespace sol
{
    class state_view;
};
namespace tgui::utf::Bindings
{
    void LoadFunctionEncodeCharUtf8(sol::state_view state);
    void LoadFunctionDecodeCharUtf8(sol::state_view state);
    void LoadFunctionConvertUtf8toUtf32(sol::state_view state);
    void LoadFunctionConvertUtf16toUtf32(sol::state_view state);
    void LoadFunctionConvertWidetoUtf32(sol::state_view state);
    void LoadFunctionConvertUtf32toLatin1(sol::state_view state);
    void LoadFunctionConvertUtf32toStdStringUtf8(sol::state_view state);
    void LoadFunctionConvertUtf32toWide(sol::state_view state);
    void LoadFunctionConvertUtf32toUtf16(sol::state_view state);
};