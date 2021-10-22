#pragma once

#include <optional>

#include <Graphics/RenderTarget.hpp>
#include <Transform/Movable.hpp>
#include <Transform/Referential.hpp>
#include <Types/Tweenable.hpp>

namespace obe::Transform
{
    /**
     * \brief Conversion Type for Referential Usage
     */
    enum class ReferentialConversionType
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
     * \brief A Class that does represent a Rectangle with various methods to
     *        manipulate it
     */
    class Rect : public Movable, public Types::Tweenable<3>
    {
    protected:
        /**
         * \brief Size of the Rect
         */
        UnitVector m_size;
        double m_angle = 0;

    public:
        /**
         * \brief Transform the UnitVector passed by reference using the given
         * Referential
         * \param vec The UnitVector you want to transform
         * \param ref The chosen Rect::Referential
         * \param type The way you want to transform your UnitVector
         *          - From : Referential::TopLeft to ref
         *          - To : ref to Referential::TopLeft
         */
        void transformRef(
            UnitVector& vec, const Referential& ref, ReferentialConversionType type) const;

        Rect() = default;
        Rect(const Transform::UnitVector& position, const Transform::UnitVector& size);
        /**
         * \brief Set the position of the Rect (Movable override) using an
         *        UnitVector
         * \param position Position to affect to the Rect (Movable
         *        override)
         */
        void setPosition(const UnitVector& position) override;
        /**
         * \brief Get the Position of the Rect (Movable Override)
         * \return The Position of the given Referential of the Rect (Movable
         *         Override)
         */
        [[nodiscard]] UnitVector getPosition() const override;
        /**
         * \brief Set the position of the Rect using an UnitVector
         * \param position Position to affect to the Rect
         * \param ref Referential used to set the Position
         */
        virtual void setPosition(const UnitVector& position, const Referential& ref);
        /**
         * \brief Moves the Rectangle (Adds the given position to the current
         *        one)
         * \param position Position to add to the current Position
         */
        void move(const UnitVector& position) override;
        /**
         * \brief Get the Position of the Rect
         * \param ref Referential of the Rect you want to use to get the
         *        Position
         * \return The Position of the given Referential of the Rect
         */
        [[nodiscard]] virtual UnitVector getPosition(const Referential& ref) const;

        /**
         * \brief Set the Position of a specific Referential of the Rect (The
         *        opposite Point won't move)
         * \param position Position to affect to the specific Referential
         * \param ref Referential you want to move
         */
        void setPointPosition(
            const UnitVector& position, const Referential& ref = Referential::TopLeft);
        /**
         * \brief Move a specific Referential of the Rect (The opposite Point won't move)
         * \param position Position to add to the specific
         *        Referential
         * \param ref Referential you want to move
         */
        void movePoint(const UnitVector& position, const Referential& ref = Referential::TopLeft);

        /**
         * \brief Set the size of the Rect
         * \param size New size of the Rect
         * \param ref Referential used to resize the Rect (Referential that
         *        won't move)
         */
        void setSize(const UnitVector& size, const Referential& ref = Referential::TopLeft);
        /**
         * \brief Scales the Rect (Relative to the current size)
         * \param size Size to multiply to the current size
         * \param ref Referential used to scale the Rect (Referential that won't
         *        move)
         */
        void scale(const UnitVector& size, const Referential& ref = Referential::TopLeft);
        /**
         * \brief Get the Size of the Rect
         * \return An UnitVector containing the size of the Rect (Default Unit
         *         is SceneUnits)
         */
        [[nodiscard]] virtual UnitVector getSize() const;
        /**
         * \brief Get the Scale Factor of the Rect
         * \return An UnitVector containing the Scale Factors of the Rect.
         *          - x attribute will be equal to -1 if the Rect is flipped
         *            horizontally, 1 otherwise.
         *          - y attribute will be equal to -1 if the
         *            Rect is flipped vertically, 1 otherwise.
         */
        [[nodiscard]] UnitVector getScaleFactor() const;
        [[nodiscard]] double getRotation() const;
        void setRotation(double angle, Transform::UnitVector origin);
        void rotate(double angle, Transform::UnitVector origin);
        /**
         * \brief Draws the Rect for debug purposes <REMOVE>
         */
        void draw(Graphics::RenderTarget surface, int x, int y) const;

        /**
         * \asproperty
         */
        [[nodiscard]] double x() const;
        /**
         * \asproperty
         */
        [[nodiscard]] double y() const;
        /**
         * \asproperty
         */
        [[nodiscard]] double width() const;
        /**
         * \asproperty
         */
        [[nodiscard]] double height() const;
        /**
        * \brief Checks if the Rect intersects a specified Rect
        * \param other The other Rect to check
        * \return true if the Rect intersects the other Rect, false otherwise
        */
        [[nodiscard]] bool intersects(const Rect& rect) const;
        [[nodiscard]] std::optional<Rect> intersection(const Rect& rect) const;
        [[nodiscard]] bool contains(const Rect& rect) const;
        [[nodiscard]] bool contains(const UnitVector& position) const;

        void setNumericalComponents(const NumericalComponents& components) override
        {
            m_size.set(components.at(0), components.at(1));
            m_angle = components.at(2);
        }

        [[nodiscard]] NumericalComponents getNumericalComponents() override
        {
            return { m_size.x, m_size.y, m_angle };
        }
    };
} // namespace obe::Transform
