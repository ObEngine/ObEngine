#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Color.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassColor(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Color> bindColor = tguiNamespace.new_usertype<tgui::Color>("Color",
            sol::call_constructor,
            sol::constructors<tgui::Color(), tgui::Color(std::uint8_t, std::uint8_t, std::uint8_t),
                tgui::Color(std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t),
                tgui::Color(const tgui::String&), tgui::Color(const char*)>());
        bindColor["isSet"] = &tgui::Color::isSet;
        bindColor["getRed"] = &tgui::Color::getRed;
        bindColor["getGreen"] = &tgui::Color::getGreen;
        bindColor["getBlue"] = &tgui::Color::getBlue;
        bindColor["getAlpha"] = &tgui::Color::getAlpha;
        bindColor[sol::meta_function::equal_to] = &tgui::Color::operator==;
        bindColor["applyOpacity"] = &tgui::Color::applyOpacity;
        bindColor["Black"] = sol::var(&tgui::Color::Black);
        bindColor["White"] = sol::var(&tgui::Color::White);
        bindColor["Red"] = sol::var(&tgui::Color::Red);
        bindColor["Green"] = sol::var(&tgui::Color::Green);
        bindColor["Blue"] = sol::var(&tgui::Color::Blue);
        bindColor["Yellow"] = sol::var(&tgui::Color::Yellow);
        bindColor["Magenta"] = sol::var(&tgui::Color::Magenta);
        bindColor["Cyan"] = sol::var(&tgui::Color::Cyan);
        bindColor["Transparent"] = sol::var(&tgui::Color::Transparent);
        bindColor["colorMap"] = sol::var(&tgui::Color::colorMap);
    }
};