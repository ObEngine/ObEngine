#pragma once

#include <Transform/Referencial.hpp>

namespace obe
{
	namespace Transform
	{
	    /**
		 * \brief A Class that does represent a Rectangle with various methods to manipulate it
		 */
		class Rect
		{
		protected:
		    /**
			 * \brief Size of the Rect
			 */
			UnitVector m_size;
		    /**
			 * \brief Position of the Rect
			 */
			UnitVector m_position;
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

		    /**
			* \brief Set the position of the Rect using an UnitVector
			* \param position Position to affect to the Rect
			* \param ref Referencial used to set the Position
			*/
			void setPosition(const UnitVector& position, Referencial ref = Referencial::TopLeft);
            /**
            * \brief Set the position of the Rect using a pair of double
            * \param x x Coordinate of the Position to affect to the Rect
            * \param y x Coordinate of the Position to affect to the Rect
            * \param ref Referencial used to set the Position
            */
			void setPosition(double x, double y, Referencial ref = Referencial::TopLeft);
		    /**
			 * \brief Moves the Rectangle (Adds the given position to the current one)
			 * \param position Position to add to the current Position
			 */
			void move(const UnitVector& position);
		    /**
			 * \brief Moves the Rectangle (Adds the given position to the current one)
			 * \param x x Coordinate of the Position to add to the current Position
			 * \param y y Coordinate of the Position to add to the current Position
			 */
			void move(double x, double y);
		    /**
			 * \brief Only set the x Coordinate of the Position of the Rect
			 * \param x x Coordinate of the Position to set to the Rect
			 * \param ref Referencial used to set the Position
			 */
			void setX(double x, Referencial ref = Referencial::TopLeft);
            /**
            * \brief Only set the y Coordinate of the Position of the Rect
            * \param y y Coordinate of the Position to set to the Rect
            * \param ref Referencial used to set the Position
            */
			void setY(double y, Referencial ref = Referencial::TopLeft);
		    /**
			 * \brief Get the x Coordinate of the Rect Position
			 * \param ref Referencial of the Rect you want to use to get the Position
			 * \return The x Coordinate of the given Referencial of the Rect
			 */
			double getX(Referencial ref = Referencial::TopLeft) const;
            /**
            * \brief Get the y Coordinate of the Rect Position
            * \param ref Referencial of the Rect you want to use to get the Position
            * \return The y Coordinate of the given Referencial of the Rect
            */
			double getY(Referencial ref = Referencial::TopLeft) const;
		    /**
			 * \brief Get the Position of the Rect
			 * \param ref Referencial of the Rect you want to use to get the Position
			 * \return The Position of the given Referencial of the Rect
			 */
			UnitVector getPosition(Referencial ref = Referencial::TopLeft) const;

		    /**
			 * \brief Set the Position of a specific Referencial of the Rect (The opposite Point won't move)
			 * \param position Position to affect to the specific Referencial
			 * \param ref Referencial you want to move
			 */
			void setPointPosition(const UnitVector& position, Referencial ref = Referencial::TopLeft);
		    /**
			 * \brief Set the Position of a specific Referencial of the Rect (The opposite Point won't move)
			 * \param x x Coordinate of the Position to affect to the specific Referencial
			 * \param y y Coordinate of the Position to affect to the specific Referencial
			 * \param ref Referencial you want to move
			 */
			void setPointPosition(double x, double y, Referencial ref = Referencial::TopLeft);
		    /**
			 * \brief Move a specific Referencial of the Rect (The opposite Point won't move)
			 * \param position Position to add to the specific Referencial
			 * \param ref Referencial you want to move
			 */
			void movePoint(const UnitVector& position, Referencial ref = Referencial::TopLeft);
		    /**
			 * \brief Move a specific Referencial of the Rect (The opposite Point won't move)
			 * \param x x Coordinate of the Position to add to the specific Referencial
			 * \param y y Coordinate of the Position to add to the specific Referencial
			 * \param ref Referencial you want to move
			 */
			void movePoint(double x, double y, Referencial ref = Referencial::TopLeft);
		    /**
			 * \brief Only set the x Coordinate of a specific Referencial of the Rect
			 * \param x x Coordinate of the Position to set to the specific Referencial
			 * \param ref Referencial you want to move
			 */
			void setPointX(double x, Referencial ref = Referencial::TopLeft);
            /**
            * \brief Only set the y Coordinate of a specific Referencial of the Rect
            * \param y y Coordinate of the Position to set to the specific Referencial
            * \param ref Referencial you want to move
            */
			void setPointY(double y, Referencial ref = Referencial::TopLeft);

		    /**
			 * \brief Set the size of the Rect
			 * \param size New size of the Rect
			 * \param ref Referencial used to resize the Rect (Referencial that won't move)
			 */
			void setSize(const UnitVector& size, Referencial ref = Referencial::TopLeft);
		    /**
			 * \brief Set the size of the Rect
			 * \param width New width of the Rect
			 * \param height New height of the Rect
			 * \param ref Referencial used to resize the Rect (Referencial that won't move)
			 */
			void setSize(double width, double height, Referencial ref = Referencial::TopLeft);
		    /**
			 * \brief Scales the Rect (Relative to the current size)
			 * \param size Size to multiply to the current size 
			 * \param ref Referencial used to scale the Rect (Referencial that won't move)
			 */
			void scale(const UnitVector& size, Referencial ref = Referencial::TopLeft);
		    /**
			 * \brief Scales the Rect (Relative to the current size)
			 * \param width Width to multiply to the current width
			 * \param height height to multiply to the current height
			 * \param ref Referencial used to scale the Rect (Referencial that won't move)
			 */
			void scale(double width, double height, Referencial ref = Referencial::TopLeft);
		    /**
			 * \brief Set the Width of the Rect
			 * \param width New Width of the Rect
			 * \param ref Referencial used to resize the Rect (Referencial that won't move)
			 */
			void setWidth(double width, Referencial ref = Referencial::TopLeft);
            /**
            * \brief Set the Height of the Rect
            * \param height New Height of the Rect
            * \param ref Referencial used to resize the Rect (Referencial that won't move)
            */
			void setHeight(double height, Referencial ref = Referencial::TopLeft);
		    /**
			 * \brief Get the Width of the Rect
			 * \return The Width of the Rect
			 */
			double getWidth() const;
		    /**
			 * \brief Get the Height of the Rect
			 * \return The Height of the Rect
			 */
			double getHeight() const;
		    /**
			 * \brief Get the Size of the Rect
			 * \return An UnitVector containing the size of the Rect (Default Unit is WorldUnits)
			 */
			UnitVector getSize() const;
		    /**
			 * \brief Get the Scale Factor of the Rect
			 * \return An UnitVector containing the Scale Factors of the Rect. \n
			 *         x attribute will be equal to -1 if the Rect is flipped horizontally, 1 otherwise. \n
			 *         y attribute will be equal to -1 if the Rect is flipped vertically, 1 otherwise.
			 */
			UnitVector getScaleFactor() const;

		    /**
			 * \brief Draws the Rect for debug purposes <REMOVE>
			 * \param target sf::RenderWindow where to render the Rect
			 */
			void display(sf::RenderWindow& target);
		};
	}
}