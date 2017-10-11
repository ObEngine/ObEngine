#include <Bindings/SystemBindings.hpp>
#include <System/Cursor.hpp>
#include <System/Loaders.hpp>
#include <System/Package.hpp>
#include <System/Path.hpp>
#include <System/Workspace.hpp>
#include <Transform/UnitVector.hpp>
#include <System/Window.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace SystemBindings
        {

            std::string getOsName()
            {
                #ifdef _WIN32
                return "Windows 32-bit";
                #elif _WIN64
                return "Windows 64-bit";
                #elif __unix || __unix__
                return "Unix";
                #elif __APPLE__ || __MACH__
                return "Mac OSX";
                #elif __linux__
                return "Linux";
                #elif __FreeBSD__
                return "FreeBSD";
                #else
                return "Other";
                #endif
            }
            void LoadSystemConstants(kaguya::State* lua)
            {
                (*lua)["Core"]["System"]["OS"] = getOsName();
                (*lua)["Core"]["System"]["Screen"] = kaguya::NewTable();
                (*lua)["Core"]["System"]["Screen"]["Width"] = Transform::UnitVector::Screen.w;
                (*lua)["Core"]["System"]["Screen"]["Height"] = Transform::UnitVector::Screen.h;
            }

            void LoadSCursor(kaguya::State* lua)
            {
                (*lua)["Core"]["System"]["Cursor"].setClass(kaguya::UserdataMetatable<System::Cursor>()
                    .addFunction("getRawX", &System::Cursor::getRawX)
                    .addFunction("getRawY", &System::Cursor::getRawY)
                    .addFunction("getX", &System::Cursor::getX)
                    .addFunction("getY", &System::Cursor::getY)
                    .addFunction("setConstraint", &System::Cursor::setConstraint)
                    .addFunction("setPosition", &System::Cursor::setPosition)
                    .addFunction("setX", &System::Cursor::setX)
                    .addFunction("setY", &System::Cursor::setY)
                    .addFunction("update", &System::Cursor::update)
                );
            }
            void LoadMountablePath(kaguya::State* lua)
            {
                (*lua)["Core"]["System"]["MountablePath"].setClass(kaguya::UserdataMetatable<System::MountablePath>()
                    .addProperty("basePath", &System::MountablePath::basePath)
                    .addProperty("priority", &System::MountablePath::priority)
                    .addProperty("pathType", &System::MountablePath::pathType)
                );
                (*lua)["Core"]["System"]["MountPaths"] = kaguya::function(System::MountPaths);
            }

            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                System_find_proxy, System::Path, find, 0, 1, std::string(System::Path::*)(System::PathType)
            );
            void LoadPath(kaguya::State* lua)
            {
                (*lua)["Core"]["System"]["Path"].setClass(kaguya::UserdataMetatable<System::Path>()
                    .setConstructors<System::Path(), System::Path(const std::string&)>()
                    .addStaticFunction("Mount", &System::Path::Mount)
                    .addStaticFunction("Paths", &System::Path::Paths)
                    .addFunction("add", &System::Path::add)
                    .addFunction("find", System_find_proxy())
                    .addFunction("getPath", &System::Path::getPath)
                    .addFunction("last", &System::Path::last)
                    .addFunction("toString", &System::Path::toString)
                );
                (*lua)["Core"]["System"]["Path"]["FileListLoader"] = kaguya::function([](const System::Path& path)
                {
                    std::vector<std::string> fileList;
                    path.loadResource(&fileList, System::Loaders::filePathLoader);
                    return fileList;
                });
                (*lua)["Core"]["System"]["Path"]["DirectoryListLoader"] = kaguya::function([](const System::Path& path)
                {
                    std::vector<std::string> dirList;
                    path.loadResource(&dirList, System::Loaders::dirPathLoader);
                    return dirList;
                });
                (*lua)["Core"]["System"]["Path"]["DataLoader"] = kaguya::function([](const System::Path& path)
                {
                    vili::ViliParser parsedFile;
                    path.loadResource(&parsedFile, System::Loaders::dataLoader);
                    return parsedFile;
                });
                (*lua)["Core"]["System"]["Path"]["FontLoader"] = kaguya::function([](const System::Path& path)
                {
                    sf::Font loadedFont;
                    path.loadResource(&loadedFont, System::Loaders::fontLoader);
                    return loadedFont;
                });
                (*lua)["Core"]["System"]["Path"]["LuaLoader"] = kaguya::function([](const System::Path& path, kaguya::State* lua)
                {
                    path.loadResource(lua, System::Loaders::luaLoader);
                });
                (*lua)["Core"]["System"]["PathType"] = kaguya::NewTable();
                (*lua)["Core"]["System"]["PathType"]["All"] = System::PathType::All;
                (*lua)["Core"]["System"]["PathType"]["Directory"] = System::PathType::Directory;
                (*lua)["Core"]["System"]["PathType"]["File"] = System::PathType::File;
                // Add missing loaders <REVISION>
            }

            void LoadPackage(kaguya::State* lua)
            {
                (*lua)["Core"]["System"]["Package"] = kaguya::NewTable();
                (*lua)["Core"]["System"]["Package"]["GetPackageLocation"] = kaguya::function(System::Package::GetPackageLocation);
                (*lua)["Core"]["System"]["Package"]["PackageExists"] = kaguya::function(System::Package::PackageExists);
                (*lua)["Core"]["System"]["Package"]["Install"] = kaguya::function(System::Package::Install);
                (*lua)["Core"]["System"]["Package"]["Load"] = kaguya::function(System::Package::Load);
            }

            void LoadWorkspace(kaguya::State* lua)
            {
                (*lua)["Core"]["System"]["Workspace"] = kaguya::NewTable();
                (*lua)["Core"]["System"]["Workspace"]["GetWorkspaceLocation"] = kaguya::function(System::Workspace::GetWorkspaceLocation);
                (*lua)["Core"]["System"]["Workspace"]["WorkspaceExists"] = kaguya::function(System::Workspace::WorkspaceExists);
                (*lua)["Core"]["System"]["Workspace"]["Load"] = kaguya::function(System::Workspace::Load);
            }

            void LoadWindow(kaguya::State* lua)
            {
                (*lua)["Core"]["System"]["Window"] = kaguya::NewTable();
                (*lua)["Core"]["System"]["Window"]["setTitle"] = kaguya::function(System::setTitle);
            }
        }
    }
}
