#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics/RenderTexture.hpp>
#include <sfe/RichText.hpp>

#include <Debug/Logger.hpp>
#include <Graphics/Sprite.hpp>
#include <Transform/Polygon.hpp>
#include <Types/Identifiable.hpp>

namespace obe::Graphics::Canvas
{
    /*
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
        Sprite
    };

    class Canvas;
    /**
     * \brief A Drawable Canvas Element
     * \lua_bind{Canvas.Element}
     */
    class CanvasElement : public Types::ProtectedIdentifiable
    {
    public:
        static const CanvasElementType Type = CanvasElementType::CanvasElement;

        Canvas* parent;
        unsigned int layer = 1;
        bool visible = true;
        CanvasElementType type;

        /**
         * \brief Create a new CanvasElement
         * \param parent Pointer to the Canvas
         * \param id Id of the new CanvasElement
         */
        explicit CanvasElement(Canvas* parent, const std::string& id);
        /**
         * \brief Abstract draw method
         * \param target Target where to render the result
         */
        virtual void draw(sf::RenderTexture& target) = 0;
        virtual ~CanvasElement();

        /*
         * \brief Change layer or object and will ask the Canvas to reorder
         * elements automatically
         */
        void setLayer(unsigned int layer);

        using Ptr = std::unique_ptr<CanvasElement>;
    };

    /**
     * \brief A Canvas Line
     * \lua_bind{Canvas.Line}
     */
    class Line : public CanvasElement
    {
    public:
        Transform::UnitVector p1;
        Transform::UnitVector p2;
        unsigned int thickness = 1;
        sf::Color p1color;
        sf::Color p2color;
        static const CanvasElementType Type = CanvasElementType::Line;

        /**
         * \brief Create a new Line
         * \param parent Pointer to the Canvas
         * \param id Id of the new Line
         */
        explicit Line(Canvas* parent, const std::string& id);
        /**
         * \brief Draw the Line
         * \param target Target where to draw the Line to
         */
        void draw(sf::RenderTexture& target) override;
    };

    /*
     * \brief Base class for CanvasElement classes with a position attribute
     * \lua_bind{Canvas.Positionable}
     */
    class CanvasPositionable : public CanvasElement
    {
    public:
        Transform::UnitVector position;
        CanvasPositionable(Canvas* parent, const std::string& id);
    };

    /**
     * \brief A Canvas Rectangle
     * \lua_bind{Canvas.Rectangle}
     */
    class Rectangle : public CanvasPositionable
    {
    public:
        static const CanvasElementType Type = CanvasElementType::Rectangle;

        sf::RectangleShape shape;
        Transform::UnitVector size;
        /**
         * \brief Create a new Rectangle
         * \param parent Pointer to the Canvas
         * \param id Id of the new Rectangle
         */
        explicit Rectangle(Canvas* parent, const std::string& id);
        /**
         * \brief Draw the Rectangle
         * \param target Target where to draw the Rectangle to
         */
        void draw(sf::RenderTexture& target) override;
    };

    /*
     * \brief Horizontal Alignment state of Text
     * \lua_bind{Canvas.Text.Alignment.Horizontal}
     */
    enum class TextHorizontalAlign
    {
        Left,
        Center,
        Right
    };

    /*
     * \brief Vertical Aligment of Text
     * \lua_bind{Canvas.Text.Alignment.Vertical}
     */
    enum class TextVerticalAlign
    {
        Top,
        Center,
        Bottom
    };

    /**
     * \brief A Canvas Text
     * \lua_bind{Canvas.Text}
     */
    class Text : public CanvasPositionable
    {
    public:
        static const CanvasElementType Type = CanvasElementType::Text;

        std::string fontPath;
        sfe::RichText shape;
        TextHorizontalAlign h_align;
        TextVerticalAlign v_align;
        /**
         * \brief Create a new Text
         * \param parent Pointer to the Canvas
         * \param id Id of the new Text
         */
        explicit Text(Canvas* parent, const std::string& id);
        /**
         * \brief Draw the Text
         * \param target Target where to draw the Text to
         */
        void draw(sf::RenderTexture& target) override;
    };

    /**
     * \brief A Canvas Circle
     * \lua_bind{Canvas.Circle}
     */
    class Circle : public CanvasPositionable
    {
    public:
        static const CanvasElementType Type = CanvasElementType::Circle;

        sf::CircleShape shape;
        float radius = 1;
        /**
         * \brief Create a new Circle
         * \param parent Pointer to the Canvas
         * \param id Id of the new Circle
         */
        explicit Circle(Canvas* parent, const std::string& id);
        /**
         * \brief Draw the Circle
         * \param target Target where to draw the Circle to
         */
        void draw(sf::RenderTexture& target) override;
    };

    /*
     * \brief A Canvas Polygon
     * \lua_bind{Canvas.Polygon}
     */
    class Polygon : public CanvasPositionable
    {
        static const CanvasElementType Type = CanvasElementType::Polygon;

        sf::ConvexShape shape;
        Transform::Polygon polygon;

        explicit Polygon(Canvas* parent, const std::string& id);

        void draw(sf::RenderTexture& target) override;
    };

    /*
     * \brief A Canvas Image
     * \lua_bind{Canvas.Sprite}
     */
    class Image : public CanvasPositionable
    {
    public:
        static const CanvasElementType Type = CanvasElementType::Sprite;

        std::string path;
        sfe::ComplexSprite sprite;
        explicit Image(Canvas* parent, const std::string& id);
        /**
         * \brief Draw the Sprite
         * \param target Target where to draw the Sprite to
         */
        void draw(sf::RenderTexture& target) override;
    };

    /**
     * \brief A Canvas where you can draw CanvasElements on
     * \lua_bind{Canvas.Canvas}
     */
    class Canvas
    {
    private:
        Graphics::Sprite* m_target = nullptr;
        sf::RenderTexture m_canvas;
        std::vector<CanvasElement::Ptr> m_elements;
        bool m_sortRequired = true;
        void sortElements();

    public:
        /**
         * \brief Create a new Canvas
         * \param width Width of the Canvas (in pixels)
         * \param height Height of the Canvas (in pixels)
         */
        Canvas(unsigned int width, unsigned int height);

        template <class T> T* add(const std::string& id);

        CanvasElement* get(const std::string& id);

        /**
         * \brief Sets the Sprite where the Canvas should render
         * \param target Pointer to the Sprite where the Canvas should
         * render
         */
        void setTarget(Sprite* target);
        /**
         * \brief Render all the Canvas content to the Sprite target
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
        const sf::Texture& getTexture() const;
        /**
         * \brief Ask the Canvas to sort elements for the next rendering
         */
        void requiresSort();
    };

    template <class T> inline T* Canvas::add(const std::string& id)
    {
        if (this->get(id) == nullptr)
        {
            m_sortRequired = true;
            std::unique_ptr<T> newElement = std::make_unique<T>(this, id);
            auto insert_it = std::find_if(m_elements.begin(), m_elements.end(),
                [&newElement](const CanvasElement::Ptr& elem) {
                    return newElement->layer <= elem->layer;
                });
            auto elem_it = m_elements.insert(insert_it, std::move(newElement));
            return static_cast<T*>(elem_it->get());
        }
        else if (this->get(id)->type == T::Type)
        {
            Debug::Log->warn("<Scene> CanvasElement '{0}' already exists !", id);
            return static_cast<T*>(this->get(id));
        }
        else
        {
            throw aube::ErrorHandler::Raise("obe.Graphics.Canvas.Canvas."
                                            "ElementAlreadyExistsWithDifferentType");
        }
    }
} // namespace obe::Graphics::Canvas
