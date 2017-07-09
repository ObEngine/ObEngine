#pragma once

#include <SFML/Graphics.hpp>

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

        /**
         * \brief A Class to manipulate and display the Cursor in the Engine
         */
        class Cursor
        {
        private:
            int m_x = 0;
            int m_y = 0;
            int m_constrainedX = 0;
            int m_constrainedY = 0;
            sf::RenderWindow* m_window = nullptr;
            bool m_leftPressed = false;
            bool m_rightPressed = false;
            bool m_leftClicked = false;
            bool m_rightClicked = false;
            bool m_leftReleased = false;
            bool m_rightReleased = false;
            Triggers::TriggerGroup::Ptr m_cursorTriggers;
            Animation::Animator m_cursorAnim;
            sf::Sprite m_cursorSprite;
            std::function<std::pair<int, int>(Cursor*)> m_constraint;
        public:
            /**
             * \brief Creates a Cursor
             * \param window Pointer to the sf::RenderWindow stored for internal usage
             */
            explicit Cursor(sf::RenderWindow* window);
            /**
             * \brief Sets the root path to the Cursor Animator
             * \param cursor Path to the Cursor Animator (Base root is Sprites/Cursors)
             */
            void selectAnimatorPath(const std::string& cursor);
            /**
             * \brief Sets the Animation Key (CLIC, HOLD, IDLE, RELEASE)
             * \param key Key of the Animation to set
             */
            void selectAnimationKey(const std::string& key);
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
             * \brief Handles the internal Cursor Triggers
             */
            void handleTriggers() const;
            /**
             * \brief Gets if one MouseButton is pressed
             * \param button The MouseButton to check (Left / Right)
             * \return true if the MouseButton is pressed, false otherwise
             */
            bool getPressed(MouseButton button) const;
            /**
            * \brief Gets if one MouseButton is clicked
            * \param button The MouseButton to check (Left / Right)
            * \return true if the MouseButton is clicked, false otherwise
            */
            bool getClicked(MouseButton button) const;
            /**
            * \brief Gets if one MouseButton is released
            * \param button The MouseButton to check (Left / Right)
            * \return true if the MouseButton is released, false otherwise
            */
            bool getReleased(MouseButton button) const;
            /**
             * \brief Sets the Cursor's constraint
             * \param constraint A function returning the constrained Position of the Cursor (a std::pair<int, int>) and taking the Cursor pointer in parameter
             */
            void setConstraint(std::function<std::pair<int, int>(Cursor*)> constraint);
            /**
             * \brief Displays the Cursor
             * \param target sf::RenderWindow where to render the Cursor
             */
            void display(sf::RenderWindow& target) const;
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
