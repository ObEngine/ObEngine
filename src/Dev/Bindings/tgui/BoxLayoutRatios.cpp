#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/BoxLayoutRatios.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassBoxLayoutRatios(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BoxLayoutRatios> bindBoxLayoutRatios
            = tguiNamespace.new_usertype<tgui::BoxLayoutRatios>("BoxLayoutRatios",
                sol::base_classes,
                sol::bases<tgui::BoxLayout, tgui::Group, tgui::Container,
                    tgui::Widget>());
        bindBoxLayoutRatios["add"] = sol::overload(
            static_cast<void (tgui::BoxLayoutRatios::*)(const tgui::Widget::Ptr&,
                const tgui::String&)>(&tgui::BoxLayoutRatios::add),
            static_cast<void (tgui::BoxLayoutRatios::*)(const tgui::Widget::Ptr&, float,
                const tgui::String&)>(&tgui::BoxLayoutRatios::add));
        bindBoxLayoutRatios["insert"]
            = sol::overload(static_cast<void (tgui::BoxLayoutRatios::*)(std::size_t,
                                const tgui::Widget::Ptr&, const tgui::String&)>(
                                &tgui::BoxLayoutRatios::insert),
                static_cast<void (tgui::BoxLayoutRatios::*)(
                    std::size_t, const tgui::Widget::Ptr&, float, const tgui::String&)>(
                    &tgui::BoxLayoutRatios::insert));
        bindBoxLayoutRatios["remove"]
            = sol::overload(static_cast<bool (tgui::BoxLayoutRatios::*)(std::size_t)>(
                                &tgui::BoxLayoutRatios::remove),
                static_cast<bool (tgui::BoxLayoutRatios::*)(const tgui::Widget::Ptr&)>(
                    &tgui::BoxLayoutRatios::remove),
                static_cast<bool (tgui::BoxLayoutRatios::*)(std::size_t)>(
                    &tgui::BoxLayoutRatios::remove));
        bindBoxLayoutRatios["removeAllWidgets"]
            = &tgui::BoxLayoutRatios::removeAllWidgets;
        bindBoxLayoutRatios["addSpace"] = &tgui::BoxLayoutRatios::addSpace;
        bindBoxLayoutRatios["insertSpace"] = &tgui::BoxLayoutRatios::insertSpace;
        bindBoxLayoutRatios["setRatio"] = sol::overload(
            static_cast<bool (tgui::BoxLayoutRatios::*)(tgui::Widget::Ptr, float)>(
                &tgui::BoxLayoutRatios::setRatio),
            static_cast<bool (tgui::BoxLayoutRatios::*)(std::size_t, float)>(
                &tgui::BoxLayoutRatios::setRatio));
        bindBoxLayoutRatios["getRatio"] = sol::overload(
            static_cast<float (tgui::BoxLayoutRatios::*)(tgui::Widget::Ptr) const>(
                &tgui::BoxLayoutRatios::getRatio),
            static_cast<float (tgui::BoxLayoutRatios::*)(std::size_t) const>(
                &tgui::BoxLayoutRatios::getRatio));
    }
};