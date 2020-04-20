#include <Bindings/Animation/Animation.hpp>
#include <Bindings/Animation/Easing/Easing.hpp>
#include <Bindings/Animation/Exceptions/Exceptions.hpp>
#include <Bindings/Audio/Audio.hpp>
#include <Bindings/Audio/Exceptions/Exceptions.hpp>
#include <Bindings/BindingTree.hpp>
#include <Bindings/Bindings.hpp>
#include <Bindings/Bindings/Bindings.hpp>
#include <Bindings/Collision/Collision.hpp>
#include <Bindings/Component/Component.hpp>
#include <Bindings/Component/Exceptions/Exceptions.hpp>
#include <Bindings/Config/Config.hpp>
#include <Bindings/Debug/Debug.hpp>
#include <Bindings/Engine/Engine.hpp>
#include <Bindings/Engine/Exceptions/Exceptions.hpp>
#include <Bindings/Exceptions.hpp>
#include <Bindings/Graphics/Canvas/Canvas.hpp>
#include <Bindings/Graphics/Exceptions/Exceptions.hpp>
#include <Bindings/Graphics/Graphics.hpp>
#include <Bindings/Graphics/Shapes/Shapes.hpp>
#include <Bindings/Graphics/Utils/Utils.hpp>
#include <Bindings/Input/Exceptions/Exceptions.hpp>
#include <Bindings/Input/Input.hpp>
#include <Bindings/Modes/Modes.hpp>
#include <Bindings/Network/Network.hpp>
#include <Bindings/Obe/obe.hpp>
#include <Bindings/Scene/Exceptions/Exceptions.hpp>
#include <Bindings/Scene/Scene.hpp>
#include <Bindings/Script/DataBridge/DataBridge.hpp>
#include <Bindings/Script/Exceptions/Exceptions.hpp>
#include <Bindings/Script/Script.hpp>
#include <Bindings/System/Constraints/Constraints.hpp>
#include <Bindings/System/Exceptions/Exceptions.hpp>
#include <Bindings/System/Loaders/Loaders.hpp>
#include <Bindings/System/Package/Package.hpp>
#include <Bindings/System/System.hpp>
#include <Bindings/System/Workspace/Workspace.hpp>
#include <Bindings/Time/Time.hpp>
#include <Bindings/Transform/Transform.hpp>
#include <Bindings/Triggers/Triggers.hpp>
#include <Bindings/Types/Types.hpp>
#include <Bindings/Utils/Exec/Exec.hpp>
#include <Bindings/Utils/File/File.hpp>
#include <Bindings/Utils/Math/Math.hpp>
#include <Bindings/Utils/String/String.hpp>
#include <Bindings/Utils/Utils.hpp>
#include <Bindings/Utils/Vector/Vector.hpp>
#include <sol/sol.hpp>
namespace obe::Bindings
{
    void IndexAllBindings(sol::state_view state)
    {
        BindingTree BindTree("ObEngine");
        BindTree.add("obe", InitTreeNodeAsTable("obe"));
        BindTree.add("obe", InitTreeNodeAsTable("obe"));
        BindTree["obe"].add("Animation", InitTreeNodeAsTable("obe.Animation"));
        BindTree["obe"].add("Audio", InitTreeNodeAsTable("obe.Audio"));
        BindTree["obe"].add("Collision", InitTreeNodeAsTable("obe.Collision"));
        BindTree["obe"].add("Component", InitTreeNodeAsTable("obe.Component"));
        BindTree["obe"].add("Config", InitTreeNodeAsTable("obe.Config"));
        BindTree["obe"].add("Engine", InitTreeNodeAsTable("obe.Engine"));
        BindTree["obe"].add("Graphics", InitTreeNodeAsTable("obe.Graphics"));
        BindTree["obe"].add("Input", InitTreeNodeAsTable("obe.Input"));
        BindTree["obe"].add("Network", InitTreeNodeAsTable("obe.Network"));
        BindTree["obe"].add("Scene", InitTreeNodeAsTable("obe.Scene"));
        BindTree["obe"].add("Script", InitTreeNodeAsTable("obe.Script"));
        BindTree["obe"].add("System", InitTreeNodeAsTable("obe.System"));
        BindTree["obe"].add("Time", InitTreeNodeAsTable("obe.Time"));
        BindTree["obe"].add("Transform", InitTreeNodeAsTable("obe.Transform"));
        BindTree["obe"].add("Triggers", InitTreeNodeAsTable("obe.Triggers"));
        BindTree["obe"].add("Types", InitTreeNodeAsTable("obe.Types"));
        BindTree["obe"].add("Bindings", InitTreeNodeAsTable("obe.Bindings"));
        BindTree["obe"].add("Debug", InitTreeNodeAsTable("obe.Debug"));
        BindTree["obe"].add("Modes", InitTreeNodeAsTable("obe.Modes"));
        BindTree["obe"].add("Utils", InitTreeNodeAsTable("obe.Utils"));
        BindTree["obe"]["Animation"].add(
            "Exceptions", InitTreeNodeAsTable("obe.Animation.Exceptions"));
        BindTree["obe"]["Audio"].add(
            "Exceptions", InitTreeNodeAsTable("obe.Audio.Exceptions"));
        BindTree["obe"]["Component"].add(
            "Exceptions", InitTreeNodeAsTable("obe.Component.Exceptions"));
        BindTree["obe"]["Engine"].add(
            "Exceptions", InitTreeNodeAsTable("obe.Engine.Exceptions"));
        BindTree["obe"]["Graphics"].add(
            "Canvas", InitTreeNodeAsTable("obe.Graphics.Canvas"));
        BindTree["obe"]["Graphics"].add(
            "Exceptions", InitTreeNodeAsTable("obe.Graphics.Exceptions"));
        BindTree["obe"]["Graphics"].add(
            "Shapes", InitTreeNodeAsTable("obe.Graphics.Shapes"));
        BindTree["obe"]["Input"].add(
            "Exceptions", InitTreeNodeAsTable("obe.Input.Exceptions"));
        BindTree["obe"]["Scene"].add(
            "Exceptions", InitTreeNodeAsTable("obe.Scene.Exceptions"));
        BindTree["obe"]["Script"].add(
            "Exceptions", InitTreeNodeAsTable("obe.Script.Exceptions"));
        BindTree["obe"]["System"].add(
            "Exceptions", InitTreeNodeAsTable("obe.System.Exceptions"));
        BindTree["obe"]["System"].add(
            "Loaders", InitTreeNodeAsTable("obe.System.Loaders"));
        BindTree["obe"]["Utils"].add("Exec", InitTreeNodeAsTable("obe.Utils.Exec"));
        BindTree["obe"]["Animation"].add(
            "Easing", InitTreeNodeAsTable("obe.Animation.Easing"));
        BindTree["obe"]["Graphics"].add(
            "Utils", InitTreeNodeAsTable("obe.Graphics.Utils"));
        BindTree["obe"]["Script"].add(
            "DataBridge", InitTreeNodeAsTable("obe.Script.DataBridge"));
        BindTree["obe"]["System"].add(
            "Package", InitTreeNodeAsTable("obe.System.Package"));
        BindTree["obe"]["System"].add(
            "Workspace", InitTreeNodeAsTable("obe.System.Workspace"));
        BindTree["obe"]["Utils"].add("File", InitTreeNodeAsTable("obe.Utils.File"));
        BindTree["obe"]["Utils"].add("Math", InitTreeNodeAsTable("obe.Utils.Math"));
        BindTree["obe"]["Utils"].add("String", InitTreeNodeAsTable("obe.Utils.String"));
        BindTree["obe"]["Utils"].add("Vector", InitTreeNodeAsTable("obe.Utils.Vector"));
        BindTree["obe"]["System"].add(
            "Constraints", InitTreeNodeAsTable("obe.System.Constraints"));
        BindTree["obe"]["Animation"]
            .add("ClassAnimation", &obe::Animation::Bindings::LoadClassAnimation)
            .add(
                "ClassAnimationGroup", &obe::Animation::Bindings::LoadClassAnimationGroup)
            .add("ClassAnimator", &obe::Animation::Bindings::LoadClassAnimator)
            .add("ClassValueTweening", &obe::Animation::Bindings::LoadClassValueTweening)
            .add("EnumAnimationPlayMode",
                &obe::Animation::Bindings::LoadEnumAnimationPlayMode)
            .add(
                "EnumAnimationStatus", &obe::Animation::Bindings::LoadEnumAnimationStatus)
            .add("EnumAnimatorTargetScaleMode",
                &obe::Animation::Bindings::LoadEnumAnimatorTargetScaleMode)
            .add("FunctionStringToAnimationPlayMode",
                &obe::Animation::Bindings::LoadFunctionStringToAnimationPlayMode);

        BindTree["obe"]["Animation"]["Exceptions"]
            .add("ClassAnimationGroupTextureIndexOverflow",
                &obe::Animation::Exceptions::Bindings::
                    LoadClassAnimationGroupTextureIndexOverflow)
            .add("ClassAnimationTextureIndexOverflow",
                &obe::Animation::Exceptions::Bindings::
                    LoadClassAnimationTextureIndexOverflow)
            .add("ClassNoSelectedAnimation",
                &obe::Animation::Exceptions::Bindings::LoadClassNoSelectedAnimation)
            .add("ClassNoSelectedAnimationGroup",
                &obe::Animation::Exceptions::Bindings::LoadClassNoSelectedAnimationGroup)
            .add("ClassUnknownAnimation",
                &obe::Animation::Exceptions::Bindings::LoadClassUnknownAnimation)
            .add("ClassUnknownAnimationCommand",
                &obe::Animation::Exceptions::Bindings::LoadClassUnknownAnimationCommand)
            .add("ClassUnknownAnimationGroup",
                &obe::Animation::Exceptions::Bindings::LoadClassUnknownAnimationGroup)
            .add("ClassUnknownAnimationPlayMode",
                &obe::Animation::Exceptions::Bindings::LoadClassUnknownAnimationPlayMode)
            .add("ClassUnknownEasingFromEnum",
                &obe::Animation::Exceptions::Bindings::LoadClassUnknownEasingFromEnum)
            .add("ClassUnknownEasingFromString",
                &obe::Animation::Exceptions::Bindings::LoadClassUnknownEasingFromString);

        BindTree["obe"]["Audio"]
            .add("ClassAudioManager", &obe::Audio::Bindings::LoadClassAudioManager)
            .add("ClassSound", &obe::Audio::Bindings::LoadClassSound)
            .add("EnumLoadPolicy", &obe::Audio::Bindings::LoadEnumLoadPolicy)
            .add("EnumSoundStatus", &obe::Audio::Bindings::LoadEnumSoundStatus);

        BindTree["obe"]["Audio"]["Exceptions"].add("ClassAudioFileNotFound",
            &obe::Audio::Exceptions::Bindings::LoadClassAudioFileNotFound);

        BindTree["obe"]["Collision"]
            .add("ClassPolygonalCollider",
                &obe::Collision::Bindings::LoadClassPolygonalCollider)
            .add("ClassTrajectory", &obe::Collision::Bindings::LoadClassTrajectory)
            .add(
                "ClassTrajectoryNode", &obe::Collision::Bindings::LoadClassTrajectoryNode)
            .add("EnumColliderTagType",
                &obe::Collision::Bindings::LoadEnumColliderTagType);

        BindTree["obe"]["Component"].add(
            "ClassComponentBase", &obe::Component::Bindings::LoadClassComponentBase);

        BindTree["obe"]["Component"]["Exceptions"].add("ClassComponentIdAlreadyTaken",
            &obe::Component::Exceptions::Bindings::LoadClassComponentIdAlreadyTaken);

        BindTree["obe"]["Config"].add("ClassConfigurationManager",
            &obe::Config::Bindings::LoadClassConfigurationManager);

        BindTree["obe"]
            .add("ClassDebugInfo", &obe::Bindings::LoadClassDebugInfo)
            .add("ClassException", &obe::Bindings::LoadClassException)
            .add("FunctionInitEngine", &obe::Bindings::LoadFunctionInitEngine);

        BindTree["obe"]["Engine"]
            .add("ClassEngine", &obe::Engine::Bindings::LoadClassEngine)
            .add("ClassResourceManagedObject",
                &obe::Engine::Bindings::LoadClassResourceManagedObject)
            .add(
                "ClassResourceManager", &obe::Engine::Bindings::LoadClassResourceManager);

        BindTree["obe"]["Engine"]["Exceptions"]
            .add("ClassBootScriptMissing",
                &obe::Engine::Exceptions::Bindings::LoadClassBootScriptMissing)
            .add("ClassFontNotFound",
                &obe::Engine::Exceptions::Bindings::LoadClassFontNotFound)
            .add("ClassTextureNotFound",
                &obe::Engine::Exceptions::Bindings::LoadClassTextureNotFound);

        BindTree["obe"]["Graphics"]["Canvas"]
            .add("ClassBezier", &obe::Graphics::Canvas::Bindings::LoadClassBezier)
            .add("ClassCanvas", &obe::Graphics::Canvas::Bindings::LoadClassCanvas)
            .add("ClassCanvasElement",
                &obe::Graphics::Canvas::Bindings::LoadClassCanvasElement)
            .add("ClassCanvasPositionable",
                &obe::Graphics::Canvas::Bindings::LoadClassCanvasPositionable)
            .add("ClassCircle", &obe::Graphics::Canvas::Bindings::LoadClassCircle)
            .add("ClassLine", &obe::Graphics::Canvas::Bindings::LoadClassLine)
            .add("ClassPolygon", &obe::Graphics::Canvas::Bindings::LoadClassPolygon)
            .add("ClassRectangle", &obe::Graphics::Canvas::Bindings::LoadClassRectangle)
            .add("ClassText", &obe::Graphics::Canvas::Bindings::LoadClassText)
            .add("EnumCanvasElementType",
                &obe::Graphics::Canvas::Bindings::LoadEnumCanvasElementType)
            .add("EnumTextHorizontalAlign",
                &obe::Graphics::Canvas::Bindings::LoadEnumTextHorizontalAlign)
            .add("EnumTextVerticalAlign",
                &obe::Graphics::Canvas::Bindings::LoadEnumTextVerticalAlign)
            .add("FunctionCanvasElementTypeToString",
                &obe::Graphics::Canvas::Bindings::LoadFunctionCanvasElementTypeToString);

        BindTree["obe"]["Graphics"]
            .add("ClassColor", &obe::Graphics::Bindings::LoadClassColor)
            .add("ClassFont", &obe::Graphics::Bindings::LoadClassFont)
            .add("ClassPositionTransformer",
                &obe::Graphics::Bindings::LoadClassPositionTransformer)
            .add("ClassRenderTarget", &obe::Graphics::Bindings::LoadClassRenderTarget)
            .add("ClassRichText", &obe::Graphics::Bindings::LoadClassRichText)
            .add("ClassShader", &obe::Graphics::Bindings::LoadClassShader)
            .add("ClassSprite", &obe::Graphics::Bindings::LoadClassSprite)
            .add("ClassSpriteHandlePoint",
                &obe::Graphics::Bindings::LoadClassSpriteHandlePoint)
            .add("ClassText", &obe::Graphics::Bindings::LoadClassText)
            .add("ClassTexture", &obe::Graphics::Bindings::LoadClassTexture)
            .add("EnumSpriteHandlePointType",
                &obe::Graphics::Bindings::LoadEnumSpriteHandlePointType)
            .add("FunctionInitPositionTransformer",
                &obe::Graphics::Bindings::LoadFunctionInitPositionTransformer)
            .add("FunctionMakeNullTexture",
                &obe::Graphics::Bindings::LoadFunctionMakeNullTexture)
            .add("GlobalTransformers", &obe::Graphics::Bindings::LoadGlobalTransformers)
            .add("GlobalParallax", &obe::Graphics::Bindings::LoadGlobalParallax)
            .add("GlobalCamera", &obe::Graphics::Bindings::LoadGlobalCamera)
            .add("GlobalPosition", &obe::Graphics::Bindings::LoadGlobalPosition);

        BindTree["obe"]["Graphics"]["Exceptions"]
            .add("ClassCanvasElementAlreadyExists",
                &obe::Graphics::Exceptions::Bindings::LoadClassCanvasElementAlreadyExists)
            .add("ClassInvalidColorName",
                &obe::Graphics::Exceptions::Bindings::LoadClassInvalidColorName)
            .add("ClassReadOnlyTexture",
                &obe::Graphics::Exceptions::Bindings::LoadClassReadOnlyTexture);

        BindTree["obe"]["Graphics"]["Shapes"]
            .add("ClassCircle", &obe::Graphics::Shapes::Bindings::LoadClassCircle)
            .add("ClassPolygon", &obe::Graphics::Shapes::Bindings::LoadClassPolygon)
            .add("ClassRectangle", &obe::Graphics::Shapes::Bindings::LoadClassRectangle)
            .add("ClassText", &obe::Graphics::Shapes::Bindings::LoadClassText);

        BindTree["obe"]["Input"]["Exceptions"]
            .add("ClassInputButtonInvalidOperation",
                &obe::Input::Exceptions::Bindings::LoadClassInputButtonInvalidOperation)
            .add("ClassInvalidInputButtonState",
                &obe::Input::Exceptions::Bindings::LoadClassInvalidInputButtonState)
            .add("ClassUnknownInputAction",
                &obe::Input::Exceptions::Bindings::LoadClassUnknownInputAction)
            .add("ClassUnknownInputButton",
                &obe::Input::Exceptions::Bindings::LoadClassUnknownInputButton);

        BindTree["obe"]["Input"]
            .add("ClassInputAction", &obe::Input::Bindings::LoadClassInputAction)
            .add(
                "ClassInputActionEvent", &obe::Input::Bindings::LoadClassInputActionEvent)
            .add("ClassInputButton", &obe::Input::Bindings::LoadClassInputButton)
            .add("ClassInputButtonMonitor",
                &obe::Input::Bindings::LoadClassInputButtonMonitor)
            .add("ClassInputCondition", &obe::Input::Bindings::LoadClassInputCondition)
            .add("ClassInputManager", &obe::Input::Bindings::LoadClassInputManager)
            .add("EnumAxisThresholdDirection",
                &obe::Input::Bindings::LoadEnumAxisThresholdDirection)
            .add("EnumInputButtonState", &obe::Input::Bindings::LoadEnumInputButtonState)
            .add("EnumInputType", &obe::Input::Bindings::LoadEnumInputType)
            .add("FunctionInputButtonStateToString",
                &obe::Input::Bindings::LoadFunctionInputButtonStateToString)
            .add("FunctionStringToInputButtonState",
                &obe::Input::Bindings::LoadFunctionStringToInputButtonState)
            .add("FunctionInputTypeToString",
                &obe::Input::Bindings::LoadFunctionInputTypeToString);

        BindTree["obe"]["Network"]
            .add("ClassLuaPacket", &obe::Network::Bindings::LoadClassLuaPacket)
            .add("ClassNetworkHandler", &obe::Network::Bindings::LoadClassNetworkHandler)
            .add("ClassTcpServer", &obe::Network::Bindings::LoadClassTcpServer)
            .add("ClassTcpSocket", &obe::Network::Bindings::LoadClassTcpSocket);

        BindTree["obe"]["Scene"]
            .add("ClassCamera", &obe::Scene::Bindings::LoadClassCamera)
            .add("ClassScene", &obe::Scene::Bindings::LoadClassScene)
            .add("ClassSceneNode", &obe::Scene::Bindings::LoadClassSceneNode)
            .add("FunctionSceneGetGameObjectProxy",
                &obe::Scene::Bindings::LoadFunctionSceneGetGameObjectProxy)
            .add("FunctionSceneCreateGameObjectProxy",
                &obe::Scene::Bindings::LoadFunctionSceneCreateGameObjectProxy);

        BindTree["obe"]["Scene"]["Exceptions"].add("ClassChildNotInSceneNode",
            &obe::Scene::Exceptions::Bindings::LoadClassChildNotInSceneNode);

        BindTree["obe"]["Script"]["Exceptions"].add("ClassNoScriptComponent",
            &obe::Script::Exceptions::Bindings::LoadClassNoScriptComponent);

        BindTree["obe"]["Script"]
            .add("ClassGameObject", &obe::Script::Bindings::LoadClassGameObject)
            .add("ClassGameObjectDatabase",
                &obe::Script::Bindings::LoadClassGameObjectDatabase);

        BindTree["obe"]["System"]
            .add("ClassCursor", &obe::System::Bindings::LoadClassCursor)
            .add("ClassLoaderMultipleResult",
                &obe::System::Bindings::LoadClassLoaderMultipleResult)
            .add("ClassLoaderResult", &obe::System::Bindings::LoadClassLoaderResult)
            .add("ClassMountablePath", &obe::System::Bindings::LoadClassMountablePath)
            .add("ClassPath", &obe::System::Bindings::LoadClassPath)
            .add("ClassPlugin", &obe::System::Bindings::LoadClassPlugin)
            .add("ClassWindow", &obe::System::Bindings::LoadClassWindow)
            .add("EnumMountablePathType",
                &obe::System::Bindings::LoadEnumMountablePathType)
            .add("EnumPathType", &obe::System::Bindings::LoadEnumPathType)
            .add("EnumWindowContext", &obe::System::Bindings::LoadEnumWindowContext);

        BindTree["obe"]["System"]["Exceptions"].add("ClassResourceNotFound",
            &obe::System::Exceptions::Bindings::LoadClassResourceNotFound);

        BindTree["obe"]["System"]["Loaders"]
            .add("GlobalTextureLoader",
                &obe::System::Loaders::Bindings::LoadGlobalTextureLoader)
            .add(
                "GlobalDataLoader", &obe::System::Loaders::Bindings::LoadGlobalDataLoader)
            .add(
                "GlobalFontLoader", &obe::System::Loaders::Bindings::LoadGlobalFontLoader)
            .add("GlobalDirPathLoader",
                &obe::System::Loaders::Bindings::LoadGlobalDirPathLoader)
            .add("GlobalFilePathLoader",
                &obe::System::Loaders::Bindings::LoadGlobalFilePathLoader);

        BindTree["obe"]["Time"]
            .add("ClassChronometer", &obe::Time::Bindings::LoadClassChronometer)
            .add("ClassFramerateCounter", &obe::Time::Bindings::LoadClassFramerateCounter)
            .add("ClassFramerateManager", &obe::Time::Bindings::LoadClassFramerateManager)
            .add("FunctionEpoch", &obe::Time::Bindings::LoadFunctionEpoch)
            .add("GlobalSeconds", &obe::Time::Bindings::LoadGlobalSeconds)
            .add("GlobalMilliseconds", &obe::Time::Bindings::LoadGlobalMilliseconds)
            .add("GlobalMicroseconds", &obe::Time::Bindings::LoadGlobalMicroseconds)
            .add("GlobalMinutes", &obe::Time::Bindings::LoadGlobalMinutes)
            .add("GlobalHours", &obe::Time::Bindings::LoadGlobalHours)
            .add("GlobalDays", &obe::Time::Bindings::LoadGlobalDays)
            .add("GlobalWeeks", &obe::Time::Bindings::LoadGlobalWeeks);

        BindTree["obe"]["Transform"]
            .add("ClassMatrix2D", &obe::Transform::Bindings::LoadClassMatrix2D)
            .add("ClassMovable", &obe::Transform::Bindings::LoadClassMovable)
            .add("ClassPolygon", &obe::Transform::Bindings::LoadClassPolygon)
            .add("ClassPolygonPoint", &obe::Transform::Bindings::LoadClassPolygonPoint)
            .add(
                "ClassPolygonSegment", &obe::Transform::Bindings::LoadClassPolygonSegment)
            .add("ClassRect", &obe::Transform::Bindings::LoadClassRect)
            .add("ClassReferential", &obe::Transform::Bindings::LoadClassReferential)
            .add("ClassUnitBasedObject",
                &obe::Transform::Bindings::LoadClassUnitBasedObject)
            .add("ClassUnitVector", &obe::Transform::Bindings::LoadClassUnitVector)
            .add("EnumUnits", &obe::Transform::Bindings::LoadEnumUnits)
            .add("FunctionStringToUnits",
                &obe::Transform::Bindings::LoadFunctionStringToUnits)
            .add("FunctionUnitsToString",
                &obe::Transform::Bindings::LoadFunctionUnitsToString);

        BindTree["obe"]["Triggers"]
            .add("ClassCallbackScheduler",
                &obe::Triggers::Bindings::LoadClassCallbackScheduler)
            .add("ClassTrigger", &obe::Triggers::Bindings::LoadClassTrigger)
            .add("ClassTriggerEnv", &obe::Triggers::Bindings::LoadClassTriggerEnv)
            .add("ClassTriggerGroup", &obe::Triggers::Bindings::LoadClassTriggerGroup)
            .add("ClassTriggerManager", &obe::Triggers::Bindings::LoadClassTriggerManager)
            .add("EnumCallbackSchedulerState",
                &obe::Triggers::Bindings::LoadEnumCallbackSchedulerState);

        BindTree["obe"]["Types"]
            .add("ClassIdentifiable", &obe::Types::Bindings::LoadClassIdentifiable)
            .add("ClassProtectedIdentifiable",
                &obe::Types::Bindings::LoadClassProtectedIdentifiable)
            .add("ClassSelectable", &obe::Types::Bindings::LoadClassSelectable)
            .add("ClassSerializable", &obe::Types::Bindings::LoadClassSerializable)
            .add("ClassTogglable", &obe::Types::Bindings::LoadClassTogglable);

        BindTree["obe"]["Utils"]["Exec"].add(
            "ClassRunArgsParser", &obe::Utils::Exec::Bindings::LoadClassRunArgsParser);

        BindTree["obe"]["Animation"]["Easing"]
            .add("EnumEasingType", &obe::Animation::Easing::Bindings::LoadEnumEasingType)
            .add("FunctionLinear", &obe::Animation::Easing::Bindings::LoadFunctionLinear)
            .add("FunctionInSine", &obe::Animation::Easing::Bindings::LoadFunctionInSine)
            .add(
                "FunctionOutSine", &obe::Animation::Easing::Bindings::LoadFunctionOutSine)
            .add("FunctionInOutSine",
                &obe::Animation::Easing::Bindings::LoadFunctionInOutSine)
            .add("FunctionInQuad", &obe::Animation::Easing::Bindings::LoadFunctionInQuad)
            .add(
                "FunctionOutQuad", &obe::Animation::Easing::Bindings::LoadFunctionOutQuad)
            .add("FunctionInOutQuad",
                &obe::Animation::Easing::Bindings::LoadFunctionInOutQuad)
            .add(
                "FunctionInCubic", &obe::Animation::Easing::Bindings::LoadFunctionInCubic)
            .add("FunctionOutCubic",
                &obe::Animation::Easing::Bindings::LoadFunctionOutCubic)
            .add("FunctionInOutCubic",
                &obe::Animation::Easing::Bindings::LoadFunctionInOutCubic)
            .add(
                "FunctionInQuart", &obe::Animation::Easing::Bindings::LoadFunctionInQuart)
            .add("FunctionOutQuart",
                &obe::Animation::Easing::Bindings::LoadFunctionOutQuart)
            .add("FunctionInOutQuart",
                &obe::Animation::Easing::Bindings::LoadFunctionInOutQuart)
            .add(
                "FunctionInQuint", &obe::Animation::Easing::Bindings::LoadFunctionInQuint)
            .add("FunctionOutQuint",
                &obe::Animation::Easing::Bindings::LoadFunctionOutQuint)
            .add("FunctionInOutQuint",
                &obe::Animation::Easing::Bindings::LoadFunctionInOutQuint)
            .add("FunctionInExpo", &obe::Animation::Easing::Bindings::LoadFunctionInExpo)
            .add(
                "FunctionOutExpo", &obe::Animation::Easing::Bindings::LoadFunctionOutExpo)
            .add("FunctionInOutExpo",
                &obe::Animation::Easing::Bindings::LoadFunctionInOutExpo)
            .add("FunctionInCirc", &obe::Animation::Easing::Bindings::LoadFunctionInCirc)
            .add(
                "FunctionOutCirc", &obe::Animation::Easing::Bindings::LoadFunctionOutCirc)
            .add("FunctionInOutCirc",
                &obe::Animation::Easing::Bindings::LoadFunctionInOutCirc)
            .add("FunctionInBack", &obe::Animation::Easing::Bindings::LoadFunctionInBack)
            .add(
                "FunctionOutBack", &obe::Animation::Easing::Bindings::LoadFunctionOutBack)
            .add("FunctionInOutBack",
                &obe::Animation::Easing::Bindings::LoadFunctionInOutBack)
            .add("FunctionInElastic",
                &obe::Animation::Easing::Bindings::LoadFunctionInElastic)
            .add("FunctionOutElastic",
                &obe::Animation::Easing::Bindings::LoadFunctionOutElastic)
            .add("FunctionInOutElastic",
                &obe::Animation::Easing::Bindings::LoadFunctionInOutElastic)
            .add("FunctionInBounce",
                &obe::Animation::Easing::Bindings::LoadFunctionInBounce)
            .add("FunctionOutBounce",
                &obe::Animation::Easing::Bindings::LoadFunctionOutBounce)
            .add("FunctionInOutBounce",
                &obe::Animation::Easing::Bindings::LoadFunctionInOutBounce)
            .add("FunctionGet", &obe::Animation::Easing::Bindings::LoadFunctionGet);

        BindTree["obe"]["Bindings"].add("FunctionIndexAllBindings",
            &obe::Bindings::Bindings::LoadFunctionIndexAllBindings);

        BindTree["obe"]["Debug"]
            .add("FunctionInitLogger", &obe::Debug::Bindings::LoadFunctionInitLogger)
            .add("GlobalLog", &obe::Debug::Bindings::LoadGlobalLog);

        BindTree["obe"]["Graphics"]["Utils"]
            .add("FunctionDrawPoint",
                &obe::Graphics::Utils::Bindings::LoadFunctionDrawPoint)
            .add(
                "FunctionDrawLine", &obe::Graphics::Utils::Bindings::LoadFunctionDrawLine)
            .add("FunctionDrawPolygon",
                &obe::Graphics::Utils::Bindings::LoadFunctionDrawPolygon);

        BindTree["obe"]["Modes"].add(
            "FunctionStartGame", &obe::Modes::Bindings::LoadFunctionStartGame);

        BindTree["obe"]["Script"]["DataBridge"]
            .add("FunctionDataToLua",
                &obe::Script::DataBridge::Bindings::LoadFunctionDataToLua)
            .add("FunctionLuaToData",
                &obe::Script::DataBridge::Bindings::LoadFunctionLuaToData)
            .add("FunctionComplexNodeToLuaTable",
                &obe::Script::DataBridge::Bindings::LoadFunctionComplexNodeToLuaTable)
            .add("FunctionDataNodeToLuaElement",
                &obe::Script::DataBridge::Bindings::LoadFunctionDataNodeToLuaElement)
            .add("FunctionArrayNodeToLuaTable",
                &obe::Script::DataBridge::Bindings::LoadFunctionArrayNodeToLuaTable)
            .add("FunctionLuaTableToComplexNode",
                &obe::Script::DataBridge::Bindings::LoadFunctionLuaTableToComplexNode)
            .add("FunctionLuaElementToDataNode",
                &obe::Script::DataBridge::Bindings::LoadFunctionLuaElementToDataNode)
            .add("FunctionLuaTableToArrayNode",
                &obe::Script::DataBridge::Bindings::LoadFunctionLuaTableToArrayNode);

        BindTree["obe"]["System"]["Package"]
            .add("FunctionGetPackageLocation",
                &obe::System::Package::Bindings::LoadFunctionGetPackageLocation)
            .add("FunctionPackageExists",
                &obe::System::Package::Bindings::LoadFunctionPackageExists)
            .add("FunctionInstall", &obe::System::Package::Bindings::LoadFunctionInstall)
            .add("FunctionLoad", &obe::System::Package::Bindings::LoadFunctionLoad);

        BindTree["obe"]["System"]["Workspace"]
            .add("FunctionGetWorkspaceLocation",
                &obe::System::Workspace::Bindings::LoadFunctionGetWorkspaceLocation)
            .add("FunctionWorkspaceExists",
                &obe::System::Workspace::Bindings::LoadFunctionWorkspaceExists)
            .add("FunctionLoad", &obe::System::Workspace::Bindings::LoadFunctionLoad);

        BindTree["obe"]["Utils"]["File"]
            .add("FunctionGetDirectoryList",
                &obe::Utils::File::Bindings::LoadFunctionGetDirectoryList)
            .add("FunctionGetFileList",
                &obe::Utils::File::Bindings::LoadFunctionGetFileList)
            .add(
                "FunctionFileExists", &obe::Utils::File::Bindings::LoadFunctionFileExists)
            .add("FunctionDirectoryExists",
                &obe::Utils::File::Bindings::LoadFunctionDirectoryExists)
            .add("FunctionCreateDirectory",
                &obe::Utils::File::Bindings::LoadFunctionCreateDirectory)
            .add(
                "FunctionCreateFile", &obe::Utils::File::Bindings::LoadFunctionCreateFile)
            .add("FunctionCopy", &obe::Utils::File::Bindings::LoadFunctionCopy)
            .add(
                "FunctionDeleteFile", &obe::Utils::File::Bindings::LoadFunctionDeleteFile)
            .add("FunctionDeleteDirectory",
                &obe::Utils::File::Bindings::LoadFunctionDeleteDirectory)
            .add("FunctionGetCurrentDirectory",
                &obe::Utils::File::Bindings::LoadFunctionGetCurrentDirectory)
            .add("FunctionSeparator", &obe::Utils::File::Bindings::LoadFunctionSeparator);

        BindTree["obe"]["Utils"]["Math"]
            .add("FunctionRandint", &obe::Utils::Math::Bindings::LoadFunctionRandint)
            .add("FunctionRandfloat", &obe::Utils::Math::Bindings::LoadFunctionRandfloat)
            .add("FunctionGetMin", &obe::Utils::Math::Bindings::LoadFunctionGetMin)
            .add("FunctionGetMax", &obe::Utils::Math::Bindings::LoadFunctionGetMax)
            .add("FunctionIsBetween", &obe::Utils::Math::Bindings::LoadFunctionIsBetween)
            .add("FunctionIsDoubleInt",
                &obe::Utils::Math::Bindings::LoadFunctionIsDoubleInt)
            .add("FunctionSign", &obe::Utils::Math::Bindings::LoadFunctionSign)
            .add("FunctionConvertToRadian",
                &obe::Utils::Math::Bindings::LoadFunctionConvertToRadian)
            .add("FunctionConvertToDegree",
                &obe::Utils::Math::Bindings::LoadFunctionConvertToDegree)
            .add("FunctionNormalize", &obe::Utils::Math::Bindings::LoadFunctionNormalize)
            .add("GlobalPi", &obe::Utils::Math::Bindings::LoadGlobalPi);

        BindTree["obe"]["Utils"]["String"]
            .add("FunctionSplit", &obe::Utils::String::Bindings::LoadFunctionSplit)
            .add("FunctionOccurencesInString",
                &obe::Utils::String::Bindings::LoadFunctionOccurencesInString)
            .add("FunctionIsStringAlpha",
                &obe::Utils::String::Bindings::LoadFunctionIsStringAlpha)
            .add("FunctionIsStringAlphaNumeric",
                &obe::Utils::String::Bindings::LoadFunctionIsStringAlphaNumeric)
            .add("FunctionIsStringNumeric",
                &obe::Utils::String::Bindings::LoadFunctionIsStringNumeric)
            .add("FunctionIsStringInt",
                &obe::Utils::String::Bindings::LoadFunctionIsStringInt)
            .add("FunctionIsStringFloat",
                &obe::Utils::String::Bindings::LoadFunctionIsStringFloat)
            .add("FunctionReplace", &obe::Utils::String::Bindings::LoadFunctionReplace)
            .add("FunctionIsSurroundedBy",
                &obe::Utils::String::Bindings::LoadFunctionIsSurroundedBy)
            .add("FunctionGetRandomKey",
                &obe::Utils::String::Bindings::LoadFunctionGetRandomKey)
            .add("FunctionContains", &obe::Utils::String::Bindings::LoadFunctionContains)
            .add("FunctionStartsWith",
                &obe::Utils::String::Bindings::LoadFunctionStartsWith)
            .add("FunctionEndsWith", &obe::Utils::String::Bindings::LoadFunctionEndsWith)
            .add("FunctionDistance", &obe::Utils::String::Bindings::LoadFunctionDistance)
            .add("GlobalAlphabet", &obe::Utils::String::Bindings::LoadGlobalAlphabet)
            .add("GlobalNumbers", &obe::Utils::String::Bindings::LoadGlobalNumbers);

        BindTree["obe"]["Utils"]["Vector"]
            .add("FunctionContains", &obe::Utils::Vector::Bindings::LoadFunctionContains)
            .add("FunctionJoin", &obe::Utils::Vector::Bindings::LoadFunctionJoin);

        BindTree["obe"]["System"]["Constraints"].add(
            "GlobalDefault", &obe::System::Constraints::Bindings::LoadGlobalDefault);

        BindTree(state);
    }
}