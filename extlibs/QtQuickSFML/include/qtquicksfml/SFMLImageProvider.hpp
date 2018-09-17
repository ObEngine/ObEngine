#pragma once

#include <QQuickImageProvider>
#include <QQueue>
#include <QImage>
#include <QTimer>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class SFMLOffscreen;
class SFMLImageProvider :  public QObject, public QQuickImageProvider {
		Q_OBJECT
	public:
		explicit SFMLImageProvider(sf::RenderTexture& target);
		~SFMLImageProvider() override;

		QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
	private:
		void feed();

        sf::RectangleShape m_shape;
        sf::RenderTexture& m_target;
		QQueue<QImage> m_images;
		QTimer m_timer;
};
