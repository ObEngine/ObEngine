#include <Bindings/SystemBindings.hpp>
#include <System/Cursor.hpp>
#include <System/Path.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace SystemBindings
        {
            void BindCursor(kaguya::State* lua)
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
            void BindMountablePath(kaguya::State* lua)
            {
                (*lua)["Core"]["System"]["MountablePath"].setClass(kaguya::UserdataMetatable<System::MountablePath>()
                );
            }
            void BindPath(kaguya::State* lua)
            {
                //Missing LoadResource <REVISION>
                (*lua)["Core"]["System"]["Path"].setClass(kaguya::UserdataMetatable<System::Path>()
                    .addStaticFunction("Mount", &System::Path::Mount)
                    .addStaticFunction("Paths", &System::Path::Paths)
                    .addFunction("add", &System::Path::add)
                    .addFunction("getPath", &System::Path::getPath)
                    .addFunction("last", &System::Path::last)
                    .addFunction("toString", &System::Path::toString)
                );
            }
        }
    }
}
