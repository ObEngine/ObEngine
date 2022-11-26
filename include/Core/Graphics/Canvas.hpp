#pragma once

#include <Debug/Logger.hpp>
#include <Graphics/Exceptions.hpp>
#include <Graphics/Shapes.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Text.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <Transform/Polygon.hpp>
#include <Types/Identifiable.hpp>
#include <sfe/RichText.hpp>
#include <string>
#include <vector>

namespace obe::graphics::canvas
{
    /**
     * \brief Type of the CanvasElement, used for identification
     * \lua_bind{Canvas.Type}
     */
    enum class CanvasElementType
    {
        CanvasElement,
        Line,
        Rectangle,
        Text,
        Circle,
        Polygon,
        Bezier,
        NinePatch
    };

    using CanvasElementTypeMeta = types::SmartEnum<CanvasElementType>;

    class Canvas;
    /**
     * \brief A Drawable Canvas Element
     */
    class CanvasElement : public types::ProtectedIdentifiable
    {
    public:
        static constexpr CanvasElementType Type = CanvasElementType::CanvasElement;

        /**
         * \nobind
         */
        Canvas& parent;
        int32_t layer = 1;
        bool visible = true;
        CanvasElementType type = CanvasElementType::CanvasElement;

        /**
         * \brief Create a new CanvasElement
         * \param parent Reference to the Canvas
         * \param id Id of the new CanvasElement
         */
        explicit CanvasElement(Canvas& parent, const std::string& id);
        /**
         * \brief Abstract draw method
         * \param target Target where to render the result
         */
        virtual void draw(RenderTarget target) = 0;

        ~CanvasElement() override = default;
        CanvasElement& operator=(CanvasElement&&) = delete;

        /**
         * \brief Change layer or object and will ask the Canvas to reorder
         *        elements automatically
         */
        void set_layer(unsigned int layer);

        using Ptr = std::unique_ptr<CanvasElement>;
    };

    /**
     * \brief A Canvas Line
     */
    class Line : public CanvasElement
    {
    public:
        transform::UnitVector p1;
        transform::UnitVector p2;
        unsigned int thickness = 1;
        Color p1_color;
        Color p2_color;
        static constexpr CanvasElementType Type = CanvasElementType::Line;

        /**
         * \brief Create a new Line
         * \param parent Reference to the Canvas
         * \param id Id of the new Line
         */
        explicit Line(Canvas& parent, const std::string& id);
        /**
         * \brief Draw the Line
         * \param target Target where to draw the Line to
         */
        void draw(RenderTarget target) override;
    };

    /**
     * \brief Base class for CanvasElement classes with a position attribute
     */
    class CanvasPositionable : public CanvasElement
    {
    public:
        transform::UnitVector position;
        CanvasPositionable(Canvas& parent, const std::string& id);
    };

    /**
     * \brief A Canvas Rectangle
     */
    class Rectangle : public CanvasPositionable
    {
    public:
        static constexpr CanvasElementType Type = CanvasElementType::Rectangle;

        shapes::Rectangle shape;
        transform::UnitVector size;
        /**
         * \brief Create a new Rectangle
         * \param parent Reference to the Canvas
         * \param id Id of the new Rectangle
         */
        explicit Rectangle(Canvas& parent, const std::string& id);
        /**
         * \brief Draw the Rectangle
         * \param target Target where to draw the Rectangle to
         */
        void draw(RenderTarget target) override;
    };

    /**
     * \brief Horizontal alignment state of Text
     * \lua_bind{Canvas.TextAlignment.Horizontal}
     */
    enum class TextHorizontalAlign
    {
        Left,
        Center,
        Right
    };

    /**
     * \brief Vertical alignment of Text
     * \lua_bind{Canvas.TextAlignment.Vertical}
     */
    enum class TextVerticalAlign
    {
        Top,
        Center,
        Bottom
    };

    /**
     * \brief A Canvas Text
     */
    class Text : public CanvasPositionable
    {
    public:
        static constexpr CanvasElementType Type = CanvasElementType::Text;

        std::string font_path;
        shapes::Text shape;
        TextHorizontalAlign h_align;
        TextVerticalAlign v_align;
        std::vector<graphics::Text> texts;
        /**
         * \brief Create a new Text
         * \param parent Reference to the Canvas
         * \param id Id of the new Text
         */
        explicit Text(Canvas& parent, const std::string& id);
        /**
         * \brief Draw the Text
         * \param target Target where to draw the Text to
         */
        void draw(RenderTarget target) override;
        void refresh();
        /**
         * \rename{text}
         * \asproperty
         * \brief Returns the current Text part
         */
        graphics::Text& current_text();
    };

    /**
     * \brief A Canvas Circle
     */
    class Circle : public CanvasPositionable
    {
    public:
        static constexpr CanvasElementType Type = CanvasElementType::Circle;

        shapes::Circle shape;
        /**
         * \brief Create a new Circle
         * \param parent Reference to the Canvas
         * \param id Id of the new Circle
         */
        explicit Circle(Canvas& parent, const std::string& id);
        /**
         * \brief Draw the Circle
         * \param target Target where to draw the Circle to
         */
        void draw(RenderTarget target) override;
    };

    /**
     * \brief A Canvas Polygon
     */
    class Polygon : public CanvasPositionable
    {
    public:
        static constexpr CanvasElementType Type = CanvasElementType::Polygon;

        shapes::Polygon shape;
        // transform::Polygon polygon;

        explicit Polygon(Canvas& parent, const std::string& id);

        void draw(RenderTarget target) override;
    };

    /**
     * \brief A Canvas Bezier Curve
     */
    class Bezier : public CanvasElement
    {
    public:
        static constexpr CanvasElementType Type = CanvasElementType::Bezier;
        std::vector<transform::UnitVector> points;
        std::vector<graphics::Color> colors;
        unsigned int precision = 10;

        explicit Bezier(Canvas& parent, const std::string& id);
        /**
         * \brief Draw the Bezier Curve
         * \param target Target where to draw the Sprite to
         */
        void draw(RenderTarget target) override;
    };

    /**
     * \brief A NinePatch sprite
     */
    class NinePatch : public CanvasPositionable
    {
    public:
        static constexpr CanvasElementType Type = CanvasElementType::NinePatch;

        shapes::NinePatch shape;

        explicit NinePatch(Canvas& parent, const std::string& id);
        /**
         * \brief Draw the NinePatch sprite
         * \param target Target where to draw the Sprite to
         */
        void draw(RenderTarget target) override;
    };

    /**
     * \brief A Canvas where you can draw CanvasElements
     * \helper{obe://Lib/Internal/Canvas.lua}
     */
    class Canvas
    {
    private:
        sf::RenderTexture m_canvas;
        std::vector<CanvasElement::Ptr> m_elements {};
        bool m_sort_required = true;
        void sort_elements();

    public:
        /**
         * \brief Create a new Canvas
         * \param width Width of the Canvas (in pixels)
         * \param height Height of the Canvas (in pixels)
         */
        Canvas(unsigned int width, unsigned int height);

        /**
         * \brief Adds a new CanvasElement of type T to the Canvas
         * \tparam T Class of the CanvasElement to add to the canvas
         * \param id Id of the new element to add to the canvas
         * \return a pointer to the newly created CanvasElement
         * \throw CanvasElementAlreadyExists if an element with
         *        the given id already exists in the Canvas
         *
         * \thints
         * \thint{Line, T=obe::graphics::canvas::Line}
         * \thint{Rectangle, T=obe::graphics::canvas::Rectangle}
         * \thint{Text, T=obe::graphics::canvas::Text}
         * \thint{Circle, T=obe::graphics::canvas::Circle}
         * \thint{Polygon, T=obe::graphics::canvas::Polygon}
         * \thint{Bezier, T=obe::graphics::canvas::Bezier}
         * \thint{NinePatch, T=obe::graphics::canvas::NinePatch}
         * \endthints
         *
         */
        template <class T>
        T& add(const std::string& id);

        /**
         * \brief Get a CanvasElement with the given id
         * \param id Id of the CanvasElement you want to retrieve
         * \return pointer to the CanvasElement with given id
         */
        CanvasElement* get(const std::string& id) const;

        /**
         * \brief Render all the Canvas content
         */
        void render();
        /**
         * \brief Clear all CanvasElement from the Canvas
         */
        void clear();
        /**
         * \brief Remove a CanvasElement from the Canvas
         * \param id Id of the CanvasElement to remove
         */
        void remove(const std::string& id);
        /**
         * \brief Get the current Texture of the Canvas
         * \return A reference to the current Texture of the Canvas
         */
        Texture get_texture() const;
        /**
         * \brief Ask the Canvas to sort elements for the next rendering
         */
        void requires_sort();
    };

    template <class T>
    inline T& Canvas::add(const std::string& id)
    {
        if (const auto existing_element = this->get(id); existing_element)
        {
            if (existing_element->type == T::Type)
            {
                debug::Log->warn("<Scene> CanvasElement '{0}' already exists !", id);
                return *static_cast<T*>(this->get(id));
            }
            else
            {
                throw exceptions::CanvasElementAlreadyExists(id,
                    CanvasElementTypeMeta::to_string(T::Type),
                    CanvasElementTypeMeta::to_string(existing_element->type), EXC_INFO);
            }
        }
        else
        {
            m_sort_required = true;
            std::unique_ptr<T> new_element = std::make_unique<T>(*this, id);
            auto insert_it = std::find_if(m_elements.begin(), m_elements.end(),
                [&new_element](
                    const CanvasElement::Ptr& elem) { return new_element->layer <= elem->layer; });
            auto elem_it = m_elements.insert(insert_it, std::move(new_element));
            return *static_cast<T*>(elem_it->get());
        }
    }
} // namespace obe::graphics::canvas
