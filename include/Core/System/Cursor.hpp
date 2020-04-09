#pragma once

#include <map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

#include <Animation/Animator.hpp>
#include <System/Window.hpp>
#include <Transform/UnitVector.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Triggers/TriggerManager.hpp>

namespace obe::System
{
    /**
     * \brief A Class to manipulate and display the Cursor in the Engine
     */
    class Cursor
    {
    private:
        sf::Vector2i m_saveOldPos;
        int m_x = 0;
        int m_y = 0;
        int m_constrainedX = 0;
        int m_constrainedY = 0;
        bool m_visible = true;
        System::Window& m_window;
        Triggers::TriggerGroupPtr m_cursorTriggers;
        std::function<std::pair<int, int>(Cursor*)> m_constraint;
        std::function<bool()> m_constraintCondition;
        std::map<sf::Mouse::Button, bool> m_buttonState;

    public:
        /**
         * \brief Creates a Cursor
         */
        explicit Cursor(System::Window& window, Triggers::TriggerManager& triggers);
        /**
         * \brief Gets the x Coordinate of the Cursor Position (Constrained)
         * \return An int containing the x Coordinate of the Cursor Position
         */
        [[nodiscard]] int getConstrainedX() const;
        /**
         * \brief Gets the y Coordinate of the Cursor Position (Constrained)
         * \return An int containing the y Coordinate of the Cursor Position
         */
        [[nodiscard]] int getConstrainedY() const;
        /**
         * \brief Gets the x Coordinate of the raw (System) position of the
         *        Cursor (Unconstrained)
         * \return An int containing the x Coordinate of
         *         the Cursor Position
         */
        [[nodiscard]] int getX() const;
        /**
         * \brief Gets the y Coordinate of the raw (System) position of the
         *        Cursor (Unconstrained)
         * \return An int containing the y Coordinate of
         *         the Cursor Position
         */
        [[nodiscard]] int getY() const;
        /**
         * \brief Sets the x Coordinate of the Cursor Position
         * \param x An int containing the x Coordinate of the new Cursor
         *        Position
         */
        void setX(int x);
        /**
         * \brief Sets the y Coordinate of the Cursor Position
         * \param y An int containing the y Coordinate of the new Cursor
         *        Position
         */
        void setY(int y);
        /**
         * \brief Sets the Position of the Cursor
         * \param x An int containing the x Coordinate of the new Cursor
         *        Position
         * \param y An int containing the y Coordinate of the new
         *        Cursor Position
         */
        void setPosition(int x, int y);

        void show();
        void hide();
        void setVisible(bool visible);
        [[nodiscard]] bool isVisible() const;

        [[nodiscard]] Transform::UnitVector getPosition() const;
        /**
         * \brief Updates the Cursor
         */
        void update();
        /**
         * \brief Sets the Cursor's constraint
         * \param constraint A function returning the constrained Position of
         *        the Cursor (a std::pair<int, int>) and taking the Cursor pointer in
         *        parameter
         * \param condition condition for the constraint to apply
         */
        void setConstraint(
            std::function<std::pair<int, int>(Cursor*)> constraint,
            std::function<bool()> condition = []() { return true; });
        bool isPressed(sf::Mouse::Button button);
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
    } // namespace Constraints
} // namespace obe::System