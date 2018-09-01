#pragma once

#include <QQuickImageProvider>
#include <QQueue>
#include <QImage>
#include <QTimer>

class SFMLOffscreen;
class SFMLImageProvider :  public QObject, public QQuickImageProvider {
		Q_OBJECT
	public:
		explicit SFMLImageProvider(SFMLOffscreen &offscreen);
		~SFMLImageProvider() override;

		QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
	private:
		void feed();

		SFMLOffscreen &m_offscreen;

		QQueue<QImage> m_images;

		QTimer m_timer;
};
