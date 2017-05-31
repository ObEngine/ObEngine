#include "Cursor.hpp"

namespace obe
{
    namespace Cursor
    {
        namespace Constraints
        {
            std::function<std::pair<int, int>(Cursor*)> Default = [](Cursor* cursor)
            {
                return std::pair<int, int>(cursor->getRawX(), cursor->getRawY());
            };
        }

        Cursor::Cursor()
        {
            m_constraint = Constraints::Default;
        }

        Cursor::Cursor(sf::RenderWindow* window) : m_cursorAnim(System::Path("Sprites/Cursors/Round"))
        {
            m_constraint = Constraints::Default;
            m_window = window;
            m_cursorAnim.loadAnimator();
            m_cursorAnim.setKey("IDLE");

            m_cursorTriggers = Script::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Cursor")
                                                                     ->addTrigger("Clicked")
                                                                     ->addTrigger("Pressed")
                                                                     ->addTrigger("Released");
        }

        Cursor::~Cursor()
        {
            Script::TriggerDatabase::GetInstance()->removeTriggerGroup(m_cursorTriggers);
        }

        void Cursor::selectCursor(std::string cursor)
        {
            m_cursorAnim.clear();
            m_cursorAnim = Animation::Animator(System::Path("Sprites/Cursors/").add(cursor).toString());
            m_cursorAnim.loadAnimator();
            m_cursorAnim.setKey("IDLE");
            m_cursorAnim.update();
            m_cursorSprite = m_cursorAnim.getSprite();
        }

        void Cursor::selectKey(std::string key)
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

        void Cursor::setX(int newx)
        {
            m_x = newx;
            sf::Mouse::setPosition(sf::Vector2i(m_x, m_y));
        }

        void Cursor::setY(int newy)
        {
            m_y = newy;
            sf::Mouse::setPosition(sf::Vector2i(m_x, m_y));
        }

        void Cursor::setPosition(int newx, int newy)
        {
            m_x = newx;
            m_y = newy;
            sf::Mouse::setPosition(sf::Vector2i(m_x, m_y));
        }

        void Cursor::update()
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_leftclicked)
            {
                m_leftclicked = true;
                m_leftfirstclic = true;
                m_leftReleased = false;
                m_cursorAnim.setKey("CLIC");
            }
            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_leftclicked)
            {
                m_leftclicked = false;
                m_leftfirstclic = false;
                m_leftReleased = true;
                m_cursorAnim.setKey("RELEASE");
            }
            else
            {
                m_leftfirstclic = false;
                m_leftReleased = false;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !m_rightclicked)
            {
                m_rightclicked = true;
                m_rightfirstclic = true;
                m_rightReleased = false;
                m_cursorAnim.setKey("CLIC");
            }
            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && m_rightclicked)
            {
                m_rightclicked = false;
                m_rightfirstclic = false;
                m_rightReleased = true;
                m_cursorAnim.setKey("RELEASE");
            }
            else
            {
                m_rightfirstclic = false;
                m_rightReleased = false;
            }
            if (!m_leftclicked && !m_rightclicked && m_cursorAnim.getKey() == "HOLD")
                m_cursorAnim.setKey("RELEASE");
            m_cursorAnim.update();
            if (m_cursorAnim.textureChanged())
            {
                m_cursorSprite = m_cursorAnim.getSprite();
            }
            if (m_doesUpdateOutsideWindow)
            {
                m_x = sf::Mouse::getPosition().x - m_window->getPosition().x;
                m_y = sf::Mouse::getPosition().y - m_window->getPosition().y;
                if (m_x < 0) m_x = 0;
                if (m_x > Coord::UnitVector::Screen.w) m_x = Coord::UnitVector::Screen.w;
                if (m_y < 0) m_y = 0;
                if (m_y > Coord::UnitVector::Screen.h) m_y = Coord::UnitVector::Screen.h;
            }
            else
            {
                if (sf::Mouse::getPosition().x - m_window->getPosition().x > 0 && sf::Mouse::getPosition().y - m_window->getPosition().y > 0)
                {
                    if (sf::Mouse::getPosition().x - m_window->getPosition().x < Coord::UnitVector::Screen.w)
                    {
                        if (sf::Mouse::getPosition().y - m_window->getPosition().y < Coord::UnitVector::Screen.h)
                        {
                            m_x = sf::Mouse::getPosition().x - m_window->getPosition().x;
                            m_y = sf::Mouse::getPosition().y - m_window->getPosition().y;
                            if (m_x < 0) m_x = 0;
                            if (m_x > Coord::UnitVector::Screen.w) m_x = Coord::UnitVector::Screen.w;
                            if (m_y < 0) m_y = 0;
                            if (m_y > Coord::UnitVector::Screen.h) m_y = Coord::UnitVector::Screen.h;
                        }
                    }
                }
            }
            //x = (double)x * (Functions::Coord::resolution->w / (double)Functions::Coord::width);
            //y = (double)y * ((double)Functions::Coord::viewHeight / (double)Functions::Coord::height);
            std::pair<int, int> constrainedPosition = m_constraint(this);
            m_constrainedX = constrainedPosition.first;
            m_constrainedY = constrainedPosition.second;
            m_cursorSprite->setPosition(m_constrainedX, m_constrainedY);
        }

        void Cursor::handleTriggers() const
        {
            //<Rewrite> Dumb code, could do way shorter
            if (this->getClicked("Left"))
            {
                m_cursorTriggers->pushParameter("Clicked", "Key", std::string("Left"));
                m_cursorTriggers->pushParameter("Clicked", "X", m_constrainedX);
                m_cursorTriggers->pushParameter("Clicked", "Y", m_constrainedY);
                m_cursorTriggers->enableTrigger("Clicked");
            }
            if (this->getClicked("Right"))
            {
                m_cursorTriggers->pushParameter("Clicked", "Key", std::string("Right"));
                m_cursorTriggers->pushParameter("Clicked", "X", m_constrainedX);
                m_cursorTriggers->pushParameter("Clicked", "Y", m_constrainedY);
                m_cursorTriggers->enableTrigger("Clicked");
            }
            if (this->getPressed("Left"))
            {
                m_cursorTriggers->pushParameter("Pressed", "Key", std::string("Left"));
                m_cursorTriggers->pushParameter("Pressed", "X", m_constrainedX);
                m_cursorTriggers->pushParameter("Pressed", "Y", m_constrainedY);
                m_cursorTriggers->enableTrigger("Pressed");
            }
            if (this->getPressed("Right"))
            {
                m_cursorTriggers->pushParameter("Pressed", "Key", std::string("Right"));
                m_cursorTriggers->pushParameter("Pressed", "X", m_constrainedX);
                m_cursorTriggers->pushParameter("Pressed", "Y", m_constrainedY);
                m_cursorTriggers->enableTrigger("Pressed");
            }
            if (this->getReleased("Left"))
            {
                m_cursorTriggers->pushParameter("Released", "Key", std::string("Left"));
                m_cursorTriggers->pushParameter("Released", "X", m_constrainedX);
                m_cursorTriggers->pushParameter("Released", "Y", m_constrainedY);
                m_cursorTriggers->enableTrigger("Released");
            }
            if (this->getReleased("Right"))
            {
                m_cursorTriggers->pushParameter("Released", "Key", std::string("Right"));
                m_cursorTriggers->pushParameter("Released", "X", m_constrainedX);
                m_cursorTriggers->pushParameter("Released", "Y", m_constrainedY);
                m_cursorTriggers->enableTrigger("Released");
            }
        }

        void Cursor::updateOutsideWindow(bool state)
        {
            m_doesUpdateOutsideWindow = state;
        }

        bool Cursor::getPressed(std::string clic) const
        {
            if (clic == "Left")
                return m_leftclicked;
            if (clic == "Right")
                return m_rightclicked;
            return false;
        }

        bool Cursor::getClicked(std::string clic) const
        {
            if (clic == "Left")
                return m_leftfirstclic;
            if (clic == "Right")
                return m_rightfirstclic;
            return false;
        }

        bool Cursor::getReleased(std::string clic) const
        {
            if (clic == "Left")
                return m_leftReleased;
            if (clic == "Right")
                return m_rightReleased;
            return false;
        }

        void Cursor::setConstraint(std::function<std::pair<int, int>(Cursor*)> constraint)
        {
            m_constraint = constraint;
        }

        sf::Sprite* Cursor::getSprite() const
        {
            return m_cursorSprite;
        }
    }
}
