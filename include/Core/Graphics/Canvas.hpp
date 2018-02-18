#pragma once

#include <string>
#include <vector>

#include <kaguya/kaguya.hpp>
#include <sfe/RichText.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <Component/Component.hpp>
#include <Debug/Logger.hpp>
#include <Graphics/LevelSprite.hpp>

namespace obe
{
    namespace Graphics
    {
        namespace Canvas
        {
            enum class CanvasElementType
            {
                CanvasElement,
                Line,
                Rectangle,
                Text,
                Circle,
                Sprite
            };

            class Canvas;
            /**
             * \brief A Drawable Canvas Element
             */
            class CanvasElement
            {
            public:
                static const CanvasElementType Type = CanvasElementType::CanvasElement;

                Canvas* parent;
                std::string id; // <REVISION> Possible id overlap in Canvas
                unsigned int layer = 1;
                bool visible = true;
                CanvasElementType type;

                /**
                 * \brief Creates a new CanvasElement
                 * \param id Id of the new CanvasElement
                 */
                explicit CanvasElement(Canvas* parent, const std::string& id);
                /**
                 * \brief Abstract draw method
                 * \param target Target where to render the result
                 */
                virtual void draw(sf::RenderTexture& target) = 0;
                virtual ~CanvasElement() = default;

                /*
                 * \brief Changes layer or object and will ask the Canvas to reorder elements automatically
                 */
                void setLayer(unsigned int layer);

                using Ptr = std::unique_ptr<CanvasElement>;
            };

            /**
             * \brief A Canvas Line
             */
            class Line : public CanvasElement
            {
            public:
                Transform::UnitVector p1;
                Transform::UnitVector p2;
                unsigned int thickness;
                sf::Color p1color;
                sf::Color p2color;
                static const CanvasElementType Type = CanvasElementType::Line;

                /**
                 * \brief Creates a new Line
                 * \param id
                 */
                explicit Line(Canvas* parent, const std::string& id);
                /**
                 * \brief Draws the Line
                 * \param target Target where to draw the Line to
                 */
                void draw(sf::RenderTexture& target) override;
            };

            /**
             * \brief A Canvas Rectangle
             */
            class Rectangle : public CanvasElement
            {
            public:
                static const CanvasElementType Type = CanvasElementType::Rectangle;

                sf::RectangleShape shape;
                /**
                 * \brief Creates a new Rectangle
                 * \param id Id of the new Rectangle
                 */
                explicit Rectangle(Canvas* parent, const std::string& id);
                /**
                 * \brief Draws the Rectangle
                 * \param target Target where to draw the Rectangle to
                 */
                void draw(sf::RenderTexture& target) override;
            };

            enum class TextHorizontalAlign
            {
                Left,
                Center,
                Right
            };

            enum class TextVerticalAlign
            {
                Top,
                Center,
                Bottom
            };

            /**
             * \brief A Canvas Text
             */
            class Text : public CanvasElement
            {
            public:
                static const CanvasElementType Type = CanvasElementType::Text;

                std::string fontPath;
                sfe::RichText shape;
                TextHorizontalAlign h_align;
                TextVerticalAlign v_align;
                /**
                 * \brief Creates a new Text
                 * \param id Id of the new Text
                 */
                explicit Text(Canvas* parent, const std::string& id);
                /**
                 * \brief Draws the Text
                 * \param target Target where to draw the Text to
                 */
                void draw(sf::RenderTexture& target) override;
            };

            /**
             * \brief A Canvas Circle
             */
            class Circle : public CanvasElement
            {
            public:
                static const CanvasElementType Type = CanvasElementType::Circle;

                sf::CircleShape shape;
                float radius;
                /**
                 * \brief Creates a new Circle
                 * \param id Id of the new Circle
                 */
                explicit Circle(Canvas* parent, const std::string& id);
                /**
                 * \brief Draws the Circle
                 * \param target Target where to draw the Circle to
                 */
                void draw(sf::RenderTexture& target) override;
            };

            /*
            * \brief A Canvas Sprite
            */
            class Sprite : public CanvasElement
            {
            public:
                static const CanvasElementType Type = CanvasElementType::Sprite;

                std::string path;
                sfe::ComplexSprite sprite;
                explicit Sprite(Canvas* parent, const std::string& id);
                /**
                 * \brief Draws the Sprite
                 * \param target Target where to draw the Sprite to
                 */
                void draw(sf::RenderTexture& target) override;
            };

            /**
             * \brief A Canvas where you can draw CanvasElements on
             */
            class Canvas
            {
            private:
                LevelSprite* m_target;
                sf::RenderTexture m_canvas;
                std::vector<CanvasElement::Ptr> m_elements;
                bool m_sortRequired = true;
                void sortElements();
            public:
                /**
                 * \brief Creates a new Canvas
                 * \param width Width of the Canvas (in pixels)
                 * \param height Height of the Canvas (in pixels)
                 */
                Canvas(unsigned int width, unsigned int height);

                template <class S>
                S* add(const std::string& id);

                CanvasElement* get(const std::string& id);

                /**
                 * \brief Sets the LevelSprite where the Canvas should render
                 * \param target Pointer to the LevelSprite where the Canvas should render
                 */
                void setTarget(LevelSprite* target);
                /**
                 * \brief Renders all the Canvas content to the LevelSprite target
                 */
                void render();
                /**
                 * \brief Clears all CanvasElement from the Canvas
                 */
                void clear();
                /**
                 * \brief Removes a CanvasElement from the Canvas
                 * \param id Id of the CanvasElement to remove
                 */
                void remove(const std::string& id);
                /**
                 * \brief Gets the current Texture of the Canvas
                 * \return A reference to the current Texture of the Canvas
                 */
                const sf::Texture& getTexture() const;
                /**
                * \brief Asks the Canvas to sort elements for the next rendering
                */
                void requiresSort();
            };

            template <class S>
            inline S* Canvas::add(const std::string& id)
            {
                if (this->get(id) == nullptr)
                {
                    m_sortRequired = true;
                    m_elements.push_back(std::make_unique<S>(this, id));
                    return static_cast<S*>(m_elements.back().get());
                }
                else if (this->get(id)->type == S::Type)
                {
                    Debug::Log->warn("<Scene> CanvasElement '{0}' already exists !", id);
                    return static_cast<S*>(this->get(id));
                }
                else
                {
                    throw aube::ErrorHandler::Raise("obe.Graphics.Canvas.Canvas.ElementAlreadyExistsWithDifferentType");
                }
            }
        }
    }
}
