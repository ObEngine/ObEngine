#pragma once

#include <Transform/Movable.hpp>
#include <Transform/Referencial.hpp>

namespace obe::Transform
{
    /**
    * \brief A Class that does represent a Rectangle with various methods to manipulate it
    * @Bind
    */
    class Rect : public Movable
    {
    protected:
		/**
		* \brief Size of the Rect
		*/
        UnitVector m_size;
        float m_angle = 0;
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

        Rect(MovableType type);
        /**
        * \brief Set the position of the Rect (Movable override) using an UnitVector
        * \param position Position to affect to the Rect (Movable override)
        */
        void setPosition(const UnitVector& position) override;
        /**
        * \brief Get the Position of the Rect (Movable Override)
        * \return The Position of the given Referencial of the Rect (Movable Override)
        */
        UnitVector getPosition() const override;
        /**
        * \brief Set the position of the Rect using an UnitVector
        * \param position Position to affect to the Rect
        * \param ref Referencial used to set the Position
        */
	    virtual void setPosition(const UnitVector& position, Referencial ref);
        /**
        * \brief Moves the Rectangle (Adds the given position to the current one)
        * \param position Position to add to the current Position
        */
        void move(const UnitVector& position) override;
        /**
        * \brief Get the Position of the Rect
        * \param ref Referencial of the Rect you want to use to get the Position
        * \return The Position of the given Referencial of the Rect
        */
	    virtual UnitVector getPosition(Referencial ref) const;

        /**
        * \brief Set the Position of a specific Referencial of the Rect (The opposite Point won't move)
        * \param position Position to affect to the specific Referencial
        * \param ref Referencial you want to move
        */
        void setPointPosition(const UnitVector& position, Referencial ref = Referencial::TopLeft);
        /**
        * \brief Move a specific Referencial of the Rect (The opposite Point won't move)
        * \param position Position to add to the specific Referencial
        * \param ref Referencial you want to move
        */
        void movePoint(const UnitVector& position, Referencial ref = Referencial::TopLeft);

        /**
        * \brief Set the size of the Rect
        * \param size New size of the Rect
        * \param ref Referencial used to resize the Rect (Referencial that won't move)
        */
        void setSize(const UnitVector& size, Referencial ref = Referencial::TopLeft);
        /**
        * \brief Scales the Rect (Relative to the current size)
        * \param size Size to multiply to the current size 
        * \param ref Referencial used to scale the Rect (Referencial that won't move)
        */
        void scale(const UnitVector& size, Referencial ref = Referencial::TopLeft);
        /**
        * \brief Get the Size of the Rect
        * \return An UnitVector containing the size of the Rect (Default Unit is WorldUnits)
        */
	    virtual UnitVector getSize() const;
        /**
        * \brief Get the Scale Factor of the Rect
        * \return An UnitVector containing the Scale Factors of the Rect. \n
        *         x attribute will be equal to -1 if the Rect is flipped horizontally, 1 otherwise. \n
        *         y attribute will be equal to -1 if the Rect is flipped vertically, 1 otherwise.
        */
        UnitVector getScaleFactor() const;
        float getRotation() const;
        void setRotation(float angle, Transform::UnitVector origin);
        void rotate(float angle, Transform::UnitVector origin);
        /**
        * \brief Draws the Rect for debug purposes <REMOVE>
        */
        void draw(int posX, int posY) const;
    };
}
