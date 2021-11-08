#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/Grid.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassGrid(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Grid> bindGrid
            = tguiNamespace.new_usertype<tgui::Grid>("Grid", sol::call_constructor,
                sol::constructors<tgui::Grid(), tgui::Grid(const char*),
                    tgui::Grid(const char*, bool), tgui::Grid(const tgui::Grid&)>(),
                sol::base_classes, sol::bases<tgui::Container, tgui::Widget>());
        bindGrid["operator="] = sol::overload(
            static_cast<tgui::Grid& (tgui::Grid::*)(const tgui::Grid&)>(&tgui::Grid::operator=),
            static_cast<tgui::Grid& (tgui::Grid::*)(tgui::Grid &&)>(&tgui::Grid::operator=));
        bindGrid["setSize"] = sol::overload(
            static_cast<void (tgui::Grid::*)(const tgui::Layout2d&)>(&tgui::Grid::setSize),
            static_cast<void (tgui::Grid::*)(const tgui::Layout2d&)>(&tgui::Grid::setSize),
            static_cast<void (tgui::Grid::*)(tgui::Layout, tgui::Layout)>(&tgui::Grid::setSize));
        bindGrid["setAutoSize"] = &tgui::Grid::setAutoSize;
        bindGrid["getAutoSize"] = &tgui::Grid::getAutoSize;
        bindGrid["remove"] = &tgui::Grid::remove;
        bindGrid["removeAllWidgets"] = &tgui::Grid::removeAllWidgets;
        bindGrid["addWidget"] = sol::overload(
            [](tgui::Grid* self, const tgui::Widget::Ptr& widget, std::size_t row,
                std::size_t column) -> void { return self->addWidget(widget, row, column); },
            [](tgui::Grid* self, const tgui::Widget::Ptr& widget, std::size_t row,
                std::size_t column, tgui::Grid::Alignment alignment) -> void {
                return self->addWidget(widget, row, column, alignment);
            },
            [](tgui::Grid* self, const tgui::Widget::Ptr& widget, std::size_t row,
                std::size_t column, tgui::Grid::Alignment alignment,
                const tgui::Padding& padding) -> void {
                return self->addWidget(widget, row, column, alignment, padding);
            });
        bindGrid["getWidget"] = &tgui::Grid::getWidget;
        bindGrid["getWidgetLocations"] = &tgui::Grid::getWidgetLocations;
        bindGrid["setWidgetPadding"] = sol::overload(
            [](tgui::Grid* self, const tgui::Widget::Ptr& widget) -> void {
                return self->setWidgetPadding(widget);
            },
            [](tgui::Grid* self, const tgui::Widget::Ptr& widget, const tgui::Padding& padding)
                -> void { return self->setWidgetPadding(widget, padding); },
            [](tgui::Grid* self, std::size_t row, std::size_t column) -> void {
                return self->setWidgetPadding(row, column);
            },
            [](tgui::Grid* self, std::size_t row, std::size_t column, const tgui::Padding& padding)
                -> void { return self->setWidgetPadding(row, column, padding); });
        bindGrid["getWidgetPadding"] = sol::overload(
            static_cast<tgui::Padding (tgui::Grid::*)(const tgui::Widget::Ptr&) const>(
                &tgui::Grid::getWidgetPadding),
            static_cast<tgui::Padding (tgui::Grid::*)(std::size_t, std::size_t) const>(
                &tgui::Grid::getWidgetPadding));
        bindGrid["setWidgetAlignment"] = sol::overload(
            [](tgui::Grid* self, const tgui::Widget::Ptr& widget) -> void {
                return self->setWidgetAlignment(widget);
            },
            [](tgui::Grid* self, const tgui::Widget::Ptr& widget, tgui::Grid::Alignment alignment)
                -> void { return self->setWidgetAlignment(widget, alignment); },
            [](tgui::Grid* self, std::size_t row, std::size_t column) -> void {
                return self->setWidgetAlignment(row, column);
            },
            [](tgui::Grid* self, std::size_t row, std::size_t column,
                tgui::Grid::Alignment alignment) -> void {
                return self->setWidgetAlignment(row, column, alignment);
            });
        bindGrid["getWidgetAlignment"] = sol::overload(
            static_cast<tgui::Grid::Alignment (tgui::Grid::*)(const tgui::Widget::Ptr&) const>(
                &tgui::Grid::getWidgetAlignment),
            static_cast<tgui::Grid::Alignment (tgui::Grid::*)(std::size_t, std::size_t) const>(
                &tgui::Grid::getWidgetAlignment));
        bindGrid["getGridWidgets"] = &tgui::Grid::getGridWidgets;
        bindGrid["isMouseOnWidget"] = &tgui::Grid::isMouseOnWidget;
        bindGrid["create"] = &tgui::Grid::create;
        bindGrid["copy"] = &tgui::Grid::copy;
    }
};