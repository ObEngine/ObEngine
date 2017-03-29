#include "Canvas.hpp"

Element::Element(const std::string& id)
{
    m_id = id;
    requires.push_back({"id", "\"\""});
}

Drawable::Drawable(const std::string& id) : Configurable(id), Element(id)
{
    requires.push_back({"layer", "1"});
}

void Drawable::update(kaguya::State& state)
{
    Configurable::update(state);
    m_layer = m_tableWrapper["layer"];
}

Colorable::Colorable(const std::string& id) : Drawable(id), Configurable(id), Element(id)
{
    requires.insert(requires.end(), {
        {"color", "{ r = 255, g = 255, b = 255, a = 255}"}
    });
}

void Colorable::update(kaguya::State& state)
{
    Drawable::update(state);
    m_color = sf::Color(m_tableWrapper["color"]["r"],
                        m_tableWrapper["color"]["g"],
                        m_tableWrapper["color"]["b"],
                        m_tableWrapper["color"]["a"]);
}

Transformable::Transformable(const std::string& id) : Element(id), Configurable(id)
{
    requires.insert(requires.end(), {
        {"x", "0"},
        {"y", "0"},
        {"width", "0"},
        {"height", "0"},
        {"rotation", "0"},
        {"origin", "{ translation = { x = 0, y = 0 }, rotation = { x = 0, y = 0 }}"}
    });
}

void Transformable::update(kaguya::State& state)
{
    Configurable::update(state);
    m_x = m_tableWrapper["x"];
    m_y = m_tableWrapper["y"];
    m_width = m_tableWrapper["width"];
    m_height = m_tableWrapper["height"];
    m_rotation = m_tableWrapper["rotation"];
    m_translationOriginX = m_tableWrapper["origin"]["translation"]["x"];
    m_translationOriginY = m_tableWrapper["origin"]["translation"]["y"];
    m_rotationOriginX = m_tableWrapper["origin"]["rotation"]["x"];
    m_rotationOriginY = m_tableWrapper["origin"]["rotation"]["y"];
}

Configurable::Configurable(const std::string& id) : Element(id)
{
}

kaguya::LuaTable& Configurable::init(const kaguya::LuaTable& tableWrapper)
{
    m_tableWrapper = tableWrapper;
    m_tableWrapper["id"] = m_id;
    return m_tableWrapper;
}

kaguya::LuaTable& Configurable::get()
{
    return m_tableWrapper;
}

void Configurable::update(kaguya::State& state)
{
    state["ApplyDefaultValue"](m_tableWrapper, requires);
}

CanvasElement::CanvasElement(const std::string& id) : Drawable(id), Configurable(id), Element(id)
{

}

void CanvasElement::update(kaguya::State& state)
{
    Drawable::update(state);
}

Line::Line(const std::string& id) : CanvasElement(id), Drawable(id), Colorable(id), Configurable(id), Element(id)
{
    requires.insert(requires.end(), {
        {"x1", "0"}, {"y1", "0"},
        {"x2", "0"}, {"y2", "0"}
    });
}

void Line::draw(sf::RenderTexture& target) const
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(m_x1, m_y1), m_color),
        sf::Vertex(sf::Vector2f(m_x2, m_y2), m_color)
    };
    target.draw(line, 2, sf::Lines);
}

void Line::update(kaguya::State& state)
{
    Colorable::update(state);
    m_x1 = m_tableWrapper["x1"];
    m_y1 = m_tableWrapper["y1"];
    m_x2 = m_tableWrapper["x2"];
    m_y2 = m_tableWrapper["y2"];
}

Rectangle::Rectangle(const std::string& id) : CanvasElement(id), Transformable(id), Drawable(id), Colorable(id), Configurable(id), Element(id)
{

}

void Rectangle::draw(sf::RenderTexture& target) const
{
    sf::RectangleShape rectangle(sf::Vector2f(m_width, m_height));
    rectangle.setPosition(m_x, m_y);
    rectangle.setFillColor(m_color);
    target.draw(rectangle);
}

void Rectangle::update(kaguya::State& state) 
{
    Transformable::update(state);
    CanvasElement::update(state);
    Colorable::update(state);
}

Canvas::Canvas(unsigned int width, unsigned int height)
{
    m_canvas.create(width, height);
    m_state.dofile("CanvasConfig.lua");

    m_state["Pair"].setClass(kaguya::UserdataMetatable<std::pair<std::string, std::string>>()
        .addFunction("first", &std::pair<std::string, std::string>::first)
        .addFunction("second", &std::pair<std::string, std::string>::second)
    );
    m_state["Element"].setClass(kaguya::UserdataMetatable<Element>());
    m_state["Configurable"].setClass(kaguya::UserdataMetatable<Configurable, Element>()
        .addFunction("init", &Configurable::init)
    );
    m_state["Drawable"].setClass(kaguya::UserdataMetatable<Drawable, Configurable>());
    m_state["Colorable"].setClass(kaguya::UserdataMetatable<Colorable, Drawable>());
    m_state["Transformable"].setClass(kaguya::UserdataMetatable<Transformable, Configurable>());
    m_state["CanvasElement"].setClass(kaguya::UserdataMetatable<CanvasElement, Drawable>());
    m_state["Line"].setClass(kaguya::UserdataMetatable<Line, kaguya::MultipleBase<CanvasElement, Colorable>>());
    m_state["Rectangle"].setClass(kaguya::UserdataMetatable<Rectangle, kaguya::MultipleBase<CanvasElement, Colorable, Transformable>>());
    m_state["Canvas"].setClass(kaguya::UserdataMetatable<Canvas>()
        .addFunction("Line", &Canvas::line)
        .addFunction("Rectangle", &Canvas::rectangle)
        .addFunction("Get", &Canvas::get)
    );
}

Line* Canvas::line(std::string id)
{
    Line* newLine = new Line(id);
    elements[id] = newLine;
    return newLine;
}

Rectangle* Canvas::rectangle(std::string id)
{
    Rectangle* newRectangle = new Rectangle(id);
    elements[id] = newRectangle;
    return newRectangle;
}

kaguya::LuaTable& Canvas::get(std::string id)
{
    return elements[id]->get();
}

void Canvas::clear()
{
    m_canvas.clear(sf::Color(0, 0, 0, 0));
}

void Canvas::draw(const sf::Drawable& drawable)
{
    m_canvas.draw(drawable);
}

void Canvas::render()
{
    for (auto& element : elements)
    {
        element.second->update(m_state);
        element.second->draw(m_canvas);
    }
}

kaguya::State& Canvas::getState()
{
    return m_state;
}

const sf::Texture& Canvas::getTexture()
{
    m_canvas.display();
    return m_canvas.getTexture();
}
