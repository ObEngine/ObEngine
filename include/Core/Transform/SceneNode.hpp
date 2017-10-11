#pragma once

#include <vector>

#include <Transform/Movable.hpp>
#include <Types/Identifiable.hpp>

namespace obe
{
    namespace Transform
    {
        /**
         * \brief A SceneNode holds objects herited from Movable class and "links" their position
         */
        class SceneNode : public Movable
        {
        private:
            std::vector<Movable*> m_children;
        public:
            SceneNode(const std::string& id);
            /**
             * \brief Adds a child to the SceneNode
             * \param child Pointer to the new SceneNode child
             */
            void addChild(Movable* child);
            /**
            * \brief Set the position of the SceneNode and all of its children using an UnitVector
            * \param position Position to affect to the SceneNode and all of its children
            */
            void setPosition(const UnitVector& position) override;
            /**
            * \brief Moves the SceneNode (Adds the given position to the current one) and all of its children
            * \param position Position to add to the current Position
            */
            void move(const UnitVector& position) override;
        };
    }
}
