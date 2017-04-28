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
		class LevelSprite
		{
		private:
			std::string m_path = "";
			std::string m_id;

			Coord::UnitVector m_position;
			Coord::UnitVector m_offset;
			Coord::Units m_workingUnit = Coord::WorldUnits;

			double m_width = 0;
			double m_height = 0;

			bool m_drawable = true;
			bool m_visible = true;

			double m_rotation = 0;
			double m_scaleX = 1;
			double m_scaleY = 1;

			int m_originTraX = 0;
			int m_originTraY = 0;
			int m_originRotX = 0;
			int m_originRotY = 0;

			std::vector<std::string> m_currentAtr = {};
			int m_layer = 1;
			int m_zdepth = 0;
			sf::Texture m_texture;
			sfe::ComplexSprite m_returnSprite;
			sf::Color m_spriteColor = sf::Color(255, 255, 255);
			std::string m_parentID = "";

			void update();

		public:
			LevelSprite(std::string id);

			void load(std::string path);

			void setWorkingUnit(Coord::Units unit);
			Coord::Units getWorkingUnit() const;
			void setSprite(sf::Sprite* spr);
			void setTexture(sf::Texture texture);
			void setLayer(int layer);
			void setZDepth(int zdepth);
			void rotate(double addRotate);
			void setRotation(double rotate);
			void scale(double scaleX, double scaleY);
			void setScale(double scaleX, double scaleY);
			void setTranslationOrigin(int x, int y);
			void setRotationOrigin(int x, int y);
			void setPosition(double x, double y);
			void setOffset(double offx, double offy);
			double getX() const;
			double getY() const;
			double getOffsetX() const;
			double getOffsetY() const;
			void setAtr(std::vector<std::string> atrList);
			void addAtr(std::string atr);
			std::vector<std::string> getAttributes() const;
			void removeAtrByIndex(int index);
			void removeAtrByName(std::string name);
			sfe::ComplexSprite* getSprite();
			void setColor(sf::Color newColor);
			void move(double x, double y);
			double getScaleX() const;
			double getScaleY() const;
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
