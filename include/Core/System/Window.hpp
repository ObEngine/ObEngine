#pragma once

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

#include <Graphics/Color.hpp>
#include <Graphics/RenderTarget.hpp>

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
        unsigned int m_width = 1280;
        unsigned int m_height = 720;
        int m_style;
        std::string m_title;
        sf::RenderWindow m_window;
        Graphics::Color m_background = Graphics::Color(0, 0, 0);

    public:
        Window(WindowContext context);
        void create();
        void clear();
        void close();
        void display();
        void draw(const sf::Drawable& drawable,
            const sf::RenderStates& states = sf::RenderStates::Default);
        void draw(const sf::Vertex* vertices, std::size_t vertexCount,
            sf::PrimitiveType type,
            const sf::RenderStates& states = sf::RenderStates::Default);
        [[nodiscard]] sf::Vector2u getSize() const;
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
    };
} // namespace obe::System