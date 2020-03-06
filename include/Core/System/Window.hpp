#pragma once

#include <string>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <Graphics/Color.hpp>

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
        void init(const WindowContext context);
        void create();
        void clear();
        void close();
        void display();
        void draw(const sf::Drawable& drawable,
            const sf::RenderStates& states = sf::RenderStates::Default);
        void draw(const sf::Vertex* vertices, std::size_t vertexCount,
            sf::PrimitiveType type,
            const sf::RenderStates& states = sf::RenderStates::Default);
        sf::Vector2u getSize() const;
        bool isOpen() const;
        bool pollEvent(sf::Event& event);
        void setSize(unsigned int width, unsigned int height);
        void setTitle(const std::string& title);
        void setVerticalSyncEnabled(bool enabled);
        void setView(const sf::View& view);

        sf::RenderTarget& getTarget();
        sf::RenderWindow& getWindow();

        Graphics::Color getClearColor() const;
        void setClearColor(Graphics::Color color);
    };

    inline Window MainWindow;
} // namespace obe::System