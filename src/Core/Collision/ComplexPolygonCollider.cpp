#include <Collision/ComplexPolygonCollider.hpp>

namespace obe::collision
{
    bool points_comparator(const transform::Vector2& first, const transform::Vector2& second)
    {
        if (first.x < second.x)
            return true;
        if (first.x == second.x)
            return first.y > second.y;
        return false;
    }

    double points_distance(const transform::Vector2& first, const transform::Vector2& second)
    {
        return std::sqrt(std::pow(second.x - first.x, 2) + std::pow(second.y - first.y, 2));
    }

    double cross(const transform::Vector2& O, const transform::Vector2& A,
        const transform::Vector2& B)
    {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }

    std::vector<transform::Vector2> convex_hull(std::vector<transform::Vector2> points)
    {
        std::sort(points.begin(), points.end(), points_comparator);
        if (points.size() <= 1)
            return points;
        std::vector<transform::Vector2> lower_hull;
        for (transform::Vector2& point : points)
        {
            while (lower_hull.size() >= 2
                && cross(
                       lower_hull[lower_hull.size() - 2], lower_hull[lower_hull.size() - 1], point)
                    <= 0)
                lower_hull.pop_back();
            lower_hull.push_back(point);
        }
        std::reverse(points.begin(), points.end());
        std::vector<transform::Vector2> upper_hull;
        for (transform::Vector2& point : points)
        {
            while (upper_hull.size() >= 2
                && cross(
                       upper_hull[upper_hull.size() - 2], upper_hull[upper_hull.size() - 1], point)
                    <= 0)
                upper_hull.pop_back();
            upper_hull.push_back(point);
        }
        std::vector<transform::Vector2> full_hull;
        full_hull.reserve(lower_hull.size() + upper_hull.size() - 2);
        full_hull.insert(full_hull.end(), lower_hull.begin(), lower_hull.end() - 1);
        full_hull.insert(full_hull.end(), upper_hull.begin(), upper_hull.end() - 1);
        return full_hull;
    }
}