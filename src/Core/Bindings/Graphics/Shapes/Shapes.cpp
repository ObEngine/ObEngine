#include <Bindings/Graphics/Shapes/Shapes.hpp>

#include <Graphics/Shapes.hpp>

#include <sol/sol.hpp>

namespace obe::Graphics::Shapes::Bindings
{
void LoadClassCircle(sol::state_view state)
{
sol::table ShapesNamespace = state["obe"]["Graphics"]["Shapes"].get<sol::table>();
sol::usertype<obe::Graphics::Shapes::Circle> bindCircle = ShapesNamespace.new_usertype<obe::Graphics::Shapes::Circle>(
"Circle", sol::call_constructor, sol::constructors<obe::Graphics::Shapes::Circle(), obe::Graphics::Shapes::Circle(const sf::CircleShape &), obe::Graphics::Shapes::Circle(const obe::Graphics::Shapes::Circle &)>());
bindCircle["operator sf::CircleShape &"] = 
&obe::Graphics::Shapes::Circle::operator sf::CircleShape &
;
bindCircle["operator const sf::CircleShape &"] = 
&obe::Graphics::Shapes::Circle::operator const sf::CircleShape &
;

}
void LoadClassPolygon(sol::state_view state)
{
sol::table ShapesNamespace = state["obe"]["Graphics"]["Shapes"].get<sol::table>();
sol::usertype<obe::Graphics::Shapes::Polygon> bindPolygon = ShapesNamespace.new_usertype<obe::Graphics::Shapes::Polygon>(
"Polygon", sol::call_constructor, sol::constructors<obe::Graphics::Shapes::Polygon(), obe::Graphics::Shapes::Polygon(const sf::ConvexShape &), obe::Graphics::Shapes::Polygon(const obe::Graphics::Shapes::Polygon &)>());
bindPolygon["operator sf::ConvexShape &"] = 
&obe::Graphics::Shapes::Polygon::operator sf::ConvexShape &
;
bindPolygon["operator const sf::ConvexShape &"] = 
&obe::Graphics::Shapes::Polygon::operator const sf::ConvexShape &
;

}
void LoadClassRectangle(sol::state_view state)
{
sol::table ShapesNamespace = state["obe"]["Graphics"]["Shapes"].get<sol::table>();
sol::usertype<obe::Graphics::Shapes::Rectangle> bindRectangle = ShapesNamespace.new_usertype<obe::Graphics::Shapes::Rectangle>(
"Rectangle", sol::call_constructor, sol::constructors<obe::Graphics::Shapes::Rectangle(), obe::Graphics::Shapes::Rectangle(const sf::RectangleShape &), obe::Graphics::Shapes::Rectangle(const obe::Graphics::Shapes::Rectangle &)>());
bindRectangle["operator sf::RectangleShape &"] = 
&obe::Graphics::Shapes::Rectangle::operator sf::RectangleShape &
;
bindRectangle["operator const sf::RectangleShape &"] = 
&obe::Graphics::Shapes::Rectangle::operator const sf::RectangleShape &
;

}
};