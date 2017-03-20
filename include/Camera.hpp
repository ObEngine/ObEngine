#pragma once

#include <SFML/Graphics.hpp>

#include "Functions.hpp"

namespace obe
{
	namespace World
	{
		enum Units
		{
			Pixels,
			WorldPercentage,
			WorldUnits
		};

		class Camera
		{
			private:
				sf::View view;
				double x;
				double y;
				double width;
				double height;
				double angle;
				double worldWidth;
				double worldHeight;

				double transformHorizontal(const double& x, Units unit);
				double transformVertical(const double& y, Units unit);
			public:
				Camera();
				void setWorldSize(const double& worldWidth, const double& worldHeight);
				void setPosition(const double& x, const double& y, Units unit = Units::WorldUnits);
				void move(const double& x, const double& y, Units unit = Units::WorldUnits);
				void setX(const double& x, Units unit = Units::WorldUnits);
				void setY(const double& y, Units unit = Units::WorldUnits);
				void setSize(const double& width, const double& height, Units unit = Units::WorldUnits);
				void scale(const double& width, const double& height, Units unit = Units::WorldUnits);
				void setWidth(const double& width, Units unit = Units::WorldUnits);
				void setHeight(const double& height, Units unit = Units::WorldUnits);
				void setAngle(const double& angle);
				void rotate(const double& angle);

				std::pair<double, double> getPosition(Units unit = Units::WorldUnits);
				double getX(Units unit = Units::WorldUnits);
				double getY(Units unit = Units::WorldUnits);
				double getWidth(Units unit = Units::WorldUnits);
				double getHeight(Units unit = Units::WorldUnits);
				double getWidthRatio();
				double getHeightRatio();
		};
	}
}