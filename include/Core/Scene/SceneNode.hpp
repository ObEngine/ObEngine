#pragma once

#include <Transform/Movable.hpp>
#include <Types/Selectable.hpp>
#include <vector>

namespace obe::scene
{
    /**
     * \brief A SceneNode holds objects inherited from Movable class and "links"
     * their position
     */
    class SceneNode : public transform::Movable
    {
    private:
        std::vector<transform::Movable*> m_children;

    public:
        /**
         * \brief Adds a child to the SceneNode
         * \param child Pointer to the new SceneNode child
         */
        void add_child(transform::Movable& child);
        /**
         * \brief Removes a child from the SceneNode
         * \param child Reference to the SceneNode child to remove
         */
        void remove_child(transform::Movable& child);
        /**
         * \brief Set the position of the SceneNode and all of its children
         *        using an Vector2
         * \param position Position to affect to the
         *        SceneNode and all of its children
         */
        void set_position(const transform::Vector2& position) override;
        /**
         * \brief Moves the SceneNode (Adds the given position to the current
         *        one) and all of its children
         * \param position Position to add to the current Position
         */
        void move(const transform::Vector2& position) override;
        /**
         * \brief Set the position of the SceneNode using an Vector2
         * \param position Position to affect to the SceneNode
         */
        void set_position_without_children(const transform::Vector2& position);
        /**
         * \brief Moves the SceneNode (Adds the given position to the current one)
         * \param position Position to add to the current Position
         */
        void move_without_children(const transform::Vector2& position);
    };
} // namespace obe::scene
