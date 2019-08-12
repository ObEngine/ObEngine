#include <cmath>

#include <Editor/Grid.hpp>
#include <Transform/UnitVector.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::Editor
{
    EditorGrid::EditorGrid(const unsigned int sizeX, const unsigned int sizeY, const int offsetX, const int offsetY) : 
    Togglable(false),
    Registrable("Grid")
    {
        m_gridSizeX = sizeX;
        m_gridSizeY = sizeY;
        m_gridOffX = offsetX;
        m_gridOffY = offsetY;
    }

    void EditorGrid::setCellWidth(const unsigned int cellWidth)
    {
        Debug::Log->trace("<EditorGrid> Set Cell Width : {0}", cellWidth);
        m_gridSizeX = cellWidth;
    }

    void EditorGrid::setCellHeight(const unsigned int cellHeight)
    {
        Debug::Log->trace("<EditorGrid> Set Cell Height : {0}", cellHeight);
        m_gridSizeY = cellHeight;
    }

    void EditorGrid::setSize(const unsigned int cellWidth, const unsigned int cellHeight)
    {
        Debug::Log->trace("<EditorGrid> Set Cell Size : {0}x{1}", cellWidth, cellHeight);
        this->setCellWidth(cellWidth);
        this->setCellHeight(cellHeight);
    }

    void EditorGrid::setOffsetX(const int offsetX)
    {
        Debug::Log->trace("<EditorGrid> Set Cell Offset X : {0}", offsetX);
        this->m_gridOffX = offsetX % this->m_gridSizeX;
    }

    void EditorGrid::setOffsetY(const int offsetY)
    {
        Debug::Log->trace("<EditorGrid> Set Cell Offset Y : {0}", offsetY);
        this->m_gridOffY = offsetY % this->m_gridSizeY;
    }

    void EditorGrid::setOffset(const int offsetX, const int offsetY)
    {
        Debug::Log->trace("<EditorGrid> Set Cell Offset : {0}, {1}", offsetX, offsetY);
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
        return m_gridOffX;
    }

    int EditorGrid::getOffsetY() const
    {
        return m_gridOffY;
    }

    void EditorGrid::magnetize(System::Cursor& cursor) const
    {
        if (m_gridMagnetX != -1 && m_gridMagnetY != -1)
        {
            Debug::Log->trace("<EditorGrid> Magnetize Cursor on {0}, {1}", m_gridMagnetX, m_gridMagnetY);
            cursor.setPosition(m_gridMagnetX, m_gridMagnetY);
        }
    }

    std::pair<int, int> EditorGrid::getClosestIntersection(const int x, const int y, const int offsetX, const int offsetY) const
    {
        const int startGridX = (m_gridSizeX - ((m_gridOffX + offsetX) % m_gridSizeX)) % m_gridSizeX;
        const int startGridY = (m_gridSizeY - ((m_gridOffY + offsetY) % m_gridSizeY)) % m_gridSizeY;
        int snappedX = std::round(float(x) / float(m_gridSizeX)) * m_gridSizeX + startGridX;
        int snappedY = std::round(float(y) / float(m_gridSizeY)) * m_gridSizeY + startGridY;
        Graphics::Utils::drawPoint(snappedX, snappedY, 4, sf::Color::Magenta);
        return std::pair<int, int>(snappedX, snappedY);
    }

    void EditorGrid::moveMagnet(System::Cursor& cursor, const int x, const int y)
    {
        if (m_gridMagnetX != -1 && m_gridMagnetY != -1)
        {
            Debug::Log->trace("<EditorGrid> Move Magnet to {0}, {1}", x, y);
            if (x != 0) m_gridMagnetX += (m_gridSizeX * x);
            if (y != 0) m_gridMagnetY += (m_gridSizeY * y);
            cursor.setPosition(m_gridMagnetX, m_gridMagnetY);
        }
    }

    void EditorGrid::draw(System::Cursor& cursor, int offsetX, int offsetY)
    {
        int stackX = -1;
        int stackY = -1;
        const sf::Color selectedLineColor(0, 125, 255, 255);
        const sf::Color normalLineColor(125, 125, 125, 255);
        while (offsetX < 0)
            offsetX += m_gridSizeX;
        while (offsetY < 0)
            offsetY += m_gridSizeY;
        const int startGridX = (m_gridSizeX - ((m_gridOffX + offsetX) % m_gridSizeX)) % m_gridSizeX; //<REVISION>
        for (int i = startGridX; i < Transform::UnitVector::Screen.w; i += m_gridSizeX)
        {
            if (Utils::Math::isBetween(i, cursor.getX() - (static_cast<int>(floor(m_gridSizeX / 2)) - 1), cursor.getX() + (static_cast<int>(floor(m_gridSizeX / 2)) - 1)))
            {
                Graphics::Utils::drawLine(i, 0, i, Transform::UnitVector::Screen.h, 2, selectedLineColor);
                stackX = i;
            }
            else
            {
                Graphics::Utils::drawLine(i, 0, i, Transform::UnitVector::Screen.h, 2, normalLineColor);
            }
        }
        const int startGridY = (m_gridSizeY - ((m_gridOffY + offsetY) % m_gridSizeY)) % m_gridSizeY;
        for (int i = startGridY; i < Transform::UnitVector::Screen.h; i += m_gridSizeY)
        {
            if (Utils::Math::isBetween(i, cursor.getY() - (static_cast<int>(floor(m_gridSizeY / 2)) - 1), cursor.getY() + (static_cast<int>(floor(m_gridSizeY / 2)) - 1)))
            {
                Graphics::Utils::drawLine(0, i, Transform::UnitVector::Screen.w, i, 2, selectedLineColor);
                stackY = i;
            }
            else
            {
                Graphics::Utils::drawLine(0, i, Transform::UnitVector::Screen.w, i, 2, normalLineColor);
            }
        }
        if (stackX != -1 && stackY != -1)
        {
            m_gridMagnetX = stackX;
            m_gridMagnetY = stackY;
        }
        else
        {
            m_gridMagnetX = -1;
            m_gridMagnetY = -1;
        }
    }
}