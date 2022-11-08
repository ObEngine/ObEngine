#pragma once

#include <Collision/Collider.hpp>
#include <Transform/Polygon.hpp>

namespace obe::collision
{
    class PolygonCollider : public Collider
    {
    private:
        c2Poly m_shape = {};
        c2x m_transform;
        float m_angle = 0;

    protected:
        [[nodiscard]] const void* get_c2_shape() const override;
        [[nodiscard]] const c2x* get_c2_space_transform() const override;
        void update_transform();
        void update_shape();

    public:
        static constexpr ColliderType Type = ColliderType::Polygon;
        [[nodiscard]] ColliderType get_collider_type() const override;

        PolygonCollider();
        explicit PolygonCollider(const transform::UnitVector& position);

        [[nodiscard]] transform::AABB get_bounding_box() const override;
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
        transform::Polygon get_polygon() const;

        /**
         * \brief Sets the angle of the PolygonalCollider (will rotate all
         *        points around the given origin)
         * \param angle Angle to set to the PolygonalCollider
         */
        virtual void set_rotation(float angle);
        /**
         * \brief Adds an angle to the current angle of the PolygonalCollider
         *        (will rotate all points around the given origin)
         * \param angle Angle to add to the PolygonalCollider
         */
        virtual void rotate(float angle);
        /**
         * \brief Gets the current angle of the PolygonalCollider
         * \return A float containing the value of the current angle of the
         *         PolygonalCollider
         */
        [[nodiscard]] float get_rotation() const;
    };

}
