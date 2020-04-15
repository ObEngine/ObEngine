#pragma once

#include <Exception.hpp>

namespace obe::Graphics::Exceptions
{
    class ReadOnlyTexture : public Exception
    {
    public:
        ReadOnlyTexture(std::string_view method, DebugInfo info)
            : Exception("ReadOnlyTexture", info)
        {
            this->error(
                "Impossible to call method Texture::{} when Texture is in readonly-mode",
                method);
        }
    };
}