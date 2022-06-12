#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <System/Path.hpp>
#include <System/Window.hpp>

namespace obe::System
{
    void Window::applyView()
    {
        const float fWidth = static_cast<float>(m_width);
        const float fHeight = static_cast<float>(m_height);
        const float fRenderWidth = static_cast<float>(m_renderWidth);
        const float fRenderHeight = static_cast<float>(m_renderHeight);
        if (m_width != m_renderWidth || m_height != m_renderHeight)
        {
            if (m_stretch == StretchMode::None) { }
            else if (m_stretch == StretchMode::Center)
            {
                m_view.setSize(fRenderWidth, fRenderHeight);

                const float xOffset = ((fWidth - fRenderWidth) / 2) / fWidth;
                const float yOffset = ((fHeight - fRenderHeight) / 2) / fHeight;
                const float viewportWidth = fRenderWidth / fWidth;
                const float viewportHeight = fRenderHeight / fHeight;
                m_view.setViewport(sf::FloatRect(xOffset, yOffset, viewportWidth, viewportHeight));
                m_view.setCenter(m_renderWidth / 2, m_renderHeight / 2);
                m_window.setView(m_view);
            }
            else if (m_stretch == StretchMode::Stretch)
            {
                m_view.setSize(fRenderWidth, fRenderHeight);
                m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
                m_view.setCenter(fRenderWidth / 2.f, fRenderHeight / 2.f);
                m_window.setView(m_view);
            }
            else if (m_stretch == StretchMode::Fit)
            {
                float expectedWidth = (fHeight / fRenderHeight) * fRenderWidth;
                float expectedHeight;
                if (expectedWidth > fWidth)
                {
                    expectedWidth = 1;
                    expectedHeight = ((fRenderHeight / fRenderWidth) * fWidth) / fHeight;
                }
                else
                {
                    expectedWidth = ((fRenderWidth / fRenderHeight) * fHeight) / fWidth;
                    expectedHeight = 1;
                }
                const float xOffset = (1 - expectedWidth) / 2;
                const float yOffset = (1 - expectedHeight) / 2;

                m_view.setSize(fRenderWidth, fRenderHeight);
                m_view.setViewport(sf::FloatRect(xOffset, yOffset, expectedWidth, expectedHeight));
                m_view.setCenter(fRenderWidth / 2.f, fRenderHeight / 2.f);
                m_window.setView(m_view);
            }
        }
    }

    Window::Window(vili::node configuration)
    {
        const auto screenSize = sf::VideoMode::getDesktopMode();

        unsigned int windowWidth = 0;
        unsigned int windowHeight = 0;
        unsigned int renderWidth = 0;
        unsigned int renderHeight = 0;

        if (configuration.contains("width"))
        {
            if (configuration.at("width").is<vili::integer>())
                windowWidth = configuration.at("width");
            else if (configuration.at("width").is<vili::string>())
            {
                switch (WindowSizeMeta::fromString(configuration.at("width")))
                {
                case WindowSize::Screen:
                    windowWidth = screenSize.width;
                    break;
                }
            }
        }
        else
            windowWidth = screenSize.width;

        if (configuration.contains("height"))
        {
            if (configuration.at("height").is<vili::integer>())
                windowHeight = configuration.at("height");
            else if (configuration.at("height").is<vili::string>())
            {
                switch (WindowSizeMeta::fromString(configuration.at("height")))
                {
                case WindowSize::Screen:
                    windowHeight = screenSize.height;
                    break;
                }
            }
        }
        else
            windowHeight = screenSize.height;

        if (configuration.contains("render"))
        {
            const vili::node& render = configuration.at("render");

            if (render.contains("width"))
            {
                if (render.at("width").is<vili::integer>())
                    renderWidth = render.at("width");
                else if (render.at("width").is<vili::string>())
                {
                    switch (RenderSizeMeta::fromString(render.at("width")))
                    {
                    case RenderSize::Window:
                        renderWidth = windowWidth;
                        break;
                    case RenderSize::Screen:
                        renderWidth = screenSize.width;
                        break;
                    }
                }
            }
            else
                renderWidth = windowWidth;

            if (render.contains("height"))
            {
                if (render.at("height").is<vili::integer>())
                    renderHeight = render.at("height");
                else if (render.at("height").is<vili::string>())
                {
                    switch (RenderSizeMeta::fromString(render.at("height")))
                    {
                    case RenderSize::Window:
                        renderHeight = windowHeight;
                        break;
                    case RenderSize::Screen:
                        renderHeight = screenSize.height;
                        break;
                    }
                }
            }
            else
                renderHeight = windowHeight;

            if (render.contains("stretch"))
            {
                m_stretch = StretchModeMeta::fromString(render.at("stretch"));
            }
        }
        else
        {
            renderWidth = windowWidth;
            renderHeight = windowHeight;
        }

        this->setWindowSize(windowWidth, windowHeight);
        this->setRenderSize(renderWidth, renderHeight);

        bool fullscreen = true;
        bool closeable = true;
        bool resizeable = true;
        bool titlebar = true;

        if (configuration.contains("fullscreen"))
            fullscreen = configuration.at("fullscreen");
        if (configuration.contains("closeable"))
            closeable = configuration.at("closeable");
        if (configuration.contains("resizeable"))
            resizeable = configuration.at("resizeable");
        if (configuration.contains("titlebar"))
            titlebar = configuration.at("titlebar");

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
        if (configuration.contains("title"))
            m_title = configuration.at("title");
    }

    void Window::create()
    {
        Transform::UnitVector::Init(m_renderWidth, m_renderHeight);
        m_window.create(sf::VideoMode(m_width, m_height), m_title, m_style);
        m_window.setKeyRepeatEnabled(false);

        this->applyView();
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

    void Window::draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type,
        const sf::RenderStates& states)
    {
        m_window.draw(vertices, vertexCount, type, states);
    }

    Transform::UnitVector Window::getRenderSize() const
    {
        return Transform::UnitVector(m_renderWidth, m_renderHeight, Transform::Units::ScenePixels);
    }

    Transform::UnitVector Window::getWindowSize() const
    {
        const sf::Vector2u windowSize = m_window.getSize();
        return Transform::UnitVector(windowSize.x, windowSize.y, Transform::Units::ScenePixels);
    }

    Transform::UnitVector Window::getScreenSize() const
    {
        const auto screenSize = sf::VideoMode::getDesktopMode();
        return Transform::UnitVector(
            screenSize.width, screenSize.height, Transform::Units::ScenePixels);
    }

    Transform::UnitVector Window::getSize() const
    {
        return this->getRenderSize();
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

    void Window::setIcon(const std::string& path)
    {
        const std::string& realPath = System::Path(path).find();
        sf::Texture iconTexture;
        iconTexture.loadFromFile(realPath);
        m_icon = iconTexture.copyToImage();

        m_window.setIcon(32, 32, m_icon.getPixelsPtr());
    }

    graphics::RenderTarget Window::getTarget()
    {
        return m_window;
    }

    sf::RenderWindow& Window::getWindow()
    {
        return m_window;
    }

    graphics::Color Window::getClearColor() const
    {
        return m_background;
    }

    void Window::setClearColor(graphics::Color color)
    {
        m_background = std::move(color);
    }

    void Window::setMouseCursorVisible(bool visible)
    {
        m_window.setMouseCursorVisible(visible);
    }

    void Window::setSize(const unsigned int width, const unsigned int height)
    {
        this->setWindowSize(width, height);
        this->setRenderSize(width, height);
    }

    void Window::setWindowSize(unsigned width, unsigned height)
    {
        m_window.setSize(sf::Vector2u(width, height));
        this->setView(sf::View(sf::FloatRect(0, 0, width, height)));
        m_width = width;
        m_height = height;
        this->applyView();
    }

    void Window::setRenderSize(unsigned width, unsigned height)
    {
        Transform::UnitVector::Screen.w = width;
        Transform::UnitVector::Screen.h = height;
        m_renderWidth = width;
        m_renderHeight = height;
        this->applyView();
    }
} // namespace obe::System
