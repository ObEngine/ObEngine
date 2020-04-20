#include <Bindings/Scene/Exceptions/Exceptions.hpp>

#include <Scene/Exceptions.hpp>

#include <sol/sol.hpp>

namespace obe::Scene::Exceptions::Bindings
{
    void LoadClassChildNotInSceneNode(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::ChildNotInSceneNode> bindChildNotInSceneNode
            = ExceptionsNamespace
                  .new_usertype<obe::Scene::Exceptions::ChildNotInSceneNode>(
                      "ChildNotInSceneNode", sol::call_constructor,
                      sol::constructors<obe::Scene::Exceptions::ChildNotInSceneNode(
                          void*, void*, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
};