#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Renderers/WidgetRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassRendererData(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RendererData> bindRendererData
            = tguiNamespace.new_usertype<tgui::RendererData>(
                "RendererData", sol::call_constructor, sol::constructors<tgui::RendererData()>());
        bindRendererData["create"] = sol::overload(
            []() -> std::shared_ptr<tgui::RendererData> { return tgui::RendererData::create(); },
            [](const std::map<tgui::String, tgui::ObjectConverter>& init)
                -> std::shared_ptr<tgui::RendererData> {
                return tgui::RendererData::create(init);
            });
        bindRendererData["createFromDataIONode"] = &tgui::RendererData::createFromDataIONode;
        bindRendererData["propertyValuePairs"] = &tgui::RendererData::propertyValuePairs;
        bindRendererData["observers"] = &tgui::RendererData::observers;
        bindRendererData["shared"] = &tgui::RendererData::shared;
    }
};