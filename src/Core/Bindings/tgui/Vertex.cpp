#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Vertex.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassVertex(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Vertex> bindVertex
            = tguiNamespace.new_usertype<tgui::Vertex>("Vertex", sol::call_constructor,
                sol::constructors<tgui::Vertex(), tgui::Vertex(tgui::Vector2f),
                    tgui::Vertex(tgui::Vector2f, tgui::Vertex::Color),
                    tgui::Vertex(tgui::Vector2f, tgui::Vertex::Color, tgui::Vector2f)>());
        bindVertex["position"] = &tgui::Vertex::position;
        bindVertex["color"] = &tgui::Vertex::color;
        bindVertex["texCoords"] = &tgui::Vertex::texCoords;
    }
};