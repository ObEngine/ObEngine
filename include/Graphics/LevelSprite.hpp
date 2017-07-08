#pragma once

#include <sfe/ComplexSprite.hpp>

#include <Transform/Rect.hpp>
#include <Transform/Referencial.hpp>
#include <Transform/UnitBasedObject.hpp>
#include <Types/Identifiable.hpp>
#include <Types/Selectable.hpp>

namespace obe
{
    namespace Graphics
    {
        class LevelSprite : public Transform::UnitBasedObject, public Types::Selectable, public Transform::Rect, public Types::Identifiable
        {
        public:
            class HandlePoint
            {
            private:
                Transform::Rect* m_rect;
                int m_changeWidthFactor;
                int m_changeHeightFactor;
                Transform::Referencial m_referencial;
                int m_x;
                int m_y;
            public:
                HandlePoint(Transform::Rect* parentRect, Transform::Referencial ref);
                void moveTo(int x, int y);
                Transform::Referencial getReferencial() const;
                Transform::Rect& getRect() const;
                static const int radius = 6;
            };
        private:
            std::string m_path = "";

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

            std::vector<HandlePoint> m_handlePoints;
            std::vector<std::string> m_currentAtr = {};
            int m_layer = 1;
            int m_zdepth = 0;
            sf::Texture m_texture;
            sfe::ComplexSprite m_returnSprite;
            std::string m_parentID = "";

            void applySize();;
        public:
            explicit LevelSprite(const std::string& id);

            void load(const std::string& path);

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
            Transform::UnitVector getDrawPosition(Transform::UnitVector& cameraPosition);

            double getSpriteWidth();
            double getSpriteHeight();
            int getXScaleFactor();
            int getYScaleFactor();

            void setAtr(std::vector<std::string> atrList);
            void addAtr(const std::string& atr);
            std::vector<std::string> getAttributes() const;
            void removeAtrByIndex(int index);
            void removeAtrByName(std::string name);
            sfe::ComplexSprite& getSprite();
            void setColor(sf::Color newColor);
            float getRotation() const;
            int getLayer() const;
            int getZDepth() const;
            std::string getPath() const;
            sf::FloatRect getRect();
            bool isDrawable() const;
            void setVisible(bool visible);
            bool isVisible() const;
            std::string getParentID() const;
            void setParentID(const std::string& parent);

            //Handle
            void drawHandle(sf::RenderWindow& target, int spritePositionX, int spritePositionY);
            HandlePoint* getHandlePoint(Transform::UnitVector& cameraPosition, int posX, int posY);
            int getHandlePointRadius() const;
        };
    }
}
