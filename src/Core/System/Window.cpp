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

        unsigned int width = 1280;
        unsigned int height = 720;

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
                width = wconf->getDataNode("width").get<int>();
            else if (wconf->getDataNode("width").getDataType() == vili::DataType::String)
            {
                if (wconf->getDataNode("width").get<std::string>() == "Fill")
                    width = Transform::UnitVector::Screen.w;
            }
        }
        else
            width = Transform::UnitVector::Screen.w;
        if (wconf->contains("height"))
        {
            if (wconf->getDataNode("height").getDataType() == vili::DataType::Int)
                height = wconf->getDataNode("height").get<int>();
            else if (wconf->getDataNode("height").getDataType() == vili::DataType::String)
            {
                if (wconf->getDataNode("height").get<std::string>() == "Fill")
                {
                    height = Transform::UnitVector::Screen.h;
                }
            }
        }
        else
            height = Transform::UnitVector::Screen.h;

        int wStyle = sf::Style::None;
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
        if (context == WindowContext::EditorWindow && wconf->contains("docked"))
            m_docked = wconf->getDataNode("docked").get<bool>();

        if (fullscreen)
            wStyle = sf::Style::Fullscreen;
        else
        {
            if (closeable)
                wStyle |= sf::Style::Close;
            if (resizeable)
                wStyle |= sf::Style::Resize;
            if (titlebar)
                wStyle |= sf::Style::Titlebar;
        }

        std::string title = "ObEngine";
        if (wconf->contains("title"))
            title = wconf->getDataNode("title").get<std::string>();

        if (m_docked)
        {
            m_surface.create(1, 1);
        }
        else
        {
            m_window.create(sf::VideoMode(width, height), title, wStyle);
            m_window.setKeyRepeatEnabled(false);
        }
    }

    void Window::clear(const sf::Color& color)
    {
        if (!m_docked)
            m_window.clear(color);
        else
            m_surface.clear();
    }

    void Window::close()
    {
        if (!m_docked)
            m_window.close();
    }

    void Window::display()
    {
        if (!m_docked)
            m_window.display();
        else
            m_surface.display();
    }

    void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
    {
        if (!m_docked)
            m_window.draw(drawable, states);
        else
            m_surface.draw(drawable, states);
    }

    void Window::draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type,
        const sf::RenderStates& states)
    {
        if (!m_docked)
            m_window.draw(vertices, vertexCount, type, states);
        else
            m_surface.draw(vertices, vertexCount, type, states);
    }

    sf::Vector2u Window::getSize() const
    {
        if (!m_docked)
            return m_window.getSize();
        else
            return m_surface.getSize();
    }

    bool Window::isOpen() const
    {
        if (!m_docked)
            return m_window.isOpen();
        else
            return true;
    }

    bool Window::pollEvent(sf::Event& event)
    {
        if (!m_docked)
            return m_window.pollEvent(event);
        else
            return true;
    }

    void Window::setTitle(const std::string& title)
    {

        if (!m_docked)
            m_window.setTitle(title);
    }

    void Window::setVerticalSyncEnabled(bool enabled)
    {
        if (!m_docked)
            m_window.setVerticalSyncEnabled(enabled);
    }

    void Window::setView(const sf::View& view)
    {
        if (!m_docked)
            m_window.setView(view);
        else
            m_surface.setView(view);
    }

    sf::RenderTarget& Window::getTarget()
    {
        if (m_docked)
            return m_surface;
        else
            return m_window;
    }

    sf::RenderWindow& Window::getWindow()
    {
        return m_window;
    }

    sf::RenderTexture& Window::getTexture()
    {
        return m_surface;
    }

    void Window::setSize(const unsigned int width, const unsigned int height)
    {
        Transform::UnitVector::Screen.w = width;
        Transform::UnitVector::Screen.h = height;
        if (!m_docked)
            m_window.setSize(sf::Vector2u(width, height));
        else
            m_surface.create(width, height);
        this->setView(sf::View(sf::FloatRect(0, 0, width, height)));
    }
} // namespace obe::System