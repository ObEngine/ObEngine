#pragma once

#include "Coordinates.hpp"

namespace obe
{
	namespace Coord
	{
		class Rect
		{
			protected:
				UnitVector m_size;
				UnitVector m_position;
			public:
				/**
				 * \brief Set or Get Position using Referencials
				 */
				enum Referencial
				{
					/**
					* \brief Referencial TopLeft
					* \code
					* Coeff : w * 0, h * 0
					*
					* o | x | x
					* ----------
					* x | x | x
					* ----------
					* x | x | x
					* \endcode
					*/
					TopLeft,
					/**
					* \brief Referencial Top
					* \code
					* Coeff : w * 0.5, h * 1
					*
					* x | o | x
					* ----------
					* x | x | x
					* ----------
					* x | x | x
					* \endcode
					*/
					Top,
					/**
					* \brief Referencial TopRight
					* \code
					* Coeff : w * 1, h * 0
					*
					* x | x | o
					* ----------
					* x | x | x
					* ----------
					* x | x | x
					* \endcode
					*/
					TopRight,
					/**
					* \brief Referencial Left
					* \code
					* Coeff : w * 0, h * 0.5
					* 
					* x | x | x
					* ----------
					* o | x | x
					* ----------
					* x | x | x
					* \endcode
					*/
					Left,
					/**
					* \brief Referencial Center
					* \code
					* Coeff : w * 0.5, h * 0.5
					*
					* x | x | x
					* ----------
					* x | o | x
					* ----------
					* x | x | x
					* \endcode
					*/
					Center,
					/**
					* \brief Referencial Right
					* \code
					* Coeff : w * 1, h * 0.5
					*
					* x | x | x
					* ----------
					* x | x | o
					* ----------
					* x | x | x
					* \endcode
					*/
					Right,
					/**
					* \brief Referencial BottomLeft
					* \code
					* Coeff : w * 0, h * 1
					*
					* x | x | x
					* ----------
					* x | x | x
					* ----------
					* o | x | x
					* \endcode
					*/
					BottomLeft,
					/**
					* \brief Referencial Bottom
					* \code
					* Coeff : w * 0.5, h * 1
					*
					* x | x | x
					* ----------
					* x | x | x
					* ----------
					* x | o | x
					* \endcode
					*/
					Bottom,
					/**
					* \brief Referencial BottomRight
					* \code
					* Coeff : w * 1, h * 1
					* 
					* x | x | x
					* ----------
					* x | x | x
					* ----------
					* x | x | o
					* \endcode
					*/
					BottomRight,
				};
				/**
				 * \brief Conversion Type for Referencial Usage
				 */
				enum ConversionType
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

				void setPosition(const UnitVector& position, Referencial ref = TopLeft);
				void setPosition(double x, double y, Referencial ref = TopLeft);
				void move(const UnitVector& position);
				void move(double x, double y);
				void setX(double x, Referencial ref = TopLeft);
				void setY(double y, Referencial ref = TopLeft);
				double getX(Referencial ref = TopLeft) const;
				double getY(Referencial ref = TopLeft) const;
				UnitVector getPosition(Referencial ref = TopLeft) const;

				void setSize(const UnitVector& size);
				void setSize(double width, double height);
				void scale(const UnitVector& size);
				void scale(double width, double height);
				void setWidth(double width);
				void setHeight(double height);
				double getWidth() const;
				double getHeight() const;
				UnitVector getSize() const;
				
		};
	}
}