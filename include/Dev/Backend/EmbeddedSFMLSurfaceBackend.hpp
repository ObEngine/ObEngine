#pragma once

#include <Backend/Backend.hpp>

namespace obe::Backend
{
    class EmbeddedSFMLSurfaceBackend : public Backend
    {
        Q_OBJECT
    public:
        EmbeddedSFMLSurfaceBackend();
        Q_INVOKABLE void setWindowSize(unsigned int width, unsigned int height) const;
        QString m_input;
        Q_PROPERTY(QString input MEMBER m_input)
    signals:
        void render();
    };
}

#include "EmbeddedSFMLSurfaceBackend.moc"