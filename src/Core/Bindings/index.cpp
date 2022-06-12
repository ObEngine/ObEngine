#include <Bindings/Config.hpp>
#include <Bindings/Exceptions.hpp>
#include <Bindings/Patches.hpp>
#include <Bindings/obe/Animation/Animation.hpp>
#include <Bindings/obe/Animation/Easing/Easing.hpp>
#include <Bindings/obe/Animation/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Audio/Audio.hpp>
#include <Bindings/obe/Audio/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Bindings/Bindings.hpp>
#include <Bindings/obe/Collision/Collision.hpp>
#include <Bindings/obe/Collision/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Component/Component.hpp>
#include <Bindings/obe/Component/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Config/Config.hpp>
#include <Bindings/obe/Config/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Config/Validators/Validators.hpp>
#include <Bindings/obe/Debug/Debug.hpp>
#include <Bindings/obe/Debug/Render/Render.hpp>
#include <Bindings/obe/Engine/Engine.hpp>
#include <Bindings/obe/Engine/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Event/Event.hpp>
#include <Bindings/obe/Event/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Events/Actions/Actions.hpp>
#include <Bindings/obe/Events/Cursor/Cursor.hpp>
#include <Bindings/obe/Events/Game/Game.hpp>
#include <Bindings/obe/Events/Keys/Keys.hpp>
#include <Bindings/obe/Events/Network/Network.hpp>
#include <Bindings/obe/Events/Scene/Scene.hpp>
#include <Bindings/obe/Graphics/Canvas/Canvas.hpp>
#include <Bindings/obe/Graphics/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Graphics/Graphics.hpp>
#include <Bindings/obe/Graphics/Shapes/Shapes.hpp>
#include <Bindings/obe/Graphics/Utils/Utils.hpp>
#include <Bindings/obe/Input/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Input/Input.hpp>
#include <Bindings/obe/Network/Network.hpp>
#include <Bindings/obe/Scene/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Scene/Scene.hpp>
#include <Bindings/obe/Script/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Script/Script.hpp>
#include <Bindings/obe/Script/ViliLuaBridge/ViliLuaBridge.hpp>
#include <Bindings/obe/System/Constraints/Constraints.hpp>
#include <Bindings/obe/System/Exceptions/Exceptions.hpp>
#include <Bindings/obe/System/Package/Package.hpp>
#include <Bindings/obe/System/Prefixes/Prefixes.hpp>
#include <Bindings/obe/System/Priorities/Priorities.hpp>
#include <Bindings/obe/System/Project/Prefixes/Prefixes.hpp>
#include <Bindings/obe/System/Project/Project.hpp>
#include <Bindings/obe/System/System.hpp>
#include <Bindings/obe/Tiles/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Tiles/Tiles.hpp>
#include <Bindings/obe/Time/Time.hpp>
#include <Bindings/obe/Transform/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Transform/Transform.hpp>
#include <Bindings/obe/Types/Types.hpp>
#include <Bindings/obe/Utils/Exec/Exec.hpp>
#include <Bindings/obe/Utils/File/File.hpp>
#include <Bindings/obe/Utils/Math/Math.hpp>
#include <Bindings/obe/Utils/String/String.hpp>
#include <Bindings/obe/Utils/Utils.hpp>
#include <Bindings/obe/Utils/Vector/Vector.hpp>
#include <Bindings/obe/obe.hpp>
#include <Bindings/vili/exceptions/exceptions.hpp>
#include <Bindings/vili/parser/parser.hpp>
#include <Bindings/vili/parser/rules/rules.hpp>
#include <Bindings/vili/utils/string/string.hpp>
#include <Bindings/vili/vili.hpp>
#include <Bindings/vili/writer/writer.hpp>
#include <sol/sol.hpp>
namespace obe::Bindings
{
    void IndexCoreBindings(sol::state_view state)
    {
        state["obe"].get_or_create<sol::table>();
        state["vili"].get_or_create<sol::table>();
        state["obe"]["animation"].get_or_create<sol::table>();
        state["obe"]["audio"].get_or_create<sol::table>();
        state["obe"]["collision"].get_or_create<sol::table>();
        state["obe"]["Component"].get_or_create<sol::table>();
        state["obe"]["config"].get_or_create<sol::table>();
        state["obe"]["engine"].get_or_create<sol::table>();
        state["obe"]["event"].get_or_create<sol::table>();
        state["obe"]["graphics"].get_or_create<sol::table>();
        state["obe"]["Input"].get_or_create<sol::table>();
        state["obe"]["Network"].get_or_create<sol::table>();
        state["obe"]["Scene"].get_or_create<sol::table>();
        state["obe"]["Script"].get_or_create<sol::table>();
        state["obe"]["System"].get_or_create<sol::table>();
        state["obe"]["Tiles"].get_or_create<sol::table>();
        state["obe"]["Time"].get_or_create<sol::table>();
        state["obe"]["Transform"].get_or_create<sol::table>();
        state["obe"]["Types"].get_or_create<sol::table>();
        state["obe"]["Utils"].get_or_create<sol::table>();
        state["vili"]["exceptions"].get_or_create<sol::table>();
        state["vili"]["parser"].get_or_create<sol::table>();
        state["vili"]["writer"].get_or_create<sol::table>();
        state["obe"]["Bindings"].get_or_create<sol::table>();
        state["obe"]["debug"].get_or_create<sol::table>();
        state["obe"]["events"].get_or_create<sol::table>();
        state["vili"]["utils"].get_or_create<sol::table>();
        state["obe"]["animation"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["audio"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["collision"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["Component"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["config"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["engine"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["event"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["graphics"]["canvas"].get_or_create<sol::table>();
        state["obe"]["graphics"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["graphics"]["shapes"].get_or_create<sol::table>();
        state["obe"]["Input"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["Scene"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["Script"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["System"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["System"]["Project"].get_or_create<sol::table>();
        state["obe"]["Tiles"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["Transform"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["Utils"]["Exec"].get_or_create<sol::table>();
        state["obe"]["events"]["Actions"].get_or_create<sol::table>();
        state["obe"]["events"]["Cursor"].get_or_create<sol::table>();
        state["obe"]["events"]["game"].get_or_create<sol::table>();
        state["obe"]["events"]["Keys"].get_or_create<sol::table>();
        state["obe"]["events"]["Network"].get_or_create<sol::table>();
        state["obe"]["events"]["Scene"].get_or_create<sol::table>();
        state["obe"]["graphics"]["utils"].get_or_create<sol::table>();
        state["vili"]["parser"]["rules"].get_or_create<sol::table>();
        state["obe"]["animation"]["easing"].get_or_create<sol::table>();
        state["obe"]["config"]["Templates"].get_or_create<sol::table>();
        state["obe"]["config"]["validators"].get_or_create<sol::table>();
        state["obe"]["debug"]["render"].get_or_create<sol::table>();
        state["obe"]["Script"]["ViliLuaBridge"].get_or_create<sol::table>();
        state["obe"]["System"]["Package"].get_or_create<sol::table>();
        state["obe"]["Utils"]["File"].get_or_create<sol::table>();
        state["obe"]["Utils"]["Math"].get_or_create<sol::table>();
        state["obe"]["Utils"]["String"].get_or_create<sol::table>();
        state["obe"]["Utils"]["Vector"].get_or_create<sol::table>();
        state["vili"]["utils"]["string"].get_or_create<sol::table>();
        state["obe"]["System"]["Constraints"].get_or_create<sol::table>();
        state["obe"]["System"]["Prefixes"].get_or_create<sol::table>();
        state["obe"]["System"]["Priorities"].get_or_create<sol::table>();
        state["obe"]["System"]["Project"]["Prefixes"].get_or_create<sol::table>();

        obe::System::Bindings::LoadClassMountablePath(state);
        obe::System::Bindings::LoadClassFindResult(state);
        obe::System::Bindings::LoadClassPath(state);
        obe::animation::Bindings::LoadClassAnimation(state);
        obe::animation::Bindings::LoadClassAnimationGroup(state);
        obe::animation::Bindings::LoadClassAnimationState(state);
        obe::animation::Bindings::LoadClassAnimator(state);
        obe::animation::Bindings::LoadClassAnimatorState(state);
        obe::animation::Bindings::LoadClassColorTweening(state);
        obe::animation::Bindings::LoadClassUnitVectorTweening(state);
        obe::animation::Bindings::LoadClassRectTweening(state);
        obe::animation::Bindings::LoadClassTrajectoryTweening(state);
        obe::animation::Bindings::LoadClassIntTweening(state);
        obe::animation::Bindings::LoadClassDoubleTweening(state);
        obe::animation::Bindings::LoadEnumAnimationPlayMode(state);
        obe::animation::Bindings::LoadEnumAnimationStatus(state);
        obe::animation::Bindings::LoadEnumAnimatorTargetScaleMode(state);
        obe::animation::Bindings::LoadFunctionTemplateSpecializationExistsImpl(state);
        obe::animation::Bindings::LoadFunctionTween(state);
        obe::animation::exceptions::Bindings::LoadClassAnimationGroupTextureIndexOverflow(state);
        obe::animation::exceptions::Bindings::LoadClassAnimationTextureIndexOverflow(state);
        obe::animation::exceptions::Bindings::LoadClassInvalidAnimationFile(state);
        obe::animation::exceptions::Bindings::LoadClassNoSelectedAnimation(state);
        obe::animation::exceptions::Bindings::LoadClassNoSelectedAnimationGroup(state);
        obe::animation::exceptions::Bindings::LoadClassUnknownAnimation(state);
        obe::animation::exceptions::Bindings::LoadClassUnknownAnimationGroup(state);
        obe::animation::exceptions::Bindings::LoadClassUnknownEasingFromEnum(state);
        obe::animation::exceptions::Bindings::LoadClassUnknownEasingFromString(state);
        obe::audio::Bindings::LoadClassAudioManager(state);
        obe::audio::Bindings::LoadClassSound(state);
        obe::audio::Bindings::LoadEnumLoadPolicy(state);
        obe::audio::Bindings::LoadEnumSoundStatus(state);
        obe::audio::exceptions::Bindings::LoadClassAudioFileNotFound(state);
        obe::Bindings::LoadClassBaseException(state);
        obe::Bindings::LoadClassDebugInfo(state);
        obe::Bindings::LoadFunctionGetTypeName(state);
        obe::Bindings::LoadFunctionInitEngine(state);
        obe::Bindings::LoadGlobalObengineProduction(state);
        obe::collision::Bindings::LoadClassCollisionData(state);
        obe::collision::Bindings::LoadClassPolygonalCollider(state);
        obe::collision::Bindings::LoadClassTrajectory(state);
        obe::collision::Bindings::LoadClassTrajectoryNode(state);
        obe::collision::Bindings::LoadEnumColliderTagType(state);
        obe::collision::Exceptions::Bindings::LoadClassInvalidTagFormat(state);
        obe::Component::Bindings::LoadClassComponentBase(state);
        obe::Component::Exceptions::Bindings::LoadClassComponentIdAlreadyTaken(state);
        obe::Component::Exceptions::Bindings::LoadClassUnknownComponentType(state);
        obe::config::Bindings::LoadClassConfigurationManager(state);
        obe::config::Bindings::LoadClassVersion(state);
        obe::config::Exceptions::Bindings::LoadClassConfigError(state);
        obe::config::Exceptions::Bindings::LoadClassInvalidVersionFormat(state);
        obe::engine::Bindings::LoadClassEngine(state);
        obe::engine::Bindings::LoadClassResourceManagedObject(state);
        obe::engine::Bindings::LoadClassResourceManager(state);
        obe::engine::exceptions::Bindings::LoadClassBootScriptExecutionError(state);
        obe::engine::exceptions::Bindings::LoadClassBootScriptLoadingError(state);
        obe::engine::exceptions::Bindings::LoadClassBootScriptMissing(state);
        obe::engine::exceptions::Bindings::LoadClassFontNotFound(state);
        obe::engine::exceptions::Bindings::LoadClassTextureNotFound(state);
        obe::engine::exceptions::Bindings::LoadClassUnitializedEngine(state);
        obe::event::Bindings::LoadClassCallbackProfiler(state);
        obe::event::Bindings::LoadClassCallbackScheduler(state);
        obe::event::Bindings::LoadClassEventBase(state);
        obe::event::Bindings::LoadClassEventGroup(state);
        obe::event::Bindings::LoadClassEventGroupView(state);
        obe::event::Bindings::LoadClassEventManager(state);
        obe::event::Bindings::LoadClassEventNamespace(state);
        obe::event::Bindings::LoadClassEventNamespaceView(state);
        obe::event::Bindings::LoadClassLuaEventListener(state);
        obe::event::Bindings::LoadClassScopeProfiler(state);
        obe::event::Bindings::LoadEnumCallbackSchedulerState(state);
        obe::event::Bindings::LoadEnumListenerChangeState(state);
        obe::event::Exceptions::Bindings::LoadClassCallbackCreationError(state);
        obe::event::Exceptions::Bindings::LoadClassEventAlreadyExists(state);
        obe::event::Exceptions::Bindings::LoadClassEventExecutionError(state);
        obe::event::Exceptions::Bindings::LoadClassEventGroupAlreadyExists(state);
        obe::event::Exceptions::Bindings::LoadClassEventGroupNotJoinable(state);
        obe::event::Exceptions::Bindings::LoadClassEventNamespaceAlreadyExists(state);
        obe::event::Exceptions::Bindings::LoadClassEventNamespaceNotJoinable(state);
        obe::event::Exceptions::Bindings::LoadClassUnknownEvent(state);
        obe::event::Exceptions::Bindings::LoadClassUnknownEventGroup(state);
        obe::event::Exceptions::Bindings::LoadClassUnknownEventNamespace(state);
        obe::graphics::canvas::Bindings::LoadClassBezier(state);
        obe::graphics::canvas::Bindings::LoadClassCanvas(state);
        obe::graphics::canvas::Bindings::LoadClassCanvasElement(state);
        obe::graphics::canvas::Bindings::LoadClassCanvasPositionable(state);
        obe::graphics::canvas::Bindings::LoadClassCircle(state);
        obe::graphics::canvas::Bindings::LoadClassLine(state);
        obe::graphics::canvas::Bindings::LoadClassPolygon(state);
        obe::graphics::canvas::Bindings::LoadClassRectangle(state);
        obe::graphics::canvas::Bindings::LoadClassText(state);
        obe::graphics::canvas::Bindings::LoadEnumCanvasElementType(state);
        obe::graphics::canvas::Bindings::LoadEnumTextHorizontalAlign(state);
        obe::graphics::canvas::Bindings::LoadEnumTextVerticalAlign(state);
        obe::graphics::Bindings::LoadClassColor(state);
        obe::graphics::Bindings::LoadClassFont(state);
        obe::graphics::Bindings::LoadClassPositionTransformer(state);
        obe::graphics::Bindings::LoadClassRenderTarget(state);
        obe::graphics::Bindings::LoadClassRenderable(state);
        obe::graphics::Bindings::LoadClassRichText(state);
        obe::graphics::Bindings::LoadClassShader(state);
        obe::graphics::Bindings::LoadClassSprite(state);
        obe::graphics::Bindings::LoadClassSpriteHandlePoint(state);
        obe::graphics::Bindings::LoadClassSvgTexture(state);
        obe::graphics::Bindings::LoadClassText(state);
        obe::graphics::Bindings::LoadClassTexture(state);
        obe::graphics::Bindings::LoadClassHsv(state);
        obe::graphics::Bindings::LoadEnumColorType(state);
        obe::graphics::Bindings::LoadEnumSpriteHandlePointType(state);
        obe::graphics::Bindings::LoadFunctionInitPositionTransformer(state);
        obe::graphics::Bindings::LoadFunctionMakeNullTexture(state);
        obe::graphics::Bindings::LoadGlobalTransformers(state);
        obe::graphics::Bindings::LoadGlobalParallax(state);
        obe::graphics::Bindings::LoadGlobalCamera(state);
        obe::graphics::Bindings::LoadGlobalPosition(state);
        obe::graphics::exceptions::Bindings::LoadClassCanvasElementAlreadyExists(state);
        obe::graphics::exceptions::Bindings::LoadClassImageFileNotFound(state);
        obe::graphics::exceptions::Bindings::LoadClassInvalidColorName(state);
        obe::graphics::exceptions::Bindings::LoadClassInvalidHexFormat(state);
        obe::graphics::exceptions::Bindings::LoadClassInvalidHsvFormat(state);
        obe::graphics::exceptions::Bindings::LoadClassInvalidRgbFormat(state);
        obe::graphics::exceptions::Bindings::LoadClassInvalidSpriteColorType(state);
        obe::graphics::exceptions::Bindings::LoadClassReadOnlyTexture(state);
        obe::graphics::shapes::Bindings::LoadClassCircle(state);
        obe::graphics::shapes::Bindings::LoadClassPolygon(state);
        obe::graphics::shapes::Bindings::LoadClassRectangle(state);
        obe::graphics::shapes::Bindings::LoadClassText(state);
        obe::Input::Exceptions::Bindings::LoadClassInputButtonAlreadyInCombination(state);
        obe::Input::Exceptions::Bindings::LoadClassInputButtonInvalidOperation(state);
        obe::Input::Exceptions::Bindings::LoadClassInvalidGamepadButton(state);
        obe::Input::Exceptions::Bindings::LoadClassInvalidInputButtonState(state);
        obe::Input::Exceptions::Bindings::LoadClassInvalidInputCombinationCode(state);
        obe::Input::Exceptions::Bindings::LoadClassInvalidInputTypeEnumValue(state);
        obe::Input::Exceptions::Bindings::LoadClassUnknownInputAction(state);
        obe::Input::Exceptions::Bindings::LoadClassUnknownInputButton(state);
        obe::Input::Bindings::LoadClassInputAction(state);
        obe::Input::Bindings::LoadClassInputButton(state);
        obe::Input::Bindings::LoadClassInputButtonMonitor(state);
        obe::Input::Bindings::LoadClassInputCondition(state);
        obe::Input::Bindings::LoadClassInputManager(state);
        obe::Input::Bindings::LoadEnumMouseWheelScrollDirection(state);
        obe::Input::Bindings::LoadEnumAxisThresholdDirection(state);
        obe::Input::Bindings::LoadEnumInputButtonState(state);
        obe::Input::Bindings::LoadEnumInputType(state);
        obe::Input::Bindings::LoadFunctionInputTypeToString(state);
        obe::Network::Bindings::LoadClassLuaPacket(state);
        obe::Network::Bindings::LoadClassNetworkHandler(state);
        obe::Network::Bindings::LoadClassTcpServer(state);
        obe::Network::Bindings::LoadClassTcpSocket(state);
        obe::Scene::Bindings::LoadClassCamera(state);
        obe::Scene::Bindings::LoadClassScene(state);
        obe::Scene::Bindings::LoadClassSceneNode(state);
        obe::Scene::Bindings::LoadClassSceneRenderOptions(state);
        obe::Scene::Exceptions::Bindings::LoadClassChildNotInSceneNode(state);
        obe::Scene::Exceptions::Bindings::LoadClassGameObjectAlreadyExists(state);
        obe::Scene::Exceptions::Bindings::LoadClassInvalidSceneFile(state);
        obe::Scene::Exceptions::Bindings::LoadClassMissingSceneFileBlock(state);
        obe::Scene::Exceptions::Bindings::LoadClassSceneOnLoadCallbackError(state);
        obe::Scene::Exceptions::Bindings::LoadClassSceneScriptLoadingError(state);
        obe::Scene::Exceptions::Bindings::LoadClassUnknownCollider(state);
        obe::Scene::Exceptions::Bindings::LoadClassUnknownGameObject(state);
        obe::Scene::Exceptions::Bindings::LoadClassUnknownSprite(state);
        obe::Script::Exceptions::Bindings::LoadClassGameObjectScriptError(state);
        obe::Script::Exceptions::Bindings::LoadClassInvalidScript(state);
        obe::Script::Exceptions::Bindings::LoadClassLuaExecutionError(state);
        obe::Script::Exceptions::Bindings::LoadClassLuaNestedExceptionError(state);
        obe::Script::Exceptions::Bindings::LoadClassNoSuchComponent(state);
        obe::Script::Exceptions::Bindings::LoadClassObjectDefinitionNotFound(state);
        obe::Script::Exceptions::Bindings::LoadClassScriptFileNotFound(state);
        obe::Script::Exceptions::Bindings::LoadClassWrongSourceAttributeType(state);
        obe::Script::Bindings::LoadClassGameObject(state);
        obe::Script::Bindings::LoadClassGameObjectDatabase(state);
        obe::Script::Bindings::LoadClassLuaState(state);
        obe::Script::Bindings::LoadFunctionSafeLuaCall(state);
        obe::System::Bindings::LoadClassContextualPathFactory(state);
        obe::System::Bindings::LoadClassCursor(state);
        obe::System::Bindings::LoadClassCursorModel(state);
        obe::System::Bindings::LoadClassPlugin(state);
        obe::System::Bindings::LoadClassWindow(state);
        obe::System::Bindings::LoadEnumCursorType(state);
        obe::System::Bindings::LoadEnumMountablePathType(state);
        obe::System::Bindings::LoadEnumSamePrefixPolicy(state);
        obe::System::Bindings::LoadEnumPathType(state);
        obe::System::Bindings::LoadEnumWindowContext(state);
        obe::System::Bindings::LoadEnumStretchMode(state);
        obe::System::Bindings::LoadFunctionSplitPathAndPrefix(state);
        obe::System::Bindings::LoadFunctionPathTypeToString(state);
        obe::System::Exceptions::Bindings::LoadClassInvalidDeferredMountablePath(state);
        obe::System::Exceptions::Bindings::LoadClassInvalidMountFile(state);
        obe::System::Exceptions::Bindings::LoadClassInvalidMouseButtonEnumValue(state);
        obe::System::Exceptions::Bindings::LoadClassInvalidProjectFile(state);
        obe::System::Exceptions::Bindings::LoadClassMissingDefaultMountPoint(state);
        obe::System::Exceptions::Bindings::LoadClassMountFileMissing(state);
        obe::System::Exceptions::Bindings::LoadClassMountablePathIndexOverflow(state);
        obe::System::Exceptions::Bindings::LoadClassPackageAlreadyInstalled(state);
        obe::System::Exceptions::Bindings::LoadClassPackageFileNotFound(state);
        obe::System::Exceptions::Bindings::LoadClassPathError(state);
        obe::System::Exceptions::Bindings::LoadClassResourceNotFound(state);
        obe::System::Exceptions::Bindings::LoadClassUnknownPackage(state);
        obe::System::Exceptions::Bindings::LoadClassUnknownPathPrefix(state);
        obe::System::Exceptions::Bindings::LoadClassUnknownProject(state);
        obe::System::Exceptions::Bindings::LoadClassUnknownStretchMode(state);
        obe::System::Project::Bindings::LoadClassProject(state);
        obe::System::Project::Bindings::LoadClassProjectURLs(state);
        obe::System::Project::Bindings::LoadFunctionGetProjectLocation(state);
        obe::System::Project::Bindings::LoadFunctionProjectExists(state);
        obe::System::Project::Bindings::LoadFunctionLoad(state);
        obe::System::Project::Bindings::LoadFunctionListProjects(state);
        obe::Tiles::Bindings::LoadClassAnimatedTile(state);
        obe::Tiles::Bindings::LoadClassTileLayer(state);
        obe::Tiles::Bindings::LoadClassTileScene(state);
        obe::Tiles::Bindings::LoadClassTileset(state);
        obe::Tiles::Bindings::LoadClassTilesetCollection(state);
        obe::Tiles::Bindings::LoadClassTextureQuadsIndex(state);
        obe::Tiles::Bindings::LoadClassTileInfo(state);
        obe::Tiles::Bindings::LoadFunctionGetTileInfo(state);
        obe::Tiles::Bindings::LoadFunctionStripTileFlags(state);
        obe::Tiles::Bindings::LoadFunctionApplyTextureQuadsTransforms(state);
        obe::Tiles::Exceptions::Bindings::LoadClassTilePositionOutsideLayer(state);
        obe::Tiles::Exceptions::Bindings::LoadClassUnknownTileId(state);
        obe::Tiles::Exceptions::Bindings::LoadClassUnknownTileLayer(state);
        obe::Tiles::Exceptions::Bindings::LoadClassUnknownTileset(state);
        obe::Time::Bindings::LoadClassChronometer(state);
        obe::Time::Bindings::LoadClassFramerateCounter(state);
        obe::Time::Bindings::LoadClassFramerateManager(state);
        obe::Time::Bindings::LoadFunctionEpoch(state);
        obe::Time::Bindings::LoadGlobalSeconds(state);
        obe::Time::Bindings::LoadGlobalMilliseconds(state);
        obe::Time::Bindings::LoadGlobalMicroseconds(state);
        obe::Time::Bindings::LoadGlobalMinutes(state);
        obe::Time::Bindings::LoadGlobalHours(state);
        obe::Time::Bindings::LoadGlobalDays(state);
        obe::Time::Bindings::LoadGlobalWeeks(state);
        obe::Transform::Exceptions::Bindings::LoadClassInvalidUnitsEnumValue(state);
        obe::Transform::Exceptions::Bindings::LoadClassPolygonNotEnoughPoints(state);
        obe::Transform::Exceptions::Bindings::LoadClassPolygonPointIndexOverflow(state);
        obe::Transform::Exceptions::Bindings::LoadClassUnknownReferential(state);
        obe::Transform::Exceptions::Bindings::LoadClassUnknownUnit(state);
        obe::Transform::Bindings::LoadClassMatrix2D(state);
        obe::Transform::Bindings::LoadClassMovable(state);
        obe::Transform::Bindings::LoadClassPolygon(state);
        obe::Transform::Bindings::LoadClassPolygonPoint(state);
        obe::Transform::Bindings::LoadClassPolygonSegment(state);
        obe::Transform::Bindings::LoadClassRect(state);
        obe::Transform::Bindings::LoadClassReferential(state);
        obe::Transform::Bindings::LoadClassUnitBasedObject(state);
        obe::Transform::Bindings::LoadClassUnitVector(state);
        obe::Transform::Bindings::LoadClassScreenStruct(state);
        obe::Transform::Bindings::LoadClassViewStruct(state);
        obe::Transform::Bindings::LoadEnumRelativePositionFrom(state);
        obe::Transform::Bindings::LoadEnumReferentialConversionType(state);
        obe::Transform::Bindings::LoadEnumFlipAxis(state);
        obe::Transform::Bindings::LoadEnumUnits(state);
        obe::Types::Bindings::LoadClassIdentifiable(state);
        obe::Types::Bindings::LoadClassProtectedIdentifiable(state);
        obe::Types::Bindings::LoadClassSelectable(state);
        obe::Types::Bindings::LoadClassSerializable(state);
        obe::Types::Bindings::LoadClassTogglable(state);
        obe::Utils::Exec::Bindings::LoadClassRunArgsParser(state);
        vili::Bindings::LoadClassConstNodeIterator(state);
        vili::Bindings::LoadClassNode(state);
        vili::Bindings::LoadClassNodeIterator(state);
        vili::Bindings::LoadEnumNodeType(state);
        vili::Bindings::LoadFunctionFromString(state);
        vili::Bindings::LoadFunctionToString(state);
        vili::Bindings::LoadGlobalPERMISSIVECAST(state);
        vili::Bindings::LoadGlobalVERBOSEEXCEPTIONS(state);
        vili::Bindings::LoadGlobalTrueValue(state);
        vili::Bindings::LoadGlobalFalseValue(state);
        vili::Bindings::LoadGlobalNullTypename(state);
        vili::Bindings::LoadGlobalBooleanTypename(state);
        vili::Bindings::LoadGlobalIntegerTypename(state);
        vili::Bindings::LoadGlobalNumberTypename(state);
        vili::Bindings::LoadGlobalStringTypename(state);
        vili::Bindings::LoadGlobalObjectTypename(state);
        vili::Bindings::LoadGlobalArrayTypename(state);
        vili::Bindings::LoadGlobalUnknownTypename(state);
        vili::Bindings::LoadGlobalContainerTypename(state);
        vili::exceptions::Bindings::LoadClassArrayIndexOverflow(state);
        vili::exceptions::Bindings::LoadClassBaseException(state);
        vili::exceptions::Bindings::LoadClassDebugInfo(state);
        vili::exceptions::Bindings::LoadClassFileNotFound(state);
        vili::exceptions::Bindings::LoadClassInconsistentIndentation(state);
        vili::exceptions::Bindings::LoadClassIntegerDumpError(state);
        vili::exceptions::Bindings::LoadClassInvalidCast(state);
        vili::exceptions::Bindings::LoadClassInvalidDataType(state);
        vili::exceptions::Bindings::LoadClassInvalidMerge(state);
        vili::exceptions::Bindings::LoadClassInvalidNodeType(state);
        vili::exceptions::Bindings::LoadClassNumberDumpError(state);
        vili::exceptions::Bindings::LoadClassParsingError(state);
        vili::exceptions::Bindings::LoadClassTooMuchIndentation(state);
        vili::exceptions::Bindings::LoadClassUnknownChildNode(state);
        vili::parser::Bindings::LoadClassNodeInStack(state);
        vili::parser::Bindings::LoadClassState(state);
        vili::parser::Bindings::LoadClassError(state);
        vili::parser::Bindings::LoadFunctionFromString(state);
        vili::parser::Bindings::LoadFunctionFromFile(state);
        obe::events::Actions::Bindings::LoadClassAction(state);
        obe::events::Cursor::Bindings::LoadClassHold(state);
        obe::events::Cursor::Bindings::LoadClassMove(state);
        obe::events::Cursor::Bindings::LoadClassPress(state);
        obe::events::Cursor::Bindings::LoadClassRelease(state);
        obe::events::game::Bindings::LoadClassEnd(state);
        obe::events::game::Bindings::LoadClassRender(state);
        obe::events::game::Bindings::LoadClassStart(state);
        obe::events::game::Bindings::LoadClassUpdate(state);
        obe::events::Keys::Bindings::LoadClassStateChanged(state);
        obe::events::Network::Bindings::LoadClassConnected(state);
        obe::events::Network::Bindings::LoadClassDataReceived(state);
        obe::events::Network::Bindings::LoadClassDisconnected(state);
        obe::events::Scene::Bindings::LoadClassLoaded(state);
        obe::graphics::utils::Bindings::LoadClassDrawPolygonOptions(state);
        obe::graphics::utils::Bindings::LoadFunctionDrawPoint(state);
        obe::graphics::utils::Bindings::LoadFunctionDrawLine(state);
        obe::graphics::utils::Bindings::LoadFunctionDrawPolygon(state);
        vili::parser::rules::Bindings::LoadClassAffectation(state);
        vili::parser::rules::Bindings::LoadClassAffectationSeparator(state);
        vili::parser::rules::Bindings::LoadClassArray(state);
        vili::parser::rules::Bindings::LoadClassArrayElements(state);
        vili::parser::rules::Bindings::LoadClassArraySeparator(state);
        vili::parser::rules::Bindings::LoadClassBlock(state);
        vili::parser::rules::Bindings::LoadClassBoolean(state);
        vili::parser::rules::Bindings::LoadClassBraceBasedObject(state);
        vili::parser::rules::Bindings::LoadClassChar_(state);
        vili::parser::rules::Bindings::LoadClassCloseArray(state);
        vili::parser::rules::Bindings::LoadClassCloseObject(state);
        vili::parser::rules::Bindings::LoadClassComment(state);
        vili::parser::rules::Bindings::LoadClassData(state);
        vili::parser::rules::Bindings::LoadClassDigits(state);
        vili::parser::rules::Bindings::LoadClassElement(state);
        vili::parser::rules::Bindings::LoadClassEmptyLine(state);
        vili::parser::rules::Bindings::LoadClassEndline(state);
        vili::parser::rules::Bindings::LoadClassEscaped(state);
        vili::parser::rules::Bindings::LoadClassEscapedChar(state);
        vili::parser::rules::Bindings::LoadClassFalse_(state);
        vili::parser::rules::Bindings::LoadClassFloatingPoint(state);
        vili::parser::rules::Bindings::LoadClassFullNode(state);
        vili::parser::rules::Bindings::LoadClassGrammar(state);
        vili::parser::rules::Bindings::LoadClassIdentifier(state);
        vili::parser::rules::Bindings::LoadClassIndent(state);
        vili::parser::rules::Bindings::LoadClassIndentBasedObject(state);
        vili::parser::rules::Bindings::LoadClassInlineComment(state);
        vili::parser::rules::Bindings::LoadClassInlineElement(state);
        vili::parser::rules::Bindings::LoadClassInlineNode(state);
        vili::parser::rules::Bindings::LoadClassInteger(state);
        vili::parser::rules::Bindings::LoadClassMultilineComment(state);
        vili::parser::rules::Bindings::LoadClassMultilineCommentBlock(state);
        vili::parser::rules::Bindings::LoadClassNode(state);
        vili::parser::rules::Bindings::LoadClassNumber(state);
        vili::parser::rules::Bindings::LoadClassObject(state);
        vili::parser::rules::Bindings::LoadClassObjectElements(state);
        vili::parser::rules::Bindings::LoadClassObjectSeparator(state);
        vili::parser::rules::Bindings::LoadClassOpenArray(state);
        vili::parser::rules::Bindings::LoadClassOpenObject(state);
        vili::parser::rules::Bindings::LoadClassSign(state);
        vili::parser::rules::Bindings::LoadClassSpaceOrComment(state);
        vili::parser::rules::Bindings::LoadClassString(state);
        vili::parser::rules::Bindings::LoadClassStringContent(state);
        vili::parser::rules::Bindings::LoadClassStringDelimiter(state);
        vili::parser::rules::Bindings::LoadClassTrue_(state);
        vili::parser::rules::Bindings::LoadClassUnescaped(state);
        vili::parser::rules::Bindings::LoadClassUnicode(state);
        vili::parser::rules::Bindings::LoadClassViliGrammar(state);
        vili::parser::rules::Bindings::LoadClassXdigit(state);
        vili::writer::Bindings::LoadClassDumpOptions(state);
        vili::writer::Bindings::LoadClass_array(state);
        vili::writer::Bindings::LoadClass_object(state);
        vili::writer::Bindings::LoadEnumDelimiterNewlinePolicy(state);
        vili::writer::Bindings::LoadEnumCommaSpacingPolicy(state);
        vili::writer::Bindings::LoadEnumObjectStyle(state);
        vili::writer::Bindings::LoadFunctionDumpInteger(state);
        vili::writer::Bindings::LoadFunctionDumpNumber(state);
        vili::writer::Bindings::LoadFunctionDumpBoolean(state);
        vili::writer::Bindings::LoadFunctionDumpString(state);
        vili::writer::Bindings::LoadFunctionDumpArray(state);
        vili::writer::Bindings::LoadFunctionDumpObject(state);
        vili::writer::Bindings::LoadFunctionDump(state);
        obe::animation::easing::Bindings::LoadEnumEasingType(state);
        obe::animation::easing::Bindings::LoadFunctionLinear(state);
        obe::animation::easing::Bindings::LoadFunctionInSine(state);
        obe::animation::easing::Bindings::LoadFunctionOutSine(state);
        obe::animation::easing::Bindings::LoadFunctionInOutSine(state);
        obe::animation::easing::Bindings::LoadFunctionInQuad(state);
        obe::animation::easing::Bindings::LoadFunctionOutQuad(state);
        obe::animation::easing::Bindings::LoadFunctionInOutQuad(state);
        obe::animation::easing::Bindings::LoadFunctionInCubic(state);
        obe::animation::easing::Bindings::LoadFunctionOutCubic(state);
        obe::animation::easing::Bindings::LoadFunctionInOutCubic(state);
        obe::animation::easing::Bindings::LoadFunctionInQuart(state);
        obe::animation::easing::Bindings::LoadFunctionOutQuart(state);
        obe::animation::easing::Bindings::LoadFunctionInOutQuart(state);
        obe::animation::easing::Bindings::LoadFunctionInQuint(state);
        obe::animation::easing::Bindings::LoadFunctionOutQuint(state);
        obe::animation::easing::Bindings::LoadFunctionInOutQuint(state);
        obe::animation::easing::Bindings::LoadFunctionInExpo(state);
        obe::animation::easing::Bindings::LoadFunctionOutExpo(state);
        obe::animation::easing::Bindings::LoadFunctionInOutExpo(state);
        obe::animation::easing::Bindings::LoadFunctionInCirc(state);
        obe::animation::easing::Bindings::LoadFunctionOutCirc(state);
        obe::animation::easing::Bindings::LoadFunctionInOutCirc(state);
        obe::animation::easing::Bindings::LoadFunctionInBack(state);
        obe::animation::easing::Bindings::LoadFunctionOutBack(state);
        obe::animation::easing::Bindings::LoadFunctionInOutBack(state);
        obe::animation::easing::Bindings::LoadFunctionInElastic(state);
        obe::animation::easing::Bindings::LoadFunctionOutElastic(state);
        obe::animation::easing::Bindings::LoadFunctionInOutElastic(state);
        obe::animation::easing::Bindings::LoadFunctionInBounce(state);
        obe::animation::easing::Bindings::LoadFunctionOutBounce(state);
        obe::animation::easing::Bindings::LoadFunctionInOutBounce(state);
        obe::animation::easing::Bindings::LoadFunctionGet(state);
        obe::Bindings::Bindings::LoadFunctionIndexCoreBindings(state);
        obe::config::validators::Bindings::LoadFunctionAnimationValidator(state);
        obe::config::validators::Bindings::LoadFunctionConfigValidator(state);
        obe::config::validators::Bindings::LoadFunctionMountValidator(state);
        obe::config::validators::Bindings::LoadFunctionProjectValidator(state);
        obe::debug::Bindings::LoadFunctionInitLogger(state);
        obe::debug::Bindings::LoadFunctionTrace(state);
        obe::debug::Bindings::LoadFunctionDebug(state);
        obe::debug::Bindings::LoadFunctionInfo(state);
        obe::debug::Bindings::LoadFunctionWarn(state);
        obe::debug::Bindings::LoadFunctionError(state);
        obe::debug::Bindings::LoadFunctionCritical(state);
        obe::debug::Bindings::LoadGlobalLog(state);
        obe::debug::render::Bindings::LoadFunctionDrawPolygon(state);
        obe::Script::ViliLuaBridge::Bindings::LoadFunctionViliToLua(state);
        obe::Script::ViliLuaBridge::Bindings::LoadFunctionLuaToVili(state);
        obe::Script::ViliLuaBridge::Bindings::LoadFunctionViliObjectToLuaTable(state);
        obe::Script::ViliLuaBridge::Bindings::LoadFunctionViliPrimitiveToLuaValue(state);
        obe::Script::ViliLuaBridge::Bindings::LoadFunctionViliArrayToLuaTable(state);
        obe::Script::ViliLuaBridge::Bindings::LoadFunctionLuaTableToViliObject(state);
        obe::Script::ViliLuaBridge::Bindings::LoadFunctionLuaValueToViliPrimitive(state);
        obe::Script::ViliLuaBridge::Bindings::LoadFunctionLuaTableToViliArray(state);
        obe::System::Package::Bindings::LoadFunctionGetPackageLocation(state);
        obe::System::Package::Bindings::LoadFunctionPackageExists(state);
        obe::System::Package::Bindings::LoadFunctionListPackages(state);
        obe::System::Package::Bindings::LoadFunctionInstall(state);
        obe::System::Package::Bindings::LoadFunctionLoad(state);
        obe::Utils::File::Bindings::LoadFunctionGetDirectoryList(state);
        obe::Utils::File::Bindings::LoadFunctionGetFileList(state);
        obe::Utils::File::Bindings::LoadFunctionFileExists(state);
        obe::Utils::File::Bindings::LoadFunctionDirectoryExists(state);
        obe::Utils::File::Bindings::LoadFunctionCreateDirectory(state);
        obe::Utils::File::Bindings::LoadFunctionCreateFile(state);
        obe::Utils::File::Bindings::LoadFunctionCopy(state);
        obe::Utils::File::Bindings::LoadFunctionDeleteFile(state);
        obe::Utils::File::Bindings::LoadFunctionDeleteDirectory(state);
        obe::Utils::File::Bindings::LoadFunctionGetCurrentDirectory(state);
        obe::Utils::File::Bindings::LoadFunctionSeparator(state);
        obe::Utils::File::Bindings::LoadFunctionGetExecutableDirectory(state);
        obe::Utils::File::Bindings::LoadFunctionGetExecutablePath(state);
        obe::Utils::File::Bindings::LoadFunctionNormalizePath(state);
        obe::Utils::File::Bindings::LoadFunctionCanonicalPath(state);
        obe::Utils::File::Bindings::LoadFunctionJoin(state);
        obe::Utils::Math::Bindings::LoadFunctionRandint(state);
        obe::Utils::Math::Bindings::LoadFunctionRandfloat(state);
        obe::Utils::Math::Bindings::LoadFunctionGetMin(state);
        obe::Utils::Math::Bindings::LoadFunctionGetMax(state);
        obe::Utils::Math::Bindings::LoadFunctionIsBetween(state);
        obe::Utils::Math::Bindings::LoadFunctionIsDoubleInt(state);
        obe::Utils::Math::Bindings::LoadFunctionSign(state);
        obe::Utils::Math::Bindings::LoadFunctionConvertToRadian(state);
        obe::Utils::Math::Bindings::LoadFunctionConvertToDegree(state);
        obe::Utils::Math::Bindings::LoadFunctionNormalize(state);
        obe::Utils::Math::Bindings::LoadGlobalPi(state);
        obe::Utils::String::Bindings::LoadFunctionSplit(state);
        obe::Utils::String::Bindings::LoadFunctionOccurencesInString(state);
        obe::Utils::String::Bindings::LoadFunctionIsStringAlpha(state);
        obe::Utils::String::Bindings::LoadFunctionIsStringAlphaNumeric(state);
        obe::Utils::String::Bindings::LoadFunctionIsStringNumeric(state);
        obe::Utils::String::Bindings::LoadFunctionIsStringInt(state);
        obe::Utils::String::Bindings::LoadFunctionIsStringFloat(state);
        obe::Utils::String::Bindings::LoadFunctionReplace(state);
        obe::Utils::String::Bindings::LoadFunctionIsSurroundedBy(state);
        obe::Utils::String::Bindings::LoadFunctionGetRandomKey(state);
        obe::Utils::String::Bindings::LoadFunctionContains(state);
        obe::Utils::String::Bindings::LoadFunctionStartsWith(state);
        obe::Utils::String::Bindings::LoadFunctionEndsWith(state);
        obe::Utils::String::Bindings::LoadFunctionDistance(state);
        obe::Utils::String::Bindings::LoadFunctionSortByDistance(state);
        obe::Utils::String::Bindings::LoadFunctionQuote(state);
        obe::Utils::String::Bindings::LoadGlobalAlphabet(state);
        obe::Utils::String::Bindings::LoadGlobalNumbers(state);
        obe::Utils::Vector::Bindings::LoadFunctionContains(state);
        obe::Utils::Vector::Bindings::LoadFunctionJoin(state);
        vili::utils::string::Bindings::LoadFunctionReplace(state);
        vili::utils::string::Bindings::LoadFunctionIsInt(state);
        vili::utils::string::Bindings::LoadFunctionIsFloat(state);
        vili::utils::string::Bindings::LoadFunctionTruncateFloat(state);
        vili::utils::string::Bindings::LoadFunctionQuote(state);
        vili::utils::string::Bindings::LoadFunctionToDouble(state);
        vili::utils::string::Bindings::LoadFunctionToLong(state);
        vili::utils::string::Bindings::LoadFunctionIndent(state);
        vili::utils::string::Bindings::LoadFunctionDistance(state);
        vili::utils::string::Bindings::LoadFunctionSortByDistance(state);
        obe::System::Constraints::Bindings::LoadGlobalDefault(state);
        obe::System::Prefixes::Bindings::LoadGlobalObe(state);
        obe::System::Prefixes::Bindings::LoadGlobalCwd(state);
        obe::System::Prefixes::Bindings::LoadGlobalExe(state);
        obe::System::Prefixes::Bindings::LoadGlobalCfg(state);
        obe::System::Prefixes::Bindings::LoadGlobalMount(state);
        obe::System::Prefixes::Bindings::LoadGlobalExtlibs(state);
        obe::System::Prefixes::Bindings::LoadGlobalRoot(state);
        obe::System::Prefixes::Bindings::LoadGlobalGame(state);
        obe::System::Priorities::Bindings::LoadGlobalHigh(state);
        obe::System::Priorities::Bindings::LoadGlobalProjectmount(state);
        obe::System::Priorities::Bindings::LoadGlobalProject(state);
        obe::System::Priorities::Bindings::LoadGlobalMount(state);
        obe::System::Priorities::Bindings::LoadGlobalDefaults(state);
        obe::System::Priorities::Bindings::LoadGlobalLow(state);
        obe::System::Project::Prefixes::Bindings::LoadGlobalObjects(state);
        obe::System::Project::Prefixes::Bindings::LoadGlobalScenes(state);
    }
}