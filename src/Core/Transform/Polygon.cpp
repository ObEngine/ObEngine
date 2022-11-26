#include <Transform/Exceptions.hpp>
#include <Transform/Polygon.hpp>
#include <Utils/MathUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::transform
{
    PolygonPoint::PolygonPoint(Polygon& parent, std::size_t index)
        : m_parent(parent)
        , rw_index(index)
    {
    }

    PolygonPoint::PolygonPoint(
        Polygon& parent, std::size_t index, const transform::Vector2& position)
        : PolygonPoint(parent, index)
    {
        this->x = position.x;
        this->y = position.y;
    }

    PolygonPoint& PolygonPoint::operator=(const PolygonPoint& point)
    {
        this->x = point.x;
        this->y = point.y;
        this->rw_index = point.rw_index;
        return *this;
    }

    void PolygonPoint::remove() const
    {
        m_parent.m_points.erase(m_parent.m_points.begin() + index);
        for (point_index_t i = index; i < m_parent.m_points.size(); i++)
            m_parent.m_points[i].rw_index = i;
    }

    double PolygonPoint::distance(const transform::Vector2& position) const
    {
        const transform::Vector2 p_vec = position.to<transform::Units::SceneUnits>();
        return std::sqrt(std::pow((p_vec.x - x), 2) + std::pow((p_vec.y - y), 2));
    }

    Vector2 PolygonPoint::get_relative_position(RelativePositionFrom from) const
    {
        if (from == RelativePositionFrom::Point0)
            return (*this - m_parent.get(0));
        else
            return (*this - m_parent.get_centroid());
    }

    void PolygonPoint::set_relative_position(
        RelativePositionFrom from, const transform::Vector2& position)
    {
        if (from == RelativePositionFrom::Point0)
            this->set(position.to<transform::Units::SceneUnits>() + m_parent.get(0));
        else if (from == RelativePositionFrom::Centroid)
        {
            const transform::Vector2 centroid = m_parent.get_centroid();
            this->set(position.to<transform::Units::SceneUnits>() + centroid);
        }
    }

    void PolygonPoint::move(const transform::Vector2& position)
    {
        this->add(position);
    }

    PolygonSegment::PolygonSegment(const PolygonPoint& first, const PolygonPoint& second)
        : first(first)
        , second(second)
    {
    }

    double PolygonSegment::get_angle() const
    {
        const double delta_x = second.x - first.x;
        const double delta_y
            = first.y - second.y; // inverse y to get angle in counterclockwise direction
        return (std::atan2(delta_y, delta_x) * 180.0 / utils::math::pi);
    }

    double PolygonSegment::get_length() const
    {
        return first.distance(second);
    }

    std::size_t Polygon::get_points_amount() const
    {
        return m_points.size();
    }

    Polygon::Polygon(const Polygon& polygon)
        : m_angle(polygon.m_angle)
    {
        size_t index = 0;
        for (const auto& point : polygon.m_points)
        {
            m_points.push_back(transform::PolygonPoint(
                *this, index++, transform::Vector2(point.x, point.y, point.unit)));
        }
    }

    void Polygon::add_point(const transform::Vector2& position, int point_index)
    {
        const transform::Vector2 p_vec = position.to<transform::Units::SceneUnits>();
        if (point_index == -1 || point_index == m_points.size())
            m_points.push_back(PolygonPoint(*this, m_points.size(), p_vec));
        else if (point_index >= 0 && point_index < m_points.size())
        {
            m_points.insert(m_points.begin() + point_index,
                PolygonPoint(*this, point_index, p_vec));
            for (point_index_t i = point_index; i < m_points.size(); i++)
                m_points[i].rw_index = i;
        }
    }

    PolygonPoint& Polygon::find_closest_point(const transform::Vector2& position, bool neighbor,
        const std::vector<point_index_t>& excluded_points)
    {
        if (!m_points.empty())
        {
            const transform::Vector2 p_vec = position.to<transform::Units::SceneUnits>();
            int closest_point = 0;
            double shortest_distance = -1;
            for (std::size_t i = 0; i < m_points.size(); i++)
            {
                const double current_point_distance = m_points[i].distance(p_vec);
                if ((shortest_distance == -1 || shortest_distance > current_point_distance)
                    && !utils::vector::contains(i, excluded_points))
                {
                    closest_point = i;
                    shortest_distance = current_point_distance;
                }
            }
            if (neighbor)
            {
                int left_neighbor = closest_point - 1;
                int right_neighbor = closest_point + 1;
                if (left_neighbor < 0)
                    left_neighbor = m_points.size() - 1;
                if (right_neighbor >= m_points.size())
                    right_neighbor = 0;
                const int left_neighbor_distance = m_points[left_neighbor].distance(position);
                const int right_neighbor_distance = m_points[right_neighbor].distance(position);
                if (left_neighbor_distance > right_neighbor_distance)
                {
                    closest_point++;
                    if (closest_point >= m_points.size())
                        closest_point = 0;
                }
            }
            return m_points[closest_point];
        }
        throw exceptions::PolygonNotEnoughPoints(this, m_points.size(), EXC_INFO);
    }

    PolygonPath& Polygon::get_all_points()
    {
        return m_points;
    }

    PolygonSegment Polygon::find_closest_segment(const transform::Vector2& position)
    {
        const transform::Vector2 p3 = position.to<transform::Units::SceneUnits>();
        constexpr auto distance_line_from_point
            = [](const transform::Vector2& point, const transform::Vector2& line_p1,
                  const transform::Vector2& line_p2) {
                  transform::Vector2 line_diff = line_p2 - line_p1;
                  if (line_diff.x == 0 && line_diff.y == 0)
                  {
                      line_diff = point - line_p1;
                      return sqrt(line_diff.x * line_diff.x + line_diff.y * line_diff.y);
                  }

                  const double t
                      = ((point.x - line_p1.x) * line_diff.x + (point.y - line_p1.y) * line_diff.y)
                      / (line_diff.x * line_diff.x + line_diff.y * line_diff.y);

                  if (t < 0)
                  {
                      // point is nearest to the first point i.e x1 and y1
                      line_diff = point - line_p1;
                  }
                  else if (t > 1)
                  {
                      // point is nearest to the end point i.e x2 and y2
                      line_diff = point - line_p2;
                  }
                  else
                  {
                      // if perpendicular line intersect the line segment.
                      line_diff.x = point.x - (line_p1.x + t * line_diff.x);
                      line_diff.y = point.y - (line_p1.y + t * line_diff.y);
                  }

                  // returning shortest distance
                  return sqrt(line_diff.x * line_diff.x + line_diff.y * line_diff.y);
              };
        double shortest_distance = -1;
        std::size_t shortest_index = 0;
        for (std::size_t i = 0, j = get_all_points().size() - 1; i < get_all_points().size();
             j = i++)
        {
            const double current_distance
                = distance_line_from_point(p3, this->get(i), this->get(j));
            if (shortest_distance == -1 || current_distance < shortest_distance)
            {
                shortest_distance = current_distance;
                shortest_index = i;
            }
        }
        return this->get_segment(shortest_index);
    }

    std::optional<PolygonSegment> Polygon::get_segment_containing_point(
        const transform::Vector2& position, const double tolerance)
    {
        for (point_index_t i = 0; i < m_points.size(); i++)
        {
            const point_index_t next_node = (i != m_points.size() - 1) ? i + 1 : 0;
            const double line_length = m_points[i].distance(this->get(next_node));
            const double first_length = m_points[i].distance(position);
            const double second_length = m_points[next_node].distance(position);
            if (utils::math::is_between(line_length, first_length + second_length - tolerance,
                    first_length + second_length + tolerance))
                return std::make_optional(this->get_segment(i));
        }
        return std::nullopt;
    }

    const PolygonPath& Polygon::get_all_points() const
    {
        return m_points;
    }

    Vector2 Polygon::get_centroid() const
    {
        transform::Vector2 centroid = { 0, 0 };
        double signed_area = 0.0;
        double x0, y0, x1, y1, a;

        std::size_t i;
        for (i = 0; i < m_points.size() - 1; ++i)
        {
            x0 = m_points[i].x;
            y0 = m_points[i].y;
            x1 = m_points[i + 1].x;
            y1 = m_points[i + 1].y;
            a = x0 * y1 - x1 * y0;
            signed_area += a;
            centroid.x += (x0 + x1) * a;
            centroid.y += (y0 + y1) * a;
        }

        x0 = m_points[i].x;
        y0 = m_points[i].y;
        x1 = m_points[0].x;
        y1 = m_points[0].y;
        a = x0 * y1 - x1 * y0;
        signed_area += a;
        centroid.x += (x0 + x1) * a;
        centroid.y += (y0 + y1) * a;

        signed_area *= 0.5;
        centroid.x /= (6.0 * signed_area);
        centroid.y /= (6.0 * signed_area);

        return centroid;
    }

    std::optional<const PolygonPoint*> Polygon::get_point_near_position(
        const transform::Vector2& position, const transform::Vector2& tolerance) const
    {
        const transform::Vector2 p_vec = position.to<transform::Units::SceneUnits>();
        const transform::Vector2 p_tolerance = tolerance.to<transform::Units::SceneUnits>();
        point_index_t i = 0;
        for (auto& point : m_points)
        {
            if (utils::math::is_between(
                    p_vec.x, point.x - p_tolerance.x, point.x + p_tolerance.x))
            {
                if (utils::math::is_between(
                        p_vec.y, point.y - p_tolerance.y, point.y + p_tolerance.y))
                    return std::optional<const PolygonPoint*>(&point);
            }
            i++;
        }
        return std::nullopt;
    }

    bool Polygon::is_centroid_near_position(
        const transform::Vector2& position, const transform::Vector2& tolerance) const
    {
        const transform::Vector2 p_vec = position.to<transform::Units::SceneUnits>();
        const transform::Vector2 p_tolerance = tolerance.to<transform::Units::SceneUnits>();
        const transform::Vector2 centroid = this->get_centroid();
        if (utils::math::is_between(
                p_vec.x, centroid.x - p_tolerance.x, centroid.x + p_tolerance.x))
        {
            if (utils::math::is_between(
                    p_vec.y, centroid.y - p_tolerance.x, centroid.y + p_tolerance.y))
                return true;
        }
        return false;
    }

    PolygonSegment Polygon::get_segment(const point_index_t segment)
    {
        point_index_t p2 = segment + 1;
        if (segment == m_points.size() - 1)
            p2 = 0;
        return PolygonSegment(this->get(segment), this->get(p2));
    }

    Vector2 Polygon::get_position() const
    {
        return static_cast<Vector2>(m_points[0]);
    }

    void Polygon::set_rotation(const float angle, const transform::Vector2 origin)
    {
        this->rotate(angle - m_angle, origin);
    }

    float Polygon::get_rotation() const
    {
        return m_angle;
    }

    void Polygon::rotate(float angle, transform::Vector2 origin)
    {
        m_angle += angle;

        const double rad_angle = (utils::math::pi / 180.0) * -angle;
        for (auto& point : m_points)
        {
            point.set(std::cos(rad_angle) * (point.x - origin.x)
                    - std::sin(rad_angle) * (point.y - origin.y) + origin.x,
                std::sin(rad_angle) * (point.x - origin.x)
                    + std::cos(rad_angle) * (point.y - origin.y) + origin.y);
        }
    }

    void Polygon::move(const transform::Vector2& position)
    {
        if (!m_points.empty())
        {
            for (auto& point : m_points)
                point += position;
        }
    }

    void Polygon::set_position(const transform::Vector2& position)
    {
        if (!m_points.empty())
        {
            const transform::Vector2 p_vec = position.to<transform::Units::SceneUnits>();
            const transform::Vector2 offset = p_vec - m_points[0];

            for (auto& point : m_points)
            {
                point += offset;
            }
        }
    }

    void Polygon::set_position_from_centroid(const transform::Vector2& position)
    {
        if (!m_points.empty())
        {
            const transform::Vector2 p_vec = position.to<transform::Units::SceneUnits>();
            const transform::Vector2 centroid = this->get_centroid();
            const transform::Vector2 offset = p_vec - centroid;

            for (auto& point : m_points)
            {
                point += offset;
            }
        }
    }

    PolygonPoint& Polygon::operator[](point_index_t i)
    {
        return this->get(i);
    }

    PolygonPoint& Polygon::get(point_index_t i)
    {
        if (i < m_points.size())
            return m_points[i];
        else
            throw exceptions::PolygonPointIndexOverflow(this, i, m_points.size(), EXC_INFO);
    }

    const PolygonPoint& Polygon::get(point_index_t i) const
    {
        if (i < m_points.size())
            return m_points[i];
        else
            throw exceptions::PolygonPointIndexOverflow(this, i, m_points.size(), EXC_INFO);
    }

    Rect Polygon::get_bounding_box() const
    {
        auto [min_x, max_x] = std::minmax_element(m_points.begin(), m_points.end(),
            [](auto& point1, auto& point2) { return point1.x < point2.x; });
        auto [min_y, max_y] = std::minmax_element(m_points.begin(), m_points.end(),
            [](auto& point1, auto& point2) { return point1.y < point2.y; });
        const double width = max_x->x - min_x->x;
        const double height = max_y->y - min_y->y;
        return Rect(transform::Vector2(min_x->x, min_y->y),
            transform::Vector2(width, height));
    }
} // namespace obe::transform
