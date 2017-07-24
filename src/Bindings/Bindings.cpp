#include <Bindings/AnimationBindings.hpp>
#include <Bindings/CollisionBindings.hpp>
#include <Bindings/DebugBindings.hpp>
#include <Bindings/EditorBindings.hpp>
#include <Bindings/GraphicsBindings.hpp>
#include <Bindings/InputBindings.hpp>
#include <Bindings/SceneBindings.hpp>
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
        BindingTree BindTree("Root", [](kaguya::State& lua)
                         {
                         });

        void BuildLuaLibPath(LuaTRef lua, std::vector<std::string>& path)
        {
            if (path.size() > 1)
            {
                if (!static_cast<bool>(lua[path[0]]))
                {
                    lua[path[0]] = kaguya::NewTable();
                }
                std::vector<std::string> subPath = Utils::Vector::getSubVector(path, 1, 0);
                BuildLuaLibPath(lua[path[0]], subPath);
            }
            else if (path.size() == 1)
            {
                if (!static_cast<bool>(lua[path[0]]))
                {
                    lua[path[0]] = kaguya::NewTable();
                }
            }
        }

        void BuildLuaLibPath(kaguya::State& lua, const std::string& path)
        {
            std::vector<std::string> splittedLibPath = Utils::String::split(path, ".");
            if (!static_cast<bool>(lua[splittedLibPath[0]]))
            {
                lua[splittedLibPath[0]] = kaguya::NewTable();
            }
            LuaTRef firstTableKey = lua[splittedLibPath[0]];
            if (splittedLibPath.size() > 1)
            {
                std::vector<std::string> subPath = Utils::Vector::getSubVector(splittedLibPath, 1, 0);
                return BuildLuaLibPath(firstTableKey, subPath);
            }
        }

        void Load(kaguya::State& lua, const std::string& lib)
        {
            std::cout << "Load start" << std::endl;
            BuildLuaLibPath(lua, lib);
            std::vector<std::string> splittedLibPath = Utils::String::split(lib, ".");
            BindTree.walkTo(splittedLibPath)(lua);
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
                .add("ConsoleStrea", &DebugBindings::LoadConsoleStream);
            BindTree["Core"].add("Editor")["Editor"]
                .add("EditorGrid", EditorBindings::LoadEditorGrid);
            BindTree["Core"].add("Graphics")["Graphics"]
                .add("LevelSprite", GraphicsBindings::LoadLevelSprite)
                .add("LevelSpriteHandlePoint", &GraphicsBindings::LoadLevelSpriteHandlePoint)
                .add("ResourceManager", GraphicsBindings::LoadResourceManager);
        }
    }
}
