#include <SFML/Window/Mouse.hpp>

#include <Input/InputManager.hpp>
#include <System/Cursor.hpp>
#include <System/Window.hpp>
#include <Transform/UnitVector.hpp>
#include <Triggers/TriggerDatabase.hpp>

namespace obe::System
{
    namespace Constraints
    {
        std::function<std::pair<int, int>(Cursor*)> Default
            = [](Cursor* cursor) { return std::pair<int, int>(cursor->getX(), cursor->getY()); };
    }

    std::string MouseButtonToString(const sf::Mouse::Button button)
    {
        if (button == sf::Mouse::Button::Left)
            return "left";
        if (button == sf::Mouse::Button::Middle)
            return "middle";
        if (button == sf::Mouse::Button::Right)
            return "right";
        throw aube::ErrorHandler::Raise("obe.System.Cursor.InvalidButtonEnumValue");
    }

    Cursor::Cursor()
        : Registrable("Cursor")
        , m_cursorTriggers(
              Triggers::TriggerDatabase::GetInstance().createTriggerGroup("Global", "Cursor"),
              Triggers::TriggerGroupPtrRemover)
    {
        m_constraint = Constraints::Default;
        m_constraintCondition = []() { return true; };

        m_buttonState[sf::Mouse::Button::Left]
            = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        m_buttonState[sf::Mouse::Button::Middle]
            = sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
        m_buttonState[sf::Mouse::Button::Right]
            = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);

        m_cursorTriggers->addTrigger("Move");
        m_cursorTriggers->addTrigger("Press");
        m_cursorTriggers->addTrigger("Release");
        m_cursorTriggers->addTrigger("Hold");

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

    void Cursor::setX(const unsigned int newx)
    {
        m_x = newx;
        sf::Mouse::setPosition(sf::Vector2i(m_x, m_y), System::MainWindow.getWindow());
    }

    void Cursor::setY(const unsigned int newy)
    {
        m_y = newy;
        sf::Mouse::setPosition(sf::Vector2i(m_x, m_y), System::MainWindow.getWindow());
    }

    void Cursor::setPosition(const unsigned int newx, const unsigned int newy)
    {
        m_x = newx;
        m_y = newy;
        sf::Mouse::setPosition(sf::Vector2i(m_x, m_y), System::MainWindow.getWindow());
    }

    void Cursor::show()
    {
        m_visible = true;
        // MainWindow.setMouseCursorVisible(true);
    }

    void Cursor::hide()
    {
        m_visible = false;
        // MainWindow.setMouseCursorVisible(false);
    }

    void Cursor::setVisible(const bool visible)
    {
        m_visible = visible;
        // MainWindow.setMouseCursorVisible(visible);
    }

    bool Cursor::isVisible() const
    {
        return m_visible;
    }

    Transform::UnitVector Cursor::getPosition() const
    {
        return Transform::UnitVector(m_constrainedX, m_constrainedY, Transform::Units::ScenePixels);
    }

    void Cursor::update()
    {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(MainWindow.getWindow());
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
                m_cursorTriggers->pushParameter("Hold", MouseButtonToString(state.first), true);
                m_cursorTriggers->pushParameter("Hold", "x", m_x);
                m_cursorTriggers->pushParameter("Hold", "y", m_y);
                hold = true;
            }
            if (sf::Mouse::isButtonPressed(state.first) && !state.second)
            {
                m_cursorTriggers->pushParameter("Press", MouseButtonToString(state.first), true);
                m_cursorTriggers->pushParameter("Press", "x", m_x);
                m_cursorTriggers->pushParameter("Press", "y", m_y);
                state.second = true;
                press = true;
            }
            if (!sf::Mouse::isButtonPressed(state.first) && state.second)
            {
                m_cursorTriggers->pushParameter("Release", MouseButtonToString(state.first), true);
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

    void Cursor::setConstraint(const std::function<std::pair<int, int>(Cursor*)> constraint,
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