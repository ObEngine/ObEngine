#pragma once

#include <vector>

#include <kaguya/kaguya.hpp>
#include <sfe/RichText.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <Graphics/LevelSprite.hpp>

namespace obe
{
    namespace Graphics
    {
            namespace Canvas
            {
            /**
             * \brief A Drawable Canvas Element
             */
            class CanvasElement
            {
            public:
                std::string id;
                unsigned int layer = 1;
                bool visible;

                /**
                 * \brief Creates a new CanvasElement
                 * \param id Id of the new CanvasElement
                 */
                explicit CanvasElement(const std::string& id);
                /**
                 * \brief Abstract draw method
                 * \param target Target where to render the result
                 */
                virtual void draw(sf::RenderTexture& target) = 0;
                virtual ~CanvasElement() = default;
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
                sf::Color color;

                /**
                 * \brief Creates a new Line
                 * \param id 
                 */
                explicit Line(const std::string& id);
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
                std::string fontPath;
                sfe::RichText shape;
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
                void draw(sf::RenderTexture& target) override;
            };

            /**
             * \brief A Canvas Circle
             */
            class Circle : public CanvasElement
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
                void draw(sf::RenderTexture& target) override;
            };

            /*
            * \brief A Canvas Sprite
            */
            class Sprite : public CanvasElement
            {
            public:
                std::string path;
                sfe::ComplexSprite sprite;
                explicit Sprite(const std::string& id);
                /**
                 * \brief Draws the Sprite
                 * \param target Target where to draw the Sprite to
                 */
                void draw(sf::RenderTexture& target) override;
            };

            /**
             * \brief A Canvas where you can draw CanvasElements on
             */
            using CanvasElementPair = std::pair<std::string, std::unique_ptr<CanvasElement>>;
            class Canvas
            {
            private:
                LevelSprite* m_target;
                sf::RenderTexture m_canvas;
                std::vector<CanvasElementPair> m_elements;
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
            };
        }
    }
}
