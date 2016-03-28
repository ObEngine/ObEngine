#include "EditorGrid.hpp"

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

void EditorGrid::setOffsetX(int offsetX)
{
	bool needToRender = offsetX != gridOffX;
	gridOffX = offsetX;
}

void EditorGrid::setOffsetY(int offsetY)
{
	bool needToRender = offsetY != gridOffY;
	gridOffY = offsetY;
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

void EditorGrid::magnetize(Cursor* cur)
{
	if (gridMagnetX != -1 && gridMagnetY != -1)
	{
		cur->setPosition(gridMagnetX, gridMagnetY);
	}
}

void EditorGrid::moveMagnet(Cursor* cur, int tox, int toy)
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
	for (int i = gridOffX; i < fn::Coord::width; i += gridSizeX)
	{
		if (fn::Math::isBetween(i + gridCamOffX, gridCursorX - ((int)std::floor(gridSizeX / 2) - 1), gridCursorX + ((int)std::floor(gridSizeX / 2) - 1)))
		{
			drawLine(surf, i + gridCamOffX, 0 + gridCamOffY, i + gridCamOffX, fn::Coord::height + gridCamOffY, 2, sf::Color(0, 125, 255, 255));
			stackX = i + gridCamOffX;
		}
		else
		{
			drawLine(surf, i + gridCamOffX, 0 + gridCamOffY, i + gridCamOffX, fn::Coord::height + gridCamOffY, 2, sf::Color(125, 125, 125, 255));
		}
	}
	for (int i = gridOffY; i < fn::Coord::height; i += gridSizeY)
	{
		if (fn::Math::isBetween(i + gridCamOffY, gridCursorY - ((int)std::floor(gridSizeY / 2) - 1), gridCursorY + ((int)std::floor(gridSizeY / 2) - 1)))
		{
			drawLine(surf, 0 + gridCamOffX, i + gridCamOffY, fn::Coord::width + gridCamOffX, i + gridCamOffY, 2, sf::Color(0, 125, 255, 255));
			stackY = i + gridCamOffY;
		}
		else
		{
			drawLine(surf, 0 + gridCamOffX, i + gridCamOffY, fn::Coord::width + gridCamOffX, i + gridCamOffY, 2, sf::Color(125, 125, 125, 255));
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