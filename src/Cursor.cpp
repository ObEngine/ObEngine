#include "Cursor.hpp"

namespace obe
{
	namespace Cursor
	{
		Cursor::Cursor()
		{
		}

		Cursor::Cursor(sf::RenderWindow* window) : m_cursorAnim(System::Path("Sprites/Cursors/Round"))
		{
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
			return m_x;
		}

		int Cursor::getY() const
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
			m_cursorSprite->setPosition(m_x, m_y);
		}

		void Cursor::handleTriggers() const
		{
			//<Rewrite> Dumb code, could do way shorter
			if (this->getClicked("Left"))
			{
				m_cursorTriggers->pushParameter("Clicked", "Key", std::string("Left"));
				m_cursorTriggers->pushParameter("Clicked", "X", m_x);
				m_cursorTriggers->pushParameter("Clicked", "Y", m_y);
				m_cursorTriggers->enableTrigger("Clicked");
			}
			if (this->getClicked("Right"))
			{
				m_cursorTriggers->pushParameter("Clicked", "Key", std::string("Right"));
				m_cursorTriggers->pushParameter("Clicked", "X", m_x);
				m_cursorTriggers->pushParameter("Clicked", "Y", m_y);
				m_cursorTriggers->enableTrigger("Clicked");
			}
			if (this->getPressed("Left"))
			{
				m_cursorTriggers->pushParameter("Pressed", "Key", std::string("Left"));
				m_cursorTriggers->pushParameter("Pressed", "X", m_x);
				m_cursorTriggers->pushParameter("Pressed", "Y", m_y);
				m_cursorTriggers->enableTrigger("Pressed");
			}
			if (this->getPressed("Right"))
			{
				m_cursorTriggers->pushParameter("Pressed", "Key", std::string("Right"));
				m_cursorTriggers->pushParameter("Pressed", "X", m_x);
				m_cursorTriggers->pushParameter("Pressed", "Y", m_y);
				m_cursorTriggers->enableTrigger("Pressed");
			}
			if (this->getReleased("Left"))
			{
				m_cursorTriggers->pushParameter("Released", "Key", std::string("Left"));
				m_cursorTriggers->pushParameter("Released", "X", m_x);
				m_cursorTriggers->pushParameter("Released", "Y", m_y);
				m_cursorTriggers->enableTrigger("Released");
			}
			if (this->getReleased("Right"))
			{
				m_cursorTriggers->pushParameter("Released", "Key", std::string("Right"));
				m_cursorTriggers->pushParameter("Released", "X", m_x);
				m_cursorTriggers->pushParameter("Released", "Y", m_y);
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
			else if (clic == "Right")
				return m_rightclicked;
			else
				return false;
		}

		bool Cursor::getClicked(std::string clic) const
		{
			if (clic == "Left")
				return m_leftfirstclic;
			else if (clic == "Right")
				return m_rightfirstclic;
			else
				return false;
		}

		bool Cursor::getReleased(std::string clic) const
		{
			if (clic == "Left")
				return m_leftReleased;
			else if (clic == "Right")
				return m_rightReleased;
			else
				return false;
		}

		sf::Sprite* Cursor::getSprite() const
		{
			return m_cursorSprite;
		}
	}
}
