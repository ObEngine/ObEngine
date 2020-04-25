#include <Config/Config.hpp>
#include <Engine/Engine.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Input/InputManager.hpp>
#include <Modes/Game.hpp>

namespace obe::Modes
{
    void startGame()
    {
        Engine::Engine engine;
        engine.init();
        engine.run();
    }
} // namespace obe::Modes
