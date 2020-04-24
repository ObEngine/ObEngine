#include <SFML/Window/Mouse.hpp>

#include <Input/InputManager.hpp>
#include <System/Cursor.hpp>
#include <System/Window.hpp>
#include <Transform/UnitVector.hpp>
#include <Triggers/TriggerManager.hpp>

namespace obe::System
{
    namespace Constraints
    {
        std::function<std::pair<int, int>(Cursor*)> Default = [](Cursor* cursor) {
            return std::pair<int, int>(cursor->getX(), cursor->getY());
        };
    }

    std::string MouseButtonToString(const sf::Mouse::Button button)
    {
        if (button == sf::Mouse::Button::Left)
            return "left";
        if (button == sf::Mouse::Button::Middle)
            return "middle";
        if (button == sf::Mouse::Button::Right)
            return "right";
        const int enumValue
            = static_cast<std::underlying_type_t<sf::Mouse::Button>>(button);
        throw Exceptions::InvalidMouseButtonEnumValue(enumValue, EXC_INFO);
    }

    Cursor::Cursor(System::Window& window, Triggers::TriggerManager& triggers)
        : m_window(window)
        , m_cursorTriggers(triggers.createTriggerGroup("Event", "Cursor"))
    {
        m_constraint = Constraints::Default;
        m_constraintCondition = []() { return true; };

        m_buttonState[sf::Mouse::Button::Left]
            = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        m_buttonState[sf::Mouse::Button::Middle]
            = sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
        m_buttonState[sf::Mouse::Button::Right]
            = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);

        m_cursorTriggers->add("Move");
        m_cursorTriggers->add("Press");
        m_cursorTriggers->add("Release");
        m_cursorTriggers->add("Hold");

        m_saveOldPos = sf::Mouse::getPosition();
    }

    int Cursor::getConstrainedX() const
    {
        return m_constrainedX;
    }

    int Cursor::getConstrainedY() const
    {
        return m_constrainedY;
    }

    int Cursor::getX() const
    {
        return m_x;
    }

    int Cursor::getY() const
    {
        return m_y;
    }

    void Cursor::setX(const int x)
    {
        m_x = x;
        sf::Mouse::setPosition(sf::Vector2i(m_x, m_y), m_window.getWindow());
    }

    void Cursor::setY(const int y)
    {
        m_y = y;
        sf::Mouse::setPosition(sf::Vector2i(m_x, m_y), m_window.getWindow());
    }

    void Cursor::setPosition(const int x, const int y)
    {
        m_x = x;
        m_y = y;
        sf::Mouse::setPosition(sf::Vector2i(m_x, m_y), m_window.getWindow());
    }

    void Cursor::show()
    {
        m_visible = true;
        m_window.setMouseCursorVisible(true);
    }

    void Cursor::hide()
    {
        m_visible = false;
        m_window.setMouseCursorVisible(false);
    }

    void Cursor::setVisible(const bool visible)
    {
        m_visible = visible;
        m_window.setMouseCursorVisible(visible);
    }

    bool Cursor::isVisible() const
    {
        return m_visible;
    }

    Transform::UnitVector Cursor::getPosition() const
    {
        return Transform::UnitVector(
            m_constrainedX, m_constrainedY, Transform::Units::ScenePixels);
    }

    void Cursor::update()
    {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(m_window.getWindow());
        m_x = mousePos.x;
        m_y = mousePos.y;
        if (mousePos != m_saveOldPos)
        {
            m_cursorTriggers->pushParameter("Move", "x", m_x);
            m_cursorTriggers->pushParameter("Move", "y", m_y);
            m_cursorTriggers->pushParameter("Move", "oldX", m_saveOldPos.x);
            m_cursorTriggers->pushParameter("Move", "oldY", m_saveOldPos.y);
            m_cursorTriggers->trigger("Move");
            m_saveOldPos = mousePos;
        }
        std::pair<int, int> constrainedPosition;
        if (m_constraintCondition())
            constrainedPosition = m_constraint(this);
        else
            constrainedPosition = std::make_pair(m_x, m_y);
        m_constrainedX = constrainedPosition.first;
        m_constrainedY = constrainedPosition.second;

        bool hold = false;
        bool press = false;
        bool release = false;

        for (auto& state : m_buttonState)
        {
            if (sf::Mouse::isButtonPressed(state.first) && state.second)
            {
                m_cursorTriggers->pushParameter(
                    "Hold", MouseButtonToString(state.first), true);
                m_cursorTriggers->pushParameter("Hold", "x", m_x);
                m_cursorTriggers->pushParameter("Hold", "y", m_y);
                hold = true;
            }
            if (sf::Mouse::isButtonPressed(state.first) && !state.second)
            {
                m_cursorTriggers->pushParameter(
                    "Press", MouseButtonToString(state.first), true);
                m_cursorTriggers->pushParameter("Press", "x", m_x);
                m_cursorTriggers->pushParameter("Press", "y", m_y);
                state.second = true;
                press = true;
            }
            if (!sf::Mouse::isButtonPressed(state.first) && state.second)
            {
                m_cursorTriggers->pushParameter(
                    "Release", MouseButtonToString(state.first), true);
                m_cursorTriggers->pushParameter("Release", "x", m_x);
                m_cursorTriggers->pushParameter("Release", "y", m_y);
                state.second = false;
                release = true;
            }
            m_buttonState[state.first] = sf::Mouse::isButtonPressed(state.first);
        }

        if (hold)
            m_cursorTriggers->trigger("Hold");
        if (press)
            m_cursorTriggers->trigger("Press");
        if (release)
            m_cursorTriggers->trigger("Release");
    }

    void Cursor::setConstraint(
        const std::function<std::pair<int, int>(Cursor*)> constraint,
        std::function<bool()> condition)
    {
        m_constraint = constraint;
        m_constraintCondition = condition;
    }

    bool Cursor::isPressed(sf::Mouse::Button button)
    {
        return m_buttonState[button];
    }
} // namespace obe::System