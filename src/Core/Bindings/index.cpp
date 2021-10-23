#include <Bindings/Config.hpp>
#include <Bindings/Exceptions.hpp>
#include <Bindings/Patches.hpp>
#include <Bindings/obe/Animation/Animation.hpp>
#include <Bindings/obe/Animation/Easing/Easing.hpp>
#include <Bindings/obe/Animation/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Audio/Audio.hpp>
#include <Bindings/obe/Audio/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Bindings/Bindings.hpp>
#include <Bindings/obe/Bindings/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Collision/Collision.hpp>
#include <Bindings/obe/Collision/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Component/Component.hpp>
#include <Bindings/obe/Component/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Config/Config.hpp>
#include <Bindings/obe/Config/Templates/Templates.hpp>
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
#include <Bindings/obe/System/System.hpp>
#include <Bindings/obe/System/Workspace/Workspace.hpp>
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
#include <Bindings/obe/Utils/Vector/Vector.hpp>
#include <Bindings/obe/obe.hpp>
#include <Bindings/tgui/bind_functions/bind_functions.hpp>
#include <Bindings/tgui/keyboard/keyboard.hpp>
#include <Bindings/tgui/priv/dev/dev.hpp>
#include <Bindings/tgui/priv/priv.hpp>
#include <Bindings/tgui/tgui.hpp>
#include <Bindings/tgui/utf/utf.hpp>
#include <Bindings/vili/exceptions/exceptions.hpp>
#include <Bindings/vili/parser/parser.hpp>
#include <Bindings/vili/parser/rules/rules.hpp>
#include <Bindings/vili/utils/string/string.hpp>
#include <Bindings/vili/vili.hpp>
#include <Bindings/vili/writer/writer.hpp>
#include <sol/sol.hpp>
namespace obe::Bindings
{
    void IndexAllBindings(sol::state_view state)
    {
        state["obe"].get_or_create<sol::table>();
        state["tgui"].get_or_create<sol::table>();
        state["vili"].get_or_create<sol::table>();
        state["obe"]["Animation"].get_or_create<sol::table>();
        state["obe"]["Audio"].get_or_create<sol::table>();
        state["obe"]["Collision"].get_or_create<sol::table>();
        state["obe"]["Component"].get_or_create<sol::table>();
        state["obe"]["Config"].get_or_create<sol::table>();
        state["obe"]["Engine"].get_or_create<sol::table>();
        state["obe"]["Event"].get_or_create<sol::table>();
        state["obe"]["Graphics"].get_or_create<sol::table>();
        state["obe"]["Input"].get_or_create<sol::table>();
        state["obe"]["Network"].get_or_create<sol::table>();
        state["obe"]["Scene"].get_or_create<sol::table>();
        state["obe"]["Script"].get_or_create<sol::table>();
        state["obe"]["System"].get_or_create<sol::table>();
        state["obe"]["Tiles"].get_or_create<sol::table>();
        state["obe"]["Time"].get_or_create<sol::table>();
        state["obe"]["Transform"].get_or_create<sol::table>();
        state["obe"]["Types"].get_or_create<sol::table>();
        state["tgui"]["priv"].get_or_create<sol::table>();
        state["vili"]["exceptions"].get_or_create<sol::table>();
        state["vili"]["parser"].get_or_create<sol::table>();
        state["vili"]["writer"].get_or_create<sol::table>();
        state["obe"]["Bindings"].get_or_create<sol::table>();
        state["obe"]["Debug"].get_or_create<sol::table>();
        state["tgui"]["bind_functions"].get_or_create<sol::table>();
        state["tgui"]["keyboard"].get_or_create<sol::table>();
        state["tgui"]["utf"].get_or_create<sol::table>();
        state["obe"]["Utils"].get_or_create<sol::table>();
        state["obe"]["Events"].get_or_create<sol::table>();
        state["vili"]["utils"].get_or_create<sol::table>();
        state["obe"]["Animation"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["Audio"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["Bindings"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["Collision"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["Component"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["Engine"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["Event"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["Graphics"]["Canvas"].get_or_create<sol::table>();
        state["obe"]["Graphics"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["Graphics"]["Shapes"].get_or_create<sol::table>();
        state["obe"]["Input"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["Scene"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["Script"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["System"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["Tiles"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["Transform"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["Utils"]["Exec"].get_or_create<sol::table>();
        state["tgui"]["priv"]["dev"].get_or_create<sol::table>();
        state["obe"]["Events"]["Actions"].get_or_create<sol::table>();
        state["obe"]["Events"]["Cursor"].get_or_create<sol::table>();
        state["obe"]["Events"]["Game"].get_or_create<sol::table>();
        state["obe"]["Events"]["Keys"].get_or_create<sol::table>();
        state["obe"]["Events"]["Network"].get_or_create<sol::table>();
        state["obe"]["Events"]["Scene"].get_or_create<sol::table>();
        state["vili"]["parser"]["rules"].get_or_create<sol::table>();
        state["obe"]["Animation"]["Easing"].get_or_create<sol::table>();
        state["obe"]["Config"]["Templates"].get_or_create<sol::table>();
        state["obe"]["Config"]["Validators"].get_or_create<sol::table>();
        state["obe"]["Debug"]["Render"].get_or_create<sol::table>();
        state["obe"]["Graphics"]["Utils"].get_or_create<sol::table>();
        state["obe"]["Script"]["ViliLuaBridge"].get_or_create<sol::table>();
        state["obe"]["System"]["Package"].get_or_create<sol::table>();
        state["obe"]["System"]["Workspace"].get_or_create<sol::table>();
        state["obe"]["Utils"]["File"].get_or_create<sol::table>();
        state["obe"]["Utils"]["Math"].get_or_create<sol::table>();
        state["obe"]["Utils"]["String"].get_or_create<sol::table>();
        state["obe"]["Utils"]["Vector"].get_or_create<sol::table>();
        state["vili"]["utils"]["string"].get_or_create<sol::table>();
        state["obe"]["System"]["Constraints"].get_or_create<sol::table>();
        obe::Animation::Bindings::LoadClassAnimation(state);
        obe::Animation::Bindings::LoadClassAnimationGroup(state);
        obe::Animation::Bindings::LoadClassAnimationState(state);
        obe::Animation::Bindings::LoadClassAnimator(state);
        obe::Animation::Bindings::LoadClassAnimatorState(state);
        obe::Animation::Bindings::LoadClassValueTweening(state);
        obe::Animation::Bindings::LoadEnumAnimationPlayMode(state);
        obe::Animation::Bindings::LoadEnumAnimationStatus(state);
        obe::Animation::Bindings::LoadEnumAnimatorTargetScaleMode(state);
        obe::Animation::Bindings::LoadFunctionStringToAnimationPlayMode(state);
        obe::Animation::Bindings::LoadFunctionStringToAnimatorTargetScaleMode(state);

        obe::Animation::Exceptions::Bindings::LoadClassAnimationGroupTextureIndexOverflow(
            state);
        obe::Animation::Exceptions::Bindings::LoadClassAnimationTextureIndexOverflow(
            state);
        obe::Animation::Exceptions::Bindings::LoadClassNoSelectedAnimation(state);
        obe::Animation::Exceptions::Bindings::LoadClassNoSelectedAnimationGroup(state);
        obe::Animation::Exceptions::Bindings::LoadClassUnknownAnimation(state);
        obe::Animation::Exceptions::Bindings::LoadClassUnknownAnimationCommand(state);
        obe::Animation::Exceptions::Bindings::LoadClassUnknownAnimationGroup(state);
        obe::Animation::Exceptions::Bindings::LoadClassUnknownAnimationPlayMode(state);
        obe::Animation::Exceptions::Bindings::LoadClassUnknownEasingFromEnum(state);
        obe::Animation::Exceptions::Bindings::LoadClassUnknownEasingFromString(state);
        obe::Animation::Exceptions::Bindings::LoadClassUnknownTargetScaleMode(state);

        obe::Audio::Bindings::LoadClassAudioManager(state);
        obe::Audio::Bindings::LoadClassSound(state);
        obe::Audio::Bindings::LoadEnumLoadPolicy(state);
        obe::Audio::Bindings::LoadEnumSoundStatus(state);

        obe::Audio::Exceptions::Bindings::LoadClassAudioFileNotFound(state);

        obe::Bindings::Exceptions::Bindings::LoadClassBindingTreeNodeNotFound(state);

        obe::Collision::Bindings::LoadClassCollisionData(state);
        obe::Collision::Bindings::LoadClassPolygonalCollider(state);
        obe::Collision::Bindings::LoadClassTrajectory(state);
        obe::Collision::Bindings::LoadClassTrajectoryNode(state);
        obe::Collision::Bindings::LoadEnumColliderTagType(state);

        obe::Collision::Exceptions::Bindings::LoadClassInvalidTagFormat(state);

        obe::Component::Bindings::LoadClassComponentBase(state);

        obe::Component::Exceptions::Bindings::LoadClassComponentIdAlreadyTaken(state);

        obe::Config::Bindings::LoadClassConfigurationManager(state);

        obe::Bindings::LoadClassDebugInfo(state);
        obe::Bindings::LoadClassException(state);
        obe::Bindings::LoadFunctionInitEngine(state);

        obe::Engine::Bindings::LoadClassEngine(state);
        obe::Engine::Bindings::LoadClassResourceManagedObject(state);
        obe::Engine::Bindings::LoadClassResourceManager(state);

        obe::Engine::Exceptions::Bindings::LoadClassBootScriptExecutionError(state);
        obe::Engine::Exceptions::Bindings::LoadClassBootScriptLoadingError(state);
        obe::Engine::Exceptions::Bindings::LoadClassBootScriptMissing(state);
        obe::Engine::Exceptions::Bindings::LoadClassFontNotFound(state);
        obe::Engine::Exceptions::Bindings::LoadClassTextureNotFound(state);
        obe::Engine::Exceptions::Bindings::LoadClassUnitializedEngine(state);

        obe::Event::Bindings::LoadClassCallbackProfiler(state);
        obe::Event::Bindings::LoadClassCallbackScheduler(state);
        obe::Event::Bindings::LoadClassEventBase(state);
        obe::Event::Bindings::LoadClassEventGroup(state);
        obe::Event::Bindings::LoadClassEventGroupView(state);
        obe::Event::Bindings::LoadClassEventManager(state);
        obe::Event::Bindings::LoadClassEventNamespace(state);
        obe::Event::Bindings::LoadClassEventNamespaceView(state);
        obe::Event::Bindings::LoadClassLuaEventListener(state);
        obe::Event::Bindings::LoadClassScopeProfiler(state);
        obe::Event::Bindings::LoadEnumCallbackSchedulerState(state);
        obe::Event::Bindings::LoadEnumListenerChangeState(state);

        obe::Event::Exceptions::Bindings::LoadClassCallbackCreationError(state);
        obe::Event::Exceptions::Bindings::LoadClassEventAlreadyExists(state);
        obe::Event::Exceptions::Bindings::LoadClassEventExecutionError(state);
        obe::Event::Exceptions::Bindings::LoadClassEventGroupAlreadyExists(state);
        obe::Event::Exceptions::Bindings::LoadClassEventGroupNotJoinable(state);
        obe::Event::Exceptions::Bindings::LoadClassEventNamespaceAlreadyExists(state);
        obe::Event::Exceptions::Bindings::LoadClassLuaExecutionError(state);
        obe::Event::Exceptions::Bindings::LoadClassUnknownEvent(state);
        obe::Event::Exceptions::Bindings::LoadClassUnknownEventGroup(state);
        obe::Event::Exceptions::Bindings::LoadClassUnknownEventNamespace(state);

        obe::Graphics::Canvas::Bindings::LoadClassBezier(state);
        obe::Graphics::Canvas::Bindings::LoadClassCanvas(state);
        obe::Graphics::Canvas::Bindings::LoadClassCanvasElement(state);
        obe::Graphics::Canvas::Bindings::LoadClassCanvasPositionable(state);
        obe::Graphics::Canvas::Bindings::LoadClassCircle(state);
        obe::Graphics::Canvas::Bindings::LoadClassLine(state);
        obe::Graphics::Canvas::Bindings::LoadClassPolygon(state);
        obe::Graphics::Canvas::Bindings::LoadClassRectangle(state);
        obe::Graphics::Canvas::Bindings::LoadClassText(state);
        obe::Graphics::Canvas::Bindings::LoadEnumCanvasElementType(state);
        obe::Graphics::Canvas::Bindings::LoadEnumTextHorizontalAlign(state);
        obe::Graphics::Canvas::Bindings::LoadEnumTextVerticalAlign(state);
        obe::Graphics::Canvas::Bindings::LoadFunctionCanvasElementTypeToString(state);

        obe::Graphics::Bindings::LoadClassColor(state);
        obe::Graphics::Bindings::LoadClassFont(state);
        obe::Graphics::Bindings::LoadClassPositionTransformer(state);
        obe::Graphics::Bindings::LoadClassRenderable(state);
        obe::Graphics::Bindings::LoadClassRenderTarget(state);
        obe::Graphics::Bindings::LoadClassRichText(state);
        obe::Graphics::Bindings::LoadClassShader(state);
        obe::Graphics::Bindings::LoadClassSprite(state);
        obe::Graphics::Bindings::LoadClassSpriteHandlePoint(state);
        obe::Graphics::Bindings::LoadClassText(state);
        obe::Graphics::Bindings::LoadClassTexture(state);
        obe::Graphics::Bindings::LoadEnumSpriteHandlePointType(state);
        obe::Graphics::Bindings::LoadFunctionInitPositionTransformer(state);
        obe::Graphics::Bindings::LoadFunctionMakeNullTexture(state);
        obe::Graphics::Bindings::LoadGlobalTransformers(state);
        obe::Graphics::Bindings::LoadGlobalParallax(state);
        obe::Graphics::Bindings::LoadGlobalCamera(state);
        obe::Graphics::Bindings::LoadGlobalPosition(state);

        obe::Graphics::Exceptions::Bindings::LoadClassCanvasElementAlreadyExists(state);
        obe::Graphics::Exceptions::Bindings::LoadClassImageFileNotFound(state);
        obe::Graphics::Exceptions::Bindings::LoadClassInvalidColorName(state);
        obe::Graphics::Exceptions::Bindings::LoadClassInvalidHexFormat(state);
        obe::Graphics::Exceptions::Bindings::LoadClassInvalidHsvFormat(state);
        obe::Graphics::Exceptions::Bindings::LoadClassInvalidRgbFormat(state);
        obe::Graphics::Exceptions::Bindings::LoadClassInvalidSpriteColorType(state);
        obe::Graphics::Exceptions::Bindings::LoadClassReadOnlyTexture(state);

        obe::Graphics::Shapes::Bindings::LoadClassCircle(state);
        obe::Graphics::Shapes::Bindings::LoadClassPolygon(state);
        obe::Graphics::Shapes::Bindings::LoadClassRectangle(state);
        obe::Graphics::Shapes::Bindings::LoadClassText(state);

        obe::Input::Exceptions::Bindings::LoadClassInputButtonAlreadyInCombination(state);
        obe::Input::Exceptions::Bindings::LoadClassInputButtonInvalidOperation(state);
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
        obe::Input::Bindings::LoadFunctionInputButtonStateToString(state);
        obe::Input::Bindings::LoadFunctionStringToInputButtonState(state);
        obe::Input::Bindings::LoadFunctionInputTypeToString(state);

        obe::Network::Bindings::LoadClassLuaPacket(state);
        obe::Network::Bindings::LoadClassNetworkHandler(state);
        obe::Network::Bindings::LoadClassTcpServer(state);
        obe::Network::Bindings::LoadClassTcpSocket(state);

        obe::Scene::Bindings::LoadClassCamera(state);
        obe::Scene::Bindings::LoadClassScene(state);
        obe::Scene::Bindings::LoadClassSceneNode(state);
        obe::Scene::Bindings::LoadClassSceneRenderOptions(state);
        obe::Scene::Bindings::LoadFunctionSceneGetGameObjectProxy(state);
        obe::Scene::Bindings::LoadFunctionSceneCreateGameObjectProxy(state);
        obe::Scene::Bindings::LoadFunctionSceneGetAllGameObjectsProxy(state);

        obe::Scene::Exceptions::Bindings::LoadClassChildNotInSceneNode(state);
        obe::Scene::Exceptions::Bindings::LoadClassGameObjectAlreadyExists(state);
        obe::Scene::Exceptions::Bindings::LoadClassMissingSceneFileBlock(state);
        obe::Scene::Exceptions::Bindings::LoadClassSceneOnLoadCallbackError(state);
        obe::Scene::Exceptions::Bindings::LoadClassSceneScriptLoadingError(state);
        obe::Scene::Exceptions::Bindings::LoadClassUnknownCollider(state);
        obe::Scene::Exceptions::Bindings::LoadClassUnknownGameObject(state);
        obe::Scene::Exceptions::Bindings::LoadClassUnknownSprite(state);

        obe::Script::Exceptions::Bindings::LoadClassInvalidScript(state);
        obe::Script::Exceptions::Bindings::LoadClassNoSuchComponent(state);
        obe::Script::Exceptions::Bindings::LoadClassObjectDefinitionBlockNotFound(state);
        obe::Script::Exceptions::Bindings::LoadClassObjectDefinitionNotFound(state);
        obe::Script::Exceptions::Bindings::LoadClassScriptFileNotFound(state);
        obe::Script::Exceptions::Bindings::LoadClassWrongSourceAttributeType(state);

        obe::Script::Bindings::LoadClassGameObject(state);
        obe::Script::Bindings::LoadClassGameObjectDatabase(state);

        obe::System::Bindings::LoadClassContextualPathFactory(state);
        obe::System::Bindings::LoadClassCursor(state);
        obe::System::Bindings::LoadClassFindResult(state);
        obe::System::Bindings::LoadClassMountablePath(state);
        obe::System::Bindings::LoadClassPath(state);
        obe::System::Bindings::LoadClassPlugin(state);
        obe::System::Bindings::LoadClassWindow(state);
        obe::System::Bindings::LoadEnumMountablePathType(state);
        obe::System::Bindings::LoadEnumPathType(state);
        obe::System::Bindings::LoadEnumWindowContext(state);
        obe::System::Bindings::LoadEnumStretchMode(state);
        obe::System::Bindings::LoadFunctionSplitPathAndPrefix(state);
        obe::System::Bindings::LoadFunctionStringToStretchMode(state);

        obe::System::Exceptions::Bindings::LoadClassInvalidMouseButtonEnumValue(state);
        obe::System::Exceptions::Bindings::LoadClassMountablePathIndexOverflow(state);
        obe::System::Exceptions::Bindings::LoadClassMountFileMissing(state);
        obe::System::Exceptions::Bindings::LoadClassPackageAlreadyInstalled(state);
        obe::System::Exceptions::Bindings::LoadClassPackageFileNotFound(state);
        obe::System::Exceptions::Bindings::LoadClassResourceNotFound(state);
        obe::System::Exceptions::Bindings::LoadClassUnknownPackage(state);
        obe::System::Exceptions::Bindings::LoadClassUnknownPathPrefix(state);
        obe::System::Exceptions::Bindings::LoadClassUnknownStretchMode(state);
        obe::System::Exceptions::Bindings::LoadClassUnknownWorkspace(state);

        obe::Tiles::Bindings::LoadClassAnimatedTile(state);
        obe::Tiles::Bindings::LoadClassTileset(state);
        obe::Tiles::Bindings::LoadClassTilesetCollection(state);
        obe::Tiles::Bindings::LoadClassTileLayer(state);
        obe::Tiles::Bindings::LoadClassTileScene(state);
        obe::Tiles::Bindings::LoadClassTextureQuadsIndex(state);
        obe::Tiles::Bindings::LoadClassTileInfo(state);
        obe::Tiles::Bindings::LoadFunctionGetTileInfo(state);
        obe::Tiles::Bindings::LoadFunctionStripTileFlags(state);
        obe::Tiles::Bindings::LoadFunctionApplyTextureQuadsTransforms(state);

        obe::Tiles::Exceptions::Bindings::LoadClassTilePositionOutsideLayer(state);
        obe::Tiles::Exceptions::Bindings::LoadClassUnknownTileset(state);
        obe::Tiles::Exceptions::Bindings::LoadClassUnknownTileId(state);

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
        obe::Transform::Bindings::LoadEnumFlipAxis(state);
        obe::Transform::Bindings::LoadEnumUnits(state);
        obe::Transform::Bindings::LoadFunctionStringToUnits(state);
        obe::Transform::Bindings::LoadFunctionUnitsToString(state);

        obe::Types::Bindings::LoadClassIdentifiable(state);
        obe::Types::Bindings::LoadClassProtectedIdentifiable(state);
        obe::Types::Bindings::LoadClassSelectable(state);
        obe::Types::Bindings::LoadClassSerializable(state);
        obe::Types::Bindings::LoadClassTogglable(state);

        obe::Utils::Exec::Bindings::LoadClassRunArgsParser(state);

        tgui::priv::dev::Bindings::LoadClassBackgroundComponent(state);
        tgui::priv::dev::Bindings::LoadClassComponent(state);
        tgui::priv::dev::Bindings::LoadClassGroupComponent(state);
        tgui::priv::dev::Bindings::LoadClassImageComponent(state);
        tgui::priv::dev::Bindings::LoadClassMessageBroker(state);
        tgui::priv::dev::Bindings::LoadClassStylePropertyBase(state);
        tgui::priv::dev::Bindings::LoadClassTextComponent(state);
        tgui::priv::dev::Bindings::LoadClassStylePropertyBackground(state);
        tgui::priv::dev::Bindings::LoadClassStylePropertyText(state);
        tgui::priv::dev::Bindings::LoadEnumComponentState(state);
        tgui::priv::dev::Bindings::LoadEnumAlignLayout(state);
        tgui::priv::dev::Bindings::LoadEnumPositionAlignment(state);
        tgui::priv::dev::Bindings::LoadFunctionGetStateFromFlags(state);
        tgui::priv::dev::Bindings::LoadFunctionSetOptionalPropertyValue(state);

        tgui::priv::Bindings::LoadClassAnimation(state);
        tgui::priv::Bindings::LoadClassFadeAnimation(state);
        tgui::priv::Bindings::LoadClassMoveAnimation(state);
        tgui::priv::Bindings::LoadClassResizeAnimation(state);
        tgui::priv::Bindings::LoadFunctionCheckAndLogOpenGlError(state);

        tgui::Bindings::LoadClassAbsoluteOrRelativeValue(state);
        tgui::Bindings::LoadClassBackendBase(state);
        tgui::Bindings::LoadClassBackendFontBase(state);
        tgui::Bindings::LoadClassBackendRenderTargetBase(state);
        tgui::Bindings::LoadClassBackendTextureBase(state);
        tgui::Bindings::LoadClassBackendTextBase(state);
        tgui::Bindings::LoadClassBaseThemeLoader(state);
        tgui::Bindings::LoadClassBitmapButton(state);
        tgui::Bindings::LoadClassBoxLayout(state);
        tgui::Bindings::LoadClassBoxLayoutRatios(state);
        tgui::Bindings::LoadClassBoxLayoutRenderer(state);
        tgui::Bindings::LoadClassButton(state);
        tgui::Bindings::LoadClassButtonBase(state);
        tgui::Bindings::LoadClassButtonRenderer(state);
        tgui::Bindings::LoadClassChatBox(state);
        tgui::Bindings::LoadClassChatBoxRenderer(state);
        tgui::Bindings::LoadClassCheckBox(state);
        tgui::Bindings::LoadClassCheckBoxRenderer(state);
        tgui::Bindings::LoadClassChildWindow(state);
        tgui::Bindings::LoadClassChildWindowRenderer(state);
        tgui::Bindings::LoadClassClickableWidget(state);
        tgui::Bindings::LoadClassColor(state);
        tgui::Bindings::LoadClassColorPicker(state);
        tgui::Bindings::LoadClassColorPickerRenderer(state);
        tgui::Bindings::LoadClassComboBox(state);
        tgui::Bindings::LoadClassComboBoxRenderer(state);
        tgui::Bindings::LoadClassContainer(state);
        tgui::Bindings::LoadClassCursor(state);
        tgui::Bindings::LoadClassCustomWidgetForBindings(state);
        tgui::Bindings::LoadClassDataIO(state);
        tgui::Bindings::LoadClassDefaultBackendWindow(state);
        tgui::Bindings::LoadClassDefaultThemeLoader(state);
        tgui::Bindings::LoadClassDeserializer(state);
        tgui::Bindings::LoadClassDuration(state);
        tgui::Bindings::LoadClassEditBox(state);
        tgui::Bindings::LoadClassEditBoxRenderer(state);
        tgui::Bindings::LoadClassException(state);
        tgui::Bindings::LoadClassFilesystem(state);
        tgui::Bindings::LoadClassFileDialog(state);
        tgui::Bindings::LoadClassFileDialogIconLoader(state);
        tgui::Bindings::LoadClassFileDialogRenderer(state);
        tgui::Bindings::LoadClassFont(state);
        tgui::Bindings::LoadClassGrid(state);
        tgui::Bindings::LoadClassGroup(state);
        tgui::Bindings::LoadClassGroupRenderer(state);
        tgui::Bindings::LoadClassGuiBase(state);
        tgui::Bindings::LoadClassHorizontalLayout(state);
        tgui::Bindings::LoadClassHorizontalWrap(state);
        tgui::Bindings::LoadClassKnob(state);
        tgui::Bindings::LoadClassKnobRenderer(state);
        tgui::Bindings::LoadClassLabel(state);
        tgui::Bindings::LoadClassLabelRenderer(state);
        tgui::Bindings::LoadClassLayout(state);
        tgui::Bindings::LoadClassLayout2d(state);
        tgui::Bindings::LoadClassListBox(state);
        tgui::Bindings::LoadClassListBoxRenderer(state);
        tgui::Bindings::LoadClassListView(state);
        tgui::Bindings::LoadClassListViewRenderer(state);
        tgui::Bindings::LoadClassMenuBar(state);
        tgui::Bindings::LoadClassMenuBarMenuPlaceholder(state);
        tgui::Bindings::LoadClassMenuBarRenderer(state);
        tgui::Bindings::LoadClassMessageBox(state);
        tgui::Bindings::LoadClassMessageBoxRenderer(state);
        tgui::Bindings::LoadClassObjectConverter(state);
        tgui::Bindings::LoadClassOutline(state);
        tgui::Bindings::LoadClassPanel(state);
        tgui::Bindings::LoadClassPanelRenderer(state);
        tgui::Bindings::LoadClassPicture(state);
        tgui::Bindings::LoadClassPictureRenderer(state);
        tgui::Bindings::LoadClassProgressBar(state);
        tgui::Bindings::LoadClassProgressBarRenderer(state);
        tgui::Bindings::LoadClassRadioButton(state);
        tgui::Bindings::LoadClassRadioButtonGroup(state);
        tgui::Bindings::LoadClassRadioButtonRenderer(state);
        tgui::Bindings::LoadClassRangeSlider(state);
        tgui::Bindings::LoadClassRangeSliderRenderer(state);
        tgui::Bindings::LoadClassRootContainer(state);
        tgui::Bindings::LoadClassScrollablePanel(state);
        tgui::Bindings::LoadClassScrollablePanelRenderer(state);
        tgui::Bindings::LoadClassScrollbar(state);
        tgui::Bindings::LoadClassScrollbarChildWidget(state);
        tgui::Bindings::LoadClassScrollbarRenderer(state);
        tgui::Bindings::LoadClassSeparatorLine(state);
        tgui::Bindings::LoadClassSeparatorLineRenderer(state);
        tgui::Bindings::LoadClassSerializer(state);
        tgui::Bindings::LoadClassSignal(state);
        tgui::Bindings::LoadClassSignalAnimation(state);
        tgui::Bindings::LoadClassSignalChildWindow(state);
        tgui::Bindings::LoadClassSignalItem(state);
        tgui::Bindings::LoadClassSignalItemHierarchy(state);
        tgui::Bindings::LoadClassSignalManager(state);
        tgui::Bindings::LoadClassSlider(state);
        tgui::Bindings::LoadClassSliderRenderer(state);
        tgui::Bindings::LoadClassSpinButton(state);
        tgui::Bindings::LoadClassSpinButtonRenderer(state);
        tgui::Bindings::LoadClassSpinControl(state);
        tgui::Bindings::LoadClassSprite(state);
        tgui::Bindings::LoadClassString(state);
        tgui::Bindings::LoadClassSubwidgetContainer(state);
        tgui::Bindings::LoadClassSvgImage(state);
        tgui::Bindings::LoadClassTabs(state);
        tgui::Bindings::LoadClassTabsRenderer(state);
        tgui::Bindings::LoadClassTabContainer(state);
        tgui::Bindings::LoadClassText(state);
        tgui::Bindings::LoadClassTexture(state);
        tgui::Bindings::LoadClassTextureManager(state);
        tgui::Bindings::LoadClassTextArea(state);
        tgui::Bindings::LoadClassTextAreaRenderer(state);
        tgui::Bindings::LoadClassTextStyles(state);
        tgui::Bindings::LoadClassTheme(state);
        tgui::Bindings::LoadClassTimer(state);
        tgui::Bindings::LoadClassToggleButton(state);
        tgui::Bindings::LoadClassToolTip(state);
        tgui::Bindings::LoadClassTransform(state);
        tgui::Bindings::LoadClassTreeView(state);
        tgui::Bindings::LoadClassTreeViewRenderer(state);
        tgui::Bindings::LoadClassVerticalLayout(state);
        tgui::Bindings::LoadClassWidget(state);
        tgui::Bindings::LoadClassWidgetFactory(state);
        tgui::Bindings::LoadClassWidgetRenderer(state);
        tgui::Bindings::LoadClassAny(state);
        tgui::Bindings::LoadClassEvent(state);
        tgui::Bindings::LoadClassFontGlyph(state);
        tgui::Bindings::LoadClassImageLoader(state);
        tgui::Bindings::LoadClassRelativeValue(state);
        tgui::Bindings::LoadClassRelFloatRect(state);
        tgui::Bindings::LoadClassRendererData(state);
        tgui::Bindings::LoadClassRenderStates(state);
        tgui::Bindings::LoadClassTextureData(state);
        tgui::Bindings::LoadClassTextureDataHolder(state);
        tgui::Bindings::LoadClassVertex(state);
        tgui::Bindings::LoadEnumShowAnimationType(state);
        tgui::Bindings::LoadEnumTextStyle(state);
        tgui::Bindings::LoadFunctionAnyCast(state);
        tgui::Bindings::LoadFunctionIsBackendSet(state);
        tgui::Bindings::LoadFunctionSetBackend(state);
        tgui::Bindings::LoadFunctionGetBackend(state);
        tgui::Bindings::LoadFunctionSetGlobalTextSize(state);
        tgui::Bindings::LoadFunctionGetGlobalTextSize(state);
        tgui::Bindings::LoadFunctionSetDoubleClickTime(state);
        tgui::Bindings::LoadFunctionGetDoubleClickTime(state);
        tgui::Bindings::LoadFunctionSetResourcePath(state);
        tgui::Bindings::LoadFunctionGetResourcePath(state);
        tgui::Bindings::LoadFunctionSetEditCursorBlinkRate(state);
        tgui::Bindings::LoadFunctionGetEditCursorBlinkRate(state);
        tgui::Bindings::LoadFunctionReadFileToMemory(state);
        tgui::Bindings::LoadFunctionBindPosX(state);
        tgui::Bindings::LoadFunctionBindPosY(state);
        tgui::Bindings::LoadFunctionBindLeft(state);
        tgui::Bindings::LoadFunctionBindTop(state);
        tgui::Bindings::LoadFunctionBindWidth(state);
        tgui::Bindings::LoadFunctionBindHeight(state);
        tgui::Bindings::LoadFunctionBindInnerWidth(state);
        tgui::Bindings::LoadFunctionBindInnerHeight(state);
        tgui::Bindings::LoadFunctionBindRight(state);
        tgui::Bindings::LoadFunctionBindBottom(state);
        tgui::Bindings::LoadFunctionBindPosition(state);
        tgui::Bindings::LoadFunctionBindSize(state);
        tgui::Bindings::LoadFunctionBindInnerSize(state);
        tgui::Bindings::LoadFunctionBindMin(state);
        tgui::Bindings::LoadFunctionBindMax(state);
        tgui::Bindings::LoadFunctionIsWhitespace(state);

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
        vili::exceptions::Bindings::LoadClassUnknownTemplate(state);
        vili::exceptions::Bindings::LoadFunctionIndentString(state);

        vili::parser::Bindings::LoadClassNodeInStack(state);
        vili::parser::Bindings::LoadClassState(state);
        vili::parser::Bindings::LoadClassError(state);
        vili::parser::Bindings::LoadFunctionStatePushProxy(state);
        vili::parser::Bindings::LoadFunctionFromString(state);
        vili::parser::Bindings::LoadFunctionFromFile(state);

        obe::Events::Actions::Bindings::LoadClassAction(state);

        obe::Events::Cursor::Bindings::LoadClassHold(state);
        obe::Events::Cursor::Bindings::LoadClassMove(state);
        obe::Events::Cursor::Bindings::LoadClassPress(state);
        obe::Events::Cursor::Bindings::LoadClassRelease(state);

        obe::Events::Game::Bindings::LoadClassEnd(state);
        obe::Events::Game::Bindings::LoadClassRender(state);
        obe::Events::Game::Bindings::LoadClassStart(state);
        obe::Events::Game::Bindings::LoadClassUpdate(state);

        obe::Events::Keys::Bindings::LoadClassStateChanged(state);

        obe::Events::Network::Bindings::LoadClassConnected(state);
        obe::Events::Network::Bindings::LoadClassDataReceived(state);
        obe::Events::Network::Bindings::LoadClassDisconnected(state);

        obe::Events::Scene::Bindings::LoadClassLoaded(state);

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
        vili::parser::rules::Bindings::LoadClassTemplateBegin(state);
        vili::parser::rules::Bindings::LoadClassTemplateDecl(state);
        vili::parser::rules::Bindings::LoadClassTemplateDeclContent(state);
        vili::parser::rules::Bindings::LoadClassTemplateIdentifier(state);
        vili::parser::rules::Bindings::LoadClassTemplateIdentifierUsage(state);
        vili::parser::rules::Bindings::LoadClassTemplateKeyword(state);
        vili::parser::rules::Bindings::LoadClassTemplateSpecialization(state);
        vili::parser::rules::Bindings::LoadClassTemplateUsage(state);
        vili::parser::rules::Bindings::LoadClassTrue_(state);
        vili::parser::rules::Bindings::LoadClassUnescaped(state);
        vili::parser::rules::Bindings::LoadClassUnicode(state);
        vili::parser::rules::Bindings::LoadClassViliGrammar(state);
        vili::parser::rules::Bindings::LoadClassXdigit(state);

        vili::writer::Bindings::LoadClassDumpOptions(state);
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

        obe::Animation::Easing::Bindings::LoadEnumEasingType(state);
        obe::Animation::Easing::Bindings::LoadFunctionLinear(state);
        obe::Animation::Easing::Bindings::LoadFunctionInSine(state);
        obe::Animation::Easing::Bindings::LoadFunctionOutSine(state);
        obe::Animation::Easing::Bindings::LoadFunctionInOutSine(state);
        obe::Animation::Easing::Bindings::LoadFunctionInQuad(state);
        obe::Animation::Easing::Bindings::LoadFunctionOutQuad(state);
        obe::Animation::Easing::Bindings::LoadFunctionInOutQuad(state);
        obe::Animation::Easing::Bindings::LoadFunctionInCubic(state);
        obe::Animation::Easing::Bindings::LoadFunctionOutCubic(state);
        obe::Animation::Easing::Bindings::LoadFunctionInOutCubic(state);
        obe::Animation::Easing::Bindings::LoadFunctionInQuart(state);
        obe::Animation::Easing::Bindings::LoadFunctionOutQuart(state);
        obe::Animation::Easing::Bindings::LoadFunctionInOutQuart(state);
        obe::Animation::Easing::Bindings::LoadFunctionInQuint(state);
        obe::Animation::Easing::Bindings::LoadFunctionOutQuint(state);
        obe::Animation::Easing::Bindings::LoadFunctionInOutQuint(state);
        obe::Animation::Easing::Bindings::LoadFunctionInExpo(state);
        obe::Animation::Easing::Bindings::LoadFunctionOutExpo(state);
        obe::Animation::Easing::Bindings::LoadFunctionInOutExpo(state);
        obe::Animation::Easing::Bindings::LoadFunctionInCirc(state);
        obe::Animation::Easing::Bindings::LoadFunctionOutCirc(state);
        obe::Animation::Easing::Bindings::LoadFunctionInOutCirc(state);
        obe::Animation::Easing::Bindings::LoadFunctionInBack(state);
        obe::Animation::Easing::Bindings::LoadFunctionOutBack(state);
        obe::Animation::Easing::Bindings::LoadFunctionInOutBack(state);
        obe::Animation::Easing::Bindings::LoadFunctionInElastic(state);
        obe::Animation::Easing::Bindings::LoadFunctionOutElastic(state);
        obe::Animation::Easing::Bindings::LoadFunctionInOutElastic(state);
        obe::Animation::Easing::Bindings::LoadFunctionInBounce(state);
        obe::Animation::Easing::Bindings::LoadFunctionOutBounce(state);
        obe::Animation::Easing::Bindings::LoadFunctionInOutBounce(state);
        obe::Animation::Easing::Bindings::LoadFunctionGet(state);

        obe::Bindings::Bindings::LoadFunctionIndexAllBindings(state);

        obe::Config::Templates::Bindings::LoadFunctionGetAnimationTemplates(state);
        obe::Config::Templates::Bindings::LoadFunctionGetConfigTemplates(state);
        obe::Config::Templates::Bindings::LoadFunctionGetGameObjectTemplates(state);
        obe::Config::Templates::Bindings::LoadFunctionGetMountTemplates(state);
        obe::Config::Templates::Bindings::LoadFunctionGetSceneTemplates(state);
        obe::Config::Templates::Bindings::LoadGlobalWaitCommand(state);
        obe::Config::Templates::Bindings::LoadGlobalPlayGroupCommand(state);
        obe::Config::Templates::Bindings::LoadGlobalSetAnimationCommand(state);

        obe::Config::Validators::Bindings::LoadFunctionAnimationValidator(state);
        obe::Config::Validators::Bindings::LoadFunctionConfigValidator(state);
        obe::Config::Validators::Bindings::LoadFunctionMountValidator(state);

        obe::Debug::Bindings::LoadFunctionInitLogger(state);
        obe::Debug::Bindings::LoadFunctionTrace(state);
        obe::Debug::Bindings::LoadFunctionDebug(state);
        obe::Debug::Bindings::LoadFunctionInfo(state);
        obe::Debug::Bindings::LoadFunctionWarn(state);
        obe::Debug::Bindings::LoadFunctionError(state);
        obe::Debug::Bindings::LoadFunctionCritical(state);
        obe::Debug::Bindings::LoadGlobalLog(state);

        obe::Debug::Render::Bindings::LoadFunctionDrawPolygon(state);

        obe::Graphics::Utils::Bindings::LoadFunctionDrawPoint(state);
        obe::Graphics::Utils::Bindings::LoadFunctionDrawLine(state);
        obe::Graphics::Utils::Bindings::LoadFunctionDrawPolygon(state);

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

        obe::System::Workspace::Bindings::LoadFunctionGetWorkspaceLocation(state);
        obe::System::Workspace::Bindings::LoadFunctionWorkspaceExists(state);
        obe::System::Workspace::Bindings::LoadFunctionLoad(state);
        obe::System::Workspace::Bindings::LoadFunctionListWorkspaces(state);

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

        tgui::bind_functions::Bindings::LoadFunctionBindPosX(state);
        tgui::bind_functions::Bindings::LoadFunctionBindPosY(state);
        tgui::bind_functions::Bindings::LoadFunctionBindLeft(state);
        tgui::bind_functions::Bindings::LoadFunctionBindTop(state);
        tgui::bind_functions::Bindings::LoadFunctionBindWidth(state);
        tgui::bind_functions::Bindings::LoadFunctionBindHeight(state);
        tgui::bind_functions::Bindings::LoadFunctionBindInnerWidth(state);
        tgui::bind_functions::Bindings::LoadFunctionBindInnerHeight(state);
        tgui::bind_functions::Bindings::LoadFunctionBindRight(state);
        tgui::bind_functions::Bindings::LoadFunctionBindBottom(state);
        tgui::bind_functions::Bindings::LoadFunctionBindPosition(state);
        tgui::bind_functions::Bindings::LoadFunctionBindSize(state);
        tgui::bind_functions::Bindings::LoadFunctionBindInnerSize(state);
        tgui::bind_functions::Bindings::LoadFunctionBindMin(state);
        tgui::bind_functions::Bindings::LoadFunctionBindMax(state);

        tgui::keyboard::Bindings::LoadFunctionIsShiftPressed(state);
        tgui::keyboard::Bindings::LoadFunctionOpenVirtualKeyboard(state);
        tgui::keyboard::Bindings::LoadFunctionCloseVirtualKeyboard(state);
        tgui::keyboard::Bindings::LoadFunctionIsMultiselectModifierPressed(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressCopy(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressCut(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressPaste(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressSelectAll(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressMoveCaretLeft(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressMoveCaretRight(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressMoveCaretWordBegin(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressMoveCaretWordEnd(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressMoveCaretUp(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressMoveCaretDown(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressMoveCaretLineStart(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressMoveCaretLineEnd(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressMoveCaretDocumentBegin(state);
        tgui::keyboard::Bindings::LoadFunctionIsKeyPressMoveCaretDocumentEnd(state);

        tgui::utf::Bindings::LoadFunctionEncodeCharUtf8(state);
        tgui::utf::Bindings::LoadFunctionDecodeCharUtf8(state);
        tgui::utf::Bindings::LoadFunctionConvertUtf8toUtf32(state);
        tgui::utf::Bindings::LoadFunctionConvertUtf16toUtf32(state);
        tgui::utf::Bindings::LoadFunctionConvertWidetoUtf32(state);
        tgui::utf::Bindings::LoadFunctionConvertUtf32toLatin1(state);
        tgui::utf::Bindings::LoadFunctionConvertUtf32toStdStringUtf8(state);
        tgui::utf::Bindings::LoadFunctionConvertUtf32toWide(state);
        tgui::utf::Bindings::LoadFunctionConvertUtf32toUtf16(state);

        vili::utils::string::Bindings::LoadFunctionReplace(state);
        vili::utils::string::Bindings::LoadFunctionIsInt(state);
        vili::utils::string::Bindings::LoadFunctionIsFloat(state);
        vili::utils::string::Bindings::LoadFunctionTruncateFloat(state);
        vili::utils::string::Bindings::LoadFunctionQuote(state);
        vili::utils::string::Bindings::LoadFunctionToDouble(state);
        vili::utils::string::Bindings::LoadFunctionToLong(state);

        obe::System::Constraints::Bindings::LoadGlobalDefault(state);
    }
}