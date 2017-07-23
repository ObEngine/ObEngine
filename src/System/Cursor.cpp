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
            m_cursorTriggers(Triggers::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Cursor")),
            m_cursorAnim(Path("Sprites/Cursors/Round"))
        {
            m_constraint = Constraints::Default;
            m_cursorAnim.loadAnimator();
            m_cursorAnim.setKey("IDLE");

            m_cursorTriggers->addTrigger("Pressed")
                            ->addTrigger("Hold")
                            ->addTrigger("Released")
                            ->addTrigger("Idle");

        }

        void Cursor::selectAnimatorPath(const std::string& cursor)
        {
            m_cursorAnim.clear();
            m_cursorAnim = Animation::Animator(Path("Sprites/Cursors/").add(cursor));
            m_cursorAnim.loadAnimator();
            m_cursorAnim.setKey("IDLE");
            m_cursorAnim.update();
            m_cursorSprite.setTexture(m_cursorAnim.getTexture());
        }

        void Cursor::selectAnimationKey(const std::string& key)
        {
            m_cursorAnim.setKey(key);
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
            /*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                m_cursorAnim.setKey("CLIC");
            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_leftHold)
                m_cursorAnim.setKey("RELEASE");
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !m_rightHold)
                m_cursorAnim.setKey("CLIC");
            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && m_rightHold)
                m_cursorAnim.setKey("RELEASE");
            if (!m_leftHold && !m_rightHold && m_cursorAnim.getKey() == "HOLD")
                m_cursorAnim.setKey("RELEASE");*/

            m_cursorAnim.update();

            if (m_cursorAnim.textureChanged())
            {
                m_cursorSprite.setTexture(m_cursorAnim.getTexture());
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition();
            m_x = mousePos.x;
            m_y = mousePos.y;
            std::pair<int, int> constrainedPosition = m_constraint(this);
            m_constrainedX = constrainedPosition.first;
            m_constrainedY = constrainedPosition.second;
            m_cursorSprite.setPosition(m_constrainedX, m_constrainedY);
        }

        void Cursor::setConstraint(std::function<std::pair<int, int>(Cursor*)> constraint)
        {
            m_constraint = constraint;
        }

        void Cursor::display(sf::RenderWindow& target) const
        {
            return target.draw(m_cursorSprite);
        }
    }
}
