#include <Bindings/obe/Graphics/Graphics.hpp>

#include <Graphics/Color.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/PositionTransformers.hpp>
#include <Graphics/RenderTarget.hpp>
#include <Graphics/Renderable.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/Texture.hpp>

#include <Bindings/Config.hpp>

namespace obe::graphics::Bindings
{
    void LoadEnumColorType(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        GraphicsNamespace.new_enum<obe::graphics::ColorType>("ColorType",
            { { "Rgba", obe::graphics::ColorType::Rgba }, { "Hsv", obe::graphics::ColorType::Hsv },
                { "Hex", obe::graphics::ColorType::Hex },
                { "ColorName", obe::graphics::ColorType::ColorName } });
    }
    void LoadEnumSpriteHandlePointType(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        GraphicsNamespace.new_enum<obe::graphics::SpriteHandlePointType>("SpriteHandlePointType",
            { { "ScaleHandle", obe::graphics::SpriteHandlePointType::ScaleHandle },
                { "RotateHandle", obe::graphics::SpriteHandlePointType::RotateHandle } });
    }
    void LoadClassColor(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Color> bindColor = GraphicsNamespace.new_usertype<
            obe::graphics::Color>("Color", sol::call_constructor,
            sol::constructors<obe::graphics::Color(), obe::graphics::Color(double, double, double),
                obe::graphics::Color(double, double, double, double),
                obe::graphics::Color(const std::string&), obe::graphics::Color(const sf::Color&)>(),
            sol::base_classes, sol::bases<obe::Types::Serializable>());
        bindColor["dump"] = sol::overload(
            static_cast<vili::node (obe::graphics::Color::*)(obe::graphics::ColorType) const>(
                &obe::graphics::Color::dump),
            static_cast<vili::node (obe::graphics::Color::*)() const>(&obe::graphics::Color::dump));
        bindColor["load"] = &obe::graphics::Color::load;
        bindColor["from_string"] = &obe::graphics::Color::from_string;
        bindColor["from_name"]
            = sol::overload([](obe::graphics::Color* self,
                                std::string name) -> bool { return self->from_name(name); },
                [](obe::graphics::Color* self, std::string name, bool strict) -> bool {
                    return self->from_name(name, strict);
                });
        bindColor["from_hex"] = &obe::graphics::Color::from_hex;
        bindColor["from_rgb"]
            = sol::overload([](obe::graphics::Color* self, double r, double g,
                                double b) -> void { return self->from_rgb(r, g, b); },
                [](obe::graphics::Color* self, double r, double g, double b, double a) -> void {
                    return self->from_rgb(r, g, b, a);
                });
        bindColor["from_hsv"] = &obe::graphics::Color::from_hsv;
        bindColor["to_integer"] = &obe::graphics::Color::to_integer;
        bindColor["to_hex"] = &obe::graphics::Color::to_hex;
        bindColor["to_name"] = &obe::graphics::Color::to_name;
        bindColor["to_hsv"] = &obe::graphics::Color::to_hsv;
        bindColor["to_string"] = &obe::graphics::Color::to_string;
        bindColor[sol::meta_function::equal_to] = &obe::graphics::Color::operator==;
        bindColor[sol::meta_function::addition] = &obe::graphics::Color::operator+;
        bindColor[sol::meta_function::subtraction]
            = static_cast<obe::graphics::Color (obe::graphics::Color::*)(
                const obe::graphics::Color&) const>(&obe::graphics::Color::operator-);
        bindColor[sol::meta_function::unary_minus]
            = static_cast<obe::graphics::Color (obe::graphics::Color::*)() const>(
                &obe::graphics::Color::operator-);
        bindColor[sol::meta_function::multiplication] = sol::overload(
            static_cast<obe::graphics::Color (obe::graphics::Color::*)(const obe::graphics::Color&)
                    const>(&obe::graphics::Color::operator*),
            static_cast<obe::graphics::Color (obe::graphics::Color::*)(double) const>(
                &obe::graphics::Color::operator*));
        bindColor[sol::meta_function::division] = sol::overload(
            static_cast<obe::graphics::Color (obe::graphics::Color::*)(const obe::graphics::Color&)
                    const>(&obe::graphics::Color::operator/),
            static_cast<obe::graphics::Color (obe::graphics::Color::*)(double) const>(
                &obe::graphics::Color::operator/));
        bindColor["Random"]
            = sol::overload([]() -> obe::graphics::Color { return obe::graphics::Color::Random(); },
                [](bool randomAlpha) -> obe::graphics::Color {
                    return obe::graphics::Color::Random(randomAlpha);
                });
        bindColor["r"] = &obe::graphics::Color::r;
        bindColor["g"] = &obe::graphics::Color::g;
        bindColor["b"] = &obe::graphics::Color::b;
        bindColor["a"] = &obe::graphics::Color::a;
        bindColor["AliceBlue"] = sol::var(&obe::graphics::Color::AliceBlue);
        bindColor["AntiqueWhite"] = sol::var(&obe::graphics::Color::AntiqueWhite);
        bindColor["Aqua"] = sol::var(&obe::graphics::Color::Aqua);
        bindColor["Aquamarine"] = sol::var(&obe::graphics::Color::Aquamarine);
        bindColor["Azure"] = sol::var(&obe::graphics::Color::Azure);
        bindColor["Beige"] = sol::var(&obe::graphics::Color::Beige);
        bindColor["Bisque"] = sol::var(&obe::graphics::Color::Bisque);
        bindColor["Black"] = sol::var(&obe::graphics::Color::Black);
        bindColor["BlanchedAlmond"] = sol::var(&obe::graphics::Color::BlanchedAlmond);
        bindColor["Blue"] = sol::var(&obe::graphics::Color::Blue);
        bindColor["BlueViolet"] = sol::var(&obe::graphics::Color::BlueViolet);
        bindColor["Brown"] = sol::var(&obe::graphics::Color::Brown);
        bindColor["BurlyWood"] = sol::var(&obe::graphics::Color::BurlyWood);
        bindColor["CadetBlue"] = sol::var(&obe::graphics::Color::CadetBlue);
        bindColor["Chartreuse"] = sol::var(&obe::graphics::Color::Chartreuse);
        bindColor["Chocolate"] = sol::var(&obe::graphics::Color::Chocolate);
        bindColor["Coral"] = sol::var(&obe::graphics::Color::Coral);
        bindColor["CornflowerBlue"] = sol::var(&obe::graphics::Color::CornflowerBlue);
        bindColor["Cornsilk"] = sol::var(&obe::graphics::Color::Cornsilk);
        bindColor["Crimson"] = sol::var(&obe::graphics::Color::Crimson);
        bindColor["Cyan"] = sol::var(&obe::graphics::Color::Cyan);
        bindColor["DarkBlue"] = sol::var(&obe::graphics::Color::DarkBlue);
        bindColor["DarkCyan"] = sol::var(&obe::graphics::Color::DarkCyan);
        bindColor["DarkGoldenrod"] = sol::var(&obe::graphics::Color::DarkGoldenrod);
        bindColor["DarkGray"] = sol::var(&obe::graphics::Color::DarkGray);
        bindColor["DarkGreen"] = sol::var(&obe::graphics::Color::DarkGreen);
        bindColor["DarkKhaki"] = sol::var(&obe::graphics::Color::DarkKhaki);
        bindColor["DarkMagenta"] = sol::var(&obe::graphics::Color::DarkMagenta);
        bindColor["DarkOliveGreen"] = sol::var(&obe::graphics::Color::DarkOliveGreen);
        bindColor["DarkOrange"] = sol::var(&obe::graphics::Color::DarkOrange);
        bindColor["DarkOrchid"] = sol::var(&obe::graphics::Color::DarkOrchid);
        bindColor["DarkRed"] = sol::var(&obe::graphics::Color::DarkRed);
        bindColor["DarkSalmon"] = sol::var(&obe::graphics::Color::DarkSalmon);
        bindColor["DarkSeaGreen"] = sol::var(&obe::graphics::Color::DarkSeaGreen);
        bindColor["DarkSlateBlue"] = sol::var(&obe::graphics::Color::DarkSlateBlue);
        bindColor["DarkSlateGray"] = sol::var(&obe::graphics::Color::DarkSlateGray);
        bindColor["DarkTurquoise"] = sol::var(&obe::graphics::Color::DarkTurquoise);
        bindColor["DarkViolet"] = sol::var(&obe::graphics::Color::DarkViolet);
        bindColor["DeepPink"] = sol::var(&obe::graphics::Color::DeepPink);
        bindColor["DeepSkyBlue"] = sol::var(&obe::graphics::Color::DeepSkyBlue);
        bindColor["DimGray"] = sol::var(&obe::graphics::Color::DimGray);
        bindColor["DodgerBlue"] = sol::var(&obe::graphics::Color::DodgerBlue);
        bindColor["FireBrick"] = sol::var(&obe::graphics::Color::FireBrick);
        bindColor["FloralWhite"] = sol::var(&obe::graphics::Color::FloralWhite);
        bindColor["ForestGreen"] = sol::var(&obe::graphics::Color::ForestGreen);
        bindColor["Fuchsia"] = sol::var(&obe::graphics::Color::Fuchsia);
        bindColor["Gainsboro"] = sol::var(&obe::graphics::Color::Gainsboro);
        bindColor["GhostWhite"] = sol::var(&obe::graphics::Color::GhostWhite);
        bindColor["Gold"] = sol::var(&obe::graphics::Color::Gold);
        bindColor["Goldenrod"] = sol::var(&obe::graphics::Color::Goldenrod);
        bindColor["Gray"] = sol::var(&obe::graphics::Color::Gray);
        bindColor["Green"] = sol::var(&obe::graphics::Color::Green);
        bindColor["GreenYellow"] = sol::var(&obe::graphics::Color::GreenYellow);
        bindColor["HoneyDew"] = sol::var(&obe::graphics::Color::HoneyDew);
        bindColor["HotPink"] = sol::var(&obe::graphics::Color::HotPink);
        bindColor["IndianRed"] = sol::var(&obe::graphics::Color::IndianRed);
        bindColor["Indigo"] = sol::var(&obe::graphics::Color::Indigo);
        bindColor["Ivory"] = sol::var(&obe::graphics::Color::Ivory);
        bindColor["Khaki"] = sol::var(&obe::graphics::Color::Khaki);
        bindColor["Lavender"] = sol::var(&obe::graphics::Color::Lavender);
        bindColor["LavenderBlush"] = sol::var(&obe::graphics::Color::LavenderBlush);
        bindColor["LawnGreen"] = sol::var(&obe::graphics::Color::LawnGreen);
        bindColor["LemonChiffon"] = sol::var(&obe::graphics::Color::LemonChiffon);
        bindColor["LightBlue"] = sol::var(&obe::graphics::Color::LightBlue);
        bindColor["LightCoral"] = sol::var(&obe::graphics::Color::LightCoral);
        bindColor["LightCyan"] = sol::var(&obe::graphics::Color::LightCyan);
        bindColor["LightGoldenrodYellow"] = sol::var(&obe::graphics::Color::LightGoldenrodYellow);
        bindColor["LightGray"] = sol::var(&obe::graphics::Color::LightGray);
        bindColor["LightGreen"] = sol::var(&obe::graphics::Color::LightGreen);
        bindColor["LightPink"] = sol::var(&obe::graphics::Color::LightPink);
        bindColor["LightSalmon"] = sol::var(&obe::graphics::Color::LightSalmon);
        bindColor["LightSeaGreen"] = sol::var(&obe::graphics::Color::LightSeaGreen);
        bindColor["LightSkyBlue"] = sol::var(&obe::graphics::Color::LightSkyBlue);
        bindColor["LightSlateGray"] = sol::var(&obe::graphics::Color::LightSlateGray);
        bindColor["LightSteelBlue"] = sol::var(&obe::graphics::Color::LightSteelBlue);
        bindColor["LightYellow"] = sol::var(&obe::graphics::Color::LightYellow);
        bindColor["Lime"] = sol::var(&obe::graphics::Color::Lime);
        bindColor["LimeGreen"] = sol::var(&obe::graphics::Color::LimeGreen);
        bindColor["Linen"] = sol::var(&obe::graphics::Color::Linen);
        bindColor["Magenta"] = sol::var(&obe::graphics::Color::Magenta);
        bindColor["Maroon"] = sol::var(&obe::graphics::Color::Maroon);
        bindColor["MediumAquamarine"] = sol::var(&obe::graphics::Color::MediumAquamarine);
        bindColor["MediumBlue"] = sol::var(&obe::graphics::Color::MediumBlue);
        bindColor["MediumOrchid"] = sol::var(&obe::graphics::Color::MediumOrchid);
        bindColor["MediumPurple"] = sol::var(&obe::graphics::Color::MediumPurple);
        bindColor["MediumSeaGreen"] = sol::var(&obe::graphics::Color::MediumSeaGreen);
        bindColor["MediumSlateBlue"] = sol::var(&obe::graphics::Color::MediumSlateBlue);
        bindColor["MediumSpringGreen"] = sol::var(&obe::graphics::Color::MediumSpringGreen);
        bindColor["MediumTurquoise"] = sol::var(&obe::graphics::Color::MediumTurquoise);
        bindColor["MediumVioletRed"] = sol::var(&obe::graphics::Color::MediumVioletRed);
        bindColor["MidnightBlue"] = sol::var(&obe::graphics::Color::MidnightBlue);
        bindColor["MintCream"] = sol::var(&obe::graphics::Color::MintCream);
        bindColor["MistyRose"] = sol::var(&obe::graphics::Color::MistyRose);
        bindColor["Moccasin"] = sol::var(&obe::graphics::Color::Moccasin);
        bindColor["NavajoWhite"] = sol::var(&obe::graphics::Color::NavajoWhite);
        bindColor["Navy"] = sol::var(&obe::graphics::Color::Navy);
        bindColor["OldLace"] = sol::var(&obe::graphics::Color::OldLace);
        bindColor["Olive"] = sol::var(&obe::graphics::Color::Olive);
        bindColor["OliveDrab"] = sol::var(&obe::graphics::Color::OliveDrab);
        bindColor["Orange"] = sol::var(&obe::graphics::Color::Orange);
        bindColor["OrangeRed"] = sol::var(&obe::graphics::Color::OrangeRed);
        bindColor["Orchid"] = sol::var(&obe::graphics::Color::Orchid);
        bindColor["PaleGoldenrod"] = sol::var(&obe::graphics::Color::PaleGoldenrod);
        bindColor["PaleGreen"] = sol::var(&obe::graphics::Color::PaleGreen);
        bindColor["PaleTurquoise"] = sol::var(&obe::graphics::Color::PaleTurquoise);
        bindColor["PaleVioletRed"] = sol::var(&obe::graphics::Color::PaleVioletRed);
        bindColor["PapayaWhip"] = sol::var(&obe::graphics::Color::PapayaWhip);
        bindColor["PeachPuff"] = sol::var(&obe::graphics::Color::PeachPuff);
        bindColor["Peru"] = sol::var(&obe::graphics::Color::Peru);
        bindColor["Pink"] = sol::var(&obe::graphics::Color::Pink);
        bindColor["Plum"] = sol::var(&obe::graphics::Color::Plum);
        bindColor["PowderBlue"] = sol::var(&obe::graphics::Color::PowderBlue);
        bindColor["Purple"] = sol::var(&obe::graphics::Color::Purple);
        bindColor["RebeccaPurple"] = sol::var(&obe::graphics::Color::RebeccaPurple);
        bindColor["Red"] = sol::var(&obe::graphics::Color::Red);
        bindColor["RosyBrown"] = sol::var(&obe::graphics::Color::RosyBrown);
        bindColor["RoyalBlue"] = sol::var(&obe::graphics::Color::RoyalBlue);
        bindColor["SaddleBrown"] = sol::var(&obe::graphics::Color::SaddleBrown);
        bindColor["Salmon"] = sol::var(&obe::graphics::Color::Salmon);
        bindColor["SandyBrown"] = sol::var(&obe::graphics::Color::SandyBrown);
        bindColor["SeaGreen"] = sol::var(&obe::graphics::Color::SeaGreen);
        bindColor["SeaShell"] = sol::var(&obe::graphics::Color::SeaShell);
        bindColor["Sienna"] = sol::var(&obe::graphics::Color::Sienna);
        bindColor["Silver"] = sol::var(&obe::graphics::Color::Silver);
        bindColor["SkyBlue"] = sol::var(&obe::graphics::Color::SkyBlue);
        bindColor["SlateBlue"] = sol::var(&obe::graphics::Color::SlateBlue);
        bindColor["SlateGray"] = sol::var(&obe::graphics::Color::SlateGray);
        bindColor["Snow"] = sol::var(&obe::graphics::Color::Snow);
        bindColor["SpringGreen"] = sol::var(&obe::graphics::Color::SpringGreen);
        bindColor["SteelBlue"] = sol::var(&obe::graphics::Color::SteelBlue);
        bindColor["Tan"] = sol::var(&obe::graphics::Color::Tan);
        bindColor["Teal"] = sol::var(&obe::graphics::Color::Teal);
        bindColor["Thistle"] = sol::var(&obe::graphics::Color::Thistle);
        bindColor["Tomato"] = sol::var(&obe::graphics::Color::Tomato);
        bindColor["Turquoise"] = sol::var(&obe::graphics::Color::Turquoise);
        bindColor["Violet"] = sol::var(&obe::graphics::Color::Violet);
        bindColor["Wheat"] = sol::var(&obe::graphics::Color::Wheat);
        bindColor["White"] = sol::var(&obe::graphics::Color::White);
        bindColor["WhiteSmoke"] = sol::var(&obe::graphics::Color::WhiteSmoke);
        bindColor["Yellow"] = sol::var(&obe::graphics::Color::Yellow);
        bindColor["YellowGreen"] = sol::var(&obe::graphics::Color::YellowGreen);
    }
    void LoadClassFont(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Font> bindFont
            = GraphicsNamespace.new_usertype<obe::graphics::Font>("Font", sol::call_constructor,
                sol::constructors<obe::graphics::Font(),
                    obe::graphics::Font(const obe::graphics::Font&),
                    obe::graphics::Font(const sf::Font&)>());
        bindFont["load_from_file"] = &obe::graphics::Font::load_from_file;
        bindFont[sol::meta_function::equal_to] = &obe::graphics::Font::operator==;
    }
    void LoadClassPositionTransformer(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::PositionTransformer> bindPositionTransformer
            = GraphicsNamespace.new_usertype<obe::graphics::PositionTransformer>(
                "PositionTransformer", sol::call_constructor,
                sol::constructors<obe::graphics::PositionTransformer(),
                    obe::graphics::PositionTransformer(const std::string&, const std::string&)>());
        bindPositionTransformer["get_x_transformer"]
            = &obe::graphics::PositionTransformer::get_x_transformer;
        bindPositionTransformer["get_x_transformer_name"]
            = &obe::graphics::PositionTransformer::get_x_transformer_name;
        bindPositionTransformer["get_y_transformer"]
            = &obe::graphics::PositionTransformer::get_y_transformer;
        bindPositionTransformer["get_y_transformer_name"]
            = &obe::graphics::PositionTransformer::get_y_transformer_name;
        bindPositionTransformer[sol::meta_function::call]
            = &obe::graphics::PositionTransformer::operator();
    }
    void LoadClassRenderTarget(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::RenderTarget> bindRenderTarget
            = GraphicsNamespace.new_usertype<obe::graphics::RenderTarget>("RenderTarget",
                sol::call_constructor,
                sol::constructors<obe::graphics::RenderTarget(sf::RenderTarget&),
                    obe::graphics::RenderTarget(sf::RenderWindow&)>());
        bindRenderTarget["draw"] = sol::overload(
            [](obe::graphics::RenderTarget* self, const sf::Drawable& drawable) -> void {
                return self->draw(drawable);
            },
            [](obe::graphics::RenderTarget* self, const sf::Drawable& drawable,
                const sf::RenderStates& states) -> void { return self->draw(drawable, states); },
            [](obe::graphics::RenderTarget* self, const sf::Vertex* vertices,
                std::size_t vertexCount,
                sf::PrimitiveType type) -> void { return self->draw(vertices, vertexCount, type); },
            [](obe::graphics::RenderTarget* self, const sf::Vertex* vertices,
                std::size_t vertexCount, sf::PrimitiveType type,
                const sf::RenderStates& states) -> void {
                return self->draw(vertices, vertexCount, type, states);
            });
        bindRenderTarget["get_size"] = &obe::graphics::RenderTarget::get_size;
    }
    void LoadClassRenderable(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Renderable> bindRenderable
            = GraphicsNamespace.new_usertype<obe::graphics::Renderable>("Renderable");
        bindRenderable["get_layer"] = &obe::graphics::Renderable::get_layer;
        bindRenderable["get_sublayer"] = &obe::graphics::Renderable::get_sublayer;
        bindRenderable["is_visible"] = &obe::graphics::Renderable::is_visible;
        bindRenderable["set_layer"] = &obe::graphics::Renderable::set_layer;
        bindRenderable["set_sublayer"] = &obe::graphics::Renderable::set_sublayer;
        bindRenderable["set_visible"] = &obe::graphics::Renderable::set_visible;
        bindRenderable["show"] = &obe::graphics::Renderable::show;
        bindRenderable["hide"] = &obe::graphics::Renderable::hide;
        bindRenderable["draw"] = &obe::graphics::Renderable::draw;
    }
    void LoadClassRichText(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::RichText> bindRichText
            = GraphicsNamespace.new_usertype<obe::graphics::RichText>("RichText",
                sol::call_constructor,
                sol::constructors<obe::graphics::RichText(),
                    obe::graphics::RichText(const obe::graphics::Font&)>());
        bindRichText["clear"] = &obe::graphics::RichText::clear;
        bindRichText["append"] = &obe::graphics::RichText::append;
        bindRichText["get_font"] = &obe::graphics::RichText::get_font;
        bindRichText["set_font"] = &obe::graphics::RichText::set_font;
        bindRichText["get_lines"] = &obe::graphics::RichText::get_lines;
        bindRichText["get_character_size"] = &obe::graphics::RichText::get_character_size;
        bindRichText["set_character_size"] = &obe::graphics::RichText::set_character_size;
        bindRichText["getLocalBounds"] = &obe::graphics::RichText::getLocalBounds;
        bindRichText["getGlobalBounds"] = &obe::graphics::RichText::getGlobalBounds;
    }
    void LoadClassShader(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Shader> bindShader
            = GraphicsNamespace.new_usertype<obe::graphics::Shader>("Shader", sol::call_constructor,
                sol::constructors<obe::graphics::Shader(),
                    obe::graphics::Shader(const std::string&)>(),
                sol::base_classes, sol::bases<obe::Types::Serializable>());
        bindShader["dump"] = &obe::graphics::Shader::dump;
        bindShader["load"] = &obe::graphics::Shader::load;
        bindShader["load_from_file"] = &obe::graphics::Shader::load_from_file;
    }
    void LoadClassSprite(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Sprite> bindSprite
            = GraphicsNamespace.new_usertype<obe::graphics::Sprite>("Sprite", sol::base_classes,
                sol::bases<obe::Transform::UnitBasedObject, obe::Types::Selectable,
                    obe::Transform::Rect, obe::Transform::Movable, obe::graphics::Renderable,
                    obe::Component::Component<obe::graphics::Sprite>, obe::Component::ComponentBase,
                    obe::Types::Identifiable, obe::Types::Serializable,
                    obe::engine::ResourceManagedObject>());
        bindSprite["draw_handle"] = &obe::graphics::Sprite::draw_handle;
        bindSprite["dump"] = &obe::graphics::Sprite::dump;
        bindSprite["get_color"] = &obe::graphics::Sprite::get_color;
        bindSprite["get_parent_id"] = &obe::graphics::Sprite::get_parent_id;
        bindSprite["get_filesystem_path"] = &obe::graphics::Sprite::get_filesystem_path;
        bindSprite["get_position_transformer"] = &obe::graphics::Sprite::get_position_transformer;
        bindSprite["get_rect"] = &obe::graphics::Sprite::get_rect;
        bindSprite["get_shader"] = &obe::graphics::Sprite::get_shader;
        bindSprite["get_internal_sprite"] = &obe::graphics::Sprite::get_internal_sprite;
        bindSprite["get_height"] = &obe::graphics::Sprite::get_height;
        bindSprite["get_width"] = &obe::graphics::Sprite::get_width;
        bindSprite["get_texture"] = sol::overload(
            static_cast<const obe::graphics::Texture& (obe::graphics::Sprite::*)() const>(
                &obe::graphics::Sprite::get_texture),
            static_cast<obe::graphics::Texture& (obe::graphics::Sprite::*)()>(
                &obe::graphics::Sprite::get_texture));
        bindSprite["get_x_scale_factor"] = &obe::graphics::Sprite::get_x_scale_factor;
        bindSprite["get_y_scale_factor"] = &obe::graphics::Sprite::get_y_scale_factor;
        bindSprite["is_anti_aliased"] = &obe::graphics::Sprite::is_anti_aliased;
        bindSprite["has_shader"] = &obe::graphics::Sprite::has_shader;
        bindSprite["load"] = &obe::graphics::Sprite::load;
        bindSprite["load_texture"] = &obe::graphics::Sprite::load_texture;
        bindSprite["rotate"] = &obe::graphics::Sprite::rotate;
        bindSprite["set_color"] = &obe::graphics::Sprite::set_color;
        bindSprite["set_parent_id"] = &obe::graphics::Sprite::set_parent_id;
        bindSprite["set_position_transformer"] = &obe::graphics::Sprite::set_position_transformer;
        bindSprite["set_rotation"] = &obe::graphics::Sprite::set_rotation;
        bindSprite["set_rotation_origin"] = &obe::graphics::Sprite::set_rotation_origin;
        bindSprite["set_scaling_origin"] = &obe::graphics::Sprite::set_scaling_origin;
        bindSprite["set_shader"] = &obe::graphics::Sprite::set_shader;
        bindSprite["set_texture"] = &obe::graphics::Sprite::set_texture;
        bindSprite["set_texture_rect"] = &obe::graphics::Sprite::set_texture_rect;
        bindSprite["set_translation_origin"] = &obe::graphics::Sprite::set_translation_origin;
        bindSprite["set_anti_aliasing"] = &obe::graphics::Sprite::set_anti_aliasing;
        bindSprite["use_texture_size"] = &obe::graphics::Sprite::use_texture_size;
        bindSprite["draw"] = &obe::graphics::Sprite::draw;
        bindSprite["attach_resource_manager"] = &obe::graphics::Sprite::attach_resource_manager;
        bindSprite["type"] = &obe::graphics::Sprite::type;

        Sprite::Register();
    }
    void LoadClassSpriteHandlePoint(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::SpriteHandlePoint> bindSpriteHandlePoint
            = GraphicsNamespace.new_usertype<obe::graphics::SpriteHandlePoint>("SpriteHandlePoint");
        bindSpriteHandlePoint["get_rect"] = &obe::graphics::SpriteHandlePoint::get_rect;
        bindSpriteHandlePoint["get_referential"] = &obe::graphics::SpriteHandlePoint::get_referential;
        bindSpriteHandlePoint["get_type"] = &obe::graphics::SpriteHandlePoint::get_type;
        bindSpriteHandlePoint["set_position"] = &obe::graphics::SpriteHandlePoint::set_position;
        bindSpriteHandlePoint["m_dp"] = &obe::graphics::SpriteHandlePoint::m_dp;
        bindSpriteHandlePoint["radius"] = sol::var(&obe::graphics::SpriteHandlePoint::radius);
    }
    void LoadClassSvgTexture(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::SvgTexture> bindSvgTexture
            = GraphicsNamespace.new_usertype<obe::graphics::SvgTexture>("SvgTexture",
                sol::call_constructor,
                sol::constructors<obe::graphics::SvgTexture(const std::string&),
                    obe::graphics::SvgTexture(const obe::graphics::SvgTexture&)>());
        bindSvgTexture["is_autoscaled"] = &obe::graphics::SvgTexture::is_autoscaled;
        bindSvgTexture["set_autoscaling"] = &obe::graphics::SvgTexture::set_autoscaling;
        bindSvgTexture["set_size_hint"] = &obe::graphics::SvgTexture::set_size_hint;
        bindSvgTexture["success"] = &obe::graphics::SvgTexture::success;
        bindSvgTexture["get_texture"]
            = sol::overload(static_cast<const sf::Texture& (obe::graphics::SvgTexture::*)() const>(
                                &obe::graphics::SvgTexture::get_texture),
                static_cast<sf::Texture& (obe::graphics::SvgTexture::*)()>(
                    &obe::graphics::SvgTexture::get_texture));
    }
    void LoadClassText(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Text> bindText
            = GraphicsNamespace.new_usertype<obe::graphics::Text>("Text", sol::call_constructor,
                sol::constructors<obe::graphics::Text(),
                    obe::graphics::Text(const std::string&)>());
        bindText["color"] = &obe::graphics::Text::color;
        bindText["outline"] = &obe::graphics::Text::outline;
        bindText["thickness"] = &obe::graphics::Text::thickness;
        bindText["style"] = &obe::graphics::Text::style;
        bindText["string"] = &obe::graphics::Text::string;
    }
    void LoadClassTexture(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Texture> bindTexture
            = GraphicsNamespace.new_usertype<obe::graphics::Texture>("Texture",
                sol::call_constructor,
                sol::constructors<obe::graphics::Texture(),
                    obe::graphics::Texture(std::shared_ptr<sf::Texture>),
                    obe::graphics::Texture(const sf::Texture&),
                    obe::graphics::Texture(const obe::graphics::Texture&)>());
        bindTexture["create"] = &obe::graphics::Texture::create;
        bindTexture["load_from_file"]
            = sol::overload(static_cast<bool (obe::graphics::Texture::*)(const std::string&)>(
                                &obe::graphics::Texture::load_from_file),
                static_cast<bool (obe::graphics::Texture::*)(const std::string&,
                    const obe::Transform::Rect&)>(&obe::graphics::Texture::load_from_file));
        bindTexture["load_from_image"] = &obe::graphics::Texture::load_from_image;
        bindTexture["get_size"] = &obe::graphics::Texture::get_size;
        bindTexture["set_size_hint"] = &obe::graphics::Texture::set_size_hint;
        bindTexture["is_autoscaled"] = &obe::graphics::Texture::is_autoscaled;
        bindTexture["set_autoscaling"] = &obe::graphics::Texture::set_autoscaling;
        bindTexture["set_anti_aliasing"] = &obe::graphics::Texture::set_anti_aliasing;
        bindTexture["is_anti_aliased"] = &obe::graphics::Texture::is_anti_aliased;
        bindTexture["set_repeated"] = &obe::graphics::Texture::set_repeated;
        bindTexture["is_repeated"] = &obe::graphics::Texture::is_repeated;
        bindTexture["reset"] = &obe::graphics::Texture::reset;
        bindTexture["useCount"] = &obe::graphics::Texture::useCount;
        bindTexture["isVector"] = &obe::graphics::Texture::isVector;
        bindTexture["isBitmap"] = &obe::graphics::Texture::isBitmap;
        bindTexture["make_shared_texture"] = &obe::graphics::Texture::make_shared_texture;
    }
    void LoadClassHsv(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Hsv> bindHsv
            = GraphicsNamespace.new_usertype<obe::graphics::Hsv>(
                "Hsv", sol::call_constructor, sol::default_constructor);
        bindHsv["H"] = &obe::graphics::Hsv::H;
        bindHsv["S"] = &obe::graphics::Hsv::S;
        bindHsv["V"] = &obe::graphics::Hsv::V;
    }
    void LoadFunctionInitPositionTransformer(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        GraphicsNamespace.set_function(
            "init_position_transformers", &obe::graphics::init_position_transformers);
    }
    void LoadFunctionMakeNullTexture(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        GraphicsNamespace.set_function("make_null_texture", &obe::graphics::make_null_texture);
    }
    void LoadGlobalTransformers(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        GraphicsNamespace["Transformers"] = obe::graphics::Transformers;
    }
    void LoadGlobalParallax(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        GraphicsNamespace["Parallax"] = obe::graphics::Parallax;
    }
    void LoadGlobalCamera(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        GraphicsNamespace["Camera"] = obe::graphics::Camera;
    }
    void LoadGlobalPosition(sol::state_view state)
    {
        sol::table GraphicsNamespace = state["obe"]["graphics"].get<sol::table>();
        GraphicsNamespace["Position"] = obe::graphics::Position;
    }
};