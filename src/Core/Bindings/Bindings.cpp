// Corresponding header
#include <Bindings/Bindings.hpp>

// ObEngineCore headers
#include <Bindings/AnimationBindings.hpp>
#include <Bindings/AudioBindings.hpp>
#include <Bindings/CPPBindings.hpp>
#include <Bindings/CollisionBindings.hpp>
#include <Bindings/ConfigBindings.hpp>
#include <Bindings/DebugBindings.hpp>
#include <Bindings/GraphicsBindings.hpp>
#include <Bindings/InputBindings.hpp>
#include <Bindings/NetworkBindings.hpp>
#include <Bindings/SFMLBindings.hpp>
#include <Bindings/SceneBindings.hpp>
#include <Bindings/ScriptBindings.hpp>
#include <Bindings/SystemBindings.hpp>
#include <Bindings/TimeBindings.hpp>
#include <Bindings/TransformBindings.hpp>
#include <Bindings/TriggersBindings.hpp>
#include <Bindings/TypesBindings.hpp>
#include <Bindings/UtilsBindings.hpp>
#include <Bindings/ViliBindings.hpp>
#include <Debug/Logger.hpp>
#include <System/Plugin.hpp>
#include <Utils/StringUtils.hpp>

// extlibs headers
#include <kaguya/kaguya.hpp>

namespace obe::Bindings
{
    BindingTree BindTree("Root");

    void Load(kaguya::State* lua, const std::string& lib)
    {
        const std::vector<std::string> splitLibPath = Utils::String::split(lib, ".");
        BindTree.walkTo(splitLibPath)(lua);
    }

    void IndexBaseBindings()
    {
        // obe Binding
        BindTree.add("obe", InitTreeNodeAsTable("obe"));
        BindTree["obe"]
            // Animation
            .add("AnimationGroup", &AnimationBindings::LoadAnimationGroup)
            .add("Animation", &AnimationBindings::LoadAnimation)
            .add("Animator", &AnimationBindings::LoadAnimator)
            // Audio
            .add("AudioManager", &AudioBindings::LoadAudioManager)
            .add("Sound", &AudioBindings::LoadSound)
            // Collision
            .add("PolygonalCollider", &CollisionBindings::LoadPolygonalCollider)
            .add("Trajectory", &CollisionBindings::LoadTrajectory)
            .add("TrajectoryNode", &CollisionBindings::LoadTrajectoryNode)
            // Config
            .add("Git", &ConfigBindings::LoadGit)
            // Debug
            .add("Log", &DebugBindings::LoadLog)
            // Graphics
            .add("Canvas", &GraphicsBindings::LoadCanvas)
            .add("Color", &GraphicsBindings::LoadColor)
            .add("LevelSprite", &GraphicsBindings::LoadLevelSprite)
            .add("LevelSpriteHandlePoint", &GraphicsBindings::LoadLevelSpriteHandlePoint)
            .add("ResourceManager", &GraphicsBindings::LoadResourceManager)
            .add("Shader", &GraphicsBindings::LoadShader)
            .add("Utils", &GraphicsBindings::LoadGraphicsUtils)
            // Input
            .add("InputAction", &InputBindings::LoadInputAction)
            .add("InputActionEvent", &InputBindings::LoadInputActionEvent)
            .add("InputButton", &InputBindings::LoadInputButton)
            .add("InputButtons", &InputBindings::LoadInputButtons)
            .add("InputButtonMonitor", &InputBindings::LoadInputButtonMonitor)
            .add("InputCondition", &InputBindings::LoadInputCondition)
            .add("InputFunctions", &InputBindings::LoadInputFunctions)
            .add("InputManager", &InputBindings::LoadInputManager)
            // Network
            .add("TcpServer", &NetworkBindings::LoadTcpServer)
            // Scene
            .add("Camera", &SceneBindings::LoadCamera)
            .add("Scene", &SceneBindings::LoadScene)
            .add("SceneNode", &SceneBindings::LoadSceneNode)
            // Script
            .add("Script", &ScriptBindings::LoadGameObject)
            // System
            .add("Constants", &SystemBindings::LoadSystemConstants)
            .add("MountablePath", &SystemBindings::LoadMountablePath)
            .add("Package", &SystemBindings::LoadPackage)
            .add("Path", &SystemBindings::LoadPath)
            .add("Cursor", &SystemBindings::LoadSCursor)
            .add("Workspace", &SystemBindings::LoadWorkspace)
            .add("Window", &SystemBindings::LoadWindow)
            // Time
            .add("Chronometer", &TimeBindings::LoadChronometer)
            .add("FPSCounter", &TimeBindings::LoadFPSCounter)
            .add("FramerateManager", &TimeBindings::LoadFramerateManager)
            .add("TimeCheck", &TimeBindings::LoadTimeCheck)
            .add("TimeUtils", &TimeBindings::LoadTimeUtils)
            // Transform
            .add("Movable", &TransformBindings::LoadMovable)
            .add("Polygon", &TransformBindings::LoadPolygon)
            .add("ProtectedUnitVector", &TransformBindings::LoadProtectedUnitVector)
            .add("Rect", &TransformBindings::LoadRect)
            .add("Referential", &TransformBindings::LoadReferential)
            .add("UnitBasedObject", &TransformBindings::LoadUnitBasedObject)
            .add("Units", &TransformBindings::LoadUnits)
            .add("UnitVector", &TransformBindings::LoadUnitVector)
            // Triggers
            .add("Trigger", &TriggersBindings::LoadTrigger)
            .add("TriggerDatabase", &TriggersBindings::LoadTriggerDatabase)
            .add("TriggerDelay", &TriggersBindings::LoadTriggerDelay)
            .add("TriggerGroup", &TriggersBindings::LoadTriggerGroup)
            // Types
            .add("Identifiable", &TypesBindings::LoadIdentifiable)
            .add("Selectable", &TypesBindings::LoadSelectable)
            .add("Serializable", &TypesBindings::LoadSerializable)
            .add("Togglable", &TypesBindings::LoadTogglable)
            // Utils
            .add("ExecUtils", &UtilsBindings::LoadExecUtils)
            .add("FileUtils", &UtilsBindings::LoadFileUtils)
            .add("MathUtils", &UtilsBindings::LoadMathUtils)
            .add("StringUtils", &UtilsBindings::loadStringUtils)
            .add("VectorUtils", &UtilsBindings::loadVectorUtils);

        // SFML Binding
        BindTree.add("SFML", InitTreeNodeAsTable("SFML"));
        BindTree["SFML"]
            .add("Color", SFMLBindings::LoadSfColor)
            .add("Drawable", SFMLBindings::LoadSfDrawable)
            .add("Rect", SFMLBindings::LoadSfRect)
            .add("Shape", SFMLBindings::LoadSfShape)
            .add("Text", SFMLBindings::LoadSfText)
            .add("Texture", SFMLBindings::LoadSfTexture)
            .add("Time", SFMLBindings::LoadSfTime)
            .add("Transformable", SFMLBindings::LoadSfTransformable)
            .add("Vector", SFMLBindings::LoadSfVector);

        // Vili Binding
        BindTree.add("Vili", InitTreeNodeAsTable("Vili"));
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

    void IndexPluginsBindings()
    {
        Debug::Log->info("Indexing Plugins...");
        for (auto& plugin : System::Plugins)
        {
            Debug::Log->info("Indexing plugin bindings {} ({})", plugin->getId(),
                plugin->hasOnLoadBindings());
            if (plugin->hasOnLoadBindings())
                BindTree.add(plugin->getId(),
                    [&plugin](kaguya::State* lua) { plugin->onLoadBindings(lua); });
        }
    }
} // namespace obe::Bindings
