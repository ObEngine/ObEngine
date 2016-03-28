#pragma once

#include <SFML/Graphics.hpp>

#include "Functions.hpp"
#include "SpriteFunc.hpp"
#include "Cursor.hpp"

class EditorGrid
{
	private:
		int gridSizeX;
		int gridSizeY;
		int gridOffX = 0;
		int gridOffY = 0;
		int gridCamOffX = 0;
		int gridCamOffY = 0;
		int gridCursorX = 0;
		int gridCursorY = 0;
		bool fixedGrid = false;
		int gridMagnetX = -1;
		int gridMagnetY = -1;
		sf::RenderTexture gridCreate;
		sf::Texture gridCache;
		sf::Sprite gridCacheSpr;
		void drawLine(sf::RenderWindow* surf, int x1, int y1, int x2, int y2, int w, sf::Color col);
	public:
		EditorGrid(int sizeX, int sizeY, int offsetX = 0, int offsetY = 0);
		void sendCursorPosition(int x, int y);
		void setSizeX(int sizeX);
		void setSizeY(int sizeY);
		void setOffsetX(int offsetX);
		void setOffsetY(int offsetY);
		void setCamOffsetX(int camOffsetX);
		void setCamOffsetY(int camOffsetY);
		void setFixedCam(bool fixed);
		int getSizeX();
		int getSizeY();
		int getOffsetX();
		int getOffsetY();
		void magnetize(Cursor* cur);
		void moveMagnet(Cursor* cur, int tox, int toy);
		void draw(sf::RenderWindow* surf);
};