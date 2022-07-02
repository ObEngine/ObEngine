#pragma once

#include <Animation/Animator.hpp>
#include <Event/EventGroup.hpp>
#include <Event/EventNamespace.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Mouse.hpp>
#include <System/Window.hpp>
#include <Transform/UnitVector.hpp>
#include <map>

namespace obe::events
{
    namespace Cursor
    {
        struct Move
        {
            static constexpr std::string_view id = "Move";
            int x;
            int y;
            int previous_x;
            int previous_y;
        };

        struct Press
        {
            static constexpr std::string_view id = "Press";
            int x;
            int y;
            bool left;
            bool middle;
            bool right;
        };

        struct Hold
        {
            static constexpr std::string_view id = "Hold";
            int x;
            int y;
            bool left;
            bool middle;
            bool right;
        };

        struct Release
        {
            static constexpr std::string_view id = "Release";
            int x;
            int y;
            bool left;
            bool middle;
            bool right;
        };
    } // namespace Cursor
} // namespace obe::events

namespace obe::system
{
    enum class CursorType // taken from sf::Cursor::Type
    {
        Arrow, ///< Arrow cursor (default)
        ArrowWait, ///< Busy arrow cursor
        Wait, ///< Busy cursor
        Text, ///< I-beam, cursor when hovering over a field allowing text entry
        Hand, ///< Pointing hand cursor
        SizeHorizontal, ///< Horizontal double arrow cursor
        SizeVertical, ///< Vertical double arrow cursor
        SizeTopLeftBottomRight, ///< Double arrow cursor going from top-left to bottom-right
        SizeBottomLeftTopRight, ///< Double arrow cursor going from bottom-left to top-right
        SizeAll, ///< Combination of SizeHorizontal and SizeVertical
        Cross, ///< Crosshair cursor
        Help, ///< Help cursor
        NotAllowed ///< Action not allowed cursor
    };

    /**
    * \brief A Class to define a custom cursor. Used for System::Cursor.set_cursor()
    */
    class CursorModel
    {
    private:
        std::shared_ptr<sf::Cursor> m_cursor;

    public:
        /**
         * \brief Set cursor appearance and hotspot from an image file
         * \param filename Image file to use for the cursor
         * \param hotspot_x X coordinate on image (in pixels) of the cursor hotspot
         * \param hotspot_y Y coordinate on image (in pixels) of the cursor hotspot
         * \return true if loading succeeded, false otherwise
         */
        bool load_from_file(
            const std::string& filename, unsigned int hotspot_x, unsigned int hotspot_y);
        /**
         * \brief Loads a native system cursor
         * \param type Native system cursor type
         * \return true if loading succeeded, false otherwise
         */
        bool load_from_system(CursorType type);
        /**
         * \nobind
         * \brief Returns cursor shared pointer
         */
        [[nodiscard]] std::shared_ptr<sf::Cursor> get_ptr() const;
    };

    /**
     * \brief A Class to manipulate and display the Cursor in the Engine
     */
    class Cursor
    {
    private:
        sf::Vector2i m_old_position;
        int m_x = 0;
        int m_y = 0;
        int m_constrained_x = 0;
        int m_constrained_y = 0;
        bool m_visible = true;
        system::Window& m_window;
        event::EventGroupPtr e_cursor;
        std::function<std::pair<int, int>(Cursor*)> m_constraint;
        std::function<bool()> m_constraint_condition;
        std::map<sf::Mouse::Button, bool> m_button_state;
        std::shared_ptr<sf::Cursor> m_custom_cursor;

    public:
        using PositionConstraint = std::function<std::pair<int, int>(Cursor* cursor)>;
        using ConstraintCondition = std::function<bool()>;
        /**
         * \brief Creates a Cursor
         */
        explicit Cursor(system::Window& window, event::EventNamespace& event_namespace);
        /**
         * \brief Gets the x Coordinate of the Cursor Position (Constrained)
         * \return An int containing the x Coordinate of the Cursor Position
         */
        [[nodiscard]] int get_constrained_x() const;
        /**
         * \brief Gets the y Coordinate of the Cursor Position (Constrained)
         * \return An int containing the y Coordinate of the Cursor Position
         */
        [[nodiscard]] int get_constrained_y() const;
        /**
         * \brief Gets the x Coordinate of the raw (System) position of the
         *        Cursor (Unconstrained)
         * \return An int containing the x Coordinate of
         *         the Cursor Position
         */
        [[nodiscard]] int get_x() const;
        /**
         * \brief Gets the y Coordinate of the raw (System) position of the
         *        Cursor (Unconstrained)
         * \return An int containing the y Coordinate of
         *         the Cursor Position
         */
        [[nodiscard]] int get_y() const;
        /**
         * \brief Sets the x Coordinate of the Cursor Position
         * \param x An int containing the x Coordinate of the new Cursor
         *        Position
         */
        void set_x(int x);
        /**
         * \brief Sets the y Coordinate of the Cursor Position
         * \param y An int containing the y Coordinate of the new Cursor
         *        Position
         */
        void set_y(int y);
        /**
         * \brief Sets the Position of the Cursor
         * \param x An int containing the x Coordinate of the new Cursor
         *        Position
         * \param y An int containing the y Coordinate of the new
         *        Cursor Position
         */
        void set_position(int x, int y);

        void show();
        void hide();
        void set_visible(bool visible);
        [[nodiscard]] bool is_visible() const;

        [[nodiscard]] transform::UnitVector get_position() const;
        [[nodiscard]] transform::UnitVector get_scene_position() const;
        /**
         * \brief Updates the Cursor
         */
        void update();
        /**
         * \brief Sets the Cursor's constraint
         * \param constraint A function returning the constrained Position of
         *        the Cursor (x, y coordinates) and taking the Cursor pointer in
         *        parameter
         * \param condition condition for the constraint to apply
         */
        void set_constraint(
            const PositionConstraint& constraint,
            ConstraintCondition condition = []() { return true; });
        bool is_pressed(sf::Mouse::Button button) const;
        /**
         * \brief Change the cursor
         * \param new_cursor CursorModel defining the cursor to display
         */
        void set_cursor(const system::CursorModel& new_cursor);
    };

    /**
     * \brief Some Cursor default constraints
     */
    namespace constraints
    {
        /**
         * \brief Unconstrained position
         */
        extern std::function<std::pair<int, int>(Cursor*)> Default;
    } // namespace constraints
} // namespace obe::system