#include <Bindings/SystemBindings.hpp>
#include <System/Cursor.hpp>
#include <System/Loaders.hpp>
#include <System/Package.hpp>
#include <System/Path.hpp>
#include <System/Workspace.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace SystemBindings
        {
            void LoadSCursor(kaguya::State* lua)
            {
                (*lua)["Core"]["System"]["Cursor"].setClass(kaguya::UserdataMetatable<System::Cursor>()
                    .addFunction("display", &System::Cursor::display)
                    .addFunction("getRawX", &System::Cursor::getRawX)
                    .addFunction("getRawY", &System::Cursor::getRawY)
                    .addFunction("getX", &System::Cursor::getX)
                    .addFunction("getY", &System::Cursor::getY)
                    .addFunction("selectAnimationKey", &System::Cursor::selectAnimationKey)
                    .addFunction("selectAnimatorPath", &System::Cursor::selectAnimatorPath)
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
                );
            }
            void LoadPath(kaguya::State* lua)
            {
                (*lua)["Core"]["System"]["Path"].setClass(kaguya::UserdataMetatable<System::Path>()
                    .addStaticFunction("Mount", &System::Path::Mount)
                    .addStaticFunction("Paths", &System::Path::Paths)
                    .addFunction("add", &System::Path::add)
                    .addFunction("getPath", &System::Path::getPath)
                    .addFunction("last", &System::Path::last)
                    .addFunction("toString", &System::Path::toString)
                );
                (*lua)["Core"]["System"]["Path"]["FileListLoader"] = kaguya::function([](const std::string& path)
                {
                    std::vector<std::string> fileList;
                    System::Path(path).loadResource(&fileList, System::Loaders::filePathLoader);
                    return fileList;
                });
                (*lua)["Core"]["System"]["Path"]["DirectoryListLoader"] = kaguya::function([](const std::string& path)
                {
                    std::vector<std::string> dirList;
                    System::Path(path).loadResource(&dirList, System::Loaders::dirPathLoader);
                    return dirList;
                });
                (*lua)["Core"]["System"]["Path"]["DataLoader"] = kaguya::function([](const std::string& path)
                {
                    vili::ViliParser parsedFile;
                    System::Path(path).loadResource(&parsedFile, System::Loaders::dataLoader);
                    return parsedFile;
                });
                (*lua)["Core"]["System"]["Path"]["FontLoader"] = kaguya::function([](const std::string& path)
                {
                    sf::Font loadedFont;
                    System::Path(path).loadResource(&loadedFont, System::Loaders::fontLoader);
                    return loadedFont;
                });
                (*lua)["Core"]["System"]["Path"]["LuaLoader"] = kaguya::function([](kaguya::State* lua, const std::string& path)
                {
                    System::Path(path).loadResource(lua, System::Loaders::luaLoader);
                });
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
        }
    }
}
