//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>

#include <System/Cursor.hpp>

namespace obe
{
    namespace Editor
    {
        class EditorGrid
        {
        private:
            unsigned int m_gridSizeX;
            unsigned int m_gridSizeY;
            int gridOffX = 0;
            int gridOffY = 0;
            int gridMagnetX = -1;
            int gridMagnetY = -1;
        public:
            /**
             * \brief Constructor of the EditorGrid
             * \param cellWidth
             * \param cellHeight 
             * \param offsetX 
             * \param offsetY 
             */
            explicit EditorGrid(int cellWidth, int cellHeight, int offsetX = 0, int offsetY = 0);
            void setCellWidth(int cellWidth);
            void setCellHeight(int cellHeight);
            void setSize(int cellWidth, int cellHeight);
            void setOffsetX(int offsetX);
            void setOffsetY(int offsetY);
            void setOffset(int offsetX, int offsetY);
            int getCellWidth() const;
            int getCellHeight() const;
            int getOffsetX() const;
            int getOffsetY() const;
            void magnetize(System::Cursor& cursor) const;
            void moveMagnet(System::Cursor& cursor, int x, int y);
            void draw(sf::RenderWindow& target, System::Cursor& cursor, int offsetX, int offsetY);
        };
    }
}
