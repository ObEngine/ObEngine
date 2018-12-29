#include <Graphics/Canvas.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Script/GlobalState.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <Utils/StringUtils.hpp>

namespace obe::Graphics::Canvas
{     
    CanvasElement::CanvasElement(Canvas* parent, const std::string& id) : ProtectedIdentifiable(id)
    {
        this->parent = parent;
    }

    CanvasElement::~CanvasElement()
    {
    }

    void CanvasElement::setLayer(const unsigned int layer)
    {
        if (this->layer != layer)
        {
            this->layer = layer;
            parent->requiresSort();
        }
    }
    
    Line::Line(Canvas* parent, const std::string& id) : CanvasElement(parent, id)
    {
    }
    
    void Line::draw(sf::RenderTexture& target)
    {
        const Transform::UnitVector p1px = p1.to<Transform::Units::ScenePixels>();
        const Transform::UnitVector p2px = p2.to<Transform::Units::ScenePixels>();
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(p1px.x, p1px.y), p1color),
            sf::Vertex(sf::Vector2f(p2px.x, p2px.y), p2color)
        };
        target.draw(line, 2, sf::Lines);
    }

    CanvasPositionable::CanvasPositionable(Canvas* parent, const std::string& id) : CanvasElement(parent, id)
    {
        // Default Canvas elements unit is ScenePixels
        position.unit = Transform::Units::ScenePixels;
    }

    Rectangle::Rectangle(Canvas* parent, const std::string& id) : CanvasPositionable(parent, id)
    {
        this->size.unit = Transform::Units::ScenePixels;
    }
    
    void Rectangle::draw(sf::RenderTexture& target)
    {
        target.draw(shape);
    }
    
    Text::Text(Canvas* parent, const std::string& id) : CanvasPositionable(parent, id)
    {
    }
    
    void Text::draw(sf::RenderTexture& target)
    {
        sf::Vector2f offset;
        if (h_align == TextHorizontalAlign::Center)
            offset.x -= shape.getGlobalBounds().width / 2;
        else if (h_align == TextHorizontalAlign::Right)
            offset.x -= shape.getGlobalBounds().width;
        if (v_align == TextVerticalAlign::Center)
            offset.y -= shape.getGlobalBounds().height / 2;
        else if (v_align == TextVerticalAlign::Bottom)
            offset.y -= shape.getGlobalBounds().height;     
        shape.move(offset);
        target.draw(shape);
        shape.move(-offset);
    }
    
    Circle::Circle(Canvas* parent, const std::string& id) : CanvasPositionable(parent, id)
    {
    }
    
    void Circle::draw(sf::RenderTexture& target)
    {
        target.draw(shape);
    }

    Polygon::Polygon(Canvas* parent, const std::string& id) : CanvasPositionable(parent, id)
    {
    }

    void Polygon::draw(sf::RenderTexture& target)
    {
        target.draw(shape);
    }

    Sprite::Sprite(Canvas* parent, const std::string& id) : CanvasPositionable(parent, id)
    {
    }
    
    void Sprite::draw(sf::RenderTexture& target)
    {
        target.draw(sprite);
    }
    
    void Canvas::sortElements()
    {
        std::sort(m_elements.begin(), m_elements.end(), [](const auto& elem1, const auto& elem2)
        {
            return elem1->layer > elem2->layer;
        });
    }

    Canvas::Canvas(unsigned int width, unsigned int height)
    {
        m_canvas.create(width, height);
    }

    CanvasElement* Canvas::get(const std::string & id)
    {
        for (auto& elem : m_elements)
        {
            if (elem->getId() == id)
            {
                return elem.get();
            }
        }
        return nullptr;
    }
    
    void Canvas::setTarget(LevelSprite* target)
    {
        m_target = target;
    }
    
    void Canvas::render()
    {
        m_canvas.clear(sf::Color(0, 0, 0, 0));

        if (m_sortRequired)
        {
            this->sortElements();
            m_sortRequired = false;
        }
                
        for (auto& element : m_elements)
        {
            if (element->visible)
                element->draw(m_canvas);
        }
        m_canvas.display();
        m_target->setTexture(m_canvas.getTexture());
    }

    void Canvas::clear()
    {
        m_elements.clear();
    }

    void Canvas::remove(const std::string& id)
    {
        m_elements.erase(std::remove_if(m_elements.begin(), m_elements.end(), [&id](auto& elem)
        {
            return elem->getId() == id;
        }), m_elements.end());
    }

    const sf::Texture& Canvas::getTexture() const
    {
        return m_canvas.getTexture();
    }

    void Canvas::requiresSort()
    {
        m_sortRequired = true;
    }
}