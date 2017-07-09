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
        class Element
        {
        protected:
            std::vector<std::pair<std::string, std::string>> requires;
            std::string m_id;
        public:
            Element(const std::string& id);
            virtual ~Element() = default;
            virtual void update(kaguya::State* state) = 0;
        };

        class Configurable : public virtual Element
        {
        protected:
            kaguya::LuaTable m_tableWrapper;
        public:
            Configurable(const std::string& id);
            kaguya::LuaTable& init(const kaguya::LuaTable& tableWrapper);
            kaguya::LuaTable& get();
            void update(kaguya::State* state) override;
        };

        class Drawable : public virtual Configurable
        {
        protected:
            unsigned int m_layer = 1;
        public:
            Drawable(const std::string& id);
            virtual void draw(sf::RenderTexture& target) const = 0;
            void update(kaguya::State* state) override;
        };

        class Colorable : public virtual Drawable
        {
        protected:
            sf::Color m_color;
        public:
            Colorable(const std::string& id);
            void draw(sf::RenderTexture& target) const override = 0;
            void update(kaguya::State* state) override;
        };

        class Transformable : public virtual Configurable
        {
        protected:
            double m_x;
            double m_y;
            double m_width;
            double m_height;
            double m_rotation;
            double m_translationOriginX;
            double m_translationOriginY;
            double m_rotationOriginX;
            double m_rotationOriginY;
        public:
            Transformable(const std::string& id);
            void update(kaguya::State* state) override;
        };

        class CanvasElement : public virtual Drawable
        {
        public:
            CanvasElement(const std::string& id);
            void draw(sf::RenderTexture& target) const override = 0;
            void update(kaguya::State* state) override;
        };

        class Line : public CanvasElement, public Colorable
        {
        private:
            int m_x1;
            int m_x2;
            int m_y1;
            int m_y2;
        public:
            Line(const std::string& id);
            void draw(sf::RenderTexture& target) const override;
            void update(kaguya::State* state) override;
        };

        class Rectangle : public CanvasElement, public Colorable, public Transformable
        {
        public:
            Rectangle(const std::string& id);
            void draw(sf::RenderTexture& target) const override;
            void update(kaguya::State* state) override;
        };

        class Text : public CanvasElement, public Colorable, public Transformable
        {
        private:
            int m_characterSize;
            std::string m_text;
            std::string m_font;
        public:
            Text(const std::string& id);
            void draw(sf::RenderTexture& target) const override;
            void update(kaguya::State* state) override;
        };

        class Circle : public CanvasElement, public Colorable, public Transformable
        {
        private:
            double m_radius;
        public:
            Circle(const std::string& id);
            void draw(sf::RenderTexture& target) const override;
            void update(kaguya::State* state) override;
        };

        class Canvas
        {
        private:
            kaguya::State* m_state;
            LevelSprite* m_target;
            sf::RenderTexture m_canvas;
            std::map<std::string, CanvasElement*> elements;
        public:
            Canvas(kaguya::State* state, unsigned int width, unsigned int height);

            Line* line(const std::string& id);
            Rectangle* rectangle(const std::string& id);
            Text* text(const std::string& id);
            Circle* circle(const std::string& id);
            /*Polygon& Polygon(std::string id);
            Shader& Shader(std::string id);
            Vertexes& Vertexes(std::string id);*/

            kaguya::LuaTable& get(std::string id);

            void setTarget(LevelSprite* target);
            void render();
            const sf::Texture& getTexture();
        };
    }
}
