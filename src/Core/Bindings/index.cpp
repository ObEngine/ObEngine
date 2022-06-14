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
    void index_core_bindings(sol::state_view state)
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
        state["obe"]["input"].get_or_create<sol::table>();
        state["obe"]["network"].get_or_create<sol::table>();
        state["obe"]["scene"].get_or_create<sol::table>();
        state["obe"]["script"].get_or_create<sol::table>();
        state["obe"]["system"].get_or_create<sol::table>();
        state["obe"]["tiles"].get_or_create<sol::table>();
        state["obe"]["time"].get_or_create<sol::table>();
        state["obe"]["transform"].get_or_create<sol::table>();
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
        state["obe"]["input"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["scene"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["script"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["system"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["system"]["project"].get_or_create<sol::table>();
        state["obe"]["tiles"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["transform"]["exceptions"].get_or_create<sol::table>();
        state["obe"]["Utils"]["Exec"].get_or_create<sol::table>();
        state["obe"]["events"]["actions"].get_or_create<sol::table>();
        state["obe"]["events"]["cursor"].get_or_create<sol::table>();
        state["obe"]["events"]["game"].get_or_create<sol::table>();
        state["obe"]["events"]["keys"].get_or_create<sol::table>();
        state["obe"]["events"]["network"].get_or_create<sol::table>();
        state["obe"]["events"]["scene"].get_or_create<sol::table>();
        state["obe"]["graphics"]["utils"].get_or_create<sol::table>();
        state["vili"]["parser"]["rules"].get_or_create<sol::table>();
        state["obe"]["animation"]["easing"].get_or_create<sol::table>();
        state["obe"]["config"]["Templates"].get_or_create<sol::table>();
        state["obe"]["config"]["validators"].get_or_create<sol::table>();
        state["obe"]["debug"]["render"].get_or_create<sol::table>();
        state["obe"]["script"]["vili_lua_bridge"].get_or_create<sol::table>();
        state["obe"]["system"]["package"].get_or_create<sol::table>();
        state["obe"]["Utils"]["File"].get_or_create<sol::table>();
        state["obe"]["Utils"]["Math"].get_or_create<sol::table>();
        state["obe"]["Utils"]["String"].get_or_create<sol::table>();
        state["obe"]["Utils"]["Vector"].get_or_create<sol::table>();
        state["vili"]["utils"]["string"].get_or_create<sol::table>();
        state["obe"]["system"]["constraints"].get_or_create<sol::table>();
        state["obe"]["system"]["prefixes"].get_or_create<sol::table>();
        state["obe"]["system"]["priorities"].get_or_create<sol::table>();
        state["obe"]["system"]["project"]["prefixes"].get_or_create<sol::table>();

        obe::system::Bindings::LoadClassMountablePath(state);
        obe::system::Bindings::LoadClassFindResult(state);
        obe::system::Bindings::LoadClassPath(state);
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
        obe::input::Exceptions::Bindings::LoadClassInputButtonAlreadyInCombination(state);
        obe::input::Exceptions::Bindings::LoadClassInputButtonInvalidOperation(state);
        obe::input::Exceptions::Bindings::LoadClassInvalidGamepadButton(state);
        obe::input::Exceptions::Bindings::LoadClassInvalidInputButtonState(state);
        obe::input::Exceptions::Bindings::LoadClassInvalidInputCombinationCode(state);
        obe::input::Exceptions::Bindings::LoadClassInvalidInputTypeEnumValue(state);
        obe::input::Exceptions::Bindings::LoadClassUnknownInputAction(state);
        obe::input::Exceptions::Bindings::LoadClassUnknownInputButton(state);
        obe::input::Bindings::LoadClassInputAction(state);
        obe::input::Bindings::LoadClassInputButton(state);
        obe::input::Bindings::LoadClassInputButtonMonitor(state);
        obe::input::Bindings::LoadClassInputCondition(state);
        obe::input::Bindings::LoadClassInputManager(state);
        obe::input::Bindings::LoadEnumMouseWheelScrollDirection(state);
        obe::input::Bindings::LoadEnumAxisThresholdDirection(state);
        obe::input::Bindings::LoadEnumInputButtonState(state);
        obe::input::Bindings::LoadEnumInputType(state);
        obe::network::Bindings::LoadClassLuaPacket(state);
        obe::network::Bindings::LoadClassNetworkHandler(state);
        obe::network::Bindings::LoadClassTcpServer(state);
        obe::network::Bindings::LoadClassTcpSocket(state);
        obe::scene::Bindings::LoadClassCamera(state);
        obe::scene::Bindings::LoadClassScene(state);
        obe::scene::Bindings::LoadClassSceneNode(state);
        obe::scene::Bindings::LoadClassSceneRenderOptions(state);
        obe::scene::Exceptions::Bindings::LoadClassChildNotInSceneNode(state);
        obe::scene::Exceptions::Bindings::LoadClassGameObjectAlreadyExists(state);
        obe::scene::Exceptions::Bindings::LoadClassInvalidSceneFile(state);
        obe::scene::Exceptions::Bindings::LoadClassMissingSceneFileBlock(state);
        obe::scene::Exceptions::Bindings::LoadClassSceneOnLoadCallbackError(state);
        obe::scene::Exceptions::Bindings::LoadClassSceneScriptLoadingError(state);
        obe::scene::Exceptions::Bindings::LoadClassUnknownCollider(state);
        obe::scene::Exceptions::Bindings::LoadClassUnknownGameObject(state);
        obe::scene::Exceptions::Bindings::LoadClassUnknownSprite(state);
        obe::script::exceptions::Bindings::LoadClassGameObjectScriptError(state);
        obe::script::exceptions::Bindings::LoadClassInvalidScript(state);
        obe::script::exceptions::Bindings::LoadClassLuaExecutionError(state);
        obe::script::exceptions::Bindings::LoadClassLuaNestedExceptionError(state);
        obe::script::exceptions::Bindings::LoadClassNoSuchComponent(state);
        obe::script::exceptions::Bindings::LoadClassObjectDefinitionNotFound(state);
        obe::script::exceptions::Bindings::LoadClassScriptFileNotFound(state);
        obe::script::exceptions::Bindings::LoadClassWrongSourceAttributeType(state);
        obe::script::Bindings::LoadClassGameObject(state);
        obe::script::Bindings::LoadClassGameObjectDatabase(state);
        obe::script::Bindings::LoadClassLuaState(state);
        obe::script::Bindings::LoadFunctionSafeLuaCall(state);
        obe::system::Bindings::LoadClassContextualPathFactory(state);
        obe::system::Bindings::LoadClassCursor(state);
        obe::system::Bindings::LoadClassCursorModel(state);
        obe::system::Bindings::LoadClassPlugin(state);
        obe::system::Bindings::LoadClassWindow(state);
        obe::system::Bindings::LoadEnumCursorType(state);
        obe::system::Bindings::LoadEnumMountablePathType(state);
        obe::system::Bindings::LoadEnumSamePrefixPolicy(state);
        obe::system::Bindings::LoadEnumPathType(state);
        obe::system::Bindings::LoadEnumWindowContext(state);
        obe::system::Bindings::LoadEnumStretchMode(state);
        obe::system::Bindings::LoadFunctionSplitPathAndPrefix(state);
        obe::system::Exceptions::Bindings::LoadClassInvalidDeferredMountablePath(state);
        obe::system::Exceptions::Bindings::LoadClassInvalidMountFile(state);
        obe::system::Exceptions::Bindings::LoadClassInvalidMouseButtonEnumValue(state);
        obe::system::Exceptions::Bindings::LoadClassInvalidProjectFile(state);
        obe::system::Exceptions::Bindings::LoadClassMissingDefaultMountPoint(state);
        obe::system::Exceptions::Bindings::LoadClassMountFileMissing(state);
        obe::system::Exceptions::Bindings::LoadClassMountablePathIndexOverflow(state);
        obe::system::Exceptions::Bindings::LoadClassPackageAlreadyInstalled(state);
        obe::system::Exceptions::Bindings::LoadClassPackageFileNotFound(state);
        obe::system::Exceptions::Bindings::LoadClassPathError(state);
        obe::system::Exceptions::Bindings::LoadClassResourceNotFound(state);
        obe::system::Exceptions::Bindings::LoadClassUnknownPackage(state);
        obe::system::Exceptions::Bindings::LoadClassUnknownPathPrefix(state);
        obe::system::Exceptions::Bindings::LoadClassUnknownProject(state);
        obe::system::project::Bindings::LoadClassProject(state);
        obe::system::project::Bindings::LoadClassProjectURLs(state);
        obe::system::project::Bindings::LoadFunctionGetProjectLocation(state);
        obe::system::project::Bindings::LoadFunctionProjectExists(state);
        obe::system::project::Bindings::LoadFunctionLoad(state);
        obe::system::project::Bindings::LoadFunctionListProjects(state);
        obe::tiles::Bindings::LoadClassAnimatedTile(state);
        obe::tiles::Bindings::LoadClassTileLayer(state);
        obe::tiles::Bindings::LoadClassTileScene(state);
        obe::tiles::Bindings::LoadClassTileset(state);
        obe::tiles::Bindings::LoadClassTilesetCollection(state);
        obe::tiles::Bindings::LoadClassTextureQuadsIndex(state);
        obe::tiles::Bindings::LoadClassTileInfo(state);
        obe::tiles::Bindings::LoadFunctionGetTileInfo(state);
        obe::tiles::Bindings::LoadFunctionStripTileFlags(state);
        obe::tiles::Bindings::LoadFunctionApplyTextureQuadsTransforms(state);
        obe::tiles::exceptions::Bindings::LoadClassTilePositionOutsideLayer(state);
        obe::tiles::exceptions::Bindings::LoadClassUnknownTileId(state);
        obe::tiles::exceptions::Bindings::LoadClassUnknownTileLayer(state);
        obe::tiles::exceptions::Bindings::LoadClassUnknownTileset(state);
        obe::time::Bindings::LoadClassChronometer(state);
        obe::time::Bindings::LoadClassFramerateCounter(state);
        obe::time::Bindings::LoadClassFramerateManager(state);
        obe::time::Bindings::LoadFunctionEpoch(state);
        obe::time::Bindings::LoadGlobalSeconds(state);
        obe::time::Bindings::LoadGlobalMilliseconds(state);
        obe::time::Bindings::LoadGlobalMicroseconds(state);
        obe::time::Bindings::LoadGlobalMinutes(state);
        obe::time::Bindings::LoadGlobalHours(state);
        obe::time::Bindings::LoadGlobalDays(state);
        obe::time::Bindings::LoadGlobalWeeks(state);
        obe::transform::exceptions::Bindings::LoadClassPolygonNotEnoughPoints(state);
        obe::transform::exceptions::Bindings::LoadClassPolygonPointIndexOverflow(state);
        obe::transform::exceptions::Bindings::LoadClassUnknownReferential(state);
        obe::transform::Bindings::LoadClassMatrix2D(state);
        obe::transform::Bindings::LoadClassMovable(state);
        obe::transform::Bindings::LoadClassPolygon(state);
        obe::transform::Bindings::LoadClassPolygonPoint(state);
        obe::transform::Bindings::LoadClassPolygonSegment(state);
        obe::transform::Bindings::LoadClassRect(state);
        obe::transform::Bindings::LoadClassReferential(state);
        obe::transform::Bindings::LoadClassUnitBasedObject(state);
        obe::transform::Bindings::LoadClassUnitVector(state);
        obe::transform::Bindings::LoadClassScreenStruct(state);
        obe::transform::Bindings::LoadClassViewStruct(state);
        obe::transform::Bindings::LoadEnumRelativePositionFrom(state);
        obe::transform::Bindings::LoadEnumReferentialConversionType(state);
        obe::transform::Bindings::LoadEnumFlipAxis(state);
        obe::transform::Bindings::LoadEnumUnits(state);
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
        obe::events::actions::Bindings::LoadClassAction(state);
        obe::events::cursor::Bindings::LoadClassHold(state);
        obe::events::cursor::Bindings::LoadClassMove(state);
        obe::events::cursor::Bindings::LoadClassPress(state);
        obe::events::cursor::Bindings::LoadClassRelease(state);
        obe::events::game::Bindings::LoadClassEnd(state);
        obe::events::game::Bindings::LoadClassRender(state);
        obe::events::game::Bindings::LoadClassStart(state);
        obe::events::game::Bindings::LoadClassUpdate(state);
        obe::events::keys::Bindings::LoadClassStateChanged(state);
        obe::events::network::Bindings::LoadClassConnected(state);
        obe::events::network::Bindings::LoadClassDataReceived(state);
        obe::events::network::Bindings::LoadClassDisconnected(state);
        obe::events::scene::Bindings::LoadClassLoaded(state);
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
        obe::script::vili_lua_bridge::Bindings::LoadFunctionViliToLua(state);
        obe::script::vili_lua_bridge::Bindings::LoadFunctionLuaToVili(state);
        obe::script::vili_lua_bridge::Bindings::LoadFunctionViliObjectToLuaTable(state);
        obe::script::vili_lua_bridge::Bindings::LoadFunctionViliPrimitiveToLuaValue(state);
        obe::script::vili_lua_bridge::Bindings::LoadFunctionViliArrayToLuaTable(state);
        obe::script::vili_lua_bridge::Bindings::LoadFunctionLuaTableToViliObject(state);
        obe::script::vili_lua_bridge::Bindings::LoadFunctionLuaValueToViliPrimitive(state);
        obe::script::vili_lua_bridge::Bindings::LoadFunctionLuaTableToViliArray(state);
        obe::system::package::Bindings::LoadFunctionGetPackageLocation(state);
        obe::system::package::Bindings::LoadFunctionPackageExists(state);
        obe::system::package::Bindings::LoadFunctionListPackages(state);
        obe::system::package::Bindings::LoadFunctionInstall(state);
        obe::system::package::Bindings::LoadFunctionLoad(state);
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
        obe::system::constraints::Bindings::LoadGlobalDefault(state);
        obe::system::prefixes::Bindings::LoadGlobalObe(state);
        obe::system::prefixes::Bindings::LoadGlobalCwd(state);
        obe::system::prefixes::Bindings::LoadGlobalExe(state);
        obe::system::prefixes::Bindings::LoadGlobalCfg(state);
        obe::system::prefixes::Bindings::LoadGlobalMount(state);
        obe::system::prefixes::Bindings::LoadGlobalExtlibs(state);
        obe::system::prefixes::Bindings::LoadGlobalRoot(state);
        obe::system::prefixes::Bindings::LoadGlobalGame(state);
        obe::system::priorities::Bindings::LoadGlobalHigh(state);
        obe::system::priorities::Bindings::LoadGlobalProjectmount(state);
        obe::system::priorities::Bindings::LoadGlobalProject(state);
        obe::system::priorities::Bindings::LoadGlobalMount(state);
        obe::system::priorities::Bindings::LoadGlobalDefaults(state);
        obe::system::priorities::Bindings::LoadGlobalLow(state);
        obe::system::project::Prefixes::Bindings::LoadGlobalObjects(state);
        obe::system::project::Prefixes::Bindings::LoadGlobalScenes(state);
    }
}