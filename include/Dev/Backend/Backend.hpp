#pragma once

#include <QObject>
#include <QWindow>

namespace obe::Backend
{
    class Backend : public QObject
    {
        Q_OBJECT
    protected:
        Q_PROPERTY(QWindow* window MEMBER m_window)
        QWindow* m_window;
    };

    void RegisterTypes();
}

#include "Backend.moc"