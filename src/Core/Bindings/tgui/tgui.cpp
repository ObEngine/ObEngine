#include <Bindings/tgui/tgui.hpp>

#include <TGUI/AbsoluteOrRelativeValue.hpp>
#include <TGUI/Animation.hpp>
#include <TGUI/Any.hpp>
#include <TGUI/Backend.hpp>
#include <TGUI/BackendFont.hpp>
#include <TGUI/BackendRenderTarget.hpp>
#include <TGUI/BackendText.hpp>
#include <TGUI/BackendTexture.hpp>
#include <TGUI/Color.hpp>
#include <TGUI/Container.hpp>
#include <TGUI/Cursor.hpp>
#include <TGUI/CustomWidgetForBindings.hpp>
#include <TGUI/DefaultBackendWindow.hpp>
#include <TGUI/Duration.hpp>
#include <TGUI/Event.hpp>
#include <TGUI/Exception.hpp>
#include <TGUI/FileDialogIconLoader.hpp>
#include <TGUI/Filesystem.hpp>
#include <TGUI/Font.hpp>
#include <TGUI/Global.hpp>
#include <TGUI/GuiBase.hpp>
#include <TGUI/Layout.hpp>
#include <TGUI/Loading/DataIO.hpp>
#include <TGUI/Loading/Deserializer.hpp>
#include <TGUI/Loading/ImageLoader.hpp>
#include <TGUI/Loading/Serializer.hpp>
#include <TGUI/Loading/Theme.hpp>
#include <TGUI/Loading/ThemeLoader.hpp>
#include <TGUI/Loading/WidgetFactory.hpp>
#include <TGUI/ObjectConverter.hpp>
#include <TGUI/Outline.hpp>
#include <TGUI/RelFloatRect.hpp>
#include <TGUI/RenderStates.hpp>
#include <TGUI/Renderers/BoxLayoutRenderer.hpp>
#include <TGUI/Renderers/ButtonRenderer.hpp>
#include <TGUI/Renderers/ChatBoxRenderer.hpp>
#include <TGUI/Renderers/CheckBoxRenderer.hpp>
#include <TGUI/Renderers/ChildWindowRenderer.hpp>
#include <TGUI/Renderers/ColorPickerRenderer.hpp>
#include <TGUI/Renderers/ComboBoxRenderer.hpp>
#include <TGUI/Renderers/EditBoxRenderer.hpp>
#include <TGUI/Renderers/FileDialogRenderer.hpp>
#include <TGUI/Renderers/GroupRenderer.hpp>
#include <TGUI/Renderers/KnobRenderer.hpp>
#include <TGUI/Renderers/LabelRenderer.hpp>
#include <TGUI/Renderers/ListBoxRenderer.hpp>
#include <TGUI/Renderers/ListViewRenderer.hpp>
#include <TGUI/Renderers/MenuBarRenderer.hpp>
#include <TGUI/Renderers/MessageBoxRenderer.hpp>
#include <TGUI/Renderers/PanelRenderer.hpp>
#include <TGUI/Renderers/PictureRenderer.hpp>
#include <TGUI/Renderers/ProgressBarRenderer.hpp>
#include <TGUI/Renderers/RadioButtonRenderer.hpp>
#include <TGUI/Renderers/RangeSliderRenderer.hpp>
#include <TGUI/Renderers/ScrollablePanelRenderer.hpp>
#include <TGUI/Renderers/ScrollbarRenderer.hpp>
#include <TGUI/Renderers/SeparatorLineRenderer.hpp>
#include <TGUI/Renderers/SliderRenderer.hpp>
#include <TGUI/Renderers/SpinButtonRenderer.hpp>
#include <TGUI/Renderers/TabsRenderer.hpp>
#include <TGUI/Renderers/TextAreaRenderer.hpp>
#include <TGUI/Renderers/TreeViewRenderer.hpp>
#include <TGUI/Renderers/WidgetRenderer.hpp>
#include <TGUI/Signal.hpp>
#include <TGUI/SignalManager.hpp>
#include <TGUI/Sprite.hpp>
#include <TGUI/String.hpp>
#include <TGUI/SubwidgetContainer.hpp>
#include <TGUI/SvgImage.hpp>
#include <TGUI/Text.hpp>
#include <TGUI/TextStyle.hpp>
#include <TGUI/Texture.hpp>
#include <TGUI/TextureData.hpp>
#include <TGUI/TextureManager.hpp>
#include <TGUI/Timer.hpp>
#include <TGUI/ToolTip.hpp>
#include <TGUI/Transform.hpp>
#include <TGUI/Vertex.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/Widgets/BitmapButton.hpp>
#include <TGUI/Widgets/BoxLayout.hpp>
#include <TGUI/Widgets/BoxLayoutRatios.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/ButtonBase.hpp>
#include <TGUI/Widgets/ChatBox.hpp>
#include <TGUI/Widgets/CheckBox.hpp>
#include <TGUI/Widgets/ChildWindow.hpp>
#include <TGUI/Widgets/ClickableWidget.hpp>
#include <TGUI/Widgets/ColorPicker.hpp>
#include <TGUI/Widgets/ComboBox.hpp>
#include <TGUI/Widgets/EditBox.hpp>
#include <TGUI/Widgets/FileDialog.hpp>
#include <TGUI/Widgets/Grid.hpp>
#include <TGUI/Widgets/Group.hpp>
#include <TGUI/Widgets/HorizontalLayout.hpp>
#include <TGUI/Widgets/HorizontalWrap.hpp>
#include <TGUI/Widgets/Knob.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/ListBox.hpp>
#include <TGUI/Widgets/ListView.hpp>
#include <TGUI/Widgets/MenuBar.hpp>
#include <TGUI/Widgets/MessageBox.hpp>
#include <TGUI/Widgets/Panel.hpp>
#include <TGUI/Widgets/Picture.hpp>
#include <TGUI/Widgets/ProgressBar.hpp>
#include <TGUI/Widgets/RadioButton.hpp>
#include <TGUI/Widgets/RadioButtonGroup.hpp>
#include <TGUI/Widgets/RangeSlider.hpp>
#include <TGUI/Widgets/ScrollablePanel.hpp>
#include <TGUI/Widgets/Scrollbar.hpp>
#include <TGUI/Widgets/SeparatorLine.hpp>
#include <TGUI/Widgets/Slider.hpp>
#include <TGUI/Widgets/SpinButton.hpp>
#include <TGUI/Widgets/SpinControl.hpp>
#include <TGUI/Widgets/TabContainer.hpp>
#include <TGUI/Widgets/Tabs.hpp>
#include <TGUI/Widgets/TextArea.hpp>
#include <TGUI/Widgets/ToggleButton.hpp>
#include <TGUI/Widgets/TreeView.hpp>
#include <TGUI/Widgets/VerticalLayout.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumShowAnimationType(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::ShowAnimationType>("ShowAnimationType",
            { { "Fade", tgui::ShowAnimationType::Fade },
                { "Scale", tgui::ShowAnimationType::Scale },
                { "SlideToRight", tgui::ShowAnimationType::SlideToRight },
                { "SlideToLeft", tgui::ShowAnimationType::SlideToLeft },
                { "SlideToBottom", tgui::ShowAnimationType::SlideToBottom },
                { "SlideToTop", tgui::ShowAnimationType::SlideToTop },
                { "SlideFromLeft", tgui::ShowAnimationType::SlideFromLeft },
                { "SlideFromRight", tgui::ShowAnimationType::SlideFromRight },
                { "SlideFromTop", tgui::ShowAnimationType::SlideFromTop },
                { "SlideFromBottom", tgui::ShowAnimationType::SlideFromBottom } });
    }
    void LoadEnumTextStyle(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::TextStyle>("TextStyle",
            { { "Regular", tgui::TextStyle::Regular }, { "Bold", tgui::TextStyle::Bold },
                { "Italic", tgui::TextStyle::Italic },
                { "Underlined", tgui::TextStyle::Underlined },
                { "StrikeThrough", tgui::TextStyle::StrikeThrough } });
    }
    void LoadClassAbsoluteOrRelativeValue(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::AbsoluteOrRelativeValue> bindAbsoluteOrRelativeValue
            = tguiNamespace.new_usertype<tgui::AbsoluteOrRelativeValue>(
                "AbsoluteOrRelativeValue", sol::call_constructor,
                sol::constructors<tgui::AbsoluteOrRelativeValue(),
                    tgui::AbsoluteOrRelativeValue(T),
                    tgui::AbsoluteOrRelativeValue(const char*),
                    tgui::AbsoluteOrRelativeValue(const gui::String&)>());
        bindAbsoluteOrRelativeValue["getValue"]
            = &tgui::AbsoluteOrRelativeValue::getValue;
        bindAbsoluteOrRelativeValue["getRatio"]
            = &tgui::AbsoluteOrRelativeValue::getRatio;
        bindAbsoluteOrRelativeValue["isConstant"]
            = &tgui::AbsoluteOrRelativeValue::isConstant;
        bindAbsoluteOrRelativeValue["updateParentSize"]
            = &tgui::AbsoluteOrRelativeValue::updateParentSize;
        bindAbsoluteOrRelativeValue["toString"]
            = &tgui::AbsoluteOrRelativeValue::toString;
    }
    void LoadClassBackendBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BackendBase> bindBackendBase
            = tguiNamespace.new_usertype<tgui::BackendBase>("BackendBase");
        bindBackendBase["operator="] = &tgui::BackendBase::operator=;
        bindBackendBase["setDestroyOnLastGuiDetatch"]
            = &tgui::BackendBase::setDestroyOnLastGuiDetatch;
        bindBackendBase["attachGui"] = &tgui::BackendBase::attachGui;
        bindBackendBase["detatchGui"] = &tgui::BackendBase::detatchGui;
        bindBackendBase["createDefaultFont"] = &tgui::BackendBase::createDefaultFont;
        bindBackendBase["createFont"] = &tgui::BackendBase::createFont;
        bindBackendBase["createText"] = &tgui::BackendBase::createText;
        bindBackendBase["createTexture"] = &tgui::BackendBase::createTexture;
        bindBackendBase["setMouseCursorStyle"] = &tgui::BackendBase::setMouseCursorStyle;
        bindBackendBase["resetMouseCursorStyle"]
            = &tgui::BackendBase::resetMouseCursorStyle;
        bindBackendBase["setMouseCursor"] = &tgui::BackendBase::setMouseCursor;
        bindBackendBase["openVirtualKeyboard"] = &tgui::BackendBase::openVirtualKeyboard;
        bindBackendBase["closeVirtualKeyboard"]
            = &tgui::BackendBase::closeVirtualKeyboard;
        bindBackendBase["isKeyboardModifierPressed"]
            = &tgui::BackendBase::isKeyboardModifierPressed;
        bindBackendBase["setClipboard"] = &tgui::BackendBase::setClipboard;
        bindBackendBase["getClipboard"] = &tgui::BackendBase::getClipboard;
        bindBackendBase["readFileFromAndroidAssets"]
            = &tgui::BackendBase::readFileFromAndroidAssets;
    }
    void LoadClassBackendFontBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BackendFontBase> bindBackendFontBase
            = tguiNamespace.new_usertype<tgui::BackendFontBase>("BackendFontBase");
        bindBackendFontBase["loadFromFile"] = &tgui::BackendFontBase::loadFromFile;
        bindBackendFontBase["loadFromMemory"] = &tgui::BackendFontBase::loadFromMemory;
        bindBackendFontBase["getGlyph"] = sol::overload(
            [](tgui::BackendFontBase* self, char32_t codePoint,
                unsigned int characterSize, bool bold) -> gui::FontGlyph {
                return self->getGlyph(codePoint, characterSize, bold);
            },
            [](tgui::BackendFontBase* self, char32_t codePoint,
                unsigned int characterSize, bool bold,
                float outlineThickness) -> gui::FontGlyph {
                return self->getGlyph(codePoint, characterSize, bold, outlineThickness);
            });
        bindBackendFontBase["getKerning"] = &tgui::BackendFontBase::getKerning;
        bindBackendFontBase["getLineSpacing"] = &tgui::BackendFontBase::getLineSpacing;
    }
    void LoadClassBackendRenderTargetBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BackendRenderTargetBase> bindBackendRenderTargetBase
            = tguiNamespace.new_usertype<tgui::BackendRenderTargetBase>(
                "BackendRenderTargetBase");
        bindBackendRenderTargetBase["setView"] = &tgui::BackendRenderTargetBase::setView;
        bindBackendRenderTargetBase["drawGui"] = &tgui::BackendRenderTargetBase::drawGui;
        bindBackendRenderTargetBase["drawWidget"]
            = &tgui::BackendRenderTargetBase::drawWidget;
        bindBackendRenderTargetBase["addClippingLayer"]
            = &tgui::BackendRenderTargetBase::addClippingLayer;
        bindBackendRenderTargetBase["removeClippingLayer"]
            = &tgui::BackendRenderTargetBase::removeClippingLayer;
        bindBackendRenderTargetBase["drawBorders"]
            = &tgui::BackendRenderTargetBase::drawBorders;
        bindBackendRenderTargetBase["drawFilledRect"]
            = &tgui::BackendRenderTargetBase::drawFilledRect;
        bindBackendRenderTargetBase["drawSprite"]
            = &tgui::BackendRenderTargetBase::drawSprite;
        bindBackendRenderTargetBase["drawText"]
            = &tgui::BackendRenderTargetBase::drawText;
        bindBackendRenderTargetBase["drawTriangles"] = sol::overload(
            static_cast<void (tgui::BackendRenderTargetBase::*)(const gui::RenderStates&,
                const gui::Vertex*, std::size_t, const int*, std::size_t)>(
                &tgui::BackendRenderTargetBase::drawTriangles),
            static_cast<void (tgui::BackendRenderTargetBase::*)(const gui::RenderStates&,
                std::initializer_list<gui::Vertex>, std::initializer_list<int>)>(
                &tgui::BackendRenderTargetBase::drawTriangles));
        bindBackendRenderTargetBase["drawCircle"] = sol::overload(
            [](tgui::BackendRenderTargetBase* self, const gui::RenderStates& states,
                float size, const gui::Color& backgroundColor) -> void {
                return self->drawCircle(states, size, backgroundColor);
            },
            [](tgui::BackendRenderTargetBase* self, const gui::RenderStates& states,
                float size, const gui::Color& backgroundColor,
                float borderThickness) -> void {
                return self->drawCircle(states, size, backgroundColor, borderThickness);
            },
            [](tgui::BackendRenderTargetBase* self, const gui::RenderStates& states,
                float size, const gui::Color& backgroundColor, float borderThickness,
                const gui::Color& borderColor) -> void {
                return self->drawCircle(
                    states, size, backgroundColor, borderThickness, borderColor);
            });
        bindBackendRenderTargetBase["drawRoundedRectangle"] = sol::overload(
            [](tgui::BackendRenderTargetBase* self, const gui::RenderStates& states,
                const tgui::Vector2f& size, const gui::Color& backgroundColor,
                float radius) -> void {
                return self->drawRoundedRectangle(states, size, backgroundColor, radius);
            },
            [](tgui::BackendRenderTargetBase* self, const gui::RenderStates& states,
                const tgui::Vector2f& size, const gui::Color& backgroundColor,
                float radius, const tgui::Borders& borders) -> void {
                return self->drawRoundedRectangle(
                    states, size, backgroundColor, radius, borders);
            },
            [](tgui::BackendRenderTargetBase* self, const gui::RenderStates& states,
                const tgui::Vector2f& size, const gui::Color& backgroundColor,
                float radius, const tgui::Borders& borders,
                const gui::Color& borderColor) -> void {
                return self->drawRoundedRectangle(
                    states, size, backgroundColor, radius, borders, borderColor);
            });
    }
    void LoadClassBackendTextureBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BackendTextureBase> bindBackendTextureBase
            = tguiNamespace.new_usertype<tgui::BackendTextureBase>("BackendTextureBase");
        bindBackendTextureBase["load"] = &tgui::BackendTextureBase::load;
        bindBackendTextureBase["getSize"] = &tgui::BackendTextureBase::getSize;
        bindBackendTextureBase["setSmooth"] = &tgui::BackendTextureBase::setSmooth;
        bindBackendTextureBase["isSmooth"] = &tgui::BackendTextureBase::isSmooth;
        bindBackendTextureBase["isTransparentPixel"]
            = &tgui::BackendTextureBase::isTransparentPixel;
    }
    void LoadClassBackendTextBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BackendTextBase> bindBackendTextBase
            = tguiNamespace.new_usertype<tgui::BackendTextBase>("BackendTextBase");
        bindBackendTextBase["getSize"] = &tgui::BackendTextBase::getSize;
        bindBackendTextBase["setString"] = &tgui::BackendTextBase::setString;
        bindBackendTextBase["setCharacterSize"]
            = &tgui::BackendTextBase::setCharacterSize;
        bindBackendTextBase["setFillColor"] = &tgui::BackendTextBase::setFillColor;
        bindBackendTextBase["setOutlineColor"] = &tgui::BackendTextBase::setOutlineColor;
        bindBackendTextBase["setOutlineThickness"]
            = &tgui::BackendTextBase::setOutlineThickness;
        bindBackendTextBase["setStyle"] = &tgui::BackendTextBase::setStyle;
        bindBackendTextBase["setFont"] = &tgui::BackendTextBase::setFont;
        bindBackendTextBase["findCharacterPos"]
            = &tgui::BackendTextBase::findCharacterPos;
    }
    void LoadClassBaseThemeLoader(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BaseThemeLoader> bindBaseThemeLoader
            = tguiNamespace.new_usertype<tgui::BaseThemeLoader>("BaseThemeLoader");
        bindBaseThemeLoader["preload"] = &tgui::BaseThemeLoader::preload;
        bindBaseThemeLoader["load"] = &tgui::BaseThemeLoader::load;
        bindBaseThemeLoader["canLoad"] = &tgui::BaseThemeLoader::canLoad;
    }
    void LoadClassBitmapButton(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BitmapButton> bindBitmapButton
            = tguiNamespace.new_usertype<tgui::BitmapButton>("BitmapButton",
                sol::call_constructor,
                sol::constructors<tgui::BitmapButton(), tgui::BitmapButton(const char*),
                    tgui::BitmapButton(const char*, bool),
                    tgui::BitmapButton(const gui::BitmapButton&),
                    tgui::BitmapButton(gui::BitmapButton &&)>(),
                sol::base_classes,
                sol::bases<tgui::Button, tgui::ButtonBase, tgui::ClickableWidget,
                    tgui::Widget>());
        bindBitmapButton["operator="] = sol::overload(
            static_cast<gui::BitmapButton& (
                tgui::BitmapButton::*)(const gui::BitmapButton&)>(
                &tgui::BitmapButton::operator=),
            static_cast<gui::BitmapButton& (tgui::BitmapButton::*)(gui::BitmapButton &&)>(
                &tgui::BitmapButton::operator=));
        bindBitmapButton["setSize"] = sol::overload(
            static_cast<void (tgui::BitmapButton::*)(const gui::Layout2d&)>(
                &tgui::BitmapButton::setSize),
            static_cast<void (tgui::BitmapButton::*)(const gui::Layout2d&)>(
                &tgui::BitmapButton::setSize),
            static_cast<void (tgui::BitmapButton::*)(gui::Layout, gui::Layout)>(
                &tgui::BitmapButton::setSize));
        bindBitmapButton["setText"] = &tgui::BitmapButton::setText;
        bindBitmapButton["setImage"] = &tgui::BitmapButton::setImage;
        bindBitmapButton["getImage"] = &tgui::BitmapButton::getImage;
        bindBitmapButton["setImageScaling"] = &tgui::BitmapButton::setImageScaling;
        bindBitmapButton["getImageScaling"] = &tgui::BitmapButton::getImageScaling;
        bindBitmapButton["create"] = sol::overload(
            [](tgui::BitmapButton* self)
                -> gui::BitmapButton1ae37149a58ad65eff3a1f255a496a5103 {
                return self->create();
            },
            [](tgui::BitmapButton* self, const gui::String& text)
                -> gui::BitmapButton1ae37149a58ad65eff3a1f255a496a5103 {
                return self->create(text);
            });
        bindBitmapButton["copy"] = &tgui::BitmapButton::copy;
    }
    void LoadClassBoxLayout(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BoxLayout> bindBoxLayout
            = tguiNamespace.new_usertype<tgui::BoxLayout>("BoxLayout", sol::base_classes,
                sol::bases<tgui::Group, tgui::Container, tgui::Widget>());
        bindBoxLayout["getSharedRenderer"]
            = sol::overload(static_cast<gui::BoxLayoutRenderer* (tgui::BoxLayout::*)()>(
                                &tgui::BoxLayout::getSharedRenderer),
                static_cast<const gui::BoxLayoutRenderer* (tgui::BoxLayout::*)() const>(
                    &tgui::BoxLayout::getSharedRenderer));
        bindBoxLayout["getRenderer"]
            = sol::overload(static_cast<gui::BoxLayoutRenderer* (tgui::BoxLayout::*)()>(
                                &tgui::BoxLayout::getRenderer),
                static_cast<const gui::BoxLayoutRenderer* (tgui::BoxLayout::*)() const>(
                    &tgui::BoxLayout::getRenderer));
        bindBoxLayout["setSize"]
            = sol::overload(static_cast<void (tgui::BoxLayout::*)(const gui::Layout2d&)>(
                                &tgui::BoxLayout::setSize),
                static_cast<void (tgui::BoxLayout::*)(const gui::Layout2d&)>(
                    &tgui::BoxLayout::setSize),
                static_cast<void (tgui::BoxLayout::*)(gui::Layout, gui::Layout)>(
                    &tgui::BoxLayout::setSize));
        bindBoxLayout["add"] = sol::overload(
            [](tgui::BoxLayout* self,
                const gui::Widget1a388912f13898735531886bc676b14f81& widget) -> void {
                return self->add(widget);
            },
            [](tgui::BoxLayout* self,
                const gui::Widget1a388912f13898735531886bc676b14f81& widget,
                const gui::String& widgetName) -> void {
                return self->add(widget, widgetName);
            });
        bindBoxLayout["insert"] = sol::overload(
            [](tgui::BoxLayout* self, std::size_t index,
                const gui::Widget1a388912f13898735531886bc676b14f81& widget) -> void {
                return self->insert(index, widget);
            },
            [](tgui::BoxLayout* self, std::size_t index,
                const gui::Widget1a388912f13898735531886bc676b14f81& widget,
                const gui::String& widgetName) -> void {
                return self->insert(index, widget, widgetName);
            });
        bindBoxLayout["remove"]
            = sol::overload(static_cast<bool (tgui::BoxLayout::*)(
                                const gui::Widget1a388912f13898735531886bc676b14f81&)>(
                                &tgui::BoxLayout::remove),
                static_cast<bool (tgui::BoxLayout::*)(std::size_t)>(
                    &tgui::BoxLayout::remove));
        bindBoxLayout["get"] = sol::overload(
            static_cast<gui::Widget1a388912f13898735531886bc676b14f81 (
                tgui::BoxLayout::*)(std::size_t) const>(&tgui::BoxLayout::get),
            static_cast<gui::Widget1a388912f13898735531886bc676b14f81 (
                tgui::BoxLayout::*)(const gui::String&)>(&tgui::BoxLayout::get));
    }
    void LoadClassBoxLayoutRatios(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BoxLayoutRatios> bindBoxLayoutRatios
            = tguiNamespace.new_usertype<tgui::BoxLayoutRatios>("BoxLayoutRatios",
                sol::call_constructor,
                sol::constructors<tgui::BoxLayoutRatios(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::BoxLayout, tgui::Group, tgui::Container,
                    tgui::Widget>());
        bindBoxLayoutRatios["add"]
            = sol::overload(static_cast<void (tgui::BoxLayoutRatios::*)(
                                const gui::Widget1a388912f13898735531886bc676b14f81&,
                                const gui::String&)>(&tgui::BoxLayoutRatios::add),
                static_cast<void (tgui::BoxLayoutRatios::*)(
                    const gui::Widget1a388912f13898735531886bc676b14f81&, float,
                    const gui::String&)>(&tgui::BoxLayoutRatios::add));
        bindBoxLayoutRatios["insert"]
            = sol::overload(static_cast<void (tgui::BoxLayoutRatios::*)(std::size_t,
                                const gui::Widget1a388912f13898735531886bc676b14f81&,
                                const gui::String&)>(&tgui::BoxLayoutRatios::insert),
                static_cast<void (tgui::BoxLayoutRatios::*)(std::size_t,
                    const gui::Widget1a388912f13898735531886bc676b14f81&, float,
                    const gui::String&)>(&tgui::BoxLayoutRatios::insert));
        bindBoxLayoutRatios["remove"]
            = sol::overload(static_cast<bool (tgui::BoxLayoutRatios::*)(std::size_t)>(
                                &tgui::BoxLayoutRatios::remove),
                static_cast<bool (tgui::BoxLayoutRatios::*)(
                    const gui::Widget1a388912f13898735531886bc676b14f81&)>(
                    &tgui::BoxLayoutRatios::remove),
                static_cast<bool (tgui::BoxLayoutRatios::*)(std::size_t)>(
                    &tgui::BoxLayoutRatios::remove));
        bindBoxLayoutRatios["removeAllWidgets"]
            = &tgui::BoxLayoutRatios::removeAllWidgets;
        bindBoxLayoutRatios["addSpace"] = &tgui::BoxLayoutRatios::addSpace;
        bindBoxLayoutRatios["insertSpace"] = &tgui::BoxLayoutRatios::insertSpace;
        bindBoxLayoutRatios["setRatio"]
            = sol::overload(static_cast<bool (tgui::BoxLayoutRatios::*)(
                                gui::Widget1a388912f13898735531886bc676b14f81, float)>(
                                &tgui::BoxLayoutRatios::setRatio),
                static_cast<bool (tgui::BoxLayoutRatios::*)(std::size_t, float)>(
                    &tgui::BoxLayoutRatios::setRatio));
        bindBoxLayoutRatios["getRatio"]
            = sol::overload(static_cast<float (tgui::BoxLayoutRatios::*)(
                                gui::Widget1a388912f13898735531886bc676b14f81) const>(
                                &tgui::BoxLayoutRatios::getRatio),
                static_cast<float (tgui::BoxLayoutRatios::*)(std::size_t) const>(
                    &tgui::BoxLayoutRatios::getRatio));
    }
    void LoadClassBoxLayoutRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BoxLayoutRenderer> bindBoxLayoutRenderer
            = tguiNamespace.new_usertype<tgui::BoxLayoutRenderer>("BoxLayoutRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::GroupRenderer, tgui::WidgetRenderer>());
        bindBoxLayoutRenderer["setSpaceBetweenWidgets"]
            = &tgui::BoxLayoutRenderer::setSpaceBetweenWidgets;
        bindBoxLayoutRenderer["getSpaceBetweenWidgets"]
            = &tgui::BoxLayoutRenderer::getSpaceBetweenWidgets;
    }
    void LoadClassButton(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Button> bindButton
            = tguiNamespace.new_usertype<tgui::Button>("Button", sol::call_constructor,
                sol::constructors<tgui::Button(), tgui::Button(const char*),
                    tgui::Button(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::ButtonBase, tgui::ClickableWidget, tgui::Widget>());
        bindButton["leftMousePressed"] = &tgui::Button::leftMousePressed;
        bindButton["leftMouseReleased"] = &tgui::Button::leftMouseReleased;
        bindButton["leftMouseButtonNoLongerDown"]
            = &tgui::Button::leftMouseButtonNoLongerDown;
        bindButton["keyPressed"] = &tgui::Button::keyPressed;
        bindButton["create"] = sol::overload(
            [](tgui::Button* self) -> gui::Button1a50f5464cad267b298d16014d027a1eda {
                return self->create();
            },
            [](tgui::Button* self, const gui::String& text)
                -> gui::Button1a50f5464cad267b298d16014d027a1eda {
                return self->create(text);
            });
        bindButton["copy"] = &tgui::Button::copy;
        bindButton["onPress"] = &tgui::Button::onPress;
    }
    void LoadClassButtonBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ButtonBase> bindButtonBase
            = tguiNamespace.new_usertype<tgui::ButtonBase>("ButtonBase",
                sol::call_constructor,
                sol::constructors<tgui::ButtonBase(const char*, bool),
                    tgui::ButtonBase(const gui::ButtonBase&),
                    tgui::ButtonBase(gui::ButtonBase &&)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindButtonBase["operator="] = sol::overload(
            static_cast<gui::ButtonBase& (tgui::ButtonBase::*)(const gui::ButtonBase&)>(
                &tgui::ButtonBase::operator=),
            static_cast<gui::ButtonBase& (tgui::ButtonBase::*)(gui::ButtonBase &&)>(
                &tgui::ButtonBase::operator=));
        bindButtonBase["getSharedRenderer"]
            = sol::overload(static_cast<gui::ButtonRenderer* (tgui::ButtonBase::*)()>(
                                &tgui::ButtonBase::getSharedRenderer),
                static_cast<const gui::ButtonRenderer* (tgui::ButtonBase::*)() const>(
                    &tgui::ButtonBase::getSharedRenderer));
        bindButtonBase["getRenderer"]
            = sol::overload(static_cast<gui::ButtonRenderer* (tgui::ButtonBase::*)()>(
                                &tgui::ButtonBase::getRenderer),
                static_cast<const gui::ButtonRenderer* (tgui::ButtonBase::*)() const>(
                    &tgui::ButtonBase::getRenderer));
        bindButtonBase["setSize"]
            = sol::overload(static_cast<void (tgui::ButtonBase::*)(const gui::Layout2d&)>(
                                &tgui::ButtonBase::setSize),
                static_cast<void (tgui::ButtonBase::*)(const gui::Layout2d&)>(
                    &tgui::ButtonBase::setSize),
                static_cast<void (tgui::ButtonBase::*)(gui::Layout, gui::Layout)>(
                    &tgui::ButtonBase::setSize));
        bindButtonBase["setEnabled"] = &tgui::ButtonBase::setEnabled;
        bindButtonBase["setText"] = &tgui::ButtonBase::setText;
        bindButtonBase["getText"] = &tgui::ButtonBase::getText;
        bindButtonBase["setTextSize"] = &tgui::ButtonBase::setTextSize;
        bindButtonBase["getTextSize"] = &tgui::ButtonBase::getTextSize;
        bindButtonBase["setFocused"] = &tgui::ButtonBase::setFocused;
        bindButtonBase["isMouseOnWidget"] = &tgui::ButtonBase::isMouseOnWidget;
        bindButtonBase["leftMousePressed"] = &tgui::ButtonBase::leftMousePressed;
        bindButtonBase["leftMouseReleased"] = &tgui::ButtonBase::leftMouseReleased;
        bindButtonBase["leftMouseButtonNoLongerDown"]
            = &tgui::ButtonBase::leftMouseButtonNoLongerDown;
        bindButtonBase["draw"] = &tgui::ButtonBase::draw;
    }
    void LoadClassButtonRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ButtonRenderer> bindButtonRenderer
            = tguiNamespace.new_usertype<tgui::ButtonRenderer>("ButtonRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindButtonRenderer["setBorders"] = &tgui::ButtonRenderer::setBorders;
        bindButtonRenderer["getBorders"] = &tgui::ButtonRenderer::getBorders;
        bindButtonRenderer["setTextColor"] = &tgui::ButtonRenderer::setTextColor;
        bindButtonRenderer["getTextColor"] = &tgui::ButtonRenderer::getTextColor;
        bindButtonRenderer["setTextColorDown"] = &tgui::ButtonRenderer::setTextColorDown;
        bindButtonRenderer["getTextColorDown"] = &tgui::ButtonRenderer::getTextColorDown;
        bindButtonRenderer["setTextColorHover"]
            = &tgui::ButtonRenderer::setTextColorHover;
        bindButtonRenderer["getTextColorHover"]
            = &tgui::ButtonRenderer::getTextColorHover;
        bindButtonRenderer["setTextColorDownHover"]
            = &tgui::ButtonRenderer::setTextColorDownHover;
        bindButtonRenderer["getTextColorDownHover"]
            = &tgui::ButtonRenderer::getTextColorDownHover;
        bindButtonRenderer["setTextColorDisabled"]
            = &tgui::ButtonRenderer::setTextColorDisabled;
        bindButtonRenderer["getTextColorDisabled"]
            = &tgui::ButtonRenderer::getTextColorDisabled;
        bindButtonRenderer["setTextColorDownDisabled"]
            = &tgui::ButtonRenderer::setTextColorDownDisabled;
        bindButtonRenderer["getTextColorDownDisabled"]
            = &tgui::ButtonRenderer::getTextColorDownDisabled;
        bindButtonRenderer["setTextColorFocused"]
            = &tgui::ButtonRenderer::setTextColorFocused;
        bindButtonRenderer["getTextColorFocused"]
            = &tgui::ButtonRenderer::getTextColorFocused;
        bindButtonRenderer["setTextColorDownFocused"]
            = &tgui::ButtonRenderer::setTextColorDownFocused;
        bindButtonRenderer["getTextColorDownFocused"]
            = &tgui::ButtonRenderer::getTextColorDownFocused;
        bindButtonRenderer["setBackgroundColor"]
            = &tgui::ButtonRenderer::setBackgroundColor;
        bindButtonRenderer["getBackgroundColor"]
            = &tgui::ButtonRenderer::getBackgroundColor;
        bindButtonRenderer["setBackgroundColorDown"]
            = &tgui::ButtonRenderer::setBackgroundColorDown;
        bindButtonRenderer["getBackgroundColorDown"]
            = &tgui::ButtonRenderer::getBackgroundColorDown;
        bindButtonRenderer["setBackgroundColorHover"]
            = &tgui::ButtonRenderer::setBackgroundColorHover;
        bindButtonRenderer["getBackgroundColorHover"]
            = &tgui::ButtonRenderer::getBackgroundColorHover;
        bindButtonRenderer["setBackgroundColorDownHover"]
            = &tgui::ButtonRenderer::setBackgroundColorDownHover;
        bindButtonRenderer["getBackgroundColorDownHover"]
            = &tgui::ButtonRenderer::getBackgroundColorDownHover;
        bindButtonRenderer["setBackgroundColorDisabled"]
            = &tgui::ButtonRenderer::setBackgroundColorDisabled;
        bindButtonRenderer["getBackgroundColorDisabled"]
            = &tgui::ButtonRenderer::getBackgroundColorDisabled;
        bindButtonRenderer["setBackgroundColorDownDisabled"]
            = &tgui::ButtonRenderer::setBackgroundColorDownDisabled;
        bindButtonRenderer["getBackgroundColorDownDisabled"]
            = &tgui::ButtonRenderer::getBackgroundColorDownDisabled;
        bindButtonRenderer["setBackgroundColorFocused"]
            = &tgui::ButtonRenderer::setBackgroundColorFocused;
        bindButtonRenderer["getBackgroundColorFocused"]
            = &tgui::ButtonRenderer::getBackgroundColorFocused;
        bindButtonRenderer["setBackgroundColorDownFocused"]
            = &tgui::ButtonRenderer::setBackgroundColorDownFocused;
        bindButtonRenderer["getBackgroundColorDownFocused"]
            = &tgui::ButtonRenderer::getBackgroundColorDownFocused;
        bindButtonRenderer["setBorderColor"] = &tgui::ButtonRenderer::setBorderColor;
        bindButtonRenderer["getBorderColor"] = &tgui::ButtonRenderer::getBorderColor;
        bindButtonRenderer["setBorderColorDown"]
            = &tgui::ButtonRenderer::setBorderColorDown;
        bindButtonRenderer["getBorderColorDown"]
            = &tgui::ButtonRenderer::getBorderColorDown;
        bindButtonRenderer["setBorderColorHover"]
            = &tgui::ButtonRenderer::setBorderColorHover;
        bindButtonRenderer["getBorderColorHover"]
            = &tgui::ButtonRenderer::getBorderColorHover;
        bindButtonRenderer["setBorderColorDownHover"]
            = &tgui::ButtonRenderer::setBorderColorDownHover;
        bindButtonRenderer["getBorderColorDownHover"]
            = &tgui::ButtonRenderer::getBorderColorDownHover;
        bindButtonRenderer["setBorderColorDisabled"]
            = &tgui::ButtonRenderer::setBorderColorDisabled;
        bindButtonRenderer["getBorderColorDisabled"]
            = &tgui::ButtonRenderer::getBorderColorDisabled;
        bindButtonRenderer["setBorderColorDownDisabled"]
            = &tgui::ButtonRenderer::setBorderColorDownDisabled;
        bindButtonRenderer["getBorderColorDownDisabled"]
            = &tgui::ButtonRenderer::getBorderColorDownDisabled;
        bindButtonRenderer["setBorderColorFocused"]
            = &tgui::ButtonRenderer::setBorderColorFocused;
        bindButtonRenderer["getBorderColorFocused"]
            = &tgui::ButtonRenderer::getBorderColorFocused;
        bindButtonRenderer["setBorderColorDownFocused"]
            = &tgui::ButtonRenderer::setBorderColorDownFocused;
        bindButtonRenderer["getBorderColorDownFocused"]
            = &tgui::ButtonRenderer::getBorderColorDownFocused;
        bindButtonRenderer["setTexture"] = &tgui::ButtonRenderer::setTexture;
        bindButtonRenderer["getTexture"] = &tgui::ButtonRenderer::getTexture;
        bindButtonRenderer["setTextureDown"] = &tgui::ButtonRenderer::setTextureDown;
        bindButtonRenderer["getTextureDown"] = &tgui::ButtonRenderer::getTextureDown;
        bindButtonRenderer["setTextureHover"] = &tgui::ButtonRenderer::setTextureHover;
        bindButtonRenderer["getTextureHover"] = &tgui::ButtonRenderer::getTextureHover;
        bindButtonRenderer["setTextureDownHover"]
            = &tgui::ButtonRenderer::setTextureDownHover;
        bindButtonRenderer["getTextureDownHover"]
            = &tgui::ButtonRenderer::getTextureDownHover;
        bindButtonRenderer["setTextureDisabled"]
            = &tgui::ButtonRenderer::setTextureDisabled;
        bindButtonRenderer["getTextureDisabled"]
            = &tgui::ButtonRenderer::getTextureDisabled;
        bindButtonRenderer["setTextureDownDisabled"]
            = &tgui::ButtonRenderer::setTextureDownDisabled;
        bindButtonRenderer["getTextureDownDisabled"]
            = &tgui::ButtonRenderer::getTextureDownDisabled;
        bindButtonRenderer["setTextureFocused"]
            = &tgui::ButtonRenderer::setTextureFocused;
        bindButtonRenderer["getTextureFocused"]
            = &tgui::ButtonRenderer::getTextureFocused;
        bindButtonRenderer["setTextureDownFocused"]
            = &tgui::ButtonRenderer::setTextureDownFocused;
        bindButtonRenderer["getTextureDownFocused"]
            = &tgui::ButtonRenderer::getTextureDownFocused;
        bindButtonRenderer["setTextStyle"] = &tgui::ButtonRenderer::setTextStyle;
        bindButtonRenderer["getTextStyle"] = &tgui::ButtonRenderer::getTextStyle;
        bindButtonRenderer["setTextStyleDown"] = &tgui::ButtonRenderer::setTextStyleDown;
        bindButtonRenderer["getTextStyleDown"] = &tgui::ButtonRenderer::getTextStyleDown;
        bindButtonRenderer["setTextStyleHover"]
            = &tgui::ButtonRenderer::setTextStyleHover;
        bindButtonRenderer["getTextStyleHover"]
            = &tgui::ButtonRenderer::getTextStyleHover;
        bindButtonRenderer["setTextStyleDownHover"]
            = &tgui::ButtonRenderer::setTextStyleDownHover;
        bindButtonRenderer["getTextStyleDownHover"]
            = &tgui::ButtonRenderer::getTextStyleDownHover;
        bindButtonRenderer["setTextStyleDisabled"]
            = &tgui::ButtonRenderer::setTextStyleDisabled;
        bindButtonRenderer["getTextStyleDisabled"]
            = &tgui::ButtonRenderer::getTextStyleDisabled;
        bindButtonRenderer["setTextStyleDownDisabled"]
            = &tgui::ButtonRenderer::setTextStyleDownDisabled;
        bindButtonRenderer["getTextStyleDownDisabled"]
            = &tgui::ButtonRenderer::getTextStyleDownDisabled;
        bindButtonRenderer["setTextStyleFocused"]
            = &tgui::ButtonRenderer::setTextStyleFocused;
        bindButtonRenderer["getTextStyleFocused"]
            = &tgui::ButtonRenderer::getTextStyleFocused;
        bindButtonRenderer["setTextStyleDownFocused"]
            = &tgui::ButtonRenderer::setTextStyleDownFocused;
        bindButtonRenderer["getTextStyleDownFocused"]
            = &tgui::ButtonRenderer::getTextStyleDownFocused;
        bindButtonRenderer["setTextOutlineColor"]
            = &tgui::ButtonRenderer::setTextOutlineColor;
        bindButtonRenderer["getTextOutlineColor"]
            = &tgui::ButtonRenderer::getTextOutlineColor;
        bindButtonRenderer["setTextOutlineThickness"]
            = &tgui::ButtonRenderer::setTextOutlineThickness;
        bindButtonRenderer["getTextOutlineThickness"]
            = &tgui::ButtonRenderer::getTextOutlineThickness;
        bindButtonRenderer["setRoundedBorderRadius"]
            = &tgui::ButtonRenderer::setRoundedBorderRadius;
        bindButtonRenderer["getRoundedBorderRadius"]
            = &tgui::ButtonRenderer::getRoundedBorderRadius;
        bindButtonRenderer["WidgetRenderer"]
            = sol::overload(static_cast<(tgui::ButtonRenderer::*)()>(
                                &tgui::ButtonRenderer::WidgetRenderer),
                static_cast<(
                    tgui::ButtonRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                    &tgui::ButtonRenderer::WidgetRenderer));
    }
    void LoadClassChatBox(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ChatBox> bindChatBox
            = tguiNamespace.new_usertype<tgui::ChatBox>("ChatBox", sol::call_constructor,
                sol::constructors<tgui::ChatBox(), tgui::ChatBox(const char*),
                    tgui::ChatBox(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindChatBox["getSharedRenderer"]
            = sol::overload(static_cast<gui::ChatBoxRenderer* (tgui::ChatBox::*)()>(
                                &tgui::ChatBox::getSharedRenderer),
                static_cast<const gui::ChatBoxRenderer* (tgui::ChatBox::*)() const>(
                    &tgui::ChatBox::getSharedRenderer));
        bindChatBox["getRenderer"]
            = sol::overload(static_cast<gui::ChatBoxRenderer* (tgui::ChatBox::*)()>(
                                &tgui::ChatBox::getRenderer),
                static_cast<const gui::ChatBoxRenderer* (tgui::ChatBox::*)() const>(
                    &tgui::ChatBox::getRenderer));
        bindChatBox["setSize"]
            = sol::overload(static_cast<void (tgui::ChatBox::*)(const gui::Layout2d&)>(
                                &tgui::ChatBox::setSize),
                static_cast<void (tgui::ChatBox::*)(const gui::Layout2d&)>(
                    &tgui::ChatBox::setSize),
                static_cast<void (tgui::ChatBox::*)(gui::Layout, gui::Layout)>(
                    &tgui::ChatBox::setSize));
        bindChatBox["addLine"]
            = sol::overload(static_cast<void (tgui::ChatBox::*)(const gui::String&)>(
                                &tgui::ChatBox::addLine),
                static_cast<void (tgui::ChatBox::*)(const gui::String&, gui::Color)>(
                    &tgui::ChatBox::addLine),
                static_cast<void (tgui::ChatBox::*)(const gui::String&, gui::Color,
                    gui::TextStyles)>(&tgui::ChatBox::addLine));
        bindChatBox["getLine"] = &tgui::ChatBox::getLine;
        bindChatBox["getLineColor"] = &tgui::ChatBox::getLineColor;
        bindChatBox["getLineTextStyle"] = &tgui::ChatBox::getLineTextStyle;
        bindChatBox["removeLine"] = &tgui::ChatBox::removeLine;
        bindChatBox["removeAllLines"] = &tgui::ChatBox::removeAllLines;
        bindChatBox["getLineAmount"] = &tgui::ChatBox::getLineAmount;
        bindChatBox["setLineLimit"] = &tgui::ChatBox::setLineLimit;
        bindChatBox["getLineLimit"] = &tgui::ChatBox::getLineLimit;
        bindChatBox["setTextSize"] = &tgui::ChatBox::setTextSize;
        bindChatBox["setTextColor"] = &tgui::ChatBox::setTextColor;
        bindChatBox["getTextColor"] = &tgui::ChatBox::getTextColor;
        bindChatBox["setTextStyle"] = &tgui::ChatBox::setTextStyle;
        bindChatBox["getTextStyle"] = &tgui::ChatBox::getTextStyle;
        bindChatBox["setLinesStartFromTop"] = sol::overload(
            [](tgui::ChatBox* self) -> void { return self->setLinesStartFromTop(); },
            [](tgui::ChatBox* self, bool startFromTop) -> void {
                return self->setLinesStartFromTop(startFromTop);
            });
        bindChatBox["getLinesStartFromTop"] = &tgui::ChatBox::getLinesStartFromTop;
        bindChatBox["setNewLinesBelowOthers"] = sol::overload(
            [](tgui::ChatBox* self) -> void { return self->setNewLinesBelowOthers(); },
            [](tgui::ChatBox* self, bool newLinesBelowOthers) -> void {
                return self->setNewLinesBelowOthers(newLinesBelowOthers);
            });
        bindChatBox["getNewLinesBelowOthers"] = &tgui::ChatBox::getNewLinesBelowOthers;
        bindChatBox["setScrollbarValue"] = &tgui::ChatBox::setScrollbarValue;
        bindChatBox["getScrollbarValue"] = &tgui::ChatBox::getScrollbarValue;
        bindChatBox["isMouseOnWidget"] = &tgui::ChatBox::isMouseOnWidget;
        bindChatBox["leftMousePressed"] = &tgui::ChatBox::leftMousePressed;
        bindChatBox["leftMouseReleased"] = &tgui::ChatBox::leftMouseReleased;
        bindChatBox["mouseMoved"] = &tgui::ChatBox::mouseMoved;
        bindChatBox["mouseWheelScrolled"] = &tgui::ChatBox::mouseWheelScrolled;
        bindChatBox["mouseNoLongerOnWidget"] = &tgui::ChatBox::mouseNoLongerOnWidget;
        bindChatBox["leftMouseButtonNoLongerDown"]
            = &tgui::ChatBox::leftMouseButtonNoLongerDown;
        bindChatBox["create"] = &tgui::ChatBox::create;
        bindChatBox["copy"] = &tgui::ChatBox::copy;
    }
    void LoadClassChatBoxRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ChatBoxRenderer> bindChatBoxRenderer
            = tguiNamespace.new_usertype<tgui::ChatBoxRenderer>("ChatBoxRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindChatBoxRenderer["setBorders"] = &tgui::ChatBoxRenderer::setBorders;
        bindChatBoxRenderer["getBorders"] = &tgui::ChatBoxRenderer::getBorders;
        bindChatBoxRenderer["setPadding"] = &tgui::ChatBoxRenderer::setPadding;
        bindChatBoxRenderer["getPadding"] = &tgui::ChatBoxRenderer::getPadding;
        bindChatBoxRenderer["setBackgroundColor"]
            = &tgui::ChatBoxRenderer::setBackgroundColor;
        bindChatBoxRenderer["getBackgroundColor"]
            = &tgui::ChatBoxRenderer::getBackgroundColor;
        bindChatBoxRenderer["setBorderColor"] = &tgui::ChatBoxRenderer::setBorderColor;
        bindChatBoxRenderer["getBorderColor"] = &tgui::ChatBoxRenderer::getBorderColor;
        bindChatBoxRenderer["setTextureBackground"]
            = &tgui::ChatBoxRenderer::setTextureBackground;
        bindChatBoxRenderer["getTextureBackground"]
            = &tgui::ChatBoxRenderer::getTextureBackground;
        bindChatBoxRenderer["setScrollbar"] = &tgui::ChatBoxRenderer::setScrollbar;
        bindChatBoxRenderer["getScrollbar"] = &tgui::ChatBoxRenderer::getScrollbar;
        bindChatBoxRenderer["setScrollbarWidth"]
            = &tgui::ChatBoxRenderer::setScrollbarWidth;
        bindChatBoxRenderer["getScrollbarWidth"]
            = &tgui::ChatBoxRenderer::getScrollbarWidth;
        bindChatBoxRenderer["WidgetRenderer"]
            = sol::overload(static_cast<(tgui::ChatBoxRenderer::*)()>(
                                &tgui::ChatBoxRenderer::WidgetRenderer),
                static_cast<(
                    tgui::ChatBoxRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                    &tgui::ChatBoxRenderer::WidgetRenderer));
    }
    void LoadClassCheckBox(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::CheckBox> bindCheckBox
            = tguiNamespace.new_usertype<tgui::CheckBox>("CheckBox",
                sol::call_constructor,
                sol::constructors<tgui::CheckBox(), tgui::CheckBox(const char*),
                    tgui::CheckBox(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::RadioButton, tgui::ClickableWidget, tgui::Widget>());
        bindCheckBox["getSharedRenderer"]
            = sol::overload(static_cast<gui::CheckBoxRenderer* (tgui::CheckBox::*)()>(
                                &tgui::CheckBox::getSharedRenderer),
                static_cast<const gui::CheckBoxRenderer* (tgui::CheckBox::*)() const>(
                    &tgui::CheckBox::getSharedRenderer));
        bindCheckBox["getRenderer"]
            = sol::overload(static_cast<gui::CheckBoxRenderer* (tgui::CheckBox::*)()>(
                                &tgui::CheckBox::getRenderer),
                static_cast<const gui::CheckBoxRenderer* (tgui::CheckBox::*)() const>(
                    &tgui::CheckBox::getRenderer));
        bindCheckBox["getFullSize"] = &tgui::CheckBox::getFullSize;
        bindCheckBox["getWidgetOffset"] = &tgui::CheckBox::getWidgetOffset;
        bindCheckBox["setChecked"] = &tgui::CheckBox::setChecked;
        bindCheckBox["leftMouseReleased"] = &tgui::CheckBox::leftMouseReleased;
        bindCheckBox["keyPressed"] = &tgui::CheckBox::keyPressed;
        bindCheckBox["draw"] = &tgui::CheckBox::draw;
        bindCheckBox["create"] = sol::overload(
            [](tgui::CheckBox* self) -> gui::CheckBox1a27eceefb72290e57ce936c788b183814 {
                return self->create();
            },
            [](tgui::CheckBox* self,
                gui::String text) -> gui::CheckBox1a27eceefb72290e57ce936c788b183814 {
                return self->create(text);
            });
        bindCheckBox["copy"] = &tgui::CheckBox::copy;
    }
    void LoadClassCheckBoxRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::CheckBoxRenderer> bindCheckBoxRenderer
            = tguiNamespace.new_usertype<tgui::CheckBoxRenderer>("CheckBoxRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::RadioButtonRenderer, tgui::WidgetRenderer>());
    }
    void LoadClassChildWindow(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ChildWindow> bindChildWindow
            = tguiNamespace.new_usertype<tgui::ChildWindow>("ChildWindow",
                sol::call_constructor,
                sol::constructors<tgui::ChildWindow(), tgui::ChildWindow(const char*),
                    tgui::ChildWindow(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Container, tgui::Widget>());
        bindChildWindow["getSharedRenderer"] = sol::overload(
            static_cast<gui::ChildWindowRenderer* (tgui::ChildWindow::*)()>(
                &tgui::ChildWindow::getSharedRenderer),
            static_cast<const gui::ChildWindowRenderer* (tgui::ChildWindow::*)() const>(
                &tgui::ChildWindow::getSharedRenderer));
        bindChildWindow["getRenderer"] = sol::overload(
            static_cast<gui::ChildWindowRenderer* (tgui::ChildWindow::*)()>(
                &tgui::ChildWindow::getRenderer),
            static_cast<const gui::ChildWindowRenderer* (tgui::ChildWindow::*)() const>(
                &tgui::ChildWindow::getRenderer));
        bindChildWindow["setPosition"] = sol::overload(
            static_cast<void (tgui::ChildWindow::*)(const gui::Layout2d&)>(
                &tgui::ChildWindow::setPosition),
            static_cast<void (tgui::ChildWindow::*)(const gui::Layout2d&)>(
                &tgui::ChildWindow::setPosition),
            static_cast<void (tgui::ChildWindow::*)(gui::Layout, gui::Layout)>(
                &tgui::ChildWindow::setPosition));
        bindChildWindow["setSize"] = sol::overload(
            static_cast<void (tgui::ChildWindow::*)(const gui::Layout2d&)>(
                &tgui::ChildWindow::setSize),
            static_cast<void (tgui::ChildWindow::*)(const gui::Layout2d&)>(
                &tgui::ChildWindow::setSize),
            static_cast<void (tgui::ChildWindow::*)(gui::Layout, gui::Layout)>(
                &tgui::ChildWindow::setSize));
        bindChildWindow["getInnerSize"] = &tgui::ChildWindow::getInnerSize;
        bindChildWindow["setClientSize"] = &tgui::ChildWindow::setClientSize;
        bindChildWindow["getClientSize"] = &tgui::ChildWindow::getClientSize;
        bindChildWindow["setMaximumSize"] = &tgui::ChildWindow::setMaximumSize;
        bindChildWindow["getMaximumSize"] = &tgui::ChildWindow::getMaximumSize;
        bindChildWindow["setMinimumSize"] = &tgui::ChildWindow::setMinimumSize;
        bindChildWindow["getMinimumSize"] = &tgui::ChildWindow::getMinimumSize;
        bindChildWindow["setTitle"] = &tgui::ChildWindow::setTitle;
        bindChildWindow["getTitle"] = &tgui::ChildWindow::getTitle;
        bindChildWindow["setTitleTextSize"] = &tgui::ChildWindow::setTitleTextSize;
        bindChildWindow["getTitleTextSize"] = &tgui::ChildWindow::getTitleTextSize;
        bindChildWindow["setTitleAlignment"] = &tgui::ChildWindow::setTitleAlignment;
        bindChildWindow["getTitleAlignment"] = &tgui::ChildWindow::getTitleAlignment;
        bindChildWindow["setTitleButtons"] = &tgui::ChildWindow::setTitleButtons;
        bindChildWindow["getTitleButtons"] = &tgui::ChildWindow::getTitleButtons;
        bindChildWindow["close"] = &tgui::ChildWindow::close;
        bindChildWindow["destroy"] = &tgui::ChildWindow::destroy;
        bindChildWindow["setResizable"] = sol::overload(
            [](tgui::ChildWindow* self) -> void { return self->setResizable(); },
            [](tgui::ChildWindow* self, bool resizable) -> void {
                return self->setResizable(resizable);
            });
        bindChildWindow["isResizable"] = &tgui::ChildWindow::isResizable;
        bindChildWindow["setPositionLocked"] = sol::overload(
            [](tgui::ChildWindow* self) -> void { return self->setPositionLocked(); },
            [](tgui::ChildWindow* self, bool positionLocked) -> void {
                return self->setPositionLocked(positionLocked);
            });
        bindChildWindow["isPositionLocked"] = &tgui::ChildWindow::isPositionLocked;
        bindChildWindow["setKeepInParent"] = sol::overload(
            [](tgui::ChildWindow* self) -> void { return self->setKeepInParent(); },
            [](tgui::ChildWindow* self, bool enabled) -> void {
                return self->setKeepInParent(enabled);
            });
        bindChildWindow["isKeptInParent"] = &tgui::ChildWindow::isKeptInParent;
        bindChildWindow["getChildWidgetsOffset"]
            = &tgui::ChildWindow::getChildWidgetsOffset;
        bindChildWindow["setParent"] = &tgui::ChildWindow::setParent;
        bindChildWindow["isMouseOnWidget"] = &tgui::ChildWindow::isMouseOnWidget;
        bindChildWindow["leftMousePressed"] = &tgui::ChildWindow::leftMousePressed;
        bindChildWindow["leftMouseReleased"] = &tgui::ChildWindow::leftMouseReleased;
        bindChildWindow["rightMousePressed"] = &tgui::ChildWindow::rightMousePressed;
        bindChildWindow["rightMouseReleased"] = &tgui::ChildWindow::rightMouseReleased;
        bindChildWindow["mouseMoved"] = &tgui::ChildWindow::mouseMoved;
        bindChildWindow["keyPressed"] = &tgui::ChildWindow::keyPressed;
        bindChildWindow["mouseNoLongerOnWidget"]
            = &tgui::ChildWindow::mouseNoLongerOnWidget;
        bindChildWindow["leftMouseButtonNoLongerDown"]
            = &tgui::ChildWindow::leftMouseButtonNoLongerDown;
        bindChildWindow["draw"] = &tgui::ChildWindow::draw;
        bindChildWindow["create"] = sol::overload(
            [](tgui::ChildWindow* self)
                -> gui::ChildWindow1a5135c949483bf6a1a4320bd7ea93f522 {
                return self->create();
            },
            [](tgui::ChildWindow* self, const gui::String& title)
                -> gui::ChildWindow1a5135c949483bf6a1a4320bd7ea93f522 {
                return self->create(title);
            },
            [](tgui::ChildWindow* self, const gui::String& title,
                unsigned int titleButtons)
                -> gui::ChildWindow1a5135c949483bf6a1a4320bd7ea93f522 {
                return self->create(title, titleButtons);
            });
        bindChildWindow["copy"] = &tgui::ChildWindow::copy;
        bindChildWindow["onMousePress"] = &tgui::ChildWindow::onMousePress;
        bindChildWindow["onClose"] = &tgui::ChildWindow::onClose;
        bindChildWindow["onMinimize"] = &tgui::ChildWindow::onMinimize;
        bindChildWindow["onMaximize"] = &tgui::ChildWindow::onMaximize;
        bindChildWindow["onEscapeKeyPress"] = &tgui::ChildWindow::onEscapeKeyPress;
        bindChildWindow["onClosing"] = &tgui::ChildWindow::onClosing;
    }
    void LoadClassChildWindowRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ChildWindowRenderer> bindChildWindowRenderer
            = tguiNamespace.new_usertype<tgui::ChildWindowRenderer>("ChildWindowRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindChildWindowRenderer["setBorders"] = &tgui::ChildWindowRenderer::setBorders;
        bindChildWindowRenderer["getBorders"] = &tgui::ChildWindowRenderer::getBorders;
        bindChildWindowRenderer["setTitleBarHeight"]
            = &tgui::ChildWindowRenderer::setTitleBarHeight;
        bindChildWindowRenderer["getTitleBarHeight"]
            = &tgui::ChildWindowRenderer::getTitleBarHeight;
        bindChildWindowRenderer["setTitleBarColor"]
            = &tgui::ChildWindowRenderer::setTitleBarColor;
        bindChildWindowRenderer["getTitleBarColor"]
            = &tgui::ChildWindowRenderer::getTitleBarColor;
        bindChildWindowRenderer["setTitleColor"]
            = &tgui::ChildWindowRenderer::setTitleColor;
        bindChildWindowRenderer["getTitleColor"]
            = &tgui::ChildWindowRenderer::getTitleColor;
        bindChildWindowRenderer["setBackgroundColor"]
            = &tgui::ChildWindowRenderer::setBackgroundColor;
        bindChildWindowRenderer["getBackgroundColor"]
            = &tgui::ChildWindowRenderer::getBackgroundColor;
        bindChildWindowRenderer["setBorderColor"]
            = &tgui::ChildWindowRenderer::setBorderColor;
        bindChildWindowRenderer["getBorderColor"]
            = &tgui::ChildWindowRenderer::getBorderColor;
        bindChildWindowRenderer["setBorderColorFocused"]
            = &tgui::ChildWindowRenderer::setBorderColorFocused;
        bindChildWindowRenderer["getBorderColorFocused"]
            = &tgui::ChildWindowRenderer::getBorderColorFocused;
        bindChildWindowRenderer["setBorderBelowTitleBar"]
            = &tgui::ChildWindowRenderer::setBorderBelowTitleBar;
        bindChildWindowRenderer["getBorderBelowTitleBar"]
            = &tgui::ChildWindowRenderer::getBorderBelowTitleBar;
        bindChildWindowRenderer["setDistanceToSide"]
            = &tgui::ChildWindowRenderer::setDistanceToSide;
        bindChildWindowRenderer["getDistanceToSide"]
            = &tgui::ChildWindowRenderer::getDistanceToSide;
        bindChildWindowRenderer["setPaddingBetweenButtons"]
            = &tgui::ChildWindowRenderer::setPaddingBetweenButtons;
        bindChildWindowRenderer["getPaddingBetweenButtons"]
            = &tgui::ChildWindowRenderer::getPaddingBetweenButtons;
        bindChildWindowRenderer["setMinimumResizableBorderWidth"]
            = &tgui::ChildWindowRenderer::setMinimumResizableBorderWidth;
        bindChildWindowRenderer["getMinimumResizableBorderWidth"]
            = &tgui::ChildWindowRenderer::getMinimumResizableBorderWidth;
        bindChildWindowRenderer["setShowTextOnTitleButtons"]
            = &tgui::ChildWindowRenderer::setShowTextOnTitleButtons;
        bindChildWindowRenderer["getShowTextOnTitleButtons"]
            = &tgui::ChildWindowRenderer::getShowTextOnTitleButtons;
        bindChildWindowRenderer["setTextureTitleBar"]
            = &tgui::ChildWindowRenderer::setTextureTitleBar;
        bindChildWindowRenderer["getTextureTitleBar"]
            = &tgui::ChildWindowRenderer::getTextureTitleBar;
        bindChildWindowRenderer["setTextureBackground"]
            = &tgui::ChildWindowRenderer::setTextureBackground;
        bindChildWindowRenderer["getTextureBackground"]
            = &tgui::ChildWindowRenderer::getTextureBackground;
        bindChildWindowRenderer["setCloseButton"]
            = &tgui::ChildWindowRenderer::setCloseButton;
        bindChildWindowRenderer["getCloseButton"]
            = &tgui::ChildWindowRenderer::getCloseButton;
        bindChildWindowRenderer["setMaximizeButton"]
            = &tgui::ChildWindowRenderer::setMaximizeButton;
        bindChildWindowRenderer["getMaximizeButton"]
            = &tgui::ChildWindowRenderer::getMaximizeButton;
        bindChildWindowRenderer["setMinimizeButton"]
            = &tgui::ChildWindowRenderer::setMinimizeButton;
        bindChildWindowRenderer["getMinimizeButton"]
            = &tgui::ChildWindowRenderer::getMinimizeButton;
        bindChildWindowRenderer["WidgetRenderer"] = sol::overload(
            static_cast<(tgui::ChildWindowRenderer::*)()>(
                &tgui::ChildWindowRenderer::WidgetRenderer),
            static_cast<(
                tgui::ChildWindowRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                &tgui::ChildWindowRenderer::WidgetRenderer));
    }
    void LoadClassClickableWidget(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ClickableWidget> bindClickableWidget
            = tguiNamespace.new_usertype<tgui::ClickableWidget>("ClickableWidget",
                sol::call_constructor,
                sol::constructors<tgui::ClickableWidget(),
                    tgui::ClickableWidget(const char*),
                    tgui::ClickableWidget(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindClickableWidget["isMouseOnWidget"] = &tgui::ClickableWidget::isMouseOnWidget;
        bindClickableWidget["leftMousePressed"]
            = &tgui::ClickableWidget::leftMousePressed;
        bindClickableWidget["leftMouseReleased"]
            = &tgui::ClickableWidget::leftMouseReleased;
        bindClickableWidget["rightMousePressed"]
            = &tgui::ClickableWidget::rightMousePressed;
        bindClickableWidget["rightMouseReleased"]
            = &tgui::ClickableWidget::rightMouseReleased;
        bindClickableWidget["rightMouseButtonNoLongerDown"]
            = &tgui::ClickableWidget::rightMouseButtonNoLongerDown;
        bindClickableWidget["draw"] = &tgui::ClickableWidget::draw;
        bindClickableWidget["create"] = sol::overload(
            [](tgui::ClickableWidget* self)
                -> gui::ClickableWidget1a6ac85e9df673fe1f4c012ad21199b6b0 {
                return self->create();
            },
            [](tgui::ClickableWidget* self, gui::Layout2d size)
                -> gui::ClickableWidget1a6ac85e9df673fe1f4c012ad21199b6b0 {
                return self->create(size);
            });
        bindClickableWidget["copy"] = &tgui::ClickableWidget::copy;
        bindClickableWidget["onMousePress"] = &tgui::ClickableWidget::onMousePress;
        bindClickableWidget["onMouseRelease"] = &tgui::ClickableWidget::onMouseRelease;
        bindClickableWidget["onClick"] = &tgui::ClickableWidget::onClick;
        bindClickableWidget["onRightMousePress"]
            = &tgui::ClickableWidget::onRightMousePress;
        bindClickableWidget["onRightMouseRelease"]
            = &tgui::ClickableWidget::onRightMouseRelease;
        bindClickableWidget["onRightClick"] = &tgui::ClickableWidget::onRightClick;
    }
    void LoadClassColor(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Color> bindColor
            = tguiNamespace.new_usertype<tgui::Color>("Color", sol::call_constructor,
                sol::constructors<tgui::Color(),
                    tgui::Color(std::uint8_t, std::uint8_t, std::uint8_t),
                    tgui::Color(std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t),
                    tgui::Color(const gui::String&), tgui::Color(const char*)>());
        bindColor["isSet"] = &tgui::Color::isSet;
        bindColor["operator Vertex::Color"] = &tgui::Color::operator Vertex::Color;
        bindColor["getRed"] = &tgui::Color::getRed;
        bindColor["getGreen"] = &tgui::Color::getGreen;
        bindColor["getBlue"] = &tgui::Color::getBlue;
        bindColor["getAlpha"] = &tgui::Color::getAlpha;
        bindColor[sol::meta_function::equal_to] = &tgui::Color::operator==;
        bindColor["applyOpacity"] = &tgui::Color::applyOpacity;
        bindColor["Black"] = sol::var(&tgui::Color::Black);
        bindColor["White"] = sol::var(&tgui::Color::White);
        bindColor["Red"] = sol::var(&tgui::Color::Red);
        bindColor["Green"] = sol::var(&tgui::Color::Green);
        bindColor["Blue"] = sol::var(&tgui::Color::Blue);
        bindColor["Yellow"] = sol::var(&tgui::Color::Yellow);
        bindColor["Magenta"] = sol::var(&tgui::Color::Magenta);
        bindColor["Cyan"] = sol::var(&tgui::Color::Cyan);
        bindColor["Transparent"] = sol::var(&tgui::Color::Transparent);
        bindColor["colorMap"] = sol::var(&tgui::Color::colorMap);
    }
    void LoadClassColorPicker(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ColorPicker> bindColorPicker
            = tguiNamespace.new_usertype<tgui::ColorPicker>("ColorPicker",
                sol::call_constructor,
                sol::constructors<tgui::ColorPicker(), tgui::ColorPicker(const char*),
                    tgui::ColorPicker(const char*, bool),
                    tgui::ColorPicker(const gui::ColorPicker&),
                    tgui::ColorPicker(gui::ColorPicker &&)>(),
                sol::base_classes,
                sol::bases<tgui::ChildWindow, tgui::Container, tgui::Widget>());
        bindColorPicker["operator="] = sol::overload(
            static_cast<gui::ColorPicker& (
                tgui::ColorPicker::*)(const gui::ColorPicker&)>(
                &tgui::ColorPicker::operator=),
            static_cast<gui::ColorPicker& (tgui::ColorPicker::*)(gui::ColorPicker &&)>(
                &tgui::ColorPicker::operator=));
        bindColorPicker["getSharedRenderer"] = sol::overload(
            static_cast<gui::ColorPickerRenderer* (tgui::ColorPicker::*)()>(
                &tgui::ColorPicker::getSharedRenderer),
            static_cast<const gui::ColorPickerRenderer* (tgui::ColorPicker::*)() const>(
                &tgui::ColorPicker::getSharedRenderer));
        bindColorPicker["getRenderer"] = sol::overload(
            static_cast<gui::ColorPickerRenderer* (tgui::ColorPicker::*)()>(
                &tgui::ColorPicker::getRenderer),
            static_cast<const gui::ColorPickerRenderer* (tgui::ColorPicker::*)() const>(
                &tgui::ColorPicker::getRenderer));
        bindColorPicker["setColor"] = &tgui::ColorPicker::setColor;
        bindColorPicker["getColor"] = &tgui::ColorPicker::getColor;
        bindColorPicker["leftMousePressed"] = &tgui::ColorPicker::leftMousePressed;
        bindColorPicker["leftMouseButtonNoLongerDown"]
            = &tgui::ColorPicker::leftMouseButtonNoLongerDown;
        bindColorPicker["mouseMoved"] = &tgui::ColorPicker::mouseMoved;
        bindColorPicker["draw"] = &tgui::ColorPicker::draw;
        bindColorPicker["create"] = sol::overload(
            [](tgui::ColorPicker* self)
                -> gui::ColorPicker1a34a4e7c4f30583f9bb84fcca1e2b7a42 {
                return self->create();
            },
            [](tgui::ColorPicker* self,
                gui::String title) -> gui::ColorPicker1a34a4e7c4f30583f9bb84fcca1e2b7a42 {
                return self->create(title);
            },
            [](tgui::ColorPicker* self, gui::String title,
                gui::Color color) -> gui::ColorPicker1a34a4e7c4f30583f9bb84fcca1e2b7a42 {
                return self->create(title, color);
            });
        bindColorPicker["copy"] = &tgui::ColorPicker::copy;
        bindColorPicker["onColorChange"] = &tgui::ColorPicker::onColorChange;
        bindColorPicker["onOkPress"] = &tgui::ColorPicker::onOkPress;
    }
    void LoadClassColorPickerRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ColorPickerRenderer> bindColorPickerRenderer
            = tguiNamespace.new_usertype<tgui::ColorPickerRenderer>("ColorPickerRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::ChildWindowRenderer, tgui::WidgetRenderer>());
        bindColorPickerRenderer["setButton"] = &tgui::ColorPickerRenderer::setButton;
        bindColorPickerRenderer["getButton"] = &tgui::ColorPickerRenderer::getButton;
        bindColorPickerRenderer["setLabel"] = &tgui::ColorPickerRenderer::setLabel;
        bindColorPickerRenderer["getLabel"] = &tgui::ColorPickerRenderer::getLabel;
        bindColorPickerRenderer["setSlider"] = &tgui::ColorPickerRenderer::setSlider;
        bindColorPickerRenderer["getSlider"] = &tgui::ColorPickerRenderer::getSlider;
    }
    void LoadClassComboBox(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ComboBox> bindComboBox
            = tguiNamespace.new_usertype<tgui::ComboBox>("ComboBox",
                sol::call_constructor,
                sol::constructors<tgui::ComboBox(), tgui::ComboBox(const char*),
                    tgui::ComboBox(const char*, bool),
                    tgui::ComboBox(const gui::ComboBox&),
                    tgui::ComboBox(gui::ComboBox &&)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindComboBox["operator="] = sol::overload(
            static_cast<gui::ComboBox& (tgui::ComboBox::*)(const gui::ComboBox&)>(
                &tgui::ComboBox::operator=),
            static_cast<gui::ComboBox& (tgui::ComboBox::*)(gui::ComboBox &&)>(
                &tgui::ComboBox::operator=));
        bindComboBox["getSharedRenderer"]
            = sol::overload(static_cast<gui::ComboBoxRenderer* (tgui::ComboBox::*)()>(
                                &tgui::ComboBox::getSharedRenderer),
                static_cast<const gui::ComboBoxRenderer* (tgui::ComboBox::*)() const>(
                    &tgui::ComboBox::getSharedRenderer));
        bindComboBox["getRenderer"]
            = sol::overload(static_cast<gui::ComboBoxRenderer* (tgui::ComboBox::*)()>(
                                &tgui::ComboBox::getRenderer),
                static_cast<const gui::ComboBoxRenderer* (tgui::ComboBox::*)() const>(
                    &tgui::ComboBox::getRenderer));
        bindComboBox["setSize"]
            = sol::overload(static_cast<void (tgui::ComboBox::*)(const gui::Layout2d&)>(
                                &tgui::ComboBox::setSize),
                static_cast<void (tgui::ComboBox::*)(const gui::Layout2d&)>(
                    &tgui::ComboBox::setSize),
                static_cast<void (tgui::ComboBox::*)(gui::Layout, gui::Layout)>(
                    &tgui::ComboBox::setSize));
        bindComboBox["setEnabled"] = &tgui::ComboBox::setEnabled;
        bindComboBox["setItemsToDisplay"] = &tgui::ComboBox::setItemsToDisplay;
        bindComboBox["getItemsToDisplay"] = &tgui::ComboBox::getItemsToDisplay;
        bindComboBox["addItem"] = sol::overload(
            [](tgui::ComboBox* self, const gui::String& itemName) -> std::size_t {
                return self->addItem(itemName);
            },
            [](tgui::ComboBox* self, const gui::String& itemName, const gui::String& id)
                -> std::size_t { return self->addItem(itemName, id); });
        bindComboBox["setSelectedItem"] = &tgui::ComboBox::setSelectedItem;
        bindComboBox["setSelectedItemById"] = &tgui::ComboBox::setSelectedItemById;
        bindComboBox["setSelectedItemByIndex"] = &tgui::ComboBox::setSelectedItemByIndex;
        bindComboBox["deselectItem"] = &tgui::ComboBox::deselectItem;
        bindComboBox["removeItem"] = &tgui::ComboBox::removeItem;
        bindComboBox["removeItemById"] = &tgui::ComboBox::removeItemById;
        bindComboBox["removeItemByIndex"] = &tgui::ComboBox::removeItemByIndex;
        bindComboBox["removeAllItems"] = &tgui::ComboBox::removeAllItems;
        bindComboBox["getItemById"] = &tgui::ComboBox::getItemById;
        bindComboBox["getSelectedItem"] = &tgui::ComboBox::getSelectedItem;
        bindComboBox["getSelectedItemId"] = &tgui::ComboBox::getSelectedItemId;
        bindComboBox["getSelectedItemIndex"] = &tgui::ComboBox::getSelectedItemIndex;
        bindComboBox["changeItem"] = &tgui::ComboBox::changeItem;
        bindComboBox["changeItemById"] = &tgui::ComboBox::changeItemById;
        bindComboBox["changeItemByIndex"] = &tgui::ComboBox::changeItemByIndex;
        bindComboBox["getItemCount"] = &tgui::ComboBox::getItemCount;
        bindComboBox["getItems"] = &tgui::ComboBox::getItems;
        bindComboBox["getItemIds"] = &tgui::ComboBox::getItemIds;
        bindComboBox["setMaximumItems"] = sol::overload(
            [](tgui::ComboBox* self) -> void { return self->setMaximumItems(); },
            [](tgui::ComboBox* self, std::size_t maximumItems) -> void {
                return self->setMaximumItems(maximumItems);
            });
        bindComboBox["getMaximumItems"] = &tgui::ComboBox::getMaximumItems;
        bindComboBox["setTextSize"] = &tgui::ComboBox::setTextSize;
        bindComboBox["getTextSize"] = &tgui::ComboBox::getTextSize;
        bindComboBox["setDefaultText"] = &tgui::ComboBox::setDefaultText;
        bindComboBox["getDefaultText"] = &tgui::ComboBox::getDefaultText;
        bindComboBox["setExpandDirection"] = &tgui::ComboBox::setExpandDirection;
        bindComboBox["getExpandDirection"] = &tgui::ComboBox::getExpandDirection;
        bindComboBox["contains"] = &tgui::ComboBox::contains;
        bindComboBox["containsId"] = &tgui::ComboBox::containsId;
        bindComboBox["setChangeItemOnScroll"] = &tgui::ComboBox::setChangeItemOnScroll;
        bindComboBox["getChangeItemOnScroll"] = &tgui::ComboBox::getChangeItemOnScroll;
        bindComboBox["setParent"] = &tgui::ComboBox::setParent;
        bindComboBox["isMouseOnWidget"] = &tgui::ComboBox::isMouseOnWidget;
        bindComboBox["leftMousePressed"] = &tgui::ComboBox::leftMousePressed;
        bindComboBox["mouseWheelScrolled"] = &tgui::ComboBox::mouseWheelScrolled;
        bindComboBox["draw"] = &tgui::ComboBox::draw;
        bindComboBox["create"] = &tgui::ComboBox::create;
        bindComboBox["copy"] = &tgui::ComboBox::copy;
        bindComboBox["onItemSelect"] = &tgui::ComboBox::onItemSelect;
    }
    void LoadClassComboBoxRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ComboBoxRenderer> bindComboBoxRenderer
            = tguiNamespace.new_usertype<tgui::ComboBoxRenderer>("ComboBoxRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindComboBoxRenderer["setBorders"] = &tgui::ComboBoxRenderer::setBorders;
        bindComboBoxRenderer["getBorders"] = &tgui::ComboBoxRenderer::getBorders;
        bindComboBoxRenderer["setPadding"] = &tgui::ComboBoxRenderer::setPadding;
        bindComboBoxRenderer["getPadding"] = &tgui::ComboBoxRenderer::getPadding;
        bindComboBoxRenderer["setTextStyle"] = &tgui::ComboBoxRenderer::setTextStyle;
        bindComboBoxRenderer["getTextStyle"] = &tgui::ComboBoxRenderer::getTextStyle;
        bindComboBoxRenderer["setDefaultTextStyle"]
            = &tgui::ComboBoxRenderer::setDefaultTextStyle;
        bindComboBoxRenderer["getDefaultTextStyle"]
            = &tgui::ComboBoxRenderer::getDefaultTextStyle;
        bindComboBoxRenderer["setBackgroundColor"]
            = &tgui::ComboBoxRenderer::setBackgroundColor;
        bindComboBoxRenderer["getBackgroundColor"]
            = &tgui::ComboBoxRenderer::getBackgroundColor;
        bindComboBoxRenderer["setBackgroundColorDisabled"]
            = &tgui::ComboBoxRenderer::setBackgroundColorDisabled;
        bindComboBoxRenderer["getBackgroundColorDisabled"]
            = &tgui::ComboBoxRenderer::getBackgroundColorDisabled;
        bindComboBoxRenderer["setTextColor"] = &tgui::ComboBoxRenderer::setTextColor;
        bindComboBoxRenderer["getTextColor"] = &tgui::ComboBoxRenderer::getTextColor;
        bindComboBoxRenderer["setTextColorDisabled"]
            = &tgui::ComboBoxRenderer::setTextColorDisabled;
        bindComboBoxRenderer["getTextColorDisabled"]
            = &tgui::ComboBoxRenderer::getTextColorDisabled;
        bindComboBoxRenderer["setDefaultTextColor"]
            = &tgui::ComboBoxRenderer::setDefaultTextColor;
        bindComboBoxRenderer["getDefaultTextColor"]
            = &tgui::ComboBoxRenderer::getDefaultTextColor;
        bindComboBoxRenderer["setArrowBackgroundColor"]
            = &tgui::ComboBoxRenderer::setArrowBackgroundColor;
        bindComboBoxRenderer["getArrowBackgroundColor"]
            = &tgui::ComboBoxRenderer::getArrowBackgroundColor;
        bindComboBoxRenderer["setArrowBackgroundColorHover"]
            = &tgui::ComboBoxRenderer::setArrowBackgroundColorHover;
        bindComboBoxRenderer["getArrowBackgroundColorHover"]
            = &tgui::ComboBoxRenderer::getArrowBackgroundColorHover;
        bindComboBoxRenderer["setArrowBackgroundColorDisabled"]
            = &tgui::ComboBoxRenderer::setArrowBackgroundColorDisabled;
        bindComboBoxRenderer["getArrowBackgroundColorDisabled"]
            = &tgui::ComboBoxRenderer::getArrowBackgroundColorDisabled;
        bindComboBoxRenderer["setArrowColor"] = &tgui::ComboBoxRenderer::setArrowColor;
        bindComboBoxRenderer["getArrowColor"] = &tgui::ComboBoxRenderer::getArrowColor;
        bindComboBoxRenderer["setArrowColorHover"]
            = &tgui::ComboBoxRenderer::setArrowColorHover;
        bindComboBoxRenderer["getArrowColorHover"]
            = &tgui::ComboBoxRenderer::getArrowColorHover;
        bindComboBoxRenderer["setArrowColorDisabled"]
            = &tgui::ComboBoxRenderer::setArrowColorDisabled;
        bindComboBoxRenderer["getArrowColorDisabled"]
            = &tgui::ComboBoxRenderer::getArrowColorDisabled;
        bindComboBoxRenderer["setBorderColor"] = &tgui::ComboBoxRenderer::setBorderColor;
        bindComboBoxRenderer["getBorderColor"] = &tgui::ComboBoxRenderer::getBorderColor;
        bindComboBoxRenderer["setTextureBackground"]
            = &tgui::ComboBoxRenderer::setTextureBackground;
        bindComboBoxRenderer["getTextureBackground"]
            = &tgui::ComboBoxRenderer::getTextureBackground;
        bindComboBoxRenderer["setTextureBackgroundDisabled"]
            = &tgui::ComboBoxRenderer::setTextureBackgroundDisabled;
        bindComboBoxRenderer["getTextureBackgroundDisabled"]
            = &tgui::ComboBoxRenderer::getTextureBackgroundDisabled;
        bindComboBoxRenderer["setTextureArrow"]
            = &tgui::ComboBoxRenderer::setTextureArrow;
        bindComboBoxRenderer["getTextureArrow"]
            = &tgui::ComboBoxRenderer::getTextureArrow;
        bindComboBoxRenderer["setTextureArrowHover"]
            = &tgui::ComboBoxRenderer::setTextureArrowHover;
        bindComboBoxRenderer["getTextureArrowHover"]
            = &tgui::ComboBoxRenderer::getTextureArrowHover;
        bindComboBoxRenderer["setTextureArrowDisabled"]
            = &tgui::ComboBoxRenderer::setTextureArrowDisabled;
        bindComboBoxRenderer["getTextureArrowDisabled"]
            = &tgui::ComboBoxRenderer::getTextureArrowDisabled;
        bindComboBoxRenderer["setListBox"] = &tgui::ComboBoxRenderer::setListBox;
        bindComboBoxRenderer["getListBox"] = &tgui::ComboBoxRenderer::getListBox;
        bindComboBoxRenderer["WidgetRenderer"] = sol::overload(
            static_cast<(tgui::ComboBoxRenderer::*)()>(
                &tgui::ComboBoxRenderer::WidgetRenderer),
            static_cast<(
                tgui::ComboBoxRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                &tgui::ComboBoxRenderer::WidgetRenderer));
    }
    void LoadClassContainer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Container> bindContainer
            = tguiNamespace.new_usertype<tgui::Container>("Container",
                sol::call_constructor,
                sol::constructors<tgui::Container(const char*, bool),
                    tgui::Container(const gui::Container&),
                    tgui::Container(gui::Container &&)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindContainer["operator="] = sol::overload(
            static_cast<gui::Container& (tgui::Container::*)(const gui::Container&)>(
                &tgui::Container::operator=),
            static_cast<gui::Container& (tgui::Container::*)(gui::Container &&)>(
                &tgui::Container::operator=));
        bindContainer["setSize"]
            = sol::overload(static_cast<void (tgui::Container::*)(const gui::Layout2d&)>(
                                &tgui::Container::setSize),
                static_cast<void (tgui::Container::*)(const gui::Layout2d&)>(
                    &tgui::Container::setSize),
                static_cast<void (tgui::Container::*)(gui::Layout, gui::Layout)>(
                    &tgui::Container::setSize));
        bindContainer["getWidgets"] = &tgui::Container::getWidgets;
        bindContainer["add"] = sol::overload(
            [](tgui::Container* self,
                const gui::Widget1a388912f13898735531886bc676b14f81& widgetPtr) -> void {
                return self->add(widgetPtr);
            },
            [](tgui::Container* self,
                const gui::Widget1a388912f13898735531886bc676b14f81& widgetPtr,
                const gui::String& widgetName) -> void {
                return self->add(widgetPtr, widgetName);
            });
        bindContainer["get"] = sol::overload(
            static_cast<gui::Widget1a388912f13898735531886bc676b14f81 (
                tgui::Container::*)(const gui::String&) const>(&tgui::Container::get));
        bindContainer["remove"] = &tgui::Container::remove;
        bindContainer["removeAllWidgets"] = &tgui::Container::removeAllWidgets;
        bindContainer["getInnerSize"] = &tgui::Container::getInnerSize;
        bindContainer["getChildWidgetsOffset"] = &tgui::Container::getChildWidgetsOffset;
        bindContainer["setTextSize"] = &tgui::Container::setTextSize;
        bindContainer["loadWidgetsFromFile"] = sol::overload(
            [](tgui::Container* self, const gui::String& filename) -> void {
                return self->loadWidgetsFromFile(filename);
            },
            [](tgui::Container* self, const gui::String& filename, bool replaceExisting)
                -> void { return self->loadWidgetsFromFile(filename, replaceExisting); });
        bindContainer["saveWidgetsToFile"] = &tgui::Container::saveWidgetsToFile;
        bindContainer["loadWidgetsFromStream"] = sol::overload(
            static_cast<void (tgui::Container::*)(std::stringstream&, bool)>(
                &tgui::Container::loadWidgetsFromStream),
            static_cast<void (tgui::Container::*)(std::stringstream&&, bool)>(
                &tgui::Container::loadWidgetsFromStream));
        bindContainer["saveWidgetsToStream"] = &tgui::Container::saveWidgetsToStream;
        bindContainer["moveWidgetToFront"] = &tgui::Container::moveWidgetToFront;
        bindContainer["moveWidgetToBack"] = &tgui::Container::moveWidgetToBack;
        bindContainer["moveWidgetForward"] = &tgui::Container::moveWidgetForward;
        bindContainer["moveWidgetBackward"] = &tgui::Container::moveWidgetBackward;
        bindContainer["getFocusedChild"] = &tgui::Container::getFocusedChild;
        bindContainer["getFocusedLeaf"] = &tgui::Container::getFocusedLeaf;
        bindContainer["getWidgetAtPosition"] = &tgui::Container::getWidgetAtPosition;
        bindContainer["focusNextWidget"] = sol::overload(
            [](tgui::Container* self) -> bool { return self->focusNextWidget(); },
            [](tgui::Container* self, bool recursive) -> bool {
                return self->focusNextWidget(recursive);
            });
        bindContainer["focusPreviousWidget"] = sol::overload(
            [](tgui::Container* self) -> bool { return self->focusPreviousWidget(); },
            [](tgui::Container* self, bool recursive) -> bool {
                return self->focusPreviousWidget(recursive);
            });
        bindContainer["setFocused"] = &tgui::Container::setFocused;
        bindContainer["processMouseMoveEvent"] = &tgui::Container::processMouseMoveEvent;
        bindContainer["processMousePressEvent"]
            = &tgui::Container::processMousePressEvent;
        bindContainer["processMouseReleaseEvent"]
            = &tgui::Container::processMouseReleaseEvent;
        bindContainer["processMouseWheelScrollEvent"]
            = &tgui::Container::processMouseWheelScrollEvent;
        bindContainer["processKeyPressEvent"] = &tgui::Container::processKeyPressEvent;
        bindContainer["processTextEnteredEvent"]
            = &tgui::Container::processTextEnteredEvent;
        bindContainer["childWidgetFocused"] = &tgui::Container::childWidgetFocused;
        bindContainer["leftMousePressed"] = &tgui::Container::leftMousePressed;
        bindContainer["rightMousePressed"] = &tgui::Container::rightMousePressed;
        bindContainer["leftMouseReleased"] = &tgui::Container::leftMouseReleased;
        bindContainer["rightMouseReleased"] = &tgui::Container::rightMouseReleased;
        bindContainer["mouseMoved"] = &tgui::Container::mouseMoved;
        bindContainer["keyPressed"] = &tgui::Container::keyPressed;
        bindContainer["textEntered"] = &tgui::Container::textEntered;
        bindContainer["mouseWheelScrolled"] = &tgui::Container::mouseWheelScrolled;
        bindContainer["mouseNoLongerOnWidget"] = &tgui::Container::mouseNoLongerOnWidget;
        bindContainer["leftMouseButtonNoLongerDown"]
            = &tgui::Container::leftMouseButtonNoLongerDown;
        bindContainer["rightMouseButtonNoLongerDown"]
            = &tgui::Container::rightMouseButtonNoLongerDown;
        bindContainer["askToolTip"] = &tgui::Container::askToolTip;
        bindContainer["updateTime"] = &tgui::Container::updateTime;
        bindContainer["setParent"] = &tgui::Container::setParent;
        bindContainer["setParentGui"] = &tgui::Container::setParentGui;
    }
    void LoadClassCursor(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Cursor> bindCursor = tguiNamespace.new_usertype<tgui::Cursor>(
            "Cursor", sol::call_constructor, sol::default_constructor);
        bindCursor["setStyle"] = &tgui::Cursor::setStyle;
        bindCursor["resetStyle"] = &tgui::Cursor::resetStyle;
    }
    void LoadClassCustomWidgetForBindings(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::CustomWidgetForBindings> bindCustomWidgetForBindings
            = tguiNamespace.new_usertype<tgui::CustomWidgetForBindings>(
                "CustomWidgetForBindings", sol::call_constructor,
                sol::constructors<tgui::CustomWidgetForBindings(),
                    tgui::CustomWidgetForBindings(const char*),
                    tgui::CustomWidgetForBindings(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindCustomWidgetForBindings["setPosition"]
            = &tgui::CustomWidgetForBindings::setPosition;
        bindCustomWidgetForBindings["setSize"] = &tgui::CustomWidgetForBindings::setSize;
        bindCustomWidgetForBindings["getFullSize"]
            = &tgui::CustomWidgetForBindings::getFullSize;
        bindCustomWidgetForBindings["getAbsolutePosition"]
            = &tgui::CustomWidgetForBindings::getAbsolutePosition;
        bindCustomWidgetForBindings["getWidgetOffset"]
            = &tgui::CustomWidgetForBindings::getWidgetOffset;
        bindCustomWidgetForBindings["setVisible"]
            = &tgui::CustomWidgetForBindings::setVisible;
        bindCustomWidgetForBindings["setEnabled"]
            = &tgui::CustomWidgetForBindings::setEnabled;
        bindCustomWidgetForBindings["setFocused"]
            = &tgui::CustomWidgetForBindings::setFocused;
        bindCustomWidgetForBindings["canGainFocus"]
            = &tgui::CustomWidgetForBindings::canGainFocus;
        bindCustomWidgetForBindings["updateTime"]
            = &tgui::CustomWidgetForBindings::updateTime;
        bindCustomWidgetForBindings["isMouseOnWidget"]
            = &tgui::CustomWidgetForBindings::isMouseOnWidget;
        bindCustomWidgetForBindings["leftMousePressed"]
            = &tgui::CustomWidgetForBindings::leftMousePressed;
        bindCustomWidgetForBindings["leftMouseReleased"]
            = &tgui::CustomWidgetForBindings::leftMouseReleased;
        bindCustomWidgetForBindings["rightMousePressed"]
            = &tgui::CustomWidgetForBindings::rightMousePressed;
        bindCustomWidgetForBindings["rightMouseReleased"]
            = &tgui::CustomWidgetForBindings::rightMouseReleased;
        bindCustomWidgetForBindings["mouseMoved"]
            = &tgui::CustomWidgetForBindings::mouseMoved;
        bindCustomWidgetForBindings["keyPressed"]
            = &tgui::CustomWidgetForBindings::keyPressed;
        bindCustomWidgetForBindings["textEntered"]
            = &tgui::CustomWidgetForBindings::textEntered;
        bindCustomWidgetForBindings["mouseWheelScrolled"]
            = &tgui::CustomWidgetForBindings::mouseWheelScrolled;
        bindCustomWidgetForBindings["mouseNoLongerOnWidget"]
            = &tgui::CustomWidgetForBindings::mouseNoLongerOnWidget;
        bindCustomWidgetForBindings["leftMouseButtonNoLongerDown"]
            = &tgui::CustomWidgetForBindings::leftMouseButtonNoLongerDown;
        bindCustomWidgetForBindings["draw"] = &tgui::CustomWidgetForBindings::draw;
        bindCustomWidgetForBindings["clone"] = &tgui::CustomWidgetForBindings::clone;
        bindCustomWidgetForBindings["create"] = &tgui::CustomWidgetForBindings::create;
        bindCustomWidgetForBindings["implPositionChanged"]
            = &tgui::CustomWidgetForBindings::implPositionChanged;
        bindCustomWidgetForBindings["implSizeChanged"]
            = &tgui::CustomWidgetForBindings::implSizeChanged;
        bindCustomWidgetForBindings["implVisibleChanged"]
            = &tgui::CustomWidgetForBindings::implVisibleChanged;
        bindCustomWidgetForBindings["implEnableChanged"]
            = &tgui::CustomWidgetForBindings::implEnableChanged;
        bindCustomWidgetForBindings["implFocusChanged"]
            = &tgui::CustomWidgetForBindings::implFocusChanged;
        bindCustomWidgetForBindings["implCanGainFocus"]
            = &tgui::CustomWidgetForBindings::implCanGainFocus;
        bindCustomWidgetForBindings["implGetFullSize"]
            = &tgui::CustomWidgetForBindings::implGetFullSize;
        bindCustomWidgetForBindings["implGetAbsolutePosition"]
            = &tgui::CustomWidgetForBindings::implGetAbsolutePosition;
        bindCustomWidgetForBindings["implGetWidgetOffset"]
            = &tgui::CustomWidgetForBindings::implGetWidgetOffset;
        bindCustomWidgetForBindings["implUpdateTimeFunction"]
            = &tgui::CustomWidgetForBindings::implUpdateTimeFunction;
        bindCustomWidgetForBindings["implMouseOnWidget"]
            = &tgui::CustomWidgetForBindings::implMouseOnWidget;
        bindCustomWidgetForBindings["implLeftMousePressed"]
            = &tgui::CustomWidgetForBindings::implLeftMousePressed;
        bindCustomWidgetForBindings["implLeftMouseReleased"]
            = &tgui::CustomWidgetForBindings::implLeftMouseReleased;
        bindCustomWidgetForBindings["implRightMousePressed"]
            = &tgui::CustomWidgetForBindings::implRightMousePressed;
        bindCustomWidgetForBindings["implRightMouseReleased"]
            = &tgui::CustomWidgetForBindings::implRightMouseReleased;
        bindCustomWidgetForBindings["implMouseMoved"]
            = &tgui::CustomWidgetForBindings::implMouseMoved;
        bindCustomWidgetForBindings["implKeyPressed"]
            = &tgui::CustomWidgetForBindings::implKeyPressed;
        bindCustomWidgetForBindings["implTextEntered"]
            = &tgui::CustomWidgetForBindings::implTextEntered;
        bindCustomWidgetForBindings["implMouseWheelScrolled"]
            = &tgui::CustomWidgetForBindings::implMouseWheelScrolled;
        bindCustomWidgetForBindings["implMouseNoLongerOnWidget"]
            = &tgui::CustomWidgetForBindings::implMouseNoLongerOnWidget;
        bindCustomWidgetForBindings["implLeftMouseButtonNoLongerDown"]
            = &tgui::CustomWidgetForBindings::implLeftMouseButtonNoLongerDown;
        bindCustomWidgetForBindings["implMouseEnteredWidget"]
            = &tgui::CustomWidgetForBindings::implMouseEnteredWidget;
        bindCustomWidgetForBindings["implMouseLeftWidget"]
            = &tgui::CustomWidgetForBindings::implMouseLeftWidget;
        bindCustomWidgetForBindings["implRendererChanged"]
            = &tgui::CustomWidgetForBindings::implRendererChanged;
        bindCustomWidgetForBindings["implDrawFunction"]
            = &tgui::CustomWidgetForBindings::implDrawFunction;
    }
    void LoadClassDataIO(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::DataIO> bindDataIO = tguiNamespace.new_usertype<tgui::DataIO>(
            "DataIO", sol::call_constructor, sol::default_constructor);
        bindDataIO["parse"] = &tgui::DataIO::parse;
        bindDataIO["emit"] = &tgui::DataIO::emit;
    }
    void LoadClassDefaultBackendWindow(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::DefaultBackendWindow> bindDefaultBackendWindow
            = tguiNamespace.new_usertype<tgui::DefaultBackendWindow>(
                "DefaultBackendWindow");
        bindDefaultBackendWindow["getGui"] = &tgui::DefaultBackendWindow::getGui;
        bindDefaultBackendWindow["isOpen"] = &tgui::DefaultBackendWindow::isOpen;
        bindDefaultBackendWindow["close"] = &tgui::DefaultBackendWindow::close;
        bindDefaultBackendWindow["pollEvent"] = &tgui::DefaultBackendWindow::pollEvent;
        bindDefaultBackendWindow["draw"] = &tgui::DefaultBackendWindow::draw;
        bindDefaultBackendWindow["mainLoop"] = &tgui::DefaultBackendWindow::mainLoop;
        bindDefaultBackendWindow["setIcon"] = &tgui::DefaultBackendWindow::setIcon;
        bindDefaultBackendWindow["create"] = &tgui::DefaultBackendWindow::create;
    }
    void LoadClassDefaultThemeLoader(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::DefaultThemeLoader> bindDefaultThemeLoader
            = tguiNamespace.new_usertype<tgui::DefaultThemeLoader>("DefaultThemeLoader",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::BaseThemeLoader>());
        bindDefaultThemeLoader["preload"] = &tgui::DefaultThemeLoader::preload;
        bindDefaultThemeLoader["load"] = &tgui::DefaultThemeLoader::load;
        bindDefaultThemeLoader["canLoad"] = &tgui::DefaultThemeLoader::canLoad;
        bindDefaultThemeLoader["flushCache"] = sol::overload(
            [](tgui::DefaultThemeLoader* self) -> void { return self->flushCache(); },
            [](tgui::DefaultThemeLoader* self, const gui::String& filename) -> void {
                return self->flushCache(filename);
            });
    }
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
    void LoadClassDuration(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Duration> bindDuration
            = tguiNamespace.new_usertype<tgui::Duration>("Duration",
                sol::call_constructor,
                sol::constructors<tgui::Duration(),
                    tgui::Duration(std::chrono::duration<Rep, Period>),
                    tgui::Duration(int)>());
        bindDuration["asSeconds"] = &tgui::Duration::asSeconds;
        bindDuration["operator std::chrono::nanoseconds"]
            = &tgui::Duration::operator std::chrono::nanoseconds;
    }
    void LoadClassEditBox(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::EditBox> bindEditBox
            = tguiNamespace.new_usertype<tgui::EditBox>("EditBox", sol::call_constructor,
                sol::constructors<tgui::EditBox(), tgui::EditBox(const char*),
                    tgui::EditBox(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindEditBox["getSharedRenderer"]
            = sol::overload(static_cast<gui::EditBoxRenderer* (tgui::EditBox::*)()>(
                                &tgui::EditBox::getSharedRenderer),
                static_cast<const gui::EditBoxRenderer* (tgui::EditBox::*)() const>(
                    &tgui::EditBox::getSharedRenderer));
        bindEditBox["getRenderer"]
            = sol::overload(static_cast<gui::EditBoxRenderer* (tgui::EditBox::*)()>(
                                &tgui::EditBox::getRenderer),
                static_cast<const gui::EditBoxRenderer* (tgui::EditBox::*)() const>(
                    &tgui::EditBox::getRenderer));
        bindEditBox["setSize"]
            = sol::overload(static_cast<void (tgui::EditBox::*)(const gui::Layout2d&)>(
                                &tgui::EditBox::setSize),
                static_cast<void (tgui::EditBox::*)(const gui::Layout2d&)>(
                    &tgui::EditBox::setSize),
                static_cast<void (tgui::EditBox::*)(gui::Layout, gui::Layout)>(
                    &tgui::EditBox::setSize));
        bindEditBox["setEnabled"] = &tgui::EditBox::setEnabled;
        bindEditBox["setText"] = &tgui::EditBox::setText;
        bindEditBox["getText"] = &tgui::EditBox::getText;
        bindEditBox["setDefaultText"] = &tgui::EditBox::setDefaultText;
        bindEditBox["getDefaultText"] = &tgui::EditBox::getDefaultText;
        bindEditBox["selectText"] = sol::overload(
            [](tgui::EditBox* self) -> void { return self->selectText(); },
            [](tgui::EditBox* self, std::size_t start) -> void {
                return self->selectText(start);
            },
            [](tgui::EditBox* self, std::size_t start, std::size_t length) -> void {
                return self->selectText(start, length);
            });
        bindEditBox["getSelectedText"] = &tgui::EditBox::getSelectedText;
        bindEditBox["setTextSize"] = &tgui::EditBox::setTextSize;
        bindEditBox["getTextSize"] = &tgui::EditBox::getTextSize;
        bindEditBox["setPasswordCharacter"] = &tgui::EditBox::setPasswordCharacter;
        bindEditBox["getPasswordCharacter"] = &tgui::EditBox::getPasswordCharacter;
        bindEditBox["setMaximumCharacters"] = &tgui::EditBox::setMaximumCharacters;
        bindEditBox["getMaximumCharacters"] = &tgui::EditBox::getMaximumCharacters;
        bindEditBox["setAlignment"] = &tgui::EditBox::setAlignment;
        bindEditBox["getAlignment"] = &tgui::EditBox::getAlignment;
        bindEditBox["limitTextWidth"] = sol::overload(
            [](tgui::EditBox* self) -> void { return self->limitTextWidth(); },
            [](tgui::EditBox* self, bool limitWidth) -> void {
                return self->limitTextWidth(limitWidth);
            });
        bindEditBox["isTextWidthLimited"] = &tgui::EditBox::isTextWidthLimited;
        bindEditBox["setReadOnly"] = sol::overload(
            [](tgui::EditBox* self) -> void { return self->setReadOnly(); },
            [](tgui::EditBox* self, bool readOnly) -> void {
                return self->setReadOnly(readOnly);
            });
        bindEditBox["isReadOnly"] = &tgui::EditBox::isReadOnly;
        bindEditBox["setCaretPosition"] = &tgui::EditBox::setCaretPosition;
        bindEditBox["getCaretPosition"] = &tgui::EditBox::getCaretPosition;
        bindEditBox["setInputValidator"] = sol::overload(
            [](tgui::EditBox* self) -> bool { return self->setInputValidator(); },
            [](tgui::EditBox* self, const gui::String& regex) -> bool {
                return self->setInputValidator(regex);
            });
        bindEditBox["getInputValidator"] = &tgui::EditBox::getInputValidator;
        bindEditBox["setSuffix"] = &tgui::EditBox::setSuffix;
        bindEditBox["getSuffix"] = &tgui::EditBox::getSuffix;
        bindEditBox["setFocused"] = &tgui::EditBox::setFocused;
        bindEditBox["isMouseOnWidget"] = &tgui::EditBox::isMouseOnWidget;
        bindEditBox["leftMousePressed"] = &tgui::EditBox::leftMousePressed;
        bindEditBox["mouseMoved"] = &tgui::EditBox::mouseMoved;
        bindEditBox["keyPressed"] = &tgui::EditBox::keyPressed;
        bindEditBox["textEntered"] = &tgui::EditBox::textEntered;
        bindEditBox["draw"] = &tgui::EditBox::draw;
        bindEditBox["create"] = &tgui::EditBox::create;
        bindEditBox["copy"] = &tgui::EditBox::copy;
        bindEditBox["onTextChange"] = &tgui::EditBox::onTextChange;
        bindEditBox["onReturnKeyPress"] = &tgui::EditBox::onReturnKeyPress;
        bindEditBox["onReturnOrUnfocus"] = &tgui::EditBox::onReturnOrUnfocus;
    }
    void LoadClassEditBoxRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::EditBoxRenderer> bindEditBoxRenderer
            = tguiNamespace.new_usertype<tgui::EditBoxRenderer>("EditBoxRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindEditBoxRenderer["setTextStyle"] = &tgui::EditBoxRenderer::setTextStyle;
        bindEditBoxRenderer["getTextStyle"] = &tgui::EditBoxRenderer::getTextStyle;
        bindEditBoxRenderer["setDefaultTextStyle"]
            = &tgui::EditBoxRenderer::setDefaultTextStyle;
        bindEditBoxRenderer["getDefaultTextStyle"]
            = &tgui::EditBoxRenderer::getDefaultTextStyle;
        bindEditBoxRenderer["setBorders"] = &tgui::EditBoxRenderer::setBorders;
        bindEditBoxRenderer["getBorders"] = &tgui::EditBoxRenderer::getBorders;
        bindEditBoxRenderer["setPadding"] = &tgui::EditBoxRenderer::setPadding;
        bindEditBoxRenderer["getPadding"] = &tgui::EditBoxRenderer::getPadding;
        bindEditBoxRenderer["setCaretWidth"] = &tgui::EditBoxRenderer::setCaretWidth;
        bindEditBoxRenderer["getCaretWidth"] = &tgui::EditBoxRenderer::getCaretWidth;
        bindEditBoxRenderer["setTextColor"] = &tgui::EditBoxRenderer::setTextColor;
        bindEditBoxRenderer["getTextColor"] = &tgui::EditBoxRenderer::getTextColor;
        bindEditBoxRenderer["setTextColorDisabled"]
            = &tgui::EditBoxRenderer::setTextColorDisabled;
        bindEditBoxRenderer["getTextColorDisabled"]
            = &tgui::EditBoxRenderer::getTextColorDisabled;
        bindEditBoxRenderer["setTextColorFocused"]
            = &tgui::EditBoxRenderer::setTextColorFocused;
        bindEditBoxRenderer["getTextColorFocused"]
            = &tgui::EditBoxRenderer::getTextColorFocused;
        bindEditBoxRenderer["setSelectedTextColor"]
            = &tgui::EditBoxRenderer::setSelectedTextColor;
        bindEditBoxRenderer["getSelectedTextColor"]
            = &tgui::EditBoxRenderer::getSelectedTextColor;
        bindEditBoxRenderer["setSelectedTextBackgroundColor"]
            = &tgui::EditBoxRenderer::setSelectedTextBackgroundColor;
        bindEditBoxRenderer["getSelectedTextBackgroundColor"]
            = &tgui::EditBoxRenderer::getSelectedTextBackgroundColor;
        bindEditBoxRenderer["setDefaultTextColor"]
            = &tgui::EditBoxRenderer::setDefaultTextColor;
        bindEditBoxRenderer["getDefaultTextColor"]
            = &tgui::EditBoxRenderer::getDefaultTextColor;
        bindEditBoxRenderer["setBackgroundColor"]
            = &tgui::EditBoxRenderer::setBackgroundColor;
        bindEditBoxRenderer["getBackgroundColor"]
            = &tgui::EditBoxRenderer::getBackgroundColor;
        bindEditBoxRenderer["setBackgroundColorHover"]
            = &tgui::EditBoxRenderer::setBackgroundColorHover;
        bindEditBoxRenderer["getBackgroundColorHover"]
            = &tgui::EditBoxRenderer::getBackgroundColorHover;
        bindEditBoxRenderer["setBackgroundColorDisabled"]
            = &tgui::EditBoxRenderer::setBackgroundColorDisabled;
        bindEditBoxRenderer["getBackgroundColorDisabled"]
            = &tgui::EditBoxRenderer::getBackgroundColorDisabled;
        bindEditBoxRenderer["setBackgroundColorFocused"]
            = &tgui::EditBoxRenderer::setBackgroundColorFocused;
        bindEditBoxRenderer["getBackgroundColorFocused"]
            = &tgui::EditBoxRenderer::getBackgroundColorFocused;
        bindEditBoxRenderer["setCaretColor"] = &tgui::EditBoxRenderer::setCaretColor;
        bindEditBoxRenderer["getCaretColor"] = &tgui::EditBoxRenderer::getCaretColor;
        bindEditBoxRenderer["setCaretColorHover"]
            = &tgui::EditBoxRenderer::setCaretColorHover;
        bindEditBoxRenderer["getCaretColorHover"]
            = &tgui::EditBoxRenderer::getCaretColorHover;
        bindEditBoxRenderer["setCaretColorFocused"]
            = &tgui::EditBoxRenderer::setCaretColorFocused;
        bindEditBoxRenderer["getCaretColorFocused"]
            = &tgui::EditBoxRenderer::getCaretColorFocused;
        bindEditBoxRenderer["setBorderColor"] = &tgui::EditBoxRenderer::setBorderColor;
        bindEditBoxRenderer["getBorderColor"] = &tgui::EditBoxRenderer::getBorderColor;
        bindEditBoxRenderer["setBorderColorHover"]
            = &tgui::EditBoxRenderer::setBorderColorHover;
        bindEditBoxRenderer["getBorderColorHover"]
            = &tgui::EditBoxRenderer::getBorderColorHover;
        bindEditBoxRenderer["setBorderColorDisabled"]
            = &tgui::EditBoxRenderer::setBorderColorDisabled;
        bindEditBoxRenderer["getBorderColorDisabled"]
            = &tgui::EditBoxRenderer::getBorderColorDisabled;
        bindEditBoxRenderer["setBorderColorFocused"]
            = &tgui::EditBoxRenderer::setBorderColorFocused;
        bindEditBoxRenderer["getBorderColorFocused"]
            = &tgui::EditBoxRenderer::getBorderColorFocused;
        bindEditBoxRenderer["setTexture"] = &tgui::EditBoxRenderer::setTexture;
        bindEditBoxRenderer["getTexture"] = &tgui::EditBoxRenderer::getTexture;
        bindEditBoxRenderer["setTextureHover"] = &tgui::EditBoxRenderer::setTextureHover;
        bindEditBoxRenderer["getTextureHover"] = &tgui::EditBoxRenderer::getTextureHover;
        bindEditBoxRenderer["setTextureDisabled"]
            = &tgui::EditBoxRenderer::setTextureDisabled;
        bindEditBoxRenderer["getTextureDisabled"]
            = &tgui::EditBoxRenderer::getTextureDisabled;
        bindEditBoxRenderer["setTextureFocused"]
            = &tgui::EditBoxRenderer::setTextureFocused;
        bindEditBoxRenderer["getTextureFocused"]
            = &tgui::EditBoxRenderer::getTextureFocused;
        bindEditBoxRenderer["WidgetRenderer"]
            = sol::overload(static_cast<(tgui::EditBoxRenderer::*)()>(
                                &tgui::EditBoxRenderer::WidgetRenderer),
                static_cast<(
                    tgui::EditBoxRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                    &tgui::EditBoxRenderer::WidgetRenderer));
    }
    void LoadClassException(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Exception> bindException
            = tguiNamespace.new_usertype<tgui::Exception>("Exception",
                sol::call_constructor,
                sol::constructors<tgui::Exception(const gui::String&)>());
    }
    void LoadClassFilesystem(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Filesystem> bindFilesystem
            = tguiNamespace.new_usertype<tgui::Filesystem>(
                "Filesystem", sol::call_constructor, sol::default_constructor);
        bindFilesystem["directoryExists"]
            = sol::overload(static_cast<bool (*)(const gui::Filesystem::Path&)>(
                                &tgui::Filesystem::directoryExists),
                static_cast<bool (*)(const gui::String&)>(
                    &tgui::Filesystem::directoryExists));
        bindFilesystem["fileExists"]
            = sol::overload(static_cast<bool (*)(const gui::Filesystem::Path&)>(
                                &tgui::Filesystem::fileExists),
                static_cast<bool (*)(const gui::String&)>(&tgui::Filesystem::fileExists));
        bindFilesystem["createDirectory"]
            = sol::overload(static_cast<bool (*)(const gui::Filesystem::Path&)>(
                                &tgui::Filesystem::createDirectory),
                static_cast<bool (*)(const gui::String&)>(
                    &tgui::Filesystem::createDirectory));
        bindFilesystem["getHomeDirectory"] = &tgui::Filesystem::getHomeDirectory;
        bindFilesystem["getCurrentWorkingDirectory"]
            = &tgui::Filesystem::getCurrentWorkingDirectory;
        bindFilesystem["getLocalDataDirectory"]
            = &tgui::Filesystem::getLocalDataDirectory;
        bindFilesystem["listFilesInDirectory"] = &tgui::Filesystem::listFilesInDirectory;
    }
    void LoadClassFileDialog(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::FileDialog> bindFileDialog
            = tguiNamespace.new_usertype<tgui::FileDialog>("FileDialog",
                sol::call_constructor,
                sol::constructors<tgui::FileDialog(), tgui::FileDialog(const char*),
                    tgui::FileDialog(const char*, bool),
                    tgui::FileDialog(const gui::FileDialog&),
                    tgui::FileDialog(gui::FileDialog &&)>(),
                sol::base_classes,
                sol::bases<tgui::ChildWindow, tgui::Container, tgui::Widget>());
        bindFileDialog["operator="] = sol::overload(
            static_cast<gui::FileDialog& (tgui::FileDialog::*)(const gui::FileDialog&)>(
                &tgui::FileDialog::operator=),
            static_cast<gui::FileDialog& (tgui::FileDialog::*)(gui::FileDialog &&)>(
                &tgui::FileDialog::operator=));
        bindFileDialog["getSharedRenderer"]
            = sol::overload(static_cast<gui::FileDialogRenderer* (tgui::FileDialog::*)()>(
                                &tgui::FileDialog::getSharedRenderer),
                static_cast<const gui::FileDialogRenderer* (tgui::FileDialog::*)() const>(
                    &tgui::FileDialog::getSharedRenderer));
        bindFileDialog["getRenderer"]
            = sol::overload(static_cast<gui::FileDialogRenderer* (tgui::FileDialog::*)()>(
                                &tgui::FileDialog::getRenderer),
                static_cast<const gui::FileDialogRenderer* (tgui::FileDialog::*)() const>(
                    &tgui::FileDialog::getRenderer));
        bindFileDialog["getSelectedPaths"] = &tgui::FileDialog::getSelectedPaths;
        bindFileDialog["setPath"]
            = sol::overload(static_cast<void (tgui::FileDialog::*)(const gui::String&)>(
                                &tgui::FileDialog::setPath),
                static_cast<void (tgui::FileDialog::*)(const gui::Filesystem::Path&)>(
                    &tgui::FileDialog::setPath));
        bindFileDialog["getPath"] = &tgui::FileDialog::getPath;
        bindFileDialog["setFilename"] = &tgui::FileDialog::setFilename;
        bindFileDialog["getFilename"] = &tgui::FileDialog::getFilename;
        bindFileDialog["setFileTypeFilters"] = sol::overload(
            [](tgui::FileDialog* self,
                const std::vector<std::pair<gui::String, std::vector<gui::String>>>&
                    filters) -> void { return self->setFileTypeFilters(filters); },
            [](tgui::FileDialog* self,
                const std::vector<std::pair<gui::String, std::vector<gui::String>>>&
                    filters,
                std::size_t defaultFilterIndex) -> void {
                return self->setFileTypeFilters(filters, defaultFilterIndex);
            });
        bindFileDialog["getFileTypeFilters"] = &tgui::FileDialog::getFileTypeFilters;
        bindFileDialog["getFileTypeFiltersIndex"]
            = &tgui::FileDialog::getFileTypeFiltersIndex;
        bindFileDialog["setConfirmButtonText"] = sol::overload(
            [](tgui::FileDialog* self) -> void { return self->setConfirmButtonText(); },
            [](tgui::FileDialog* self, const gui::String& text) -> void {
                return self->setConfirmButtonText(text);
            });
        bindFileDialog["getConfirmButtonText"] = &tgui::FileDialog::getConfirmButtonText;
        bindFileDialog["setCancelButtonText"] = sol::overload(
            [](tgui::FileDialog* self) -> void { return self->setCancelButtonText(); },
            [](tgui::FileDialog* self, const gui::String& text) -> void {
                return self->setCancelButtonText(text);
            });
        bindFileDialog["getCancelButtonText"] = &tgui::FileDialog::getCancelButtonText;
        bindFileDialog["setFilenameLabelText"] = sol::overload(
            [](tgui::FileDialog* self) -> void { return self->setFilenameLabelText(); },
            [](tgui::FileDialog* self, const gui::String& labelText) -> void {
                return self->setFilenameLabelText(labelText);
            });
        bindFileDialog["getFilenameLabelText"] = &tgui::FileDialog::getFilenameLabelText;
        bindFileDialog["setListViewColumnCaptions"] = sol::overload(
            [](tgui::FileDialog* self) -> void {
                return self->setListViewColumnCaptions();
            },
            [](tgui::FileDialog* self, const gui::String& nameColumnText) -> void {
                return self->setListViewColumnCaptions(nameColumnText);
            },
            [](tgui::FileDialog* self, const gui::String& nameColumnText,
                const gui::String& sizeColumnText) -> void {
                return self->setListViewColumnCaptions(nameColumnText, sizeColumnText);
            },
            [](tgui::FileDialog* self, const gui::String& nameColumnText,
                const gui::String& sizeColumnText,
                const gui::String& modifiedColumnText) -> void {
                return self->setListViewColumnCaptions(
                    nameColumnText, sizeColumnText, modifiedColumnText);
            });
        bindFileDialog["getListViewColumnCaptions"]
            = &tgui::FileDialog::getListViewColumnCaptions;
        bindFileDialog["setFileMustExist"] = &tgui::FileDialog::setFileMustExist;
        bindFileDialog["getFileMustExist"] = &tgui::FileDialog::getFileMustExist;
        bindFileDialog["setSelectingDirectory"]
            = &tgui::FileDialog::setSelectingDirectory;
        bindFileDialog["getSelectingDirectory"]
            = &tgui::FileDialog::getSelectingDirectory;
        bindFileDialog["setMultiSelect"] = &tgui::FileDialog::setMultiSelect;
        bindFileDialog["getMultiSelect"] = &tgui::FileDialog::getMultiSelect;
        bindFileDialog["setIconLoader"] = &tgui::FileDialog::setIconLoader;
        bindFileDialog["getIconLoader"] = &tgui::FileDialog::getIconLoader;
        bindFileDialog["keyPressed"] = &tgui::FileDialog::keyPressed;
        bindFileDialog["create"] = sol::overload(
            [](tgui::FileDialog* self)
                -> gui::FileDialog1a81942519fac991f576139fbe55e55a7d {
                return self->create();
            },
            [](tgui::FileDialog* self,
                gui::String title) -> gui::FileDialog1a81942519fac991f576139fbe55e55a7d {
                return self->create(title);
            },
            [](tgui::FileDialog* self, gui::String title, gui::String confirmButtonText)
                -> gui::FileDialog1a81942519fac991f576139fbe55e55a7d {
                return self->create(title, confirmButtonText);
            });
        bindFileDialog["copy"] = &tgui::FileDialog::copy;
        bindFileDialog["onFileSelect"] = &tgui::FileDialog::onFileSelect;
    }
    void LoadClassFileDialogIconLoader(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::FileDialogIconLoader> bindFileDialogIconLoader
            = tguiNamespace.new_usertype<tgui::FileDialogIconLoader>(
                "FileDialogIconLoader", sol::call_constructor, sol::default_constructor);
        bindFileDialogIconLoader["update"] = &tgui::FileDialogIconLoader::update;
        bindFileDialogIconLoader["supportsSystemIcons"]
            = &tgui::FileDialogIconLoader::supportsSystemIcons;
        bindFileDialogIconLoader["hasGenericIcons"]
            = &tgui::FileDialogIconLoader::hasGenericIcons;
        bindFileDialogIconLoader["getGenericFileIcon"]
            = &tgui::FileDialogIconLoader::getGenericFileIcon;
        bindFileDialogIconLoader["requestFileIcons"]
            = &tgui::FileDialogIconLoader::requestFileIcons;
        bindFileDialogIconLoader["retrieveFileIcons"]
            = &tgui::FileDialogIconLoader::retrieveFileIcons;
        bindFileDialogIconLoader["createInstance"]
            = &tgui::FileDialogIconLoader::createInstance;
    }
    void LoadClassFileDialogRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::FileDialogRenderer> bindFileDialogRenderer
            = tguiNamespace.new_usertype<tgui::FileDialogRenderer>("FileDialogRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::ChildWindowRenderer, tgui::WidgetRenderer>());
        bindFileDialogRenderer["setListView"] = &tgui::FileDialogRenderer::setListView;
        bindFileDialogRenderer["getListView"] = &tgui::FileDialogRenderer::getListView;
        bindFileDialogRenderer["setEditBox"] = &tgui::FileDialogRenderer::setEditBox;
        bindFileDialogRenderer["getEditBox"] = &tgui::FileDialogRenderer::getEditBox;
        bindFileDialogRenderer["setFilenameLabel"]
            = &tgui::FileDialogRenderer::setFilenameLabel;
        bindFileDialogRenderer["getFilenameLabel"]
            = &tgui::FileDialogRenderer::getFilenameLabel;
        bindFileDialogRenderer["setFileTypeComboBox"]
            = &tgui::FileDialogRenderer::setFileTypeComboBox;
        bindFileDialogRenderer["getFileTypeComboBox"]
            = &tgui::FileDialogRenderer::getFileTypeComboBox;
        bindFileDialogRenderer["setButton"] = &tgui::FileDialogRenderer::setButton;
        bindFileDialogRenderer["getButton"] = &tgui::FileDialogRenderer::getButton;
        bindFileDialogRenderer["setBackButton"]
            = &tgui::FileDialogRenderer::setBackButton;
        bindFileDialogRenderer["getBackButton"]
            = &tgui::FileDialogRenderer::getBackButton;
        bindFileDialogRenderer["setForwardButton"]
            = &tgui::FileDialogRenderer::setForwardButton;
        bindFileDialogRenderer["getForwardButton"]
            = &tgui::FileDialogRenderer::getForwardButton;
        bindFileDialogRenderer["setUpButton"] = &tgui::FileDialogRenderer::setUpButton;
        bindFileDialogRenderer["getUpButton"] = &tgui::FileDialogRenderer::getUpButton;
        bindFileDialogRenderer["setArrowsOnNavigationButtonsVisible"]
            = &tgui::FileDialogRenderer::setArrowsOnNavigationButtonsVisible;
        bindFileDialogRenderer["getArrowsOnNavigationButtonsVisible"]
            = &tgui::FileDialogRenderer::getArrowsOnNavigationButtonsVisible;
    }
    void LoadClassFont(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Font> bindFont = tguiNamespace.new_usertype<tgui::Font>(
            "Font", sol::call_constructor,
            sol::constructors<tgui::Font(), tgui::Font(std::nullptr_t),
                tgui::Font(const gui::String&), tgui::Font(const char*),
                tgui::Font(const void*, std::size_t),
                tgui::Font(std::shared_ptr<gui::BackendFontBase>, const gui::String&)>());
        bindFont["getId"] = &tgui::Font::getId;
        bindFont["operator bool"] = &tgui::Font::operator bool;
        bindFont[sol::meta_function::equal_to]
            = sol::overload(static_cast<bool (tgui::Font::*)(std::nullptr_t) const>(
                                &tgui::Font::operator==),
                static_cast<bool (tgui::Font::*)(const gui::Font&) const>(
                    &tgui::Font::operator==));
        bindFont["getGlyph"] = sol::overload(
            [](tgui::Font* self, char32_t codePoint, unsigned int characterSize,
                bool bold) -> gui::FontGlyph {
                return self->getGlyph(codePoint, characterSize, bold);
            },
            [](tgui::Font* self, char32_t codePoint, unsigned int characterSize,
                bool bold, float outlineThickness) -> gui::FontGlyph {
                return self->getGlyph(codePoint, characterSize, bold, outlineThickness);
            });
        bindFont["getKerning"] = &tgui::Font::getKerning;
        bindFont["getLineSpacing"] = &tgui::Font::getLineSpacing;
        bindFont["getBackendFont"] = &tgui::Font::getBackendFont;
        bindFont["setGlobalFont"] = &tgui::Font::setGlobalFont;
        bindFont["getGlobalFont"] = &tgui::Font::getGlobalFont;
    }
    void LoadClassGrid(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Grid> bindGrid
            = tguiNamespace.new_usertype<tgui::Grid>("Grid", sol::call_constructor,
                sol::constructors<tgui::Grid(), tgui::Grid(const char*),
                    tgui::Grid(const char*, bool), tgui::Grid(const gui::Grid&),
                    tgui::Grid(gui::Grid &&)>(),
                sol::base_classes, sol::bases<tgui::Container, tgui::Widget>());
        bindGrid["operator="]
            = sol::overload(static_cast<gui::Grid& (tgui::Grid::*)(const gui::Grid&)>(
                                &tgui::Grid::operator=),
                static_cast<gui::Grid& (tgui::Grid::*)(gui::Grid &&)>(
                    &tgui::Grid::operator=));
        bindGrid["setSize"] = sol::overload(
            static_cast<void (tgui::Grid::*)(const gui::Layout2d&)>(&tgui::Grid::setSize),
            static_cast<void (tgui::Grid::*)(const gui::Layout2d&)>(&tgui::Grid::setSize),
            static_cast<void (tgui::Grid::*)(gui::Layout, gui::Layout)>(
                &tgui::Grid::setSize));
        bindGrid["setAutoSize"] = &tgui::Grid::setAutoSize;
        bindGrid["getAutoSize"] = &tgui::Grid::getAutoSize;
        bindGrid["remove"] = &tgui::Grid::remove;
        bindGrid["removeAllWidgets"] = &tgui::Grid::removeAllWidgets;
        bindGrid["addWidget"] = sol::overload(
            [](tgui::Grid* self,
                const gui::Widget1a388912f13898735531886bc676b14f81& widget,
                std::size_t row, std::size_t column) -> void {
                return self->addWidget(widget, row, column);
            },
            [](tgui::Grid* self,
                const gui::Widget1a388912f13898735531886bc676b14f81& widget,
                std::size_t row, std::size_t column,
                gui::Grid1a862e75cc54ce2fff46c9590db7f6b5e9 alignment) -> void {
                return self->addWidget(widget, row, column, alignment);
            },
            [](tgui::Grid* self,
                const gui::Widget1a388912f13898735531886bc676b14f81& widget,
                std::size_t row, std::size_t column,
                gui::Grid1a862e75cc54ce2fff46c9590db7f6b5e9 alignment,
                const tgui::Padding& padding) -> void {
                return self->addWidget(widget, row, column, alignment, padding);
            });
        bindGrid["getWidget"] = &tgui::Grid::getWidget;
        bindGrid["getWidgetLocations"] = &tgui::Grid::getWidgetLocations;
        bindGrid["setWidgetPadding"]
            = sol::overload(static_cast<void (tgui::Grid::*)(
                                const gui::Widget1a388912f13898735531886bc676b14f81&,
                                const tgui::Padding&)>(&tgui::Grid::setWidgetPadding),
                static_cast<void (tgui::Grid::*)(std::size_t, std::size_t,
                    const tgui::Padding&)>(&tgui::Grid::setWidgetPadding));
        bindGrid["getWidgetPadding"] = sol::overload(
            static_cast<tgui::Padding (tgui::Grid::*)(
                const gui::Widget1a388912f13898735531886bc676b14f81&) const>(
                &tgui::Grid::getWidgetPadding),
            static_cast<tgui::Padding (tgui::Grid::*)(std::size_t, std::size_t) const>(
                &tgui::Grid::getWidgetPadding));
        bindGrid["setWidgetAlignment"]
            = sol::overload(static_cast<void (tgui::Grid::*)(
                                const gui::Widget1a388912f13898735531886bc676b14f81&,
                                gui::Grid1a862e75cc54ce2fff46c9590db7f6b5e9)>(
                                &tgui::Grid::setWidgetAlignment),
                static_cast<void (tgui::Grid::*)(std::size_t, std::size_t,
                    gui::Grid1a862e75cc54ce2fff46c9590db7f6b5e9)>(
                    &tgui::Grid::setWidgetAlignment));
        bindGrid["getWidgetAlignment"] = sol::overload(
            static_cast<gui::Grid1a862e75cc54ce2fff46c9590db7f6b5e9 (tgui::Grid::*)(
                const gui::Widget1a388912f13898735531886bc676b14f81&) const>(
                &tgui::Grid::getWidgetAlignment),
            static_cast<gui::Grid1a862e75cc54ce2fff46c9590db7f6b5e9 (tgui::Grid::*)(
                std::size_t, std::size_t) const>(&tgui::Grid::getWidgetAlignment));
        bindGrid["getGridWidgets"] = &tgui::Grid::getGridWidgets;
        bindGrid["isMouseOnWidget"] = &tgui::Grid::isMouseOnWidget;
        bindGrid["create"] = &tgui::Grid::create;
        bindGrid["copy"] = &tgui::Grid::copy;
    }
    void LoadClassGroup(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Group> bindGroup
            = tguiNamespace.new_usertype<tgui::Group>("Group", sol::call_constructor,
                sol::constructors<tgui::Group(), tgui::Group(const char*),
                    tgui::Group(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Container, tgui::Widget>());
        bindGroup["getSharedRenderer"]
            = sol::overload(static_cast<gui::GroupRenderer* (tgui::Group::*)()>(
                                &tgui::Group::getSharedRenderer),
                static_cast<const gui::GroupRenderer* (tgui::Group::*)() const>(
                    &tgui::Group::getSharedRenderer));
        bindGroup["getRenderer"]
            = sol::overload(static_cast<gui::GroupRenderer* (tgui::Group::*)()>(
                                &tgui::Group::getRenderer),
                static_cast<const gui::GroupRenderer* (tgui::Group::*)() const>(
                    &tgui::Group::getRenderer));
        bindGroup["setSize"]
            = sol::overload(static_cast<void (tgui::Group::*)(const gui::Layout2d&)>(
                                &tgui::Group::setSize),
                static_cast<void (tgui::Group::*)(const gui::Layout2d&)>(
                    &tgui::Group::setSize),
                static_cast<void (tgui::Group::*)(gui::Layout, gui::Layout)>(
                    &tgui::Group::setSize));
        bindGroup["getInnerSize"] = &tgui::Group::getInnerSize;
        bindGroup["getChildWidgetsOffset"] = &tgui::Group::getChildWidgetsOffset;
        bindGroup["isMouseOnWidget"] = &tgui::Group::isMouseOnWidget;
        bindGroup["draw"] = &tgui::Group::draw;
        bindGroup["create"] = sol::overload(
            [](tgui::Group* self) -> gui::Group1a4ef3a6223e5542ac07edb3f010d8c2c3 {
                return self->create();
            },
            [](tgui::Group* self, const gui::Layout2d& size)
                -> gui::Group1a4ef3a6223e5542ac07edb3f010d8c2c3 {
                return self->create(size);
            });
        bindGroup["copy"] = &tgui::Group::copy;
    }
    void LoadClassGroupRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::GroupRenderer> bindGroupRenderer
            = tguiNamespace.new_usertype<tgui::GroupRenderer>("GroupRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindGroupRenderer["setPadding"] = &tgui::GroupRenderer::setPadding;
        bindGroupRenderer["getPadding"] = &tgui::GroupRenderer::getPadding;
        bindGroupRenderer["WidgetRenderer"] = sol::overload(
            static_cast<(tgui::GroupRenderer::*)()>(&tgui::GroupRenderer::WidgetRenderer),
            static_cast<(
                tgui::GroupRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                &tgui::GroupRenderer::WidgetRenderer));
    }
    void LoadClassGuiBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::GuiBase> bindGuiBase
            = tguiNamespace.new_usertype<tgui::GuiBase>("GuiBase");
        bindGuiBase["operator="] = &tgui::GuiBase::operator=;
        bindGuiBase["setAbsoluteViewport"] = &tgui::GuiBase::setAbsoluteViewport;
        bindGuiBase["setRelativeViewport"] = &tgui::GuiBase::setRelativeViewport;
        bindGuiBase["getViewport"] = &tgui::GuiBase::getViewport;
        bindGuiBase["setAbsoluteView"] = &tgui::GuiBase::setAbsoluteView;
        bindGuiBase["setRelativeView"] = &tgui::GuiBase::setRelativeView;
        bindGuiBase["getView"] = &tgui::GuiBase::getView;
        bindGuiBase["handleEvent"] = &tgui::GuiBase::handleEvent;
        bindGuiBase["setTabKeyUsageEnabled"] = &tgui::GuiBase::setTabKeyUsageEnabled;
        bindGuiBase["isTabKeyUsageEnabled"] = &tgui::GuiBase::isTabKeyUsageEnabled;
        bindGuiBase["draw"] = &tgui::GuiBase::draw;
        bindGuiBase["getContainer"] = &tgui::GuiBase::getContainer;
        bindGuiBase["setFont"] = &tgui::GuiBase::setFont;
        bindGuiBase["getFont"] = &tgui::GuiBase::getFont;
        bindGuiBase["getWidgets"] = &tgui::GuiBase::getWidgets;
        bindGuiBase["add"] = sol::overload(
            [](tgui::GuiBase* self,
                const gui::Widget1a388912f13898735531886bc676b14f81& widgetPtr) -> void {
                return self->add(widgetPtr);
            },
            [](tgui::GuiBase* self,
                const gui::Widget1a388912f13898735531886bc676b14f81& widgetPtr,
                const gui::String& widgetName) -> void {
                return self->add(widgetPtr, widgetName);
            });
        bindGuiBase["get"]
            = sol::overload(static_cast<gui::Widget1a388912f13898735531886bc676b14f81 (
                    tgui::GuiBase::*)(const gui::String&) const>(&tgui::GuiBase::get));
        bindGuiBase["remove"] = &tgui::GuiBase::remove;
        bindGuiBase["removeAllWidgets"] = &tgui::GuiBase::removeAllWidgets;
        bindGuiBase["getFocusedChild"] = &tgui::GuiBase::getFocusedChild;
        bindGuiBase["getFocusedLeaf"] = &tgui::GuiBase::getFocusedLeaf;
        bindGuiBase["getWidgetAtPosition"] = &tgui::GuiBase::getWidgetAtPosition;
        bindGuiBase["getWidgetBelowMouseCursor"]
            = &tgui::GuiBase::getWidgetBelowMouseCursor;
        bindGuiBase["focusNextWidget"] = sol::overload(
            [](tgui::GuiBase* self) -> bool { return self->focusNextWidget(); },
            [](tgui::GuiBase* self, bool recursive) -> bool {
                return self->focusNextWidget(recursive);
            });
        bindGuiBase["focusPreviousWidget"] = sol::overload(
            [](tgui::GuiBase* self) -> bool { return self->focusPreviousWidget(); },
            [](tgui::GuiBase* self, bool recursive) -> bool {
                return self->focusPreviousWidget(recursive);
            });
        bindGuiBase["unfocusAllWidgets"] = &tgui::GuiBase::unfocusAllWidgets;
        bindGuiBase["moveWidgetToFront"] = &tgui::GuiBase::moveWidgetToFront;
        bindGuiBase["moveWidgetToBack"] = &tgui::GuiBase::moveWidgetToBack;
        bindGuiBase["moveWidgetForward"] = &tgui::GuiBase::moveWidgetForward;
        bindGuiBase["moveWidgetBackward"] = &tgui::GuiBase::moveWidgetBackward;
        bindGuiBase["setOpacity"] = &tgui::GuiBase::setOpacity;
        bindGuiBase["getOpacity"] = &tgui::GuiBase::getOpacity;
        bindGuiBase["setTextSize"] = &tgui::GuiBase::setTextSize;
        bindGuiBase["getTextSize"] = &tgui::GuiBase::getTextSize;
        bindGuiBase["loadWidgetsFromFile"] = sol::overload(
            [](tgui::GuiBase* self, const gui::String& filename) -> void {
                return self->loadWidgetsFromFile(filename);
            },
            [](tgui::GuiBase* self, const gui::String& filename, bool replaceExisting)
                -> void { return self->loadWidgetsFromFile(filename, replaceExisting); });
        bindGuiBase["saveWidgetsToFile"] = &tgui::GuiBase::saveWidgetsToFile;
        bindGuiBase["loadWidgetsFromStream"] = sol::overload(
            static_cast<void (tgui::GuiBase::*)(std::stringstream&, bool)>(
                &tgui::GuiBase::loadWidgetsFromStream),
            static_cast<void (tgui::GuiBase::*)(std::stringstream&&, bool)>(
                &tgui::GuiBase::loadWidgetsFromStream));
        bindGuiBase["saveWidgetsToStream"] = &tgui::GuiBase::saveWidgetsToStream;
        bindGuiBase["setOverrideMouseCursor"] = &tgui::GuiBase::setOverrideMouseCursor;
        bindGuiBase["restoreOverrideMouseCursor"]
            = &tgui::GuiBase::restoreOverrideMouseCursor;
        bindGuiBase["requestMouseCursor"] = &tgui::GuiBase::requestMouseCursor;
        bindGuiBase["setDrawingUpdatesTime"] = &tgui::GuiBase::setDrawingUpdatesTime;
        bindGuiBase["updateTime"] = sol::overload(
            static_cast<bool (tgui::GuiBase::*)()>(&tgui::GuiBase::updateTime),
            static_cast<bool (tgui::GuiBase::*)(gui::Duration)>(
                &tgui::GuiBase::updateTime));
        bindGuiBase["mapPixelToView"] = &tgui::GuiBase::mapPixelToView;
        bindGuiBase["mainLoop"] = &tgui::GuiBase::mainLoop;
        bindGuiBase["onViewChange"] = &tgui::GuiBase::onViewChange;
    }
    void LoadClassHorizontalLayout(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::HorizontalLayout> bindHorizontalLayout
            = tguiNamespace.new_usertype<tgui::HorizontalLayout>("HorizontalLayout",
                sol::call_constructor,
                sol::constructors<tgui::HorizontalLayout(),
                    tgui::HorizontalLayout(const char*),
                    tgui::HorizontalLayout(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::BoxLayoutRatios, tgui::BoxLayout, tgui::Group,
                    tgui::Container, tgui::Widget>());
        bindHorizontalLayout["create"] = sol::overload(
            [](tgui::HorizontalLayout* self)
                -> gui::HorizontalLayout1a4547c4b89b9a96efab1c363d1618c433 {
                return self->create();
            },
            [](tgui::HorizontalLayout* self, const gui::Layout2d& size)
                -> gui::HorizontalLayout1a4547c4b89b9a96efab1c363d1618c433 {
                return self->create(size);
            });
        bindHorizontalLayout["copy"] = &tgui::HorizontalLayout::copy;
    }
    void LoadClassHorizontalWrap(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::HorizontalWrap> bindHorizontalWrap
            = tguiNamespace.new_usertype<tgui::HorizontalWrap>("HorizontalWrap",
                sol::call_constructor,
                sol::constructors<tgui::HorizontalWrap(),
                    tgui::HorizontalWrap(const char*),
                    tgui::HorizontalWrap(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::BoxLayout, tgui::Group, tgui::Container,
                    tgui::Widget>());
        bindHorizontalWrap["create"] = sol::overload(
            [](tgui::HorizontalWrap* self)
                -> gui::HorizontalWrap1aa9d79846648bbb7e466bbcc2c32b77d9 {
                return self->create();
            },
            [](tgui::HorizontalWrap* self, const gui::Layout2d& size)
                -> gui::HorizontalWrap1aa9d79846648bbb7e466bbcc2c32b77d9 {
                return self->create(size);
            });
        bindHorizontalWrap["copy"] = &tgui::HorizontalWrap::copy;
    }
    void LoadClassKnob(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Knob> bindKnob
            = tguiNamespace.new_usertype<tgui::Knob>("Knob", sol::call_constructor,
                sol::constructors<tgui::Knob(), tgui::Knob(const char*),
                    tgui::Knob(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindKnob["getSharedRenderer"]
            = sol::overload(static_cast<gui::KnobRenderer* (tgui::Knob::*)()>(
                                &tgui::Knob::getSharedRenderer),
                static_cast<const gui::KnobRenderer* (tgui::Knob::*)() const>(
                    &tgui::Knob::getSharedRenderer));
        bindKnob["getRenderer"] = sol::overload(
            static_cast<gui::KnobRenderer* (tgui::Knob::*)()>(&tgui::Knob::getRenderer),
            static_cast<const gui::KnobRenderer* (tgui::Knob::*)() const>(
                &tgui::Knob::getRenderer));
        bindKnob["setSize"] = sol::overload(
            static_cast<void (tgui::Knob::*)(const gui::Layout2d&)>(&tgui::Knob::setSize),
            static_cast<void (tgui::Knob::*)(const gui::Layout2d&)>(&tgui::Knob::setSize),
            static_cast<void (tgui::Knob::*)(gui::Layout, gui::Layout)>(
                &tgui::Knob::setSize));
        bindKnob["setStartRotation"] = &tgui::Knob::setStartRotation;
        bindKnob["getStartRotation"] = &tgui::Knob::getStartRotation;
        bindKnob["setEndRotation"] = &tgui::Knob::setEndRotation;
        bindKnob["getEndRotation"] = &tgui::Knob::getEndRotation;
        bindKnob["setMinimum"] = &tgui::Knob::setMinimum;
        bindKnob["getMinimum"] = &tgui::Knob::getMinimum;
        bindKnob["setMaximum"] = &tgui::Knob::setMaximum;
        bindKnob["getMaximum"] = &tgui::Knob::getMaximum;
        bindKnob["setValue"] = &tgui::Knob::setValue;
        bindKnob["getValue"] = &tgui::Knob::getValue;
        bindKnob["setClockwiseTurning"] = &tgui::Knob::setClockwiseTurning;
        bindKnob["getClockwiseTurning"] = &tgui::Knob::getClockwiseTurning;
        bindKnob["isMouseOnWidget"] = &tgui::Knob::isMouseOnWidget;
        bindKnob["leftMousePressed"] = &tgui::Knob::leftMousePressed;
        bindKnob["mouseMoved"] = &tgui::Knob::mouseMoved;
        bindKnob["draw"] = &tgui::Knob::draw;
        bindKnob["create"] = &tgui::Knob::create;
        bindKnob["copy"] = &tgui::Knob::copy;
        bindKnob["onValueChange"] = &tgui::Knob::onValueChange;
    }
    void LoadClassKnobRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::KnobRenderer> bindKnobRenderer
            = tguiNamespace.new_usertype<tgui::KnobRenderer>("KnobRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindKnobRenderer["setBorders"] = &tgui::KnobRenderer::setBorders;
        bindKnobRenderer["getBorders"] = &tgui::KnobRenderer::getBorders;
        bindKnobRenderer["setBackgroundColor"] = &tgui::KnobRenderer::setBackgroundColor;
        bindKnobRenderer["getBackgroundColor"] = &tgui::KnobRenderer::getBackgroundColor;
        bindKnobRenderer["setThumbColor"] = &tgui::KnobRenderer::setThumbColor;
        bindKnobRenderer["getThumbColor"] = &tgui::KnobRenderer::getThumbColor;
        bindKnobRenderer["setBorderColor"] = &tgui::KnobRenderer::setBorderColor;
        bindKnobRenderer["getBorderColor"] = &tgui::KnobRenderer::getBorderColor;
        bindKnobRenderer["setTextureBackground"]
            = &tgui::KnobRenderer::setTextureBackground;
        bindKnobRenderer["getTextureBackground"]
            = &tgui::KnobRenderer::getTextureBackground;
        bindKnobRenderer["setTextureForeground"]
            = &tgui::KnobRenderer::setTextureForeground;
        bindKnobRenderer["getTextureForeground"]
            = &tgui::KnobRenderer::getTextureForeground;
        bindKnobRenderer["setImageRotation"] = &tgui::KnobRenderer::setImageRotation;
        bindKnobRenderer["getImageRotation"] = &tgui::KnobRenderer::getImageRotation;
        bindKnobRenderer["WidgetRenderer"] = sol::overload(
            static_cast<(tgui::KnobRenderer::*)()>(&tgui::KnobRenderer::WidgetRenderer),
            static_cast<(
                tgui::KnobRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                &tgui::KnobRenderer::WidgetRenderer));
    }
    void LoadClassLabel(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Label> bindLabel
            = tguiNamespace.new_usertype<tgui::Label>("Label", sol::call_constructor,
                sol::constructors<tgui::Label(), tgui::Label(const char*),
                    tgui::Label(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindLabel["getSharedRenderer"]
            = sol::overload(static_cast<gui::LabelRenderer* (tgui::Label::*)()>(
                                &tgui::Label::getSharedRenderer),
                static_cast<const gui::LabelRenderer* (tgui::Label::*)() const>(
                    &tgui::Label::getSharedRenderer));
        bindLabel["getRenderer"]
            = sol::overload(static_cast<gui::LabelRenderer* (tgui::Label::*)()>(
                                &tgui::Label::getRenderer),
                static_cast<const gui::LabelRenderer* (tgui::Label::*)() const>(
                    &tgui::Label::getRenderer));
        bindLabel["setSize"]
            = sol::overload(static_cast<void (tgui::Label::*)(const gui::Layout2d&)>(
                                &tgui::Label::setSize),
                static_cast<void (tgui::Label::*)(const gui::Layout2d&)>(
                    &tgui::Label::setSize),
                static_cast<void (tgui::Label::*)(gui::Layout, gui::Layout)>(
                    &tgui::Label::setSize));
        bindLabel["setText"] = &tgui::Label::setText;
        bindLabel["getText"] = &tgui::Label::getText;
        bindLabel["setTextSize"] = &tgui::Label::setTextSize;
        bindLabel["setHorizontalAlignment"] = &tgui::Label::setHorizontalAlignment;
        bindLabel["getHorizontalAlignment"] = &tgui::Label::getHorizontalAlignment;
        bindLabel["setVerticalAlignment"] = &tgui::Label::setVerticalAlignment;
        bindLabel["getVerticalAlignment"] = &tgui::Label::getVerticalAlignment;
        bindLabel["setScrollbarPolicy"] = &tgui::Label::setScrollbarPolicy;
        bindLabel["getScrollbarPolicy"] = &tgui::Label::getScrollbarPolicy;
        bindLabel["setAutoSize"] = &tgui::Label::setAutoSize;
        bindLabel["getAutoSize"] = &tgui::Label::getAutoSize;
        bindLabel["setMaximumTextWidth"] = &tgui::Label::setMaximumTextWidth;
        bindLabel["getMaximumTextWidth"] = &tgui::Label::getMaximumTextWidth;
        bindLabel["ignoreMouseEvents"] = sol::overload(
            [](tgui::Label* self) -> void { return self->ignoreMouseEvents(); },
            [](tgui::Label* self, bool ignore) -> void {
                return self->ignoreMouseEvents(ignore);
            });
        bindLabel["isIgnoringMouseEvents"] = &tgui::Label::isIgnoringMouseEvents;
        bindLabel["setParent"] = &tgui::Label::setParent;
        bindLabel["canGainFocus"] = &tgui::Label::canGainFocus;
        bindLabel["isMouseOnWidget"] = &tgui::Label::isMouseOnWidget;
        bindLabel["leftMousePressed"] = &tgui::Label::leftMousePressed;
        bindLabel["leftMouseReleased"] = &tgui::Label::leftMouseReleased;
        bindLabel["mouseMoved"] = &tgui::Label::mouseMoved;
        bindLabel["mouseWheelScrolled"] = &tgui::Label::mouseWheelScrolled;
        bindLabel["mouseNoLongerOnWidget"] = &tgui::Label::mouseNoLongerOnWidget;
        bindLabel["leftMouseButtonNoLongerDown"]
            = &tgui::Label::leftMouseButtonNoLongerDown;
        bindLabel["draw"] = &tgui::Label::draw;
        bindLabel["create"] = sol::overload(
            [](tgui::Label* self) -> gui::Label1aa0bc55780302197e337a6cda7f0e16df {
                return self->create();
            },
            [](tgui::Label* self,
                gui::String text) -> gui::Label1aa0bc55780302197e337a6cda7f0e16df {
                return self->create(text);
            });
        bindLabel["copy"] = &tgui::Label::copy;
        bindLabel["onDoubleClick"] = &tgui::Label::onDoubleClick;
    }
    void LoadClassLabelRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::LabelRenderer> bindLabelRenderer
            = tguiNamespace.new_usertype<tgui::LabelRenderer>("LabelRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindLabelRenderer["setBorders"] = &tgui::LabelRenderer::setBorders;
        bindLabelRenderer["getBorders"] = &tgui::LabelRenderer::getBorders;
        bindLabelRenderer["setPadding"] = &tgui::LabelRenderer::setPadding;
        bindLabelRenderer["getPadding"] = &tgui::LabelRenderer::getPadding;
        bindLabelRenderer["setTextColor"] = &tgui::LabelRenderer::setTextColor;
        bindLabelRenderer["getTextColor"] = &tgui::LabelRenderer::getTextColor;
        bindLabelRenderer["setBackgroundColor"]
            = &tgui::LabelRenderer::setBackgroundColor;
        bindLabelRenderer["getBackgroundColor"]
            = &tgui::LabelRenderer::getBackgroundColor;
        bindLabelRenderer["setBorderColor"] = &tgui::LabelRenderer::setBorderColor;
        bindLabelRenderer["getBorderColor"] = &tgui::LabelRenderer::getBorderColor;
        bindLabelRenderer["setTextStyle"] = &tgui::LabelRenderer::setTextStyle;
        bindLabelRenderer["getTextStyle"] = &tgui::LabelRenderer::getTextStyle;
        bindLabelRenderer["setTextOutlineColor"]
            = &tgui::LabelRenderer::setTextOutlineColor;
        bindLabelRenderer["getTextOutlineColor"]
            = &tgui::LabelRenderer::getTextOutlineColor;
        bindLabelRenderer["setTextOutlineThickness"]
            = &tgui::LabelRenderer::setTextOutlineThickness;
        bindLabelRenderer["getTextOutlineThickness"]
            = &tgui::LabelRenderer::getTextOutlineThickness;
        bindLabelRenderer["setTextureBackground"]
            = &tgui::LabelRenderer::setTextureBackground;
        bindLabelRenderer["getTextureBackground"]
            = &tgui::LabelRenderer::getTextureBackground;
        bindLabelRenderer["setScrollbar"] = &tgui::LabelRenderer::setScrollbar;
        bindLabelRenderer["getScrollbar"] = &tgui::LabelRenderer::getScrollbar;
        bindLabelRenderer["setScrollbarWidth"] = &tgui::LabelRenderer::setScrollbarWidth;
        bindLabelRenderer["getScrollbarWidth"] = &tgui::LabelRenderer::getScrollbarWidth;
        bindLabelRenderer["WidgetRenderer"] = sol::overload(
            static_cast<(tgui::LabelRenderer::*)()>(&tgui::LabelRenderer::WidgetRenderer),
            static_cast<(
                tgui::LabelRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                &tgui::LabelRenderer::WidgetRenderer));
    }
    void LoadClassLayout(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Layout> bindLayout = tguiNamespace.new_usertype<tgui::Layout>(
            "Layout", sol::call_constructor,
            sol::constructors<tgui::Layout(), tgui::Layout(T), tgui::Layout(const char*),
                tgui::Layout(gui::String),
                tgui::Layout(gui::Layout1a35bfb195a1f1e6fd4ed82b0568feb81b, gui::Widget*),
                tgui::Layout(gui::Layout1a35bfb195a1f1e6fd4ed82b0568feb81b,
                    std::unique_ptr<gui::Layout>, std::unique_ptr<gui::Layout>),
                tgui::Layout(const gui::Layout&), tgui::Layout(gui::Layout &&)>());
        bindLayout["operator="] = sol::overload(
            static_cast<gui::Layout& (tgui::Layout::*)(const gui::Layout&)>(
                &tgui::Layout::operator=),
            static_cast<gui::Layout& (tgui::Layout::*)(gui::Layout &&)>(
                &tgui::Layout::operator=));
        bindLayout["getValue"] = &tgui::Layout::getValue;
        bindLayout["isConstant"] = &tgui::Layout::isConstant;
        bindLayout["toString"] = &tgui::Layout::toString;
        bindLayout["connectWidget"] = &tgui::Layout::connectWidget;
        bindLayout["unbindWidget"] = &tgui::Layout::unbindWidget;
        bindLayout["recalculateValue"] = &tgui::Layout::recalculateValue;
    }
    void LoadClassLayout2d(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Layout2d> bindLayout2d
            = tguiNamespace.new_usertype<tgui::Layout2d>("Layout2d",
                sol::call_constructor,
                sol::constructors<tgui::Layout2d(), tgui::Layout2d(tgui::Vector2f),
                    tgui::Layout2d(gui::Layout, gui::Layout), tgui::Layout2d(const char*),
                    tgui::Layout2d(const gui::String&)>());
        bindLayout2d["getValue"] = &tgui::Layout2d::getValue;
        bindLayout2d["toString"] = &tgui::Layout2d::toString;
        bindLayout2d["x"] = &tgui::Layout2d::x;
        bindLayout2d["y"] = &tgui::Layout2d::y;
    }
    void LoadClassListBox(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ListBox> bindListBox
            = tguiNamespace.new_usertype<tgui::ListBox>("ListBox", sol::call_constructor,
                sol::constructors<tgui::ListBox(), tgui::ListBox(const char*),
                    tgui::ListBox(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindListBox["getSharedRenderer"]
            = sol::overload(static_cast<gui::ListBoxRenderer* (tgui::ListBox::*)()>(
                                &tgui::ListBox::getSharedRenderer),
                static_cast<const gui::ListBoxRenderer* (tgui::ListBox::*)() const>(
                    &tgui::ListBox::getSharedRenderer));
        bindListBox["getRenderer"]
            = sol::overload(static_cast<gui::ListBoxRenderer* (tgui::ListBox::*)()>(
                                &tgui::ListBox::getRenderer),
                static_cast<const gui::ListBoxRenderer* (tgui::ListBox::*)() const>(
                    &tgui::ListBox::getRenderer));
        bindListBox["setPosition"]
            = sol::overload(static_cast<void (tgui::ListBox::*)(const gui::Layout2d&)>(
                                &tgui::ListBox::setPosition),
                static_cast<void (tgui::ListBox::*)(const gui::Layout2d&)>(
                    &tgui::ListBox::setPosition),
                static_cast<void (tgui::ListBox::*)(gui::Layout, gui::Layout)>(
                    &tgui::ListBox::setPosition));
        bindListBox["setSize"]
            = sol::overload(static_cast<void (tgui::ListBox::*)(const gui::Layout2d&)>(
                                &tgui::ListBox::setSize),
                static_cast<void (tgui::ListBox::*)(const gui::Layout2d&)>(
                    &tgui::ListBox::setSize),
                static_cast<void (tgui::ListBox::*)(gui::Layout, gui::Layout)>(
                    &tgui::ListBox::setSize));
        bindListBox["addItem"] = sol::overload(
            [](tgui::ListBox* self, const gui::String& itemName) -> std::size_t {
                return self->addItem(itemName);
            },
            [](tgui::ListBox* self, const gui::String& itemName, const gui::String& id)
                -> std::size_t { return self->addItem(itemName, id); });
        bindListBox["setSelectedItem"] = &tgui::ListBox::setSelectedItem;
        bindListBox["setSelectedItemById"] = &tgui::ListBox::setSelectedItemById;
        bindListBox["setSelectedItemByIndex"] = &tgui::ListBox::setSelectedItemByIndex;
        bindListBox["deselectItem"] = &tgui::ListBox::deselectItem;
        bindListBox["removeItem"] = &tgui::ListBox::removeItem;
        bindListBox["removeItemById"] = &tgui::ListBox::removeItemById;
        bindListBox["removeItemByIndex"] = &tgui::ListBox::removeItemByIndex;
        bindListBox["removeAllItems"] = &tgui::ListBox::removeAllItems;
        bindListBox["getItemById"] = &tgui::ListBox::getItemById;
        bindListBox["getItemByIndex"] = &tgui::ListBox::getItemByIndex;
        bindListBox["getIndexById"] = &tgui::ListBox::getIndexById;
        bindListBox["getIdByIndex"] = &tgui::ListBox::getIdByIndex;
        bindListBox["getSelectedItem"] = &tgui::ListBox::getSelectedItem;
        bindListBox["getSelectedItemId"] = &tgui::ListBox::getSelectedItemId;
        bindListBox["getSelectedItemIndex"] = &tgui::ListBox::getSelectedItemIndex;
        bindListBox["changeItem"] = &tgui::ListBox::changeItem;
        bindListBox["changeItemById"] = &tgui::ListBox::changeItemById;
        bindListBox["changeItemByIndex"] = &tgui::ListBox::changeItemByIndex;
        bindListBox["getItemCount"] = &tgui::ListBox::getItemCount;
        bindListBox["getItems"] = &tgui::ListBox::getItems;
        bindListBox["getItemIds"] = &tgui::ListBox::getItemIds;
        bindListBox["setItemData"] = &tgui::ListBox::setItemData;
        bindListBox["setItemHeight"] = &tgui::ListBox::setItemHeight;
        bindListBox["getItemHeight"] = &tgui::ListBox::getItemHeight;
        bindListBox["setTextSize"] = &tgui::ListBox::setTextSize;
        bindListBox["setMaximumItems"] = sol::overload(
            [](tgui::ListBox* self) -> void { return self->setMaximumItems(); },
            [](tgui::ListBox* self, std::size_t maximumItems) -> void {
                return self->setMaximumItems(maximumItems);
            });
        bindListBox["getMaximumItems"] = &tgui::ListBox::getMaximumItems;
        bindListBox["setAutoScroll"] = &tgui::ListBox::setAutoScroll;
        bindListBox["getAutoScroll"] = &tgui::ListBox::getAutoScroll;
        bindListBox["contains"] = &tgui::ListBox::contains;
        bindListBox["containsId"] = &tgui::ListBox::containsId;
        bindListBox["setScrollbarValue"] = &tgui::ListBox::setScrollbarValue;
        bindListBox["getScrollbarValue"] = &tgui::ListBox::getScrollbarValue;
        bindListBox["isMouseOnWidget"] = &tgui::ListBox::isMouseOnWidget;
        bindListBox["leftMousePressed"] = &tgui::ListBox::leftMousePressed;
        bindListBox["leftMouseReleased"] = &tgui::ListBox::leftMouseReleased;
        bindListBox["mouseMoved"] = &tgui::ListBox::mouseMoved;
        bindListBox["mouseWheelScrolled"] = &tgui::ListBox::mouseWheelScrolled;
        bindListBox["mouseNoLongerOnWidget"] = &tgui::ListBox::mouseNoLongerOnWidget;
        bindListBox["leftMouseButtonNoLongerDown"]
            = &tgui::ListBox::leftMouseButtonNoLongerDown;
        bindListBox["keyPressed"] = &tgui::ListBox::keyPressed;
        bindListBox["draw"] = &tgui::ListBox::draw;
        bindListBox["create"] = &tgui::ListBox::create;
        bindListBox["copy"] = &tgui::ListBox::copy;
        bindListBox["onItemSelect"] = &tgui::ListBox::onItemSelect;
        bindListBox["onMousePress"] = &tgui::ListBox::onMousePress;
        bindListBox["onMouseRelease"] = &tgui::ListBox::onMouseRelease;
        bindListBox["onDoubleClick"] = &tgui::ListBox::onDoubleClick;
    }
    void LoadClassListBoxRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ListBoxRenderer> bindListBoxRenderer
            = tguiNamespace.new_usertype<tgui::ListBoxRenderer>("ListBoxRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindListBoxRenderer["setBorders"] = &tgui::ListBoxRenderer::setBorders;
        bindListBoxRenderer["getBorders"] = &tgui::ListBoxRenderer::getBorders;
        bindListBoxRenderer["setPadding"] = &tgui::ListBoxRenderer::setPadding;
        bindListBoxRenderer["getPadding"] = &tgui::ListBoxRenderer::getPadding;
        bindListBoxRenderer["setTextStyle"] = &tgui::ListBoxRenderer::setTextStyle;
        bindListBoxRenderer["getTextStyle"] = &tgui::ListBoxRenderer::getTextStyle;
        bindListBoxRenderer["setSelectedTextStyle"]
            = &tgui::ListBoxRenderer::setSelectedTextStyle;
        bindListBoxRenderer["getSelectedTextStyle"]
            = &tgui::ListBoxRenderer::getSelectedTextStyle;
        bindListBoxRenderer["setBackgroundColor"]
            = &tgui::ListBoxRenderer::setBackgroundColor;
        bindListBoxRenderer["getBackgroundColor"]
            = &tgui::ListBoxRenderer::getBackgroundColor;
        bindListBoxRenderer["setBackgroundColorHover"]
            = &tgui::ListBoxRenderer::setBackgroundColorHover;
        bindListBoxRenderer["getBackgroundColorHover"]
            = &tgui::ListBoxRenderer::getBackgroundColorHover;
        bindListBoxRenderer["setSelectedBackgroundColor"]
            = &tgui::ListBoxRenderer::setSelectedBackgroundColor;
        bindListBoxRenderer["getSelectedBackgroundColor"]
            = &tgui::ListBoxRenderer::getSelectedBackgroundColor;
        bindListBoxRenderer["setSelectedBackgroundColorHover"]
            = &tgui::ListBoxRenderer::setSelectedBackgroundColorHover;
        bindListBoxRenderer["getSelectedBackgroundColorHover"]
            = &tgui::ListBoxRenderer::getSelectedBackgroundColorHover;
        bindListBoxRenderer["setTextColor"] = &tgui::ListBoxRenderer::setTextColor;
        bindListBoxRenderer["getTextColor"] = &tgui::ListBoxRenderer::getTextColor;
        bindListBoxRenderer["setTextColorHover"]
            = &tgui::ListBoxRenderer::setTextColorHover;
        bindListBoxRenderer["getTextColorHover"]
            = &tgui::ListBoxRenderer::getTextColorHover;
        bindListBoxRenderer["setSelectedTextColor"]
            = &tgui::ListBoxRenderer::setSelectedTextColor;
        bindListBoxRenderer["getSelectedTextColor"]
            = &tgui::ListBoxRenderer::getSelectedTextColor;
        bindListBoxRenderer["setSelectedTextColorHover"]
            = &tgui::ListBoxRenderer::setSelectedTextColorHover;
        bindListBoxRenderer["getSelectedTextColorHover"]
            = &tgui::ListBoxRenderer::getSelectedTextColorHover;
        bindListBoxRenderer["setBorderColor"] = &tgui::ListBoxRenderer::setBorderColor;
        bindListBoxRenderer["getBorderColor"] = &tgui::ListBoxRenderer::getBorderColor;
        bindListBoxRenderer["setTextureBackground"]
            = &tgui::ListBoxRenderer::setTextureBackground;
        bindListBoxRenderer["getTextureBackground"]
            = &tgui::ListBoxRenderer::getTextureBackground;
        bindListBoxRenderer["setScrollbar"] = &tgui::ListBoxRenderer::setScrollbar;
        bindListBoxRenderer["getScrollbar"] = &tgui::ListBoxRenderer::getScrollbar;
        bindListBoxRenderer["setScrollbarWidth"]
            = &tgui::ListBoxRenderer::setScrollbarWidth;
        bindListBoxRenderer["getScrollbarWidth"]
            = &tgui::ListBoxRenderer::getScrollbarWidth;
        bindListBoxRenderer["WidgetRenderer"]
            = sol::overload(static_cast<(tgui::ListBoxRenderer::*)()>(
                                &tgui::ListBoxRenderer::WidgetRenderer),
                static_cast<(
                    tgui::ListBoxRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                    &tgui::ListBoxRenderer::WidgetRenderer));
    }
    void LoadClassListView(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ListView> bindListView
            = tguiNamespace.new_usertype<tgui::ListView>("ListView",
                sol::call_constructor,
                sol::constructors<tgui::ListView(), tgui::ListView(const char*),
                    tgui::ListView(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindListView["getSharedRenderer"]
            = sol::overload(static_cast<gui::ListViewRenderer* (tgui::ListView::*)()>(
                                &tgui::ListView::getSharedRenderer),
                static_cast<const gui::ListViewRenderer* (tgui::ListView::*)() const>(
                    &tgui::ListView::getSharedRenderer));
        bindListView["getRenderer"]
            = sol::overload(static_cast<gui::ListViewRenderer* (tgui::ListView::*)()>(
                                &tgui::ListView::getRenderer),
                static_cast<const gui::ListViewRenderer* (tgui::ListView::*)() const>(
                    &tgui::ListView::getRenderer));
        bindListView["setSize"]
            = sol::overload(static_cast<void (tgui::ListView::*)(const gui::Layout2d&)>(
                                &tgui::ListView::setSize),
                static_cast<void (tgui::ListView::*)(const gui::Layout2d&)>(
                    &tgui::ListView::setSize),
                static_cast<void (tgui::ListView::*)(gui::Layout, gui::Layout)>(
                    &tgui::ListView::setSize));
        bindListView["addColumn"] = sol::overload(
            [](tgui::ListView* self, const gui::String& text) -> std::size_t {
                return self->addColumn(text);
            },
            [](tgui::ListView* self, const gui::String& text,
                float width) -> std::size_t { return self->addColumn(text, width); },
            [](tgui::ListView* self, const gui::String& text, float width,
                gui::ListView1a878032fb53fdccdd0538d73a3038b41c alignment)
                -> std::size_t { return self->addColumn(text, width, alignment); });
        bindListView["setColumnText"] = &tgui::ListView::setColumnText;
        bindListView["getColumnText"] = &tgui::ListView::getColumnText;
        bindListView["setColumnWidth"] = &tgui::ListView::setColumnWidth;
        bindListView["getColumnWidth"] = &tgui::ListView::getColumnWidth;
        bindListView["setColumnAlignment"] = &tgui::ListView::setColumnAlignment;
        bindListView["getColumnAlignment"] = &tgui::ListView::getColumnAlignment;
        bindListView["removeAllColumns"] = &tgui::ListView::removeAllColumns;
        bindListView["getColumnCount"] = &tgui::ListView::getColumnCount;
        bindListView["setHeaderHeight"] = &tgui::ListView::setHeaderHeight;
        bindListView["getHeaderHeight"] = &tgui::ListView::getHeaderHeight;
        bindListView["getCurrentHeaderHeight"] = &tgui::ListView::getCurrentHeaderHeight;
        bindListView["setHeaderVisible"] = &tgui::ListView::setHeaderVisible;
        bindListView["getHeaderVisible"] = &tgui::ListView::getHeaderVisible;
        bindListView["addItem"] = sol::overload(
            static_cast<std::size_t (tgui::ListView::*)(const gui::String&)>(
                &tgui::ListView::addItem),
            static_cast<std::size_t (tgui::ListView::*)(const std::vector<gui::String>&)>(
                &tgui::ListView::addItem));
        bindListView["addMultipleItems"] = &tgui::ListView::addMultipleItems;
        bindListView["insertItem"] = sol::overload(
            static_cast<void (tgui::ListView::*)(std::size_t, const gui::String&)>(
                &tgui::ListView::insertItem),
            static_cast<void (tgui::ListView::*)(std::size_t,
                const std::vector<gui::String>&)>(&tgui::ListView::insertItem));
        bindListView["insertMultipleItems"] = &tgui::ListView::insertMultipleItems;
        bindListView["changeItem"] = &tgui::ListView::changeItem;
        bindListView["changeSubItem"] = &tgui::ListView::changeSubItem;
        bindListView["removeItem"] = &tgui::ListView::removeItem;
        bindListView["removeAllItems"] = &tgui::ListView::removeAllItems;
        bindListView["setSelectedItem"] = &tgui::ListView::setSelectedItem;
        bindListView["setSelectedItems"] = &tgui::ListView::setSelectedItems;
        bindListView["deselectItems"] = &tgui::ListView::deselectItems;
        bindListView["getSelectedItemIndex"] = &tgui::ListView::getSelectedItemIndex;
        bindListView["getSelectedItemIndices"] = &tgui::ListView::getSelectedItemIndices;
        bindListView["setMultiSelect"] = &tgui::ListView::setMultiSelect;
        bindListView["getMultiSelect"] = &tgui::ListView::getMultiSelect;
        bindListView["setItemData"] = &tgui::ListView::setItemData;
        bindListView["setItemIcon"] = &tgui::ListView::setItemIcon;
        bindListView["getItemIcon"] = &tgui::ListView::getItemIcon;
        bindListView["getItemCount"] = &tgui::ListView::getItemCount;
        bindListView["getItem"] = &tgui::ListView::getItem;
        bindListView["getItemRow"] = &tgui::ListView::getItemRow;
        bindListView["getItemCell"] = &tgui::ListView::getItemCell;
        bindListView["getItems"] = &tgui::ListView::getItems;
        bindListView["getItemRows"] = &tgui::ListView::getItemRows;
        bindListView["sort"] = &tgui::ListView::sort;
        bindListView["setItemHeight"] = &tgui::ListView::setItemHeight;
        bindListView["getItemHeight"] = &tgui::ListView::getItemHeight;
        bindListView["setTextSize"] = &tgui::ListView::setTextSize;
        bindListView["setHeaderTextSize"] = &tgui::ListView::setHeaderTextSize;
        bindListView["getHeaderTextSize"] = &tgui::ListView::getHeaderTextSize;
        bindListView["setSeparatorWidth"] = &tgui::ListView::setSeparatorWidth;
        bindListView["getSeparatorWidth"] = &tgui::ListView::getSeparatorWidth;
        bindListView["setHeaderSeparatorHeight"]
            = &tgui::ListView::setHeaderSeparatorHeight;
        bindListView["getHeaderSeparatorHeight"]
            = &tgui::ListView::getHeaderSeparatorHeight;
        bindListView["setGridLinesWidth"] = &tgui::ListView::setGridLinesWidth;
        bindListView["getGridLinesWidth"] = &tgui::ListView::getGridLinesWidth;
        bindListView["setAutoScroll"] = &tgui::ListView::setAutoScroll;
        bindListView["getAutoScroll"] = &tgui::ListView::getAutoScroll;
        bindListView["setShowVerticalGridLines"]
            = &tgui::ListView::setShowVerticalGridLines;
        bindListView["getShowVerticalGridLines"]
            = &tgui::ListView::getShowVerticalGridLines;
        bindListView["setShowHorizontalGridLines"]
            = &tgui::ListView::setShowHorizontalGridLines;
        bindListView["getShowHorizontalGridLines"]
            = &tgui::ListView::getShowHorizontalGridLines;
        bindListView["setExpandLastColumn"] = &tgui::ListView::setExpandLastColumn;
        bindListView["getExpandLastColumn"] = &tgui::ListView::getExpandLastColumn;
        bindListView["setVerticalScrollbarPolicy"]
            = &tgui::ListView::setVerticalScrollbarPolicy;
        bindListView["getVerticalScrollbarPolicy"]
            = &tgui::ListView::getVerticalScrollbarPolicy;
        bindListView["setHorizontalScrollbarPolicy"]
            = &tgui::ListView::setHorizontalScrollbarPolicy;
        bindListView["getHorizontalScrollbarPolicy"]
            = &tgui::ListView::getHorizontalScrollbarPolicy;
        bindListView["setVerticalScrollbarValue"]
            = &tgui::ListView::setVerticalScrollbarValue;
        bindListView["getVerticalScrollbarValue"]
            = &tgui::ListView::getVerticalScrollbarValue;
        bindListView["setHorizontalScrollbarValue"]
            = &tgui::ListView::setHorizontalScrollbarValue;
        bindListView["getHorizontalScrollbarValue"]
            = &tgui::ListView::getHorizontalScrollbarValue;
        bindListView["setFixedIconSize"] = &tgui::ListView::setFixedIconSize;
        bindListView["getFixedIconSize"] = &tgui::ListView::getFixedIconSize;
        bindListView["isMouseOnWidget"] = &tgui::ListView::isMouseOnWidget;
        bindListView["leftMousePressed"] = &tgui::ListView::leftMousePressed;
        bindListView["leftMouseReleased"] = &tgui::ListView::leftMouseReleased;
        bindListView["rightMousePressed"] = &tgui::ListView::rightMousePressed;
        bindListView["mouseMoved"] = &tgui::ListView::mouseMoved;
        bindListView["mouseWheelScrolled"] = &tgui::ListView::mouseWheelScrolled;
        bindListView["mouseNoLongerOnWidget"] = &tgui::ListView::mouseNoLongerOnWidget;
        bindListView["leftMouseButtonNoLongerDown"]
            = &tgui::ListView::leftMouseButtonNoLongerDown;
        bindListView["keyPressed"] = &tgui::ListView::keyPressed;
        bindListView["draw"] = &tgui::ListView::draw;
        bindListView["create"] = &tgui::ListView::create;
        bindListView["copy"] = &tgui::ListView::copy;
        bindListView["onItemSelect"] = &tgui::ListView::onItemSelect;
        bindListView["onDoubleClick"] = &tgui::ListView::onDoubleClick;
        bindListView["onRightClick"] = &tgui::ListView::onRightClick;
        bindListView["onHeaderClick"] = &tgui::ListView::onHeaderClick;
    }
    void LoadClassListViewRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ListViewRenderer> bindListViewRenderer
            = tguiNamespace.new_usertype<tgui::ListViewRenderer>("ListViewRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindListViewRenderer["setBorders"] = &tgui::ListViewRenderer::setBorders;
        bindListViewRenderer["getBorders"] = &tgui::ListViewRenderer::getBorders;
        bindListViewRenderer["setPadding"] = &tgui::ListViewRenderer::setPadding;
        bindListViewRenderer["getPadding"] = &tgui::ListViewRenderer::getPadding;
        bindListViewRenderer["setBackgroundColor"]
            = &tgui::ListViewRenderer::setBackgroundColor;
        bindListViewRenderer["getBackgroundColor"]
            = &tgui::ListViewRenderer::getBackgroundColor;
        bindListViewRenderer["setBackgroundColorHover"]
            = &tgui::ListViewRenderer::setBackgroundColorHover;
        bindListViewRenderer["getBackgroundColorHover"]
            = &tgui::ListViewRenderer::getBackgroundColorHover;
        bindListViewRenderer["setSelectedBackgroundColor"]
            = &tgui::ListViewRenderer::setSelectedBackgroundColor;
        bindListViewRenderer["getSelectedBackgroundColor"]
            = &tgui::ListViewRenderer::getSelectedBackgroundColor;
        bindListViewRenderer["setSelectedBackgroundColorHover"]
            = &tgui::ListViewRenderer::setSelectedBackgroundColorHover;
        bindListViewRenderer["getSelectedBackgroundColorHover"]
            = &tgui::ListViewRenderer::getSelectedBackgroundColorHover;
        bindListViewRenderer["setTextColor"] = &tgui::ListViewRenderer::setTextColor;
        bindListViewRenderer["getTextColor"] = &tgui::ListViewRenderer::getTextColor;
        bindListViewRenderer["setTextColorHover"]
            = &tgui::ListViewRenderer::setTextColorHover;
        bindListViewRenderer["getTextColorHover"]
            = &tgui::ListViewRenderer::getTextColorHover;
        bindListViewRenderer["setSelectedTextColor"]
            = &tgui::ListViewRenderer::setSelectedTextColor;
        bindListViewRenderer["getSelectedTextColor"]
            = &tgui::ListViewRenderer::getSelectedTextColor;
        bindListViewRenderer["setSelectedTextColorHover"]
            = &tgui::ListViewRenderer::setSelectedTextColorHover;
        bindListViewRenderer["getSelectedTextColorHover"]
            = &tgui::ListViewRenderer::getSelectedTextColorHover;
        bindListViewRenderer["setHeaderBackgroundColor"]
            = &tgui::ListViewRenderer::setHeaderBackgroundColor;
        bindListViewRenderer["getHeaderBackgroundColor"]
            = &tgui::ListViewRenderer::getHeaderBackgroundColor;
        bindListViewRenderer["setHeaderTextColor"]
            = &tgui::ListViewRenderer::setHeaderTextColor;
        bindListViewRenderer["getHeaderTextColor"]
            = &tgui::ListViewRenderer::getHeaderTextColor;
        bindListViewRenderer["setBorderColor"] = &tgui::ListViewRenderer::setBorderColor;
        bindListViewRenderer["getBorderColor"] = &tgui::ListViewRenderer::getBorderColor;
        bindListViewRenderer["setSeparatorColor"]
            = &tgui::ListViewRenderer::setSeparatorColor;
        bindListViewRenderer["getSeparatorColor"]
            = &tgui::ListViewRenderer::getSeparatorColor;
        bindListViewRenderer["setGridLinesColor"]
            = &tgui::ListViewRenderer::setGridLinesColor;
        bindListViewRenderer["getGridLinesColor"]
            = &tgui::ListViewRenderer::getGridLinesColor;
        bindListViewRenderer["setScrollbar"] = &tgui::ListViewRenderer::setScrollbar;
        bindListViewRenderer["getScrollbar"] = &tgui::ListViewRenderer::getScrollbar;
        bindListViewRenderer["setScrollbarWidth"]
            = &tgui::ListViewRenderer::setScrollbarWidth;
        bindListViewRenderer["getScrollbarWidth"]
            = &tgui::ListViewRenderer::getScrollbarWidth;
        bindListViewRenderer["WidgetRenderer"] = sol::overload(
            static_cast<(tgui::ListViewRenderer::*)()>(
                &tgui::ListViewRenderer::WidgetRenderer),
            static_cast<(
                tgui::ListViewRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                &tgui::ListViewRenderer::WidgetRenderer));
    }
    void LoadClassMenuBar(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::MenuBar> bindMenuBar
            = tguiNamespace.new_usertype<tgui::MenuBar>("MenuBar", sol::call_constructor,
                sol::constructors<tgui::MenuBar(), tgui::MenuBar(const char*),
                    tgui::MenuBar(const char*, bool), tgui::MenuBar(const gui::MenuBar&),
                    tgui::MenuBar(gui::MenuBar &&)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindMenuBar["operator="] = sol::overload(
            static_cast<gui::MenuBar& (tgui::MenuBar::*)(const gui::MenuBar&)>(
                &tgui::MenuBar::operator=),
            static_cast<gui::MenuBar& (tgui::MenuBar::*)(gui::MenuBar &&)>(
                &tgui::MenuBar::operator=));
        bindMenuBar["getSharedRenderer"]
            = sol::overload(static_cast<gui::MenuBarRenderer* (tgui::MenuBar::*)()>(
                                &tgui::MenuBar::getSharedRenderer),
                static_cast<const gui::MenuBarRenderer* (tgui::MenuBar::*)() const>(
                    &tgui::MenuBar::getSharedRenderer));
        bindMenuBar["getRenderer"]
            = sol::overload(static_cast<gui::MenuBarRenderer* (tgui::MenuBar::*)()>(
                                &tgui::MenuBar::getRenderer),
                static_cast<const gui::MenuBarRenderer* (tgui::MenuBar::*)() const>(
                    &tgui::MenuBar::getRenderer));
        bindMenuBar["setSize"]
            = sol::overload(static_cast<void (tgui::MenuBar::*)(const gui::Layout2d&)>(
                                &tgui::MenuBar::setSize),
                static_cast<void (tgui::MenuBar::*)(const gui::Layout2d&)>(
                    &tgui::MenuBar::setSize),
                static_cast<void (tgui::MenuBar::*)(gui::Layout, gui::Layout)>(
                    &tgui::MenuBar::setSize));
        bindMenuBar["setEnabled"] = &tgui::MenuBar::setEnabled;
        bindMenuBar["addMenu"] = &tgui::MenuBar::addMenu;
        bindMenuBar["addMenuItem"] = sol::overload(
            static_cast<bool (tgui::MenuBar::*)(const gui::String&)>(
                &tgui::MenuBar::addMenuItem),
            static_cast<bool (tgui::MenuBar::*)(const gui::String&, const gui::String&)>(
                &tgui::MenuBar::addMenuItem),
            static_cast<bool (tgui::MenuBar::*)(const std::vector<gui::String>&, bool)>(
                &tgui::MenuBar::addMenuItem));
        bindMenuBar["removeAllMenus"] = &tgui::MenuBar::removeAllMenus;
        bindMenuBar["removeMenu"] = &tgui::MenuBar::removeMenu;
        bindMenuBar["removeMenuItem"] = sol::overload(
            static_cast<bool (tgui::MenuBar::*)(const gui::String&, const gui::String&)>(
                &tgui::MenuBar::removeMenuItem),
            static_cast<bool (tgui::MenuBar::*)(const std::vector<gui::String>&, bool)>(
                &tgui::MenuBar::removeMenuItem));
        bindMenuBar["removeMenuItems"] = &tgui::MenuBar::removeMenuItems;
        bindMenuBar["removeSubMenuItems"] = &tgui::MenuBar::removeSubMenuItems;
        bindMenuBar["setMenuEnabled"] = &tgui::MenuBar::setMenuEnabled;
        bindMenuBar["getMenuEnabled"] = &tgui::MenuBar::getMenuEnabled;
        bindMenuBar["setMenuItemEnabled"] = sol::overload(
            static_cast<bool (tgui::MenuBar::*)(const gui::String&, const gui::String&,
                bool)>(&tgui::MenuBar::setMenuItemEnabled),
            static_cast<bool (tgui::MenuBar::*)(const std::vector<gui::String>&, bool)>(
                &tgui::MenuBar::setMenuItemEnabled));
        bindMenuBar["getMenuItemEnabled"] = sol::overload(
            static_cast<bool (tgui::MenuBar::*)(const gui::String&, const gui::String&)
                    const>(&tgui::MenuBar::getMenuItemEnabled),
            static_cast<bool (tgui::MenuBar::*)(const std::vector<gui::String>&) const>(
                &tgui::MenuBar::getMenuItemEnabled));
        bindMenuBar["setTextSize"] = &tgui::MenuBar::setTextSize;
        bindMenuBar["setMinimumSubMenuWidth"] = &tgui::MenuBar::setMinimumSubMenuWidth;
        bindMenuBar["getMinimumSubMenuWidth"] = &tgui::MenuBar::getMinimumSubMenuWidth;
        bindMenuBar["setInvertedMenuDirection"]
            = &tgui::MenuBar::setInvertedMenuDirection;
        bindMenuBar["getInvertedMenuDirection"]
            = &tgui::MenuBar::getInvertedMenuDirection;
        bindMenuBar["getMenus"] = &tgui::MenuBar::getMenus;
        bindMenuBar["closeMenu"] = &tgui::MenuBar::closeMenu;
        bindMenuBar["isMouseOnWidget"] = &tgui::MenuBar::isMouseOnWidget;
        bindMenuBar["leftMousePressed"] = &tgui::MenuBar::leftMousePressed;
        bindMenuBar["leftMouseReleased"] = &tgui::MenuBar::leftMouseReleased;
        bindMenuBar["mouseMoved"] = &tgui::MenuBar::mouseMoved;
        bindMenuBar["draw"] = &tgui::MenuBar::draw;
        bindMenuBar["create"] = &tgui::MenuBar::create;
        bindMenuBar["copy"] = &tgui::MenuBar::copy;
        bindMenuBar["onMenuItemClick"] = &tgui::MenuBar::onMenuItemClick;
    }
    void LoadClassMenuBarMenuPlaceholder(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::MenuBarMenuPlaceholder> bindMenuBarMenuPlaceholder
            = tguiNamespace.new_usertype<tgui::MenuBarMenuPlaceholder>(
                "MenuBarMenuPlaceholder", sol::call_constructor,
                sol::constructors<tgui::MenuBarMenuPlaceholder(
                                      const gui::MenuBarMenuPlaceholder&),
                    tgui::MenuBarMenuPlaceholder(gui::MenuBar*)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindMenuBarMenuPlaceholder["operator="]
            = &tgui::MenuBarMenuPlaceholder::operator=;
        bindMenuBarMenuPlaceholder["getFullSize"]
            = &tgui::MenuBarMenuPlaceholder::getFullSize;
        bindMenuBarMenuPlaceholder["getWidgetOffset"]
            = &tgui::MenuBarMenuPlaceholder::getWidgetOffset;
        bindMenuBarMenuPlaceholder["isMouseOnWidget"]
            = &tgui::MenuBarMenuPlaceholder::isMouseOnWidget;
        bindMenuBarMenuPlaceholder["draw"] = &tgui::MenuBarMenuPlaceholder::draw;
        bindMenuBarMenuPlaceholder["leftMouseButtonNoLongerDown"]
            = &tgui::MenuBarMenuPlaceholder::leftMouseButtonNoLongerDown;
        bindMenuBarMenuPlaceholder["mouseMoved"]
            = &tgui::MenuBarMenuPlaceholder::mouseMoved;
        bindMenuBarMenuPlaceholder["clone"] = &tgui::MenuBarMenuPlaceholder::clone;
    }
    void LoadClassMenuBarRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::MenuBarRenderer> bindMenuBarRenderer
            = tguiNamespace.new_usertype<tgui::MenuBarRenderer>("MenuBarRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindMenuBarRenderer["setBackgroundColor"]
            = &tgui::MenuBarRenderer::setBackgroundColor;
        bindMenuBarRenderer["getBackgroundColor"]
            = &tgui::MenuBarRenderer::getBackgroundColor;
        bindMenuBarRenderer["setSelectedBackgroundColor"]
            = &tgui::MenuBarRenderer::setSelectedBackgroundColor;
        bindMenuBarRenderer["getSelectedBackgroundColor"]
            = &tgui::MenuBarRenderer::getSelectedBackgroundColor;
        bindMenuBarRenderer["setTextColor"] = &tgui::MenuBarRenderer::setTextColor;
        bindMenuBarRenderer["getTextColor"] = &tgui::MenuBarRenderer::getTextColor;
        bindMenuBarRenderer["setSelectedTextColor"]
            = &tgui::MenuBarRenderer::setSelectedTextColor;
        bindMenuBarRenderer["getSelectedTextColor"]
            = &tgui::MenuBarRenderer::getSelectedTextColor;
        bindMenuBarRenderer["setTextColorDisabled"]
            = &tgui::MenuBarRenderer::setTextColorDisabled;
        bindMenuBarRenderer["getTextColorDisabled"]
            = &tgui::MenuBarRenderer::getTextColorDisabled;
        bindMenuBarRenderer["setSeparatorColor"]
            = &tgui::MenuBarRenderer::setSeparatorColor;
        bindMenuBarRenderer["getSeparatorColor"]
            = &tgui::MenuBarRenderer::getSeparatorColor;
        bindMenuBarRenderer["setTextureBackground"]
            = &tgui::MenuBarRenderer::setTextureBackground;
        bindMenuBarRenderer["getTextureBackground"]
            = &tgui::MenuBarRenderer::getTextureBackground;
        bindMenuBarRenderer["setTextureItemBackground"]
            = &tgui::MenuBarRenderer::setTextureItemBackground;
        bindMenuBarRenderer["getTextureItemBackground"]
            = &tgui::MenuBarRenderer::getTextureItemBackground;
        bindMenuBarRenderer["setTextureSelectedItemBackground"]
            = &tgui::MenuBarRenderer::setTextureSelectedItemBackground;
        bindMenuBarRenderer["getTextureSelectedItemBackground"]
            = &tgui::MenuBarRenderer::getTextureSelectedItemBackground;
        bindMenuBarRenderer["setDistanceToSide"]
            = &tgui::MenuBarRenderer::setDistanceToSide;
        bindMenuBarRenderer["getDistanceToSide"]
            = &tgui::MenuBarRenderer::getDistanceToSide;
        bindMenuBarRenderer["setSeparatorThickness"]
            = &tgui::MenuBarRenderer::setSeparatorThickness;
        bindMenuBarRenderer["getSeparatorThickness"]
            = &tgui::MenuBarRenderer::getSeparatorThickness;
        bindMenuBarRenderer["setSeparatorVerticalPadding"]
            = &tgui::MenuBarRenderer::setSeparatorVerticalPadding;
        bindMenuBarRenderer["getSeparatorVerticalPadding"]
            = &tgui::MenuBarRenderer::getSeparatorVerticalPadding;
        bindMenuBarRenderer["setSeparatorSidePadding"]
            = &tgui::MenuBarRenderer::setSeparatorSidePadding;
        bindMenuBarRenderer["getSeparatorSidePadding"]
            = &tgui::MenuBarRenderer::getSeparatorSidePadding;
        bindMenuBarRenderer["WidgetRenderer"]
            = sol::overload(static_cast<(tgui::MenuBarRenderer::*)()>(
                                &tgui::MenuBarRenderer::WidgetRenderer),
                static_cast<(
                    tgui::MenuBarRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                    &tgui::MenuBarRenderer::WidgetRenderer));
    }
    void LoadClassMessageBox(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::MessageBox> bindMessageBox
            = tguiNamespace.new_usertype<tgui::MessageBox>("MessageBox",
                sol::call_constructor,
                sol::constructors<tgui::MessageBox(), tgui::MessageBox(const char*),
                    tgui::MessageBox(const char*, bool),
                    tgui::MessageBox(const gui::MessageBox&),
                    tgui::MessageBox(gui::MessageBox &&)>(),
                sol::base_classes,
                sol::bases<tgui::ChildWindow, tgui::Container, tgui::Widget>());
        bindMessageBox["operator="] = sol::overload(
            static_cast<gui::MessageBox& (tgui::MessageBox::*)(const gui::MessageBox&)>(
                &tgui::MessageBox::operator=),
            static_cast<gui::MessageBox& (tgui::MessageBox::*)(gui::MessageBox &&)>(
                &tgui::MessageBox::operator=));
        bindMessageBox["getSharedRenderer"]
            = sol::overload(static_cast<gui::MessageBoxRenderer* (tgui::MessageBox::*)()>(
                                &tgui::MessageBox::getSharedRenderer),
                static_cast<const gui::MessageBoxRenderer* (tgui::MessageBox::*)() const>(
                    &tgui::MessageBox::getSharedRenderer));
        bindMessageBox["getRenderer"]
            = sol::overload(static_cast<gui::MessageBoxRenderer* (tgui::MessageBox::*)()>(
                                &tgui::MessageBox::getRenderer),
                static_cast<const gui::MessageBoxRenderer* (tgui::MessageBox::*)() const>(
                    &tgui::MessageBox::getRenderer));
        bindMessageBox["setText"] = &tgui::MessageBox::setText;
        bindMessageBox["getText"] = &tgui::MessageBox::getText;
        bindMessageBox["setTextSize"] = &tgui::MessageBox::setTextSize;
        bindMessageBox["addButton"] = &tgui::MessageBox::addButton;
        bindMessageBox["getButtons"] = &tgui::MessageBox::getButtons;
        bindMessageBox["create"] = sol::overload(
            [](tgui::MessageBox* self)
                -> gui::MessageBox1ab606d30a516d42437d51872ce3bc0a78 {
                return self->create();
            },
            [](tgui::MessageBox* self,
                gui::String title) -> gui::MessageBox1ab606d30a516d42437d51872ce3bc0a78 {
                return self->create(title);
            },
            [](tgui::MessageBox* self, gui::String title,
                gui::String text) -> gui::MessageBox1ab606d30a516d42437d51872ce3bc0a78 {
                return self->create(title, text);
            },
            [](tgui::MessageBox* self, gui::String title, gui::String text,
                std::vector<gui::String> buttons)
                -> gui::MessageBox1ab606d30a516d42437d51872ce3bc0a78 {
                return self->create(title, text, buttons);
            });
        bindMessageBox["copy"] = &tgui::MessageBox::copy;
        bindMessageBox["onButtonPress"] = &tgui::MessageBox::onButtonPress;
    }
    void LoadClassMessageBoxRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::MessageBoxRenderer> bindMessageBoxRenderer
            = tguiNamespace.new_usertype<tgui::MessageBoxRenderer>("MessageBoxRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::ChildWindowRenderer, tgui::WidgetRenderer>());
        bindMessageBoxRenderer["setTextColor"] = &tgui::MessageBoxRenderer::setTextColor;
        bindMessageBoxRenderer["getTextColor"] = &tgui::MessageBoxRenderer::getTextColor;
        bindMessageBoxRenderer["setButton"] = &tgui::MessageBoxRenderer::setButton;
        bindMessageBoxRenderer["getButton"] = &tgui::MessageBoxRenderer::getButton;
    }
    void LoadClassObjectConverter(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ObjectConverter> bindObjectConverter
            = tguiNamespace.new_usertype<tgui::ObjectConverter>("ObjectConverter",
                sol::call_constructor,
                sol::constructors<tgui::ObjectConverter(),
                    tgui::ObjectConverter(const char*),
                    tgui::ObjectConverter(const gui::String&),
                    tgui::ObjectConverter(gui::Font), tgui::ObjectConverter(gui::Color),
                    tgui::ObjectConverter(bool), tgui::ObjectConverter(T),
                    tgui::ObjectConverter(const gui::Outline&),
                    tgui::ObjectConverter(const gui::Texture&),
                    tgui::ObjectConverter(tgui::TextStyle),
                    tgui::ObjectConverter(gui::TextStyles),
                    tgui::ObjectConverter(std::shared_ptr<gui::RendererData>)>());
        bindObjectConverter["getString"] = &tgui::ObjectConverter::getString;
        bindObjectConverter["getFont"] = &tgui::ObjectConverter::getFont;
        bindObjectConverter["getColor"] = &tgui::ObjectConverter::getColor;
        bindObjectConverter["getOutline"] = &tgui::ObjectConverter::getOutline;
        bindObjectConverter["getBool"] = &tgui::ObjectConverter::getBool;
        bindObjectConverter["getNumber"] = &tgui::ObjectConverter::getNumber;
        bindObjectConverter["getTexture"] = &tgui::ObjectConverter::getTexture;
        bindObjectConverter["getTextStyle"] = &tgui::ObjectConverter::getTextStyle;
        bindObjectConverter["getRenderer"] = &tgui::ObjectConverter::getRenderer;
        bindObjectConverter["getType"] = &tgui::ObjectConverter::getType;
        bindObjectConverter[sol::meta_function::equal_to]
            = &tgui::ObjectConverter::operator==;
    }
    void LoadClassOutline(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Outline> bindOutline = tguiNamespace.new_usertype<
            tgui::Outline>("Outline", sol::call_constructor,
            sol::constructors<tgui::Outline(),
                tgui::Outline(gui::AbsoluteOrRelativeValue), tgui::Outline(T),
                tgui::Outline(gui::AbsoluteOrRelativeValue, gui::AbsoluteOrRelativeValue),
                tgui::Outline(gui::AbsoluteOrRelativeValue, gui::AbsoluteOrRelativeValue,
                    gui::AbsoluteOrRelativeValue, gui::AbsoluteOrRelativeValue)>());
        bindOutline["getLeft"] = &tgui::Outline::getLeft;
        bindOutline["getTop"] = &tgui::Outline::getTop;
        bindOutline["getRight"] = &tgui::Outline::getRight;
        bindOutline["getBottom"] = &tgui::Outline::getBottom;
        bindOutline["getOffset"] = &tgui::Outline::getOffset;
        bindOutline[sol::meta_function::equal_to] = &tgui::Outline::operator==;
        bindOutline[sol::meta_function::addition] = &tgui::Outline::operator+;
        bindOutline[sol::meta_function::subtraction] = &tgui::Outline::operator-;
        bindOutline["updateParentSize"] = &tgui::Outline::updateParentSize;
        bindOutline["toString"] = &tgui::Outline::toString;
    }
    void LoadClassPanel(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Panel> bindPanel = tguiNamespace.new_usertype<tgui::Panel>(
            "Panel", sol::call_constructor,
            sol::constructors<tgui::Panel(), tgui::Panel(const char*),
                tgui::Panel(const char*, bool)>(),
            sol::base_classes, sol::bases<tgui::Group, tgui::Container, tgui::Widget>());
        bindPanel["getSharedRenderer"]
            = sol::overload(static_cast<gui::PanelRenderer* (tgui::Panel::*)()>(
                                &tgui::Panel::getSharedRenderer),
                static_cast<const gui::PanelRenderer* (tgui::Panel::*)() const>(
                    &tgui::Panel::getSharedRenderer));
        bindPanel["getRenderer"]
            = sol::overload(static_cast<gui::PanelRenderer* (tgui::Panel::*)()>(
                                &tgui::Panel::getRenderer),
                static_cast<const gui::PanelRenderer* (tgui::Panel::*)() const>(
                    &tgui::Panel::getRenderer));
        bindPanel["setSize"]
            = sol::overload(static_cast<void (tgui::Panel::*)(const gui::Layout2d&)>(
                                &tgui::Panel::setSize),
                static_cast<void (tgui::Panel::*)(const gui::Layout2d&)>(
                    &tgui::Panel::setSize),
                static_cast<void (tgui::Panel::*)(gui::Layout, gui::Layout)>(
                    &tgui::Panel::setSize));
        bindPanel["getInnerSize"] = &tgui::Panel::getInnerSize;
        bindPanel["getChildWidgetsOffset"] = &tgui::Panel::getChildWidgetsOffset;
        bindPanel["isMouseOnWidget"] = &tgui::Panel::isMouseOnWidget;
        bindPanel["leftMousePressed"] = &tgui::Panel::leftMousePressed;
        bindPanel["leftMouseReleased"] = &tgui::Panel::leftMouseReleased;
        bindPanel["rightMousePressed"] = &tgui::Panel::rightMousePressed;
        bindPanel["rightMouseReleased"] = &tgui::Panel::rightMouseReleased;
        bindPanel["rightMouseButtonNoLongerDown"]
            = &tgui::Panel::rightMouseButtonNoLongerDown;
        bindPanel["draw"] = &tgui::Panel::draw;
        bindPanel["create"] = sol::overload(
            [](tgui::Panel* self) -> gui::Panel1a34b136a7d90420e28a8f4aa66a58f9d0 {
                return self->create();
            },
            [](tgui::Panel* self,
                gui::Layout2d size) -> gui::Panel1a34b136a7d90420e28a8f4aa66a58f9d0 {
                return self->create(size);
            });
        bindPanel["copy"] = &tgui::Panel::copy;
        bindPanel["onMousePress"] = &tgui::Panel::onMousePress;
        bindPanel["onMouseRelease"] = &tgui::Panel::onMouseRelease;
        bindPanel["onClick"] = &tgui::Panel::onClick;
        bindPanel["onDoubleClick"] = &tgui::Panel::onDoubleClick;
        bindPanel["onRightMousePress"] = &tgui::Panel::onRightMousePress;
        bindPanel["onRightMouseRelease"] = &tgui::Panel::onRightMouseRelease;
        bindPanel["onRightClick"] = &tgui::Panel::onRightClick;
    }
    void LoadClassPanelRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::PanelRenderer> bindPanelRenderer
            = tguiNamespace.new_usertype<tgui::PanelRenderer>("PanelRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::GroupRenderer, tgui::WidgetRenderer>());
        bindPanelRenderer["setBorders"] = &tgui::PanelRenderer::setBorders;
        bindPanelRenderer["getBorders"] = &tgui::PanelRenderer::getBorders;
        bindPanelRenderer["setBorderColor"] = &tgui::PanelRenderer::setBorderColor;
        bindPanelRenderer["getBorderColor"] = &tgui::PanelRenderer::getBorderColor;
        bindPanelRenderer["setBackgroundColor"]
            = &tgui::PanelRenderer::setBackgroundColor;
        bindPanelRenderer["getBackgroundColor"]
            = &tgui::PanelRenderer::getBackgroundColor;
        bindPanelRenderer["setTextureBackground"]
            = &tgui::PanelRenderer::setTextureBackground;
        bindPanelRenderer["getTextureBackground"]
            = &tgui::PanelRenderer::getTextureBackground;
    }
    void LoadClassPicture(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Picture> bindPicture
            = tguiNamespace.new_usertype<tgui::Picture>("Picture", sol::call_constructor,
                sol::constructors<tgui::Picture(), tgui::Picture(const char*),
                    tgui::Picture(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindPicture["getSharedRenderer"]
            = sol::overload(static_cast<gui::PictureRenderer* (tgui::Picture::*)()>(
                                &tgui::Picture::getSharedRenderer),
                static_cast<const gui::PictureRenderer* (tgui::Picture::*)() const>(
                    &tgui::Picture::getSharedRenderer));
        bindPicture["getRenderer"]
            = sol::overload(static_cast<gui::PictureRenderer* (tgui::Picture::*)()>(
                                &tgui::Picture::getRenderer),
                static_cast<const gui::PictureRenderer* (tgui::Picture::*)() const>(
                    &tgui::Picture::getRenderer));
        bindPicture["setSize"]
            = sol::overload(static_cast<void (tgui::Picture::*)(const gui::Layout2d&)>(
                                &tgui::Picture::setSize),
                static_cast<void (tgui::Picture::*)(const gui::Layout2d&)>(
                    &tgui::Picture::setSize),
                static_cast<void (tgui::Picture::*)(gui::Layout, gui::Layout)>(
                    &tgui::Picture::setSize));
        bindPicture["ignoreMouseEvents"] = sol::overload(
            [](tgui::Picture* self) -> void { return self->ignoreMouseEvents(); },
            [](tgui::Picture* self, bool ignore) -> void {
                return self->ignoreMouseEvents(ignore);
            });
        bindPicture["isIgnoringMouseEvents"] = &tgui::Picture::isIgnoringMouseEvents;
        bindPicture["canGainFocus"] = &tgui::Picture::canGainFocus;
        bindPicture["isMouseOnWidget"] = &tgui::Picture::isMouseOnWidget;
        bindPicture["leftMouseReleased"] = &tgui::Picture::leftMouseReleased;
        bindPicture["draw"] = &tgui::Picture::draw;
        bindPicture["create"] = sol::overload(
            static_cast<gui::Picture1a60a2176f42504c8afc34e278b39d781b (*)()>(
                &tgui::Picture::create),
            static_cast<gui::Picture1a60a2176f42504c8afc34e278b39d781b (*)(
                const gui::Texture&, bool)>(&tgui::Picture::create));
        bindPicture["copy"] = &tgui::Picture::copy;
        bindPicture["onDoubleClick"] = &tgui::Picture::onDoubleClick;
    }
    void LoadClassPictureRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::PictureRenderer> bindPictureRenderer
            = tguiNamespace.new_usertype<tgui::PictureRenderer>("PictureRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindPictureRenderer["setTexture"] = &tgui::PictureRenderer::setTexture;
        bindPictureRenderer["getTexture"] = &tgui::PictureRenderer::getTexture;
        bindPictureRenderer["WidgetRenderer"]
            = sol::overload(static_cast<(tgui::PictureRenderer::*)()>(
                                &tgui::PictureRenderer::WidgetRenderer),
                static_cast<(
                    tgui::PictureRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                    &tgui::PictureRenderer::WidgetRenderer));
    }
    void LoadClassProgressBar(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ProgressBar> bindProgressBar
            = tguiNamespace.new_usertype<tgui::ProgressBar>("ProgressBar",
                sol::call_constructor,
                sol::constructors<tgui::ProgressBar(), tgui::ProgressBar(const char*),
                    tgui::ProgressBar(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindProgressBar["getSharedRenderer"] = sol::overload(
            static_cast<gui::ProgressBarRenderer* (tgui::ProgressBar::*)()>(
                &tgui::ProgressBar::getSharedRenderer),
            static_cast<const gui::ProgressBarRenderer* (tgui::ProgressBar::*)() const>(
                &tgui::ProgressBar::getSharedRenderer));
        bindProgressBar["getRenderer"] = sol::overload(
            static_cast<gui::ProgressBarRenderer* (tgui::ProgressBar::*)()>(
                &tgui::ProgressBar::getRenderer),
            static_cast<const gui::ProgressBarRenderer* (tgui::ProgressBar::*)() const>(
                &tgui::ProgressBar::getRenderer));
        bindProgressBar["setSize"] = sol::overload(
            static_cast<void (tgui::ProgressBar::*)(const gui::Layout2d&)>(
                &tgui::ProgressBar::setSize),
            static_cast<void (tgui::ProgressBar::*)(const gui::Layout2d&)>(
                &tgui::ProgressBar::setSize),
            static_cast<void (tgui::ProgressBar::*)(gui::Layout, gui::Layout)>(
                &tgui::ProgressBar::setSize));
        bindProgressBar["setMinimum"] = &tgui::ProgressBar::setMinimum;
        bindProgressBar["getMinimum"] = &tgui::ProgressBar::getMinimum;
        bindProgressBar["setMaximum"] = &tgui::ProgressBar::setMaximum;
        bindProgressBar["getMaximum"] = &tgui::ProgressBar::getMaximum;
        bindProgressBar["setValue"] = &tgui::ProgressBar::setValue;
        bindProgressBar["getValue"] = &tgui::ProgressBar::getValue;
        bindProgressBar["incrementValue"] = &tgui::ProgressBar::incrementValue;
        bindProgressBar["setText"] = &tgui::ProgressBar::setText;
        bindProgressBar["getText"] = &tgui::ProgressBar::getText;
        bindProgressBar["setTextSize"] = &tgui::ProgressBar::setTextSize;
        bindProgressBar["getTextSize"] = &tgui::ProgressBar::getTextSize;
        bindProgressBar["setFillDirection"] = &tgui::ProgressBar::setFillDirection;
        bindProgressBar["getFillDirection"] = &tgui::ProgressBar::getFillDirection;
        bindProgressBar["isMouseOnWidget"] = &tgui::ProgressBar::isMouseOnWidget;
        bindProgressBar["draw"] = &tgui::ProgressBar::draw;
        bindProgressBar["create"] = &tgui::ProgressBar::create;
        bindProgressBar["copy"] = &tgui::ProgressBar::copy;
        bindProgressBar["onValueChange"] = &tgui::ProgressBar::onValueChange;
        bindProgressBar["onFull"] = &tgui::ProgressBar::onFull;
    }
    void LoadClassProgressBarRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ProgressBarRenderer> bindProgressBarRenderer
            = tguiNamespace.new_usertype<tgui::ProgressBarRenderer>("ProgressBarRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindProgressBarRenderer["setBorders"] = &tgui::ProgressBarRenderer::setBorders;
        bindProgressBarRenderer["getBorders"] = &tgui::ProgressBarRenderer::getBorders;
        bindProgressBarRenderer["setTextColor"]
            = &tgui::ProgressBarRenderer::setTextColor;
        bindProgressBarRenderer["getTextColor"]
            = &tgui::ProgressBarRenderer::getTextColor;
        bindProgressBarRenderer["setTextColorFilled"]
            = &tgui::ProgressBarRenderer::setTextColorFilled;
        bindProgressBarRenderer["getTextColorFilled"]
            = &tgui::ProgressBarRenderer::getTextColorFilled;
        bindProgressBarRenderer["setBackgroundColor"]
            = &tgui::ProgressBarRenderer::setBackgroundColor;
        bindProgressBarRenderer["getBackgroundColor"]
            = &tgui::ProgressBarRenderer::getBackgroundColor;
        bindProgressBarRenderer["setFillColor"]
            = &tgui::ProgressBarRenderer::setFillColor;
        bindProgressBarRenderer["getFillColor"]
            = &tgui::ProgressBarRenderer::getFillColor;
        bindProgressBarRenderer["setBorderColor"]
            = &tgui::ProgressBarRenderer::setBorderColor;
        bindProgressBarRenderer["getBorderColor"]
            = &tgui::ProgressBarRenderer::getBorderColor;
        bindProgressBarRenderer["setTextureBackground"]
            = &tgui::ProgressBarRenderer::setTextureBackground;
        bindProgressBarRenderer["getTextureBackground"]
            = &tgui::ProgressBarRenderer::getTextureBackground;
        bindProgressBarRenderer["setTextureFill"]
            = &tgui::ProgressBarRenderer::setTextureFill;
        bindProgressBarRenderer["getTextureFill"]
            = &tgui::ProgressBarRenderer::getTextureFill;
        bindProgressBarRenderer["setTextStyle"]
            = &tgui::ProgressBarRenderer::setTextStyle;
        bindProgressBarRenderer["getTextStyle"]
            = &tgui::ProgressBarRenderer::getTextStyle;
        bindProgressBarRenderer["WidgetRenderer"] = sol::overload(
            static_cast<(tgui::ProgressBarRenderer::*)()>(
                &tgui::ProgressBarRenderer::WidgetRenderer),
            static_cast<(
                tgui::ProgressBarRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                &tgui::ProgressBarRenderer::WidgetRenderer));
    }
    void LoadClassRadioButton(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RadioButton> bindRadioButton
            = tguiNamespace.new_usertype<tgui::RadioButton>("RadioButton",
                sol::call_constructor,
                sol::constructors<tgui::RadioButton(), tgui::RadioButton(const char*),
                    tgui::RadioButton(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindRadioButton["getSharedRenderer"] = sol::overload(
            static_cast<gui::RadioButtonRenderer* (tgui::RadioButton::*)()>(
                &tgui::RadioButton::getSharedRenderer),
            static_cast<const gui::RadioButtonRenderer* (tgui::RadioButton::*)() const>(
                &tgui::RadioButton::getSharedRenderer));
        bindRadioButton["getRenderer"] = sol::overload(
            static_cast<gui::RadioButtonRenderer* (tgui::RadioButton::*)()>(
                &tgui::RadioButton::getRenderer),
            static_cast<const gui::RadioButtonRenderer* (tgui::RadioButton::*)() const>(
                &tgui::RadioButton::getRenderer));
        bindRadioButton["setSize"] = sol::overload(
            static_cast<void (tgui::RadioButton::*)(const gui::Layout2d&)>(
                &tgui::RadioButton::setSize),
            static_cast<void (tgui::RadioButton::*)(const gui::Layout2d&)>(
                &tgui::RadioButton::setSize),
            static_cast<void (tgui::RadioButton::*)(gui::Layout, gui::Layout)>(
                &tgui::RadioButton::setSize));
        bindRadioButton["getFullSize"] = &tgui::RadioButton::getFullSize;
        bindRadioButton["getWidgetOffset"] = &tgui::RadioButton::getWidgetOffset;
        bindRadioButton["setChecked"] = &tgui::RadioButton::setChecked;
        bindRadioButton["isChecked"] = &tgui::RadioButton::isChecked;
        bindRadioButton["setText"] = &tgui::RadioButton::setText;
        bindRadioButton["getText"] = &tgui::RadioButton::getText;
        bindRadioButton["setTextSize"] = &tgui::RadioButton::setTextSize;
        bindRadioButton["getTextSize"] = &tgui::RadioButton::getTextSize;
        bindRadioButton["setTextClickable"] = &tgui::RadioButton::setTextClickable;
        bindRadioButton["isTextClickable"] = &tgui::RadioButton::isTextClickable;
        bindRadioButton["isMouseOnWidget"] = &tgui::RadioButton::isMouseOnWidget;
        bindRadioButton["leftMouseReleased"] = &tgui::RadioButton::leftMouseReleased;
        bindRadioButton["keyPressed"] = &tgui::RadioButton::keyPressed;
        bindRadioButton["draw"] = &tgui::RadioButton::draw;
        bindRadioButton["create"] = &tgui::RadioButton::create;
        bindRadioButton["copy"] = &tgui::RadioButton::copy;
        bindRadioButton["onCheck"] = &tgui::RadioButton::onCheck;
        bindRadioButton["onUncheck"] = &tgui::RadioButton::onUncheck;
        bindRadioButton["onChange"] = &tgui::RadioButton::onChange;
    }
    void LoadClassRadioButtonGroup(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RadioButtonGroup> bindRadioButtonGroup
            = tguiNamespace.new_usertype<tgui::RadioButtonGroup>("RadioButtonGroup",
                sol::call_constructor,
                sol::constructors<tgui::RadioButtonGroup(),
                    tgui::RadioButtonGroup(const char*),
                    tgui::RadioButtonGroup(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::Group, tgui::Container, tgui::Widget>());
        bindRadioButtonGroup["uncheckRadioButtons"]
            = &tgui::RadioButtonGroup::uncheckRadioButtons;
        bindRadioButtonGroup["getCheckedRadioButton"]
            = &tgui::RadioButtonGroup::getCheckedRadioButton;
        bindRadioButtonGroup["draw"] = &tgui::RadioButtonGroup::draw;
        bindRadioButtonGroup["create"] = &tgui::RadioButtonGroup::create;
        bindRadioButtonGroup["copy"] = &tgui::RadioButtonGroup::copy;
    }
    void LoadClassRadioButtonRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RadioButtonRenderer> bindRadioButtonRenderer
            = tguiNamespace.new_usertype<tgui::RadioButtonRenderer>("RadioButtonRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindRadioButtonRenderer["setBorders"] = &tgui::RadioButtonRenderer::setBorders;
        bindRadioButtonRenderer["getBorders"] = &tgui::RadioButtonRenderer::getBorders;
        bindRadioButtonRenderer["setTextDistanceRatio"]
            = &tgui::RadioButtonRenderer::setTextDistanceRatio;
        bindRadioButtonRenderer["getTextDistanceRatio"]
            = &tgui::RadioButtonRenderer::getTextDistanceRatio;
        bindRadioButtonRenderer["setTextColor"]
            = &tgui::RadioButtonRenderer::setTextColor;
        bindRadioButtonRenderer["getTextColor"]
            = &tgui::RadioButtonRenderer::getTextColor;
        bindRadioButtonRenderer["setTextColorHover"]
            = &tgui::RadioButtonRenderer::setTextColorHover;
        bindRadioButtonRenderer["getTextColorHover"]
            = &tgui::RadioButtonRenderer::getTextColorHover;
        bindRadioButtonRenderer["setTextColorDisabled"]
            = &tgui::RadioButtonRenderer::setTextColorDisabled;
        bindRadioButtonRenderer["getTextColorDisabled"]
            = &tgui::RadioButtonRenderer::getTextColorDisabled;
        bindRadioButtonRenderer["setTextColorChecked"]
            = &tgui::RadioButtonRenderer::setTextColorChecked;
        bindRadioButtonRenderer["getTextColorChecked"]
            = &tgui::RadioButtonRenderer::getTextColorChecked;
        bindRadioButtonRenderer["setTextColorCheckedHover"]
            = &tgui::RadioButtonRenderer::setTextColorCheckedHover;
        bindRadioButtonRenderer["getTextColorCheckedHover"]
            = &tgui::RadioButtonRenderer::getTextColorCheckedHover;
        bindRadioButtonRenderer["setTextColorCheckedDisabled"]
            = &tgui::RadioButtonRenderer::setTextColorCheckedDisabled;
        bindRadioButtonRenderer["getTextColorCheckedDisabled"]
            = &tgui::RadioButtonRenderer::getTextColorCheckedDisabled;
        bindRadioButtonRenderer["setBackgroundColor"]
            = &tgui::RadioButtonRenderer::setBackgroundColor;
        bindRadioButtonRenderer["getBackgroundColor"]
            = &tgui::RadioButtonRenderer::getBackgroundColor;
        bindRadioButtonRenderer["setBackgroundColorHover"]
            = &tgui::RadioButtonRenderer::setBackgroundColorHover;
        bindRadioButtonRenderer["getBackgroundColorHover"]
            = &tgui::RadioButtonRenderer::getBackgroundColorHover;
        bindRadioButtonRenderer["setBackgroundColorDisabled"]
            = &tgui::RadioButtonRenderer::setBackgroundColorDisabled;
        bindRadioButtonRenderer["getBackgroundColorDisabled"]
            = &tgui::RadioButtonRenderer::getBackgroundColorDisabled;
        bindRadioButtonRenderer["setBackgroundColorChecked"]
            = &tgui::RadioButtonRenderer::setBackgroundColorChecked;
        bindRadioButtonRenderer["getBackgroundColorChecked"]
            = &tgui::RadioButtonRenderer::getBackgroundColorChecked;
        bindRadioButtonRenderer["setBackgroundColorCheckedHover"]
            = &tgui::RadioButtonRenderer::setBackgroundColorCheckedHover;
        bindRadioButtonRenderer["getBackgroundColorCheckedHover"]
            = &tgui::RadioButtonRenderer::getBackgroundColorCheckedHover;
        bindRadioButtonRenderer["setBackgroundColorCheckedDisabled"]
            = &tgui::RadioButtonRenderer::setBackgroundColorCheckedDisabled;
        bindRadioButtonRenderer["getBackgroundColorCheckedDisabled"]
            = &tgui::RadioButtonRenderer::getBackgroundColorCheckedDisabled;
        bindRadioButtonRenderer["setBorderColor"]
            = &tgui::RadioButtonRenderer::setBorderColor;
        bindRadioButtonRenderer["getBorderColor"]
            = &tgui::RadioButtonRenderer::getBorderColor;
        bindRadioButtonRenderer["setBorderColorHover"]
            = &tgui::RadioButtonRenderer::setBorderColorHover;
        bindRadioButtonRenderer["getBorderColorHover"]
            = &tgui::RadioButtonRenderer::getBorderColorHover;
        bindRadioButtonRenderer["setBorderColorDisabled"]
            = &tgui::RadioButtonRenderer::setBorderColorDisabled;
        bindRadioButtonRenderer["getBorderColorDisabled"]
            = &tgui::RadioButtonRenderer::getBorderColorDisabled;
        bindRadioButtonRenderer["setBorderColorFocused"]
            = &tgui::RadioButtonRenderer::setBorderColorFocused;
        bindRadioButtonRenderer["getBorderColorFocused"]
            = &tgui::RadioButtonRenderer::getBorderColorFocused;
        bindRadioButtonRenderer["setBorderColorChecked"]
            = &tgui::RadioButtonRenderer::setBorderColorChecked;
        bindRadioButtonRenderer["getBorderColorChecked"]
            = &tgui::RadioButtonRenderer::getBorderColorChecked;
        bindRadioButtonRenderer["setBorderColorCheckedHover"]
            = &tgui::RadioButtonRenderer::setBorderColorCheckedHover;
        bindRadioButtonRenderer["getBorderColorCheckedHover"]
            = &tgui::RadioButtonRenderer::getBorderColorCheckedHover;
        bindRadioButtonRenderer["setBorderColorCheckedDisabled"]
            = &tgui::RadioButtonRenderer::setBorderColorCheckedDisabled;
        bindRadioButtonRenderer["getBorderColorCheckedDisabled"]
            = &tgui::RadioButtonRenderer::getBorderColorCheckedDisabled;
        bindRadioButtonRenderer["setBorderColorCheckedFocused"]
            = &tgui::RadioButtonRenderer::setBorderColorCheckedFocused;
        bindRadioButtonRenderer["getBorderColorCheckedFocused"]
            = &tgui::RadioButtonRenderer::getBorderColorCheckedFocused;
        bindRadioButtonRenderer["setCheckColor"]
            = &tgui::RadioButtonRenderer::setCheckColor;
        bindRadioButtonRenderer["getCheckColor"]
            = &tgui::RadioButtonRenderer::getCheckColor;
        bindRadioButtonRenderer["setCheckColorHover"]
            = &tgui::RadioButtonRenderer::setCheckColorHover;
        bindRadioButtonRenderer["getCheckColorHover"]
            = &tgui::RadioButtonRenderer::getCheckColorHover;
        bindRadioButtonRenderer["setCheckColorDisabled"]
            = &tgui::RadioButtonRenderer::setCheckColorDisabled;
        bindRadioButtonRenderer["getCheckColorDisabled"]
            = &tgui::RadioButtonRenderer::getCheckColorDisabled;
        bindRadioButtonRenderer["setTextureUnchecked"]
            = &tgui::RadioButtonRenderer::setTextureUnchecked;
        bindRadioButtonRenderer["getTextureUnchecked"]
            = &tgui::RadioButtonRenderer::getTextureUnchecked;
        bindRadioButtonRenderer["setTextureChecked"]
            = &tgui::RadioButtonRenderer::setTextureChecked;
        bindRadioButtonRenderer["getTextureChecked"]
            = &tgui::RadioButtonRenderer::getTextureChecked;
        bindRadioButtonRenderer["setTextureUncheckedHover"]
            = &tgui::RadioButtonRenderer::setTextureUncheckedHover;
        bindRadioButtonRenderer["getTextureUncheckedHover"]
            = &tgui::RadioButtonRenderer::getTextureUncheckedHover;
        bindRadioButtonRenderer["setTextureCheckedHover"]
            = &tgui::RadioButtonRenderer::setTextureCheckedHover;
        bindRadioButtonRenderer["getTextureCheckedHover"]
            = &tgui::RadioButtonRenderer::getTextureCheckedHover;
        bindRadioButtonRenderer["setTextureUncheckedDisabled"]
            = &tgui::RadioButtonRenderer::setTextureUncheckedDisabled;
        bindRadioButtonRenderer["getTextureUncheckedDisabled"]
            = &tgui::RadioButtonRenderer::getTextureUncheckedDisabled;
        bindRadioButtonRenderer["setTextureCheckedDisabled"]
            = &tgui::RadioButtonRenderer::setTextureCheckedDisabled;
        bindRadioButtonRenderer["getTextureCheckedDisabled"]
            = &tgui::RadioButtonRenderer::getTextureCheckedDisabled;
        bindRadioButtonRenderer["setTextureUncheckedFocused"]
            = &tgui::RadioButtonRenderer::setTextureUncheckedFocused;
        bindRadioButtonRenderer["getTextureUncheckedFocused"]
            = &tgui::RadioButtonRenderer::getTextureUncheckedFocused;
        bindRadioButtonRenderer["setTextureCheckedFocused"]
            = &tgui::RadioButtonRenderer::setTextureCheckedFocused;
        bindRadioButtonRenderer["getTextureCheckedFocused"]
            = &tgui::RadioButtonRenderer::getTextureCheckedFocused;
        bindRadioButtonRenderer["setTextStyle"]
            = &tgui::RadioButtonRenderer::setTextStyle;
        bindRadioButtonRenderer["getTextStyle"]
            = &tgui::RadioButtonRenderer::getTextStyle;
        bindRadioButtonRenderer["setTextStyleChecked"]
            = &tgui::RadioButtonRenderer::setTextStyleChecked;
        bindRadioButtonRenderer["getTextStyleChecked"]
            = &tgui::RadioButtonRenderer::getTextStyleChecked;
        bindRadioButtonRenderer["WidgetRenderer"] = sol::overload(
            static_cast<(tgui::RadioButtonRenderer::*)()>(
                &tgui::RadioButtonRenderer::WidgetRenderer),
            static_cast<(
                tgui::RadioButtonRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                &tgui::RadioButtonRenderer::WidgetRenderer));
    }
    void LoadClassRangeSlider(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RangeSlider> bindRangeSlider
            = tguiNamespace.new_usertype<tgui::RangeSlider>("RangeSlider",
                sol::call_constructor,
                sol::constructors<tgui::RangeSlider(), tgui::RangeSlider(const char*),
                    tgui::RangeSlider(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindRangeSlider["getSharedRenderer"] = sol::overload(
            static_cast<gui::RangeSliderRenderer* (tgui::RangeSlider::*)()>(
                &tgui::RangeSlider::getSharedRenderer),
            static_cast<const gui::RangeSliderRenderer* (tgui::RangeSlider::*)() const>(
                &tgui::RangeSlider::getSharedRenderer));
        bindRangeSlider["getRenderer"] = sol::overload(
            static_cast<gui::RangeSliderRenderer* (tgui::RangeSlider::*)()>(
                &tgui::RangeSlider::getRenderer),
            static_cast<const gui::RangeSliderRenderer* (tgui::RangeSlider::*)() const>(
                &tgui::RangeSlider::getRenderer));
        bindRangeSlider["setSize"] = sol::overload(
            static_cast<void (tgui::RangeSlider::*)(const gui::Layout2d&)>(
                &tgui::RangeSlider::setSize),
            static_cast<void (tgui::RangeSlider::*)(const gui::Layout2d&)>(
                &tgui::RangeSlider::setSize),
            static_cast<void (tgui::RangeSlider::*)(gui::Layout, gui::Layout)>(
                &tgui::RangeSlider::setSize));
        bindRangeSlider["getFullSize"] = &tgui::RangeSlider::getFullSize;
        bindRangeSlider["getWidgetOffset"] = &tgui::RangeSlider::getWidgetOffset;
        bindRangeSlider["setMinimum"] = &tgui::RangeSlider::setMinimum;
        bindRangeSlider["getMinimum"] = &tgui::RangeSlider::getMinimum;
        bindRangeSlider["setMaximum"] = &tgui::RangeSlider::setMaximum;
        bindRangeSlider["getMaximum"] = &tgui::RangeSlider::getMaximum;
        bindRangeSlider["setSelectionStart"] = &tgui::RangeSlider::setSelectionStart;
        bindRangeSlider["getSelectionStart"] = &tgui::RangeSlider::getSelectionStart;
        bindRangeSlider["setSelectionEnd"] = &tgui::RangeSlider::setSelectionEnd;
        bindRangeSlider["getSelectionEnd"] = &tgui::RangeSlider::getSelectionEnd;
        bindRangeSlider["setStep"] = &tgui::RangeSlider::setStep;
        bindRangeSlider["getStep"] = &tgui::RangeSlider::getStep;
        bindRangeSlider["isMouseOnWidget"] = &tgui::RangeSlider::isMouseOnWidget;
        bindRangeSlider["leftMousePressed"] = &tgui::RangeSlider::leftMousePressed;
        bindRangeSlider["leftMouseReleased"] = &tgui::RangeSlider::leftMouseReleased;
        bindRangeSlider["mouseMoved"] = &tgui::RangeSlider::mouseMoved;
        bindRangeSlider["leftMouseButtonNoLongerDown"]
            = &tgui::RangeSlider::leftMouseButtonNoLongerDown;
        bindRangeSlider["draw"] = &tgui::RangeSlider::draw;
        bindRangeSlider["create"] = sol::overload(
            [](tgui::RangeSlider* self)
                -> gui::RangeSlider1a9c1224a1af70760ef06b64fc83373c86 {
                return self->create();
            },
            [](tgui::RangeSlider* self,
                float minimum) -> gui::RangeSlider1a9c1224a1af70760ef06b64fc83373c86 {
                return self->create(minimum);
            },
            [](tgui::RangeSlider* self, float minimum,
                float maximum) -> gui::RangeSlider1a9c1224a1af70760ef06b64fc83373c86 {
                return self->create(minimum, maximum);
            });
        bindRangeSlider["copy"] = &tgui::RangeSlider::copy;
        bindRangeSlider["onRangeChange"] = &tgui::RangeSlider::onRangeChange;
    }
    void LoadClassRangeSliderRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RangeSliderRenderer> bindRangeSliderRenderer
            = tguiNamespace.new_usertype<tgui::RangeSliderRenderer>("RangeSliderRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::SliderRenderer, tgui::WidgetRenderer>());
        bindRangeSliderRenderer["setSelectedTrackColor"]
            = &tgui::RangeSliderRenderer::setSelectedTrackColor;
        bindRangeSliderRenderer["getSelectedTrackColor"]
            = &tgui::RangeSliderRenderer::getSelectedTrackColor;
        bindRangeSliderRenderer["setSelectedTrackColorHover"]
            = &tgui::RangeSliderRenderer::setSelectedTrackColorHover;
        bindRangeSliderRenderer["getSelectedTrackColorHover"]
            = &tgui::RangeSliderRenderer::getSelectedTrackColorHover;
        bindRangeSliderRenderer["setTextureSelectedTrack"]
            = &tgui::RangeSliderRenderer::setTextureSelectedTrack;
        bindRangeSliderRenderer["getTextureSelectedTrack"]
            = &tgui::RangeSliderRenderer::getTextureSelectedTrack;
        bindRangeSliderRenderer["setTextureSelectedTrackHover"]
            = &tgui::RangeSliderRenderer::setTextureSelectedTrackHover;
        bindRangeSliderRenderer["getTextureSelectedTrackHover"]
            = &tgui::RangeSliderRenderer::getTextureSelectedTrackHover;
    }
    void LoadClassRootContainer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RootContainer> bindRootContainer
            = tguiNamespace.new_usertype<tgui::RootContainer>("RootContainer",
                sol::call_constructor,
                sol::constructors<tgui::RootContainer(), tgui::RootContainer(const char*),
                    tgui::RootContainer(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Container, tgui::Widget>());
        bindRootContainer["setSize"] = sol::overload(
            static_cast<void (tgui::RootContainer::*)(const gui::Layout2d&)>(
                &tgui::RootContainer::setSize),
            static_cast<void (tgui::RootContainer::*)(const gui::Layout2d&)>(
                &tgui::RootContainer::setSize),
            static_cast<void (tgui::RootContainer::*)(gui::Layout, gui::Layout)>(
                &tgui::RootContainer::setSize));
        bindRootContainer["setFocused"] = &tgui::RootContainer::setFocused;
        bindRootContainer["isMouseOnWidget"] = &tgui::RootContainer::isMouseOnWidget;
        bindRootContainer["draw"] = &tgui::RootContainer::draw;
    }
    void LoadClassScrollablePanel(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ScrollablePanel> bindScrollablePanel
            = tguiNamespace.new_usertype<tgui::ScrollablePanel>("ScrollablePanel",
                sol::call_constructor,
                sol::constructors<tgui::ScrollablePanel(),
                    tgui::ScrollablePanel(const char*),
                    tgui::ScrollablePanel(const char*, bool),
                    tgui::ScrollablePanel(const gui::ScrollablePanel&),
                    tgui::ScrollablePanel(gui::ScrollablePanel &&)>(),
                sol::base_classes,
                sol::bases<tgui::Panel, tgui::Group, tgui::Container, tgui::Widget>());
        bindScrollablePanel["operator="]
            = sol::overload(static_cast<gui::ScrollablePanel& (
                                tgui::ScrollablePanel::*)(const gui::ScrollablePanel&)>(
                                &tgui::ScrollablePanel::operator=),
                static_cast<gui::ScrollablePanel& (
                    tgui::ScrollablePanel::*)(gui::ScrollablePanel &&)>(
                    &tgui::ScrollablePanel::operator=));
        bindScrollablePanel["getSharedRenderer"] = sol::overload(
            static_cast<gui::ScrollablePanelRenderer* (tgui::ScrollablePanel::*)()>(
                &tgui::ScrollablePanel::getSharedRenderer),
            static_cast<const gui::ScrollablePanelRenderer* (tgui::ScrollablePanel::*)()
                    const>(&tgui::ScrollablePanel::getSharedRenderer));
        bindScrollablePanel["getRenderer"] = sol::overload(
            static_cast<gui::ScrollablePanelRenderer* (tgui::ScrollablePanel::*)()>(
                &tgui::ScrollablePanel::getRenderer),
            static_cast<const gui::ScrollablePanelRenderer* (tgui::ScrollablePanel::*)()
                    const>(&tgui::ScrollablePanel::getRenderer));
        bindScrollablePanel["setSize"] = sol::overload(
            static_cast<void (tgui::ScrollablePanel::*)(const gui::Layout2d&)>(
                &tgui::ScrollablePanel::setSize),
            static_cast<void (tgui::ScrollablePanel::*)(const gui::Layout2d&)>(
                &tgui::ScrollablePanel::setSize),
            static_cast<void (tgui::ScrollablePanel::*)(gui::Layout, gui::Layout)>(
                &tgui::ScrollablePanel::setSize));
        bindScrollablePanel["getAbsolutePosition"]
            = &tgui::ScrollablePanel::getAbsolutePosition;
        bindScrollablePanel["add"] = sol::overload(
            [](tgui::ScrollablePanel* self,
                const gui::Widget1a388912f13898735531886bc676b14f81& widget) -> void {
                return self->add(widget);
            },
            [](tgui::ScrollablePanel* self,
                const gui::Widget1a388912f13898735531886bc676b14f81& widget,
                const gui::String& widgetName) -> void {
                return self->add(widget, widgetName);
            });
        bindScrollablePanel["remove"] = &tgui::ScrollablePanel::remove;
        bindScrollablePanel["removeAllWidgets"]
            = &tgui::ScrollablePanel::removeAllWidgets;
        bindScrollablePanel["setContentSize"] = &tgui::ScrollablePanel::setContentSize;
        bindScrollablePanel["getContentSize"] = &tgui::ScrollablePanel::getContentSize;
        bindScrollablePanel["getContentOffset"]
            = &tgui::ScrollablePanel::getContentOffset;
        bindScrollablePanel["getScrollbarWidth"]
            = &tgui::ScrollablePanel::getScrollbarWidth;
        bindScrollablePanel["setVerticalScrollbarPolicy"]
            = &tgui::ScrollablePanel::setVerticalScrollbarPolicy;
        bindScrollablePanel["getVerticalScrollbarPolicy"]
            = &tgui::ScrollablePanel::getVerticalScrollbarPolicy;
        bindScrollablePanel["setHorizontalScrollbarPolicy"]
            = &tgui::ScrollablePanel::setHorizontalScrollbarPolicy;
        bindScrollablePanel["getHorizontalScrollbarPolicy"]
            = &tgui::ScrollablePanel::getHorizontalScrollbarPolicy;
        bindScrollablePanel["setVerticalScrollAmount"]
            = &tgui::ScrollablePanel::setVerticalScrollAmount;
        bindScrollablePanel["getVerticalScrollAmount"]
            = &tgui::ScrollablePanel::getVerticalScrollAmount;
        bindScrollablePanel["setHorizontalScrollAmount"]
            = &tgui::ScrollablePanel::setHorizontalScrollAmount;
        bindScrollablePanel["getHorizontalScrollAmount"]
            = &tgui::ScrollablePanel::getHorizontalScrollAmount;
        bindScrollablePanel["setVerticalScrollbarValue"]
            = &tgui::ScrollablePanel::setVerticalScrollbarValue;
        bindScrollablePanel["getVerticalScrollbarValue"]
            = &tgui::ScrollablePanel::getVerticalScrollbarValue;
        bindScrollablePanel["setHorizontalScrollbarValue"]
            = &tgui::ScrollablePanel::setHorizontalScrollbarValue;
        bindScrollablePanel["getHorizontalScrollbarValue"]
            = &tgui::ScrollablePanel::getHorizontalScrollbarValue;
        bindScrollablePanel["getWidgetAtPosition"]
            = &tgui::ScrollablePanel::getWidgetAtPosition;
        bindScrollablePanel["leftMousePressed"]
            = &tgui::ScrollablePanel::leftMousePressed;
        bindScrollablePanel["leftMouseReleased"]
            = &tgui::ScrollablePanel::leftMouseReleased;
        bindScrollablePanel["mouseMoved"] = &tgui::ScrollablePanel::mouseMoved;
        bindScrollablePanel["mouseWheelScrolled"]
            = &tgui::ScrollablePanel::mouseWheelScrolled;
        bindScrollablePanel["mouseNoLongerOnWidget"]
            = &tgui::ScrollablePanel::mouseNoLongerOnWidget;
        bindScrollablePanel["leftMouseButtonNoLongerDown"]
            = &tgui::ScrollablePanel::leftMouseButtonNoLongerDown;
        bindScrollablePanel["askToolTip"] = &tgui::ScrollablePanel::askToolTip;
        bindScrollablePanel["draw"] = &tgui::ScrollablePanel::draw;
        bindScrollablePanel["create"] = sol::overload(
            [](tgui::ScrollablePanel* self)
                -> gui::ScrollablePanel1a025463003b07579476bc75c335e5decb {
                return self->create();
            },
            [](tgui::ScrollablePanel* self, gui::Layout2d size)
                -> gui::ScrollablePanel1a025463003b07579476bc75c335e5decb {
                return self->create(size);
            },
            [](tgui::ScrollablePanel* self, gui::Layout2d size,
                tgui::Vector2f contentSize)
                -> gui::ScrollablePanel1a025463003b07579476bc75c335e5decb {
                return self->create(size, contentSize);
            });
        bindScrollablePanel["copy"] = &tgui::ScrollablePanel::copy;
    }
    void LoadClassScrollablePanelRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ScrollablePanelRenderer> bindScrollablePanelRenderer
            = tguiNamespace.new_usertype<tgui::ScrollablePanelRenderer>(
                "ScrollablePanelRenderer", sol::call_constructor,
                sol::default_constructor, sol::base_classes,
                sol::bases<tgui::PanelRenderer, tgui::GroupRenderer,
                    tgui::WidgetRenderer>());
        bindScrollablePanelRenderer["setScrollbar"]
            = &tgui::ScrollablePanelRenderer::setScrollbar;
        bindScrollablePanelRenderer["getScrollbar"]
            = &tgui::ScrollablePanelRenderer::getScrollbar;
        bindScrollablePanelRenderer["setScrollbarWidth"]
            = &tgui::ScrollablePanelRenderer::setScrollbarWidth;
        bindScrollablePanelRenderer["getScrollbarWidth"]
            = &tgui::ScrollablePanelRenderer::getScrollbarWidth;
    }
    void LoadClassScrollbar(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Scrollbar> bindScrollbar
            = tguiNamespace.new_usertype<tgui::Scrollbar>("Scrollbar",
                sol::call_constructor,
                sol::constructors<tgui::Scrollbar(), tgui::Scrollbar(const char*),
                    tgui::Scrollbar(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindScrollbar["getSharedRenderer"]
            = sol::overload(static_cast<gui::ScrollbarRenderer* (tgui::Scrollbar::*)()>(
                                &tgui::Scrollbar::getSharedRenderer),
                static_cast<const gui::ScrollbarRenderer* (tgui::Scrollbar::*)() const>(
                    &tgui::Scrollbar::getSharedRenderer));
        bindScrollbar["getRenderer"]
            = sol::overload(static_cast<gui::ScrollbarRenderer* (tgui::Scrollbar::*)()>(
                                &tgui::Scrollbar::getRenderer),
                static_cast<const gui::ScrollbarRenderer* (tgui::Scrollbar::*)() const>(
                    &tgui::Scrollbar::getRenderer));
        bindScrollbar["setSize"]
            = sol::overload(static_cast<void (tgui::Scrollbar::*)(const gui::Layout2d&)>(
                                &tgui::Scrollbar::setSize),
                static_cast<void (tgui::Scrollbar::*)(const gui::Layout2d&)>(
                    &tgui::Scrollbar::setSize),
                static_cast<void (tgui::Scrollbar::*)(gui::Layout, gui::Layout)>(
                    &tgui::Scrollbar::setSize));
        bindScrollbar["setMaximum"] = &tgui::Scrollbar::setMaximum;
        bindScrollbar["getMaximum"] = &tgui::Scrollbar::getMaximum;
        bindScrollbar["setValue"] = &tgui::Scrollbar::setValue;
        bindScrollbar["getValue"] = &tgui::Scrollbar::getValue;
        bindScrollbar["setViewportSize"] = &tgui::Scrollbar::setViewportSize;
        bindScrollbar["getViewportSize"] = &tgui::Scrollbar::getViewportSize;
        bindScrollbar["setScrollAmount"] = &tgui::Scrollbar::setScrollAmount;
        bindScrollbar["getScrollAmount"] = &tgui::Scrollbar::getScrollAmount;
        bindScrollbar["setAutoHide"] = &tgui::Scrollbar::setAutoHide;
        bindScrollbar["getAutoHide"] = &tgui::Scrollbar::getAutoHide;
        bindScrollbar["setVerticalScroll"] = &tgui::Scrollbar::setVerticalScroll;
        bindScrollbar["getVerticalScroll"] = &tgui::Scrollbar::getVerticalScroll;
        bindScrollbar["getDefaultWidth"] = &tgui::Scrollbar::getDefaultWidth;
        bindScrollbar["isMouseOnWidget"] = &tgui::Scrollbar::isMouseOnWidget;
        bindScrollbar["leftMousePressed"] = &tgui::Scrollbar::leftMousePressed;
        bindScrollbar["leftMouseReleased"] = &tgui::Scrollbar::leftMouseReleased;
        bindScrollbar["mouseMoved"] = &tgui::Scrollbar::mouseMoved;
        bindScrollbar["mouseWheelScrolled"] = &tgui::Scrollbar::mouseWheelScrolled;
        bindScrollbar["leftMouseButtonNoLongerDown"]
            = &tgui::Scrollbar::leftMouseButtonNoLongerDown;
        bindScrollbar["draw"] = &tgui::Scrollbar::draw;
        bindScrollbar["create"] = &tgui::Scrollbar::create;
        bindScrollbar["copy"] = &tgui::Scrollbar::copy;
        bindScrollbar["onValueChange"] = &tgui::Scrollbar::onValueChange;
    }
    void LoadClassScrollbarChildWidget(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ScrollbarChildWidget> bindScrollbarChildWidget
            = tguiNamespace.new_usertype<tgui::ScrollbarChildWidget>(
                "ScrollbarChildWidget", sol::call_constructor, sol::default_constructor,
                sol::base_classes, sol::bases<tgui::Scrollbar, tgui::Widget>());
        bindScrollbarChildWidget["isMouseDownOnThumb"]
            = &tgui::ScrollbarChildWidget::isMouseDownOnThumb;
        bindScrollbarChildWidget["isShown"] = &tgui::ScrollbarChildWidget::isShown;
        bindScrollbarChildWidget["draw"] = &tgui::ScrollbarChildWidget::draw;
    }
    void LoadClassScrollbarRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ScrollbarRenderer> bindScrollbarRenderer
            = tguiNamespace.new_usertype<tgui::ScrollbarRenderer>("ScrollbarRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindScrollbarRenderer["setTrackColor"] = &tgui::ScrollbarRenderer::setTrackColor;
        bindScrollbarRenderer["getTrackColor"] = &tgui::ScrollbarRenderer::getTrackColor;
        bindScrollbarRenderer["setTrackColorHover"]
            = &tgui::ScrollbarRenderer::setTrackColorHover;
        bindScrollbarRenderer["getTrackColorHover"]
            = &tgui::ScrollbarRenderer::getTrackColorHover;
        bindScrollbarRenderer["setThumbColor"] = &tgui::ScrollbarRenderer::setThumbColor;
        bindScrollbarRenderer["getThumbColor"] = &tgui::ScrollbarRenderer::getThumbColor;
        bindScrollbarRenderer["setThumbColorHover"]
            = &tgui::ScrollbarRenderer::setThumbColorHover;
        bindScrollbarRenderer["getThumbColorHover"]
            = &tgui::ScrollbarRenderer::getThumbColorHover;
        bindScrollbarRenderer["setArrowBackgroundColor"]
            = &tgui::ScrollbarRenderer::setArrowBackgroundColor;
        bindScrollbarRenderer["getArrowBackgroundColor"]
            = &tgui::ScrollbarRenderer::getArrowBackgroundColor;
        bindScrollbarRenderer["setArrowBackgroundColorHover"]
            = &tgui::ScrollbarRenderer::setArrowBackgroundColorHover;
        bindScrollbarRenderer["getArrowBackgroundColorHover"]
            = &tgui::ScrollbarRenderer::getArrowBackgroundColorHover;
        bindScrollbarRenderer["setArrowColor"] = &tgui::ScrollbarRenderer::setArrowColor;
        bindScrollbarRenderer["getArrowColor"] = &tgui::ScrollbarRenderer::getArrowColor;
        bindScrollbarRenderer["setArrowColorHover"]
            = &tgui::ScrollbarRenderer::setArrowColorHover;
        bindScrollbarRenderer["getArrowColorHover"]
            = &tgui::ScrollbarRenderer::getArrowColorHover;
        bindScrollbarRenderer["setTextureTrack"]
            = &tgui::ScrollbarRenderer::setTextureTrack;
        bindScrollbarRenderer["getTextureTrack"]
            = &tgui::ScrollbarRenderer::getTextureTrack;
        bindScrollbarRenderer["setTextureTrackHover"]
            = &tgui::ScrollbarRenderer::setTextureTrackHover;
        bindScrollbarRenderer["getTextureTrackHover"]
            = &tgui::ScrollbarRenderer::getTextureTrackHover;
        bindScrollbarRenderer["setTextureThumb"]
            = &tgui::ScrollbarRenderer::setTextureThumb;
        bindScrollbarRenderer["getTextureThumb"]
            = &tgui::ScrollbarRenderer::getTextureThumb;
        bindScrollbarRenderer["setTextureThumbHover"]
            = &tgui::ScrollbarRenderer::setTextureThumbHover;
        bindScrollbarRenderer["getTextureThumbHover"]
            = &tgui::ScrollbarRenderer::getTextureThumbHover;
        bindScrollbarRenderer["setTextureArrowUp"]
            = &tgui::ScrollbarRenderer::setTextureArrowUp;
        bindScrollbarRenderer["getTextureArrowUp"]
            = &tgui::ScrollbarRenderer::getTextureArrowUp;
        bindScrollbarRenderer["setTextureArrowUpHover"]
            = &tgui::ScrollbarRenderer::setTextureArrowUpHover;
        bindScrollbarRenderer["getTextureArrowUpHover"]
            = &tgui::ScrollbarRenderer::getTextureArrowUpHover;
        bindScrollbarRenderer["setTextureArrowDown"]
            = &tgui::ScrollbarRenderer::setTextureArrowDown;
        bindScrollbarRenderer["getTextureArrowDown"]
            = &tgui::ScrollbarRenderer::getTextureArrowDown;
        bindScrollbarRenderer["setTextureArrowDownHover"]
            = &tgui::ScrollbarRenderer::setTextureArrowDownHover;
        bindScrollbarRenderer["getTextureArrowDownHover"]
            = &tgui::ScrollbarRenderer::getTextureArrowDownHover;
        bindScrollbarRenderer["WidgetRenderer"] = sol::overload(
            static_cast<(tgui::ScrollbarRenderer::*)()>(
                &tgui::ScrollbarRenderer::WidgetRenderer),
            static_cast<(
                tgui::ScrollbarRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                &tgui::ScrollbarRenderer::WidgetRenderer));
    }
    void LoadClassSeparatorLine(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SeparatorLine> bindSeparatorLine
            = tguiNamespace.new_usertype<tgui::SeparatorLine>("SeparatorLine",
                sol::call_constructor,
                sol::constructors<tgui::SeparatorLine(), tgui::SeparatorLine(const char*),
                    tgui::SeparatorLine(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindSeparatorLine["getSharedRenderer"] = sol::overload(
            static_cast<gui::SeparatorLineRenderer* (tgui::SeparatorLine::*)()>(
                &tgui::SeparatorLine::getSharedRenderer),
            static_cast<const gui::SeparatorLineRenderer* (tgui::SeparatorLine::*)()
                    const>(&tgui::SeparatorLine::getSharedRenderer));
        bindSeparatorLine["getRenderer"] = sol::overload(
            static_cast<gui::SeparatorLineRenderer* (tgui::SeparatorLine::*)()>(
                &tgui::SeparatorLine::getRenderer),
            static_cast<const gui::SeparatorLineRenderer* (tgui::SeparatorLine::*)()
                    const>(&tgui::SeparatorLine::getRenderer));
        bindSeparatorLine["draw"] = &tgui::SeparatorLine::draw;
        bindSeparatorLine["create"] = sol::overload(
            [](tgui::SeparatorLine* self)
                -> gui::SeparatorLine1a5882371a7aeef3f3cace5ff0b429741a {
                return self->create();
            },
            [](tgui::SeparatorLine* self, gui::Layout2d size)
                -> gui::SeparatorLine1a5882371a7aeef3f3cace5ff0b429741a {
                return self->create(size);
            });
        bindSeparatorLine["copy"] = &tgui::SeparatorLine::copy;
    }
    void LoadClassSeparatorLineRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SeparatorLineRenderer> bindSeparatorLineRenderer
            = tguiNamespace.new_usertype<tgui::SeparatorLineRenderer>(
                "SeparatorLineRenderer", sol::call_constructor, sol::default_constructor,
                sol::base_classes, sol::bases<tgui::WidgetRenderer>());
        bindSeparatorLineRenderer["setColor"] = &tgui::SeparatorLineRenderer::setColor;
        bindSeparatorLineRenderer["getColor"] = &tgui::SeparatorLineRenderer::getColor;
        bindSeparatorLineRenderer["WidgetRenderer"]
            = sol::overload(static_cast<(tgui::SeparatorLineRenderer::*)()>(
                                &tgui::SeparatorLineRenderer::WidgetRenderer),
                static_cast<(tgui::SeparatorLineRenderer::*)(const std::shared_ptr<
                    gui::RendererData>&)>(&tgui::SeparatorLineRenderer::WidgetRenderer));
    }
    void LoadClassSerializer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Serializer> bindSerializer
            = tguiNamespace.new_usertype<tgui::Serializer>(
                "Serializer", sol::call_constructor, sol::default_constructor);
        bindSerializer["serialize"] = &tgui::Serializer::serialize;
        bindSerializer["setFunction"] = &tgui::Serializer::setFunction;
        bindSerializer["getFunction"] = &tgui::Serializer::getFunction;
    }
    void LoadClassSignal(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Signal> bindSignal
            = tguiNamespace.new_usertype<tgui::Signal>("Signal", sol::call_constructor,
                sol::constructors<tgui::Signal(gui::String &&),
                    tgui::Signal(gui::String&&, std::size_t),
                    tgui::Signal(const gui::Signal&), tgui::Signal(gui::Signal &&)>());
        bindSignal["operator="] = sol::overload(
            static_cast<gui::Signal& (tgui::Signal::*)(const gui::Signal&)>(
                &tgui::Signal::operator=),
            static_cast<gui::Signal& (tgui::Signal::*)(gui::Signal &&)>(
                &tgui::Signal::operator=));
        bindSignal["disconnect"] = &tgui::Signal::disconnect;
        bindSignal["disconnectAll"] = &tgui::Signal::disconnectAll;
        bindSignal["emit"] = &tgui::Signal::emit;
        bindSignal["getName"] = &tgui::Signal::getName;
        bindSignal["setEnabled"] = &tgui::Signal::setEnabled;
        bindSignal["isEnabled"] = &tgui::Signal::isEnabled;
    }
    void LoadClassSignalAnimation(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SignalAnimation> bindSignalAnimation
            = tguiNamespace.new_usertype<tgui::SignalAnimation>("SignalAnimation",
                sol::call_constructor,
                sol::constructors<tgui::SignalAnimation(gui::String &&)>(),
                sol::base_classes, sol::bases<tgui::Signal>());
        bindSignalAnimation["emit"] = &tgui::SignalAnimation::emit;
    }
    void LoadClassSignalChildWindow(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SignalChildWindow> bindSignalChildWindow
            = tguiNamespace.new_usertype<tgui::SignalChildWindow>("SignalChildWindow",
                sol::call_constructor,
                sol::constructors<tgui::SignalChildWindow(gui::String &&)>(),
                sol::base_classes, sol::bases<tgui::Signal>());
        bindSignalChildWindow["emit"] = &tgui::SignalChildWindow::emit;
    }
    void LoadClassSignalItem(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SignalItem> bindSignalItem
            = tguiNamespace.new_usertype<tgui::SignalItem>("SignalItem",
                sol::call_constructor,
                sol::constructors<tgui::SignalItem(gui::String &&)>(), sol::base_classes,
                sol::bases<tgui::Signal>());
        bindSignalItem["emit"] = &tgui::SignalItem::emit;
    }
    void LoadClassSignalItemHierarchy(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SignalItemHierarchy> bindSignalItemHierarchy
            = tguiNamespace.new_usertype<tgui::SignalItemHierarchy>("SignalItemHierarchy",
                sol::call_constructor,
                sol::constructors<tgui::SignalItemHierarchy(gui::String &&)>(),
                sol::base_classes, sol::bases<tgui::Signal>());
        bindSignalItemHierarchy["emit"] = &tgui::SignalItemHierarchy::emit;
    }
    void LoadClassSignalManager(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SignalManager> bindSignalManager
            = tguiNamespace.new_usertype<tgui::SignalManager>("SignalManager",
                sol::call_constructor, sol::constructors<tgui::SignalManager()>());
        bindSignalManager["disconnect"] = &tgui::SignalManager::disconnect;
        bindSignalManager["disconnectAll"] = &tgui::SignalManager::disconnectAll;
        bindSignalManager["add"] = &tgui::SignalManager::add;
        bindSignalManager["remove"] = &tgui::SignalManager::remove;
        bindSignalManager["setDefaultSignalManager"]
            = &tgui::SignalManager::setDefaultSignalManager;
        bindSignalManager["getSignalManager"] = &tgui::SignalManager::getSignalManager;
    }
    void LoadClassSlider(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Slider> bindSlider
            = tguiNamespace.new_usertype<tgui::Slider>("Slider", sol::call_constructor,
                sol::constructors<tgui::Slider(), tgui::Slider(const char*),
                    tgui::Slider(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindSlider["getSharedRenderer"]
            = sol::overload(static_cast<gui::SliderRenderer* (tgui::Slider::*)()>(
                                &tgui::Slider::getSharedRenderer),
                static_cast<const gui::SliderRenderer* (tgui::Slider::*)() const>(
                    &tgui::Slider::getSharedRenderer));
        bindSlider["getRenderer"]
            = sol::overload(static_cast<gui::SliderRenderer* (tgui::Slider::*)()>(
                                &tgui::Slider::getRenderer),
                static_cast<const gui::SliderRenderer* (tgui::Slider::*)() const>(
                    &tgui::Slider::getRenderer));
        bindSlider["setSize"]
            = sol::overload(static_cast<void (tgui::Slider::*)(const gui::Layout2d&)>(
                                &tgui::Slider::setSize),
                static_cast<void (tgui::Slider::*)(const gui::Layout2d&)>(
                    &tgui::Slider::setSize),
                static_cast<void (tgui::Slider::*)(gui::Layout, gui::Layout)>(
                    &tgui::Slider::setSize));
        bindSlider["getFullSize"] = &tgui::Slider::getFullSize;
        bindSlider["getWidgetOffset"] = &tgui::Slider::getWidgetOffset;
        bindSlider["setMinimum"] = &tgui::Slider::setMinimum;
        bindSlider["getMinimum"] = &tgui::Slider::getMinimum;
        bindSlider["setMaximum"] = &tgui::Slider::setMaximum;
        bindSlider["getMaximum"] = &tgui::Slider::getMaximum;
        bindSlider["setValue"] = &tgui::Slider::setValue;
        bindSlider["getValue"] = &tgui::Slider::getValue;
        bindSlider["setStep"] = &tgui::Slider::setStep;
        bindSlider["getStep"] = &tgui::Slider::getStep;
        bindSlider["setVerticalScroll"] = &tgui::Slider::setVerticalScroll;
        bindSlider["getVerticalScroll"] = &tgui::Slider::getVerticalScroll;
        bindSlider["setInvertedDirection"] = &tgui::Slider::setInvertedDirection;
        bindSlider["getInvertedDirection"] = &tgui::Slider::getInvertedDirection;
        bindSlider["setChangeValueOnScroll"] = &tgui::Slider::setChangeValueOnScroll;
        bindSlider["getChangeValueOnScroll"] = &tgui::Slider::getChangeValueOnScroll;
        bindSlider["isMouseOnWidget"] = &tgui::Slider::isMouseOnWidget;
        bindSlider["leftMousePressed"] = &tgui::Slider::leftMousePressed;
        bindSlider["leftMouseReleased"] = &tgui::Slider::leftMouseReleased;
        bindSlider["mouseMoved"] = &tgui::Slider::mouseMoved;
        bindSlider["mouseWheelScrolled"] = &tgui::Slider::mouseWheelScrolled;
        bindSlider["leftMouseButtonNoLongerDown"]
            = &tgui::Slider::leftMouseButtonNoLongerDown;
        bindSlider["draw"] = &tgui::Slider::draw;
        bindSlider["create"] = sol::overload(
            [](tgui::Slider* self) -> gui::Slider1a1140cd200a988fa36d7c8112e7ce1a6c {
                return self->create();
            },
            [](tgui::Slider* self,
                float minimum) -> gui::Slider1a1140cd200a988fa36d7c8112e7ce1a6c {
                return self->create(minimum);
            },
            [](tgui::Slider* self, float minimum,
                float maximum) -> gui::Slider1a1140cd200a988fa36d7c8112e7ce1a6c {
                return self->create(minimum, maximum);
            });
        bindSlider["copy"] = &tgui::Slider::copy;
        bindSlider["onValueChange"] = &tgui::Slider::onValueChange;
    }
    void LoadClassSliderRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SliderRenderer> bindSliderRenderer
            = tguiNamespace.new_usertype<tgui::SliderRenderer>("SliderRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindSliderRenderer["setBorders"] = &tgui::SliderRenderer::setBorders;
        bindSliderRenderer["getBorders"] = &tgui::SliderRenderer::getBorders;
        bindSliderRenderer["setTrackColor"] = &tgui::SliderRenderer::setTrackColor;
        bindSliderRenderer["getTrackColor"] = &tgui::SliderRenderer::getTrackColor;
        bindSliderRenderer["setTrackColorHover"]
            = &tgui::SliderRenderer::setTrackColorHover;
        bindSliderRenderer["getTrackColorHover"]
            = &tgui::SliderRenderer::getTrackColorHover;
        bindSliderRenderer["setThumbColor"] = &tgui::SliderRenderer::setThumbColor;
        bindSliderRenderer["getThumbColor"] = &tgui::SliderRenderer::getThumbColor;
        bindSliderRenderer["setThumbColorHover"]
            = &tgui::SliderRenderer::setThumbColorHover;
        bindSliderRenderer["getThumbColorHover"]
            = &tgui::SliderRenderer::getThumbColorHover;
        bindSliderRenderer["setBorderColor"] = &tgui::SliderRenderer::setBorderColor;
        bindSliderRenderer["getBorderColor"] = &tgui::SliderRenderer::getBorderColor;
        bindSliderRenderer["setBorderColorHover"]
            = &tgui::SliderRenderer::setBorderColorHover;
        bindSliderRenderer["getBorderColorHover"]
            = &tgui::SliderRenderer::getBorderColorHover;
        bindSliderRenderer["setTextureTrack"] = &tgui::SliderRenderer::setTextureTrack;
        bindSliderRenderer["getTextureTrack"] = &tgui::SliderRenderer::getTextureTrack;
        bindSliderRenderer["setTextureTrackHover"]
            = &tgui::SliderRenderer::setTextureTrackHover;
        bindSliderRenderer["getTextureTrackHover"]
            = &tgui::SliderRenderer::getTextureTrackHover;
        bindSliderRenderer["setTextureThumb"] = &tgui::SliderRenderer::setTextureThumb;
        bindSliderRenderer["getTextureThumb"] = &tgui::SliderRenderer::getTextureThumb;
        bindSliderRenderer["setTextureThumbHover"]
            = &tgui::SliderRenderer::setTextureThumbHover;
        bindSliderRenderer["getTextureThumbHover"]
            = &tgui::SliderRenderer::getTextureThumbHover;
        bindSliderRenderer["setThumbWithinTrack"]
            = &tgui::SliderRenderer::setThumbWithinTrack;
        bindSliderRenderer["getThumbWithinTrack"]
            = &tgui::SliderRenderer::getThumbWithinTrack;
        bindSliderRenderer["WidgetRenderer"]
            = sol::overload(static_cast<(tgui::SliderRenderer::*)()>(
                                &tgui::SliderRenderer::WidgetRenderer),
                static_cast<(
                    tgui::SliderRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                    &tgui::SliderRenderer::WidgetRenderer));
    }
    void LoadClassSpinButton(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SpinButton> bindSpinButton
            = tguiNamespace.new_usertype<tgui::SpinButton>("SpinButton",
                sol::call_constructor,
                sol::constructors<tgui::SpinButton(), tgui::SpinButton(const char*),
                    tgui::SpinButton(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindSpinButton["getSharedRenderer"]
            = sol::overload(static_cast<gui::SpinButtonRenderer* (tgui::SpinButton::*)()>(
                                &tgui::SpinButton::getSharedRenderer),
                static_cast<const gui::SpinButtonRenderer* (tgui::SpinButton::*)() const>(
                    &tgui::SpinButton::getSharedRenderer));
        bindSpinButton["getRenderer"]
            = sol::overload(static_cast<gui::SpinButtonRenderer* (tgui::SpinButton::*)()>(
                                &tgui::SpinButton::getRenderer),
                static_cast<const gui::SpinButtonRenderer* (tgui::SpinButton::*)() const>(
                    &tgui::SpinButton::getRenderer));
        bindSpinButton["setSize"]
            = sol::overload(static_cast<void (tgui::SpinButton::*)(const gui::Layout2d&)>(
                                &tgui::SpinButton::setSize),
                static_cast<void (tgui::SpinButton::*)(const gui::Layout2d&)>(
                    &tgui::SpinButton::setSize),
                static_cast<void (tgui::SpinButton::*)(gui::Layout, gui::Layout)>(
                    &tgui::SpinButton::setSize));
        bindSpinButton["setMinimum"] = &tgui::SpinButton::setMinimum;
        bindSpinButton["getMinimum"] = &tgui::SpinButton::getMinimum;
        bindSpinButton["setMaximum"] = &tgui::SpinButton::setMaximum;
        bindSpinButton["getMaximum"] = &tgui::SpinButton::getMaximum;
        bindSpinButton["setValue"] = &tgui::SpinButton::setValue;
        bindSpinButton["getValue"] = &tgui::SpinButton::getValue;
        bindSpinButton["setStep"] = &tgui::SpinButton::setStep;
        bindSpinButton["getStep"] = &tgui::SpinButton::getStep;
        bindSpinButton["setVerticalScroll"] = &tgui::SpinButton::setVerticalScroll;
        bindSpinButton["getVerticalScroll"] = &tgui::SpinButton::getVerticalScroll;
        bindSpinButton["leftMousePressed"] = &tgui::SpinButton::leftMousePressed;
        bindSpinButton["leftMouseReleased"] = &tgui::SpinButton::leftMouseReleased;
        bindSpinButton["mouseMoved"] = &tgui::SpinButton::mouseMoved;
        bindSpinButton["draw"] = &tgui::SpinButton::draw;
        bindSpinButton["create"] = sol::overload(
            [](tgui::SpinButton* self)
                -> gui::SpinButton1a2b70e7b4ef4b47eac18f6d049d1c19d3 {
                return self->create();
            },
            [](tgui::SpinButton* self,
                float minimum) -> gui::SpinButton1a2b70e7b4ef4b47eac18f6d049d1c19d3 {
                return self->create(minimum);
            },
            [](tgui::SpinButton* self, float minimum,
                float maximum) -> gui::SpinButton1a2b70e7b4ef4b47eac18f6d049d1c19d3 {
                return self->create(minimum, maximum);
            });
        bindSpinButton["copy"] = &tgui::SpinButton::copy;
        bindSpinButton["onValueChange"] = &tgui::SpinButton::onValueChange;
    }
    void LoadClassSpinButtonRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SpinButtonRenderer> bindSpinButtonRenderer
            = tguiNamespace.new_usertype<tgui::SpinButtonRenderer>("SpinButtonRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindSpinButtonRenderer["setBorders"] = &tgui::SpinButtonRenderer::setBorders;
        bindSpinButtonRenderer["getBorders"] = &tgui::SpinButtonRenderer::getBorders;
        bindSpinButtonRenderer["setBorderBetweenArrows"]
            = &tgui::SpinButtonRenderer::setBorderBetweenArrows;
        bindSpinButtonRenderer["getBorderBetweenArrows"]
            = &tgui::SpinButtonRenderer::getBorderBetweenArrows;
        bindSpinButtonRenderer["setBackgroundColor"]
            = &tgui::SpinButtonRenderer::setBackgroundColor;
        bindSpinButtonRenderer["getBackgroundColor"]
            = &tgui::SpinButtonRenderer::getBackgroundColor;
        bindSpinButtonRenderer["setBackgroundColorHover"]
            = &tgui::SpinButtonRenderer::setBackgroundColorHover;
        bindSpinButtonRenderer["getBackgroundColorHover"]
            = &tgui::SpinButtonRenderer::getBackgroundColorHover;
        bindSpinButtonRenderer["setArrowColor"]
            = &tgui::SpinButtonRenderer::setArrowColor;
        bindSpinButtonRenderer["getArrowColor"]
            = &tgui::SpinButtonRenderer::getArrowColor;
        bindSpinButtonRenderer["setArrowColorHover"]
            = &tgui::SpinButtonRenderer::setArrowColorHover;
        bindSpinButtonRenderer["getArrowColorHover"]
            = &tgui::SpinButtonRenderer::getArrowColorHover;
        bindSpinButtonRenderer["setBorderColor"]
            = &tgui::SpinButtonRenderer::setBorderColor;
        bindSpinButtonRenderer["getBorderColor"]
            = &tgui::SpinButtonRenderer::getBorderColor;
        bindSpinButtonRenderer["setTextureArrowUp"]
            = &tgui::SpinButtonRenderer::setTextureArrowUp;
        bindSpinButtonRenderer["getTextureArrowUp"]
            = &tgui::SpinButtonRenderer::getTextureArrowUp;
        bindSpinButtonRenderer["setTextureArrowUpHover"]
            = &tgui::SpinButtonRenderer::setTextureArrowUpHover;
        bindSpinButtonRenderer["getTextureArrowUpHover"]
            = &tgui::SpinButtonRenderer::getTextureArrowUpHover;
        bindSpinButtonRenderer["setTextureArrowDown"]
            = &tgui::SpinButtonRenderer::setTextureArrowDown;
        bindSpinButtonRenderer["getTextureArrowDown"]
            = &tgui::SpinButtonRenderer::getTextureArrowDown;
        bindSpinButtonRenderer["setTextureArrowDownHover"]
            = &tgui::SpinButtonRenderer::setTextureArrowDownHover;
        bindSpinButtonRenderer["getTextureArrowDownHover"]
            = &tgui::SpinButtonRenderer::getTextureArrowDownHover;
        bindSpinButtonRenderer["WidgetRenderer"] = sol::overload(
            static_cast<(tgui::SpinButtonRenderer::*)()>(
                &tgui::SpinButtonRenderer::WidgetRenderer),
            static_cast<(
                tgui::SpinButtonRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                &tgui::SpinButtonRenderer::WidgetRenderer));
    }
    void LoadClassSpinControl(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SpinControl> bindSpinControl
            = tguiNamespace.new_usertype<tgui::SpinControl>("SpinControl",
                sol::call_constructor,
                sol::constructors<tgui::SpinControl(), tgui::SpinControl(const char*),
                    tgui::SpinControl(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::SubwidgetContainer, tgui::Widget>());
        bindSpinControl["getSpinButtonSharedRenderer"] = sol::overload(
            static_cast<gui::SpinButtonRenderer* (tgui::SpinControl::*)()>(
                &tgui::SpinControl::getSpinButtonSharedRenderer),
            static_cast<const gui::SpinButtonRenderer* (tgui::SpinControl::*)() const>(
                &tgui::SpinControl::getSpinButtonSharedRenderer));
        bindSpinControl["getSpinButtonRenderer"] = sol::overload(
            static_cast<gui::SpinButtonRenderer* (tgui::SpinControl::*)()>(
                &tgui::SpinControl::getSpinButtonRenderer),
            static_cast<const gui::SpinButtonRenderer* (tgui::SpinControl::*)() const>(
                &tgui::SpinControl::getSpinButtonRenderer));
        bindSpinControl["getSpinTextSharedRenderer"]
            = sol::overload(static_cast<gui::EditBoxRenderer* (tgui::SpinControl::*)()>(
                                &tgui::SpinControl::getSpinTextSharedRenderer),
                static_cast<const gui::EditBoxRenderer* (tgui::SpinControl::*)() const>(
                    &tgui::SpinControl::getSpinTextSharedRenderer));
        bindSpinControl["getSpinTextRenderer"]
            = sol::overload(static_cast<gui::EditBoxRenderer* (tgui::SpinControl::*)()>(
                                &tgui::SpinControl::getSpinTextRenderer),
                static_cast<const gui::EditBoxRenderer* (tgui::SpinControl::*)() const>(
                    &tgui::SpinControl::getSpinTextRenderer));
        bindSpinControl["setSize"] = sol::overload(
            static_cast<void (tgui::SpinControl::*)(const gui::Layout2d&)>(
                &tgui::SpinControl::setSize),
            static_cast<void (tgui::SpinControl::*)(const gui::Layout2d&)>(
                &tgui::SpinControl::setSize),
            static_cast<void (tgui::SpinControl::*)(const gui::Layout2d&)>(
                &tgui::SpinControl::setSize),
            static_cast<void (tgui::SpinControl::*)(gui::Layout, gui::Layout)>(
                &tgui::SpinControl::setSize));
        bindSpinControl["setMinimum"] = &tgui::SpinControl::setMinimum;
        bindSpinControl["getMinimum"] = &tgui::SpinControl::getMinimum;
        bindSpinControl["setMaximum"] = &tgui::SpinControl::setMaximum;
        bindSpinControl["getMaximum"] = &tgui::SpinControl::getMaximum;
        bindSpinControl["setValue"] = &tgui::SpinControl::setValue;
        bindSpinControl["getValue"] = &tgui::SpinControl::getValue;
        bindSpinControl["setStep"] = &tgui::SpinControl::setStep;
        bindSpinControl["getStep"] = &tgui::SpinControl::getStep;
        bindSpinControl["setDecimalPlaces"] = &tgui::SpinControl::setDecimalPlaces;
        bindSpinControl["getDecimalPlaces"] = &tgui::SpinControl::getDecimalPlaces;
        bindSpinControl["create"] = sol::overload(
            [](tgui::SpinControl* self)
                -> gui::SpinControl1acff6d753b3d19aa4c0777368f3f58d69 {
                return self->create();
            },
            [](tgui::SpinControl* self,
                float min) -> gui::SpinControl1acff6d753b3d19aa4c0777368f3f58d69 {
                return self->create(min);
            },
            [](tgui::SpinControl* self, float min,
                float max) -> gui::SpinControl1acff6d753b3d19aa4c0777368f3f58d69 {
                return self->create(min, max);
            },
            [](tgui::SpinControl* self, float min, float max,
                float value) -> gui::SpinControl1acff6d753b3d19aa4c0777368f3f58d69 {
                return self->create(min, max, value);
            },
            [](tgui::SpinControl* self, float min, float max, float value,
                unsigned int decimal)
                -> gui::SpinControl1acff6d753b3d19aa4c0777368f3f58d69 {
                return self->create(min, max, value, decimal);
            },
            [](tgui::SpinControl* self, float min, float max, float value,
                unsigned int decimal,
                float step) -> gui::SpinControl1acff6d753b3d19aa4c0777368f3f58d69 {
                return self->create(min, max, value, decimal, step);
            });
        bindSpinControl["copy"] = &tgui::SpinControl::copy;
        bindSpinControl["onValueChange"] = &tgui::SpinControl::onValueChange;
    }
    void LoadClassSprite(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Sprite> bindSprite
            = tguiNamespace.new_usertype<tgui::Sprite>("Sprite", sol::call_constructor,
                sol::constructors<tgui::Sprite(), tgui::Sprite(const gui::Texture&),
                    tgui::Sprite(const gui::Sprite&), tgui::Sprite(gui::Sprite &&)>());
        bindSprite["operator="] = sol::overload(
            static_cast<gui::Sprite& (tgui::Sprite::*)(const gui::Sprite&)>(
                &tgui::Sprite::operator=),
            static_cast<gui::Sprite& (tgui::Sprite::*)(gui::Sprite &&)>(
                &tgui::Sprite::operator=));
        bindSprite["setTexture"] = &tgui::Sprite::setTexture;
        bindSprite["getTexture"] = &tgui::Sprite::getTexture;
        bindSprite["isSet"] = &tgui::Sprite::isSet;
        bindSprite["setSize"] = &tgui::Sprite::setSize;
        bindSprite["getSize"] = &tgui::Sprite::getSize;
        bindSprite["setOpacity"] = &tgui::Sprite::setOpacity;
        bindSprite["getOpacity"] = &tgui::Sprite::getOpacity;
        bindSprite["setVisibleRect"] = &tgui::Sprite::setVisibleRect;
        bindSprite["getVisibleRect"] = &tgui::Sprite::getVisibleRect;
        bindSprite["setPosition"] = &tgui::Sprite::setPosition;
        bindSprite["getPosition"] = &tgui::Sprite::getPosition;
        bindSprite["setRotation"] = &tgui::Sprite::setRotation;
        bindSprite["getRotation"] = &tgui::Sprite::getRotation;
        bindSprite["isTransparentPixel"] = &tgui::Sprite::isTransparentPixel;
        bindSprite["getScalingType"] = &tgui::Sprite::getScalingType;
        bindSprite["getSvgTexture"] = &tgui::Sprite::getSvgTexture;
        bindSprite["getVertices"] = &tgui::Sprite::getVertices;
        bindSprite["getIndices"] = &tgui::Sprite::getIndices;
    }
    void LoadClassString(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::String> bindString = tguiNamespace.new_usertype<tgui::String>(
            "String", sol::call_constructor,
            sol::constructors<tgui::String(), tgui::String(const std::string&),
                tgui::String(const std::wstring&), tgui::String(const std::u16string&),
                tgui::String(const std::u32string&), tgui::String(std::u32string &&),
                tgui::String(char), tgui::String(wchar_t), tgui::String(char16_t),
                tgui::String(char32_t), tgui::String(const char*),
                tgui::String(const wchar_t*), tgui::String(const char16_t*),
                tgui::String(const char32_t*), tgui::String(T),
                tgui::String(std::size_t, char), tgui::String(std::size_t, wchar_t),
                tgui::String(std::size_t, char16_t), tgui::String(std::size_t, char32_t),
                tgui::String(const std::string&, std::size_t),
                tgui::String(const std::wstring&, std::size_t),
                tgui::String(const std::u16string&, std::size_t),
                tgui::String(const std::u32string&, std::size_t),
                tgui::String(const std::string&, std::size_t, std::size_t),
                tgui::String(const std::wstring&, std::size_t, std::size_t),
                tgui::String(const std::u16string&, std::size_t, std::size_t),
                tgui::String(const std::u32string&, std::size_t, std::size_t),
                tgui::String(const char*, std::size_t),
                tgui::String(const wchar_t*, std::size_t),
                tgui::String(const char16_t*, std::size_t),
                tgui::String(const char32_t*, std::size_t),
                tgui::String(std::initializer_list<char>),
                tgui::String(std::initializer_list<wchar_t>),
                tgui::String(std::initializer_list<char16_t>),
                tgui::String(std::initializer_list<char32_t>),
                tgui::String(std::string::const_iterator, std::string::const_iterator),
                tgui::String(std::wstring::const_iterator, std::wstring::const_iterator),
                tgui::String(
                    std::u16string::const_iterator, std::u16string::const_iterator),
                tgui::String(
                    std::u32string::const_iterator, std::u32string::const_iterator)>());
        bindString["attemptToInt"] = &tgui::String::attemptToInt;
        bindString["attemptToUInt"] = &tgui::String::attemptToUInt;
        bindString["attemptToFloat"] = &tgui::String::attemptToFloat;
        bindString["toInt"]
            = sol::overload([](tgui::String* self) -> int { return self->toInt(); },
                [](tgui::String* self, int defaultValue) -> int {
                    return self->toInt(defaultValue);
                });
        bindString["toUInt"] = sol::overload(
            [](tgui::String* self) -> unsigned int { return self->toUInt(); },
            [](tgui::String* self, unsigned int defaultValue) -> unsigned int {
                return self->toUInt(defaultValue);
            });
        bindString["toFloat"]
            = sol::overload([](tgui::String* self) -> float { return self->toFloat(); },
                [](tgui::String* self, float defaultValue) -> float {
                    return self->toFloat(defaultValue);
                });
        bindString["trim"] = &tgui::String::trim;
        bindString["toLower"] = &tgui::String::toLower;
        bindString["toUpper"] = &tgui::String::toUpper;
        bindString["equalIgnoreCase"] = &tgui::String::equalIgnoreCase;
        bindString["startsWith"] = &tgui::String::startsWith;
        bindString["endsWith"] = &tgui::String::endsWith;
        bindString["replace"] = sol::overload(
            static_cast<gui::String& (tgui::String::*)(const gui::String&,
                const gui::String&)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::string&)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::wstring&)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::u16string&)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::u32string&)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const gui::String&)>(&tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, const std::string&)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, const std::wstring&)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, const std::u16string&)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, const std::u32string&)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, const gui::String&)>(
                &tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::string&, std::size_t, std::size_t)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::wstring&, std::size_t, std::size_t)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::u16string&, std::size_t, std::size_t)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::u32string&, std::size_t, std::size_t)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const gui::String&, std::size_t, std::size_t)>(&tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::string::const_iterator, std::string::const_iterator)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::wstring::const_iterator, std::wstring::const_iterator)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::u16string::const_iterator, std::u16string::const_iterator)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::u32string::const_iterator, std::u32string::const_iterator)>(
                &tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const char*, std::size_t)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const wchar_t*, std::size_t)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const char16_t*, std::size_t)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const char32_t*, std::size_t)>(&tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, const char*, std::size_t)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, const wchar_t*,
                std::size_t)>(&tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, const char16_t*,
                std::size_t)>(&tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, const char32_t*,
                std::size_t)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const char*)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const wchar_t*)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const char16_t*)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                const char32_t*)>(&tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, const char*)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, const wchar_t*)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, const char16_t*)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, const char32_t*)>(
                &tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                std::size_t, char)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                std::size_t, wchar_t)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                std::size_t, char16_t)>(&tgui::String::replace),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                std::size_t, char32_t)>(&tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, std::size_t, char)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, std::size_t, wchar_t)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, std::size_t, char16_t)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, std::size_t, char32_t)>(
                &tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::initializer_list<char>)>(&tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::initializer_list<wchar_t>)>(&tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::initializer_list<char16_t>)>(&tgui::String::replace),
            static_cast<gui::String& (
                tgui::String::*)(gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::initializer_list<char32_t>)>(&tgui::String::replace));
        bindString["split"] = &tgui::String::split;
        bindString["operator std::string"] = &tgui::String::operator std::string;
        bindString["operator std::wstring"] = &tgui::String::operator std::wstring;
        bindString["operator std::u16string"] = &tgui::String::operator std::u16string;
        bindString["operator const std::u32string &"]
            = &tgui::String::operator const std::u32string&;
        bindString["toStdString"] = &tgui::String::toStdString;
        bindString["toWideString"] = &tgui::String::toWideString;
        bindString["toUtf16"] = &tgui::String::toUtf16;
        bindString["toUtf32"] = &tgui::String::toUtf32;
        bindString["assign"] = sol::overload(
            static_cast<TGUI_DEPRECATED(
                "Use gui::String1a890be14e25071dc8524db293f10003efinstead")
                    stdgui::String& (tgui::String::*)(std::size_t, wchar_t)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::size_t, char16_t)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::size_t, char32_t)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const std::string&)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const std::wstring&)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const std::u16string&)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const std::u32string&)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const gui::String&)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const std::string&, std::size_t,
                std::size_t)>(&tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const std::wstring&, std::size_t,
                std::size_t)>(&tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const std::u16string&, std::size_t,
                std::size_t)>(&tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const std::u32string&, std::size_t,
                std::size_t)>(&tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const gui::String&, std::size_t,
                std::size_t)>(&tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::string &&)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::wstring &&)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::u16string &&)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::u32string &&)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(gui::String &&)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const char*, std::size_t)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const wchar_t*, std::size_t)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const char16_t*, std::size_t)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const char32_t*, std::size_t)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const char*)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const wchar_t*)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const char16_t*)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(const char32_t*)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::initializer_list<char>)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::initializer_list<wchar_t>)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::initializer_list<char16_t>)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::initializer_list<char32_t>)>(
                &tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::string::const_iterator,
                std::string::const_iterator)>(&tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::wstring::const_iterator,
                std::wstring::const_iterator)>(&tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::u16string::const_iterator,
                std::u16string::const_iterator)>(&tgui::String::assign),
            static_cast<gui::String& (tgui::String::*)(std::u32string::const_iterator,
                std::u32string::const_iterator)>(&tgui::String::assign));
        bindString["at"]
            = sol::overload(static_cast<gui::String1ae089b07ea1098dc02789dd20dea719fb (
                                tgui::String::*)(std::size_t)>(&tgui::String::at),
                static_cast<gui::String1a7ecca1e5d6acb8b7b78e589043d358f3 (
                    tgui::String::*)(std::size_t) const>(&tgui::String::at));
        bindString[sol::meta_function::index] = sol::overload(
            static_cast<gui::String1a7ecca1e5d6acb8b7b78e589043d358f3 (tgui::String::*)(
                std::size_t) const>(&tgui::String::operator[]),
            static_cast<gui::String1ae089b07ea1098dc02789dd20dea719fb (tgui::String::*)(
                std::size_t)>(&tgui::String::operator[]));
        bindString["front"]
            = sol::overload(static_cast<gui::String1ae089b07ea1098dc02789dd20dea719fb (
                                tgui::String::*)()>(&tgui::String::front),
                static_cast<gui::String1a7ecca1e5d6acb8b7b78e589043d358f3 (
                    tgui::String::*)() const>(&tgui::String::front));
        bindString["back"]
            = sol::overload(static_cast<gui::String1ae089b07ea1098dc02789dd20dea719fb (
                                tgui::String::*)()>(&tgui::String::back),
                static_cast<gui::String1a7ecca1e5d6acb8b7b78e589043d358f3 (
                    tgui::String::*)() const>(&tgui::String::back));
        bindString["data"] = &tgui::String::data;
        bindString["c_str"] = &tgui::String::c_str;
        bindString["begin"]
            = sol::overload(static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (
                                tgui::String::*)()>(&tgui::String::begin),
                static_cast<gui::String1acfe563f3cd6fc319c139d13ae1bb2212 (
                    tgui::String::*)() const>(&tgui::String::begin));
        bindString["cbegin"] = &tgui::String::cbegin;
        bindString["end"]
            = sol::overload(static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (
                                tgui::String::*)()>(&tgui::String::end),
                static_cast<gui::String1acfe563f3cd6fc319c139d13ae1bb2212 (
                    tgui::String::*)() const>(&tgui::String::end));
        bindString["cend"] = &tgui::String::cend;
        bindString["rbegin"]
            = sol::overload(static_cast<gui::String1a692420f5a2c8e2d83fa9e76d0cbf0398 (
                                tgui::String::*)()>(&tgui::String::rbegin),
                static_cast<gui::String1a337383ace5062a187bd63fe2f5ed2711 (
                    tgui::String::*)() const>(&tgui::String::rbegin));
        bindString["crbegin"] = &tgui::String::crbegin;
        bindString["rend"]
            = sol::overload(static_cast<gui::String1a692420f5a2c8e2d83fa9e76d0cbf0398 (
                                tgui::String::*)()>(&tgui::String::rend),
                static_cast<gui::String1a337383ace5062a187bd63fe2f5ed2711 (
                    tgui::String::*)() const>(&tgui::String::rend));
        bindString["crend"] = &tgui::String::crend;
        bindString["empty"] = &tgui::String::empty;
        bindString["size"] = &tgui::String::size;
        bindString["length"] = &tgui::String::length;
        bindString["max_size"] = &tgui::String::max_size;
        bindString["reserve"] = &tgui::String::reserve;
        bindString["capacity"] = &tgui::String::capacity;
        bindString["shrink_to_fit"] = &tgui::String::shrink_to_fit;
        bindString["clear"] = &tgui::String::clear;
        bindString["insert"] = sol::overload(
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t, char)>(
                &tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                wchar_t)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                char16_t)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t,
                char32_t)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const std::string&)>(
                &tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const std::wstring&)>(
                &tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t,
                const std::u16string&)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t,
                const std::u32string&)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const gui::String&)>(
                &tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const std::string&,
                std::size_t, std::size_t)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const std::wstring&,
                std::size_t, std::size_t)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const std::u16string&,
                std::size_t, std::size_t)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const std::u32string&,
                std::size_t, std::size_t)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const gui::String&,
                std::size_t, std::size_t)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const char*,
                std::size_t)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const wchar_t*,
                std::size_t)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const char16_t*,
                std::size_t)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const char32_t*,
                std::size_t)>(&tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const char*)>(
                &tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const wchar_t*)>(
                &tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const char16_t*)>(
                &tgui::String::insert),
            static_cast<gui::String& (tgui::String::*)(std::size_t, const char32_t*)>(
                &tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, char)>(
                &tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, wchar_t)>(
                &tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, char16_t)>(
                &tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, char32_t)>(
                &tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, std::size_t, char)>(
                &tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, std::size_t, wchar_t)>(
                &tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, std::size_t, char16_t)>(
                &tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212, std::size_t, char32_t)>(
                &tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::initializer_list<char>)>(&tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::initializer_list<wchar_t>)>(&tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::initializer_list<char16_t>)>(&tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::initializer_list<char32_t>)>(&tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::string::const_iterator, std::string::const_iterator)>(
                &tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::wstring::const_iterator, std::wstring::const_iterator)>(
                &tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::u16string::const_iterator, std::u16string::const_iterator)>(
                &tgui::String::insert),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                std::u32string::const_iterator, std::u32string::const_iterator)>(
                &tgui::String::insert));
        bindString["erase"] = sol::overload(
            static_cast<gui::String& (tgui::String::*)(std::size_t, std::size_t)>(
                &tgui::String::erase),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212)>(&tgui::String::erase),
            static_cast<gui::String1a9830990fac5d72fffc4999320d3b98d9 (tgui::String::*)(
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212,
                gui::String1acfe563f3cd6fc319c139d13ae1bb2212)>(&tgui::String::erase));
        bindString["push_back"] = sol::overload(
            static_cast<void (tgui::String::*)(char)>(&tgui::String::push_back),
            static_cast<void (tgui::String::*)(wchar_t)>(&tgui::String::push_back),
            static_cast<void (tgui::String::*)(char16_t)>(&tgui::String::push_back),
            static_cast<void (tgui::String::*)(char32_t)>(&tgui::String::push_back));
        bindString["pop_back"] = &tgui::String::pop_back;
        bindString["append"] = sol::overload(
            static_cast<gui::String& (tgui::String::*)(std::size_t, char)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(std::size_t, wchar_t)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(std::size_t, char16_t)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(std::size_t, char32_t)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const std::string&)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const std::wstring&)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const std::u16string&)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const std::u32string&)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const gui::String&)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const std::string&, std::size_t,
                std::size_t)>(&tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const std::wstring&, std::size_t,
                std::size_t)>(&tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const std::u16string&, std::size_t,
                std::size_t)>(&tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const std::u32string&, std::size_t,
                std::size_t)>(&tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const gui::String&, std::size_t,
                std::size_t)>(&tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const char*, std::size_t)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const wchar_t*, std::size_t)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const char16_t*, std::size_t)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const char32_t*, std::size_t)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const char*)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const wchar_t*)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const char16_t*)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(const char32_t*)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(std::string::const_iterator,
                std::string::const_iterator)>(&tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(std::wstring::const_iterator,
                std::wstring::const_iterator)>(&tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(std::u16string::const_iterator,
                std::u16string::const_iterator)>(&tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(std::u32string::const_iterator,
                std::u32string::const_iterator)>(&tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(std::initializer_list<char>)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(std::initializer_list<wchar_t>)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(std::initializer_list<char16_t>)>(
                &tgui::String::append),
            static_cast<gui::String& (tgui::String::*)(std::initializer_list<char32_t>)>(
                &tgui::String::append));
        bindString["compare"] = sol::overload(
            static_cast<int (tgui::String::*)(const std::string&) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const std::wstring&) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const std::u16string&) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const std::u32string&) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const gui::String&) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::string&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::wstring&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::u16string&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::u32string&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const gui::String&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::string&, std::size_t, std::size_t) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::wstring&, std::size_t, std::size_t) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::u16string&, std::size_t, std::size_t) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::u32string&, std::size_t, std::size_t) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const gui::String&, std::size_t, std::size_t) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const char*) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(const wchar_t*) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const char16_t*) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const char32_t*) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char*)
                    const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const wchar_t*)
                    const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char16_t*)
                    const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char32_t*)
                    const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char*,
                std::size_t) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const wchar_t*,
                std::size_t) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char16_t*,
                std::size_t) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char32_t*,
                std::size_t) const>(&tgui::String::compare));
        bindString["substr"] = sol::overload(
            [](tgui::String* self) -> gui::String { return self->substr(); },
            [](tgui::String* self, std::size_t pos) -> gui::String {
                return self->substr(pos);
            },
            [](tgui::String* self, std::size_t pos, std::size_t count) -> gui::String {
                return self->substr(pos, count);
            });
        bindString["copy"] = sol::overload(
            [](tgui::String* self, char32_t* dest, std::size_t count) -> std::size_t {
                return self->copy(dest, count);
            },
            [](tgui::String* self, char32_t* dest, std::size_t count,
                std::size_t pos) -> std::size_t { return self->copy(dest, count, pos); });
        bindString["resize"] = sol::overload(
            static_cast<void (tgui::String::*)(std::size_t)>(&tgui::String::resize),
            static_cast<void (tgui::String::*)(std::size_t, char)>(&tgui::String::resize),
            static_cast<void (tgui::String::*)(std::size_t, wchar_t)>(
                &tgui::String::resize),
            static_cast<void (tgui::String::*)(std::size_t, char16_t)>(
                &tgui::String::resize),
            static_cast<void (tgui::String::*)(std::size_t, char32_t)>(
                &tgui::String::resize));
        bindString["swap"] = &tgui::String::swap;
        bindString["find"] = sol::overload(
            static_cast<std::size_t (tgui::String::*)(const std::string&, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const std::wstring&, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const std::u16string&, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const std::u32string&, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const gui::String&, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(
                const char*, std::size_t, std::size_t) const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(
                const wchar_t*, std::size_t, std::size_t) const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(
                const char16_t*, std::size_t, std::size_t) const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(
                const char32_t*, std::size_t, std::size_t) const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t) const>(
                &tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t) const>(
                &tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(char, std::size_t) const>(
                &tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(wchar_t, std::size_t) const>(
                &tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(char16_t, std::size_t) const>(
                &tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(char32_t, std::size_t) const>(
                &tgui::String::find));
        bindString["find_first_of"] = sol::overload(
            static_cast<std::size_t (tgui::String::*)(const std::string&, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const std::wstring&, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const std::u16string&, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const std::u32string&, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const gui::String&, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t) const>(
                &tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t) const>(
                &tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(char, std::size_t) const>(
                &tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(wchar_t, std::size_t) const>(
                &tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(char16_t, std::size_t) const>(
                &tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(char32_t, std::size_t) const>(
                &tgui::String::find_first_of));
        bindString["find_first_not_of"] = sol::overload(
            static_cast<std::size_t (tgui::String::*)(const std::string&, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const std::wstring&, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const std::u16string&, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const std::u32string&, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const gui::String&, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t) const>(
                &tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t) const>(
                &tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(char, std::size_t) const>(
                &tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(wchar_t, std::size_t) const>(
                &tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(char16_t, std::size_t) const>(
                &tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(char32_t, std::size_t) const>(
                &tgui::String::find_first_not_of));
        bindString["rfind"] = sol::overload(
            static_cast<std::size_t (tgui::String::*)(const std::string&, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const std::wstring&, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const std::u16string&, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const std::u32string&, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const gui::String&, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(
                const char*, std::size_t, std::size_t) const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(
                const wchar_t*, std::size_t, std::size_t) const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(
                const char16_t*, std::size_t, std::size_t) const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(
                const char32_t*, std::size_t, std::size_t) const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t) const>(
                &tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t) const>(
                &tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(char, std::size_t) const>(
                &tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(wchar_t, std::size_t) const>(
                &tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(char16_t, std::size_t) const>(
                &tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(char32_t, std::size_t) const>(
                &tgui::String::rfind));
        bindString["find_last_of"] = sol::overload(
            static_cast<std::size_t (tgui::String::*)(const std::string&, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const std::wstring&, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const std::u16string&, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const std::u32string&, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const gui::String&, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t) const>(
                &tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t) const>(
                &tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(char, std::size_t) const>(
                &tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(wchar_t, std::size_t) const>(
                &tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(char16_t, std::size_t) const>(
                &tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(char32_t, std::size_t) const>(
                &tgui::String::find_last_of));
        bindString["find_last_not_of"] = sol::overload(
            static_cast<std::size_t (tgui::String::*)(const std::string&, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const std::wstring&, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const std::u16string&, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const std::u32string&, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const gui::String&, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t) const>(
                &tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t) const>(
                &tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(char, std::size_t) const>(
                &tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(wchar_t, std::size_t) const>(
                &tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(char16_t, std::size_t) const>(
                &tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(char32_t, std::size_t) const>(
                &tgui::String::find_last_not_of));
        bindString["join"] = &tgui::String::join;
        bindString["npos"] = sol::var(&tgui::String::npos);
    }
    void LoadClassSubwidgetContainer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SubwidgetContainer> bindSubwidgetContainer
            = tguiNamespace.new_usertype<tgui::SubwidgetContainer>("SubwidgetContainer",
                sol::call_constructor,
                sol::constructors<tgui::SubwidgetContainer(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindSubwidgetContainer["setSize"] = sol::overload(
            static_cast<void (tgui::SubwidgetContainer::*)(const gui::Layout2d&)>(
                &tgui::SubwidgetContainer::setSize),
            static_cast<void (tgui::SubwidgetContainer::*)(const gui::Layout2d&)>(
                &tgui::SubwidgetContainer::setSize),
            static_cast<void (tgui::SubwidgetContainer::*)(gui::Layout, gui::Layout)>(
                &tgui::SubwidgetContainer::setSize));
        bindSubwidgetContainer["setFocused"] = &tgui::SubwidgetContainer::setFocused;
        bindSubwidgetContainer["setTextSize"] = &tgui::SubwidgetContainer::setTextSize;
        bindSubwidgetContainer["getContainer"]
            = sol::overload(static_cast<gui::Container* (tgui::SubwidgetContainer::*)()>(
                                &tgui::SubwidgetContainer::getContainer),
                static_cast<const gui::Container* (tgui::SubwidgetContainer::*)() const>(
                    &tgui::SubwidgetContainer::getContainer));
        bindSubwidgetContainer["leftMousePressed"]
            = &tgui::SubwidgetContainer::leftMousePressed;
        bindSubwidgetContainer["leftMouseReleased"]
            = &tgui::SubwidgetContainer::leftMouseReleased;
        bindSubwidgetContainer["rightMousePressed"]
            = &tgui::SubwidgetContainer::rightMousePressed;
        bindSubwidgetContainer["rightMouseReleased"]
            = &tgui::SubwidgetContainer::rightMouseReleased;
        bindSubwidgetContainer["mouseMoved"] = &tgui::SubwidgetContainer::mouseMoved;
        bindSubwidgetContainer["keyPressed"] = &tgui::SubwidgetContainer::keyPressed;
        bindSubwidgetContainer["textEntered"] = &tgui::SubwidgetContainer::textEntered;
        bindSubwidgetContainer["mouseWheelScrolled"]
            = &tgui::SubwidgetContainer::mouseWheelScrolled;
        bindSubwidgetContainer["mouseNoLongerOnWidget"]
            = &tgui::SubwidgetContainer::mouseNoLongerOnWidget;
        bindSubwidgetContainer["leftMouseButtonNoLongerDown"]
            = &tgui::SubwidgetContainer::leftMouseButtonNoLongerDown;
        bindSubwidgetContainer["rightMouseButtonNoLongerDown"]
            = &tgui::SubwidgetContainer::rightMouseButtonNoLongerDown;
        bindSubwidgetContainer["askToolTip"] = &tgui::SubwidgetContainer::askToolTip;
        bindSubwidgetContainer["updateTime"] = &tgui::SubwidgetContainer::updateTime;
        bindSubwidgetContainer["isMouseOnWidget"]
            = &tgui::SubwidgetContainer::isMouseOnWidget;
        bindSubwidgetContainer["setParent"] = &tgui::SubwidgetContainer::setParent;
    }
    void LoadClassSvgImage(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SvgImage> bindSvgImage
            = tguiNamespace.new_usertype<tgui::SvgImage>("SvgImage",
                sol::call_constructor,
                sol::constructors<tgui::SvgImage(),
                    tgui::SvgImage(const gui::String&)>());
        bindSvgImage["isSet"] = &tgui::SvgImage::isSet;
        bindSvgImage["getSize"] = &tgui::SvgImage::getSize;
        bindSvgImage["rasterize"] = &tgui::SvgImage::rasterize;
    }
    void LoadClassTabs(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Tabs> bindTabs
            = tguiNamespace.new_usertype<tgui::Tabs>("Tabs", sol::call_constructor,
                sol::constructors<tgui::Tabs(), tgui::Tabs(const char*),
                    tgui::Tabs(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindTabs["getSharedRenderer"]
            = sol::overload(static_cast<gui::TabsRenderer* (tgui::Tabs::*)()>(
                                &tgui::Tabs::getSharedRenderer),
                static_cast<const gui::TabsRenderer* (tgui::Tabs::*)() const>(
                    &tgui::Tabs::getSharedRenderer));
        bindTabs["getRenderer"] = sol::overload(
            static_cast<gui::TabsRenderer* (tgui::Tabs::*)()>(&tgui::Tabs::getRenderer),
            static_cast<const gui::TabsRenderer* (tgui::Tabs::*)() const>(
                &tgui::Tabs::getRenderer));
        bindTabs["setSize"] = sol::overload(
            static_cast<void (tgui::Tabs::*)(const gui::Layout2d&)>(&tgui::Tabs::setSize),
            static_cast<void (tgui::Tabs::*)(const gui::Layout2d&)>(&tgui::Tabs::setSize),
            static_cast<void (tgui::Tabs::*)(gui::Layout, gui::Layout)>(
                &tgui::Tabs::setSize));
        bindTabs["setEnabled"] = &tgui::Tabs::setEnabled;
        bindTabs["setAutoSize"] = &tgui::Tabs::setAutoSize;
        bindTabs["getAutoSize"] = &tgui::Tabs::getAutoSize;
        bindTabs["add"] = sol::overload(
            [](tgui::Tabs* self, const gui::String& text) -> std::size_t {
                return self->add(text);
            },
            [](tgui::Tabs* self, const gui::String& text, bool select) -> std::size_t {
                return self->add(text, select);
            });
        bindTabs["insert"] = sol::overload(
            [](tgui::Tabs* self, std::size_t index, const gui::String& text) -> void {
                return self->insert(index, text);
            },
            [](tgui::Tabs* self, std::size_t index, const gui::String& text,
                bool select) -> void { return self->insert(index, text, select); });
        bindTabs["getText"] = &tgui::Tabs::getText;
        bindTabs["changeText"] = &tgui::Tabs::changeText;
        bindTabs["select"] = sol::overload(
            static_cast<bool (tgui::Tabs::*)(const gui::String&)>(&tgui::Tabs::select),
            static_cast<bool (tgui::Tabs::*)(std::size_t)>(&tgui::Tabs::select));
        bindTabs["deselect"] = &tgui::Tabs::deselect;
        bindTabs["remove"] = sol::overload(
            static_cast<bool (tgui::Tabs::*)(const gui::String&)>(&tgui::Tabs::remove),
            static_cast<bool (tgui::Tabs::*)(std::size_t)>(&tgui::Tabs::remove));
        bindTabs["removeAll"] = &tgui::Tabs::removeAll;
        bindTabs["getSelected"] = &tgui::Tabs::getSelected;
        bindTabs["getSelectedIndex"] = &tgui::Tabs::getSelectedIndex;
        bindTabs["setTabVisible"] = &tgui::Tabs::setTabVisible;
        bindTabs["getTabVisible"] = &tgui::Tabs::getTabVisible;
        bindTabs["setTabEnabled"] = &tgui::Tabs::setTabEnabled;
        bindTabs["getTabEnabled"] = &tgui::Tabs::getTabEnabled;
        bindTabs["setTextSize"] = &tgui::Tabs::setTextSize;
        bindTabs["setTabHeight"] = &tgui::Tabs::setTabHeight;
        bindTabs["setMaximumTabWidth"] = &tgui::Tabs::setMaximumTabWidth;
        bindTabs["getMaximumTabWidth"] = &tgui::Tabs::getMaximumTabWidth;
        bindTabs["setMinimumTabWidth"] = &tgui::Tabs::setMinimumTabWidth;
        bindTabs["getMinimumTabWidth"] = &tgui::Tabs::getMinimumTabWidth;
        bindTabs["getTabsCount"] = &tgui::Tabs::getTabsCount;
        bindTabs["isMouseOnWidget"] = &tgui::Tabs::isMouseOnWidget;
        bindTabs["leftMousePressed"] = &tgui::Tabs::leftMousePressed;
        bindTabs["mouseMoved"] = &tgui::Tabs::mouseMoved;
        bindTabs["mouseNoLongerOnWidget"] = &tgui::Tabs::mouseNoLongerOnWidget;
        bindTabs["draw"] = &tgui::Tabs::draw;
        bindTabs["create"] = &tgui::Tabs::create;
        bindTabs["copy"] = &tgui::Tabs::copy;
        bindTabs["onTabSelect"] = &tgui::Tabs::onTabSelect;
    }
    void LoadClassTabsRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TabsRenderer> bindTabsRenderer
            = tguiNamespace.new_usertype<tgui::TabsRenderer>("TabsRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindTabsRenderer["setBorders"] = &tgui::TabsRenderer::setBorders;
        bindTabsRenderer["getBorders"] = &tgui::TabsRenderer::getBorders;
        bindTabsRenderer["setBackgroundColor"] = &tgui::TabsRenderer::setBackgroundColor;
        bindTabsRenderer["getBackgroundColor"] = &tgui::TabsRenderer::getBackgroundColor;
        bindTabsRenderer["setBackgroundColorHover"]
            = &tgui::TabsRenderer::setBackgroundColorHover;
        bindTabsRenderer["getBackgroundColorHover"]
            = &tgui::TabsRenderer::getBackgroundColorHover;
        bindTabsRenderer["setBackgroundColorDisabled"]
            = &tgui::TabsRenderer::setBackgroundColorDisabled;
        bindTabsRenderer["getBackgroundColorDisabled"]
            = &tgui::TabsRenderer::getBackgroundColorDisabled;
        bindTabsRenderer["setSelectedBackgroundColor"]
            = &tgui::TabsRenderer::setSelectedBackgroundColor;
        bindTabsRenderer["getSelectedBackgroundColor"]
            = &tgui::TabsRenderer::getSelectedBackgroundColor;
        bindTabsRenderer["setSelectedBackgroundColorHover"]
            = &tgui::TabsRenderer::setSelectedBackgroundColorHover;
        bindTabsRenderer["getSelectedBackgroundColorHover"]
            = &tgui::TabsRenderer::getSelectedBackgroundColorHover;
        bindTabsRenderer["setTextColor"] = &tgui::TabsRenderer::setTextColor;
        bindTabsRenderer["getTextColor"] = &tgui::TabsRenderer::getTextColor;
        bindTabsRenderer["setTextColorHover"] = &tgui::TabsRenderer::setTextColorHover;
        bindTabsRenderer["getTextColorHover"] = &tgui::TabsRenderer::getTextColorHover;
        bindTabsRenderer["setTextColorDisabled"]
            = &tgui::TabsRenderer::setTextColorDisabled;
        bindTabsRenderer["getTextColorDisabled"]
            = &tgui::TabsRenderer::getTextColorDisabled;
        bindTabsRenderer["setSelectedTextColor"]
            = &tgui::TabsRenderer::setSelectedTextColor;
        bindTabsRenderer["getSelectedTextColor"]
            = &tgui::TabsRenderer::getSelectedTextColor;
        bindTabsRenderer["setSelectedTextColorHover"]
            = &tgui::TabsRenderer::setSelectedTextColorHover;
        bindTabsRenderer["getSelectedTextColorHover"]
            = &tgui::TabsRenderer::getSelectedTextColorHover;
        bindTabsRenderer["setBorderColor"] = &tgui::TabsRenderer::setBorderColor;
        bindTabsRenderer["getBorderColor"] = &tgui::TabsRenderer::getBorderColor;
        bindTabsRenderer["setBorderColorHover"]
            = &tgui::TabsRenderer::setBorderColorHover;
        bindTabsRenderer["getBorderColorHover"]
            = &tgui::TabsRenderer::getBorderColorHover;
        bindTabsRenderer["setSelectedBorderColor"]
            = &tgui::TabsRenderer::setSelectedBorderColor;
        bindTabsRenderer["getSelectedBorderColor"]
            = &tgui::TabsRenderer::getSelectedBorderColor;
        bindTabsRenderer["setSelectedBorderColorHover"]
            = &tgui::TabsRenderer::setSelectedBorderColorHover;
        bindTabsRenderer["getSelectedBorderColorHover"]
            = &tgui::TabsRenderer::getSelectedBorderColorHover;
        bindTabsRenderer["setTextureTab"] = &tgui::TabsRenderer::setTextureTab;
        bindTabsRenderer["getTextureTab"] = &tgui::TabsRenderer::getTextureTab;
        bindTabsRenderer["setTextureTabHover"] = &tgui::TabsRenderer::setTextureTabHover;
        bindTabsRenderer["getTextureTabHover"] = &tgui::TabsRenderer::getTextureTabHover;
        bindTabsRenderer["setTextureSelectedTab"]
            = &tgui::TabsRenderer::setTextureSelectedTab;
        bindTabsRenderer["getTextureSelectedTab"]
            = &tgui::TabsRenderer::getTextureSelectedTab;
        bindTabsRenderer["setTextureSelectedTabHover"]
            = &tgui::TabsRenderer::setTextureSelectedTabHover;
        bindTabsRenderer["getTextureSelectedTabHover"]
            = &tgui::TabsRenderer::getTextureSelectedTabHover;
        bindTabsRenderer["setTextureDisabledTab"]
            = &tgui::TabsRenderer::setTextureDisabledTab;
        bindTabsRenderer["getTextureDisabledTab"]
            = &tgui::TabsRenderer::getTextureDisabledTab;
        bindTabsRenderer["setDistanceToSide"] = &tgui::TabsRenderer::setDistanceToSide;
        bindTabsRenderer["getDistanceToSide"] = &tgui::TabsRenderer::getDistanceToSide;
        bindTabsRenderer["WidgetRenderer"] = sol::overload(
            static_cast<(tgui::TabsRenderer::*)()>(&tgui::TabsRenderer::WidgetRenderer),
            static_cast<(
                tgui::TabsRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                &tgui::TabsRenderer::WidgetRenderer));
    }
    void LoadClassTabContainer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TabContainer> bindTabContainer
            = tguiNamespace.new_usertype<tgui::TabContainer>("TabContainer",
                sol::call_constructor,
                sol::constructors<tgui::TabContainer(), tgui::TabContainer(const char*),
                    tgui::TabContainer(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::SubwidgetContainer, tgui::Widget>());
        bindTabContainer["getTabsSharedRenderer"]
            = sol::overload(static_cast<gui::TabsRenderer* (tgui::TabContainer::*)()>(
                                &tgui::TabContainer::getTabsSharedRenderer),
                static_cast<const gui::TabsRenderer* (tgui::TabContainer::*)() const>(
                    &tgui::TabContainer::getTabsSharedRenderer));
        bindTabContainer["getTabsRenderer"]
            = sol::overload(static_cast<gui::TabsRenderer* (tgui::TabContainer::*)()>(
                                &tgui::TabContainer::getTabsRenderer),
                static_cast<const gui::TabsRenderer* (tgui::TabContainer::*)() const>(
                    &tgui::TabContainer::getTabsRenderer));
        bindTabContainer["setSize"] = sol::overload(
            static_cast<void (tgui::TabContainer::*)(const gui::Layout2d&)>(
                &tgui::TabContainer::setSize),
            static_cast<void (tgui::TabContainer::*)(const gui::Layout2d&)>(
                &tgui::TabContainer::setSize),
            static_cast<void (tgui::TabContainer::*)(const gui::Layout2d&)>(
                &tgui::TabContainer::setSize),
            static_cast<void (tgui::TabContainer::*)(gui::Layout, gui::Layout)>(
                &tgui::TabContainer::setSize));
        bindTabContainer["setTabsHeight"] = &tgui::TabContainer::setTabsHeight;
        bindTabContainer["addPanel"] = sol::overload(
            [](tgui::TabContainer* self, gui::Panel1a34b136a7d90420e28a8f4aa66a58f9d0 ptr,
                const gui::String& name) -> void { return self->addPanel(ptr, name); },
            [](tgui::TabContainer* self, gui::Panel1a34b136a7d90420e28a8f4aa66a58f9d0 ptr,
                const gui::String& name,
                bool select) -> void { return self->addPanel(ptr, name, select); });
        bindTabContainer["insertPanel"] = sol::overload(
            [](tgui::TabContainer* self, gui::Panel1a34b136a7d90420e28a8f4aa66a58f9d0 ptr,
                const gui::String& name, std::size_t index) -> bool {
                return self->insertPanel(ptr, name, index);
            },
            [](tgui::TabContainer* self, gui::Panel1a34b136a7d90420e28a8f4aa66a58f9d0 ptr,
                const gui::String& name, std::size_t index, bool select) -> bool {
                return self->insertPanel(ptr, name, index, select);
            });
        bindTabContainer["removePanel"] = &tgui::TabContainer::removePanel;
        bindTabContainer["select"] = sol::overload(
            [](tgui::TabContainer* self, std::size_t index) -> void {
                return self->select(index);
            },
            [](tgui::TabContainer* self, std::size_t index, bool genEvents) -> void {
                return self->select(index, genEvents);
            });
        bindTabContainer["getPanelCount"] = &tgui::TabContainer::getPanelCount;
        bindTabContainer["getIndex"] = &tgui::TabContainer::getIndex;
        bindTabContainer["getSelected"] = &tgui::TabContainer::getSelected;
        bindTabContainer["getSelectedIndex"] = &tgui::TabContainer::getSelectedIndex;
        bindTabContainer["getPanel"] = &tgui::TabContainer::getPanel;
        bindTabContainer["getTabs"] = &tgui::TabContainer::getTabs;
        bindTabContainer["getTabText"] = &tgui::TabContainer::getTabText;
        bindTabContainer["changeTabText"] = &tgui::TabContainer::changeTabText;
        bindTabContainer["create"] = sol::overload(
            [](tgui::TabContainer* self)
                -> gui::TabContainer1af2a44cfa761f9ff173af063ff3979f1c {
                return self->create();
            },
            [](tgui::TabContainer* self, const gui::Layout2d& size)
                -> gui::TabContainer1af2a44cfa761f9ff173af063ff3979f1c {
                return self->create(size);
            });
        bindTabContainer["copy"] = &tgui::TabContainer::copy;
        bindTabContainer["onSelectionChanged"] = &tgui::TabContainer::onSelectionChanged;
        bindTabContainer["onSelectionChanging"]
            = &tgui::TabContainer::onSelectionChanging;
    }
    void LoadClassText(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Text> bindText
            = tguiNamespace.new_usertype<tgui::Text>("Text", sol::call_constructor,
                sol::constructors<tgui::Text(), tgui::Text(const gui::Text&),
                    tgui::Text(gui::Text &&)>());
        bindText["operator="]
            = sol::overload(static_cast<gui::Text& (tgui::Text::*)(const gui::Text&)>(
                                &tgui::Text::operator=),
                static_cast<gui::Text& (tgui::Text::*)(gui::Text &&)>(
                    &tgui::Text::operator=));
        bindText["setPosition"] = &tgui::Text::setPosition;
        bindText["getPosition"] = &tgui::Text::getPosition;
        bindText["getSize"] = &tgui::Text::getSize;
        bindText["setString"] = &tgui::Text::setString;
        bindText["getString"] = &tgui::Text::getString;
        bindText["setCharacterSize"] = &tgui::Text::setCharacterSize;
        bindText["getCharacterSize"] = &tgui::Text::getCharacterSize;
        bindText["setColor"] = &tgui::Text::setColor;
        bindText["getColor"] = &tgui::Text::getColor;
        bindText["setOpacity"] = &tgui::Text::setOpacity;
        bindText["getOpacity"] = &tgui::Text::getOpacity;
        bindText["setFont"] = &tgui::Text::setFont;
        bindText["getFont"] = &tgui::Text::getFont;
        bindText["setStyle"] = &tgui::Text::setStyle;
        bindText["getStyle"] = &tgui::Text::getStyle;
        bindText["setOutlineColor"] = &tgui::Text::setOutlineColor;
        bindText["getOutlineColor"] = &tgui::Text::getOutlineColor;
        bindText["setOutlineThickness"] = &tgui::Text::setOutlineThickness;
        bindText["getOutlineThickness"] = &tgui::Text::getOutlineThickness;
        bindText["findCharacterPos"] = &tgui::Text::findCharacterPos;
        bindText["getExtraHorizontalPadding"]
            = sol::overload(static_cast<float (tgui::Text::*)() const>(
                                &tgui::Text::getExtraHorizontalPadding),
                static_cast<float (*)(gui::Font, unsigned int, gui::TextStyles)>(
                    &tgui::Text::getExtraHorizontalPadding));
        bindText["getExtraHorizontalOffset"]
            = sol::overload(static_cast<float (tgui::Text::*)() const>(
                                &tgui::Text::getExtraHorizontalOffset),
                static_cast<float (*)(gui::Font, unsigned int, gui::TextStyles)>(
                    &tgui::Text::getExtraHorizontalOffset));
        bindText["getLineHeight"] = sol::overload(
            static_cast<float (tgui::Text::*)() const>(&tgui::Text::getLineHeight),
            static_cast<float (*)(gui::Font, unsigned int, gui::TextStyles)>(
                &tgui::Text::getLineHeight));
        bindText["getLineWidth"] = sol::overload(
            static_cast<float (tgui::Text::*)() const>(&tgui::Text::getLineWidth),
            static_cast<float (*)(const gui::String&, gui::Font, unsigned int,
                gui::TextStyles)>(&tgui::Text::getLineWidth));
        bindText["getBackendText"] = &tgui::Text::getBackendText;
        bindText["getExtraVerticalPadding"] = &tgui::Text::getExtraVerticalPadding;
        bindText["findBestTextSize"] = sol::overload(
            [](tgui::Text* self, gui::Font font, float height) -> unsigned int {
                return self->findBestTextSize(font, height);
            },
            [](tgui::Text* self, gui::Font font, float height, int fit) -> unsigned int {
                return self->findBestTextSize(font, height, fit);
            });
        bindText["calculateExtraVerticalSpace"] = sol::overload(
            [](tgui::Text* self, gui::Font font, unsigned int characterSize) -> float {
                return self->calculateExtraVerticalSpace(font, characterSize);
            },
            [](tgui::Text* self, gui::Font font, unsigned int characterSize,
                gui::TextStyles style) -> float {
                return self->calculateExtraVerticalSpace(font, characterSize, style);
            });
        bindText["wordWrap"] = sol::overload(
            [](tgui::Text* self, float maxWidth, const gui::String& text, gui::Font font,
                unsigned int textSize, bool bold) -> gui::String {
                return self->wordWrap(maxWidth, text, font, textSize, bold);
            },
            [](tgui::Text* self, float maxWidth, const gui::String& text, gui::Font font,
                unsigned int textSize, bool bold, bool dropLeadingSpace) -> gui::String {
                return self->wordWrap(
                    maxWidth, text, font, textSize, bold, dropLeadingSpace);
            });
    }
    void LoadClassTexture(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Texture> bindTexture = tguiNamespace.new_usertype<
            tgui::Texture>("Texture", sol::call_constructor,
            sol::constructors<tgui::Texture(), tgui::Texture(const char*),
                tgui::Texture(const char*, const tgui::UIntRect&),
                tgui::Texture(const char*, const tgui::UIntRect&, const tgui::UIntRect&),
                tgui::Texture(
                    const char*, const tgui::UIntRect&, const tgui::UIntRect&, bool),
                tgui::Texture(const gui::String&),
                tgui::Texture(const gui::String&, const tgui::UIntRect&),
                tgui::Texture(
                    const gui::String&, const tgui::UIntRect&, const tgui::UIntRect&),
                tgui::Texture(const gui::String&, const tgui::UIntRect&,
                    const tgui::UIntRect&, bool),
                tgui::Texture(const gui::Texture&), tgui::Texture(gui::Texture &&)>());
        bindTexture["operator="] = sol::overload(
            static_cast<gui::Texture& (tgui::Texture::*)(const gui::Texture&)>(
                &tgui::Texture::operator=),
            static_cast<gui::Texture& (tgui::Texture::*)(gui::Texture &&)>(
                &tgui::Texture::operator=));
        bindTexture["load"] = sol::overload(
            [](tgui::Texture* self, const gui::String& id) -> void {
                return self->load(id);
            },
            [](tgui::Texture* self, const gui::String& id, const tgui::UIntRect& partRect)
                -> void { return self->load(id, partRect); },
            [](tgui::Texture* self, const gui::String& id, const tgui::UIntRect& partRect,
                const tgui::UIntRect& middleRect) -> void {
                return self->load(id, partRect, middleRect);
            },
            [](tgui::Texture* self, const gui::String& id, const tgui::UIntRect& partRect,
                const tgui::UIntRect& middleRect, bool smooth) -> void {
                return self->load(id, partRect, middleRect, smooth);
            });
        bindTexture["TGUI_DEPRECATED"] = &tgui::Texture::TGUI_DEPRECATED;
        bindTexture["loadFromMemory"] = sol::overload(
            [](tgui::Texture* self, const std::uint8_t* data, std::size_t dataSize)
                -> void { return self->loadFromMemory(data, dataSize); },
            [](tgui::Texture* self, const std::uint8_t* data, std::size_t dataSize,
                const tgui::UIntRect& partRect) -> void {
                return self->loadFromMemory(data, dataSize, partRect);
            },
            [](tgui::Texture* self, const std::uint8_t* data, std::size_t dataSize,
                const tgui::UIntRect& partRect,
                const tgui::UIntRect& middleRect) -> void {
                return self->loadFromMemory(data, dataSize, partRect, middleRect);
            },
            [](tgui::Texture* self, const std::uint8_t* data, std::size_t dataSize,
                const tgui::UIntRect& partRect, const tgui::UIntRect& middleRect,
                bool smooth) -> void {
                return self->loadFromMemory(data, dataSize, partRect, middleRect, smooth);
            });
        bindTexture["loadFromPixelData"] = sol::overload(
            [](tgui::Texture* self, tgui::Vector2u size, const std::uint8_t* pixels)
                -> void { return self->loadFromPixelData(size, pixels); },
            [](tgui::Texture* self, tgui::Vector2u size, const std::uint8_t* pixels,
                const tgui::UIntRect& partRect) -> void {
                return self->loadFromPixelData(size, pixels, partRect);
            },
            [](tgui::Texture* self, tgui::Vector2u size, const std::uint8_t* pixels,
                const tgui::UIntRect& partRect,
                const tgui::UIntRect& middleRect) -> void {
                return self->loadFromPixelData(size, pixels, partRect, middleRect);
            },
            [](tgui::Texture* self, tgui::Vector2u size, const std::uint8_t* pixels,
                const tgui::UIntRect& partRect, const tgui::UIntRect& middleRect,
                bool smooth) -> void {
                return self->loadFromPixelData(
                    size, pixels, partRect, middleRect, smooth);
            });
        bindTexture["getId"] = &tgui::Texture::getId;
        bindTexture["getData"] = &tgui::Texture::getData;
        bindTexture["getImageSize"] = &tgui::Texture::getImageSize;
        bindTexture["getPartRect"] = &tgui::Texture::getPartRect;
        bindTexture["isSmooth"] = &tgui::Texture::isSmooth;
        bindTexture["setColor"] = &tgui::Texture::setColor;
        bindTexture["getColor"] = &tgui::Texture::getColor;
        bindTexture["getMiddleRect"] = &tgui::Texture::getMiddleRect;
        bindTexture["isTransparentPixel"] = &tgui::Texture::isTransparentPixel;
        bindTexture["setCopyCallback"] = &tgui::Texture::setCopyCallback;
        bindTexture["setDestructCallback"] = &tgui::Texture::setDestructCallback;
        bindTexture[sol::meta_function::equal_to] = &tgui::Texture::operator==;
        bindTexture["setBackendTextureLoader"] = &tgui::Texture::setBackendTextureLoader;
        bindTexture["getBackendTextureLoader"] = &tgui::Texture::getBackendTextureLoader;
        bindTexture["setTextureLoader"] = &tgui::Texture::setTextureLoader;
        bindTexture["getTextureLoader"] = &tgui::Texture::getTextureLoader;
        bindTexture["pixels"] = &tgui::Texture::pixels;
        bindTexture["partRect"] = sol::property(
            [](tgui::Texture* self) -> const std::uint8_t const UIntRect& {
                return self->partRect;
            });
        bindTexture["middleRect"] = sol::property(
            [](tgui::Texture* self) -> const std::uint8_t const UIntRect const UIntRect& {
                return self->middleRect;
            });
    }
    void LoadClassTextureManager(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TextureManager> bindTextureManager
            = tguiNamespace.new_usertype<tgui::TextureManager>(
                "TextureManager", sol::call_constructor, sol::default_constructor);
        bindTextureManager["getTexture"] = &tgui::TextureManager::getTexture;
        bindTextureManager["copyTexture"] = &tgui::TextureManager::copyTexture;
        bindTextureManager["removeTexture"] = &tgui::TextureManager::removeTexture;
        bindTextureManager["getCachedImagesCount"]
            = &tgui::TextureManager::getCachedImagesCount;
    }
    void LoadClassTextArea(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TextArea> bindTextArea
            = tguiNamespace.new_usertype<tgui::TextArea>("TextArea",
                sol::call_constructor,
                sol::constructors<tgui::TextArea(), tgui::TextArea(const char*),
                    tgui::TextArea(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindTextArea["getSharedRenderer"]
            = sol::overload(static_cast<gui::TextAreaRenderer* (tgui::TextArea::*)()>(
                                &tgui::TextArea::getSharedRenderer),
                static_cast<const gui::TextAreaRenderer* (tgui::TextArea::*)() const>(
                    &tgui::TextArea::getSharedRenderer));
        bindTextArea["getRenderer"]
            = sol::overload(static_cast<gui::TextAreaRenderer* (tgui::TextArea::*)()>(
                                &tgui::TextArea::getRenderer),
                static_cast<const gui::TextAreaRenderer* (tgui::TextArea::*)() const>(
                    &tgui::TextArea::getRenderer));
        bindTextArea["setSize"]
            = sol::overload(static_cast<void (tgui::TextArea::*)(const gui::Layout2d&)>(
                                &tgui::TextArea::setSize),
                static_cast<void (tgui::TextArea::*)(const gui::Layout2d&)>(
                    &tgui::TextArea::setSize),
                static_cast<void (tgui::TextArea::*)(gui::Layout, gui::Layout)>(
                    &tgui::TextArea::setSize));
        bindTextArea["setText"] = &tgui::TextArea::setText;
        bindTextArea["addText"] = &tgui::TextArea::addText;
        bindTextArea["getText"] = &tgui::TextArea::getText;
        bindTextArea["setDefaultText"] = &tgui::TextArea::setDefaultText;
        bindTextArea["getDefaultText"] = &tgui::TextArea::getDefaultText;
        bindTextArea["setSelectedText"] = &tgui::TextArea::setSelectedText;
        bindTextArea["getSelectedText"] = &tgui::TextArea::getSelectedText;
        bindTextArea["getSelectionStart"] = &tgui::TextArea::getSelectionStart;
        bindTextArea["getSelectionEnd"] = &tgui::TextArea::getSelectionEnd;
        bindTextArea["setTextSize"] = &tgui::TextArea::setTextSize;
        bindTextArea["setMaximumCharacters"] = sol::overload(
            [](tgui::TextArea* self) -> void { return self->setMaximumCharacters(); },
            [](tgui::TextArea* self, std::size_t maxChars) -> void {
                return self->setMaximumCharacters(maxChars);
            });
        bindTextArea["getMaximumCharacters"] = &tgui::TextArea::getMaximumCharacters;
        bindTextArea["setCaretPosition"] = &tgui::TextArea::setCaretPosition;
        bindTextArea["getCaretPosition"] = &tgui::TextArea::getCaretPosition;
        bindTextArea["setReadOnly"] = sol::overload(
            [](tgui::TextArea* self) -> void { return self->setReadOnly(); },
            [](tgui::TextArea* self, bool readOnly) -> void {
                return self->setReadOnly(readOnly);
            });
        bindTextArea["isReadOnly"] = &tgui::TextArea::isReadOnly;
        bindTextArea["setVerticalScrollbarPolicy"]
            = &tgui::TextArea::setVerticalScrollbarPolicy;
        bindTextArea["getVerticalScrollbarPolicy"]
            = &tgui::TextArea::getVerticalScrollbarPolicy;
        bindTextArea["setHorizontalScrollbarPolicy"]
            = &tgui::TextArea::setHorizontalScrollbarPolicy;
        bindTextArea["getHorizontalScrollbarPolicy"]
            = &tgui::TextArea::getHorizontalScrollbarPolicy;
        bindTextArea["getLinesCount"] = &tgui::TextArea::getLinesCount;
        bindTextArea["setFocused"] = &tgui::TextArea::setFocused;
        bindTextArea["enableMonospacedFontOptimization"] = sol::overload(
            [](tgui::TextArea* self) -> void {
                return self->enableMonospacedFontOptimization();
            },
            [](tgui::TextArea* self, bool enable) -> void {
                return self->enableMonospacedFontOptimization(enable);
            });
        bindTextArea["setVerticalScrollbarValue"]
            = &tgui::TextArea::setVerticalScrollbarValue;
        bindTextArea["getVerticalScrollbarValue"]
            = &tgui::TextArea::getVerticalScrollbarValue;
        bindTextArea["setHorizontalScrollbarValue"]
            = &tgui::TextArea::setHorizontalScrollbarValue;
        bindTextArea["getHorizontalScrollbarValue"]
            = &tgui::TextArea::getHorizontalScrollbarValue;
        bindTextArea["isMouseOnWidget"] = &tgui::TextArea::isMouseOnWidget;
        bindTextArea["leftMousePressed"] = &tgui::TextArea::leftMousePressed;
        bindTextArea["leftMouseReleased"] = &tgui::TextArea::leftMouseReleased;
        bindTextArea["mouseMoved"] = &tgui::TextArea::mouseMoved;
        bindTextArea["keyPressed"] = &tgui::TextArea::keyPressed;
        bindTextArea["textEntered"] = &tgui::TextArea::textEntered;
        bindTextArea["mouseWheelScrolled"] = &tgui::TextArea::mouseWheelScrolled;
        bindTextArea["mouseNoLongerOnWidget"] = &tgui::TextArea::mouseNoLongerOnWidget;
        bindTextArea["leftMouseButtonNoLongerDown"]
            = &tgui::TextArea::leftMouseButtonNoLongerDown;
        bindTextArea["create"] = &tgui::TextArea::create;
        bindTextArea["copy"] = &tgui::TextArea::copy;
        bindTextArea["onTextChange"] = &tgui::TextArea::onTextChange;
        bindTextArea["onSelectionChange"] = &tgui::TextArea::onSelectionChange;
    }
    void LoadClassTextAreaRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TextAreaRenderer> bindTextAreaRenderer
            = tguiNamespace.new_usertype<tgui::TextAreaRenderer>("TextAreaRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindTextAreaRenderer["setBorders"] = &tgui::TextAreaRenderer::setBorders;
        bindTextAreaRenderer["getBorders"] = &tgui::TextAreaRenderer::getBorders;
        bindTextAreaRenderer["setPadding"] = &tgui::TextAreaRenderer::setPadding;
        bindTextAreaRenderer["getPadding"] = &tgui::TextAreaRenderer::getPadding;
        bindTextAreaRenderer["setBackgroundColor"]
            = &tgui::TextAreaRenderer::setBackgroundColor;
        bindTextAreaRenderer["getBackgroundColor"]
            = &tgui::TextAreaRenderer::getBackgroundColor;
        bindTextAreaRenderer["setTextColor"] = &tgui::TextAreaRenderer::setTextColor;
        bindTextAreaRenderer["getTextColor"] = &tgui::TextAreaRenderer::getTextColor;
        bindTextAreaRenderer["setDefaultTextColor"]
            = &tgui::TextAreaRenderer::setDefaultTextColor;
        bindTextAreaRenderer["getDefaultTextColor"]
            = &tgui::TextAreaRenderer::getDefaultTextColor;
        bindTextAreaRenderer["setSelectedTextColor"]
            = &tgui::TextAreaRenderer::setSelectedTextColor;
        bindTextAreaRenderer["getSelectedTextColor"]
            = &tgui::TextAreaRenderer::getSelectedTextColor;
        bindTextAreaRenderer["setSelectedTextBackgroundColor"]
            = &tgui::TextAreaRenderer::setSelectedTextBackgroundColor;
        bindTextAreaRenderer["getSelectedTextBackgroundColor"]
            = &tgui::TextAreaRenderer::getSelectedTextBackgroundColor;
        bindTextAreaRenderer["setBorderColor"] = &tgui::TextAreaRenderer::setBorderColor;
        bindTextAreaRenderer["getBorderColor"] = &tgui::TextAreaRenderer::getBorderColor;
        bindTextAreaRenderer["setCaretColor"] = &tgui::TextAreaRenderer::setCaretColor;
        bindTextAreaRenderer["getCaretColor"] = &tgui::TextAreaRenderer::getCaretColor;
        bindTextAreaRenderer["setTextureBackground"]
            = &tgui::TextAreaRenderer::setTextureBackground;
        bindTextAreaRenderer["getTextureBackground"]
            = &tgui::TextAreaRenderer::getTextureBackground;
        bindTextAreaRenderer["setCaretWidth"] = &tgui::TextAreaRenderer::setCaretWidth;
        bindTextAreaRenderer["getCaretWidth"] = &tgui::TextAreaRenderer::getCaretWidth;
        bindTextAreaRenderer["setScrollbar"] = &tgui::TextAreaRenderer::setScrollbar;
        bindTextAreaRenderer["getScrollbar"] = &tgui::TextAreaRenderer::getScrollbar;
        bindTextAreaRenderer["setScrollbarWidth"]
            = &tgui::TextAreaRenderer::setScrollbarWidth;
        bindTextAreaRenderer["getScrollbarWidth"]
            = &tgui::TextAreaRenderer::getScrollbarWidth;
        bindTextAreaRenderer["WidgetRenderer"] = sol::overload(
            static_cast<(tgui::TextAreaRenderer::*)()>(
                &tgui::TextAreaRenderer::WidgetRenderer),
            static_cast<(
                tgui::TextAreaRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                &tgui::TextAreaRenderer::WidgetRenderer));
    }
    void LoadClassTextStyles(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TextStyles> bindTextStyles
            = tguiNamespace.new_usertype<tgui::TextStyles>("TextStyles",
                sol::call_constructor,
                sol::constructors<tgui::TextStyles(), tgui::TextStyles(unsigned int),
                    tgui::TextStyles(const gui::String&),
                    tgui::TextStyles(const char*)>());
        bindTextStyles["isSet"] = &tgui::TextStyles::isSet;
        bindTextStyles["operator unsigned int"]
            = &tgui::TextStyles::operator unsigned int;
    }
    void LoadClassTheme(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Theme> bindTheme
            = tguiNamespace.new_usertype<tgui::Theme>("Theme", sol::call_constructor,
                sol::constructors<tgui::Theme(), tgui::Theme(const gui::String&)>());
        bindTheme["load"] = &tgui::Theme::load;
        bindTheme["getRenderer"] = &tgui::Theme::getRenderer;
        bindTheme["getRendererNoThrow"] = &tgui::Theme::getRendererNoThrow;
        bindTheme["addRenderer"] = &tgui::Theme::addRenderer;
        bindTheme["removeRenderer"] = &tgui::Theme::removeRenderer;
        bindTheme["getPrimary"] = &tgui::Theme::getPrimary;
        bindTheme["create"] = sol::overload(
            [](tgui::Theme* self) -> gui::Theme1a6428ad1bf9c7b651f42e4863a91b82bf {
                return self->create();
            },
            [](tgui::Theme* self, const gui::String& primary)
                -> gui::Theme1a6428ad1bf9c7b651f42e4863a91b82bf {
                return self->create(primary);
            });
        bindTheme["setThemeLoader"] = &tgui::Theme::setThemeLoader;
        bindTheme["getThemeLoader"] = &tgui::Theme::getThemeLoader;
        bindTheme["setDefault"] = sol::overload(
            static_cast<void (*)(const gui::String&)>(&tgui::Theme::setDefault),
            static_cast<void (*)(std::shared_ptr<gui::Theme>)>(&tgui::Theme::setDefault),
            static_cast<void (*)(std::nullptr_t)>(&tgui::Theme::setDefault));
        bindTheme["getDefault"] = &tgui::Theme::getDefault;
    }
    void LoadClassTimer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Timer> bindTimer
            = tguiNamespace.new_usertype<tgui::Timer>("Timer", sol::call_constructor,
                sol::constructors<tgui::Timer(const gui::Timer&)>());
        bindTimer["operator="] = &tgui::Timer::operator=;
        bindTimer["setInterval"] = &tgui::Timer::setInterval;
        bindTimer["getInterval"] = &tgui::Timer::getInterval;
        bindTimer["setEnabled"] = &tgui::Timer::setEnabled;
        bindTimer["isEnabled"] = &tgui::Timer::isEnabled;
        bindTimer["setCallback"] = sol::overload(
            static_cast<void (tgui::Timer::*)(const std::function<void()>&)>(
                &tgui::Timer::setCallback),
            static_cast<void (tgui::Timer::*)(
                const std::function<void(std::shared_ptr<gui::Timer>)>&)>(
                &tgui::Timer::setCallback));
        bindTimer["restart"] = &tgui::Timer::restart;
        bindTimer["create"] = sol::overload(
            static_cast<std::shared_ptr<gui::Timer> (*)(
                const std::function<void()>&, gui::Duration, bool)>(&tgui::Timer::create),
            static_cast<std::shared_ptr<gui::Timer> (*)(
                const std::function<void(std::shared_ptr<gui::Timer>)>&, gui::Duration,
                bool)>(&tgui::Timer::create));
        bindTimer["scheduleCallback"] = sol::overload(
            [](tgui::Timer* self, std::function<void()> callback) -> void {
                return self->scheduleCallback(callback);
            },
            [](tgui::Timer* self, std::function<void()> callback, gui::Duration interval)
                -> void { return self->scheduleCallback(callback, interval); });
        bindTimer["updateTime"] = &tgui::Timer::updateTime;
        bindTimer["getNextScheduledTime"] = &tgui::Timer::getNextScheduledTime;
        bindTimer["clearTimers"] = &tgui::Timer::clearTimers;
    }
    void LoadClassToggleButton(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ToggleButton> bindToggleButton
            = tguiNamespace.new_usertype<tgui::ToggleButton>("ToggleButton",
                sol::call_constructor,
                sol::constructors<tgui::ToggleButton(), tgui::ToggleButton(const char*),
                    tgui::ToggleButton(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::ButtonBase, tgui::ClickableWidget, tgui::Widget>());
        bindToggleButton["setDown"] = &tgui::ToggleButton::setDown;
        bindToggleButton["isDown"] = &tgui::ToggleButton::isDown;
        bindToggleButton["leftMouseReleased"] = &tgui::ToggleButton::leftMouseReleased;
        bindToggleButton["keyPressed"] = &tgui::ToggleButton::keyPressed;
        bindToggleButton["create"] = sol::overload(
            [](tgui::ToggleButton* self)
                -> gui::ToggleButton1acd33b5cc9206c3b808ba0222c3b2fc15 {
                return self->create();
            },
            [](tgui::ToggleButton* self, const gui::String& text)
                -> gui::ToggleButton1acd33b5cc9206c3b808ba0222c3b2fc15 {
                return self->create(text);
            },
            [](tgui::ToggleButton* self, const gui::String& text,
                bool down) -> gui::ToggleButton1acd33b5cc9206c3b808ba0222c3b2fc15 {
                return self->create(text, down);
            });
        bindToggleButton["copy"] = &tgui::ToggleButton::copy;
        bindToggleButton["onToggle"] = &tgui::ToggleButton::onToggle;
    }
    void LoadClassToolTip(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ToolTip> bindToolTip
            = tguiNamespace.new_usertype<tgui::ToolTip>(
                "ToolTip", sol::call_constructor, sol::default_constructor);
        bindToolTip["setInitialDelay"] = &tgui::ToolTip::setInitialDelay;
        bindToolTip["getInitialDelay"] = &tgui::ToolTip::getInitialDelay;
        bindToolTip["setDistanceToMouse"] = &tgui::ToolTip::setDistanceToMouse;
        bindToolTip["getDistanceToMouse"] = &tgui::ToolTip::getDistanceToMouse;
    }
    void LoadClassTransform(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Transform> bindTransform
            = tguiNamespace.new_usertype<tgui::Transform>("Transform",
                sol::call_constructor,
                sol::constructors<tgui::Transform(),
                    tgui::Transform(
                        float, float, float, float, float, float, float, float, float),
                    tgui::Transform(const float)>());
        bindTransform["getMatrix"] = &tgui::Transform::getMatrix;
        bindTransform["getInverse"] = &tgui::Transform::getInverse;
        bindTransform["transformPoint"] = &tgui::Transform::transformPoint;
        bindTransform["transformRect"] = &tgui::Transform::transformRect;
        bindTransform["combine"] = &tgui::Transform::combine;
        bindTransform["translate"] = &tgui::Transform::translate;
        bindTransform["rotate"] = sol::overload(
            [](tgui::Transform* self, float angle) -> gui::Transform& {
                return self->rotate(angle);
            },
            [](tgui::Transform* self, float angle, const tgui::Vector2f& center)
                -> gui::Transform& { return self->rotate(angle, center); });
        bindTransform["scale"] = sol::overload(
            [](tgui::Transform* self, const tgui::Vector2f& factors) -> gui::Transform& {
                return self->scale(factors);
            },
            [](tgui::Transform* self, const tgui::Vector2f& factors,
                const tgui::Vector2f& center) -> gui::Transform& {
                return self->scale(factors, center);
            });
        bindTransform[sol::meta_function::multiplication] = sol::overload(
            static_cast<gui::Transform (tgui::Transform::*)(const gui::Transform&) const>(
                &tgui::Transform::operator*),
            static_cast<tgui::Vector2f (tgui::Transform::*)(const tgui::Vector2f&) const>(
                &tgui::Transform::operator*));
        bindTransform["roundPosition"] = &tgui::Transform::roundPosition;
    }
    void LoadClassTreeView(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TreeView> bindTreeView
            = tguiNamespace.new_usertype<tgui::TreeView>("TreeView",
                sol::call_constructor,
                sol::constructors<tgui::TreeView(), tgui::TreeView(const char*),
                    tgui::TreeView(const char*, bool),
                    tgui::TreeView(const gui::TreeView&),
                    tgui::TreeView(gui::TreeView &&)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindTreeView["operator="] = sol::overload(
            static_cast<gui::TreeView& (tgui::TreeView::*)(const gui::TreeView&)>(
                &tgui::TreeView::operator=),
            static_cast<gui::TreeView& (tgui::TreeView::*)(gui::TreeView &&)>(
                &tgui::TreeView::operator=));
        bindTreeView["getSharedRenderer"]
            = sol::overload(static_cast<gui::TreeViewRenderer* (tgui::TreeView::*)()>(
                                &tgui::TreeView::getSharedRenderer),
                static_cast<const gui::TreeViewRenderer* (tgui::TreeView::*)() const>(
                    &tgui::TreeView::getSharedRenderer));
        bindTreeView["getRenderer"]
            = sol::overload(static_cast<gui::TreeViewRenderer* (tgui::TreeView::*)()>(
                                &tgui::TreeView::getRenderer),
                static_cast<const gui::TreeViewRenderer* (tgui::TreeView::*)() const>(
                    &tgui::TreeView::getRenderer));
        bindTreeView["setSize"]
            = sol::overload(static_cast<void (tgui::TreeView::*)(const gui::Layout2d&)>(
                                &tgui::TreeView::setSize),
                static_cast<void (tgui::TreeView::*)(const gui::Layout2d&)>(
                    &tgui::TreeView::setSize),
                static_cast<void (tgui::TreeView::*)(gui::Layout, gui::Layout)>(
                    &tgui::TreeView::setSize));
        bindTreeView["addItem"] = sol::overload(
            [](tgui::TreeView* self, const std::vector<gui::String>& hierarchy) -> bool {
                return self->addItem(hierarchy);
            },
            [](tgui::TreeView* self, const std::vector<gui::String>& hierarchy,
                bool createParents) -> bool {
                return self->addItem(hierarchy, createParents);
            });
        bindTreeView["expand"] = &tgui::TreeView::expand;
        bindTreeView["expandAll"] = &tgui::TreeView::expandAll;
        bindTreeView["collapse"] = &tgui::TreeView::collapse;
        bindTreeView["collapseAll"] = &tgui::TreeView::collapseAll;
        bindTreeView["selectItem"] = &tgui::TreeView::selectItem;
        bindTreeView["deselectItem"] = &tgui::TreeView::deselectItem;
        bindTreeView["removeItem"] = sol::overload(
            [](tgui::TreeView* self, const std::vector<gui::String>& hierarchy) -> bool {
                return self->removeItem(hierarchy);
            },
            [](tgui::TreeView* self, const std::vector<gui::String>& hierarchy,
                bool removeParentsWhenEmpty) -> bool {
                return self->removeItem(hierarchy, removeParentsWhenEmpty);
            });
        bindTreeView["removeAllItems"] = &tgui::TreeView::removeAllItems;
        bindTreeView["getSelectedItem"] = &tgui::TreeView::getSelectedItem;
        bindTreeView["getNodes"] = &tgui::TreeView::getNodes;
        bindTreeView["setItemHeight"] = &tgui::TreeView::setItemHeight;
        bindTreeView["getItemHeight"] = &tgui::TreeView::getItemHeight;
        bindTreeView["setTextSize"] = &tgui::TreeView::setTextSize;
        bindTreeView["setVerticalScrollbarValue"]
            = &tgui::TreeView::setVerticalScrollbarValue;
        bindTreeView["getVerticalScrollbarValue"]
            = &tgui::TreeView::getVerticalScrollbarValue;
        bindTreeView["setHorizontalScrollbarValue"]
            = &tgui::TreeView::setHorizontalScrollbarValue;
        bindTreeView["getHorizontalScrollbarValue"]
            = &tgui::TreeView::getHorizontalScrollbarValue;
        bindTreeView["isMouseOnWidget"] = &tgui::TreeView::isMouseOnWidget;
        bindTreeView["leftMousePressed"] = &tgui::TreeView::leftMousePressed;
        bindTreeView["leftMouseReleased"] = &tgui::TreeView::leftMouseReleased;
        bindTreeView["rightMousePressed"] = &tgui::TreeView::rightMousePressed;
        bindTreeView["mouseMoved"] = &tgui::TreeView::mouseMoved;
        bindTreeView["mouseWheelScrolled"] = &tgui::TreeView::mouseWheelScrolled;
        bindTreeView["mouseNoLongerOnWidget"] = &tgui::TreeView::mouseNoLongerOnWidget;
        bindTreeView["leftMouseButtonNoLongerDown"]
            = &tgui::TreeView::leftMouseButtonNoLongerDown;
        bindTreeView["markNodesDirty"] = &tgui::TreeView::markNodesDirty;
        bindTreeView["draw"] = &tgui::TreeView::draw;
        bindTreeView["create"] = &tgui::TreeView::create;
        bindTreeView["copy"] = &tgui::TreeView::copy;
        bindTreeView["onItemSelect"] = &tgui::TreeView::onItemSelect;
        bindTreeView["onDoubleClick"] = &tgui::TreeView::onDoubleClick;
        bindTreeView["onExpand"] = &tgui::TreeView::onExpand;
        bindTreeView["onCollapse"] = &tgui::TreeView::onCollapse;
        bindTreeView["onRightClick"] = &tgui::TreeView::onRightClick;
    }
    void LoadClassTreeViewRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TreeViewRenderer> bindTreeViewRenderer
            = tguiNamespace.new_usertype<tgui::TreeViewRenderer>("TreeViewRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::WidgetRenderer>());
        bindTreeViewRenderer["setBorders"] = &tgui::TreeViewRenderer::setBorders;
        bindTreeViewRenderer["getBorders"] = &tgui::TreeViewRenderer::getBorders;
        bindTreeViewRenderer["setPadding"] = &tgui::TreeViewRenderer::setPadding;
        bindTreeViewRenderer["getPadding"] = &tgui::TreeViewRenderer::getPadding;
        bindTreeViewRenderer["setBackgroundColor"]
            = &tgui::TreeViewRenderer::setBackgroundColor;
        bindTreeViewRenderer["getBackgroundColor"]
            = &tgui::TreeViewRenderer::getBackgroundColor;
        bindTreeViewRenderer["setBorderColor"] = &tgui::TreeViewRenderer::setBorderColor;
        bindTreeViewRenderer["getBorderColor"] = &tgui::TreeViewRenderer::getBorderColor;
        bindTreeViewRenderer["setTextColor"] = &tgui::TreeViewRenderer::setTextColor;
        bindTreeViewRenderer["getTextColor"] = &tgui::TreeViewRenderer::getTextColor;
        bindTreeViewRenderer["setTextColorHover"]
            = &tgui::TreeViewRenderer::setTextColorHover;
        bindTreeViewRenderer["getTextColorHover"]
            = &tgui::TreeViewRenderer::getTextColorHover;
        bindTreeViewRenderer["setSelectedTextColor"]
            = &tgui::TreeViewRenderer::setSelectedTextColor;
        bindTreeViewRenderer["getSelectedTextColor"]
            = &tgui::TreeViewRenderer::getSelectedTextColor;
        bindTreeViewRenderer["setSelectedTextColorHover"]
            = &tgui::TreeViewRenderer::setSelectedTextColorHover;
        bindTreeViewRenderer["getSelectedTextColorHover"]
            = &tgui::TreeViewRenderer::getSelectedTextColorHover;
        bindTreeViewRenderer["setSelectedBackgroundColor"]
            = &tgui::TreeViewRenderer::setSelectedBackgroundColor;
        bindTreeViewRenderer["getSelectedBackgroundColor"]
            = &tgui::TreeViewRenderer::getSelectedBackgroundColor;
        bindTreeViewRenderer["setBackgroundColorHover"]
            = &tgui::TreeViewRenderer::setBackgroundColorHover;
        bindTreeViewRenderer["getBackgroundColorHover"]
            = &tgui::TreeViewRenderer::getBackgroundColorHover;
        bindTreeViewRenderer["setSelectedBackgroundColorHover"]
            = &tgui::TreeViewRenderer::setSelectedBackgroundColorHover;
        bindTreeViewRenderer["getSelectedBackgroundColorHover"]
            = &tgui::TreeViewRenderer::getSelectedBackgroundColorHover;
        bindTreeViewRenderer["setScrollbar"] = &tgui::TreeViewRenderer::setScrollbar;
        bindTreeViewRenderer["getScrollbar"] = &tgui::TreeViewRenderer::getScrollbar;
        bindTreeViewRenderer["setScrollbarWidth"]
            = &tgui::TreeViewRenderer::setScrollbarWidth;
        bindTreeViewRenderer["getScrollbarWidth"]
            = &tgui::TreeViewRenderer::getScrollbarWidth;
        bindTreeViewRenderer["setTextureBranchExpanded"]
            = &tgui::TreeViewRenderer::setTextureBranchExpanded;
        bindTreeViewRenderer["getTextureBranchExpanded"]
            = &tgui::TreeViewRenderer::getTextureBranchExpanded;
        bindTreeViewRenderer["setTextureBranchCollapsed"]
            = &tgui::TreeViewRenderer::setTextureBranchCollapsed;
        bindTreeViewRenderer["getTextureBranchCollapsed"]
            = &tgui::TreeViewRenderer::getTextureBranchCollapsed;
        bindTreeViewRenderer["setTextureLeaf"] = &tgui::TreeViewRenderer::setTextureLeaf;
        bindTreeViewRenderer["getTextureLeaf"] = &tgui::TreeViewRenderer::getTextureLeaf;
        bindTreeViewRenderer["WidgetRenderer"] = sol::overload(
            static_cast<(tgui::TreeViewRenderer::*)()>(
                &tgui::TreeViewRenderer::WidgetRenderer),
            static_cast<(
                tgui::TreeViewRenderer::*)(const std::shared_ptr<gui::RendererData>&)>(
                &tgui::TreeViewRenderer::WidgetRenderer));
    }
    void LoadClassVerticalLayout(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::VerticalLayout> bindVerticalLayout
            = tguiNamespace.new_usertype<tgui::VerticalLayout>("VerticalLayout",
                sol::call_constructor,
                sol::constructors<tgui::VerticalLayout(),
                    tgui::VerticalLayout(const char*),
                    tgui::VerticalLayout(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::BoxLayoutRatios, tgui::BoxLayout, tgui::Group,
                    tgui::Container, tgui::Widget>());
        bindVerticalLayout["create"] = sol::overload(
            [](tgui::VerticalLayout* self)
                -> gui::VerticalLayout1a0fc2b3187bc1d81952610e033a44badc {
                return self->create();
            },
            [](tgui::VerticalLayout* self, const gui::Layout2d& size)
                -> gui::VerticalLayout1a0fc2b3187bc1d81952610e033a44badc {
                return self->create(size);
            });
        bindVerticalLayout["copy"] = &tgui::VerticalLayout::copy;
    }
    void LoadClassWidget(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Widget> bindWidget
            = tguiNamespace.new_usertype<tgui::Widget>("Widget");
        bindWidget["operator="] = sol::overload(
            static_cast<gui::Widget& (tgui::Widget::*)(const gui::Widget&)>(
                &tgui::Widget::operator=),
            static_cast<gui::Widget& (tgui::Widget::*)(gui::Widget &&)>(
                &tgui::Widget::operator=));
        bindWidget["setRenderer"] = &tgui::Widget::setRenderer;
        bindWidget["getSharedRenderer"]
            = sol::overload(static_cast<gui::WidgetRenderer* (tgui::Widget::*)()>(
                                &tgui::Widget::getSharedRenderer),
                static_cast<const gui::WidgetRenderer* (tgui::Widget::*)() const>(
                    &tgui::Widget::getSharedRenderer));
        bindWidget["getRenderer"]
            = sol::overload(static_cast<gui::WidgetRenderer* (tgui::Widget::*)()>(
                                &tgui::Widget::getRenderer),
                static_cast<const gui::WidgetRenderer* (tgui::Widget::*)() const>(
                    &tgui::Widget::getRenderer));
        bindWidget["setPosition"]
            = sol::overload(static_cast<void (tgui::Widget::*)(const gui::Layout2d&)>(
                                &tgui::Widget::setPosition),
                static_cast<void (tgui::Widget::*)(gui::Layout, gui::Layout)>(
                    &tgui::Widget::setPosition));
        bindWidget["getPosition"] = &tgui::Widget::getPosition;
        bindWidget["setSize"]
            = sol::overload(static_cast<void (tgui::Widget::*)(const gui::Layout2d&)>(
                                &tgui::Widget::setSize),
                static_cast<void (tgui::Widget::*)(gui::Layout, gui::Layout)>(
                    &tgui::Widget::setSize));
        bindWidget["setWidth"] = &tgui::Widget::setWidth;
        bindWidget["setHeight"] = &tgui::Widget::setHeight;
        bindWidget["getSize"] = &tgui::Widget::getSize;
        bindWidget["getFullSize"] = &tgui::Widget::getFullSize;
        bindWidget["getAbsolutePosition"] = &tgui::Widget::getAbsolutePosition;
        bindWidget["getWidgetOffset"] = &tgui::Widget::getWidgetOffset;
        bindWidget["setOrigin"] = sol::overload(
            static_cast<void (tgui::Widget::*)(float, float)>(&tgui::Widget::setOrigin),
            static_cast<void (tgui::Widget::*)(tgui::Vector2f)>(
                &tgui::Widget::setOrigin));
        bindWidget["getOrigin"] = &tgui::Widget::getOrigin;
        bindWidget["setScale"] = sol::overload(
            static_cast<void (tgui::Widget::*)(tgui::Vector2f)>(&tgui::Widget::setScale),
            static_cast<void (tgui::Widget::*)(tgui::Vector2f, tgui::Vector2f)>(
                &tgui::Widget::setScale),
            static_cast<void (tgui::Widget::*)(float)>(&tgui::Widget::setScale),
            static_cast<void (tgui::Widget::*)(float, tgui::Vector2f)>(
                &tgui::Widget::setScale));
        bindWidget["getScale"] = &tgui::Widget::getScale;
        bindWidget["getScaleOrigin"] = &tgui::Widget::getScaleOrigin;
        bindWidget["setRotation"] = sol::overload(
            static_cast<void (tgui::Widget::*)(float)>(&tgui::Widget::setRotation),
            static_cast<void (tgui::Widget::*)(float, tgui::Vector2f)>(
                &tgui::Widget::setRotation));
        bindWidget["getRotation"] = &tgui::Widget::getRotation;
        bindWidget["getRotationOrigin"] = &tgui::Widget::getRotationOrigin;
        bindWidget["showWithEffect"] = &tgui::Widget::showWithEffect;
        bindWidget["hideWithEffect"] = &tgui::Widget::hideWithEffect;
        bindWidget["setVisible"] = &tgui::Widget::setVisible;
        bindWidget["isVisible"] = &tgui::Widget::isVisible;
        bindWidget["setEnabled"] = &tgui::Widget::setEnabled;
        bindWidget["isEnabled"] = &tgui::Widget::isEnabled;
        bindWidget["setFocused"] = &tgui::Widget::setFocused;
        bindWidget["isFocused"] = &tgui::Widget::isFocused;
        bindWidget["getWidgetType"] = &tgui::Widget::getWidgetType;
        bindWidget["getParent"] = &tgui::Widget::getParent;
        bindWidget["getParentGui"] = &tgui::Widget::getParentGui;
        bindWidget["isAnimationPlaying"] = &tgui::Widget::isAnimationPlaying;
        bindWidget["moveToFront"] = &tgui::Widget::moveToFront;
        bindWidget["moveToBack"] = &tgui::Widget::moveToBack;
        bindWidget["setUserData"] = &tgui::Widget::setUserData;
        bindWidget["setInheritedFont"] = &tgui::Widget::setInheritedFont;
        bindWidget["getInheritedFont"] = &tgui::Widget::getInheritedFont;
        bindWidget["setInheritedOpacity"] = &tgui::Widget::setInheritedOpacity;
        bindWidget["getInheritedOpacity"] = &tgui::Widget::getInheritedOpacity;
        bindWidget["setTextSize"] = &tgui::Widget::setTextSize;
        bindWidget["getTextSize"] = &tgui::Widget::getTextSize;
        bindWidget["setToolTip"] = &tgui::Widget::setToolTip;
        bindWidget["getToolTip"] = &tgui::Widget::getToolTip;
        bindWidget["setWidgetName"] = &tgui::Widget::setWidgetName;
        bindWidget["getWidgetName"] = &tgui::Widget::getWidgetName;
        bindWidget["setMouseCursor"] = &tgui::Widget::setMouseCursor;
        bindWidget["getMouseCursor"] = &tgui::Widget::getMouseCursor;
        bindWidget["setFocusable"] = &tgui::Widget::setFocusable;
        bindWidget["isFocusable"] = &tgui::Widget::isFocusable;
        bindWidget["canGainFocus"] = &tgui::Widget::canGainFocus;
        bindWidget["isContainer"] = &tgui::Widget::isContainer;
        bindWidget["isDraggableWidget"] = &tgui::Widget::isDraggableWidget;
        bindWidget["isMouseDown"] = &tgui::Widget::isMouseDown;
        bindWidget["getSignal"] = &tgui::Widget::getSignal;
        bindWidget["setParent"] = &tgui::Widget::setParent;
        bindWidget["updateTime"] = &tgui::Widget::updateTime;
        bindWidget["isMouseOnWidget"] = &tgui::Widget::isMouseOnWidget;
        bindWidget["leftMousePressed"] = &tgui::Widget::leftMousePressed;
        bindWidget["leftMouseReleased"] = &tgui::Widget::leftMouseReleased;
        bindWidget["rightMousePressed"] = &tgui::Widget::rightMousePressed;
        bindWidget["rightMouseReleased"] = &tgui::Widget::rightMouseReleased;
        bindWidget["mousePressed"] = &tgui::Widget::mousePressed;
        bindWidget["mouseReleased"] = &tgui::Widget::mouseReleased;
        bindWidget["mouseMoved"] = &tgui::Widget::mouseMoved;
        bindWidget["keyPressed"] = &tgui::Widget::keyPressed;
        bindWidget["textEntered"] = &tgui::Widget::textEntered;
        bindWidget["mouseWheelScrolled"] = &tgui::Widget::mouseWheelScrolled;
        bindWidget["mouseNoLongerOnWidget"] = &tgui::Widget::mouseNoLongerOnWidget;
        bindWidget["leftMouseButtonNoLongerDown"]
            = &tgui::Widget::leftMouseButtonNoLongerDown;
        bindWidget["rightMouseButtonNoLongerDown"]
            = &tgui::Widget::rightMouseButtonNoLongerDown;
        bindWidget["askToolTip"] = &tgui::Widget::askToolTip;
        bindWidget["getPositionLayout"] = &tgui::Widget::getPositionLayout;
        bindWidget["getSizeLayout"] = &tgui::Widget::getSizeLayout;
        bindWidget["bindPositionLayout"] = &tgui::Widget::bindPositionLayout;
        bindWidget["unbindPositionLayout"] = &tgui::Widget::unbindPositionLayout;
        bindWidget["bindSizeLayout"] = &tgui::Widget::bindSizeLayout;
        bindWidget["unbindSizeLayout"] = &tgui::Widget::unbindSizeLayout;
        bindWidget["draw"] = &tgui::Widget::draw;
        bindWidget["clone"] = &tgui::Widget::clone;
        bindWidget["onPositionChange"] = &tgui::Widget::onPositionChange;
        bindWidget["onSizeChange"] = &tgui::Widget::onSizeChange;
        bindWidget["onFocus"] = &tgui::Widget::onFocus;
        bindWidget["onUnfocus"] = &tgui::Widget::onUnfocus;
        bindWidget["onMouseEnter"] = &tgui::Widget::onMouseEnter;
        bindWidget["onMouseLeave"] = &tgui::Widget::onMouseLeave;
        bindWidget["onAnimationFinish"] = &tgui::Widget::onAnimationFinish;
    }
    void LoadClassWidgetFactory(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::WidgetFactory> bindWidgetFactory
            = tguiNamespace.new_usertype<tgui::WidgetFactory>(
                "WidgetFactory", sol::call_constructor, sol::default_constructor);
        bindWidgetFactory["setConstructFunction"]
            = &tgui::WidgetFactory::setConstructFunction;
        bindWidgetFactory["getConstructFunction"]
            = &tgui::WidgetFactory::getConstructFunction;
    }
    void LoadClassWidgetRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::WidgetRenderer> bindWidgetRenderer
            = tguiNamespace.new_usertype<tgui::WidgetRenderer>("WidgetRenderer",
                sol::call_constructor,
                sol::constructors<tgui::WidgetRenderer(),
                    tgui::WidgetRenderer(const std::shared_ptr<gui::RendererData>&)>());
        bindWidgetRenderer["setOpacity"] = &tgui::WidgetRenderer::setOpacity;
        bindWidgetRenderer["getOpacity"] = &tgui::WidgetRenderer::getOpacity;
        bindWidgetRenderer["setOpacityDisabled"]
            = &tgui::WidgetRenderer::setOpacityDisabled;
        bindWidgetRenderer["getOpacityDisabled"]
            = &tgui::WidgetRenderer::getOpacityDisabled;
        bindWidgetRenderer["setFont"] = &tgui::WidgetRenderer::setFont;
        bindWidgetRenderer["getFont"] = &tgui::WidgetRenderer::getFont;
        bindWidgetRenderer["setTransparentTexture"]
            = &tgui::WidgetRenderer::setTransparentTexture;
        bindWidgetRenderer["getTransparentTexture"]
            = &tgui::WidgetRenderer::getTransparentTexture;
        bindWidgetRenderer["setProperty"] = &tgui::WidgetRenderer::setProperty;
        bindWidgetRenderer["getProperty"] = &tgui::WidgetRenderer::getProperty;
        bindWidgetRenderer["getPropertyValuePairs"]
            = &tgui::WidgetRenderer::getPropertyValuePairs;
        bindWidgetRenderer["subscribe"] = &tgui::WidgetRenderer::subscribe;
        bindWidgetRenderer["unsubscribe"] = &tgui::WidgetRenderer::unsubscribe;
        bindWidgetRenderer["setData"] = &tgui::WidgetRenderer::setData;
        bindWidgetRenderer["getData"] = &tgui::WidgetRenderer::getData;
        bindWidgetRenderer["clone"] = &tgui::WidgetRenderer::clone;
    }
    void LoadClassAny(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Any> bindAny
            = tguiNamespace.new_usertype<tgui::Any>("Any", sol::call_constructor,
                sol::constructors<tgui::Any(U &&), tgui::Any(),
                    tgui::Any(const gui::Any&), tgui::Any(gui::Any &&)>());
        bindAny["is_null"] = &tgui::Any::is_null;
        bindAny["not_null"] = &tgui::Any::not_null;
        bindAny["operator="] = sol::overload(
            static_cast<gui::Any& (tgui::Any::*)(const gui::Any&)>(&tgui::Any::operator=),
            static_cast<gui::Any& (tgui::Any::*)(gui::Any &&)>(&tgui::Any::operator=));
    }
    void LoadClassEvent(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Event> bindEvent = tguiNamespace.new_usertype<tgui::Event>(
            "Event", sol::call_constructor, sol::default_constructor);
        bindEvent["type"] = &tgui::Event::type;
        bindEvent["key"] = &tgui::Event::key;
        bindEvent["text"] = &tgui::Event::text;
        bindEvent["mouseMove"] = &tgui::Event::mouseMove;
        bindEvent["mouseButton"] = &tgui::Event::mouseButton;
        bindEvent["mouseWheel"] = &tgui::Event::mouseWheel;
        bindEvent["size"] = &tgui::Event::size;
        bindEvent["@1"] = &tgui::Event::@1;
    }
    void LoadClassFontGlyph(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::FontGlyph> bindFontGlyph
            = tguiNamespace.new_usertype<tgui::FontGlyph>(
                "FontGlyph", sol::call_constructor, sol::default_constructor);
        bindFontGlyph["advance"] = &tgui::FontGlyph::advance;
        bindFontGlyph["bounds"] = &tgui::FontGlyph::bounds;
    }
    void LoadClassImageLoader(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ImageLoader> bindImageLoader
            = tguiNamespace.new_usertype<tgui::ImageLoader>(
                "ImageLoader", sol::call_constructor, sol::default_constructor);
        bindImageLoader["loadFromFile"] = &tgui::ImageLoader::loadFromFile;
        bindImageLoader["loadFromMemory"] = &tgui::ImageLoader::loadFromMemory;
    }
    void LoadClassRelativeValue(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RelativeValue> bindRelativeValue
            = tguiNamespace.new_usertype<tgui::RelativeValue>("RelativeValue",
                sol::call_constructor, sol::constructors<tgui::RelativeValue(float)>(),
                sol::base_classes, sol::bases<tgui::AbsoluteOrRelativeValue>());
    }
    void LoadClassRelFloatRect(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RelFloatRect> bindRelFloatRect
            = tguiNamespace.new_usertype<tgui::RelFloatRect>("RelFloatRect",
                sol::call_constructor,
                sol::constructors<tgui::RelFloatRect(),
                    tgui::RelFloatRect(gui::AbsoluteOrRelativeValue,
                        gui::AbsoluteOrRelativeValue, gui::AbsoluteOrRelativeValue,
                        gui::AbsoluteOrRelativeValue)>());
        bindRelFloatRect["getLeft"] = &tgui::RelFloatRect::getLeft;
        bindRelFloatRect["getTop"] = &tgui::RelFloatRect::getTop;
        bindRelFloatRect["getWidth"] = &tgui::RelFloatRect::getWidth;
        bindRelFloatRect["getHeight"] = &tgui::RelFloatRect::getHeight;
        bindRelFloatRect["getPosition"] = &tgui::RelFloatRect::getPosition;
        bindRelFloatRect["getSize"] = &tgui::RelFloatRect::getSize;
        bindRelFloatRect["getRect"] = &tgui::RelFloatRect::getRect;
        bindRelFloatRect["updateParentSize"] = &tgui::RelFloatRect::updateParentSize;
    }
    void LoadClassRendererData(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RendererData> bindRendererData
            = tguiNamespace.new_usertype<tgui::RendererData>("RendererData",
                sol::call_constructor, sol::constructors<tgui::RendererData()>());
        bindRendererData["create"] = sol::overload(
            [](tgui::RendererData* self) -> std::shared_ptr<gui::RendererData> {
                return self->create();
            },
            [](tgui::RendererData* self,
                const std::map<gui::String, ObjectConverter>& init)
                -> std::shared_ptr<gui::RendererData> { return self->create(init); });
        bindRendererData["createFromDataIONode"]
            = &tgui::RendererData::createFromDataIONode;
        bindRendererData["propertyValuePairs"] = &tgui::RendererData::propertyValuePairs;
        bindRendererData["observers"] = &tgui::RendererData::observers;
        bindRendererData["shared"] = &tgui::RendererData::shared;
    }
    void LoadClassRenderStates(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RenderStates> bindRenderStates
            = tguiNamespace.new_usertype<tgui::RenderStates>(
                "RenderStates", sol::call_constructor, sol::default_constructor);
        bindRenderStates["transform"] = &tgui::RenderStates::transform;
    }
    void LoadClassTextureData(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TextureData> bindTextureData
            = tguiNamespace.new_usertype<tgui::TextureData>(
                "TextureData", sol::call_constructor, sol::default_constructor);
        bindTextureData["svgImage"] = &tgui::TextureData::svgImage;
        bindTextureData["backendTexture"] = &tgui::TextureData::backendTexture;
    }
    void LoadClassTextureDataHolder(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TextureDataHolder> bindTextureDataHolder
            = tguiNamespace.new_usertype<tgui::TextureDataHolder>(
                "TextureDataHolder", sol::call_constructor, sol::default_constructor);
        bindTextureDataHolder["data"] = &tgui::TextureDataHolder::data;
        bindTextureDataHolder["filename"] = &tgui::TextureDataHolder::filename;
        bindTextureDataHolder["smooth"] = &tgui::TextureDataHolder::smooth;
        bindTextureDataHolder["users"] = &tgui::TextureDataHolder::users;
    }
    void LoadClassVertex(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Vertex> bindVertex
            = tguiNamespace.new_usertype<tgui::Vertex>("Vertex", sol::call_constructor,
                sol::constructors<tgui::Vertex(), tgui::Vertex(tgui::Vector2f),
                    tgui::Vertex(tgui::Vector2f, gui::Vertex::Color),
                    tgui::Vertex(tgui::Vector2f, gui::Vertex::Color, tgui::Vector2f)>());
        bindVertex["position"] = &tgui::Vertex::position;
        bindVertex["color"] = &tgui::Vertex::color;
        bindVertex["texCoords"] = &tgui::Vertex::texCoords;
    }
    void LoadFunctionAnyCast(sol::state_view state)
    {
    }
    void LoadFunctionIsBackendSet(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("isBackendSet", tgui::isBackendSet);
    }
    void LoadFunctionSetBackend(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("setBackend", tgui::setBackend);
    }
    void LoadFunctionGetBackend(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("getBackend", tgui::getBackend);
    }
    void LoadFunctionSetGlobalTextSize(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("setGlobalTextSize", tgui::setGlobalTextSize);
    }
    void LoadFunctionGetGlobalTextSize(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("getGlobalTextSize", tgui::getGlobalTextSize);
    }
    void LoadFunctionSetDoubleClickTime(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("setDoubleClickTime", tgui::setDoubleClickTime);
    }
    void LoadFunctionGetDoubleClickTime(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("getDoubleClickTime", tgui::getDoubleClickTime);
    }
    void LoadFunctionSetResourcePath(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("setResourcePath",
            sol::overload(static_cast<TGUI_API void (*)(const gui::Filesystem::Path&)>(
                              tgui::setResourcePath),
                static_cast<TGUI_API void (*)(const gui::String&)>(
                    tgui::setResourcePath)));
    }
    void LoadFunctionGetResourcePath(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("getResourcePath", tgui::getResourcePath);
    }
    void LoadFunctionSetEditCursorBlinkRate(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function(
            "setEditCursorBlinkRate", tgui::setEditCursorBlinkRate);
    }
    void LoadFunctionGetEditCursorBlinkRate(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function(
            "getEditCursorBlinkRate", tgui::getEditCursorBlinkRate);
    }
    void LoadFunctionReadFileToMemory(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("readFileToMemory", tgui::readFileToMemory);
    }
    void LoadFunctionBindPosX(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindPosX", tgui::bindPosX);
    }
    void LoadFunctionBindPosY(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindPosY", tgui::bindPosY);
    }
    void LoadFunctionBindLeft(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindLeft", tgui::bindLeft);
    }
    void LoadFunctionBindTop(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindTop", tgui::bindTop);
    }
    void LoadFunctionBindWidth(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindWidth",
            sol::overload(
                static_cast<TGUI_API gui::Layout (*)(std::shared_ptr<gui::Widget>)>(
                    tgui::bindWidth),
                static_cast<TGUI_API gui::Layout (*)(gui::GuiBase&)>(tgui::bindWidth)));
    }
    void LoadFunctionBindHeight(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindHeight",
            sol::overload(
                static_cast<TGUI_API gui::Layout (*)(std::shared_ptr<gui::Widget>)>(
                    tgui::bindHeight),
                static_cast<TGUI_API gui::Layout (*)(gui::GuiBase&)>(tgui::bindHeight)));
    }
    void LoadFunctionBindInnerWidth(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindInnerWidth", tgui::bindInnerWidth);
    }
    void LoadFunctionBindInnerHeight(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindInnerHeight", tgui::bindInnerHeight);
    }
    void LoadFunctionBindRight(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindRight", tgui::bindRight);
    }
    void LoadFunctionBindBottom(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindBottom", tgui::bindBottom);
    }
    void LoadFunctionBindPosition(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindPosition", tgui::bindPosition);
    }
    void LoadFunctionBindSize(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindSize",
            sol::overload(
                static_cast<TGUI_API gui::Layout2d (*)(std::shared_ptr<gui::Widget>)>(
                    tgui::bindSize),
                static_cast<TGUI_API gui::Layout2d (*)(gui::GuiBase&)>(tgui::bindSize)));
    }
    void LoadFunctionBindInnerSize(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindInnerSize", tgui::bindInnerSize);
    }
    void LoadFunctionBindMin(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindMin", tgui::bindMin);
    }
    void LoadFunctionBindMax(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("bindMax", tgui::bindMax);
    }
    void LoadFunctionIsWhitespace(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.set_function("isWhitespace",
            sol::overload(static_cast<TGUI_API bool (*)(char)>(tgui::isWhitespace),
                static_cast<TGUI_API bool (*)(char32_t)>(tgui::isWhitespace)));
    }
};