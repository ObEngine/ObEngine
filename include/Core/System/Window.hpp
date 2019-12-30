#pragma once

#include <string>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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
        sf::RenderWindow m_window;
        sf::RenderTexture m_surface;
        bool m_docked = false;

    public:
        void init(const WindowContext context);
        void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));
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
        sf::RenderTexture& getTexture();
    };

    inline Window MainWindow;
} // namespace obe::System