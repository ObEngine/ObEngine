#include <Engine/Engine.hpp>

namespace obe::Modes
{
    void start_game()
    {
        engine::Engine engine;
        engine.init();
        engine.run();
    }
} // namespace obe::Modes
