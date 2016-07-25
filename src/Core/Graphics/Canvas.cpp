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
    
            void Line::draw(sf::RenderTexture& target) const
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
    
            void Rectangle::draw(sf::RenderTexture& target) const
            {
                target.draw(shape);
            }
    
            Text::Text(const std::string& id) : CanvasElement(id)
            {
            }
    
            void Text::draw(sf::RenderTexture& target) const
            {
                target.draw(text);
            }
    
            Circle::Circle(const std::string& id) : CanvasElement(id)
            {
            }
    
            void Circle::draw(sf::RenderTexture& target) const
            {
                target.draw(shape);
            }
    
            Sprite::Sprite(const std::string& id) : CanvasElement(id)
            {
            }
    
            void Sprite::draw(sf::RenderTexture& target) const
            {
                target.draw(sprite);
            }
    
            Canvas::Canvas(unsigned int width, unsigned int height)
            {
                m_canvas.create(width, height);
            }
    
            Line* Canvas::line(const std::string& id)
            {
                std::unique_ptr<Line> newline = std::make_unique<Line>(id);
                auto it = elements.emplace(id, std::move(newline));
                return static_cast<Line*>(it.first->second.get());
            }
    
            Rectangle* Canvas::rectangle(const std::string& id)
            {
                std::unique_ptr<Rectangle> newrectangle = std::make_unique<Rectangle>(id);
                auto it = elements.emplace(id, std::move(newrectangle));
                return static_cast<Rectangle*>(it.first->second.get());
            }
    
            Text* Canvas::text(const std::string& id)
            {
                std::unique_ptr<Text> newtext = std::make_unique<Text>(id);
                auto it = elements.emplace(id, std::move(newtext));
                return static_cast<Text*>(it.first->second.get());
            }
    
            Circle* Canvas::circle(const std::string& id)
            {
                std::unique_ptr<Circle> newcircle = std::make_unique<Circle>(id);
                auto it = elements.emplace(id, std::move(newcircle));
                return static_cast<Circle*>(it.first->second.get());
            }
    
            Sprite* Canvas::sprite(const std::string& id)
            {
                std::unique_ptr<Sprite> newsprite = std::make_unique<Sprite>(id);
                auto it = elements.emplace(id, std::move(newsprite));
                return static_cast<Sprite*>(it.first->second.get());
            }
    
            void Canvas::setTarget(LevelSprite* target)
            {
                m_target = target;
            }
    
            void Canvas::render()
            {
                m_canvas.clear(sf::Color(0, 0, 0, 0));
                for (auto& element : elements)
                {
                    element.second->draw(m_canvas);
                }
                m_canvas.display();
                m_target->setTexture(m_canvas.getTexture());
            }
    
            const sf::Texture& Canvas::getTexture() const
            {
                return m_canvas.getTexture();
            }
        }
    }
}
