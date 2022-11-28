#pragma once

#include <Collision/Collider.hpp>
#include <Transform/Polygon.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::collision
{
    class ComplexPolygonCollider : public Collider
    {
    private:
        std::vector<transform::UnitVector> m_points;
    protected:
        [[nodiscard]] const void* get_c2_shape() const override;
        [[nodiscard]] const c2x* get_c2_space_transform() const override;

    public:
        static constexpr ColliderType Type = ColliderType::ComplexPolygon;
        [[nodiscard]] ColliderType get_collider_type() const override;

        ComplexPolygonCollider() = default;

        [[nodiscard]] transform::UnitVector get_position() const override;
        void set_position(const transform::UnitVector& position) override;
        void move(const transform::UnitVector& position) override;

        /**
         * \brief Adds a new Point to the Polygon at Position (x, y)
         * \param position Coordinate of the Position where to add the new Point
         * \param point_index Index where to insert the new Point, Use point_index
         *        = -1 <DefaultArg> to insert at the end (between last and first Point)
         */
        virtual void add_point(const transform::UnitVector& position, int point_index = -1);
        /**
         * \brief Get the number of points in the Polygon
         * \return The amount of points in the Polygon
         */
        [[nodiscard]] std::size_t get_points_amount() const;

        /**
         * \brief Checks if two polygons are intersecting
         * \param collider The other collider to test
         * \param offset The offset to apply to the source collider
         * \return true if the two polygons intersects, false otherwise
         */
        [[nodiscard]] bool collides(const Collider& collider) const override;
        /**
         * \brief Gets the Maximum distance before Collision with a specific
         *        Collider
         * \param collider Collider to check the Collision with
         * \param offset Distance the Collider should move to (if nothing collides)
         * \return The maximum distance the Collider can travel before colliding
         */
        [[nodiscard]] transform::UnitVector get_offset_before_collision(
            const Collider& collider,
            const transform::UnitVector& self_offset = transform::UnitVector(0, 0),
            const transform::UnitVector& other_offset = transform::UnitVector(0, 0)) const override;

        // Inherited via Collider
        virtual transform::AABB get_bounding_box() const override;
    };

}
