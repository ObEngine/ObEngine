#pragma once

#include <vector>

#include <Transform/Movable.hpp>
#include <Types/Identifiable.hpp>

namespace obe
{
    namespace Transform
    {
        class Node2D : public Movable
        {
        private:
            std::vector<Movable*> m_children;
        public:
            Node2D(const std::string& id);
            /**
             * \brief Adds a child to the Node2D
             * \param child Pointer to the new Node2D child
             */
            void addChild(Movable* child);
            /**
            * \brief Set the position of the Node2D and all of its children using an UnitVector
            * \param position Position to affect to the Node2D and all of its children
            */
            void setPosition(const UnitVector& position) override;
            /**
            * \brief Moves the Node2D (Adds the given position to the current one) and all of its children
            * \param position Position to add to the current Position
            */
            void move(const UnitVector& position) override;
        };
    }
}
