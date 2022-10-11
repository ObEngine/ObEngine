#include <Engine/Engine.hpp>

namespace obe::modes
{
    void start_game(const vili::node& arguments)
    {
        engine::Engine engine;
        engine.init(arguments);
        engine.run();
    }
} // namespace obe::modes
