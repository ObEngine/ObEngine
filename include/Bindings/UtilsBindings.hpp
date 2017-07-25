#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        void LoadExecUtils(kaguya::State* lua);
        void LoadFileUtils(kaguya::State* lua);
        void LoadMathUtils(kaguya::State* lua);
        void loadStringUtils(kaguya::State* lua);
        void loadVectorUtils(kaguya::State* lua);
    }
}
