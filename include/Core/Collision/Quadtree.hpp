#pragma once

#include <array>
#include <memory>
#include <vector>

#include <Collision/Collider.hpp>
#include <Transform/AABB.hpp>

namespace obe::collision
{
    class Quadtree
    {
    private:
        static constexpr auto Threshold = std::size_t(16);
        static constexpr auto MaxDepth = std::size_t(8);

        struct Node
        {
            std::array<std::unique_ptr<Node>, 4> children;
            std::vector<const Collider*> values;
        };

        transform::AABB m_box;
        std::unique_ptr<Node> m_root;

    protected:
        bool is_leaf(const Node* node) const;
        transform::AABB compute_box(const transform::AABB& box, int i) const;
        int get_quadrant(const transform::AABB& nodeBox, const transform::AABB& valueBox) const;
        void add_internal(
            Node* node, std::size_t depth, const transform::AABB& box, const Collider* value);
        void split(Node* node, const transform::AABB& box);
        bool remove_internal(Node* node, const transform::AABB& box, const Collider* value);
        void remove_value(Node* node, const Collider* value);
        bool try_merge(Node* node);
        void query_internal(Node* node, const transform::AABB& box,
            const transform::AABB& query_box, std::vector<const Collider*>& values) const;
        void find_all_intersections_internal(Node* node,
            std::vector<std::pair<const Collider*, const Collider*>>& intersections) const;
        void find_intersections_in_descendants(Node* node, const Collider* value,
            std::vector<std::pair<const Collider*, const Collider*>>& intersections) const;

    public:
        Quadtree(const transform::AABB& box);
        void clear();
        void add(const Collider* value);
        void remove(const Collider* value);
        std::vector<const Collider*> query(const transform::AABB& box) const;
        std::vector<std::pair<const Collider*, const Collider*>> find_all_intersections() const;
    };

}
