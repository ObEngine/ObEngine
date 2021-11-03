#include <Engine/Engine.hpp>

namespace obe::Modes
{
    void startGame()
    {
        Engine::Engine engine;
        engine.init();
        engine.run();
    }
} // namespace obe::Modes
