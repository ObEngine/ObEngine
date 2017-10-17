#pragma once

#include <string>
#include <vector>

#include <kaguya/kaguya.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <Graphics/LevelSprite.hpp>

namespace obe
{
    namespace Graphics
    {
            namespace Canvas
            {
            /**
             * \brief Basic class for CanvasElement
             */
            class Element
            {
            public:
                std::string id;
                /**
                 * \brief Creates a new Canvas Element
                 * \param id Id of the new Element
                 */
                explicit Element(const std::string& id);
                /**
                 * \brief Default destructor of Element
                 */
                virtual ~Element() = default;
            };


            /**
             * \brief A Drawable Canvas Element
             */
            class Drawable : public virtual Element
            {
            public:
                unsigned int layer;
                /**
                 * \brief Creates a new Drawable
                 * \param id Id of the new Drawable
                 */
                explicit Drawable(const std::string& id);
                /**
                 * \brief Abstract draw method
                 * \param target Target where to render the result
                 */
                virtual void draw(sf::RenderTexture& target) const = 0;
            };

            /**
             * \brief A Colorable Canvas Element
             */
            class Colorable : public virtual Drawable
            {
            public:
                sf::Color color;
                /**
                 * \brief Creates a new Colorable
                 * \param id Id of the new Colorable
                 */
                explicit Colorable(const std::string& id);
                /**
                 * \brief Abstracts draw method
                 * \param target Target where to render the result
                 */
                void draw(sf::RenderTexture& target) const override = 0;
            };

            /**
             * \brief A Transformable Canvas Element
             */
            class Transformable : public virtual Element
            {
            public:
                Transform::UnitVector position;
                Transform::UnitVector size;
                float angle;
                Transform::UnitVector translationOrigin;
                Transform::UnitVector rotationOrigin;
                /**
                 * \brief Creates a new Transformable
                 * \param id Id of the new Transformable
                 */
                explicit Transformable(const std::string& id);
            };

            /**
             * \brief A CanvasElement (Base class for all real CanvasElements)
             */
            class CanvasElement : public Drawable
            {
            public:
                /**
                 * \brief Creates a new CanvasElement
                 * \param id Id of the new CanvasElement
                 */
                explicit CanvasElement(const std::string& id);
                /**
                 * \brief Abstract draw method
                 * \param target Target where to draw the result to
                 */
                void draw(sf::RenderTexture& target) const override = 0;
            };

            /**
             * \brief A Canvas Line
             */
            class Line : public CanvasElement, public Colorable
            {
            public:
                Transform::UnitVector p1;
                Transform::UnitVector p2;
                /**
                 * \brief Creates a new Line
                 * \param id 
                 */
                explicit Line(const std::string& id);
                /**
                 * \brief Draws the Line
                 * \param target Target where to draw the Line to
                 */
                void draw(sf::RenderTexture& target) const override;
            };

            /**
             * \brief A Canvas Rectangle
             */
            class Rectangle : public CanvasElement, public Colorable, public Transformable
            {
            public:
                sf::RectangleShape shape;
                /**
                 * \brief Creates a new Rectangle
                 * \param id Id of the new Rectangle
                 */
                explicit Rectangle(const std::string& id);
                /**
                 * \brief Draws the Rectangle
                 * \param target Target where to draw the Rectangle to
                 */
                void draw(sf::RenderTexture& target) const override;
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
            class Text : public CanvasElement, public Colorable, public Transformable
            {
            public:
                int characterSize;
                std::string content;
                sf::Text text;
                sf::Font font;
                TextHorizontalAlign h_align;
                TextVerticalAlign v_align;
                /**
                 * \brief Creates a new Text
                 * \param id Id of the new Text
                 */
                explicit Text(const std::string& id);
                /**
                 * \brief Draws the Text
                 * \param target Target where to draw the Text to
                 */
                void draw(sf::RenderTexture& target) const override;
            };

            /**
             * \brief A Canvas Circle
             */
            class Circle : public CanvasElement, public Colorable, public Transformable
            {
            public:
                sf::CircleShape shape;
                float radius;
                /**
                 * \brief Creates a new Circle
                 * \param id Id of the new Circle
                 */
                explicit Circle(const std::string& id);
                /**
                 * \brief Draws the Circle
                 * \param target Target where to draw the Circle to
                 */
                void draw(sf::RenderTexture& target) const override;
            };

            /*
            * \brief A Canvas Sprite
            */
            class Sprite : public CanvasElement, public Colorable, public Transformable
            {
            public:
                sf::Texture texture;
                sfe::ComplexSprite sprite;
                explicit Sprite(const std::string& id);
                /**
                 * \brief Draws the Sprite
                 * \param target Target where to draw the Sprite to
                 */
                void draw(sf::RenderTexture& target) const override;
            };

            /**
             * \brief A Canvas where you can draw CanvasElements on
             */
            class Canvas
            {
            private:
                LevelSprite* m_target;
                sf::RenderTexture m_canvas;
                std::map<std::string, std::unique_ptr<CanvasElement>> elements;
            public:
                /**
                 * \brief Creates a new Canvas
                 * \param width Width of the Canvas (in pixels)
                 * \param height Height of the Canvas (in pixels)
                 */
                Canvas(unsigned int width, unsigned int height);

                /**
                 * \brief Adds a new Line to the Canvas
                 * \param id Id of the new Line
                 * \return A pointer to the newly created Line
                 */
                Line* line(const std::string& id);
                /**
                 * \brief Adds a new Rectangle to the Canvas
                 * \param id Id of the new Rectangle
                 * \return A pointer to the newly created Rectangle
                 */
                Rectangle* rectangle(const std::string& id);
                /**
                 * \brief Adds a new Text to the Canvas
                 * \param id Id of the new Text
                 * \return A pointer to the newly created Text
                 */
                Text* text(const std::string& id);
                /**
                 * \brief Adds a new Circle to the Canvas
                 * \param id Id of the new Circle
                 * \return A pointer to the newly created Circle
                 */
                Circle* circle(const std::string& id);

                Sprite* sprite(const std::string& id);
                /*Polygon& Polygon(std::string id);
                Shader& Shader(std::string id);
                Vertexes& Vertexes(std::string id);*/

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
                 * \brief Gets the current Texture of the Canvas
                 * \return A reference to the current Texture of the Canvas
                 */
                const sf::Texture& getTexture() const;
            };
        }
    }
}
