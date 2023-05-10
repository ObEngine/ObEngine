#include <Graphics/NinePatch.hpp>

namespace obe::graphics
{
    const sf::Vector2f trim_amount { 1.f, 1.f };

    void extract_scale_positions_and_content_area_from_texture(const sf::Texture* const texture,
        const sf::IntRect texture_rect, sf::Vector2f& top_left, sf::Vector2f& bottom_right,
        sf::Vector2f& content_top_left, sf::Vector2f& content_bottom_right)
    {
        sf::Image image { texture->copyToImage() };

        // scale positions
        top_left = { 0.f, 0.f };
        bottom_right = { texture_rect.width - 2.f, texture_rect.height - 2.f };
        bool found_start { false }, found_end { false };
        for (unsigned int x { 1u }; x < static_cast<unsigned int>(texture_rect.width); ++x)
        {
            if (!found_start)
            {
                if (image.getPixel(texture_rect.left + x, texture_rect.top) == sf::Color::Black)
                {
                    found_start = true;
                    top_left.x = x - 1.f;
                }
                else
                    continue;
            }
            if (found_start)
            {
                if (image.getPixel(texture_rect.left + x, texture_rect.top) == sf::Color::Black)
                    bottom_right.x = x - 1.f;
                else
                    break;
            }
        }
        found_start = false;
        found_end = false;
        for (unsigned int y { 1u }; y < static_cast<unsigned int>(texture_rect.height); ++y)
        {
            if (!found_start)
            {
                if (image.getPixel(texture_rect.left, texture_rect.top + y) == sf::Color::Black)
                {
                    found_start = true;
                    top_left.y = y - 1.f;
                }
                else
                    continue;
            }
            if (found_start)
            {
                if (image.getPixel(texture_rect.left, texture_rect.top + y) == sf::Color::Black)
                    bottom_right.y = y - 1.f;
                else
                    break;
            }
        }

        // content area
        content_top_left = { 0.f, 0.f };
        content_bottom_right = { texture_rect.width - 2.f, texture_rect.height - 2.f };
        found_start = false;
        found_end = false;
        const sf::Vector2u texture_bottom_right_pixel(
            texture_rect.width - 1u, texture_rect.height - 1u);
        for (unsigned int x { 1u }; x < static_cast<unsigned int>(texture_rect.width); ++x)
        {
            if (!found_start)
            {
                if (image.getPixel(
                        texture_rect.left + x, texture_rect.top + texture_bottom_right_pixel.y)
                    == sf::Color::Black)
                {
                    found_start = true;
                    content_top_left.x = x - 1.f;
                }
                else
                    continue;
            }
            if (found_start)
            {
                if (image.getPixel(
                        texture_rect.left + x, texture_rect.top + texture_bottom_right_pixel.y)
                    == sf::Color::Black)
                    content_bottom_right.x = x - 1.f;
                else
                    break;
            }
        }
        found_start = false;
        found_end = false;
        for (unsigned int y { 1u }; y < static_cast<unsigned int>(texture_rect.height); ++y)
        {
            if (!found_start)
            {
                if (image.getPixel(
                        texture_rect.left + texture_bottom_right_pixel.x, texture_rect.top + y)
                    == sf::Color::Black)
                {
                    found_start = true;
                    content_top_left.y = y - 1.f;
                }
                else
                    continue;
            }
            if (found_start)
            {
                if (image.getPixel(
                        texture_rect.left + texture_bottom_right_pixel.x, texture_rect.top + y)
                    == sf::Color::Black)
                    content_bottom_right.y = y - 1.f;
                else
                    break;
            }
        }
    }

    NinePatch::NinePatch()
        : m_vertices(36, sf::Vertex({ 0.f, 0.f }))
        , m_texture { nullptr }
        , m_trimmed_size({ 0.f, 0.f })
        , m_size({ 0.f, 0.f })
        , m_scale_top_left({ 0.f, 0.f })
        , m_scale_bottom_right({ 0.f, 0.f })
        , m_content_top_left({ 0.f, 0.f })
        , m_content_bottom_right({ 0.f, 0.f })
        , m_texture_rect({ 0, 0, 3, 3 })
    {
    }

    void NinePatch::set_texture(
        const sf::Texture& texture, const bool reset_size, const bool reset_rect)
    {
        m_texture = &texture;
        if (reset_rect)
            m_texture_rect = { { 0, 0 }, sf::Vector2i(m_texture->getSize()) };
        m_trimmed_size = sf::Vector2f {
            static_cast<float>(m_texture_rect.width), static_cast<float>(m_texture_rect.height)
        } - trim_amount * 2.f;
        if (reset_size)
            m_size = m_trimmed_size;
        extract_scale_positions_and_content_area_from_texture(m_texture, m_texture_rect,
            m_scale_top_left, m_scale_bottom_right, m_content_top_left, m_content_bottom_right);
        update_vertices();
    }

    void NinePatch::set_texture()
    {
        m_texture = nullptr;
    }

    void NinePatch::set_size(sf::Vector2f size)
    {
        m_size = size;
        const sf::Vector2f minimum_size { m_scale_top_left
            + (m_trimmed_size - m_scale_bottom_right) };
        if (m_size.x < minimum_size.x)
            m_size.x = minimum_size.x;
        if (m_size.y < minimum_size.y)
            m_size.y = minimum_size.y;
        update_vertices_positions();
    }

    void NinePatch::reset_size()
    {
        set_size(m_trimmed_size);
    }

    void NinePatch::set_texture_rect(const sf::IntRect texture_rectangle, const bool reset_size)
    {
        m_texture_rect = texture_rectangle;
        m_trimmed_size = sf::Vector2f {
            static_cast<float>(m_texture_rect.width), static_cast<float>(m_texture_rect.height)
        } - trim_amount * 2.f;
        if (reset_size)
            m_size = m_trimmed_size;
        if (m_texture != nullptr)
        {
            extract_scale_positions_and_content_area_from_texture(m_texture, m_texture_rect,
                m_scale_top_left, m_scale_bottom_right, m_content_top_left, m_content_bottom_right);
            update_vertices();
        }
    }

    void NinePatch::set_color(const sf::Color& color)
    {
        for (auto& vertex : m_vertices)
            vertex.color = color;
    }

    sf::Color NinePatch::get_color() const
    {
        return m_vertices[0].color;
    }

    sf::Vector2f NinePatch::get_size() const
    {
        return m_size;
    }

    sf::FloatRect NinePatch::getLocalBounds() const
    {
        return { { 0.f, 0.f }, m_size };
    }

    sf::FloatRect NinePatch::getGlobalBounds() const
    {
        return getTransform().transformRect(getLocalBounds());
    }

    sf::FloatRect NinePatch::get_local_content_area() const
    {
        const sf::Vector2f top_left { get_resulting_position_of_texture_coord(m_content_top_left) };
        return { top_left,
            get_resulting_position_of_texture_coord(m_content_bottom_right) - top_left
                + sf::Vector2f(1.f, 1.f) };
    }

    sf::FloatRect NinePatch::get_global_content_area() const
    {
        return getTransform().transformRect(get_local_content_area());
    }

    bool NinePatch::is_point_inside_transformed_content_area(const sf::Vector2f point) const
    {
        return get_local_content_area().contains(getInverseTransform().transformPoint(point));
    }

    // PRIVATE

    void NinePatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.texture = m_texture;
        states.transform *= getTransform();
        target.draw(&m_vertices.front(), 36, sf::PrimitiveType::Quads, states);
    }

    void NinePatch::update_vertices()
    {
        update_vertices_positions();
        update_vertices_tex_coords();
    }

    void NinePatch::update_vertices_positions()
    {
        const sf::Vector2f new_bottom_right_scaled { m_size
            - (m_trimmed_size - m_scale_bottom_right) };

        // top row
        m_vertices[0].position = { 0.f, 0.f };
        m_vertices[1].position = { m_scale_top_left.x, 0.f };
        m_vertices[2].position = m_scale_top_left;
        m_vertices[3].position = { 0.f, m_scale_top_left.y };

        m_vertices[4].position = { m_scale_top_left.x, 0.f };
        m_vertices[5].position = { new_bottom_right_scaled.x, 0.f };
        m_vertices[6].position = { new_bottom_right_scaled.x, m_scale_top_left.y };
        m_vertices[7].position = m_scale_top_left;

        m_vertices[8].position = { new_bottom_right_scaled.x, 0.f };
        m_vertices[9].position = { m_size.x, 0.f };
        m_vertices[10].position = { m_size.x, m_scale_top_left.y };
        m_vertices[11].position = { new_bottom_right_scaled.x, m_scale_top_left.y };

        // centre row
        m_vertices[12].position = { 0.f, m_scale_top_left.y };
        m_vertices[13].position = { m_scale_top_left.x, m_scale_top_left.y };
        m_vertices[14].position = { m_scale_top_left.x, new_bottom_right_scaled.y };
        m_vertices[15].position = { 0.f, new_bottom_right_scaled.y };

        m_vertices[16].position = { m_scale_top_left.x, m_scale_top_left.y };
        m_vertices[17].position = { new_bottom_right_scaled.x, m_scale_top_left.y };
        m_vertices[18].position = { new_bottom_right_scaled.x, new_bottom_right_scaled.y };
        m_vertices[19].position = { m_scale_top_left.x, new_bottom_right_scaled.y };

        m_vertices[20].position = { new_bottom_right_scaled.x, m_scale_top_left.y };
        m_vertices[21].position = { m_size.x, m_scale_top_left.y };
        m_vertices[22].position = { m_size.x, new_bottom_right_scaled.y };
        m_vertices[23].position = { new_bottom_right_scaled.x, new_bottom_right_scaled.y };

        // bottom row
        m_vertices[24].position = { 0.f, new_bottom_right_scaled.y };
        m_vertices[25].position = { m_scale_top_left.x, new_bottom_right_scaled.y };
        m_vertices[26].position = { m_scale_top_left.x, m_size.y };
        m_vertices[27].position = { 0.f, m_size.y };

        m_vertices[28].position = { m_scale_top_left.x, new_bottom_right_scaled.y };
        m_vertices[29].position = { new_bottom_right_scaled.x, new_bottom_right_scaled.y };
        m_vertices[30].position = { new_bottom_right_scaled.x, m_size.y };
        m_vertices[31].position = { m_scale_top_left.x, m_size.y };

        m_vertices[32].position = { new_bottom_right_scaled.x, new_bottom_right_scaled.y };
        m_vertices[33].position = { m_size.x, new_bottom_right_scaled.y };
        m_vertices[34].position = { m_size.x, m_size.y };
        m_vertices[35].position = { new_bottom_right_scaled.x, m_size.y };
    }

    void NinePatch::update_vertices_tex_coords()
    {
        const sf::Vector2f texture_bottom_right { m_trimmed_size };

        // top row
        m_vertices[0].texCoords = { 0.f, 0.f };
        m_vertices[1].texCoords = { m_scale_top_left.x, 0.f };
        m_vertices[2].texCoords = m_scale_top_left;
        m_vertices[3].texCoords = { 0.f, m_scale_top_left.y };

        m_vertices[4].texCoords = { m_scale_top_left.x, 0.f };
        m_vertices[5].texCoords = { m_scale_bottom_right.x, 0.f };
        m_vertices[6].texCoords = { m_scale_bottom_right.x, m_scale_top_left.y };
        m_vertices[7].texCoords = m_scale_top_left;

        m_vertices[8].texCoords = { m_scale_bottom_right.x, 0.f };
        m_vertices[9].texCoords = { texture_bottom_right.x, 0.f };
        m_vertices[10].texCoords = { texture_bottom_right.x, m_scale_top_left.y };
        m_vertices[11].texCoords = { m_scale_bottom_right.x, m_scale_top_left.y };

        // center row
        m_vertices[12].texCoords = { 0.f, m_scale_top_left.y };
        m_vertices[13].texCoords = m_scale_top_left;
        m_vertices[14].texCoords = { m_scale_top_left.x, m_scale_bottom_right.y };
        m_vertices[15].texCoords = { 0.f, m_scale_bottom_right.y };

        m_vertices[16].texCoords = m_scale_top_left;
        m_vertices[17].texCoords = { m_scale_bottom_right.x, m_scale_top_left.y };
        m_vertices[18].texCoords = m_scale_bottom_right;
        m_vertices[19].texCoords = { m_scale_top_left.x, m_scale_bottom_right.y };

        m_vertices[20].texCoords = { m_scale_bottom_right.x, m_scale_top_left.y };
        m_vertices[21].texCoords = { texture_bottom_right.x, m_scale_top_left.y };
        m_vertices[22].texCoords = { texture_bottom_right.x, m_scale_bottom_right.y };
        m_vertices[23].texCoords = m_scale_bottom_right;

        // bottom row
        m_vertices[24].texCoords = { 0.f, m_scale_bottom_right.y };
        m_vertices[25].texCoords = { m_scale_top_left.x, m_scale_bottom_right.y };
        m_vertices[26].texCoords = { m_scale_top_left.x, texture_bottom_right.y };
        m_vertices[27].texCoords = { 0.f, texture_bottom_right.y };

        m_vertices[28].texCoords = { m_scale_top_left.x, m_scale_bottom_right.y };
        m_vertices[29].texCoords = m_scale_bottom_right;
        m_vertices[30].texCoords = { m_scale_bottom_right.x, texture_bottom_right.y };
        m_vertices[31].texCoords = { m_scale_top_left.x, texture_bottom_right.y };

        m_vertices[32].texCoords = m_scale_bottom_right;
        m_vertices[33].texCoords = { texture_bottom_right.x, m_scale_bottom_right.y };
        m_vertices[34].texCoords = texture_bottom_right;
        m_vertices[35].texCoords = { m_scale_bottom_right.x, texture_bottom_right.y };

        // offset trim and texture rectangle
        const sf::Vector2f texture_rectangle_offset { static_cast<float>(m_texture_rect.left),
            static_cast<float>(m_texture_rect.top) };
        for (auto& vertex : m_vertices)
            vertex.texCoords += texture_rectangle_offset + trim_amount;
    }

    sf::Vector2f NinePatch::get_resulting_position_of_texture_coord(
        sf::Vector2f texture_coord) const
    {
        sf::Vector2f result;

        const sf::Vector2f new_bottom_right_scaled { m_size
            - (m_trimmed_size - m_scale_bottom_right) };
        const sf::Vector2f scale_size { m_scale_bottom_right - m_scale_top_left };
        const sf::Vector2f new_scale_size { new_bottom_right_scaled - m_scale_top_left };

        if (texture_coord.x <= m_scale_top_left.x)
            result.x = texture_coord.x;
        else if (texture_coord.x >= m_scale_bottom_right.x)
            result.x = new_bottom_right_scaled.x + (texture_coord.x - m_scale_bottom_right.x);
        else
            result.x = ((texture_coord.x - m_scale_top_left.x) / scale_size.x) * new_scale_size.x
                + m_scale_top_left.x;
        if (texture_coord.y <= m_scale_top_left.y)
            result.y = texture_coord.y;
        else if (texture_coord.y >= m_scale_bottom_right.y)
            result.y = new_bottom_right_scaled.y + (texture_coord.y - m_scale_bottom_right.y);
        else
            result.y = ((texture_coord.y - m_scale_top_left.y) / (scale_size.y)) * new_scale_size.y
                + m_scale_top_left.y;

        return result;
    }

} // namespace selbaward