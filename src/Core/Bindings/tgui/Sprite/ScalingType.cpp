#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Sprite.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumScalingType(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::Sprite::ScalingType>("ScalingType",
            { { "Normal", tgui::Sprite::ScalingType::Normal },
                { "Horizontal", tgui::Sprite::ScalingType::Horizontal },
                { "Vertical", tgui::Sprite::ScalingType::Vertical },
                { "NineSlice", tgui::Sprite::ScalingType::NineSlice } });
    }
};