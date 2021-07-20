#include <SFML/Window/Mouse.hpp>

#include <Input/InputManager.hpp>
#include <System/Cursor.hpp>
#include <System/Window.hpp>
#include <Transform/UnitVector.hpp>

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

    Cursor::Cursor(System::Window& window, Event::EventNamespace& eventNamespace)
        : m_window(window)
        , e_cursor(eventNamespace.createGroup("Cursor"))
    {
        m_constraint = Constraints::Default;
        m_constraintCondition = []() { return true; };

        m_buttonState[sf::Mouse::Button::Left]
            = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        m_buttonState[sf::Mouse::Button::Middle]
            = sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
        m_buttonState[sf::Mouse::Button::Right]
            = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);

        e_cursor->add<Events::Cursor::Move>();
        e_cursor->add<Events::Cursor::Press>();
        e_cursor->add<Events::Cursor::Release>();
        e_cursor->add<Events::Cursor::Hold>();

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

    Transform::UnitVector Cursor::getScenePosition() const
    {
        const sf::Vector2i pixelPos(m_constrainedX, m_constrainedY);

        // TODO: Is it suitable behaviour ?
        const sf::Vector2f worldPos = m_window.getWindow().mapPixelToCoords(pixelPos);
        return Transform::UnitVector(
            worldPos.x, worldPos.y, Transform::Units::ScenePixels);
    }

    void Cursor::update()
    {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(m_window.getWindow());
        m_x = mousePos.x;
        m_y = mousePos.y;
        if (mousePos != m_saveOldPos)
        {
            e_cursor->trigger(
                Events::Cursor::Move { m_x, m_y, m_saveOldPos.x, m_saveOldPos.y });
            m_saveOldPos = mousePos;
        }
        std::pair<int, int> constrainedPosition;
        if (m_constraintCondition())
            constrainedPosition = m_constraint(this);
        else
            constrainedPosition = std::make_pair(m_x, m_y);
        m_constrainedX = constrainedPosition.first;
        m_constrainedY = constrainedPosition.second;

        for (auto& state : m_buttonState)
        {
            if (sf::Mouse::isButtonPressed(state.first) && state.second)
            {
                e_cursor->trigger(Events::Cursor::Hold { m_x, m_y,
                    state.first == sf::Mouse::Button::Left,
                    state.first == sf::Mouse::Button::Middle,
                    state.first == sf::Mouse::Button::Right });
            }
            if (sf::Mouse::isButtonPressed(state.first) && !state.second)
            {
                e_cursor->trigger(Events::Cursor::Press { m_x, m_y,
                    state.first == sf::Mouse::Button::Left,
                    state.first == sf::Mouse::Button::Middle,
                    state.first == sf::Mouse::Button::Right });
                state.second = true;
            }
            if (!sf::Mouse::isButtonPressed(state.first) && state.second)
            {
                e_cursor->trigger(Events::Cursor::Release { m_x, m_y,
                    state.first == sf::Mouse::Button::Left,
                    state.first == sf::Mouse::Button::Middle,
                    state.first == sf::Mouse::Button::Right });
                state.second = false;
            }
            m_buttonState[state.first] = sf::Mouse::isButtonPressed(state.first);
        }
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

    void Cursor::setCursor(System::CursorModel& newCursor)
    {
        m_customCursor
            = newCursor.getPtr();
        m_window.getWindow().setMouseCursor(*m_customCursor);
    }

    bool CursorModel::loadFromFile(
        const std::string& filename, unsigned int hotspotX, unsigned int hotspotY)
    {
        sf::Image img;
        if (img.loadFromFile(System::Path(filename).find()))
        {
            sf::Cursor* newCursor
                = new sf::Cursor();
            if (newCursor->loadFromPixels(
                img.getPixelsPtr(), img.getSize(), sf::Vector2u(hotspotX, hotspotY)))
            {
                m_cursor.reset(newCursor);
                return true;
            }
            else
            {
                delete newCursor;
            }
        }
        return false;
    }

    std::shared_ptr<sf::Cursor> CursorModel::getPtr() const
    {
        return m_cursor;
    }
} // namespace obe::System