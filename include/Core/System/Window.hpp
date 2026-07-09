#pragma once

#include <Graphics/Color.hpp>
#include <Graphics/RenderTarget.hpp>
#include <Event/EventManager.hpp>
#include <Event/EventGroup.hpp>
#include <Event/EventNamespace.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Transform/UnitVector.hpp>
#include <string>
#include <vili/node.hpp>

namespace obe::events
{
    namespace Window
    {
        struct Position
        {
            unsigned int x;
            unsigned int y;
        };

        struct Size
        {
            unsigned int width;
            unsigned int height;
        };

        struct Moved
        {
            static constexpr std::string_view id = "Moved";
            Position new_pos;
            Position previous_pos;
        };

        struct Resized
        {
            static constexpr std::string_view id = "Resized";
            Size new_size;
            Size previous_size;
        };

        struct Closed
        {
            static constexpr std::string_view id = "Closed";
            bool is_closed;
        };

        struct Minimized
        {
            static constexpr std::string_view id = "Minimized";
            bool is_minimized;
        };

        struct Maximized
        {
            static constexpr std::string_view id = "Maximized";
            bool is_maximized;
        };
    }
}

namespace obe::system
{
    enum class WindowContext
    {
        GameWindow,
        EditorWindow
    };

    enum class StretchMode
    {
        None,
        Center,
        Stretch,
        Fit,
    };

    using StretchModeMeta = types::SmartEnum<StretchMode>;

    enum class WindowSize
    {
        Screen
    };

    using WindowSizeMeta = types::SmartEnum<WindowSize>;

    enum class RenderSize
    {
        Window,
        Screen,
    };

    using RenderSizeMeta = types::SmartEnum<RenderSize>;

    class Window
    {
    private:
        unsigned int m_width = 1920;
        unsigned int m_height = 1080;
        unsigned int m_render_width = m_width;
        unsigned int m_render_height = m_height;
        StretchMode m_stretch = StretchMode::Fit;
        int m_style;
        std::string m_title;
        sf::RenderWindow m_window;
        sf::View m_view;
        sf::Image m_icon;
        graphics::Color m_background = graphics::Color(0, 0, 0);
        event::EventGroupPtr e_window;
        void apply_view();

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
        void draw(const sf::Vertex* vertices, std::size_t vertex_count, sf::PrimitiveType type,
            const sf::RenderStates& states = sf::RenderStates::Default);
        [[nodiscard]] transform::UnitVector get_render_size() const;
        [[nodiscard]] transform::UnitVector get_window_size() const;
        [[nodiscard]] static transform::UnitVector get_screen_size();
        [[nodiscard]] transform::UnitVector get_size() const;
        [[nodiscard]] bool is_open() const;
        [[nodiscard]] bool is_focused() const;
        bool poll_event(sf::Event& event);
        void set_size(unsigned int width, unsigned int height);
        void set_window_size(unsigned int width, unsigned int height);
        void set_render_size(unsigned int width, unsigned int height);
        void set_title(const std::string& title);
        void set_vertical_sync_enabled(bool enabled);
        void set_view(const sf::View& view);
        void set_icon(const std::string& path);

        graphics::RenderTarget get_target();
        sf::RenderWindow& get_window();

        [[nodiscard]] graphics::Color get_clear_color() const;
        void set_clear_color(graphics::Color color);
        void set_mouse_cursor_visible(bool visible);
    };
} // namespace obe::system
