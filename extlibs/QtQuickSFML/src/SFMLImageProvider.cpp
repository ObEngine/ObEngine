#include "SFMLImageProvider.hpp"

#include <cstring>
#include <SFML/Graphics/RenderTexture.hpp>
#include <iostream>
#include <SFMLOffscreen.hpp>

SFMLImageProvider::SFMLImageProvider(sf::RenderTexture& target) :
QQuickImageProvider(QQuickImageProvider::Image), 
m_target(target) 
{
    m_shape.setSize({ 200.f, 200.f });
    m_shape.setFillColor(sf::Color::Red);
}

SFMLImageProvider::~SFMLImageProvider() = default;

QImage SFMLImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) 
{
    auto sfimage = m_target.getTexture().copyToImage();
    const auto imsize = sfimage.getSize().x * sfimage.getSize().y * 4;
    auto image = QImage(sfimage.getSize().x, sfimage.getSize().y, QImage::Format_RGBA8888);
    std::memcpy(image.bits(), sfimage.getPixelsPtr(), imsize);

	if(size)
		*size = image.size();

	return image;
}