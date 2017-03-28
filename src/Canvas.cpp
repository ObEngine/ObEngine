#include "Canvas.hpp"

Element::Element(const std::string& id)
{
    m_id = id;
}

Drawable::Drawable(const std::string& id) : Element(id)
{
}

void Drawable::update(kaguya::State& state)
{
    m_layer = state[m_id]["layer"];
}

Colorable::Colorable(const std::string& id) : Drawable(id), Element(id)
{
}

void Colorable::update(kaguya::State& state)
{
    Drawable::update(state);
    m_color = sf::Color(state[m_id]["color"]["r"],
                        state[m_id]["color"]["g"],
                        state[m_id]["color"]["b"],
                        state[m_id]["color"]["a"]);
}

Transformable::Transformable(const std::string& id) : Element(id)
{

}

void Transformable::update(kaguya::State& state)
{
    m_x = state[m_id]["x"];
    m_y = state[m_id]["y"];
    m_width = state[m_id]["width"];
    m_height = state[m_id]["height"];
    m_rotation = state[m_id]["rotation"];
    m_translationOriginX = state[m_id]["origin"]["translation"]["x"];
    m_translationOriginY = state[m_id]["origin"]["translation"]["y"];
    m_rotationOriginX = state[m_id]["origin"]["rotation"]["x"];
    m_rotationOriginY = state[m_id]["origin"]["rotation"]["y"];
}

Configurable::Configurable(const std::string& id) : Element(id)
{
}

void Configurable::init(const kaguya::LuaFunction& configureFunction)
{
    std::cout << "Configuring.." << std::endl;
    m_configureFunction = configureFunction;
    m_useConfiguration = true;
}

void Configurable::build(kaguya::State& state)
{
    m_configureFunction(state[m_id]);
}

CanvasElement::CanvasElement(const std::string& id) : Drawable(id), Configurable(id), Element(id)
{

}

void CanvasElement::update(kaguya::State& state)
{
    Drawable::update(state);
}

Line::Line(const std::string& id) : CanvasElement(id), Drawable(id), Colorable(id), Element(id)
{
}
void Line::draw(sf::RenderTexture& target) const
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(m_x1, m_y1)),
        sf::Vertex(sf::Vector2f(m_x2, m_y2))
    };
    target.draw(line, 2, sf::Lines);
}
void Line::update(kaguya::State& state)
{
    Colorable::update(state);
    m_x1 = state[m_id]["x1"];
    m_y1 = state[m_id]["y1"];
    m_x2 = state[m_id]["x2"];
    m_y2 = state[m_id]["y2"];
}

Canvas::Canvas(unsigned int width, unsigned int height)
{
    m_canvas.create(width, height);
    m_state.dofile("CanvasConfig.lua");

    m_state["AttributeArray"].setClass(kaguya::UserdataMetatable<AttributeArray>());
    m_state["Element"].setClass(kaguya::UserdataMetatable<Element, AttributeArray>());
    m_state["Drawable"].setClass(kaguya::UserdataMetatable<Drawable, Element>());
    m_state["Colorable"].setClass(kaguya::UserdataMetatable<Colorable, Drawable>());
    m_state["Transformable"].setClass(kaguya::UserdataMetatable<Transformable, Element>());
    m_state["Configurable"].setClass(kaguya::UserdataMetatable<Configurable, Element>()
        .addFunction("init", &Line::init)
    );
    m_state["CanvasElement"].setClass(kaguya::UserdataMetatable<CanvasElement, kaguya::MultipleBase<Drawable, Configurable>>());
    m_state["Line"].setClass(kaguya::UserdataMetatable<Line, kaguya::MultipleBase<CanvasElement, Colorable>>());
    m_state["Canvas"].setClass(kaguya::UserdataMetatable<Canvas>()
        .addFunction("line", &Canvas::line)
    );
}

Line* Canvas::line(std::string id)
{
    m_state[id] = kaguya::NewTable();
    m_state[id]["id"] = id;
    m_state["DefaultValues"](m_state[id]);

    std::cout << "Building line" << std::endl;

    Line* newLine = new Line(id);
    elements.push_back(newLine);
    return newLine;
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
    for (CanvasElement* element : elements)
    {
        element->build(m_state);
        element->update(m_state);
        element->draw(m_canvas);
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
