#include "SFMLOffscreen.hpp"

#include <QImage>
#include <QDebug>

#include <cstring>

#include <SFML/Graphics/RectangleShape.hpp>

SFMLOffscreen::SFMLOffscreen() {
	sf::ContextSettings settings;
	m_render_texture.create(800, 600, settings);

	m_shape.setSize({200.f, 200.f});
	m_shape.setFillColor(sf::Color::Red);
}

SFMLOffscreen::~SFMLOffscreen() = default;

sf::Image SFMLOffscreen::renderFrame() {
	m_render_texture.clear(sf::Color::Black);
	m_render_texture.draw(m_shape);
	m_render_texture.display();

	return m_render_texture.getTexture().copyToImage();
}

sf::RenderTexture& SFMLOffscreen::getTexture()
{
    return m_render_texture;
}
