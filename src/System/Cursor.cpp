#include <SFML/Window/Mouse.hpp>

#include <Input/InputManager.hpp>
#include <System/Cursor.hpp>
#include <Transform/UnitVector.hpp>
#include <Triggers/TriggerDatabase.hpp>

namespace obe
{
    namespace System
    {
        namespace Constraints
        {
            std::function<std::pair<int, int>(Cursor*)> Default = [](Cursor* cursor)
            {
                return std::pair<int, int>(cursor->getRawX(), cursor->getRawY());
            };
        }

        Cursor::Cursor() :
            m_cursorTriggers(Triggers::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Cursor"))
        {
            m_constraint = Constraints::Default;

            m_cursorTriggers->addTrigger("CursorMoved");
            m_saveOldPos = sf::Mouse::getPosition();
        }

        int Cursor::getX() const
        {
            return m_constrainedX;
        }

        int Cursor::getY() const
        {
            return m_constrainedY;
        }

        int Cursor::getRawX() const
        {
            return m_x;
        }

        int Cursor::getRawY() const
        {
            return m_y;
        }

        void Cursor::setX(unsigned int newx)
        {
            m_x = newx;
            sf::Mouse::setPosition(sf::Vector2i(m_x, m_y));
        }

        void Cursor::setY(unsigned int newy)
        {
            m_y = newy;
            sf::Mouse::setPosition(sf::Vector2i(m_x, m_y));
        }

        void Cursor::setPosition(unsigned int newx, unsigned int newy)
        {
            m_x = newx;
            m_y = newy;
            sf::Mouse::setPosition(sf::Vector2i(m_x, m_y));
        }

        void Cursor::update()
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition();
            m_x = mousePos.x;
            m_y = mousePos.y;
            if (mousePos != m_saveOldPos)
            {
                m_cursorTriggers->pushParameter("CursorMoved", "x", m_x);
                m_cursorTriggers->pushParameter("CursorMoved", "y", m_y);
                m_cursorTriggers->pushParameter("CursorMoved", "oldX", m_saveOldPos.x);
                m_cursorTriggers->pushParameter("CursorMoved", "oldY", m_saveOldPos.y);
                m_cursorTriggers->trigger("CursorMoved");
                m_saveOldPos = mousePos;
            }
            std::pair<int, int> constrainedPosition = m_constraint(this);
            m_constrainedX = constrainedPosition.first;
            m_constrainedY = constrainedPosition.second;
        }

        void Cursor::setConstraint(std::function<std::pair<int, int>(Cursor*)> constraint)
        {
            m_constraint = constraint;
        }
    }
}
