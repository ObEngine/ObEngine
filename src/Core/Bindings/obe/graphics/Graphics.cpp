#include <Bindings/obe/graphics/Graphics.hpp>

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

namespace obe::graphics::bindings
{
    void load_enum_color_type(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        graphics_namespace.new_enum<obe::graphics::ColorType>("ColorType",
            { { "Rgba", obe::graphics::ColorType::Rgba }, { "Hsv", obe::graphics::ColorType::Hsv },
                { "Hex", obe::graphics::ColorType::Hex },
                { "ColorName", obe::graphics::ColorType::ColorName } });
    }
    void load_enum_sprite_handle_point_type(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        graphics_namespace.new_enum<obe::graphics::SpriteHandlePointType>("SpriteHandlePointType",
            { { "ScaleHandle", obe::graphics::SpriteHandlePointType::ScaleHandle },
                { "RotateHandle", obe::graphics::SpriteHandlePointType::RotateHandle } });
    }
    void load_class_color(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Color> bind_color = graphics_namespace.new_usertype<
            obe::graphics::Color>("Color", sol::call_constructor,
            sol::constructors<obe::graphics::Color(), obe::graphics::Color(double, double, double),
                obe::graphics::Color(double, double, double, double),
                obe::graphics::Color(const std::string&), obe::graphics::Color(const sf::Color&)>(),
            sol::base_classes, sol::bases<obe::types::Serializable>());
        bind_color["schema"] = &obe::graphics::Color::schema;
        bind_color["dump"] = sol::overload(
            static_cast<vili::node (obe::graphics::Color::*)(obe::graphics::ColorType) const>(
                &obe::graphics::Color::dump),
            static_cast<vili::node (obe::graphics::Color::*)() const>(&obe::graphics::Color::dump));
        bind_color["load"] = &obe::graphics::Color::load;
        bind_color["from_string"] = &obe::graphics::Color::from_string;
        bind_color["from_name"]
            = sol::overload([](obe::graphics::Color* self,
                                std::string name) -> bool { return self->from_name(name); },
                [](obe::graphics::Color* self, std::string name, bool strict) -> bool {
                    return self->from_name(name, strict);
                });
        bind_color["from_hex"] = &obe::graphics::Color::from_hex;
        bind_color["from_rgb"]
            = sol::overload([](obe::graphics::Color* self, double r, double g,
                                double b) -> void { return self->from_rgb(r, g, b); },
                [](obe::graphics::Color* self, double r, double g, double b, double a) -> void {
                    return self->from_rgb(r, g, b, a);
                });
        bind_color["from_hsv"] = &obe::graphics::Color::from_hsv;
        bind_color["to_integer"] = &obe::graphics::Color::to_integer;
        bind_color["to_hex"] = &obe::graphics::Color::to_hex;
        bind_color["to_name"] = &obe::graphics::Color::to_name;
        bind_color["to_hsv"] = &obe::graphics::Color::to_hsv;
        bind_color["to_string"] = &obe::graphics::Color::to_string;
        bind_color[sol::meta_function::equal_to] = &obe::graphics::Color::operator==;
        bind_color[sol::meta_function::addition] = &obe::graphics::Color::operator+;
        bind_color[sol::meta_function::subtraction]
            = static_cast<obe::graphics::Color (obe::graphics::Color::*)(
                const obe::graphics::Color&) const>(&obe::graphics::Color::operator-);
        bind_color[sol::meta_function::unary_minus]
            = static_cast<obe::graphics::Color (obe::graphics::Color::*)() const>(
                &obe::graphics::Color::operator-);
        bind_color[sol::meta_function::multiplication] = sol::overload(
            static_cast<obe::graphics::Color (obe::graphics::Color::*)(const obe::graphics::Color&)
                    const>(&obe::graphics::Color::operator*),
            static_cast<obe::graphics::Color (obe::graphics::Color::*)(double) const>(
                &obe::graphics::Color::operator*));
        bind_color[sol::meta_function::division] = sol::overload(
            static_cast<obe::graphics::Color (obe::graphics::Color::*)(const obe::graphics::Color&)
                    const>(&obe::graphics::Color::operator/),
            static_cast<obe::graphics::Color (obe::graphics::Color::*)(double) const>(
                &obe::graphics::Color::operator/));
        bind_color["Random"]
            = sol::overload([]() -> obe::graphics::Color { return obe::graphics::Color::Random(); },
                [](bool random_alpha) -> obe::graphics::Color {
                    return obe::graphics::Color::Random(random_alpha);
                });
        bind_color["r"] = &obe::graphics::Color::r;
        bind_color["g"] = &obe::graphics::Color::g;
        bind_color["b"] = &obe::graphics::Color::b;
        bind_color["a"] = &obe::graphics::Color::a;
        bind_color["AliceBlue"] = sol::var(&obe::graphics::Color::AliceBlue);
        bind_color["AntiqueWhite"] = sol::var(&obe::graphics::Color::AntiqueWhite);
        bind_color["Aqua"] = sol::var(&obe::graphics::Color::Aqua);
        bind_color["Aquamarine"] = sol::var(&obe::graphics::Color::Aquamarine);
        bind_color["Azure"] = sol::var(&obe::graphics::Color::Azure);
        bind_color["Beige"] = sol::var(&obe::graphics::Color::Beige);
        bind_color["Bisque"] = sol::var(&obe::graphics::Color::Bisque);
        bind_color["Black"] = sol::var(&obe::graphics::Color::Black);
        bind_color["BlanchedAlmond"] = sol::var(&obe::graphics::Color::BlanchedAlmond);
        bind_color["Blue"] = sol::var(&obe::graphics::Color::Blue);
        bind_color["BlueViolet"] = sol::var(&obe::graphics::Color::BlueViolet);
        bind_color["Brown"] = sol::var(&obe::graphics::Color::Brown);
        bind_color["BurlyWood"] = sol::var(&obe::graphics::Color::BurlyWood);
        bind_color["CadetBlue"] = sol::var(&obe::graphics::Color::CadetBlue);
        bind_color["Chartreuse"] = sol::var(&obe::graphics::Color::Chartreuse);
        bind_color["Chocolate"] = sol::var(&obe::graphics::Color::Chocolate);
        bind_color["Coral"] = sol::var(&obe::graphics::Color::Coral);
        bind_color["CornflowerBlue"] = sol::var(&obe::graphics::Color::CornflowerBlue);
        bind_color["Cornsilk"] = sol::var(&obe::graphics::Color::Cornsilk);
        bind_color["Crimson"] = sol::var(&obe::graphics::Color::Crimson);
        bind_color["Cyan"] = sol::var(&obe::graphics::Color::Cyan);
        bind_color["DarkBlue"] = sol::var(&obe::graphics::Color::DarkBlue);
        bind_color["DarkCyan"] = sol::var(&obe::graphics::Color::DarkCyan);
        bind_color["DarkGoldenrod"] = sol::var(&obe::graphics::Color::DarkGoldenrod);
        bind_color["DarkGray"] = sol::var(&obe::graphics::Color::DarkGray);
        bind_color["DarkGreen"] = sol::var(&obe::graphics::Color::DarkGreen);
        bind_color["DarkKhaki"] = sol::var(&obe::graphics::Color::DarkKhaki);
        bind_color["DarkMagenta"] = sol::var(&obe::graphics::Color::DarkMagenta);
        bind_color["DarkOliveGreen"] = sol::var(&obe::graphics::Color::DarkOliveGreen);
        bind_color["DarkOrange"] = sol::var(&obe::graphics::Color::DarkOrange);
        bind_color["DarkOrchid"] = sol::var(&obe::graphics::Color::DarkOrchid);
        bind_color["DarkRed"] = sol::var(&obe::graphics::Color::DarkRed);
        bind_color["DarkSalmon"] = sol::var(&obe::graphics::Color::DarkSalmon);
        bind_color["DarkSeaGreen"] = sol::var(&obe::graphics::Color::DarkSeaGreen);
        bind_color["DarkSlateBlue"] = sol::var(&obe::graphics::Color::DarkSlateBlue);
        bind_color["DarkSlateGray"] = sol::var(&obe::graphics::Color::DarkSlateGray);
        bind_color["DarkTurquoise"] = sol::var(&obe::graphics::Color::DarkTurquoise);
        bind_color["DarkViolet"] = sol::var(&obe::graphics::Color::DarkViolet);
        bind_color["DeepPink"] = sol::var(&obe::graphics::Color::DeepPink);
        bind_color["DeepSkyBlue"] = sol::var(&obe::graphics::Color::DeepSkyBlue);
        bind_color["DimGray"] = sol::var(&obe::graphics::Color::DimGray);
        bind_color["DodgerBlue"] = sol::var(&obe::graphics::Color::DodgerBlue);
        bind_color["FireBrick"] = sol::var(&obe::graphics::Color::FireBrick);
        bind_color["FloralWhite"] = sol::var(&obe::graphics::Color::FloralWhite);
        bind_color["ForestGreen"] = sol::var(&obe::graphics::Color::ForestGreen);
        bind_color["Fuchsia"] = sol::var(&obe::graphics::Color::Fuchsia);
        bind_color["Gainsboro"] = sol::var(&obe::graphics::Color::Gainsboro);
        bind_color["GhostWhite"] = sol::var(&obe::graphics::Color::GhostWhite);
        bind_color["Gold"] = sol::var(&obe::graphics::Color::Gold);
        bind_color["Goldenrod"] = sol::var(&obe::graphics::Color::Goldenrod);
        bind_color["Gray"] = sol::var(&obe::graphics::Color::Gray);
        bind_color["Green"] = sol::var(&obe::graphics::Color::Green);
        bind_color["GreenYellow"] = sol::var(&obe::graphics::Color::GreenYellow);
        bind_color["HoneyDew"] = sol::var(&obe::graphics::Color::HoneyDew);
        bind_color["HotPink"] = sol::var(&obe::graphics::Color::HotPink);
        bind_color["IndianRed"] = sol::var(&obe::graphics::Color::IndianRed);
        bind_color["Indigo"] = sol::var(&obe::graphics::Color::Indigo);
        bind_color["Ivory"] = sol::var(&obe::graphics::Color::Ivory);
        bind_color["Khaki"] = sol::var(&obe::graphics::Color::Khaki);
        bind_color["Lavender"] = sol::var(&obe::graphics::Color::Lavender);
        bind_color["LavenderBlush"] = sol::var(&obe::graphics::Color::LavenderBlush);
        bind_color["LawnGreen"] = sol::var(&obe::graphics::Color::LawnGreen);
        bind_color["LemonChiffon"] = sol::var(&obe::graphics::Color::LemonChiffon);
        bind_color["LightBlue"] = sol::var(&obe::graphics::Color::LightBlue);
        bind_color["LightCoral"] = sol::var(&obe::graphics::Color::LightCoral);
        bind_color["LightCyan"] = sol::var(&obe::graphics::Color::LightCyan);
        bind_color["LightGoldenrodYellow"] = sol::var(&obe::graphics::Color::LightGoldenrodYellow);
        bind_color["LightGray"] = sol::var(&obe::graphics::Color::LightGray);
        bind_color["LightGreen"] = sol::var(&obe::graphics::Color::LightGreen);
        bind_color["LightPink"] = sol::var(&obe::graphics::Color::LightPink);
        bind_color["LightSalmon"] = sol::var(&obe::graphics::Color::LightSalmon);
        bind_color["LightSeaGreen"] = sol::var(&obe::graphics::Color::LightSeaGreen);
        bind_color["LightSkyBlue"] = sol::var(&obe::graphics::Color::LightSkyBlue);
        bind_color["LightSlateGray"] = sol::var(&obe::graphics::Color::LightSlateGray);
        bind_color["LightSteelBlue"] = sol::var(&obe::graphics::Color::LightSteelBlue);
        bind_color["LightYellow"] = sol::var(&obe::graphics::Color::LightYellow);
        bind_color["Lime"] = sol::var(&obe::graphics::Color::Lime);
        bind_color["LimeGreen"] = sol::var(&obe::graphics::Color::LimeGreen);
        bind_color["Linen"] = sol::var(&obe::graphics::Color::Linen);
        bind_color["Magenta"] = sol::var(&obe::graphics::Color::Magenta);
        bind_color["Maroon"] = sol::var(&obe::graphics::Color::Maroon);
        bind_color["MediumAquamarine"] = sol::var(&obe::graphics::Color::MediumAquamarine);
        bind_color["MediumBlue"] = sol::var(&obe::graphics::Color::MediumBlue);
        bind_color["MediumOrchid"] = sol::var(&obe::graphics::Color::MediumOrchid);
        bind_color["MediumPurple"] = sol::var(&obe::graphics::Color::MediumPurple);
        bind_color["MediumSeaGreen"] = sol::var(&obe::graphics::Color::MediumSeaGreen);
        bind_color["MediumSlateBlue"] = sol::var(&obe::graphics::Color::MediumSlateBlue);
        bind_color["MediumSpringGreen"] = sol::var(&obe::graphics::Color::MediumSpringGreen);
        bind_color["MediumTurquoise"] = sol::var(&obe::graphics::Color::MediumTurquoise);
        bind_color["MediumVioletRed"] = sol::var(&obe::graphics::Color::MediumVioletRed);
        bind_color["MidnightBlue"] = sol::var(&obe::graphics::Color::MidnightBlue);
        bind_color["MintCream"] = sol::var(&obe::graphics::Color::MintCream);
        bind_color["MistyRose"] = sol::var(&obe::graphics::Color::MistyRose);
        bind_color["Moccasin"] = sol::var(&obe::graphics::Color::Moccasin);
        bind_color["NavajoWhite"] = sol::var(&obe::graphics::Color::NavajoWhite);
        bind_color["Navy"] = sol::var(&obe::graphics::Color::Navy);
        bind_color["OldLace"] = sol::var(&obe::graphics::Color::OldLace);
        bind_color["Olive"] = sol::var(&obe::graphics::Color::Olive);
        bind_color["OliveDrab"] = sol::var(&obe::graphics::Color::OliveDrab);
        bind_color["Orange"] = sol::var(&obe::graphics::Color::Orange);
        bind_color["OrangeRed"] = sol::var(&obe::graphics::Color::OrangeRed);
        bind_color["Orchid"] = sol::var(&obe::graphics::Color::Orchid);
        bind_color["PaleGoldenrod"] = sol::var(&obe::graphics::Color::PaleGoldenrod);
        bind_color["PaleGreen"] = sol::var(&obe::graphics::Color::PaleGreen);
        bind_color["PaleTurquoise"] = sol::var(&obe::graphics::Color::PaleTurquoise);
        bind_color["PaleVioletRed"] = sol::var(&obe::graphics::Color::PaleVioletRed);
        bind_color["PapayaWhip"] = sol::var(&obe::graphics::Color::PapayaWhip);
        bind_color["PeachPuff"] = sol::var(&obe::graphics::Color::PeachPuff);
        bind_color["Peru"] = sol::var(&obe::graphics::Color::Peru);
        bind_color["Pink"] = sol::var(&obe::graphics::Color::Pink);
        bind_color["Plum"] = sol::var(&obe::graphics::Color::Plum);
        bind_color["PowderBlue"] = sol::var(&obe::graphics::Color::PowderBlue);
        bind_color["Purple"] = sol::var(&obe::graphics::Color::Purple);
        bind_color["RebeccaPurple"] = sol::var(&obe::graphics::Color::RebeccaPurple);
        bind_color["Red"] = sol::var(&obe::graphics::Color::Red);
        bind_color["RosyBrown"] = sol::var(&obe::graphics::Color::RosyBrown);
        bind_color["RoyalBlue"] = sol::var(&obe::graphics::Color::RoyalBlue);
        bind_color["SaddleBrown"] = sol::var(&obe::graphics::Color::SaddleBrown);
        bind_color["Salmon"] = sol::var(&obe::graphics::Color::Salmon);
        bind_color["SandyBrown"] = sol::var(&obe::graphics::Color::SandyBrown);
        bind_color["SeaGreen"] = sol::var(&obe::graphics::Color::SeaGreen);
        bind_color["SeaShell"] = sol::var(&obe::graphics::Color::SeaShell);
        bind_color["Sienna"] = sol::var(&obe::graphics::Color::Sienna);
        bind_color["Silver"] = sol::var(&obe::graphics::Color::Silver);
        bind_color["SkyBlue"] = sol::var(&obe::graphics::Color::SkyBlue);
        bind_color["SlateBlue"] = sol::var(&obe::graphics::Color::SlateBlue);
        bind_color["SlateGray"] = sol::var(&obe::graphics::Color::SlateGray);
        bind_color["Snow"] = sol::var(&obe::graphics::Color::Snow);
        bind_color["SpringGreen"] = sol::var(&obe::graphics::Color::SpringGreen);
        bind_color["SteelBlue"] = sol::var(&obe::graphics::Color::SteelBlue);
        bind_color["Tan"] = sol::var(&obe::graphics::Color::Tan);
        bind_color["Teal"] = sol::var(&obe::graphics::Color::Teal);
        bind_color["Thistle"] = sol::var(&obe::graphics::Color::Thistle);
        bind_color["Tomato"] = sol::var(&obe::graphics::Color::Tomato);
        bind_color["Turquoise"] = sol::var(&obe::graphics::Color::Turquoise);
        bind_color["Violet"] = sol::var(&obe::graphics::Color::Violet);
        bind_color["Wheat"] = sol::var(&obe::graphics::Color::Wheat);
        bind_color["White"] = sol::var(&obe::graphics::Color::White);
        bind_color["WhiteSmoke"] = sol::var(&obe::graphics::Color::WhiteSmoke);
        bind_color["Yellow"] = sol::var(&obe::graphics::Color::Yellow);
        bind_color["YellowGreen"] = sol::var(&obe::graphics::Color::YellowGreen);
    }
    void load_class_editor_sprite(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::EditorSprite> bind_editor_sprite
            = graphics_namespace.new_usertype<obe::graphics::EditorSprite>("EditorSprite",
                sol::base_classes,
                sol::bases<obe::graphics::Sprite, obe::transform::UnitBasedObject,
                    obe::types::Selectable, obe::transform::Rect, obe::transform::Movable,
                    obe::graphics::Renderable, obe::component::Component<obe::graphics::Sprite>,
                    obe::component::ComponentBase, obe::types::Identifiable,
                    obe::types::Serializable, obe::types::UniqueIdentifiable,
                    obe::engine::ResourceManagedObject>());
        bind_editor_sprite["get_handle_point"] = &obe::graphics::EditorSprite::get_handle_point;
    }
    void load_class_font(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Font> bind_font
            = graphics_namespace.new_usertype<obe::graphics::Font>("Font", sol::call_constructor,
                sol::constructors<obe::graphics::Font(),
                    obe::graphics::Font(const obe::graphics::Font&),
                    obe::graphics::Font(const sf::Font&)>());
        bind_font["load_from_file"] = &obe::graphics::Font::load_from_file;
        bind_font[sol::meta_function::equal_to] = &obe::graphics::Font::operator==;
    }
    void load_class_position_transformer(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::PositionTransformer> bind_position_transformer
            = graphics_namespace.new_usertype<obe::graphics::PositionTransformer>(
                "PositionTransformer", sol::call_constructor,
                sol::constructors<obe::graphics::PositionTransformer(),
                    obe::graphics::PositionTransformer(const std::string&, const std::string&)>());
        bind_position_transformer["get_x_transformer"]
            = &obe::graphics::PositionTransformer::get_x_transformer;
        bind_position_transformer["get_x_transformer_name"]
            = &obe::graphics::PositionTransformer::get_x_transformer_name;
        bind_position_transformer["get_y_transformer"]
            = &obe::graphics::PositionTransformer::get_y_transformer;
        bind_position_transformer["get_y_transformer_name"]
            = &obe::graphics::PositionTransformer::get_y_transformer_name;
        bind_position_transformer[sol::meta_function::call]
            = &obe::graphics::PositionTransformer::operator();
    }
    void load_class_render_target(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::RenderTarget> bind_render_target
            = graphics_namespace.new_usertype<obe::graphics::RenderTarget>("RenderTarget",
                sol::call_constructor,
                sol::constructors<obe::graphics::RenderTarget(sf::RenderTarget&),
                    obe::graphics::RenderTarget(sf::RenderWindow&)>());
        bind_render_target["clear"] = &obe::graphics::RenderTarget::clear;
        bind_render_target["draw"] = sol::overload(
            [](obe::graphics::RenderTarget* self, const sf::Drawable& drawable) -> void {
                return self->draw(drawable);
            },
            [](obe::graphics::RenderTarget* self, const sf::Drawable& drawable,
                const sf::RenderStates& states) -> void { return self->draw(drawable, states); },
            [](obe::graphics::RenderTarget* self, const sf::Vertex* vertices,
                std::size_t vertex_count, sf::PrimitiveType type) -> void {
                return self->draw(vertices, vertex_count, type);
            },
            [](obe::graphics::RenderTarget* self, const sf::Vertex* vertices,
                std::size_t vertex_count, sf::PrimitiveType type,
                const sf::RenderStates& states) -> void {
                return self->draw(vertices, vertex_count, type, states);
            });
        bind_render_target["get_size"] = &obe::graphics::RenderTarget::get_size;
    }
    void load_class_renderable(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Renderable> bind_renderable
            = graphics_namespace.new_usertype<obe::graphics::Renderable>("Renderable");
        bind_renderable["get_layer"] = &obe::graphics::Renderable::get_layer;
        bind_renderable["get_sublayer"] = &obe::graphics::Renderable::get_sublayer;
        bind_renderable["is_visible"] = &obe::graphics::Renderable::is_visible;
        bind_renderable["set_layer"] = &obe::graphics::Renderable::set_layer;
        bind_renderable["set_sublayer"] = &obe::graphics::Renderable::set_sublayer;
        bind_renderable["set_visible"] = &obe::graphics::Renderable::set_visible;
        bind_renderable["show"] = &obe::graphics::Renderable::show;
        bind_renderable["hide"] = &obe::graphics::Renderable::hide;
        bind_renderable["draw"] = &obe::graphics::Renderable::draw;
    }
    void load_class_rich_text(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::RichText> bind_rich_text
            = graphics_namespace.new_usertype<obe::graphics::RichText>("RichText",
                sol::call_constructor,
                sol::constructors<obe::graphics::RichText(),
                    obe::graphics::RichText(const obe::graphics::Font&)>());
        bind_rich_text["clear"] = &obe::graphics::RichText::clear;
        bind_rich_text["append"] = &obe::graphics::RichText::append;
        bind_rich_text["get_font"] = &obe::graphics::RichText::get_font;
        bind_rich_text["set_font"] = &obe::graphics::RichText::set_font;
        bind_rich_text["get_lines"] = &obe::graphics::RichText::get_lines;
        bind_rich_text["get_character_size"] = &obe::graphics::RichText::get_character_size;
        bind_rich_text["set_character_size"] = &obe::graphics::RichText::set_character_size;
        bind_rich_text["getLocalBounds"] = &obe::graphics::RichText::getLocalBounds;
        bind_rich_text["getGlobalBounds"] = &obe::graphics::RichText::getGlobalBounds;
    }
    void load_class_shader(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Shader> bind_shader
            = graphics_namespace.new_usertype<obe::graphics::Shader>("Shader",
                sol::call_constructor,
                sol::constructors<obe::graphics::Shader(),
                    obe::graphics::Shader(const std::string&)>(),
                sol::base_classes, sol::bases<obe::types::Serializable>());
        bind_shader["schema"] = &obe::graphics::Shader::schema;
        bind_shader["dump"] = &obe::graphics::Shader::dump;
        bind_shader["load"] = &obe::graphics::Shader::load;
        bind_shader["load_from_file"] = &obe::graphics::Shader::load_from_file;
    }
    void load_class_sprite(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Sprite> bind_sprite
            = graphics_namespace.new_usertype<obe::graphics::Sprite>("Sprite", sol::base_classes,
                sol::bases<obe::transform::UnitBasedObject, obe::types::Selectable,
                    obe::transform::Rect, obe::transform::Movable, obe::graphics::Renderable,
                    obe::component::Component<obe::graphics::Sprite>, obe::component::ComponentBase,
                    obe::types::Identifiable, obe::types::Serializable,
                    obe::types::UniqueIdentifiable, obe::engine::ResourceManagedObject>());
        bind_sprite["draw_handle"] = &obe::graphics::Sprite::draw_handle;
        bind_sprite["get_color"] = &obe::graphics::Sprite::get_color;
        bind_sprite["get_parent_id"] = &obe::graphics::Sprite::get_parent_id;
        bind_sprite["get_filesystem_path"] = &obe::graphics::Sprite::get_filesystem_path;
        bind_sprite["get_position_transformer"] = &obe::graphics::Sprite::get_position_transformer;
        bind_sprite["get_rect"] = &obe::graphics::Sprite::get_rect;
        bind_sprite["get_shader"] = &obe::graphics::Sprite::get_shader;
        bind_sprite["get_internal_sprite"] = &obe::graphics::Sprite::get_internal_sprite;
        bind_sprite["get_height"] = &obe::graphics::Sprite::get_height;
        bind_sprite["get_width"] = &obe::graphics::Sprite::get_width;
        bind_sprite["get_texture"] = sol::overload(
            static_cast<const obe::graphics::Texture& (obe::graphics::Sprite::*)() const>(
                &obe::graphics::Sprite::get_texture),
            static_cast<obe::graphics::Texture& (obe::graphics::Sprite::*)()>(
                &obe::graphics::Sprite::get_texture));
        bind_sprite["get_x_scale_factor"] = &obe::graphics::Sprite::get_x_scale_factor;
        bind_sprite["get_y_scale_factor"] = &obe::graphics::Sprite::get_y_scale_factor;
        bind_sprite["is_anti_aliased"] = &obe::graphics::Sprite::is_anti_aliased;
        bind_sprite["has_shader"] = &obe::graphics::Sprite::has_shader;
        bind_sprite["schema"] = &obe::graphics::Sprite::schema;
        bind_sprite["dump"] = &obe::graphics::Sprite::dump;
        bind_sprite["load"] = &obe::graphics::Sprite::load;
        bind_sprite["load_texture"] = &obe::graphics::Sprite::load_texture;
        bind_sprite["rotate"] = &obe::graphics::Sprite::rotate;
        bind_sprite["set_color"] = &obe::graphics::Sprite::set_color;
        bind_sprite["set_parent_id"] = &obe::graphics::Sprite::set_parent_id;
        bind_sprite["set_position_transformer"] = &obe::graphics::Sprite::set_position_transformer;
        bind_sprite["set_rotation"] = &obe::graphics::Sprite::set_rotation;
        bind_sprite["set_rotation_origin"] = &obe::graphics::Sprite::set_rotation_origin;
        bind_sprite["set_scaling_origin"] = &obe::graphics::Sprite::set_scaling_origin;
        bind_sprite["set_shader"] = &obe::graphics::Sprite::set_shader;
        bind_sprite["set_texture"] = &obe::graphics::Sprite::set_texture;
        bind_sprite["set_texture_rect"] = &obe::graphics::Sprite::set_texture_rect;
        bind_sprite["set_translation_origin"] = &obe::graphics::Sprite::set_translation_origin;
        bind_sprite["set_anti_aliasing"] = &obe::graphics::Sprite::set_anti_aliasing;
        bind_sprite["use_texture_size"] = &obe::graphics::Sprite::use_texture_size;
        bind_sprite["draw"] = &obe::graphics::Sprite::draw;
        bind_sprite["attach_resource_manager"] = &obe::graphics::Sprite::attach_resource_manager;
        bind_sprite["type"] = &obe::graphics::Sprite::type;

        obe::graphics::Sprite::Register();
    }
    void load_class_sprite_handle_point(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::SpriteHandlePoint> bind_sprite_handle_point
            = graphics_namespace.new_usertype<obe::graphics::SpriteHandlePoint>(
                "SpriteHandlePoint");
        bind_sprite_handle_point["get_rect"] = &obe::graphics::SpriteHandlePoint::get_rect;
        bind_sprite_handle_point["get_referential"]
            = &obe::graphics::SpriteHandlePoint::get_referential;
        bind_sprite_handle_point["get_type"] = &obe::graphics::SpriteHandlePoint::get_type;
        bind_sprite_handle_point["set_position"] = &obe::graphics::SpriteHandlePoint::set_position;
        bind_sprite_handle_point["m_dp"] = &obe::graphics::SpriteHandlePoint::m_dp;
        bind_sprite_handle_point["radius"] = sol::var(&obe::graphics::SpriteHandlePoint::radius);
    }
    void load_class_svg_texture(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::SvgTexture> bind_svg_texture
            = graphics_namespace.new_usertype<obe::graphics::SvgTexture>("SvgTexture",
                sol::call_constructor,
                sol::constructors<obe::graphics::SvgTexture(const std::string&),
                    obe::graphics::SvgTexture(const obe::graphics::SvgTexture&)>());
        bind_svg_texture["is_autoscaled"] = &obe::graphics::SvgTexture::is_autoscaled;
        bind_svg_texture["set_autoscaling"] = &obe::graphics::SvgTexture::set_autoscaling;
        bind_svg_texture["set_size_hint"] = &obe::graphics::SvgTexture::set_size_hint;
        bind_svg_texture["success"] = &obe::graphics::SvgTexture::success;
        bind_svg_texture["get_texture"]
            = sol::overload(static_cast<const sf::Texture& (obe::graphics::SvgTexture::*)() const>(
                                &obe::graphics::SvgTexture::get_texture),
                static_cast<sf::Texture& (obe::graphics::SvgTexture::*)()>(
                    &obe::graphics::SvgTexture::get_texture));
    }
    void load_class_text(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Text> bind_text
            = graphics_namespace.new_usertype<obe::graphics::Text>("Text", sol::call_constructor,
                sol::constructors<obe::graphics::Text(),
                    obe::graphics::Text(const std::string&)>());
        bind_text["color"] = &obe::graphics::Text::color;
        bind_text["outline"] = &obe::graphics::Text::outline;
        bind_text["thickness"] = &obe::graphics::Text::thickness;
        bind_text["style"] = &obe::graphics::Text::style;
        bind_text["string"] = &obe::graphics::Text::string;
    }
    void load_class_texture(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Texture> bind_texture
            = graphics_namespace.new_usertype<obe::graphics::Texture>("Texture",
                sol::call_constructor,
                sol::constructors<obe::graphics::Texture(),
                    obe::graphics::Texture(std::shared_ptr<sf::Texture>),
                    obe::graphics::Texture(const sf::Texture&),
                    obe::graphics::Texture(const obe::graphics::Texture&)>());
        bind_texture["create"] = &obe::graphics::Texture::create;
        bind_texture["load_from_file"]
            = sol::overload(static_cast<bool (obe::graphics::Texture::*)(const std::string&)>(
                                &obe::graphics::Texture::load_from_file),
                static_cast<bool (obe::graphics::Texture::*)(const std::string&,
                    const obe::transform::AABB&)>(&obe::graphics::Texture::load_from_file));
        bind_texture["load_from_image"] = &obe::graphics::Texture::load_from_image;
        bind_texture["get_size"] = &obe::graphics::Texture::get_size;
        bind_texture["set_size_hint"] = &obe::graphics::Texture::set_size_hint;
        bind_texture["is_autoscaled"] = &obe::graphics::Texture::is_autoscaled;
        bind_texture["set_autoscaling"] = &obe::graphics::Texture::set_autoscaling;
        bind_texture["set_anti_aliasing"] = &obe::graphics::Texture::set_anti_aliasing;
        bind_texture["is_anti_aliased"] = &obe::graphics::Texture::is_anti_aliased;
        bind_texture["set_repeated"] = &obe::graphics::Texture::set_repeated;
        bind_texture["is_repeated"] = &obe::graphics::Texture::is_repeated;
        bind_texture["reset"] = &obe::graphics::Texture::reset;
        bind_texture["use_count"] = &obe::graphics::Texture::use_count;
        bind_texture["is_vector"] = &obe::graphics::Texture::is_vector;
        bind_texture["is_bitmap"] = &obe::graphics::Texture::is_bitmap;
        bind_texture["make_shared_texture"] = &obe::graphics::Texture::make_shared_texture;
    }
    void load_class_hsv(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        sol::usertype<obe::graphics::Hsv> bind_hsv
            = graphics_namespace.new_usertype<obe::graphics::Hsv>(
                "Hsv", sol::call_constructor, sol::default_constructor);
        bind_hsv["H"] = &obe::graphics::Hsv::H;
        bind_hsv["S"] = &obe::graphics::Hsv::S;
        bind_hsv["V"] = &obe::graphics::Hsv::V;
    }
    void load_function_init_position_transformers(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        graphics_namespace.set_function(
            "init_position_transformers", &obe::graphics::init_position_transformers);
    }
    void load_function_make_null_texture(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        graphics_namespace.set_function("make_null_texture", &obe::graphics::make_null_texture);
    }
    void load_global_transformers(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        graphics_namespace["Transformers"] = obe::graphics::Transformers;
    }
    void load_global_parallax(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        graphics_namespace["Parallax"] = obe::graphics::Parallax;
    }
    void load_global_camera(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        graphics_namespace["Camera"] = obe::graphics::Camera;
    }
    void load_global_position(sol::state_view state)
    {
        sol::table graphics_namespace = state["obe"]["graphics"].get<sol::table>();
        graphics_namespace["Position"] = obe::graphics::Position;
    }
};