#include <SFML/Window/Mouse.hpp>

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

        Cursor::Cursor(sf::RenderWindow* window) :
            m_cursorTriggers(Triggers::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Cursor")),
            m_cursorAnim(Path("Sprites/Cursors/Round"))
        {
            m_constraint = Constraints::Default;
            m_window = window;
            m_cursorAnim.loadAnimator();
            m_cursorAnim.setKey("IDLE");

            m_cursorTriggers->addTrigger("Clicked")
                            ->addTrigger("Pressed")
                            ->addTrigger("Released");
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
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_leftPressed)
            {
                m_leftPressed = true;
                m_leftClicked = true;
                m_leftReleased = false;
                m_cursorAnim.setKey("CLIC");
            }
            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_leftPressed)
            {
                m_leftPressed = false;
                m_leftClicked = false;
                m_leftReleased = true;
                m_cursorAnim.setKey("RELEASE");
            }
            else
            {
                m_leftClicked = false;
                m_leftReleased = false;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !m_rightPressed)
            {
                m_rightPressed = true;
                m_rightClicked = true;
                m_rightReleased = false;
                m_cursorAnim.setKey("CLIC");
            }
            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && m_rightPressed)
            {
                m_rightPressed = false;
                m_rightClicked = false;
                m_rightReleased = true;
                m_cursorAnim.setKey("RELEASE");
            }
            else
            {
                m_rightClicked = false;
                m_rightReleased = false;
            }
            if (!m_leftPressed && !m_rightPressed && m_cursorAnim.getKey() == "HOLD")
                m_cursorAnim.setKey("RELEASE");
            m_cursorAnim.update();
            if (m_cursorAnim.textureChanged())
            {
                m_cursorSprite.setTexture(m_cursorAnim.getTexture());
            }

            if (sf::Mouse::getPosition().x - m_window->getPosition().x > 0 && sf::Mouse::getPosition().y - m_window->getPosition().y > 0)
            {
                if (sf::Mouse::getPosition().x - m_window->getPosition().x < Transform::UnitVector::Screen.w)
                {
                    if (sf::Mouse::getPosition().y - m_window->getPosition().y < Transform::UnitVector::Screen.h)
                    {
                        m_x = sf::Mouse::getPosition().x - m_window->getPosition().x;
                        m_y = sf::Mouse::getPosition().y - m_window->getPosition().y;
                        if (m_x < 0) m_x = 0;
                        if (m_x > Transform::UnitVector::Screen.w) m_x = Transform::UnitVector::Screen.w;
                        if (m_y < 0) m_y = 0;
                        if (m_y > Transform::UnitVector::Screen.h) m_y = Transform::UnitVector::Screen.h;
                    }
                }
            }
            //x = (double)x * (Utils::Transform::resolution->w / (double)Utils::Transform::width);
            //y = (double)y * ((double)Utils::Transform::viewHeight / (double)Utils::Transform::height);
            std::pair<int, int> constrainedPosition = m_constraint(this);
            m_constrainedX = constrainedPosition.first;
            m_constrainedY = constrainedPosition.second;
            m_cursorSprite.setPosition(m_constrainedX, m_constrainedY);
        }

        void Cursor::handleTriggers() const
        {
            if (this->getClicked(MouseButton::Left))
            {
                m_cursorTriggers->pushParameter("Clicked", "Key", std::string("Left"));
                m_cursorTriggers->pushParameter("Clicked", "X", m_constrainedX);
                m_cursorTriggers->pushParameter("Clicked", "Y", m_constrainedY);
                m_cursorTriggers->trigger("Clicked");
            }
            if (this->getClicked(MouseButton::Right))
            {
                m_cursorTriggers->pushParameter("Clicked", "Key", std::string("Right"));
                m_cursorTriggers->pushParameter("Clicked", "X", m_constrainedX);
                m_cursorTriggers->pushParameter("Clicked", "Y", m_constrainedY);
                m_cursorTriggers->trigger("Clicked");
            }
            if (this->getPressed(MouseButton::Left))
            {
                m_cursorTriggers->pushParameter("Pressed", "Key", std::string("Left"));
                m_cursorTriggers->pushParameter("Pressed", "X", m_constrainedX);
                m_cursorTriggers->pushParameter("Pressed", "Y", m_constrainedY);
                m_cursorTriggers->trigger("Pressed");
            }
            if (this->getPressed(MouseButton::Right))
            {
                m_cursorTriggers->pushParameter("Pressed", "Key", std::string("Right"));
                m_cursorTriggers->pushParameter("Pressed", "X", m_constrainedX);
                m_cursorTriggers->pushParameter("Pressed", "Y", m_constrainedY);
                m_cursorTriggers->trigger("Pressed");
            }
            if (this->getReleased(MouseButton::Left))
            {
                m_cursorTriggers->pushParameter("Released", "Key", std::string("Left"));
                m_cursorTriggers->pushParameter("Released", "X", m_constrainedX);
                m_cursorTriggers->pushParameter("Released", "Y", m_constrainedY);
                m_cursorTriggers->trigger("Released");
            }
            if (this->getReleased(MouseButton::Right))
            {
                m_cursorTriggers->pushParameter("Released", "Key", std::string("Right"));
                m_cursorTriggers->pushParameter("Released", "X", m_constrainedX);
                m_cursorTriggers->pushParameter("Released", "Y", m_constrainedY);
                m_cursorTriggers->trigger("Released");
            }
        }

        bool Cursor::getPressed(MouseButton button) const
        {
            if (button == MouseButton::Left)
                return m_leftPressed;
            if (button == MouseButton::Right)
                return m_rightPressed;
            return false;
        }

        bool Cursor::getClicked(MouseButton button) const
        {
            if (button == MouseButton::Left)
                return m_leftClicked;
            if (button == MouseButton::Right)
                return m_rightClicked;
            return false;
        }

        bool Cursor::getReleased(MouseButton button) const
        {
            if (button == MouseButton::Left)
                return m_leftReleased;
            if (button == MouseButton::Right)
                return m_rightReleased;
            return false;
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
