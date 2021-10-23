#include <Bindings/tgui/priv/dev/dev.hpp>

#include <TGUI/Components.hpp>

#include <Bindings/Config.hpp>

namespace tgui::priv::dev::Bindings
{
    void LoadEnumComponentState(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        devNamespace.new_enum<tgui::priv::dev::ComponentState>("ComponentState",
            { { "Normal", tgui::priv::dev::ComponentState::Normal },
                { "Hover", tgui::priv::dev::ComponentState::Hover },
                { "Active", tgui::priv::dev::ComponentState::Active },
                { "ActiveHover", tgui::priv::dev::ComponentState::ActiveHover },
                { "Focused", tgui::priv::dev::ComponentState::Focused },
                { "FocusedHover", tgui::priv::dev::ComponentState::FocusedHover },
                { "FocusedActive", tgui::priv::dev::ComponentState::FocusedActive },
                { "FocusedActiveHover",
                    tgui::priv::dev::ComponentState::FocusedActiveHover },
                { "Disabled", tgui::priv::dev::ComponentState::Disabled },
                { "DisabledActive", tgui::priv::dev::ComponentState::DisabledActive } });
    }
    void LoadEnumAlignLayout(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        devNamespace.new_enum<tgui::priv::dev::AlignLayout>("AlignLayout",
            { { "None", tgui::priv::dev::AlignLayout::None },
                { "Top", tgui::priv::dev::AlignLayout::Top },
                { "Left", tgui::priv::dev::AlignLayout::Left },
                { "Right", tgui::priv::dev::AlignLayout::Right },
                { "Bottom", tgui::priv::dev::AlignLayout::Bottom },
                { "Leftmost", tgui::priv::dev::AlignLayout::Leftmost },
                { "Rightmost", tgui::priv::dev::AlignLayout::Rightmost },
                { "Fill", tgui::priv::dev::AlignLayout::Fill } });
    }
    void LoadEnumPositionAlignment(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        devNamespace.new_enum<tgui::priv::dev::PositionAlignment>("PositionAlignment",
            { { "None", tgui::priv::dev::PositionAlignment::None },
                { "TopLeft", tgui::priv::dev::PositionAlignment::TopLeft },
                { "Top", tgui::priv::dev::PositionAlignment::Top },
                { "TopRight", tgui::priv::dev::PositionAlignment::TopRight },
                { "Right", tgui::priv::dev::PositionAlignment::Right },
                { "BottomRight", tgui::priv::dev::PositionAlignment::BottomRight },
                { "Bottom", tgui::priv::dev::PositionAlignment::Bottom },
                { "BottomLeft", tgui::priv::dev::PositionAlignment::BottomLeft },
                { "Left", tgui::priv::dev::PositionAlignment::Left },
                { "Center", tgui::priv::dev::PositionAlignment::Center } });
    }
    void LoadClassBackgroundComponent(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        sol::usertype<tgui::priv::dev::BackgroundComponent> bindBackgroundComponent
            = devNamespace.new_usertype<tgui::priv::dev::BackgroundComponent>(
                "BackgroundComponent", sol::call_constructor,
                sol::constructors<tgui::priv::dev::BackgroundComponent(
                                      gui::priv::dev::StylePropertyBackground*),
                    tgui::priv::dev::BackgroundComponent(
                        const gui::priv::dev::BackgroundComponent&),
                    tgui::priv::dev::BackgroundComponent(
                        const gui::priv::dev::BackgroundComponent&,
                        gui::priv::dev::StylePropertyBackground*)>(),
                sol::base_classes,
                sol::bases<tgui::priv::dev::GroupComponent,
                    tgui::priv::dev::Component>());
        bindBackgroundComponent["operator="]
            = &tgui::priv::dev::BackgroundComponent::operator=;
        bindBackgroundComponent["init"] = &tgui::priv::dev::BackgroundComponent::init;
        bindBackgroundComponent["setSize"]
            = &tgui::priv::dev::BackgroundComponent::setSize;
        bindBackgroundComponent["setBorders"]
            = &tgui::priv::dev::BackgroundComponent::setBorders;
        bindBackgroundComponent["getBorders"]
            = &tgui::priv::dev::BackgroundComponent::getBorders;
        bindBackgroundComponent["setPadding"]
            = &tgui::priv::dev::BackgroundComponent::setPadding;
        bindBackgroundComponent["getPadding"]
            = &tgui::priv::dev::BackgroundComponent::getPadding;
        bindBackgroundComponent["setOpacity"]
            = &tgui::priv::dev::BackgroundComponent::setOpacity;
        bindBackgroundComponent["setComponentState"]
            = &tgui::priv::dev::BackgroundComponent::setComponentState;
        bindBackgroundComponent["isTransparentPixel"]
            = &tgui::priv::dev::BackgroundComponent::isTransparentPixel;
        bindBackgroundComponent["draw"] = &tgui::priv::dev::BackgroundComponent::draw;
        bindBackgroundComponent["getSizeWithoutBorders"]
            = &tgui::priv::dev::BackgroundComponent::getSizeWithoutBorders;
        bindBackgroundComponent["updateLayout"]
            = &tgui::priv::dev::BackgroundComponent::updateLayout;
        bindBackgroundComponent["clone"] = &tgui::priv::dev::BackgroundComponent::clone;
    }
    void LoadClassComponent(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        sol::usertype<tgui::priv::dev::Component> bindComponent
            = devNamespace.new_usertype<tgui::priv::dev::Component>("Component");
        bindComponent["operator="] = sol::overload(
            static_cast<gui::priv::dev::Component& (
                tgui::priv::dev::Component::*)(const gui::priv::dev::Component&)>(
                &tgui::priv::dev::Component::operator=),
            static_cast<gui::priv::dev::Component& (
                tgui::priv::dev::Component::*)(gui::priv::dev::Component &&)>(
                &tgui::priv::dev::Component::operator=));
        bindComponent["setPosition"] = &tgui::priv::dev::Component::setPosition;
        bindComponent["getPosition"] = &tgui::priv::dev::Component::getPosition;
        bindComponent["getSize"] = &tgui::priv::dev::Component::getSize;
        bindComponent["setPositionAlignment"]
            = &tgui::priv::dev::Component::setPositionAlignment;
        bindComponent["setVisible"] = &tgui::priv::dev::Component::setVisible;
        bindComponent["isVisible"] = &tgui::priv::dev::Component::isVisible;
        bindComponent["setParent"] = &tgui::priv::dev::Component::setParent;
        bindComponent["draw"] = &tgui::priv::dev::Component::draw;
        bindComponent["updateLayout"] = &tgui::priv::dev::Component::updateLayout;
        bindComponent["clone"] = &tgui::priv::dev::Component::clone;
    }
    void LoadClassGroupComponent(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        sol::usertype<tgui::priv::dev::GroupComponent> bindGroupComponent
            = devNamespace.new_usertype<tgui::priv::dev::GroupComponent>("GroupComponent",
                sol::call_constructor,
                sol::constructors<tgui::priv::dev::GroupComponent(
                                      const gui::priv::dev::GroupComponent&),
                    tgui::priv::dev::GroupComponent(gui::priv::dev::GroupComponent &&)>(),
                sol::base_classes, sol::bases<tgui::priv::dev::Component>());
        bindGroupComponent["operator="] = sol::overload(
            static_cast<gui::priv::dev::GroupComponent& (tgui::priv::dev::
                    GroupComponent::*)(const gui::priv::dev::GroupComponent&)>(
                &tgui::priv::dev::GroupComponent::operator=),
            static_cast<gui::priv::dev::GroupComponent& (
                tgui::priv::dev::GroupComponent::*)(gui::priv::dev::GroupComponent &&)>(
                &tgui::priv::dev::GroupComponent::operator=));
        bindGroupComponent["getClientSize"]
            = &tgui::priv::dev::GroupComponent::getClientSize;
        bindGroupComponent["addComponent"]
            = &tgui::priv::dev::GroupComponent::addComponent;
        bindGroupComponent["getComponents"]
            = &tgui::priv::dev::GroupComponent::getComponents;
        bindGroupComponent["draw"] = &tgui::priv::dev::GroupComponent::draw;
        bindGroupComponent["updateLayout"]
            = &tgui::priv::dev::GroupComponent::updateLayout;
        bindGroupComponent["clone"] = &tgui::priv::dev::GroupComponent::clone;
    }
    void LoadClassImageComponent(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        sol::usertype<tgui::priv::dev::ImageComponent> bindImageComponent
            = devNamespace.new_usertype<tgui::priv::dev::ImageComponent>("ImageComponent",
                sol::call_constructor,
                sol::constructors<tgui::priv::dev::ImageComponent(
                                      gui::priv::dev::StyleProperty<Texture>*),
                    tgui::priv::dev::ImageComponent(
                        const gui::priv::dev::ImageComponent&),
                    tgui::priv::dev::ImageComponent(const gui::priv::dev::ImageComponent&,
                        gui::priv::dev::StyleProperty<Texture>*)>(),
                sol::base_classes, sol::bases<tgui::priv::dev::Component>());
        bindImageComponent["operator="] = &tgui::priv::dev::ImageComponent::operator=;
        bindImageComponent["init"] = &tgui::priv::dev::ImageComponent::init;
        bindImageComponent["setSize"] = &tgui::priv::dev::ImageComponent::setSize;
        bindImageComponent["setOpacity"] = &tgui::priv::dev::ImageComponent::setOpacity;
        bindImageComponent["setComponentState"]
            = &tgui::priv::dev::ImageComponent::setComponentState;
        bindImageComponent["isTransparentPixel"]
            = &tgui::priv::dev::ImageComponent::isTransparentPixel;
        bindImageComponent["draw"] = &tgui::priv::dev::ImageComponent::draw;
        bindImageComponent["clone"] = &tgui::priv::dev::ImageComponent::clone;
    }
    void LoadClassMessageBroker(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        sol::usertype<tgui::priv::dev::MessageBroker> bindMessageBroker
            = devNamespace.new_usertype<tgui::priv::dev::MessageBroker>(
                "MessageBroker", sol::call_constructor, sol::default_constructor);
        bindMessageBroker["createTopic"] = &tgui::priv::dev::MessageBroker::createTopic;
        bindMessageBroker["destroyTopic"] = &tgui::priv::dev::MessageBroker::destroyTopic;
        bindMessageBroker["subscribe"] = &tgui::priv::dev::MessageBroker::subscribe;
        bindMessageBroker["unsubscribe"] = &tgui::priv::dev::MessageBroker::unsubscribe;
        bindMessageBroker["sendEvent"] = &tgui::priv::dev::MessageBroker::sendEvent;
    }
    void LoadClassStylePropertyBase(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        sol::usertype<tgui::priv::dev::StylePropertyBase> bindStylePropertyBase
            = devNamespace.new_usertype<tgui::priv::dev::StylePropertyBase>(
                "StylePropertyBase", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassTextComponent(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        sol::usertype<tgui::priv::dev::TextComponent> bindTextComponent
            = devNamespace.new_usertype<tgui::priv::dev::TextComponent>("TextComponent",
                sol::call_constructor,
                sol::constructors<tgui::priv::dev::TextComponent(
                                      gui::priv::dev::StylePropertyText*),
                    tgui::priv::dev::TextComponent(const gui::priv::dev::TextComponent&),
                    tgui::priv::dev::TextComponent(const gui::priv::dev::TextComponent&,
                        gui::priv::dev::StylePropertyText*)>(),
                sol::base_classes, sol::bases<tgui::priv::dev::Component>());
        bindTextComponent["operator="] = &tgui::priv::dev::TextComponent::operator=;
        bindTextComponent["init"] = &tgui::priv::dev::TextComponent::init;
        bindTextComponent["setString"] = &tgui::priv::dev::TextComponent::setString;
        bindTextComponent["getString"] = &tgui::priv::dev::TextComponent::getString;
        bindTextComponent["setCharacterSize"]
            = &tgui::priv::dev::TextComponent::setCharacterSize;
        bindTextComponent["getCharacterSize"]
            = &tgui::priv::dev::TextComponent::getCharacterSize;
        bindTextComponent["setFont"] = &tgui::priv::dev::TextComponent::setFont;
        bindTextComponent["getFont"] = &tgui::priv::dev::TextComponent::getFont;
        bindTextComponent["setOutlineColor"]
            = &tgui::priv::dev::TextComponent::setOutlineColor;
        bindTextComponent["getOutlineColor"]
            = &tgui::priv::dev::TextComponent::getOutlineColor;
        bindTextComponent["setOutlineThickness"]
            = &tgui::priv::dev::TextComponent::setOutlineThickness;
        bindTextComponent["getOutlineThickness"]
            = &tgui::priv::dev::TextComponent::getOutlineThickness;
        bindTextComponent["getLineHeight"]
            = &tgui::priv::dev::TextComponent::getLineHeight;
        bindTextComponent["setOpacity"] = &tgui::priv::dev::TextComponent::setOpacity;
        bindTextComponent["updateLayout"] = &tgui::priv::dev::TextComponent::updateLayout;
        bindTextComponent["setComponentState"]
            = &tgui::priv::dev::TextComponent::setComponentState;
        bindTextComponent["draw"] = &tgui::priv::dev::TextComponent::draw;
        bindTextComponent["clone"] = &tgui::priv::dev::TextComponent::clone;
    }
    void LoadClassStylePropertyBackground(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        sol::usertype<tgui::priv::dev::StylePropertyBackground>
            bindStylePropertyBackground
            = devNamespace.new_usertype<tgui::priv::dev::StylePropertyBackground>(
                "StylePropertyBackground", sol::call_constructor,
                sol::default_constructor);
        bindStylePropertyBackground["borderColor"]
            = &tgui::priv::dev::StylePropertyBackground::borderColor;
        bindStylePropertyBackground["color"]
            = &tgui::priv::dev::StylePropertyBackground::color;
        bindStylePropertyBackground["texture"]
            = &tgui::priv::dev::StylePropertyBackground::texture;
        bindStylePropertyBackground["borders"]
            = &tgui::priv::dev::StylePropertyBackground::borders;
        bindStylePropertyBackground["padding"]
            = &tgui::priv::dev::StylePropertyBackground::padding;
        bindStylePropertyBackground["roundedBorderRadius"]
            = &tgui::priv::dev::StylePropertyBackground::roundedBorderRadius;
    }
    void LoadClassStylePropertyText(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        sol::usertype<tgui::priv::dev::StylePropertyText> bindStylePropertyText
            = devNamespace.new_usertype<tgui::priv::dev::StylePropertyText>(
                "StylePropertyText", sol::call_constructor, sol::default_constructor);
        bindStylePropertyText["color"] = &tgui::priv::dev::StylePropertyText::color;
        bindStylePropertyText["style"] = &tgui::priv::dev::StylePropertyText::style;
    }
    void LoadFunctionGetStateFromFlags(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        devNamespace.set_function(
            "getStateFromFlags", tgui::priv::dev::getStateFromFlags);
    }
    void LoadFunctionSetOptionalPropertyValue(sol::state_view state)
    {
        sol::table devNamespace = state["tgui"]["priv"]["dev"].get<sol::table>();
        devNamespace.set_function("setOptionalPropertyValue",
            sol::overload(static_cast<void (*)(gui::priv::dev::StyleProperty<Color>&,
                              const gui::Color&, tgui::priv::dev::ComponentState)>(
                              tgui::priv::dev::setOptionalPropertyValue),
                static_cast<void (*)(gui::priv::dev::StyleProperty<TextStyles>&,
                    const gui::TextStyles&, tgui::priv::dev::ComponentState)>(
                    tgui::priv::dev::setOptionalPropertyValue),
                static_cast<void (*)(gui::priv::dev::StyleProperty<Texture>&,
                    const gui::Texture&, tgui::priv::dev::ComponentState)>(
                    tgui::priv::dev::setOptionalPropertyValue)));
    }
};