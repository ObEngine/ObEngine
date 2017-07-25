#include <Bindings/SceneBindings.hpp>
#include <Scene/Camera.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace SceneBindings
        {
            void LoadCamera(kaguya::State* lua)
            {
                (*lua)["Core"]["Scene"]["Camera"].setClass(kaguya::UserdataMetatable<Scene::Camera>()
                    .addFunction("getHeight", &Scene::Camera::getHeight)
                    .addFunction("getPosition", &Scene::Camera::getPosition)
                    .addFunction("getSize", &Scene::Camera::getSize)
                    .addFunction("getWidth", &Scene::Camera::getWidth)
                    .addFunction("getX", &Scene::Camera::getX)
                    .addFunction("getY", &Scene::Camera::getY)
                    .addFunction("lock", &Scene::Camera::lock)
                    .addOverloadedFunctions("move",
                        static_cast<void (Scene::Camera::*)(const Transform::UnitVector&)>(&Scene::Camera::move),
                        static_cast<void (Scene::Camera::*)(double, double)>(&Scene::Camera::move)
                    )
                    .addFunction("rotate", &Scene::Camera::rotate)
                    .addFunction("scale", &Scene::Camera::scale)
                    .addFunction("setAngle", &Scene::Camera::setAngle)
                    .addOverloadedFunctions("setPosition",
                        static_cast<void (Scene::Camera::*)(const Transform::UnitVector&, Transform::Referencial)>(&Scene::Camera::setPosition),
                        static_cast<void (Scene::Camera::*)(double, double, Transform::Referencial)>(&Scene::Camera::setPosition)
                    )
                    .addFunction("setSize", &Scene::Camera::setSize)
                    .addFunction("setX", &Scene::Camera::setX)
                    .addFunction("setY", &Scene::Camera::setY)
                    .addFunction("unlock", &Scene::Camera::unlock)
                );
            }
        }  
    }
}
