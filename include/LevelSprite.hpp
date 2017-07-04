//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <any/any.hpp>

#include "Animation.hpp"
#include "ComplexSprite.hpp"
#include "Coordinates.hpp"
#include "DrawUtils.hpp"
#include "Rect.hpp"
#include "Referencial.hpp"
#include "Selectable.hpp"

namespace obe
{
    namespace Graphics
    {
        class LevelSprite : public Coord::UnitBasedObject, public Types::Selectable, public Coord::Rect
        {
        private:
            std::string m_path = "";
            std::string m_id;

            Coord::Rect m_rect;
            int m_handlePointRadius = 6;

            double m_width = 0;
            double m_height = 0;

            bool m_drawable = true;
            bool m_visible = true;

            double m_rotation = 0;

            int m_originTraX = 0;
            int m_originTraY = 0;
            int m_originRotX = 0;
            int m_originRotY = 0;
            int m_originScaX = 0;
            int m_originScaY = 0;

            std::vector<std::string> m_currentAtr = {};
            int m_layer = 1;
            int m_zdepth = 0;
            sf::Texture m_texture;
            sfe::ComplexSprite m_returnSprite;
            std::string m_parentID = "";

            void applySize();;
        public:
            LevelSprite(std::string id);

            void load(std::string path);

            void setSprite(sf::Sprite* spr);
            void setTexture(sf::Texture texture);
            sf::Texture& getTexture();
            void setLayer(int layer);
            void setZDepth(int zdepth);
            void rotate(double addRotate);
            void setRotation(double rotate);
            
            //Origins
            void setTranslationOrigin(int x, int y);
            void setRotationOrigin(int x, int y);
            void setScalingOrigin(int x, int y);

            //Position
            Coord::UnitVector getDrawPosition(Coord::UnitVector& cameraPosition);

            //Handle
            void drawHandle(sf::RenderWindow& target, int spritePositionX, int spritePositionY);
            void getHandlePoint(Coord::UnitVector& cameraPosition, int posX, int posY);

            double getSpriteWidth();
            double getSpriteHeight();

            void setAtr(std::vector<std::string> atrList);
            void addAtr(std::string atr);
            std::vector<std::string> getAttributes() const;
            void removeAtrByIndex(int index);
            void removeAtrByName(std::string name);
            sfe::ComplexSprite& getSprite();
            void setColor(sf::Color newColor);
            float getRotation() const;
            int getLayer() const;
            int getZDepth() const;
            std::string getID() const;
            std::string getPath() const;
            sf::FloatRect getRect();
            bool isDrawable() const;
            void setVisible(bool visible);
            bool isVisible() const;
            std::string getParentID() const;
            void setParentID(std::string parent);

            class HandlePoint
            {
            private:
                LevelSprite* m_parent;
                int m_changeWidthFactor;
                int m_changeHeightFactor;
                Coord::Referencial m_referencial;
                int m_x;
                int m_y;
            public:
                HandlePoint(LevelSprite* parent, Coord::Referencial ref);
                void moveTo(int x, int y);
            };
        };
    }
}
