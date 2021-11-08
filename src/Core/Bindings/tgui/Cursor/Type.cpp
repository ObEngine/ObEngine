#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Cursor.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumType(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::Cursor::Type>("Type",
            { { "Arrow", tgui::Cursor::Type::Arrow }, { "Text", tgui::Cursor::Type::Text },
                { "Hand", tgui::Cursor::Type::Hand }, { "SizeLeft", tgui::Cursor::Type::SizeLeft },
                { "SizeRight", tgui::Cursor::Type::SizeRight },
                { "SizeTop", tgui::Cursor::Type::SizeTop },
                { "SizeBottom", tgui::Cursor::Type::SizeBottom },
                { "SizeTopLeft", tgui::Cursor::Type::SizeTopLeft },
                { "SizeBottomRight", tgui::Cursor::Type::SizeBottomRight },
                { "SizeBottomLeft", tgui::Cursor::Type::SizeBottomLeft },
                { "SizeTopRight", tgui::Cursor::Type::SizeTopRight },
                { "Crosshair", tgui::Cursor::Type::Crosshair },
                { "Help", tgui::Cursor::Type::Help },
                { "NotAllowed", tgui::Cursor::Type::NotAllowed } });
    }
};