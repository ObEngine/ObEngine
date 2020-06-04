#include <SFML/Window/WindowStyle.hpp>

#include <System/Path.hpp>
#include <System/Window.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::System
{
    Window::Window(const WindowContext context)
    {
        vili::node windowConfig = vili::object {};
        auto mountPoints = System::MountablePath::Paths();
        std::reverse(mountPoints.begin(), mountPoints.end());
        Path(mountPoints)
            .set("Data/window.cfg.vili")
            .loadAll(System::Loaders::dataLoader, windowConfig);

        vili::node conf;
        if (context == WindowContext::GameWindow)
        {
            if (windowConfig.contains("Game"))
                conf = windowConfig.at("Game");
            else
                conf = windowConfig;
        }
        else if (context == WindowContext::EditorWindow)
        {
            if (windowConfig.contains("Editor"))
                conf = windowConfig.at("Editor");
            else
                conf = windowConfig;
        }

        if (conf.contains("width"))
        {
            if (conf.at("width").is<vili::integer>())
                m_width = conf.at("width");
            else if (conf.at("width").is<vili::string>())
            {
                if (conf.at("width").as<vili::string>() == "Fill")
                    m_width = Transform::UnitVector::Screen.w;
            }
        }
        else
            m_width = Transform::UnitVector::Screen.w;

        if (conf.contains("height"))
        {
            if (conf.at("height").is<vili::integer>())
                m_height = conf.at("height");
            else if (conf.at("height").is<vili::string>())
            {
                if (conf.at("height").as<vili::string>() == "Fill")
                    m_height = Transform::UnitVector::Screen.h;
            }
        }
        else
            m_height = Transform::UnitVector::Screen.h;

        bool fullscreen = true;
        bool closeable = true;
        bool resizeable = true;
        bool titlebar = true;

        if (conf.contains("fullscreen"))
            fullscreen = conf.at("fullscreen");
        if (conf.contains("closeable"))
            closeable = conf.at("closeable");
        if (conf.contains("resizeable"))
            resizeable = conf.at("resizeable");
        if (conf.contains("titlebar"))
            titlebar = conf.at("titlebar");

        m_style = sf::Style::Default;
        if (fullscreen)
            m_style = sf::Style::Fullscreen;
        else
        {
            if (closeable)
                m_style |= sf::Style::Close;
            if (resizeable)
                m_style |= sf::Style::Resize;
            if (titlebar)
                m_style |= sf::Style::Titlebar;
        }

        std::string title = "ObEngine";
        if (conf.contains("title"))
            m_title = conf.at("title");
    }

    void Window::create()
    {
        Transform::UnitVector::Init(m_width, m_height);
        m_window.create(sf::VideoMode(m_width, m_height), m_title, m_style);
        m_window.setKeyRepeatEnabled(false);
    }

    void Window::clear()
    {
        m_window.clear(m_background);
    }

    void Window::close()
    {
        m_window.close();
    }

    void Window::display()
    {
        m_window.display();
    }

    void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
    {
        m_window.draw(drawable, states);
    }

    void Window::draw(const sf::Vertex* vertices, std::size_t vertexCount,
        sf::PrimitiveType type, const sf::RenderStates& states)
    {
        m_window.draw(vertices, vertexCount, type, states);
    }

    Transform::UnitVector Window::getSize() const
    {
        const sf::Vector2u windowSize = m_window.getSize();
        return Transform::UnitVector(
            windowSize.x, windowSize.y, Transform::Units::ScenePixels);
    }

    bool Window::isOpen() const
    {
        return m_window.isOpen();
    }

    bool Window::pollEvent(sf::Event& event)
    {
        return m_window.pollEvent(event);
    }

    void Window::setTitle(const std::string& title)
    {
        m_title = title;
        m_window.setTitle(title);
    }

    void Window::setVerticalSyncEnabled(bool enabled)
    {
        m_window.setVerticalSyncEnabled(enabled);
    }

    void Window::setView(const sf::View& view)
    {
        m_window.setView(view);
    }

    Graphics::RenderTarget Window::getTarget()
    {
        return m_window;
    }

    sf::RenderWindow& Window::getWindow()
    {
        return m_window;
    }

    Graphics::Color Window::getClearColor() const
    {
        return m_background;
    }

    void Window::setClearColor(Graphics::Color color)
    {
        m_background = std::move(color);
    }

    void Window::setMouseCursorVisible(bool visible)
    {
        m_window.setMouseCursorVisible(visible);
    }

    void Window::setSize(const unsigned int width, const unsigned int height)
    {
        Transform::UnitVector::Screen.w = width;
        Transform::UnitVector::Screen.h = height;
        m_width = width;
        m_height = height;
        m_window.setSize(sf::Vector2u(width, height));
        this->setView(sf::View(sf::FloatRect(0, 0, width, height)));
    }
} // namespace obe::System