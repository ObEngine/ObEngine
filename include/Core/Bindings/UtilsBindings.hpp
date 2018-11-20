#pragma once

namespace kaguya { class State; }

/**
* \brief Bindings to Utils related classes and functions
*/
namespace obe::Bindings::UtilsBindings
{
    void LoadExecUtils(kaguya::State* lua);
    void LoadFileUtils(kaguya::State* lua);
    void LoadMathUtils(kaguya::State* lua);
    void loadStringUtils(kaguya::State* lua);
    void loadVectorUtils(kaguya::State* lua);
}