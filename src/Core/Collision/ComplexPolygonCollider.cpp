#include <Collision/ComplexPolygonCollider.hpp>

namespace obe::collision
{
    bool points_comparator(const transform::UnitVector& first, const transform::UnitVector& second)
    {
        if (first.x < second.x)
            return true;
        if (first.x == second.x)
            return first.y > second.y;
        return false;
    }

    double points_distance(const transform::UnitVector& first, const transform::UnitVector& second)
    {
        return std::sqrt(std::pow(second.x - first.x, 2) + std::pow(second.y - first.y, 2));
    }

    double cross(const transform::UnitVector& O, const transform::UnitVector& A,
        const transform::UnitVector& B)
    {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }

    std::vector<transform::UnitVector> convex_hull(std::vector<transform::UnitVector> points)
    {
        std::sort(points.begin(), points.end(), points_comparator);
        if (points.size() <= 1)
            return points;
        std::vector<transform::UnitVector> lower_hull;
        for (transform::UnitVector& point : points)
        {
            while (lower_hull.size() >= 2
                && cross(
                       lower_hull[lower_hull.size() - 2], lower_hull[lower_hull.size() - 1], point)
                    <= 0)
                lower_hull.pop_back();
            lower_hull.push_back(point);
        }
        std::reverse(points.begin(), points.end());
        std::vector<transform::UnitVector> upper_hull;
        for (transform::UnitVector& point : points)
        {
            while (upper_hull.size() >= 2
                && cross(
                       upper_hull[upper_hull.size() - 2], upper_hull[upper_hull.size() - 1], point)
                    <= 0)
                upper_hull.pop_back();
            upper_hull.push_back(point);
        }
        std::vector<transform::UnitVector> full_hull;
        full_hull.reserve(lower_hull.size() + upper_hull.size() - 2);
        full_hull.insert(full_hull.end(), lower_hull.begin(), lower_hull.end() - 1);
        full_hull.insert(full_hull.end(), upper_hull.begin(), upper_hull.end() - 1);
        return full_hull;
    }

    const void* ComplexPolygonCollider::get_c2_shape() const
    {
        return nullptr;
    }

    const c2x* ComplexPolygonCollider::get_c2_space_transform() const
    {
        return nullptr;
    }

    ColliderType ComplexPolygonCollider::get_collider_type() const
    {
        return ComplexPolygonCollider::Type;
    }

    transform::UnitVector ComplexPolygonCollider::get_position() const
    {
        return m_points[0];
    }

    void ComplexPolygonCollider::set_position(const transform::UnitVector& position)
    {
        if (!m_points.empty())
        {
            const transform::UnitVector p_vec = position.to<transform::Units::SceneUnits>();
            const transform::UnitVector offset = p_vec - m_points[0];

            for (auto& point : m_points)
            {
                point += offset;
            }
        }
    }

    void ComplexPolygonCollider::move(const transform::UnitVector& position)
    {
        this->set_position(this->get_position() + position);
    }

    void ComplexPolygonCollider::add_point(const transform::UnitVector& position, int point_index)
    {
        const transform::UnitVector p_vec = position.to<transform::Units::SceneUnits>();
        if (point_index == -1 || point_index == m_points.size())
            m_points.push_back(p_vec);
        else if (point_index >= 0 && point_index < m_points.size())
        {
            m_points.insert(m_points.begin() + point_index, p_vec);
        }
    }

    std::size_t ComplexPolygonCollider::get_points_amount() const
    {
        return m_points.size();
    }

    bool ComplexPolygonCollider::collides(const Collider& collider) const
    {
        std::vector<transform::UnitVector> p_set1;
        p_set1.reserve(m_points.size());
        std::vector<transform::UnitVector> p_set2;
        p_set2.reserve(m_points.size());

        if (collider.get_collider_type() != ColliderType::ComplexPolygon)
        {
            return false;
        }

        const ComplexPolygonCollider& polygon_collider
            = static_cast<const ComplexPolygonCollider&>(collider);

        for (const auto& point : m_points)
            p_set1.push_back(point);
        for (const auto& point : polygon_collider.m_points)
            p_set2.push_back(point);
        constexpr auto point_in_polygon = [](const std::vector<transform::UnitVector>& poly,
                                              const transform::UnitVector& p_test) -> bool
        {
            int i, j, c = 0;
            const int n_pt = static_cast<int>(poly.size());
            for (i = 0, j = n_pt - 1; i < n_pt; j = i++)
            {
                if (((poly[i].y > p_test.y) != (poly[j].y > p_test.y))
                    && (p_test.x
                        < (poly[j].x - poly[i].x) * (p_test.y - poly[i].y) / (poly[j].y - poly[i].y)
                            + poly[i].x))
                    c = !c;
            }
            return c;
        };
        for (const transform::UnitVector& p_test : p_set1)
        {
            if (point_in_polygon(p_set2, p_test))
                return true;
        }
        for (const transform::UnitVector& p_test : p_set2)
        {
            if (point_in_polygon(p_set1, p_test))
                return true;
        }
    }

    transform::UnitVector ComplexPolygonCollider::get_offset_before_collision(
        const Collider& collider, const transform::UnitVector& self_offset,
        const transform::UnitVector& other_offset) const
    {
        constexpr transform::Units px_unit = transform::Units::ScenePixels;
        const transform::UnitVector t_offset = self_offset.to(px_unit);
        bool in_front = false;
        transform::UnitVector min_dep;
        const auto calc_min_distance_dep = [this](const std::vector<transform::UnitVector>& sol1,
                                               const std::vector<transform::UnitVector>& sol2,
                                               const transform::UnitVector& t_offset)
            -> std::tuple<double, transform::UnitVector, bool>
        {
            double min_distance = -1;
            bool in_front = false;

            constexpr transform::Units px_unit = transform::Units::ScenePixels;
            transform::UnitVector min_displacement(px_unit);
            transform::UnitVector point1(px_unit);
            transform::UnitVector point2(px_unit);
            transform::UnitVector point3(px_unit);
            transform::UnitVector s1(px_unit);
            for (auto& current_point : sol1)
            {
                const transform::UnitVector point0 = current_point.to(px_unit);
                for (int i = 0; i < sol2.size(); i++)
                {
                    point1 = point0 + t_offset;
                    point2 = sol2[i].to(px_unit);
                    point3 = sol2[(i == sol2.size() - 1) ? 0 : i + 1].to(px_unit);

                    s1 = point1 - point0;
                    const transform::UnitVector s2 = point3 - point2;

                    const double s = (-s1.y * (point0.x - point2.x) + s1.x * (point0.y - point2.y))
                        / (-s2.x * s1.y + s1.x * s2.y);
                    const double t = (s2.x * (point0.y - point2.y) - s2.y * (point0.x - point2.x))
                        / (-s2.x * s1.y + s1.x * s2.y);

                    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
                    {
                        in_front = true;
                        const transform::UnitVector ip
                            = point0 + (s1 * transform::UnitVector(t, t, s1.unit));

                        const double distance = std::sqrt(
                            std::pow((point0.x - ip.x), 2) + std::pow((point0.y - ip.y), 2));
                        if (distance < min_distance || min_distance == -1)
                        {
                            min_distance = distance;
                            const double x_comp = t * s1.x;
                            const double y_comp = t * s1.y;
                            min_displacement.set(
                                (x_comp > 0) ? std::floor(x_comp) : std::ceil(x_comp),
                                (y_comp > 0) ? std::floor(y_comp) : std::ceil(y_comp));
                        }
                    }
                }
            }
            return std::make_tuple(min_distance, min_displacement, in_front);
        };

        if (collider.get_collider_type() != ColliderType::ComplexPolygon)
        {
            return transform::UnitVector(0, 0);
        }

        const ComplexPolygonCollider& polygon_collider
            = static_cast<const ComplexPolygonCollider&>(collider);

        const std::vector<transform::UnitVector>& f_path = m_points;
        const std::vector<transform::UnitVector>& s_path = polygon_collider.m_points;

        const auto tdm1 = calc_min_distance_dep(f_path, s_path, t_offset);
        auto tdm2 = calc_min_distance_dep(
            s_path, f_path, t_offset * transform::UnitVector(-1.0, -1.0, t_offset.unit));
        std::get<1>(tdm2).x = -std::get<1>(tdm2).x;
        std::get<1>(tdm2).y = -std::get<1>(tdm2).y;
        if (std::get<2>(tdm1) || std::get<2>(tdm2))
            in_front = true;

        if (!in_front)
            min_dep = t_offset;
        else if (std::get<0>(tdm1) == 0 || std::get<0>(tdm2) == 0)
            return transform::UnitVector(0, 0, t_offset.unit);
        else if (std::get<0>(tdm1) > 0
            && (std::get<0>(tdm1) <= std::get<0>(tdm2) || std::get<0>(tdm2) == -1))
            min_dep = std::get<1>(tdm1);
        else if (std::get<0>(tdm2) > 0)
            min_dep = std::get<1>(tdm2);
        else
            return transform::UnitVector(0, 0, t_offset.unit);

        return min_dep;
    }

    transform::AABB ComplexPolygonCollider::get_bounding_box() const
    {
        // TODO: handle rotation
        auto [min_x, max_x] = std::minmax_element(m_points.begin(), m_points.end(),
            [](auto& point1, auto& point2)
            {
                return point1.x < point2.x;
            });
        auto [min_y, max_y] = std::minmax_element(m_points.begin(), m_points.end(),
            [](auto& point1, auto& point2)
            {
                return point1.y < point2.y;
            });
        const double width = max_x->x - min_x->x;
        const double height = max_y->y - min_y->y;
        return transform::AABB(
            transform::UnitVector(min_x->x, min_y->y), transform::UnitVector(width, height));
    }
}