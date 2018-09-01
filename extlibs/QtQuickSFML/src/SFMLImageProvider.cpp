#include "SFMLImageProvider.hpp"
#include "SFMLOffscreen.hpp"

#include <cstring>

SFMLImageProvider::SFMLImageProvider(SFMLOffscreen &offscreen) : QQuickImageProvider(QQuickImageProvider::Image), m_offscreen(offscreen) {
	QObject::connect(&m_timer, &QTimer::timeout, this, &SFMLImageProvider::feed);

	m_timer.start(1);
}

SFMLImageProvider::~SFMLImageProvider() = default;

QImage SFMLImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
	if(m_images.empty())
		return QImage(requestedSize.width(), requestedSize.height(), QImage::Format_RGBA8888);

	auto image = m_images.front();
	m_images.pop_front();

	if(size)
		*size = image.size();

	return image;
}

void SFMLImageProvider::feed() {
	auto sfimage = m_offscreen.renderFrame();
	const auto size = sfimage.getSize().x * sfimage.getSize().y * 4;

	auto image = QImage(sfimage.getSize().x, sfimage.getSize().y, QImage::Format_RGBA8888);

	std::memcpy(image.bits(), sfimage.getPixelsPtr(), size);

	m_images.push_back(image);

	m_timer.start(5);
}
