#include <SFML/Window/WindowStyle.hpp>
#include <vili/Vili.hpp>

#include <System/Path.hpp>
#include <System/Window.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::System
{
    void Window::init(const WindowContext context)
    {
        vili::ViliParser windowConfig;
        std::reverse(Path::MountedPaths.begin(), Path::MountedPaths.end());
        Path("Data/window.cfg.vili").loadAll(System::Loaders::dataLoader, windowConfig);
        std::reverse(Path::MountedPaths.begin(), Path::MountedPaths.end());

        vili::ComplexNode* wconf;
        if (context == WindowContext::GameWindow)
        {
            if (windowConfig->contains("Game"))
                wconf = &windowConfig.at("Game");
            else
                wconf = &windowConfig.root();
        }
        else if (context == WindowContext::EditorWindow)
        {
            if (windowConfig->contains("Editor"))
                wconf = &windowConfig.at("Editor");
            else
                wconf = &windowConfig.root();
        }
        else
        {
            throw aube::ErrorHandler::Raise("obe.System.Window.WrongContext");
        }

        if (wconf->contains("width"))
        {
            if (wconf->getDataNode("width").getDataType() == vili::DataType::Int)
                m_width = wconf->getDataNode("width").get<int>();
            else if (wconf->getDataNode("width").getDataType() == vili::DataType::String)
            {
                if (wconf->getDataNode("width").get<std::string>() == "Fill")
                    m_width = Transform::UnitVector::Screen.w;
            }
        }
        else
            m_width = Transform::UnitVector::Screen.w;
        if (wconf->contains("height"))
        {
            if (wconf->getDataNode("height").getDataType() == vili::DataType::Int)
                m_height = wconf->getDataNode("height").get<int>();
            else if (wconf->getDataNode("height").getDataType() == vili::DataType::String)
            {
                if (wconf->getDataNode("height").get<std::string>() == "Fill")
                {
                    m_height = Transform::UnitVector::Screen.h;
                }
            }
        }
        else
            m_height = Transform::UnitVector::Screen.h;

        bool fullscreen = true;
        bool closeable = true;
        bool resizeable = true;
        bool titlebar = true;

        if (wconf->contains("fullscreen"))
            fullscreen = wconf->getDataNode("fullscreen").get<bool>();
        if (wconf->contains("closeable"))
            closeable = wconf->getDataNode("closeable").get<bool>();
        if (wconf->contains("resizeable"))
            resizeable = wconf->getDataNode("resizeable").get<bool>();
        if (wconf->contains("titlebar"))
            titlebar = wconf->getDataNode("titlebar").get<bool>();

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
        if (wconf->contains("title"))
            m_title = wconf->getDataNode("title").get<std::string>();
    }

    void Window::create()
    {
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

    sf::Vector2u Window::getSize() const
    {
        return m_window.getSize();
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

    sf::RenderTarget& Window::getTarget()
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