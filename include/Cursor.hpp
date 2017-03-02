#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Functions.hpp"
#include "Triggers.hpp"

namespace obe
{
	namespace Cursor
	{
		class Cursor
		{
			private:
				Cursor();
				int x;
				int y;
				sf::RenderWindow* window;
				bool leftclicked = false;
				bool rightclicked = false;
				bool leftfirstclic = false;
				bool rightfirstclic = false;
				bool leftReleased = false;
				bool rightReleased = false;
				bool doesUpdateOutsideWindow = false;
				Script::TriggerGroup* cursorTriggers;
				Animation::Animator cursorAnim;
				sf::Sprite* cursorSprite;
				friend class CoreHook;

			public:
				Cursor(sf::RenderWindow* window);
				~Cursor();
				void selectCursor(std::string cursor);
				void selectKey(std::string key);
				int getX();
				int getY();
				void setX(int newx);
				void setY(int newy);
				void setPosition(int newx, int newy);
				void update();
				void handleTriggers();
				void updateOutsideWindow(bool state);
				bool getPressed(std::string clic);
				bool getClicked(std::string clic);
				bool getReleased(std::string clic);
				sf::Sprite* getSprite();
		};
	}
}