#include <Engine/Engine.hpp>

namespace obe::Modes
{
    void startGame()
    {
        engine::Engine engine;
        engine.init();
        engine.run();
    }
} // namespace obe::Modes
