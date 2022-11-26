#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <System/Path.hpp>
#include <System/Window.hpp>

namespace obe::system
{
    void Window::apply_view()
    {
        const float f_width = static_cast<float>(m_width);
        const float f_height = static_cast<float>(m_height);
        const float f_render_width = static_cast<float>(m_render_width);
        const float f_render_height = static_cast<float>(m_render_height);
        if (m_width != m_render_width || m_height != m_render_height)
        {
            if (m_stretch == StretchMode::None) { }
            else if (m_stretch == StretchMode::Center)
            {
                m_view.setSize(f_render_width, f_render_height);

                const float x_offset = ((f_width - f_render_width) / 2) / f_width;
                const float y_offset = ((f_height - f_render_height) / 2) / f_height;
                const float viewport_width = f_render_width / f_width;
                const float viewport_height = f_render_height / f_height;
                m_view.setViewport(
                    sf::FloatRect(x_offset, y_offset, viewport_width, viewport_height));
                m_view.setCenter(m_render_width / 2, m_render_height / 2);
                m_window.setView(m_view);
            }
            else if (m_stretch == StretchMode::Stretch)
            {
                m_view.setSize(f_render_width, f_render_height);
                m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
                m_view.setCenter(f_render_width / 2.f, f_render_height / 2.f);
                m_window.setView(m_view);
            }
            else if (m_stretch == StretchMode::Fit)
            {
                float expected_width = (f_height / f_render_height) * f_render_width;
                float expected_height;
                if (expected_width > f_width)
                {
                    expected_width = 1;
                    expected_height = ((f_render_height / f_render_width) * f_width) / f_height;
                }
                else
                {
                    expected_width = ((f_render_width / f_render_height) * f_height) / f_width;
                    expected_height = 1;
                }
                const float x_offset = (1 - expected_width) / 2;
                const float y_offset = (1 - expected_height) / 2;

                m_view.setSize(f_render_width, f_render_height);
                m_view.setViewport(
                    sf::FloatRect(x_offset, y_offset, expected_width, expected_height));
                m_view.setCenter(f_render_width / 2.f, f_render_height / 2.f);
                m_window.setView(m_view);
            }
        }
    }

    Window::Window(vili::node configuration)
    {
        const auto screen_size = sf::VideoMode::getDesktopMode();

        unsigned int window_width = 0;
        unsigned int window_height = 0;
        unsigned int render_width = 0;
        unsigned int render_height = 0;

        if (configuration.contains("width"))
        {
            if (configuration.at("width").is<vili::integer>())
                window_width = configuration.at("width");
            else if (configuration.at("width").is<vili::string>())
            {
                switch (WindowSizeMeta::from_string(configuration.at("width")))
                {
                case WindowSize::Screen:
                    window_width = screen_size.width;
                    break;
                }
            }
        }
        else
            window_width = screen_size.width;

        if (configuration.contains("height"))
        {
            if (configuration.at("height").is<vili::integer>())
                window_height = configuration.at("height");
            else if (configuration.at("height").is<vili::string>())
            {
                switch (WindowSizeMeta::from_string(configuration.at("height")))
                {
                case WindowSize::Screen:
                    window_height = screen_size.height;
                    break;
                }
            }
        }
        else
            window_height = screen_size.height;

        if (configuration.contains("render"))
        {
            const vili::node& render = configuration.at("render");

            if (render.contains("width"))
            {
                if (render.at("width").is<vili::integer>())
                    render_width = render.at("width");
                else if (render.at("width").is<vili::string>())
                {
                    switch (RenderSizeMeta::from_string(render.at("width")))
                    {
                    case RenderSize::Window:
                        render_width = window_width;
                        break;
                    case RenderSize::Screen:
                        render_width = screen_size.width;
                        break;
                    }
                }
            }
            else
                render_width = window_width;

            if (render.contains("height"))
            {
                if (render.at("height").is<vili::integer>())
                    render_height = render.at("height");
                else if (render.at("height").is<vili::string>())
                {
                    switch (RenderSizeMeta::from_string(render.at("height")))
                    {
                    case RenderSize::Window:
                        render_height = window_height;
                        break;
                    case RenderSize::Screen:
                        render_height = screen_size.height;
                        break;
                    }
                }
            }
            else
                render_height = window_height;

            if (render.contains("stretch"))
            {
                m_stretch = StretchModeMeta::from_string(render.at("stretch"));
            }
        }
        else
        {
            render_width = window_width;
            render_height = window_height;
        }

        this->set_window_size(window_width, window_height);
        this->set_render_size(render_width, render_height);

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
        transform::Vector2::init(m_render_width, m_render_height);
        m_window.create(sf::VideoMode(m_width, m_height), m_title, m_style);
        m_window.setKeyRepeatEnabled(false);

        this->apply_view();
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

    void Window::draw(const sf::Vertex* vertices, std::size_t vertex_count, sf::PrimitiveType type,
        const sf::RenderStates& states)
    {
        m_window.draw(vertices, vertex_count, type, states);
    }

    transform::Vector2 Window::get_render_size() const
    {
        return transform::Vector2(
            m_render_width, m_render_height, transform::Units::ScenePixels);
    }

    transform::Vector2 Window::get_window_size() const
    {
        const sf::Vector2u window_size = m_window.getSize();
        return transform::Vector2(window_size.x, window_size.y, transform::Units::ScenePixels);
    }

    transform::Vector2 Window::get_screen_size()
    {
        const auto screen_size = sf::VideoMode::getDesktopMode();
        return transform::Vector2(
            screen_size.width, screen_size.height, transform::Units::ScenePixels);
    }

    transform::Vector2 Window::get_size() const
    {
        return this->get_render_size();
    }

    bool Window::is_open() const
    {
        return m_window.isOpen();
    }

    bool Window::is_focused() const
    {
        return m_window.hasFocus();
    }

    bool Window::poll_event(sf::Event& event)
    {
        return m_window.pollEvent(event);
    }

    void Window::set_title(const std::string& title)
    {
        m_title = title;
        m_window.setTitle(title);
    }

    void Window::set_vertical_sync_enabled(bool enabled)
    {
        m_window.setVerticalSyncEnabled(enabled);
    }

    void Window::set_view(const sf::View& view)
    {
        m_window.setView(view);
    }

    void Window::set_icon(const std::string& path)
    {
        const std::string& real_path = system::Path(path).find();
        sf::Texture icon_texture;
        icon_texture.loadFromFile(real_path);
        m_icon = icon_texture.copyToImage();

        m_window.setIcon(32, 32, m_icon.getPixelsPtr());
    }

    graphics::RenderTarget Window::get_target()
    {
        return m_window;
    }

    sf::RenderWindow& Window::get_window()
    {
        return m_window;
    }

    graphics::Color Window::get_clear_color() const
    {
        return m_background;
    }

    void Window::set_clear_color(graphics::Color color)
    {
        m_background = std::move(color);
    }

    void Window::set_mouse_cursor_visible(bool visible)
    {
        m_window.setMouseCursorVisible(visible);
    }

    void Window::set_size(const unsigned int width, const unsigned int height)
    {
        this->set_window_size(width, height);
        this->set_render_size(width, height);
    }

    void Window::set_window_size(unsigned width, unsigned height)
    {
        m_window.setSize(sf::Vector2u(width, height));
        this->set_view(sf::View(sf::FloatRect(0, 0, width, height)));
        m_width = width;
        m_height = height;
        this->apply_view();
    }

    void Window::set_render_size(unsigned width, unsigned height)
    {
        transform::Vector2::Screen.w = width;
        transform::Vector2::Screen.h = height;
        m_render_width = width;
        m_render_height = height;
        this->apply_view();
    }
} // namespace obe::system
