#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Loading/Serializer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSerializer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Serializer> bindSerializer
            = tguiNamespace.new_usertype<tgui::Serializer>(
                "Serializer", sol::call_constructor, sol::default_constructor);
        bindSerializer["serialize"] =

            [](tgui::Serializer* self, tgui::ObjectConverter object) {
                self->serialize(std::move(object));
            }

        ;
    }
};