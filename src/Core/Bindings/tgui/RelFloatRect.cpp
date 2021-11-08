#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/RelFloatRect.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassRelFloatRect(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RelFloatRect> bindRelFloatRect
            = tguiNamespace.new_usertype<tgui::RelFloatRect>("RelFloatRect", sol::call_constructor,
                sol::constructors<tgui::RelFloatRect(),
                    tgui::RelFloatRect(tgui::AbsoluteOrRelativeValue, tgui::AbsoluteOrRelativeValue,
                        tgui::AbsoluteOrRelativeValue, tgui::AbsoluteOrRelativeValue)>());
        bindRelFloatRect["getLeft"] = &tgui::RelFloatRect::getLeft;
        bindRelFloatRect["getTop"] = &tgui::RelFloatRect::getTop;
        bindRelFloatRect["getWidth"] = &tgui::RelFloatRect::getWidth;
        bindRelFloatRect["getHeight"] = &tgui::RelFloatRect::getHeight;
        bindRelFloatRect["getPosition"] = &tgui::RelFloatRect::getPosition;
        bindRelFloatRect["getSize"] = &tgui::RelFloatRect::getSize;
        bindRelFloatRect["getRect"] = &tgui::RelFloatRect::getRect;
        bindRelFloatRect["updateParentSize"] = &tgui::RelFloatRect::updateParentSize;
    }
};