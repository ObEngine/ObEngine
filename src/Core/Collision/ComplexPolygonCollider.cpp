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
}