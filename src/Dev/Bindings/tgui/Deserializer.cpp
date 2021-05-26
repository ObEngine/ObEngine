#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Loading/Deserializer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassDeserializer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Deserializer> bindDeserializer
            = tguiNamespace.new_usertype<tgui::Deserializer>(
                "Deserializer", sol::call_constructor, sol::default_constructor);
        bindDeserializer["deserialize"] = &tgui::Deserializer::deserialize;
        bindDeserializer["setFunction"] = &tgui::Deserializer::setFunction;
        bindDeserializer["getFunction"] = &tgui::Deserializer::getFunction;
        bindDeserializer["split"] = &tgui::Deserializer::split;
    }
};