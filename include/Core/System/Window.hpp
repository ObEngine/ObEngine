#pragma once

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vili/node.hpp>

#include <Graphics/Color.hpp>
#include <Graphics/RenderTarget.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::System
{
    enum class WindowContext
    {
        GameWindow,
        EditorWindow
    };

    class Window
    {
    private:
        unsigned int m_width = 1920;
        unsigned int m_height = 1080;
        int m_style;
        std::string m_title;
        sf::RenderWindow m_window;
        Graphics::Color m_background = Graphics::Color(0, 0, 0);

    public:
        explicit Window(vili::node configuration);
        void create();
        void clear();
        void close();
        void display();
        /**
         * \nobind
         */
        void draw(const sf::Drawable& drawable,
            const sf::RenderStates& states = sf::RenderStates::Default);
        /**
         * \nobind
         */
        void draw(const sf::Vertex* vertices, std::size_t vertexCount,
            sf::PrimitiveType type,
            const sf::RenderStates& states = sf::RenderStates::Default);
        [[nodiscard]] Transform::UnitVector getSize() const;
        [[nodiscard]] bool isOpen() const;
        bool pollEvent(sf::Event& event);
        void setSize(unsigned int width, unsigned int height);
        void setTitle(const std::string& title);
        void setVerticalSyncEnabled(bool enabled);
        void setView(const sf::View& view);

        Graphics::RenderTarget getTarget();
        sf::RenderWindow& getWindow();

        [[nodiscard]] Graphics::Color getClearColor() const;
        void setClearColor(Graphics::Color color);
        void setMouseCursorVisible(bool visible);
    };
} // namespace obe::System