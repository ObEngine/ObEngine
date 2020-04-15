#include <Bindings/Graphics/Graphics.hpp>

#include <Graphics/Color.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/PositionTransformers.hpp>
#include <Graphics/RenderTarget.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/Texture.hpp>

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
                sol::constructors<obe::Graphics::Color(),
                    obe::Graphics::Color(uint_fast8_t, uint_fast8_t, uint_fast8_t),
                    obe::Graphics::Color(
                        uint_fast8_t, uint_fast8_t, uint_fast8_t, uint_fast8_t),
                    obe::Graphics::Color(const std::string&),
                    obe::Graphics::Color(const obe::Graphics::Color&),
                    obe::Graphics::Color(const sf::Color&)>());
        bindColor["fromName"] = &obe::Graphics::Color::fromName;
        bindColor["fromString"] = &obe::Graphics::Color::fromString;
        bindColor["fromHex"] = &obe::Graphics::Color::fromHex;
        bindColor["fromRgb"] = sol::overload(
            [](obe::Graphics::Color* self, uint_fast8_t r, uint_fast8_t g,
                uint_fast8_t b) -> void { return self->fromRgb(r, g, b); },
            [](obe::Graphics::Color* self, uint_fast8_t r, uint_fast8_t g, uint_fast8_t b,
                uint_fast8_t p3) -> void { return self->fromRgb(r, g, b, p3); });
        bindColor["fromHsv"] = &obe::Graphics::Color::fromHsv;
        bindColor["toInteger"] = &obe::Graphics::Color::toInteger;
        bindColor[sol::meta_function::addition] = &obe::Graphics::Color::operator+;
        bindColor["r"] = &obe::Graphics::Color::r;
        bindColor["g"] = &obe::Graphics::Color::g;
        bindColor["b"] = &obe::Graphics::Color::b;
        bindColor["a"] = &obe::Graphics::Color::a;
    }
    void LoadClassFont(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        sol::usertype<obe::Graphics::Font> bindFont
            = GraphicsNamespace.new_usertype<obe::Graphics::Font>("Font",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Font(),
                    obe::Graphics::Font(const obe::Graphics::Font&),
                    obe::Graphics::Font(const sf::Font&)>());
        bindFont["loadFromFile"] = &obe::Graphics::Font::loadFromFile;
        bindFont[sol::meta_function::equal_to] = &obe::Graphics::Font::operator==;
        bindFont["operator sf::Font &"] = &obe::Graphics::Font::operator sf::Font&;
        bindFont["operator const sf::Font &"]
            = &obe::Graphics::Font::operator const sf::Font&;
        bindFont["operator bool"] = &obe::Graphics::Font::operator bool;
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
    void LoadClassRenderTarget(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        sol::usertype<obe::Graphics::RenderTarget> bindRenderTarget
            = GraphicsNamespace.new_usertype<obe::Graphics::RenderTarget>("RenderTarget",
                sol::call_constructor,
                sol::constructors<obe::Graphics::RenderTarget(sf::RenderTarget&),
                    obe::Graphics::RenderTarget(sf::RenderWindow&)>());
        bindRenderTarget["draw"] = sol::overload(
            static_cast<void (obe::Graphics::RenderTarget::*)(const sf::Drawable&,
                const sf::RenderStates&) const>(&obe::Graphics::RenderTarget::draw),
            static_cast<void (obe::Graphics::RenderTarget::*)(const sf::Vertex*,
                std::size_t, sf::PrimitiveType, const sf::RenderStates&) const>(
                &obe::Graphics::RenderTarget::draw));
        bindRenderTarget["operator sf::RenderTarget &"]
            = &obe::Graphics::RenderTarget::operator sf::RenderTarget&;
        bindRenderTarget["operator const sf::RenderTarget &"]
            = &obe::Graphics::RenderTarget::operator const sf::RenderTarget&;
    }
    void LoadClassRichText(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        sol::usertype<obe::Graphics::RichText> bindRichText
            = GraphicsNamespace.new_usertype<obe::Graphics::RichText>("RichText",
                sol::call_constructor,
                sol::constructors<obe::Graphics::RichText(),
                    obe::Graphics::RichText(const obe::Graphics::Font&)>(),
                sol::base_classes, sol::bases<sf::Drawable, sf::Transformable>());
        bindRichText["clear"] = &obe::Graphics::RichText::clear;
        bindRichText["append"] = &obe::Graphics::RichText::append;
        bindRichText["getFont"] = &obe::Graphics::RichText::getFont;
        bindRichText["setFont"] = &obe::Graphics::RichText::setFont;
        bindRichText["getLines"] = &obe::Graphics::RichText::getLines;
        bindRichText["getCharacterSize"] = &obe::Graphics::RichText::getCharacterSize;
        bindRichText["setCharacterSize"] = &obe::Graphics::RichText::setCharacterSize;
        bindRichText["getLocalBounds"] = &obe::Graphics::RichText::getLocalBounds;
        bindRichText["getGlobalBounds"] = &obe::Graphics::RichText::getGlobalBounds;
    }
    void LoadClassShader(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        sol::usertype<obe::Graphics::Shader> bindShader
            = GraphicsNamespace.new_usertype<obe::Graphics::Shader>("Shader",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Shader(),
                    obe::Graphics::Shader(const std::string&)>(),
                sol::base_classes, sol::bases<sf::Shader, obe::Types::Serializable>());
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
                sol::constructors<obe::Graphics::Sprite(const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::Transform::UnitBasedObject, obe::Types::Selectable,
                    obe::Transform::Rect, obe::Transform::Movable,
                    obe::Component::Component<Sprite>, obe::Engine::ResourceManagedObject,
                    obe::Types::Identifiable>());
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
        bindSprite["getSize"] = &obe::Graphics::Sprite::getSize;
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
        bindSprite["m_layerChanged"] = &obe::Graphics::Sprite::m_layerChanged;
    }
    void LoadClassSpriteHandlePoint(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        sol::usertype<obe::Graphics::SpriteHandlePoint> bindSpriteHandlePoint
            = GraphicsNamespace.new_usertype<obe::Graphics::SpriteHandlePoint>(
                "SpriteHandlePoint", sol::call_constructor,
                sol::constructors<obe::Graphics::SpriteHandlePoint(obe::Graphics::Sprite&,
                                      obe::Transform::Referential),
                    obe::Graphics::SpriteHandlePoint(obe::Graphics::Sprite&)>());
        bindSpriteHandlePoint["getRect"] = &obe::Graphics::SpriteHandlePoint::getRect;
        bindSpriteHandlePoint["getReferential"]
            = &obe::Graphics::SpriteHandlePoint::getReferential;
        bindSpriteHandlePoint["getType"] = &obe::Graphics::SpriteHandlePoint::getType;
        bindSpriteHandlePoint["moveTo"] = &obe::Graphics::SpriteHandlePoint::moveTo;
        bindSpriteHandlePoint["m_dp"] = &obe::Graphics::SpriteHandlePoint::m_dp;
    }
    void LoadClassText(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        sol::usertype<obe::Graphics::Text> bindText
            = GraphicsNamespace.new_usertype<obe::Graphics::Text>("Text",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Text(),
                    obe::Graphics::Text(const std::string&)>());
        bindText["color"] = &obe::Graphics::Text::color;
        bindText["outline"] = &obe::Graphics::Text::outline;
        bindText["thickness"] = &obe::Graphics::Text::thickness;
        bindText["style"] = &obe::Graphics::Text::style;
        bindText["string"] = &obe::Graphics::Text::string;
    }
    void LoadClassTexture(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["Graphics"].get<sol::table>();
        sol::usertype<obe::Graphics::Texture> bindTexture
            = GraphicsNamespace.new_usertype<obe::Graphics::Texture>("Texture",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Texture(),
                    obe::Graphics::Texture(const sf::Texture&),
                    obe::Graphics::Texture(const obe::Graphics::Texture&)>());
        bindTexture["create"] = &obe::Graphics::Texture::create;
        bindTexture["loadFromFile"] = sol::overload(
            static_cast<bool (obe::Graphics::Texture::*)(const std::string&)>(
                &obe::Graphics::Texture::loadFromFile),
            static_cast<bool (obe::Graphics::Texture::*)(const std::string&,
                const obe::Transform::Rect&)>(&obe::Graphics::Texture::loadFromFile));
        bindTexture["loadFromImage"] = &obe::Graphics::Texture::loadFromImage;
        bindTexture["getSize"] = &obe::Graphics::Texture::getSize;
        bindTexture["setAntiAliasing"] = &obe::Graphics::Texture::setAntiAliasing;
        bindTexture["isAntiAliased"] = &obe::Graphics::Texture::isAntiAliased;
        bindTexture["setRepeated"] = &obe::Graphics::Texture::setRepeated;
        bindTexture["isRepeated"] = &obe::Graphics::Texture::isRepeated;
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