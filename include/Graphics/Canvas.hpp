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
        /**
         * \brief Basic class for CanvasElement
         */
        class Element
        {
        protected:
            std::vector<std::pair<std::string, std::string>> requires;
            std::string m_id;
        public:
            /**
             * \brief Creates a new Canvas Element
             * \param id Id of the new Element
             */
            explicit Element(const std::string& id);
            /**
             * \brief Default destructor of Element
             */
            virtual ~Element() = default;
            /**
             * \brief Abstract update method
             * \param state Lua VM to update
             */
            virtual void update() = 0;
        };

        /**
         * \brief A Configurable Canvas Element (can have properties)
         */
        class Configurable : public virtual Element
        {
        protected:
            kaguya::LuaTable m_tableWrapper;
        public:
            /**
             * \brief Creates a new Configurable Canvas Element
             * \param id 
             */
            explicit Configurable(const std::string& id);
            /**
             * \brief Initialize the Configurable
             * \param tableWrapper LuaTable reference used for configuration
             * \return A reference to the LuaTable passed by parameter
             */
            kaguya::LuaTable& init(const kaguya::LuaTable& tableWrapper);
            /**
             * \brief Get a reference to the LuaTable used for configuration
             * \return A reference to the LuaTable used for configuration
             */
            kaguya::LuaTable& get();
            /**
             * \brief Updates the Configurable
             * \param state Lua VM to update
             */
            void update() override;
        };

        /**
         * \brief A Drawable Canvas Element
         */
        class Drawable : public virtual Configurable
        {
        protected:
            unsigned int m_layer = 1;
        public:
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
            /**
             * \brief Updates the Drawable
             * \param state Lua VM to update
             */
            void update() override;
        };

        /**
         * \brief A Colorable Canvas Element
         */
        class Colorable : public virtual Drawable
        {
        protected:
            sf::Color m_color;
        public:
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
            /**
             * \brief Updates the Colorable
             * \param state Lua VM to update
             */
            void update() override;
        };

        /**
         * \brief A Transformable Canvas Element
         */
        class Transformable : public virtual Configurable
        {
        protected:
            float m_x;
            float m_y;
            float m_width;
            float m_height;
            float m_rotation;
            float m_translationOriginX;
            float m_translationOriginY;
            float m_rotationOriginX;
            float m_rotationOriginY;
        public:
            /**
             * \brief Creates a new Transformable
             * \param id Id of the new Transformable
             */
            explicit Transformable(const std::string& id);
            /**
             * \brief Updates the Transformable
             * \param state Lua VM to update
             */
            void update() override;
        };

        /**
         * \brief A CanvasElement (Base class for all real CanvasElements)
         */
        class CanvasElement : public virtual Drawable
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
            /**
             * \brief Updates the CanvasElement
             * \param state Lua VM to update
             */
            void update() override;
        };

        /**
         * \brief A Canvas Line
         */
        class Line : public CanvasElement, public Colorable
        {
        private:
            float m_x1;
            float m_x2;
            float m_y1;
            float m_y2;
        public:
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
            /**
             * \brief Updates the Line
             * \param state Lua VM to update
             */
            void update() override;
        };

        /**
         * \brief A Canvas Rectangle
         */
        class Rectangle : public CanvasElement, public Colorable, public Transformable
        {
        public:
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
            /**
             * \brief Updates the Rectangle
             * \param state Lua VM to update
             */
            void update() override;
        };

        /**
         * \brief A Canvas Text
         */
        class Text : public CanvasElement, public Colorable, public Transformable
        {
        private:
            int m_characterSize;
            std::string m_text;
            std::string m_font;
        public:
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
            /**
             * \brief Updates the Text
             * \param state Lua VM to update
             */
            void update() override;
        };

        /**
         * \brief A Canvas Circle
         */
        class Circle : public CanvasElement, public Colorable, public Transformable
        {
        private:
            float m_radius;
        public:
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
            /**
             * \brief Updates the Circle
             * \param state Lua VM to update
             */
            void update() override;
        };

        /**
         * \brief A Canvas where you can draw CanvasElements on
         */
        class Canvas
        {
        private:
            LevelSprite* m_target;
            sf::RenderTexture m_canvas;
            std::map<std::string, CanvasElement*> elements;
        public:
            /**
             * \brief Creates a new Canvas
             * \param state Lua VM connected to the Canvas
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
            /*Polygon& Polygon(std::string id);
            Shader& Shader(std::string id);
            Vertexes& Vertexes(std::string id);*/

            /**
             * \brief Get a reference to the LuaTable connected to a CanvasElement
             * \param id Id of the CanvasElement to get the LuaTable
             * \return A reference to the LuaTable of the CanvasElement
             */
            kaguya::LuaTable& get(std::string id);

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
