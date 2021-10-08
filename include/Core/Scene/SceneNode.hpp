#pragma once

#include <vector>

#include <Transform/Movable.hpp>
#include <Types/Selectable.hpp>

namespace obe::Scene
{
    /**
     * \brief A SceneNode holds objects inherited from Movable class and "links"
     * their position
     */
    class SceneNode : public Transform::Movable, public Types::Selectable
    {
    private:
        std::vector<Movable*> m_children;

    public:
        /**
         * \brief Adds a child to the SceneNode
         * \param child Pointer to the new SceneNode child
         */
        void addChild(Movable& child);
        /**
         * \brief Removes a child from the SceneNode
         * \param child Reference to the SceneNode child to remove
         */
        void removeChild(Movable& child);
        /**
         * \brief Set the position of the SceneNode and all of its children
         *        using an UnitVector
         * \param position Position to affect to the
         *        SceneNode and all of its children
         */
        void setPosition(const Transform::UnitVector& position) override;
        /**
         * \brief Moves the SceneNode (Adds the given position to the current
         *        one) and all of its children
         * \param position Position to add to the current Position
         */
        void move(const Transform::UnitVector& position) override;
        /**
         * \brief Set the position of the SceneNode using an UnitVector
         * \param position Position to affect to the SceneNode
         */
        void setPositionWithoutChildren(const Transform::UnitVector& position);
        /**
         * \brief Moves the SceneNode (Adds the given position to the current one)
         * \param position Position to add to the current Position
         */
        void moveWithoutChildren(const Transform::UnitVector& position);
    };
} // namespace obe::Scene
