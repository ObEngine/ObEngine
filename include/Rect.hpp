#pragma once

#include "Coordinates.hpp"
#include "Referencial.hpp"
#include "DrawUtils.hpp"

#include <SFML/Graphics.hpp>
#include <any/any.hpp>

namespace obe
{
	namespace Coord
	{
		class Rect
		{
			protected:
				UnitVector m_size;
				UnitVector m_position;
				UnitVector getPointSizeModifier(Referencial ref);
			public:
				/**
				 * \brief Conversion Type for Referencial Usage
				 */
				enum class ConversionType
				{
					/**
					 * \brief Factor x1 (GetPosition)
					 */
					From,
					/**
					 * \brief Factor x-1 (SetPosition)
					 */
					To
				};

				/**
				 * \brief Transform the UnitVector passed by reference using the given Referencial
				 * \param vec The UnitVector you want to transform
				 * \param ref The chosen Rect::Referencial
				 * \param type The way you want to transform your UnitVector
				 *			   - From : Referencial::TopLeft to ref
				 *			   - To : ref to Referencial::TopLeft
				 */
				void transformRef(UnitVector& vec, Referencial ref, ConversionType type) const;

				void setPosition(const UnitVector& position, Referencial ref = Referencial::TopLeft);
				void setPosition(double x, double y, Referencial ref = Referencial::TopLeft);
				void move(const UnitVector& position);
				void move(double x, double y);
				void setX(double x, Referencial ref = Referencial::TopLeft);
				void setY(double y, Referencial ref = Referencial::TopLeft);
				double getX(Referencial ref = Referencial::TopLeft) const;
				double getY(Referencial ref = Referencial::TopLeft) const;
				UnitVector getPosition(Referencial ref = Referencial::TopLeft) const;

				void setPointPosition(const UnitVector& position, Referencial ref = Referencial::TopLeft);
				void setPointPosition(double x, double y, Referencial ref = Referencial::TopLeft);
				void movePoint(const UnitVector& position);
				void movePoint(double x, double y);
				void setPointX(double x, Referencial ref = Referencial::TopLeft);
				void setPointY(double y, Referencial ref = Referencial::TopLeft);

				void setSize(const UnitVector& size, Referencial ref = Referencial::TopLeft);
				void setSize(double width, double height, Referencial ref = Referencial::TopLeft);
				void scale(const UnitVector& size, Referencial ref = Referencial::TopLeft);
				void scale(double width, double height, Referencial ref = Referencial::TopLeft);
				void setWidth(double width, Referencial ref = Referencial::TopLeft);
				void setHeight(double height, Referencial ref = Referencial::TopLeft);
				double getWidth() const;
				double getHeight() const;
				UnitVector getSize() const;

				void draw(sf::RenderWindow& target);
		};
	}
}