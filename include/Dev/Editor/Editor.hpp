#pragma once

namespace obe::Backend {
    class EmbeddedSFMLSurfaceBackend;
}

namespace obe::Editor
{
    /**
    * \brief Starts the ObEngine Editor
    */
    void startEditor(Backend::EmbeddedSFMLSurfaceBackend& sfBackend);
}
