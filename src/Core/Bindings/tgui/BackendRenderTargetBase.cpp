#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/BackendRenderTarget.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassBackendRenderTargetBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BackendRenderTargetBase> bindBackendRenderTargetBase
            = tguiNamespace.new_usertype<tgui::BackendRenderTargetBase>("BackendRenderTargetBase");
        bindBackendRenderTargetBase["setView"] = &tgui::BackendRenderTargetBase::setView;
        bindBackendRenderTargetBase["drawGui"] = &tgui::BackendRenderTargetBase::drawGui;
        bindBackendRenderTargetBase["drawWidget"] = &tgui::BackendRenderTargetBase::drawWidget;
        bindBackendRenderTargetBase["addClippingLayer"]
            = &tgui::BackendRenderTargetBase::addClippingLayer;
        bindBackendRenderTargetBase["removeClippingLayer"]
            = &tgui::BackendRenderTargetBase::removeClippingLayer;
        bindBackendRenderTargetBase["drawBorders"] = &tgui::BackendRenderTargetBase::drawBorders;
        bindBackendRenderTargetBase["drawFilledRect"]
            = &tgui::BackendRenderTargetBase::drawFilledRect;
        bindBackendRenderTargetBase["drawSprite"] = &tgui::BackendRenderTargetBase::drawSprite;
        bindBackendRenderTargetBase["drawText"] = &tgui::BackendRenderTargetBase::drawText;
        bindBackendRenderTargetBase["drawTriangles"] = sol::overload(
            [](tgui::BackendRenderTargetBase* self, const tgui::RenderStates& states,
                const tgui::Vertex* vertices, std::size_t vertexCount) -> void {
                return self->drawTriangles(states, vertices, vertexCount);
            },
            [](tgui::BackendRenderTargetBase* self, const tgui::RenderStates& states,
                const tgui::Vertex* vertices, std::size_t vertexCount, const int* indices) -> void {
                return self->drawTriangles(states, vertices, vertexCount, indices);
            },
            [](tgui::BackendRenderTargetBase* self, const tgui::RenderStates& states,
                const tgui::Vertex* vertices, std::size_t vertexCount, const int* indices,
                std::size_t indexCount) -> void {
                return self->drawTriangles(states, vertices, vertexCount, indices, indexCount);
            },
            [](tgui::BackendRenderTargetBase* self, const tgui::RenderStates& states,
                std::initializer_list<tgui::Vertex> vertices) -> void {
                return self->drawTriangles(states, vertices);
            },
            [](tgui::BackendRenderTargetBase* self, const tgui::RenderStates& states,
                std::initializer_list<tgui::Vertex> vertices,
                std::initializer_list<int> indices) -> void {
                return self->drawTriangles(states, vertices, indices);
            });
        bindBackendRenderTargetBase["drawCircle"] = sol::overload(
            [](tgui::BackendRenderTargetBase* self, const tgui::RenderStates& states, float size,
                const tgui::Color& backgroundColor) -> void {
                return self->drawCircle(states, size, backgroundColor);
            },
            [](tgui::BackendRenderTargetBase* self, const tgui::RenderStates& states, float size,
                const tgui::Color& backgroundColor, float borderThickness) -> void {
                return self->drawCircle(states, size, backgroundColor, borderThickness);
            },
            [](tgui::BackendRenderTargetBase* self, const tgui::RenderStates& states, float size,
                const tgui::Color& backgroundColor, float borderThickness,
                const tgui::Color& borderColor) -> void {
                return self->drawCircle(
                    states, size, backgroundColor, borderThickness, borderColor);
            });
        bindBackendRenderTargetBase["drawRoundedRectangle"] = sol::overload(
            [](tgui::BackendRenderTargetBase* self, const tgui::RenderStates& states,
                const tgui::Vector2f& size, const tgui::Color& backgroundColor,
                float radius) -> void {
                return self->drawRoundedRectangle(states, size, backgroundColor, radius);
            },
            [](tgui::BackendRenderTargetBase* self, const tgui::RenderStates& states,
                const tgui::Vector2f& size, const tgui::Color& backgroundColor, float radius,
                const tgui::Borders& borders) -> void {
                return self->drawRoundedRectangle(states, size, backgroundColor, radius, borders);
            },
            [](tgui::BackendRenderTargetBase* self, const tgui::RenderStates& states,
                const tgui::Vector2f& size, const tgui::Color& backgroundColor, float radius,
                const tgui::Borders& borders, const tgui::Color& borderColor) -> void {
                return self->drawRoundedRectangle(
                    states, size, backgroundColor, radius, borders, borderColor);
            });
    }
};