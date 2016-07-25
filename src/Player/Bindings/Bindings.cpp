#include <Bindings/AnimationBindings.hpp>
#include <Bindings/CollisionBindings.hpp>
#include <Bindings/GraphicsBindings.hpp>
#include <Bindings/InputBindings.hpp>
#include <Bindings/SceneBindings.hpp>
#include <Bindings/SFMLBindings.hpp>
#include <Bindings/ScriptBindings.hpp>
#include <Bindings/SoundBindings.hpp>
#include <Bindings/SystemBindings.hpp>
#include <Bindings/TimeBindings.hpp>
#include <Bindings/TransformBindings.hpp>
#include <Bindings/TriggersBindings.hpp>
#include <Bindings/TypesBindings.hpp>
#include <Bindings/UtilsBindings.hpp>
#include <Bindings/ViliBindings.hpp>
#include <Bindings/Bindings.hpp>
#include <Debug/Logger.hpp>
#include <System/Path.hpp>
#include <Utils/FileUtils.hpp>
#include <Utils/StringUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Bindings
    {
        BindingTree BindTree("Root");
        std::map<std::string, std::shared_ptr<dynamicLinker::dynamicLinker>> Plugins;

        void Load(kaguya::State* lua, const std::string& lib)
        {
            //BuildLuaLibPath(lua, lib);
            std::vector<std::string> splittedLibPath = Utils::String::split(lib, ".");
            BindTree.walkTo(splittedLibPath)(lua);
        }

        void IndexBindings()
        {
            // obe Binding
            BindTree.add("obe", InitTreeNodeAsTable("obe"));
            BindTree["obe"]
            // Animation
                .add("AnimationGroup", &AnimationBindings::LoadAnimationGroup)
                .add("Animation", &AnimationBindings::LoadAnimation)
                .add("Animator", &AnimationBindings::LoadAnimator)
            // Collision
                .add("PolygonalCollider", &CollisionBindings::LoadPolygonalCollider)
                .add("Trajectory", &CollisionBindings::LoadTrajectory)
                .add("TrajectoryNode", &CollisionBindings::LoadTrajectoryNode)
            // Graphics
                .add("Canvas", &GraphicsBindings::LoadCanvas)
                .add("LevelSprite", &GraphicsBindings::LoadLevelSprite)
                .add("LevelSpriteHandlePoint", &GraphicsBindings::LoadLevelSpriteHandlePoint)
                .add("ResourceManager", &GraphicsBindings::LoadResourceManager)
                .add("Utils", &GraphicsBindings::LoadGraphicsUtils)
            // Input
                .add("InputAction", &InputBindings::LoadInputAction)
                .add("InputActionEvent", &InputBindings::LoadInputActionEvent)
                .add("InputButton", &InputBindings::LoadInputButton)
                .add("InputButtonMonitor", &InputBindings::LoadInputButtonMonitor)
                .add("InputCondition", &InputBindings::LoadInputCondition)
                .add("InputFunctions", &InputBindings::LoadInputFunctions)
                .add("InputManager", &InputBindings::LoadInputManager)
            // Scene
                .add("Camera", &SceneBindings::LoadCamera)
                .add("Scene", &SceneBindings::LoadScene)
            // Script
                .add("Script", &ScriptBindings::LoadGameObject)
            // Sound
                .add("Music", &SoundBindings::LoadMusic)
                .add("Sound", &SoundBindings::LoadSound)
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
            // Transform
                .add("Movable", &TransformBindings::LoadMovable)
                .add("ProtectedUnitVector", &TransformBindings::LoadProtectedUnitVector)
                .add("Rect", &TransformBindings::LoadRect)
                .add("Referencial", &TransformBindings::LoadReferencial)
                .add("SceneNode", &TransformBindings::LoadSceneNode)
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
                .add("Shape", SFMLBindings::LoadSfShape)
                .add("Text", SFMLBindings::LoadSfText)
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
            
            // Plugins
            for (const System::MountablePath& mountedPath : System::Path::MountedPaths)
            {
                Debug::Log->info("<Bindings> Checking Plugins on Mounted Path : {0}", mountedPath.basePath);
                System::Path cPluginPath = System::Path(mountedPath.basePath).add("Plugins");
                for (const std::string& filename : Utils::File::getFileList(cPluginPath.toString()))
                {
                    const std::string pluginPath = cPluginPath.add(filename).toString();
                    const std::string pluginName = Utils::String::split(filename, ".")[0];
                    BindTree.add(Utils::String::split(filename, ".")[0], 
                        [pluginPath, pluginName](kaguya::State* lua)
                    {
                        Plugins[pluginName] = dynamicLinker::dynamicLinker::make_new(pluginPath);
                        auto exposeFunction = Plugins[pluginName]->getFunction<void(kaguya::State*)>("loadBindings");
                        try
                        {
                            Plugins[pluginName]->open();
                            exposeFunction.init();
                            exposeFunction(lua);
                            Debug::Log->info("<Bindings:Plugin> : Loaded : {0}", pluginName);
                        }
                        catch (const dynamicLinker::dynamicLinkerException& e) {
                            Debug::Log->warn("<Bindings:Plugin> : Unloadable Plugin : {0}", pluginName);
                        }
                    });
                }
            }
        }
    }
}
