//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "ComplexSprite.hpp"
#include "Coordinates.hpp"

namespace obe
{
    namespace Graphics
    {
        class LevelSprite : public Coord::UnitBasedObject
        {
        private:
            std::string m_path = "";
            std::string m_id;

            Coord::ProtectedUnitVector m_position;
            Coord::ProtectedUnitVector m_offset;
            Coord::ProtectedUnitVector m_size;

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
            sf::Color m_spriteColor = sf::Color(255, 255, 255);
            std::string m_parentID = "";

            void applySize();
            void update();

        public:
            LevelSprite(std::string id);

            void load(std::string path);

            void setSprite(sf::Sprite* spr);
            void setTexture(sf::Texture texture);
            void setLayer(int layer);
            void setZDepth(int zdepth);
            void rotate(double addRotate);
            void setRotation(double rotate);
            
            void setTranslationOrigin(int x, int y);
            void setRotationOrigin(int x, int y);

            //Position
            void setPosition(double x, double y);
            void setOffset(double offx, double offy);
            void u_setPosition(const Coord::UnitVector& vec);
            void u_setOffset(const Coord::UnitVector& vec);
            void move(double x, double y);
            void moveOffset(double x, double y);
            void u_move(const Coord::UnitVector& vec);
            void u_moveOffset(const Coord::UnitVector& vec);
            Coord::ProtectedUnitVector& getPosition();
            Coord::ProtectedUnitVector& getOffset();
            double getX() const;
            double getY() const;
            double getOffsetX() const;
            double getOffsetY() const;

            //Size
            void scale(double scaleX, double scaleY);
            void setSize(double scaleX, double scaleY);
            void u_scale(const Coord::UnitVector& vec);
            void u_setSize(const Coord::UnitVector& vec);
            Coord::ProtectedUnitVector& getSize();

            void setAtr(std::vector<std::string> atrList);
            void addAtr(std::string atr);
            std::vector<std::string> getAttributes() const;
            void removeAtrByIndex(int index);
            void removeAtrByName(std::string name);
            sfe::ComplexSprite* getSprite();
            void setColor(sf::Color newColor);
            float getRotation() const;
            int getLayer() const;
            int getZDepth() const;
            std::string getID() const;
            std::string getPath() const;
            int getWidth() const;
            int getHeight() const;
            void calculateRealCoordinates();
            sf::FloatRect getRect();
            bool isDrawable() const;
            void setVisible(bool visible);
            bool isVisible() const;
            std::string getParentID() const;
            void setParentID(std::string parent);
        };
    }
}
