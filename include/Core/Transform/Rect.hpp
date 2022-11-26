#pragma once

#include <Graphics/RenderTarget.hpp>
#include <Transform/Movable.hpp>
#include <Transform/Referential.hpp>
#include <optional>

namespace obe::animation
{
    template <class T>
    class TweenImpl;
}

namespace obe::transform
{
    /**
     * \brief Conversion Type for Referential Usage
     */
    enum class ReferentialConversionType
    {
        /**
            * \brief Factor x1 (GetPosition)
            */
        From,
        /**
            * \brief Factor x-1 (SetPosition)
            */
        To
    };

    /**
     * \brief A Class that does represent a Rectangle with various methods to
     *        manipulate it
     */
    class Rect : public Movable
    {
        friend class animation::TweenImpl<Rect>;

    protected:
        /**
         * \brief Size of the Rect
         */
        Vector2 m_size;
        double m_angle = 0;

    public:
        using Movable::get_position;
        using Movable::move;
        using Movable::set_position;

        /**
         * \brief Transform the Vector2 passed by reference using the given
         * Referential
         * \param vec The Vector2 you want to transform
         * \param ref The chosen Rect::Referential
         * \param type The way you want to transform your Vector2
         *          - From : Referential::TopLeft to ref
         *          - To : ref to Referential::TopLeft
         */
        void transform_referential(
            Vector2& vec, const Referential& ref, ReferentialConversionType type) const;

        Rect() = default;
        Rect(const transform::Vector2& position, const transform::Vector2& size);
        /**
         * \brief Set the position of the Rect using an Vector2
         * \param position Position to affect to the Rect
         * \param ref Referential used to set the Position
         */
        void set_position(const Vector2& position, const Referential& ref);
        /**
         * \brief Get the Position of the Rect
         * \param ref Referential of the Rect you want to use to get the
         *        Position
         * \return The Position of the given Referential of the Rect
         */
        [[nodiscard]] Vector2 get_position(const Referential& ref) const;

        /**
         * \brief Set the Position of a specific Referential of the Rect (The
         *        opposite Point won't move)
         * \param position Position to affect to the specific Referential
         * \param ref Referential you want to move
         */
        void set_point_position(
            const Vector2& position, const Referential& ref = Referential::TopLeft);
        /**
         * \brief Move a specific Referential of the Rect (The opposite Point won't move)
         * \param position Position to add to the specific
         *        Referential
         * \param ref Referential you want to move
         */
        void move_point(const Vector2& position, const Referential& ref = Referential::TopLeft);

        /**
         * \brief Set the size of the Rect
         * \param size New size of the Rect
         * \param ref Referential used to resize the Rect (Referential that
         *        won't move)
         */
        void set_size(const Vector2& size, const Referential& ref = Referential::TopLeft);
        /**
         * \brief Scales the Rect (Relative to the current size)
         * \param size Size to multiply to the current size
         * \param ref Referential used to scale the Rect (Referential that won't
         *        move)
         */
        void scale(const Vector2& size, const Referential& ref = Referential::TopLeft);
        /**
         * \brief Get the Size of the Rect
         * \return An Vector2 containing the size of the Rect (Default Unit
         *         is SceneUnits)
         */
        [[nodiscard]] Vector2 get_size() const;
        /**
         * \brief Get the Scale Factor of the Rect
         * \return An Vector2 containing the Scale Factors of the Rect.
         *          - x attribute will be equal to -1 if the Rect is flipped
         *            horizontally, 1 otherwise.
         *          - y attribute will be equal to -1 if the
         *            Rect is flipped vertically, 1 otherwise.
         */
        [[nodiscard]] Vector2 get_scale_factor() const;
        [[nodiscard]] double get_rotation() const;
        void set_rotation(double angle, transform::Vector2 origin);
        void rotate(double angle, transform::Vector2 origin);
        /**
         * \brief Draws the Rect for debug purposes <REMOVE>
         */
        void draw(graphics::RenderTarget surface, int x, int y) const;

        /**
         * \asproperty
         */
        [[nodiscard]] double x() const;
        /**
         * \asproperty
         */
        [[nodiscard]] double y() const;
        /**
         * \asproperty
         */
        [[nodiscard]] double width() const;
        /**
         * \asproperty
         */
        [[nodiscard]] double height() const;
        /**
        * \brief Checks if the Rect intersects a specified Rect
        * \param rect The other Rect to check
        * \return true if the Rect intersects the other Rect, false otherwise
        */
        [[nodiscard]] bool intersects(const Rect& rect) const;
        [[nodiscard]] std::optional<Rect> intersection(const Rect& rect) const;
        [[nodiscard]] bool contains(const Rect& rect) const;
        [[nodiscard]] bool contains(const Vector2& position) const;
    };
} // namespace obe::transform
