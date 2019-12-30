#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <vector>

#include <Transform/Movable.hpp>
#include <Transform/Rect.hpp>
#include <Transform/UnitBasedObject.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::Transform
{
    class Polygon;

    using point_index_t = unsigned int;
    class PolygonPoint : public UnitVector
    {
    private:
        friend class Polygon;
        Polygon* m_parent;
        point_index_t rw_index;

    public:
        enum class RelativePositionFrom
        {
            Point0,
            Centroid
        };
        explicit PolygonPoint(Polygon* parent, unsigned int index);
        explicit PolygonPoint(Polygon* parent, unsigned int index,
            const Transform::UnitVector& position);
        const point_index_t& index = rw_index;
        void remove() const;
        double distance(const Transform::UnitVector& position) const;
        UnitVector getRelativePosition(RelativePositionFrom from) const;
        void setRelativePosition(
            RelativePositionFrom from, const Transform::UnitVector& position);
        void move(const Transform::UnitVector& position);
    };

    class PolygonSegment
    {
    public:
        const PolygonPoint& first;
        const PolygonPoint& second;
        double getAngle() const;
        double getLength() const;
        PolygonSegment(const PolygonPoint& first, const PolygonPoint& second);
    };

    using PolygonPath = std::vector<std::unique_ptr<PolygonPoint>>;

    /**
     * \brief Class used for all Collisions in the engine, it's a Polygon
     * containing n points
     * @Bind
     */
    class Polygon : public Transform::UnitBasedObject, public Transform::Movable
    {
    protected:
        friend class PolygonPoint;
        PolygonPath m_points;
        float m_angle = 0;

        void resetUnit(Transform::Units unit) override;

    public:
        static constexpr double DefaultTolerance = 0.02;
        /**
         * \brief Adds a new Point to the Polygon at Position (x, y)
         * \param position Coordinate of the Position where to add the new Point
         * \param pointIndex Index where to insert the new Point, Use pointIndex
         * = -1 <DefaultArg> to insert at the end (between last and first Point)
         */
        void addPoint(
            const Transform::UnitVector& position, int pointIndex = -1);
        /**
         * \brief Finds the closest Line from the given Position
         * \param position Position used to get the closest Line
         * \return The index of the line that is the closest one of the given
         * Position (Line between point 0 and point 1 is index 0)
         */
        PolygonSegment findClosestSegment(
            const Transform::UnitVector& position);
        /**
         * \brief Find the closest Point from the given Position(x, y)
         * \param position Coordinate of the Position used to get the closest
         * Point \param neighbor Get the closest neighboor of the closest Point
         * instead of the Point \param excludedPoints A std::vector containing
         * points you want to exclude from the calculus (Not used in neighboor
         * check step) \return The index of the Point (or one of its neighboor)
         * that is the closest one of the given Position
         */
        PolygonPoint& findClosestPoint(const Transform::UnitVector& position,
            bool neighbor = false,
            const std::vector<point_index_t>& excludedPoints = {});
        /**
         * \brief Get all the Points of the Polygon
         * \return A Path containing all the Points of the Polygon
         */
        PolygonPath& getAllPoints();
        /**
         * \brief Get the position of the Master Point (centroid) of the Polygon
         * \return An UnitVector containing the position of the Master Point
         * (centroid) of the Polygon
         */
        Transform::UnitVector getCentroid() const;
        /**
         * \brief Get the number of points in the Polygon
         * \return An unsigned int containing the number of points of the
         * Polygon
         */
        unsigned int getPointsAmount() const;
        /**
         * \brief Get the Position of the first point (index 0) of the Polygon
         * \return An UnitVector containing the position of the first point of
         * the Polygon
         */
        Transform::UnitVector getPosition() const override;
        /**
         * \brief Gets the current angle of the PolygonalCollider
         * \return A float containing the value of the current angle of the
         * PolygonalCollider
         */
        float getRotation() const;
        /*
         * \brief Gets the segment of the Polygon at index segment
         * \param segment Index of the Segment to get
         * \return The segment of the Polygon at index segment
         */
        PolygonSegment getSegment(point_index_t segment);
        /**
         * \brief Get if the Position (x, y) is on one of the side of the
         * Polygon \param position Coordinate of the Position to test \param
         * tolerance \return An unsigned int containing the index of the side
         * containing the position or -1 if not found
         */
        std::optional<PolygonSegment> getSegmentContainingPoint(
            const Transform::UnitVector& position,
            double tolerance = DefaultTolerance);
        /**
         * \brief Check if the MasterPoint of the Polygon is on Position (x -
         * tolerance <= x <= x + tolerance, y - tolerance <= tolerance <= y +
         * tolerance) \param position Coordinate of the Position to test \param
         * tolerance Position tolerance, bigger number means less precise
         * \return true if the MasterPoint is on the given Positon, false
         * otherwise
         */
        bool isCentroidAroundPosition(const Transform::UnitVector& position,
            const Transform::UnitVector& tolerance) const;
        /**
         * \brief Check if a point of the Polygon is on Position (x - tolerance
         * <= x <= x + tolerance, y - tolerance <= tolerance <= y + tolerance)
         * \param position Coordinate of the Position to test
         * \param tolerance Position tolerance, bigger number means less precise
         * \return An unsigned int containing the index of the point containing
         * the position or -1 if not found
         */
        std::optional<PolygonPoint*> getPointAroundPosition(
            const Transform::UnitVector& position,
            const Transform::UnitVector& tolerance);
        /**
         * \brief Moves the Polygon (relative to the current position)
         * \param position UnitVector containing the offset to move the Polygon
         */
        void move(const Transform::UnitVector& position) override;
        /**
         * \brief Adds an angle to the current angle of the PolygonalCollider
         * (will rotate all points around the given origin) \param angle Angle
         * to add to the PolygonalCollider \param origin Origin to rotate all
         * the points around
         */
        void rotate(float angle, Transform::UnitVector origin);
        /**
         * \brief Sets the new position of the Polygon (using the point at index
         * 0) \param position UnitVector containing the new Position of the
         * Polygon
         */
        void setPosition(const Transform::UnitVector& position) override;
        /**
         * \brief Sets the angle of the PolygonalCollider (will rotate all
         * points around the given origin) \param angle Angle to set to the
         * PolygonalCollider \param origin Origin to rotate all the points
         * around
         */
        void setRotation(float angle, Transform::UnitVector origin);
        void setPositionFromCentroid(const Transform::UnitVector& position);
        PolygonPoint& operator[](point_index_t i);
        PolygonPoint& get(point_index_t i);
        Rect getBoundingBox() const;
    };
} // namespace obe::Transform
