#include <Backend/SFMLRenderWidget.hpp>
#include "Transform/UnitVector.hpp"
#include "System/Window.hpp"
#include <QPainter>

#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif

/*QSFMLCanvas::QSFMLCanvas(QQuickItem *parent)
{
}*/

/*
void QSFMLCanvas::OnInit()
{
}

void QSFMLCanvas::OnUpdate()
{
}

void QSFMLCanvas::paint(QPainter* painter)
{
    this->renderTarget()
}
*/
/*
void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!myInitialized)
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
#ifdef Q_WS_X11
        XFlush(QX11Info::display());
#endif

        // Create the SFML window with the widget handle
        sf::RenderWindow::create(reinterpret_cast<sf::WindowHandle>(winId()));

        // Let the derived class do its specific stuff
        OnInit();

        // Setup the timer to trigger a refresh at specified framerate
        connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        myTimer.start();

        myInitialized = true;
    }
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return nullptr;
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
    OnUpdate();
    sf::RenderWindow::display();
}

void QSFMLCanvas::resizeEvent(QResizeEvent* event)
{
    sf::RenderWindow::setSize(sf::Vector2u(QWidget::width(), QWidget::height()));
    obe::Transform::UnitVector::Screen.w = QWidget::width();
    obe::Transform::UnitVector::Screen.h = QWidget::height();
    obe::System::MainWindow.setView(sf::View(sf::FloatRect(0, 0, QWidget::width(), QWidget::height())));
}
*/
