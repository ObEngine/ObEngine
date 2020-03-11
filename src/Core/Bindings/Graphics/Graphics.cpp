#include <Bindings/Graphics/Graphics.hpp>

#include <Graphics/Color.hpp>
#include <Graphics/PositionTransformers.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Sprite.hpp>

#include <sol/sol.hpp>

namespace obe::Graphics::Bindings
{
    void LoadEnumSpriteHandlePointType(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        GraphicsNamespace.new_enum<obe::Graphics::SpriteHandlePointType>(
            "SpriteHandlePointType",
            { { "ScaleHandle", obe::Graphics::SpriteHandlePointType::ScaleHandle },
                { "RotateHandle", obe::Graphics::SpriteHandlePointType::RotateHandle } });
    }
    void LoadClassColor(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        sol::usertype<obe::Graphics::Color> bindColor
            = GraphicsNamespace.new_usertype<obe::Graphics::Color>("Color",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Color(
                                      uint_fast8_t, uint_fast8_t, uint_fast8_t),
                    obe::Graphics::Color(
                        uint_fast8_t, uint_fast8_t, uint_fast8_t, uint_fast8_t),
                    obe::Graphics::Color(const std::string&)>());
        bindColor["fromHex"] = &obe::Graphics::Color::fromHex;
        bindColor["fromRgb"] = &obe::Graphics::Color::fromRgb;
        bindColor["fromHsv"] = &obe::Graphics::Color::fromHsv;
    }
    void LoadClassPositionTransformer(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        sol::usertype<obe::Graphics::PositionTransformer> bindPositionTransformer
            = GraphicsNamespace.new_usertype<obe::Graphics::PositionTransformer>(
                "PositionTransformer", sol::call_constructor,
                sol::constructors<obe::Graphics::PositionTransformer(),
                    obe::Graphics::PositionTransformer(
                        const std::string&, const std::string&)>());
        bindPositionTransformer["getXTransformer"]
            = &obe::Graphics::PositionTransformer::getXTransformer;
        bindPositionTransformer["getXTransformerName"]
            = &obe::Graphics::PositionTransformer::getXTransformerName;
        bindPositionTransformer["getYTransformer"]
            = &obe::Graphics::PositionTransformer::getYTransformer;
        bindPositionTransformer["getYTransformerName"]
            = &obe::Graphics::PositionTransformer::getYTransformerName;
        bindPositionTransformer[sol::meta_function::call]
            = &obe::Graphics::PositionTransformer::operator();
    }
    void LoadClassShader(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        sol::usertype<obe::Graphics::Shader> bindShader
            = GraphicsNamespace.new_usertype<obe::Graphics::Shader>("Shader",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Shader(),
                    obe::Graphics::Shader(const std::string&)>());
        bindShader["dump"] = &obe::Graphics::Shader::dump;
        bindShader["load"] = &obe::Graphics::Shader::load;
        bindShader["loadShader"] = &obe::Graphics::Shader::loadShader;
    }
    void LoadClassSprite(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        sol::usertype<obe::Graphics::Sprite> bindSprite
            = GraphicsNamespace.new_usertype<obe::Graphics::Sprite>("Sprite",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Sprite(const std::string&)>());
        bindSprite["drawHandle"] = &obe::Graphics::Sprite::drawHandle;
        bindSprite["dump"] = &obe::Graphics::Sprite::dump;
        bindSprite["getColor"] = &obe::Graphics::Sprite::getColor;
        bindSprite["getHandlePoint"] = &obe::Graphics::Sprite::getHandlePoint;
        bindSprite["getLayer"] = &obe::Graphics::Sprite::getLayer;
        bindSprite["getParentId"] = &obe::Graphics::Sprite::getParentId;
        bindSprite["getPath"] = &obe::Graphics::Sprite::getPath;
        bindSprite["getPositionTransformer"]
            = &obe::Graphics::Sprite::getPositionTransformer;
        bindSprite["getRect"] = &obe::Graphics::Sprite::getRect;
        bindSprite["getShader"] = &obe::Graphics::Sprite::getShader;
        bindSprite["getSprite"] = &obe::Graphics::Sprite::getSprite;
        bindSprite["getSpriteHeight"] = &obe::Graphics::Sprite::getSpriteHeight;
        bindSprite["getSpriteWidth"] = &obe::Graphics::Sprite::getSpriteWidth;
        bindSprite["getTexture"] = &obe::Graphics::Sprite::getTexture;
        bindSprite["getXScaleFactor"] = &obe::Graphics::Sprite::getXScaleFactor;
        bindSprite["getYScaleFactor"] = &obe::Graphics::Sprite::getYScaleFactor;
        bindSprite["getZDepth"] = &obe::Graphics::Sprite::getZDepth;
        bindSprite["getAntiAliasing"] = &obe::Graphics::Sprite::getAntiAliasing;
        bindSprite["hasShader"] = &obe::Graphics::Sprite::hasShader;
        bindSprite["isVisible"] = &obe::Graphics::Sprite::isVisible;
        bindSprite["load"] = &obe::Graphics::Sprite::load;
        bindSprite["loadTexture"] = &obe::Graphics::Sprite::loadTexture;
        bindSprite["rotate"] = &obe::Graphics::Sprite::rotate;
        bindSprite["setColor"] = &obe::Graphics::Sprite::setColor;
        bindSprite["setLayer"] = &obe::Graphics::Sprite::setLayer;
        bindSprite["setParentId"] = &obe::Graphics::Sprite::setParentId;
        bindSprite["setPositionTransformer"]
            = &obe::Graphics::Sprite::setPositionTransformer;
        bindSprite["setRotation"] = &obe::Graphics::Sprite::setRotation;
        bindSprite["setRotationOrigin"] = &obe::Graphics::Sprite::setRotationOrigin;
        bindSprite["setScalingOrigin"] = &obe::Graphics::Sprite::setScalingOrigin;
        bindSprite["setShader"] = &obe::Graphics::Sprite::setShader;
        bindSprite["setTexture"] = &obe::Graphics::Sprite::setTexture;
        bindSprite["setTextureRect"] = &obe::Graphics::Sprite::setTextureRect;
        bindSprite["setTranslationOrigin"] = &obe::Graphics::Sprite::setTranslationOrigin;
        bindSprite["setVisible"] = &obe::Graphics::Sprite::setVisible;
        bindSprite["setZDepth"] = &obe::Graphics::Sprite::setZDepth;
        bindSprite["setAntiAliasing"] = &obe::Graphics::Sprite::setAntiAliasing;
        bindSprite["useTextureSize"] = &obe::Graphics::Sprite::useTextureSize;
        bindSprite["draw"] = &obe::Graphics::Sprite::draw;
        bindSprite["attachResourceManager"]
            = &obe::Graphics::Sprite::attachResourceManager;
        bindSprite["type"] = &obe::Graphics::Sprite::type;
        bindSprite["m_layerChanged"]
            = sol::readonly(&obe::Graphics::Sprite::m_layerChanged);
    }
    void LoadClassSpriteHandlePoint(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        sol::usertype<obe::Graphics::SpriteHandlePoint> bindSpriteHandlePoint
            = GraphicsNamespace.new_usertype<obe::Graphics::SpriteHandlePoint>(
                "SpriteHandlePoint", sol::call_constructor,
                sol::constructors<obe::Graphics::SpriteHandlePoint(obe::Graphics::Sprite*,
                                      obe::Transform::Referential),
                    obe::Graphics::SpriteHandlePoint(obe::Graphics::Sprite*)>());
        bindSpriteHandlePoint["getRect"] = &obe::Graphics::SpriteHandlePoint::getRect;
        bindSpriteHandlePoint["getReferential"]
            = &obe::Graphics::SpriteHandlePoint::getReferential;
        bindSpriteHandlePoint["getType"] = &obe::Graphics::SpriteHandlePoint::getType;
        bindSpriteHandlePoint["moveTo"] = &obe::Graphics::SpriteHandlePoint::moveTo;
        bindSpriteHandlePoint["m_dp"]
            = sol::readonly(&obe::Graphics::SpriteHandlePoint::m_dp);
    }
    void LoadFunctionInitPositionTransformer(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        GraphicsNamespace.set_function(
            "InitPositionTransformer", obe::Graphics::InitPositionTransformer);
    }
    void LoadFunctionMakeNullTexture(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        GraphicsNamespace.set_function("MakeNullTexture", obe::Graphics::MakeNullTexture);
    }
    void LoadGlobalTransformers(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        GraphicsNamespace["Transformers"] = obe::Graphics::Transformers;
    }
    void LoadGlobalParallax(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        GraphicsNamespace["Parallax"] = obe::Graphics::Parallax;
    }
    void LoadGlobalCamera(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        GraphicsNamespace["Camera"] = obe::Graphics::Camera;
    }
    void LoadGlobalPosition(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        GraphicsNamespace["Position"] = obe::Graphics::Position;
    }
};