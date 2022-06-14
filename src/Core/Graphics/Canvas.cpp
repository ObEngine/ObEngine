#include <SFML/Graphics/Vertex.hpp>
#include <bezier/bezier.h>

#include <Graphics/Canvas.hpp>

namespace obe::graphics::canvas
{
    CanvasElement::CanvasElement(Canvas& parent, const std::string& id)
        : ProtectedIdentifiable(id)
        , parent(parent)
    {
    }

    void CanvasElement::set_layer(const unsigned int layer)
    {
        if (this->layer != layer)
        {
            this->layer = layer;
            parent.requires_sort();
        }
    }

    Line::Line(Canvas& parent, const std::string& id)
        : CanvasElement(parent, id)
    {
    }

    void Line::draw(RenderTarget target)
    {
        const transform::UnitVector p1px = p1.to<transform::Units::ScenePixels>();
        const transform::UnitVector p2px = p2.to<transform::Units::ScenePixels>();
        if (thickness == 1)
        {
            const sf::Vertex first_vertex(sf::Vector2f(p1px.x, p1px.y), p1_color);
            const sf::Vertex second_vertex(sf::Vector2f(p2px.x, p2px.y), p2_color);
            const sf::Vertex line[] = { first_vertex, second_vertex };
            target.draw(line, 2, sf::Lines);
        }
        else
        {
            sf::VertexArray lines(sf::TrianglesStrip, 4);
            const sf::Vector2f sfp1(p1px.x, p1px.y);
            const sf::Vector2f sfp2(p2px.x, p2px.y);
            lines[0] = sf::Vertex(sfp1, p1_color);
            lines[1] = sf::Vertex(sfp2, p2_color);
            lines[2] = sf::Vertex(sfp2 + sf::Vector2f(thickness, thickness), p2_color);
            lines[3] = sf::Vertex(sfp1 + sf::Vector2f(thickness, thickness), p1_color);
            target.draw(lines);
        }
    }

    CanvasPositionable::CanvasPositionable(Canvas& parent, const std::string& id)
        : CanvasElement(parent, id)
    {
        // Default Canvas elements unit is ScenePixels
        position.unit = transform::Units::ScenePixels;
    }

    Rectangle::Rectangle(Canvas& parent, const std::string& id)
        : CanvasPositionable(parent, id)
    {
        this->size.unit = transform::Units::ScenePixels;
    }

    void Rectangle::draw(RenderTarget target)
    {
        target.draw(shape);
    }

    Text::Text(Canvas& parent, const std::string& id)
        : CanvasPositionable(parent, id)
        , h_align()
        , v_align()
    {
        texts.emplace_back();
    }

    void Text::draw(RenderTarget target)
    {
        transform::UnitVector offset(transform::Units::ScenePixels);
        if (h_align == TextHorizontalAlign::Center)
            offset.x -= shape.get_global_bounds().get_size().x / 2;
        else if (h_align == TextHorizontalAlign::Right)
            offset.x -= shape.get_global_bounds().get_size().x;
        if (v_align == TextVerticalAlign::Center)
            offset.y -= shape.get_global_bounds().get_size().y / 2;
        else if (v_align == TextVerticalAlign::Bottom)
            offset.y -= shape.get_global_bounds().get_size().y;
        shape.move(offset);
        target.draw(shape);
        shape.move(-offset);
    }

    void Text::refresh()
    {
        shape.clear();
        for (const auto& text : texts)
        {
            if (!text.string.empty())
            {
                shape.append(text);
            }
        }
    }

    graphics::Text& Text::current_text()
    {
        return texts.back();
    }

    Circle::Circle(Canvas& parent, const std::string& id)
        : CanvasPositionable(parent, id)
    {
    }

    void Circle::draw(RenderTarget target)
    {
        target.draw(shape);
    }

    Polygon::Polygon(Canvas& parent, const std::string& id)
        : CanvasPositionable(parent, id)
    {
    }

    void Polygon::draw(RenderTarget target)
    {
        target.draw(shape);
    }

    Bezier::Bezier(Canvas& parent, const std::string& id)
        : CanvasElement(parent, id)
    {
    }

    void Bezier::draw(RenderTarget target)
    {
        std::vector<::Bezier::Point> control_points;
        control_points.reserve(points.size());
        for (transform::UnitVector& point : points)
        {
            const transform::UnitVector pixel_position = point.to<transform::Units::ScenePixels>();
            control_points.emplace_back(pixel_position.x, pixel_position.y);
        }
        std::vector<::Bezier::Bezier<3>> bezier_curves;
        bezier_curves.reserve((control_points.size() - 1) / 3);
        for (std::size_t i = 3; i < control_points.size(); i += 3)
        {
            auto bezier_points = std::vector<::Bezier::Point>(
                control_points.begin() + (i - 3), control_points.begin() + (i + 1));
            bezier_curves.emplace_back(bezier_points);
        }
        const std::size_t maximum = bezier_curves.size() * precision;
        std::vector<sf::Vertex> vertices;
        vertices.reserve(maximum);

        std::size_t curve_index = 0;
        for (::Bezier::Bezier<3>& bezier : bezier_curves)
        {
            for (std::size_t i = 0; i < (precision % 2 ? precision : precision + 1); i++)
            {
                double t = static_cast<double>(i) / precision;
                double tc = fmod(t * 4, 4);
                Color first_color = colors[((t >= 1) ? 3 : floor(t * 4)) + curve_index];
                Color second_color = colors[((t >= 0.75) ? 3 : ceil(t * 4)) + curve_index];
                Color color = (first_color * (1 - tc)) + (second_color * tc);
                ::Bezier::Point p = bezier.valueAt(t);
                vertices.emplace_back(sf::Vector2f(p.x, p.y), color);
            }
            curve_index += 3;
        }
        target.draw(vertices.data(), maximum, sf::LineStrip);
    }

    void Canvas::sort_elements()
    {
        std::ranges::sort(m_elements,
            [](const auto& elem1, const auto& elem2) { return elem1->layer > elem2->layer; });
    }

    Canvas::Canvas(unsigned int width, unsigned int height)
    {
        m_canvas.create(width, height);
    }

    CanvasElement* Canvas::get(const std::string& id) const
    {
        for (auto& elem : m_elements)
        {
            if (elem->get_id() == id)
            {
                return elem.get();
            }
        }
        return nullptr;
    }

    void Canvas::render(Sprite& target)
    {
        m_canvas.clear(sf::Color(0, 0, 0, 0));

        if (m_sort_required)
        {
            this->sort_elements();
            m_sort_required = false;
        }

        for (const auto& element : m_elements)
        {
            if (element->visible)
                element->draw(m_canvas);
        }
        m_canvas.display();
        target.set_texture(m_canvas.getTexture());
    }

    void Canvas::clear()
    {
        m_elements.clear();
    }

    void Canvas::remove(const std::string& id)
    {
        std::erase_if(m_elements, [&id](auto& elem) { return elem->get_id() == id; });
    }

    Texture Canvas::get_texture() const
    {
        return m_canvas.getTexture();
    }

    void Canvas::requires_sort()
    {
        m_sort_required = true;
    }
} // namespace obe::graphics::canvas
