#include <Bindings/AnimationBindings.hpp>
#include <Bindings/CollisionBindings.hpp>
#include <Bindings/DebugBindings.hpp>
#include <Bindings/EditorBindings.hpp>
#include <Bindings/GraphicsBindings.hpp>
#include <Bindings/InputBindings.hpp>
#include <Bindings/SceneBindings.hpp>
#include <Bindings/SFMLBindings.hpp>
#include <Bindings/SoundBindings.hpp>
#include <Bindings/SystemBindings.hpp>
#include <Bindings/TimeBindings.hpp>
#include <Bindings/TransformBindings.hpp>
#include <Bindings/TriggersBindings.hpp>
#include <Bindings/TypesBindings.hpp>
#include <Bindings/Bindings.hpp>
#include <Utils/StringUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Bindings
    {
        BindingTree BindTree("Root");

        void Load(kaguya::State* lua, const std::string& lib)
        {
            std::cout << "Load start : "<< lib << std::endl;
            //BuildLuaLibPath(lua, lib);
            std::vector<std::string> splittedLibPath = Utils::String::split(lib, ".");
            BindTree.walkTo(splittedLibPath)(lua);
            std::cout << "Lib Successfully Loaded" << std::endl;
        }

        void IndexBindings()
        {
            BindTree.add("Core");
            BindTree["Core"].add("Animation")["Animation"]
                .add("AnimationGroup", &AnimationBindings::LoadAnimationGroup)
                .add("Animation", &AnimationBindings::LoadAnimation)
                .add("Animator", &AnimationBindings::LoadAnimator);
            BindTree["Core"].add("Collision")["Collision"]
                .add("PolygonalCollider", &CollisionBindings::LoadPolygonalCollider);
            BindTree["Core"].add("Debug")["Debug"]
                .add("Console", &DebugBindings::LoadConsole)
                .add("ConsoleMessage", &DebugBindings::LoadConsoleMessage)
                .add("ConsoleStream", &DebugBindings::LoadConsoleStream);
            BindTree["Core"].add("Editor")["Editor"]
                .add("EditorGrid", &EditorBindings::LoadEditorGrid);
            BindTree["Core"].add("Graphics")["Graphics"]
                .add("LevelSprite", &GraphicsBindings::LoadLevelSprite)
                .add("LevelSpriteHandlePoint", &GraphicsBindings::LoadLevelSpriteHandlePoint)
                .add("ResourceManager", &GraphicsBindings::LoadResourceManager);
            BindTree.add("SFML");
            BindTree["SFML"]
                .add("Color", SFMLBindings::LoadColor);
        }
    }
}
