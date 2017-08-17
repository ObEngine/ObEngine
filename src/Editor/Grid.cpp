#include <cmath>

#include <Editor/Grid.hpp>
#include <Transform/UnitVector.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Utils/MathUtils.hpp>

namespace obe
{
    namespace Editor
    {
        EditorGrid::EditorGrid(unsigned int sizeX, unsigned int sizeY, int offsetX, int offsetY) : Types::Togglable(false)
        {
            m_gridSizeX = sizeX;
            m_gridSizeY = sizeY;
            gridOffX = offsetX;
            gridOffY = offsetY;
        }

        void EditorGrid::setCellWidth(unsigned int sizeX)
        {
            m_gridSizeX = sizeX;
        }

        void EditorGrid::setCellHeight(unsigned int sizeY)
        {
            m_gridSizeY = sizeY;
        }

        void EditorGrid::setSize(unsigned int sizeX, unsigned int sizeY)
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

        unsigned int EditorGrid::getCellWidth() const
        {
            return m_gridSizeX;
        }

        unsigned int EditorGrid::getCellHeight() const
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
            while (offsetX < 0)
                offsetX += m_gridSizeX;
            while (offsetY < 0)
                offsetY += m_gridSizeY;
            int startGridX = (m_gridSizeX - ((gridOffX + offsetX) % m_gridSizeX)) % m_gridSizeX; //<REVISION>
            for (int i = startGridX; i < Transform::UnitVector::Screen.w; i += m_gridSizeX)
            {
                if (Utils::Math::isBetween(i, cursor.getX() - (static_cast<int>(floor(m_gridSizeX / 2)) - 1), cursor.getX() + (static_cast<int>(floor(m_gridSizeX / 2)) - 1)))
                {
                    Graphics::Utils::drawLine(target, i, 0, i, Transform::UnitVector::Screen.h, 2, selectedLineColor);
                    stackX = i;
                }
                else
                {
                    Graphics::Utils::drawLine(target, i, 0, i, Transform::UnitVector::Screen.h, 2, normalLineColor);
                }
            }
            int startGridY = (m_gridSizeY - ((gridOffY + offsetY) % m_gridSizeY)) % m_gridSizeY;
            for (int i = startGridY; i < Transform::UnitVector::Screen.h; i += m_gridSizeY)
            {
                if (Utils::Math::isBetween(i, cursor.getY() - (static_cast<int>(floor(m_gridSizeY / 2)) - 1), cursor.getY() + (static_cast<int>(floor(m_gridSizeY / 2)) - 1)))
                {
                    Graphics::Utils::drawLine(target, 0, i, Transform::UnitVector::Screen.w, i, 2, selectedLineColor);
                    stackY = i;
                }
                else
                {
                    Graphics::Utils::drawLine(target, 0, i, Transform::UnitVector::Screen.w, i, 2, normalLineColor);
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
