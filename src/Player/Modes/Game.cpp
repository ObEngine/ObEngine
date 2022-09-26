#include <Engine/Engine.hpp>

namespace obe::modes
{
    void start_game()
    {
        engine::Engine engine;
        engine.init();
        engine.run();
    }
} // namespace obe::modes
