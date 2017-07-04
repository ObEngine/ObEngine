//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "EditorGrid.hpp"

namespace obe
{
    namespace Editor
    {
        EditorGrid::EditorGrid(int sizeX, int sizeY, int offsetX, int offsetY)
        {
            m_gridSizeX = sizeX;
            m_gridSizeY = sizeY;
            gridOffX = offsetX;
            gridOffY = offsetY;
        }

        void EditorGrid::setCellWidth(int sizeX)
        {
            m_gridSizeX = sizeX;
        }

        void EditorGrid::setCellHeight(int sizeY)
        {
            m_gridSizeY = sizeY;
        }

        void EditorGrid::setSize(int sizeX, int sizeY)
        {
            this->setCellWidth(sizeX);
            this->setCellHeight(sizeY);
        }

        void EditorGrid::setOffsetX(int offsetX)
        {
            this->gridOffX = offsetX % this->m_gridSizeX;
        }

        void EditorGrid::setOffsetY(int offsetY)
        {
            this->gridOffY = offsetY % this->m_gridSizeY;
        }

        void EditorGrid::setOffset(int offsetX, int offsetY)
        {
            this->setOffsetX(offsetX);
            this->setOffsetY(offsetY);
        }

        int EditorGrid::getCellWidth() const
        {
            return m_gridSizeX;
        }

        int EditorGrid::getCellHeight() const
        {
            return m_gridSizeY;
        }

        int EditorGrid::getOffsetX() const
        {
            return gridOffX;
        }

        int EditorGrid::getOffsetY() const
        {
            return gridOffY;
        }

        void EditorGrid::magnetize(System::Cursor& cursor) const
        {
            if (gridMagnetX != -1 && gridMagnetY != -1)
            {
                cursor.setPosition(gridMagnetX, gridMagnetY);
            }
        }

        void EditorGrid::moveMagnet(System::Cursor& cursor, int x, int y)
        {
            if (gridMagnetX != -1 && gridMagnetY != -1)
            {
                if (x != 0) gridMagnetX += (m_gridSizeX * x);
                if (y != 0) gridMagnetY += (m_gridSizeY * y);
                cursor.setPosition(gridMagnetX, gridMagnetY);
            }
        }

        void EditorGrid::draw(sf::RenderWindow& target, System::Cursor& cursor, int offsetX, int offsetY)
        {
            int stackX = -1;
            int stackY = -1;
            sf::Color selectedLineColor(0, 125, 255, 255);
            sf::Color normalLineColor(125, 125, 125, 255);
            for (int i = gridOffX + offsetX; i < Coord::UnitVector::Screen.w; i += m_gridSizeX)
            {
                if (Functions::Math::isBetween(i, cursor.getX() - (static_cast<int>(floor(m_gridSizeX / 2)) - 1), cursor.getX() + (static_cast<int>(floor(m_gridSizeX / 2)) - 1)))
                {
                    Graphics::Utils::drawLine(target, i, 0, i, Coord::UnitVector::Screen.h, 2, selectedLineColor);
                    stackX = i;
                }
                else
                {
                    Graphics::Utils::drawLine(target, i, 0, i, Coord::UnitVector::Screen.h, 2, normalLineColor);
                }
            }
            for (int i = gridOffY + offsetY; i < Coord::UnitVector::Screen.h; i += m_gridSizeY)
            {
                if (Functions::Math::isBetween(i, cursor.getY() - (static_cast<int>(floor(m_gridSizeY / 2)) - 1), cursor.getY() + (static_cast<int>(floor(m_gridSizeY / 2)) - 1)))
                {
                    Graphics::Utils::drawLine(target, 0, i, Coord::UnitVector::Screen.w, i, 2, normalLineColor);
                    stackY = i;
                }
                else
                {
                    Graphics::Utils::drawLine(target, 0, i, Coord::UnitVector::Screen.w, i, 2, selectedLineColor);
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
