#include <Backend/EmbeddedSFMLSurfaceBackend.hpp>
#include <System/Window.hpp>

namespace obe::Backend
{
    EmbeddedSFMLSurfaceBackend::EmbeddedSFMLSurfaceBackend()
    {
    }

    void EmbeddedSFMLSurfaceBackend::setWindowSize(unsigned width, unsigned height) const
    {
        System::MainWindow.setSize(width, height);
    }
}

#include "EmbeddedSFMLSurfaceBackend.moc"