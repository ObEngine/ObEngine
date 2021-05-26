#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/WidgetRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassRendererData(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RendererData> bindRendererData
            = tguiNamespace.new_usertype<tgui::RendererData>("RendererData",
                sol::call_constructor, sol::constructors<tgui::RendererData()>());
        bindRendererData["create"] = sol::overload(
            [](tgui::RendererData* self) -> std::shared_ptr<tgui::RendererData> {
                return self->create();
            },
            [](tgui::RendererData* self,
                const std::map<tgui::String, ObjectConverter>& init)
                -> std::shared_ptr<tgui::RendererData> { return self->create(init); });
        bindRendererData["createFromDataIONode"]
            = &tgui::RendererData::createFromDataIONode;
        bindRendererData["propertyValuePairs"] = &tgui::RendererData::propertyValuePairs;
        bindRendererData["observers"] = &tgui::RendererData::observers;
        bindRendererData["shared"] = &tgui::RendererData::shared;
    }
};