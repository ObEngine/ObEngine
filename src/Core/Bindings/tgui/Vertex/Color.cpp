#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Vertex.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassColor(sol::state_view state)
    {
        sol::table VertexNamespace = state["tgui"]["Vertex"].get<sol::table>();
        sol::usertype<tgui::Vertex::Color> bindColor
            = VertexNamespace.new_usertype<tgui::Vertex::Color>("Color", sol::call_constructor,
                sol::constructors<tgui::Vertex::Color(), tgui::Vertex::Color(std::uint8_t),
                    tgui::Vertex::Color(std::uint8_t, std::uint8_t),
                    tgui::Vertex::Color(std::uint8_t, std::uint8_t, std::uint8_t),
                    tgui::Vertex::Color(std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t)>());
        bindColor["red"] = &tgui::Vertex::Color::red;
        bindColor["green"] = &tgui::Vertex::Color::green;
        bindColor["blue"] = &tgui::Vertex::Color::blue;
        bindColor["alpha"] = &tgui::Vertex::Color::alpha;
    }
};