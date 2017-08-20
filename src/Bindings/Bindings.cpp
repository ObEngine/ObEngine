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
#include <Bindings/UtilsBindings.hpp>
#include <Bindings/ViliBindings.hpp>
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
            // Core Binding
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
                .add("Canvas", &GraphicsBindings::LoadCanvas)
                .add("LevelSprite", &GraphicsBindings::LoadLevelSprite)
                .add("LevelSpriteHandlePoint", &GraphicsBindings::LoadLevelSpriteHandlePoint)
                .add("ResourceManager", &GraphicsBindings::LoadResourceManager);
            BindTree["Core"].add("Input")["Input"]
                .add("InputAction", &InputBindings::LoadInputAction)
                .add("InputActionEvent", &InputBindings::LoadInputActionEvent)
                .add("InputButton", &InputBindings::LoadInputButton)
                .add("InputButtonMonitor", &InputBindings::LoadInputButtonMonitor)
                .add("InputCondition", &InputBindings::LoadInputCondition)
                .add("InputFunctions", &InputBindings::LoadInputFunctions)
                .add("InputManager", &InputBindings::LoadInputManager);
            BindTree["Core"].add("Scene")["Scene"]
                .add("Camera", &SceneBindings::LoadCamera)
                .add("Scene", &SceneBindings::LoadScene);
            BindTree["Core"].add("Sound")["Sound"];
            BindTree["Core"].add("System")["System"]
                .add("MountablePath", &SystemBindings::LoadMountablePath)
                .add("Package", &SystemBindings::LoadPackage)
                .add("Path", &SystemBindings::LoadPath)
                .add("Cursor", &SystemBindings::LoadSCursor)
                .add("Workspace", &SystemBindings::LoadWorkspace);
            BindTree["Core"].add("Time")["Time"]
                .add("Chronometer", &TimeBindings::LoadChronometer)
                .add("FPSCounter", &TimeBindings::LoadFPSCounter)
                .add("FramerateManager", &TimeBindings::LoadFramerateManager);
            BindTree["Core"].add("Transform")["Transform"]
                .add("ProtectedUnitVector", &TransformBindings::LoadProtectedUnitVector)
                .add("Rect", &TransformBindings::LoadRect)
                .add("Referencial", &TransformBindings::LoadReferencial)
                .add("UnitBasedObject", &TransformBindings::LoadUnitBasedObject)
                .add("Units", &TransformBindings::LoadUnits)
                .add("UnitVector", &TransformBindings::LoadUnitVector);
            BindTree["Core"].add("Triggers")["Triggers"]
                .add("Trigger", &TriggersBindings::LoadTrigger)
                .add("TriggerDatabase", &TriggersBindings::LoadTriggerDatabase)
                .add("TriggerDelay", &TriggersBindings::LoadTriggerDelay)
                .add("TriggerGroup", &TriggersBindings::LoadTriggerGroup);
            BindTree["Core"].add("Types")["Types"]
                .add("Identifiable", &TypesBindings::LoadIdentifiable)
                .add("Selectable", &TypesBindings::LoadSelectable)
                .add("Togglable", &TypesBindings::LoadTogglable);
            BindTree["Core"].add("Utils")["Utils"]
                .add("ExecUtils", &UtilsBindings::LoadExecUtils)
                .add("FileUtils", &UtilsBindings::LoadFileUtils)
                .add("MathUtils", &UtilsBindings::LoadMathUtils)
                .add("StringUtils", &UtilsBindings::loadStringUtils)
                .add("VectorUtils", &UtilsBindings::loadVectorUtils);

            // SFML Binding
            BindTree.add("SFML");
            BindTree["SFML"]
                .add("Color", SFMLBindings::LoadSfColor);

            // Vili Binding
            BindTree.add("Vili");
            BindTree["Vili"]
                .add("ArrayNode", &ViliBindings::LoadViliArrayNode)
                .add("ComplexNode", &ViliBindings::LoadViliComplexNode)
                .add("ContainerNode", &ViliBindings::LoadViliContainerNode)
                .add("DataNode", &ViliBindings::LoadViliDataNode)
                .add("DataType", &ViliBindings::LoadViliDataType)
                .add("ErrorHandler", &ViliBindings::LoadViliErrorHandler)
                .add("LinkNode", &ViliBindings::LoadViliLinkNode)
                .add("Node", &ViliBindings::LoadViliNode)
                .add("NodeConstraintManager", &ViliBindings::LoadViliNodeConstraintManager)
                .add("NodeIterator", &ViliBindings::LoadViliNodeIterator)
                .add("NodeTemplate", &ViliBindings::LoadViliNodeTemplate)
                .add("NodeType", &ViliBindings::LoadViliNodeType)
                .add("ViliParser", &ViliBindings::LoadViliViliParser);
        }
    }
}
