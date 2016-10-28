//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "EditorGrid.hpp"

namespace mse
{
	namespace Editor
	{
		void EditorGrid::drawLine(sf::RenderWindow* surf, int x1, int y1, int x2, int y2, int w, sf::Color col)
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(x1, y1), col),
				sf::Vertex(sf::Vector2f(x2, y2), col)
			};
			surf->draw(line, w, sf::Lines);
		}

		EditorGrid::EditorGrid(int sizeX, int sizeY, int offsetX, int offsetY)
		{
			gridSizeX = sizeX;
			gridSizeY = sizeY;
			gridOffX = offsetX;
			gridOffY = offsetY;
		}

		void EditorGrid::sendCursorPosition(int cux, int cuy)
		{
			this->gridCursorX = cux;
			this->gridCursorY = cuy;
		}

		void EditorGrid::setSizeX(int sizeX)
		{
			bool needToRender = sizeX != gridSizeX;
			gridSizeX = sizeX;
		}

		void EditorGrid::setSizeY(int sizeY)
		{
			bool needToRender = sizeY != gridSizeY;
			gridSizeY = sizeY;
		}

		void EditorGrid::setSize(int sizeX, int sizeY)
		{
			this->setSizeX(sizeX); this->setSizeY(sizeY);
		}

		void EditorGrid::setOffsetX(int offsetX)
		{
			bool needToRender = offsetX != gridOffX;
			this->gridOffX = offsetX % this->gridSizeX;
		}

		void EditorGrid::setOffsetY(int offsetY)
		{
			bool needToRender = offsetY != gridOffY;
			this->gridOffY = offsetY % this->gridSizeY;
		}

		void EditorGrid::setOffset(int offsetX, int offsetY)
		{
			this->setOffsetX(offsetX); this->setOffsetY(offsetY);
		}

		void EditorGrid::setCamOffsetX(int camOffsetX)
		{
			gridCamOffX = camOffsetX;
		}

		void EditorGrid::setCamOffsetY(int camOffsetY)
		{
			gridCamOffY = camOffsetY;
		}

		void EditorGrid::setFixedCam(bool fixed)
		{
			fixedGrid = fixed;
		}

		int EditorGrid::getSizeX()
		{
			return gridSizeX;
		}

		int EditorGrid::getSizeY()
		{
			return gridSizeY;
		}

		int EditorGrid::getOffsetX()
		{
			return gridOffX;
		}

		int EditorGrid::getOffsetY()
		{
			return gridOffY;
		}

		void EditorGrid::magnetize(Cursor::Cursor* cur)
		{
			if (gridMagnetX != -1 && gridMagnetY != -1)
			{
				cur->setPosition(gridMagnetX, gridMagnetY);
			}
		}

		void EditorGrid::moveMagnet(Cursor::Cursor* cur, int tox, int toy)
		{
			if (gridMagnetX != -1 && gridMagnetY != -1)
			{
				if (tox != 0) gridMagnetX += (gridSizeX * tox);
				if (toy != 0) gridMagnetY += (gridSizeY * toy);
				cur->setPosition(gridMagnetX, gridMagnetY);
			}
		}

		void EditorGrid::draw(sf::RenderWindow* surf)
		{
			int stackX = -1;
			int stackY = -1;
			for (int i = gridOffX + gridCamOffX; i < Functions::Coord::width; i += gridSizeX)
			{
				if (Functions::Math::isBetween(i, gridCursorX - ((int)std::floor(gridSizeX / 2) - 1), gridCursorX + ((int)std::floor(gridSizeX / 2) - 1)))
				{
					drawLine(surf, i, 0, i, Functions::Coord::height, 2, sf::Color(0, 125, 255, 255));
					stackX = i;
				}
				else
				{
					drawLine(surf, i, 0, i, Functions::Coord::height, 2, sf::Color(125, 125, 125, 255));
				}
			}
			for (int i = gridOffY + gridCamOffY; i < Functions::Coord::height; i += gridSizeY)
			{
				if (Functions::Math::isBetween(i, gridCursorY - ((int)std::floor(gridSizeY / 2) - 1), gridCursorY + ((int)std::floor(gridSizeY / 2) - 1)))
				{
					drawLine(surf, 0, i, Functions::Coord::width, i, 2, sf::Color(0, 125, 255, 255));
					stackY = i;
				}
				else
				{
					drawLine(surf, 0, i, Functions::Coord::width, i, 2, sf::Color(125, 125, 125, 255));
				}
			}
			if (stackX != -1 && stackY != -1)
			{
				gridMagnetX = stackX;
				gridMagnetY = stackY;
			}
			else
			{
				gridMagnetX = -1;
				gridMagnetY = -1;
			}
		}
	}
}