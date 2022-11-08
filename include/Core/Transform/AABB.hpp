#pragma once

#include <optional>

#include <Transform/Movable.hpp>
#include <Transform/Referential.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::animation
{
    template <class T>
    class TweenImpl;
}

namespace obe::transform
{
    /**
     * \brief A Class that does represent a Axis-Aligned Bounding Box (AABB) with various methods to
     *        manipulate it
     */
    class AABB : public Movable
    {
        friend class animation::TweenImpl<AABB>;

    protected:
        UnitVector m_size;

    public:
        using Movable::get_position;
        using Movable::move;
        using Movable::set_position;
        
        AABB() = default;
        AABB(const transform::UnitVector& position, const transform::UnitVector& size);

        /**
         * \brief Set the position of the Rect using an UnitVector
         * \param position Position to affect to the Rect
         * \param ref Referential used to set the Position
         */
        void set_position(const UnitVector& position, const Referential& ref);
        /**
         * \brief Get the Position of the Rect
         * \param ref Referential of the Rect you want to use to get the
         *        Position
         * \return The Position of the given Referential of the Rect
         */
        [[nodiscard]] UnitVector get_position(const Referential& ref) const;

        /**
         * \brief Set the Position of a specific Referential of the Rect (The
         *        opposite Point won't move)
         * \param position Position to affect to the specific Referential
         * \param ref Referential you want to move
         */
        void set_point_position(
            const UnitVector& position, const Referential& ref = Referential::TopLeft);
        /**
         * \brief Move a specific Referential of the Rect (The opposite Point won't move)
         * \param position Position to add to the specific
         *        Referential
         * \param ref Referential you want to move
         */
        void move_point(const UnitVector& position, const Referential& ref = Referential::TopLeft);

        /**
         * \brief Set the size of the Rect
         * \param size New size of the Rect
         * \param ref Referential used to resize the Rect (Referential that
         *        won't move)
         */
        void set_size(const UnitVector& size, const Referential& ref = Referential::TopLeft);
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
        [[nodiscard]] UnitVector get_size() const;

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
        * \param rect The other Rect to check
        * \return true if the Rect intersects the other Rect, false otherwise
        */
        [[nodiscard]] bool intersects(const AABB& rect) const;
        [[nodiscard]] std::optional<AABB> intersection(const AABB& rect) const;
        [[nodiscard]] bool contains(const AABB& rect) const;
        [[nodiscard]] bool contains(const UnitVector& position) const;
    };
} // namespace obe::transform
