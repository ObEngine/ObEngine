#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/ObjectConverter.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumType(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::ObjectConverter::Type>("Type",
            { { "None", tgui::ObjectConverter::Type::None },
                { "Bool", tgui::ObjectConverter::Type::Bool },
                { "Font", tgui::ObjectConverter::Type::Font },
                { "Color", tgui::ObjectConverter::Type::Color },
                { "String", tgui::ObjectConverter::Type::String },
                { "Number", tgui::ObjectConverter::Type::Number },
                { "Outline", tgui::ObjectConverter::Type::Outline },
                { "Texture", tgui::ObjectConverter::Type::Texture },
                { "TextStyle", tgui::ObjectConverter::Type::TextStyle },
                { "RendererData", tgui::ObjectConverter::Type::RendererData } });
    }
};