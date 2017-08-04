#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Animation/Animator.hpp>
#include <Triggers/TriggerGroup.hpp>

namespace obe
{
    namespace System
    {
        /**
         * \brief An enum for Mouse buttons (Left-click / Right-click)
         */
        enum class MouseButton
        {
            Left,
            Right
        };

        enum class MouseButtonState
        {
            Idle,
            Hold,
            Pressed,
            Released
        };

        /**
         * \brief A Class to manipulate and display the Cursor in the Engine
         * @Bind
         */
        class Cursor
        {
        private:
            int m_x = 0;
            int m_y = 0;
            int m_constrainedX = 0;
            int m_constrainedY = 0;
            Triggers::TriggerGroupPtr m_cursorTriggers;
            std::function<std::pair<int, int>(Cursor*)> m_constraint;
        public:
            /**
             * \brief Creates a Cursor
             */
            explicit Cursor();
            /**
             * \brief Gets the x Coordinate of the Cursor Position (Constrained)
             * \return An int containing the x Coordinate of the Cursor Position
             */
            int getX() const;
            /**
            * \brief Gets the y Coordinate of the Cursor Position (Constrained)
            * \return An int containing the y Coordinate of the Cursor Position
            */
            int getY() const;
            /**
             * \brief Gets the x Coordinate of the raw (System) position of the Cursor (Unconstrained)
             * \return An int containing the x Coordinate of the Cursor Position
             */
            int getRawX() const;
            /**
            * \brief Gets the y Coordinate of the raw (System) position of the Cursor (Unconstrained)
            * \return An int containing the y Coordinate of the Cursor Position
            */
            int getRawY() const;
            /**
             * \brief Sets the x Coordinate of the Cursor Position
             * \param newx An int containing the x Coordinate of the new Cursor Position
             */
            void setX(unsigned int newx);
            /**
            * \brief Sets the y Coordinate of the Cursor Position
            * \param newy An int containing the y Coordinate of the new Cursor Position
            */
            void setY(unsigned int newy);
            /**
             * \brief Sets the Position of the Cursor
             * \param newx An int containing the x Coordinate of the new Cursor Position
             * \param newy An int containing the y Coordinate of the new Cursor Position
             */
            void setPosition(unsigned int newx, unsigned int newy);
            /**
             * \brief Updates the Cursor
             */
            void update();
            /**
             * \brief Sets the Cursor's constraint
             * \param constraint A function returning the constrained Position of the Cursor (a std::pair<int, int>) and taking the Cursor pointer in parameter
             */
            void setConstraint(std::function<std::pair<int, int>(Cursor*)> constraint);
        };

        /**
         * \brief Some Cursor default constraints
         */
        namespace Constraints
        {
            /**
             * \brief Unconstrained position
             */
            extern std::function<std::pair<int, int>(Cursor*)> Default;
        }
    }
}
