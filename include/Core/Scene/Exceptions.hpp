#pragma once

#include <Exception.hpp>

namespace obe::Scene::Exceptions
{
    class ChildNotInSceneNode : public Exception
    {
    public:
        ChildNotInSceneNode(void* sceneNode, void* child, DebugInfo info)
            : Exception("ChildNotInSceneNode", info)
        {
            this->error("Impossible to remove Movable {} from SceneNode {} as it is not "
                        "one of its children",
                fmt::ptr(sceneNode), fmt::ptr(child));
        }
    };
}