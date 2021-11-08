#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/ObjectConverter.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassObjectConverter(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ObjectConverter> bindObjectConverter
            = tguiNamespace.new_usertype<tgui::ObjectConverter>("ObjectConverter",
                sol::call_constructor,
                sol::constructors<tgui::ObjectConverter(), tgui::ObjectConverter(const char*),
                    tgui::ObjectConverter(const tgui::String&), tgui::ObjectConverter(tgui::Font),
                    tgui::ObjectConverter(tgui::Color), tgui::ObjectConverter(bool),
                    tgui::ObjectConverter(const tgui::Outline&),
                    tgui::ObjectConverter(const tgui::Texture&),
                    tgui::ObjectConverter(tgui::TextStyle), tgui::ObjectConverter(tgui::TextStyles),
                    tgui::ObjectConverter(std::shared_ptr<tgui::RendererData>)>());
        bindObjectConverter["getString"] = &tgui::ObjectConverter::getString;
        bindObjectConverter["getFont"] = &tgui::ObjectConverter::getFont;
        bindObjectConverter["getColor"] = &tgui::ObjectConverter::getColor;
        bindObjectConverter["getOutline"] = &tgui::ObjectConverter::getOutline;
        bindObjectConverter["getBool"] = &tgui::ObjectConverter::getBool;
        bindObjectConverter["getNumber"] = &tgui::ObjectConverter::getNumber;
        bindObjectConverter["getTexture"] = &tgui::ObjectConverter::getTexture;
        bindObjectConverter["getTextStyle"] = &tgui::ObjectConverter::getTextStyle;
        bindObjectConverter["getRenderer"] = &tgui::ObjectConverter::getRenderer;
        bindObjectConverter["getType"] = &tgui::ObjectConverter::getType;
        bindObjectConverter[sol::meta_function::equal_to] = &tgui::ObjectConverter::operator==;
    }
};