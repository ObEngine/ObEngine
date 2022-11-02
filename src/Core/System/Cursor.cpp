#include <SFML/Window/Mouse.hpp>

#include <System/Cursor.hpp>
#include <utility>

namespace obe::system
{
    namespace constraints
    {
        std::function<std::pair<int, int>(Cursor*)> Default
            = [](Cursor* cursor) { return std::pair<int, int>(cursor->get_x(), cursor->get_y()); };
    }

    std::string MouseButtonToString(const sf::Mouse::Button button)
    {
        if (button == sf::Mouse::Button::Left)
            return "left";
        if (button == sf::Mouse::Button::Middle)
            return "middle";
        if (button == sf::Mouse::Button::Right)
            return "right";
        const int enum_value = static_cast<std::underlying_type_t<sf::Mouse::Button>>(button);
        throw exceptions::InvalidMouseButtonEnumValue(enum_value, EXC_INFO);
    }

    Cursor::Cursor(system::Window& window, event::EventNamespace& event_namespace)
        : m_window(window)
        , e_cursor(event_namespace.create_group("Cursor"))
        , m_constraint(constraints::Default)
    {
        m_constraint_condition = []() { return true; };

        m_button_state[sf::Mouse::Button::Left]
            = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        m_button_state[sf::Mouse::Button::Middle]
            = sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
        m_button_state[sf::Mouse::Button::Right]
            = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);

        e_cursor->add<events::Cursor::Move>();
        e_cursor->add<events::Cursor::Press>();
        e_cursor->add<events::Cursor::Release>();
        e_cursor->add<events::Cursor::Hold>();

        m_old_position = sf::Mouse::getPosition();
    }

    int Cursor::get_constrained_x() const
    {
        return m_constrained_x;
    }

    int Cursor::get_constrained_y() const
    {
        return m_constrained_y;
    }

    int Cursor::get_x() const
    {
        return m_x;
    }

    int Cursor::get_y() const
    {
        return m_y;
    }

    void Cursor::set_x(const int x)
    {
        m_x = x;
        sf::Mouse::setPosition(sf::Vector2i(m_x, m_y), m_window.get_window());
    }

    void Cursor::set_y(const int y)
    {
        m_y = y;
        sf::Mouse::setPosition(sf::Vector2i(m_x, m_y), m_window.get_window());
    }

    void Cursor::set_position(const int x, const int y)
    {
        m_x = x;
        m_y = y;
        sf::Mouse::setPosition(sf::Vector2i(m_x, m_y), m_window.get_window());
    }

    void Cursor::show()
    {
        m_visible = true;
        m_window.set_mouse_cursor_visible(true);
    }

    void Cursor::hide()
    {
        m_visible = false;
        m_window.set_mouse_cursor_visible(false);
    }

    void Cursor::set_visible(const bool visible)
    {
        m_visible = visible;
        m_window.set_mouse_cursor_visible(visible);
    }

    bool Cursor::is_visible() const
    {
        return m_visible;
    }

    transform::UnitVector Cursor::get_position() const
    {
        return transform::UnitVector(
            m_constrained_x, m_constrained_y, transform::Units::ScenePixels);
    }

    transform::UnitVector Cursor::get_scene_position() const
    {
        const sf::Vector2i pixel_pos(m_constrained_x, m_constrained_y);

        // TODO: Is it suitable behaviour ?
        const sf::Vector2f world_pos = m_window.get_window().mapPixelToCoords(pixel_pos);
        return transform::UnitVector(world_pos.x, world_pos.y, transform::Units::ScenePixels);
    }

    void Cursor::update()
    {
        if (!m_window.is_focused())
        {
            return;
        }
        const sf::Vector2i mouse_pos = sf::Mouse::getPosition(m_window.get_window());
        m_x = mouse_pos.x;
        m_y = mouse_pos.y;
        if (mouse_pos != m_old_position)
        {
            e_cursor->trigger(
                events::Cursor::Move { m_x, m_y, m_old_position.x, m_old_position.y });
            m_old_position = mouse_pos;
        }
        std::pair<int, int> constrained_position;
        if (m_constraint_condition())
            constrained_position = m_constraint(this);
        else
            constrained_position = std::make_pair(m_x, m_y);
        m_constrained_x = constrained_position.first;
        m_constrained_y = constrained_position.second;

        for (auto& state : m_button_state)
        {
            if (sf::Mouse::isButtonPressed(state.first) && state.second)
            {
                e_cursor->trigger(
                    events::Cursor::Hold { m_x, m_y, state.first == sf::Mouse::Button::Left,
                        state.first == sf::Mouse::Button::Middle,
                        state.first == sf::Mouse::Button::Right });
            }
            if (sf::Mouse::isButtonPressed(state.first) && !state.second)
            {
                e_cursor->trigger(
                    events::Cursor::Press { m_x, m_y, state.first == sf::Mouse::Button::Left,
                        state.first == sf::Mouse::Button::Middle,
                        state.first == sf::Mouse::Button::Right });
                state.second = true;
            }
            if (!sf::Mouse::isButtonPressed(state.first) && state.second)
            {
                e_cursor->trigger(
                    events::Cursor::Release { m_x, m_y, state.first == sf::Mouse::Button::Left,
                        state.first == sf::Mouse::Button::Middle,
                        state.first == sf::Mouse::Button::Right });
                state.second = false;
            }
            m_button_state[state.first] = sf::Mouse::isButtonPressed(state.first);
        }
    }

    void Cursor::set_constraint(const std::function<std::pair<int, int>(Cursor*)>& constraint,
        std::function<bool()> condition)
    {
        m_constraint = constraint;
        m_constraint_condition = std::move(condition);
    }

    bool Cursor::is_pressed(sf::Mouse::Button button) const
    {
        return m_button_state.at(button);
    }

    void Cursor::set_cursor(const system::CursorModel& new_cursor)
    {
        m_custom_cursor = new_cursor.get_ptr();
        m_window.get_window().setMouseCursor(*m_custom_cursor);
    }

    bool CursorModel::load_from_file(
        const std::string& filename, unsigned int hotspot_x, unsigned int hotspot_y)
    {
        sf::Image img;
        if (img.loadFromFile(system::Path(filename).find()))
        {
            std::shared_ptr<sf::Cursor> new_cursor = std::make_shared<sf::Cursor>();
            if (new_cursor->loadFromPixels(
                    img.getPixelsPtr(), img.getSize(), sf::Vector2u(hotspot_x, hotspot_y)))
            {
                m_cursor.swap(new_cursor);
                return true;
            }
        }
        return false;
    }

    bool CursorModel::load_from_system(CursorType type)
    {
        std::shared_ptr<sf::Cursor> new_cursor = std::make_shared<sf::Cursor>();
        if (new_cursor->loadFromSystem(static_cast<sf::Cursor::Type>(type)))
        {
            m_cursor.swap(new_cursor);
            return true;
        }
        return false;
    }

    std::shared_ptr<sf::Cursor> CursorModel::get_ptr() const
    {
        return m_cursor;
    }
} // namespace obe::system
