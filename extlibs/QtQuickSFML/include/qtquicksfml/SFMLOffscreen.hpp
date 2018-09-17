#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class SFMLOffscreen {
	public:
		explicit SFMLOffscreen();
		~SFMLOffscreen();

		sf::Image renderFrame();
        sf::RenderTexture& getTexture();
	private:
		sf::RenderTexture  m_render_texture;
		sf::RectangleShape m_shape;
};
