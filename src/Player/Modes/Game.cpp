#include <Config/Config.hpp>
#include <Engine/Engine.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Input/InputManager.hpp>
#include <Modes/Game.hpp>
#include <Scene/Scene.hpp>
#include <System/Cursor.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>

namespace obe::Modes
{
    void startGame()
    {
        Engine::Engine engine;
        engine.run();
    }
} // namespace obe::Modes
