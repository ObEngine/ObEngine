//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Collisions.hpp"

class Cursor
{
	private:
		int x;
		int y;
		bool leftclicked = false;
		bool rightclicked = false;
		bool leftfirstclic = false;
		bool rightfirstclic = false;
		bool leftReleased = false;
		bool rightReleased = false;
		anim::Animator cursorAnim;
		sf::Sprite* cursorSprite;
		int screenSizeX;
		int screenSizeY;
		Collision::PolygonalCollider* cursorCollider;
		
	public:
		void initialize(int screenSizeX, int screenSizeY);
		void selectCursor(std::string cursor);
		void selectKey(std::string key);
		int getX();
		int getY();
		void setX(int newx);
		void setY(int newy);
		void setPosition(int newx, int newy);
		void update();
		bool getPressed(std::string clic);
		bool getClicked(std::string clic);
		bool getReleased(std::string clic);
		Collision::PolygonalCollider* getCollider();
		sf::Sprite* getSprite();
};