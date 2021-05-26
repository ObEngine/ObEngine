#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Sprite.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSprite(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Sprite> bindSprite
            = tguiNamespace.new_usertype<tgui::Sprite>("Sprite", sol::call_constructor,
                sol::constructors<tgui::Sprite(), tgui::Sprite(const tgui::Texture&),
                    tgui::Sprite(const tgui::Sprite&)>());
        bindSprite["operator="] = sol::overload(
            static_cast<tgui::Sprite& (tgui::Sprite::*)(const tgui::Sprite&)>(
                &tgui::Sprite::operator=),
            [](tgui::Sprite* self, tgui::Sprite p0) { self->operator=(std::move(p0)); });
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
};