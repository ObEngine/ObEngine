#pragma once

// Base implementation from https://github.com/Hapaxia/SelbaWard

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace obe::graphics
{
    class NinePatch : public sf::Drawable, public sf::Transformable
    {
    private:
        std::vector<sf::Vertex> m_vertices;
        const sf::Texture* m_texture;
        sf::Vector2f m_trimmed_size;
        sf::Vector2f m_size;
        sf::Vector2f m_scale_top_left;
        sf::Vector2f m_scale_bottom_right;
        sf::Vector2f m_content_top_left;
        sf::Vector2f m_content_bottom_right;
        sf::IntRect m_texture_rect;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void update_vertices();
        void update_vertices_positions();
        void update_vertices_tex_coords();
        sf::Vector2f get_resulting_position_of_texture_coord(
            sf::Vector2f texture_coord) const; // resulting local position

    public:
        NinePatch();

        void set_texture(
            const sf::Texture& texture, bool reset_size = true, bool reset_rect = true);
        void set_texture();

        [[nodiscard]] sf::Vector2f get_size() const;
        void set_size(sf::Vector2f size);
        void reset_size();

        void set_texture_rect(sf::IntRect texture_rectangle, bool reset_size = true);

        void set_color(const sf::Color& color);
        [[nodiscard]] sf::Color get_color() const;

        [[nodiscard]] sf::FloatRect getLocalBounds() const;
        [[nodiscard]] sf::FloatRect getGlobalBounds() const;
        [[nodiscard]] sf::FloatRect get_local_content_area() const;
        [[nodiscard]] sf::FloatRect get_global_content_area() const;

        [[nodiscard]] bool is_point_inside_transformed_content_area(sf::Vector2f point) const;
    };
}