#include <Graphics/Canvas.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Script/GlobalState.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>

namespace obe
{
    namespace Graphics
    {
        namespace Canvas
        {            
            CanvasElement::CanvasElement(const std::string& id)
            {
                this->id = id;
            }
    
    
            Line::Line(const std::string& id) : CanvasElement(id)
            {
            }
    
            void Line::draw(sf::RenderTexture& target)
            {
                Transform::UnitVector p1px = p1.to<Transform::Units::WorldPixels>();
                Transform::UnitVector p2px = p2.to<Transform::Units::WorldPixels>();
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(p1px.x, p1px.y), color),
                    sf::Vertex(sf::Vector2f(p2px.x, p2px.y), color)
                };
                target.draw(line, 2, sf::Lines);
            }
    
            Rectangle::Rectangle(const std::string& id) : CanvasElement(id)
            {
            }
    
            void Rectangle::draw(sf::RenderTexture& target)
            {
                target.draw(shape);
            }
    
            Text::Text(const std::string& id) : CanvasElement(id)
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
    
            Circle::Circle(const std::string& id) : CanvasElement(id)
            {
            }
    
            void Circle::draw(sf::RenderTexture& target)
            {
                target.draw(shape);
            }
    
            Sprite::Sprite(const std::string& id) : CanvasElement(id)
            {
            }
    
            void Sprite::draw(sf::RenderTexture& target)
            {
                target.draw(sprite);
            }
    
            Canvas::Canvas(unsigned int width, unsigned int height)
            {
                m_canvas.create(width, height);
            }
    
            Line* Canvas::line(const std::string& id)
            {
                m_elements.push_back(CanvasElementPair(id, std::make_unique<Line>(id)));
                return static_cast<Line*>(m_elements.back().second.get());
            }
    
            Rectangle* Canvas::rectangle(const std::string& id)
            {
                m_elements.push_back(CanvasElementPair(id, std::make_unique<Rectangle>(id)));
                return static_cast<Rectangle*>(m_elements.back().second.get());
            }
    
            Text* Canvas::text(const std::string& id)
            {
                m_elements.push_back(CanvasElementPair(id, std::make_unique<Text>(id)));
                return static_cast<Text*>(m_elements.back().second.get());
            }
    
            Circle* Canvas::circle(const std::string& id)
            {
                m_elements.push_back(CanvasElementPair(id, std::make_unique<Circle>(id)));
                return static_cast<Circle*>(m_elements.back().second.get());
            }
    
            Sprite* Canvas::sprite(const std::string& id)
            {
                m_elements.push_back(CanvasElementPair(id, std::make_unique<Sprite>(id)));
                return static_cast<Sprite*>(m_elements.back().second.get());
            }
    
            void Canvas::setTarget(LevelSprite* target)
            {
                m_target = target;
            }
    
            void Canvas::render()
            {
                m_canvas.clear(sf::Color(0, 0, 0, 0));
                std::sort(m_elements.begin(), m_elements.end(), [](const auto& elem1, const auto& elem2)
                {
                    return elem1.second->layer > elem2.second->layer;
                });
                for (auto& element : m_elements)
                {
                    if (element.second->visible)
                        element.second->draw(m_canvas);
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
                    return elem.second->id == id;
                }), m_elements.end());
            }

            const sf::Texture& Canvas::getTexture() const
            {
                return m_canvas.getTexture();
            }
        }
    }
}
