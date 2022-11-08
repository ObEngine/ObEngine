#include <algorithm>
#include <cassert>

#include <Collision/Quadtree.hpp>

namespace obe::collision
{
    Quadtree::Quadtree(const transform::AABB& box)
        : m_box(box)
        , m_root(std::make_unique<Node>())
    {
    }

    bool Quadtree::is_leaf(const Node* node) const
    {
        return !static_cast<bool>(node->children[0]);
    }

    transform::AABB Quadtree::compute_box(const transform::AABB& box, int i) const
    {
        auto origin = box.get_position();
        auto child_size = box.get_size() / 2.0;
        switch (i)
        {
        // North West
        case 0:
            return transform::AABB(origin, child_size);
        // Norst East
        case 1:
            return transform::AABB(origin + transform::UnitVector(child_size.x, 0), child_size);
        // South West
        case 2:
            return transform::AABB(origin + transform::UnitVector(0, child_size.y), child_size);
        // South East
        case 3:
            return transform::AABB(origin + child_size, child_size);
        default:
            assert(false && "Invalid child index");
            return transform::AABB();
        }
    }

    int Quadtree::get_quadrant(
        const transform::AABB& node_box, const transform::AABB& value_box) const
    {
        auto center = node_box.get_position(transform::Referential::Center);
        // West
        if (value_box.get_position(transform::Referential::Right).x < center.x)
        {
            // North West
            if (value_box.get_position(transform::Referential::Bottom).y < center.y)
                return 0;
            // South West
            else if (value_box.get_position(transform::Referential::Top).y >= center.y)
                return 2;
            // Not contained in any quadrant
            else
                return -1;
        }
        // East
        else if (value_box.get_position(transform::Referential::Left).x >= center.x)
        {
            // North East
            if (value_box.get_position(transform::Referential::Bottom).y < center.y)
                return 1;
            // South East
            else if (value_box.get_position(transform::Referential::Top).y >= center.y)
                return 3;
            // Not contained in any quadrant
            else
                return -1;
        }
        // Not contained in any quadrant
        else
            return -1;
    }

    void Quadtree::add_internal(
        Node* node, std::size_t depth, const transform::AABB& box, const Collider* value)
    {
        assert(node != nullptr);
        assert(box.contains(value->get_bounding_box()));
        if (is_leaf(node))
        {
            // Insert the value in this node if possible
            if (depth >= MaxDepth || node->values.size() < Threshold)
                node->values.push_back(value);
            // Otherwise, we split and we try again
            else
            {
                split(node, box);
                add_internal(node, depth, box, value);
            }
        }
        else
        {
            auto i = get_quadrant(box, value->get_bounding_box());
            // Add the value in a child if the value is entirely contained in it
            if (i != -1)
                add_internal(node->children[static_cast<std::size_t>(i)].get(), depth + 1,
                    compute_box(box, i), value);
            // Otherwise, we add the value in the current node
            else
                node->values.push_back(value);
        }
    }

    void Quadtree::split(Node* node, const transform::AABB& box)
    {
        assert(node != nullptr);
        assert(is_leaf(node) && "Only leaves can be split");
        // Create children
        for (auto& child : node->children)
            child = std::make_unique<Node>();
        // Assign values to children
        auto new_values = std::vector<const Collider*>(); // New values for this node
        for (const auto& value : node->values)
        {
            auto i = get_quadrant(box, value->get_bounding_box());
            if (i != -1)
                node->children[static_cast<std::size_t>(i)]->values.push_back(value);
            else
                new_values.push_back(value);
        }
        node->values = std::move(new_values);
    }

    bool Quadtree::remove_internal(Node* node, const transform::AABB& box, const Collider* value)
    {
        assert(node != nullptr);
        assert(box.contains(value->get_bounding_box()));
        if (is_leaf(node))
        {
            // Remove the value from node
            remove_value(node, value);
            return true;
        }
        else
        {
            // Remove the value in a child if the value is entirely contained in it
            auto i = get_quadrant(box, value->get_bounding_box());
            if (i != -1)
            {
                if (remove_internal(node->children[static_cast<std::size_t>(i)].get(), compute_box(box, i),
                        value))
                    return try_merge(node);
            }
            // Otherwise, we remove the value from the current node
            else
                remove_value(node, value);
            return false;
        }
    }

    void Quadtree::remove_value(Node* node, const Collider* value)
    {
        // Find the value in node->values
        auto it = std::find_if(std::begin(node->values), std::end(node->values),
            [this, &value](const auto& rhs) { return value == rhs; });
        assert(it != std::end(node->values)
            && "Trying to remove a value that is not present in the node");
        // Swap with the last element and pop back
        *it = std::move(node->values.back());
        node->values.pop_back();
    }

    bool Quadtree::try_merge(Node* node)
    {
        assert(node != nullptr);
        assert(!is_leaf(node) && "Only interior nodes can be merged");
        auto nbValues = node->values.size();
        for (const auto& child : node->children)
        {
            if (!is_leaf(child.get()))
                return false;
            nbValues += child->values.size();
        }
        if (nbValues <= Threshold)
        {
            node->values.reserve(nbValues);
            // Merge the values of all the children
            for (const auto& child : node->children)
            {
                for (const auto& value : child->values)
                    node->values.push_back(value);
            }
            // Remove the children
            for (auto& child : node->children)
                child.reset();
            return true;
        }
        else
            return false;
    }

    void Quadtree::query_internal(Node* node, const transform::AABB& box,
        const transform::AABB& query_box, std::vector<const Collider*>& values) const
    {
        assert(node != nullptr);
        assert(query_box.intersects(box));
        for (const auto& value : node->values)
        {
            if (query_box.intersects(value->get_bounding_box()))
                values.push_back(value);
        }
        if (!is_leaf(node))
        {
            for (auto i = std::size_t(0); i < node->children.size(); ++i)
            {
                auto child_box = compute_box(box, static_cast<int>(i));
                if (query_box.intersects(child_box))
                    query_internal(node->children[i].get(), child_box, query_box, values);
            }
        }
    }

    void Quadtree::find_all_intersections_internal(
        Node* node, std::vector<std::pair<const Collider*, const Collider*>>& intersections) const
    {
        // Find intersections between values stored in this node
        // Make sure to not report the same intersection twice
        for (auto i = std::size_t(0); i < node->values.size(); ++i)
        {
            for (auto j = std::size_t(0); j < i; ++j)
            {
                if (node->values[i]->get_bounding_box().intersects(
                        node->values[j]->get_bounding_box()))
                    intersections.emplace_back(node->values[i], node->values[j]);
            }
        }
        if (!is_leaf(node))
        {
            // Values in this node can intersect values in descendants
            for (const auto& child : node->children)
            {
                for (const auto& value : node->values)
                    find_intersections_in_descendants(child.get(), value, intersections);
            }
            // Find intersections in children
            for (const auto& child : node->children)
                find_all_intersections_internal(child.get(), intersections);
        }
    }

    void Quadtree::find_intersections_in_descendants(Node* node, const Collider* value,
        std::vector<std::pair<const Collider*, const Collider*>>& intersections) const
    {
        // Test against the values stored in this node
        for (const auto& other : node->values)
        {
            if (value->get_bounding_box().intersects(other->get_bounding_box()))
                intersections.emplace_back(value, other);
        }
        // Test against values stored into descendants of this node
        if (!is_leaf(node))
        {
            for (const auto& child : node->children)
                find_intersections_in_descendants(child.get(), value, intersections);
        }
    }

    void Quadtree::add(const Collider* value)
    {
        add_internal(m_root.get(), 0, m_box, value);
    }

    void Quadtree::remove(const Collider* value)
    {
        remove_internal(m_root.get(), m_box, value);
    }

    std::vector<const Collider*> Quadtree::query(const transform::AABB& box) const
    {
        auto values = std::vector<const Collider*>();
        query_internal(m_root.get(), m_box, box, values);
        return values;
    }

    std::vector<std::pair<const Collider*, const Collider*>>
    Quadtree::find_all_intersections() const
    {
        auto intersections = std::vector<std::pair<const Collider*, const Collider*>>();
        find_all_intersections_internal(m_root.get(), intersections);
        return intersections;
    }
}