#include <Bindings/obe/System/System.hpp>

#include <System/Cursor.hpp>
#include <System/MountablePath.hpp>
#include <System/Path.hpp>
#include <System/Plugin.hpp>
#include <System/Window.hpp>

#include <Bindings/Config.hpp>

namespace obe::System::Bindings
{
    void LoadEnumMountablePathType(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        SystemNamespace.new_enum<obe::System::MountablePathType>("MountablePathType",
            { { "Path", obe::System::MountablePathType::Path },
                { "Package", obe::System::MountablePathType::Package },
                { "Project", obe::System::MountablePathType::Project } });
    }
    void LoadEnumPathType(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        SystemNamespace.new_enum<obe::System::PathType>("PathType",
            { { "All", obe::System::PathType::All },
                { "Directory", obe::System::PathType::Directory },
                { "File", obe::System::PathType::File } });
    }
    void LoadEnumWindowContext(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        SystemNamespace.new_enum<obe::System::WindowContext>("WindowContext",
            { { "GameWindow", obe::System::WindowContext::GameWindow },
                { "EditorWindow", obe::System::WindowContext::EditorWindow } });
    }
    void LoadEnumStretchMode(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        SystemNamespace.new_enum<obe::System::StretchMode>("StretchMode",
            { { "None", obe::System::StretchMode::None },
                { "Center", obe::System::StretchMode::Center },
                { "Stretch", obe::System::StretchMode::Stretch },
                { "Fit", obe::System::StretchMode::Fit } });
    }
    void LoadClassContextualPathFactory(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::ContextualPathFactory> bindContextualPathFactory
            = SystemNamespace.new_usertype<obe::System::ContextualPathFactory>(
                "ContextualPathFactory", sol::call_constructor,
                sol::constructors<obe::System::ContextualPathFactory(const std::string&),
                    obe::System::ContextualPathFactory(const std::string&,
                        const MountList&)>());
        bindContextualPathFactory[sol::meta_function::call]
            = &obe::System::ContextualPathFactory::operator();
    }
    void LoadClassCursor(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::Cursor> bindCursor
            = SystemNamespace.new_usertype<obe::System::Cursor>("Cursor",
                sol::call_constructor,
                sol::constructors<obe::System::Cursor(
                    obe::System::Window&, obe::Event::EventNamespace&)>());
        bindCursor["getConstrainedX"] = &obe::System::Cursor::getConstrainedX;
        bindCursor["getConstrainedY"] = &obe::System::Cursor::getConstrainedY;
        bindCursor["getX"] = &obe::System::Cursor::getX;
        bindCursor["getY"] = &obe::System::Cursor::getY;
        bindCursor["setX"] = &obe::System::Cursor::setX;
        bindCursor["setY"] = &obe::System::Cursor::setY;
        bindCursor["setPosition"] = &obe::System::Cursor::setPosition;
        bindCursor["show"] = &obe::System::Cursor::show;
        bindCursor["hide"] = &obe::System::Cursor::hide;
        bindCursor["setVisible"] = &obe::System::Cursor::setVisible;
        bindCursor["isVisible"] = &obe::System::Cursor::isVisible;
        bindCursor["getPosition"] = &obe::System::Cursor::getPosition;
        bindCursor["getScenePosition"] = &obe::System::Cursor::getScenePosition;
        bindCursor["update"] = &obe::System::Cursor::update;
        bindCursor["setConstraint"] = sol::overload(
            [](obe::System::Cursor* self,
                std::function<std::pair<int, int>(obe::System::Cursor*)> constraint)
                -> void { return self->setConstraint(constraint); },
            [](obe::System::Cursor* self,
                std::function<std::pair<int, int>(obe::System::Cursor*)> constraint,
                std::function<bool()> condition) -> void
            { return self->setConstraint(constraint, condition); });
        bindCursor["isPressed"] = &obe::System::Cursor::isPressed;
    }
    void LoadClassFindResult(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::FindResult> bindFindResult
            = SystemNamespace.new_usertype<obe::System::FindResult>("FindResult",
                sol::call_constructor,
                sol::constructors<obe::System::FindResult(const std::string&,
                                      const MountList&),
                    obe::System::FindResult(obe::System::PathType,
                        std::shared_ptr<obe::System::MountablePath>, const std::string&,
                        const std::string&)>());
        bindFindResult["path"] = &obe::System::FindResult::path;
        bindFindResult["mount"] = &obe::System::FindResult::mount;
        bindFindResult["query"] = &obe::System::FindResult::query;
        bindFindResult["success"] = &obe::System::FindResult::success;
    }
    void LoadClassMountablePath(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::MountablePath> bindMountablePath
            = SystemNamespace.new_usertype<obe::System::MountablePath>("MountablePath",
                sol::call_constructor,
                sol::constructors<obe::System::MountablePath(
                                      obe::System::MountablePathType, const std::string&,
                                      const std::string&),
                    obe::System::MountablePath(obe::System::MountablePathType,
                        const std::string&, const std::string&, unsigned int),
                    obe::System::MountablePath(obe::System::MountablePathType,
                        const std::string&, const std::string&, unsigned int, bool)>());
        bindMountablePath[sol::meta_function::equal_to]
            = &obe::System::MountablePath::operator==;
        bindMountablePath["LoadMountFile"] = sol::overload([]() -> void
            { return MountablePath::LoadMountFile(); },
            [](bool fromCWD) -> void { return MountablePath::LoadMountFile(fromCWD); },
            [](bool fromCWD, bool fromExe) -> void
            { return MountablePath::LoadMountFile(fromCWD, fromExe); });
        bindMountablePath["Mount"] = &obe::System::MountablePath::Mount;
        bindMountablePath["Unmount"] = &obe::System::MountablePath::Unmount;
        bindMountablePath["UnmountAll"] = &obe::System::MountablePath::UnmountAll;
        bindMountablePath["Paths"] = &obe::System::MountablePath::Paths;
        bindMountablePath["StringPaths"] = &obe::System::MountablePath::StringPaths;
        bindMountablePath["Sort"] = &obe::System::MountablePath::Sort;
        bindMountablePath["pathType"] = &obe::System::MountablePath::pathType;
        bindMountablePath["basePath"] = &obe::System::MountablePath::basePath;
        bindMountablePath["prefix"] = &obe::System::MountablePath::prefix;
        bindMountablePath["priority"] = &obe::System::MountablePath::priority;
        bindMountablePath["implicit"] = &obe::System::MountablePath::implicit;
    }
    void LoadClassPath(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::Path> bindPath
            = SystemNamespace.new_usertype<obe::System::Path>("Path",
                sol::call_constructor,
                sol::constructors<obe::System::Path(),
                    obe::System::Path(const MountList&),
                    obe::System::Path(const obe::System::Path&),
                    obe::System::Path(std::string_view),
                    obe::System::Path(std::string_view, std::string_view)>());
        bindPath["set"] = &obe::System::Path::set;
        bindPath["add"] = &obe::System::Path::add;
        bindPath["last"] = &obe::System::Path::last;
        bindPath["getPath"] = &obe::System::Path::getPath;
        bindPath["list"] = sol::overload(
            [](obe::System::Path* self) -> std::vector<obe::System::FindResult> {
                return self->list();
            },
            [](obe::System::Path* self, obe::System::PathType pathType)
                -> std::vector<obe::System::FindResult> { return self->list(pathType); });
        bindPath["find"]
            = sol::overload([](obe::System::Path* self) -> obe::System::FindResult
                { return self->find(); },
                [](obe::System::Path* self,
                    obe::System::PathType pathType) -> obe::System::FindResult
                { return self->find(pathType); });
        bindPath["findAll"] = sol::overload(
            [](obe::System::Path* self) -> std::vector<obe::System::FindResult> {
                return self->findAll();
            },
            [](obe::System::Path* self,
                obe::System::PathType pathType) -> std::vector<obe::System::FindResult> {
                return self->findAll(pathType);
            });
        bindPath["toString"] = &obe::System::Path::toString;
    }
    void LoadClassPlugin(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::Plugin> bindPlugin
            = SystemNamespace.new_usertype<obe::System::Plugin>("Plugin",
                sol::call_constructor,
                sol::constructors<obe::System::Plugin(
                    const std::string&, const std::string&)>(),
                sol::base_classes, sol::bases<obe::Types::Identifiable>());
        bindPlugin["onLoadBindings"] = &obe::System::Plugin::onLoadBindings;
        bindPlugin["onUpdate"] = &obe::System::Plugin::onUpdate;
        bindPlugin["onRender"] = &obe::System::Plugin::onRender;
        bindPlugin["onExit"] = &obe::System::Plugin::onExit;
        bindPlugin["hasOnInit"] = &obe::System::Plugin::hasOnInit;
        bindPlugin["hasOnLoadBindings"] = &obe::System::Plugin::hasOnLoadBindings;
        bindPlugin["hasOnUpdate"] = &obe::System::Plugin::hasOnUpdate;
        bindPlugin["hasOnRender"] = &obe::System::Plugin::hasOnRender;
        bindPlugin["hasOnExit"] = &obe::System::Plugin::hasOnExit;
    }
    void LoadClassWindow(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::Window> bindWindow
            = SystemNamespace.new_usertype<obe::System::Window>("Window",
                sol::call_constructor,
                sol::constructors<obe::System::Window(vili::node)>());
        bindWindow["create"] = &obe::System::Window::create;
        bindWindow["clear"] = &obe::System::Window::clear;
        bindWindow["close"] = &obe::System::Window::close;
        bindWindow["display"] = &obe::System::Window::display;
        bindWindow["getRenderSize"] = &obe::System::Window::getRenderSize;
        bindWindow["getWindowSize"] = &obe::System::Window::getWindowSize;
        bindWindow["getScreenSize"] = &obe::System::Window::getScreenSize;
        bindWindow["getSize"] = &obe::System::Window::getSize;
        bindWindow["isOpen"] = &obe::System::Window::isOpen;
        bindWindow["pollEvent"] = &obe::System::Window::pollEvent;
        bindWindow["setSize"] = &obe::System::Window::setSize;
        bindWindow["setWindowSize"] = &obe::System::Window::setWindowSize;
        bindWindow["setRenderSize"] = &obe::System::Window::setRenderSize;
        bindWindow["setTitle"] = &obe::System::Window::setTitle;
        bindWindow["setVerticalSyncEnabled"]
            = &obe::System::Window::setVerticalSyncEnabled;
        bindWindow["setView"] = &obe::System::Window::setView;
        bindWindow["setIcon"] = &obe::System::Window::setIcon;
        bindWindow["getTarget"] = &obe::System::Window::getTarget;
        bindWindow["getWindow"] = &obe::System::Window::getWindow;
        bindWindow["getClearColor"] = &obe::System::Window::getClearColor;
        bindWindow["setClearColor"] = &obe::System::Window::setClearColor;
        bindWindow["setMouseCursorVisible"] = &obe::System::Window::setMouseCursorVisible;
    }
    void LoadFunctionSplitPathAndPrefix(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        SystemNamespace.set_function(
            "splitPathAndPrefix", obe::System::splitPathAndPrefix);
    }
    void LoadFunctionStringToStretchMode(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        SystemNamespace.set_function(
            "stringToStretchMode", obe::System::stringToStretchMode);
    }
};