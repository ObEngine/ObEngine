#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Triggers.hpp"

namespace obe
{
	namespace Cursor
	{
		class Cursor
		{
			private:
				Cursor();
				int m_x = 0;
				int m_y = 0;
				sf::RenderWindow* m_window = nullptr;
				bool m_leftclicked = false;
				bool m_rightclicked = false;
				bool m_leftfirstclic = false;
				bool m_rightfirstclic = false;
				bool m_leftReleased = false;
				bool m_rightReleased = false;
				bool m_doesUpdateOutsideWindow = false;
				Script::TriggerGroup* m_cursorTriggers = nullptr;
				Animation::Animator m_cursorAnim;
				sf::Sprite* m_cursorSprite = nullptr;
				friend class CoreHook;

			public:
				Cursor(sf::RenderWindow* window);
				~Cursor();
				void selectCursor(std::string cursor);
				void selectKey(std::string key);
				int getX() const;
				int getY() const;
				void setX(int newx);
				void setY(int newy);
				void setPosition(int newx, int newy);
				void update();
				void handleTriggers() const;
				void updateOutsideWindow(bool state);
				bool getPressed(std::string clic) const;
				bool getClicked(std::string clic) const;
				bool getReleased(std::string clic) const;
				sf::Sprite* getSprite() const;
		};
	}
}