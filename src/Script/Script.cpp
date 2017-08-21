#include <vili/Vili.hpp>

#include <Bindings/Bindings.hpp>
#include <Collision/PolygonalCollider.hpp>
#include <Debug/Console.hpp>
#include <Editor/Grid.hpp>
#include <Graphics/Canvas.hpp>
#include <Input/InputManager.hpp>
#include <Script/Script.hpp>
#include <System/Cursor.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/TypeUtils.hpp>

namespace obe
{
    namespace Script
    {
        CoreHook hookCore;

        void CoreHook::getValue(kaguya::State* lua, std::string name)
        {
            if (containerMap.find(name) != containerMap.end())
            {
                std::string hookType = containerMap[name].first;
                if (hookType == Utils::Type::getClassType<Debug::Console*>())
                {
                    (*lua)["Hook"][name] = containerMap[name].second->as<Debug::Console*>();
                }
                else if (hookType == Utils::Type::getClassType<System::Cursor*>())
                {
                    (*lua)["Hook"][name] = containerMap[name].second->as<System::Cursor*>();
                }
                else if (hookType == Utils::Type::getClassType<Input::InputManager*>())
                {
                    (*lua)["Hook"][name] = containerMap[name].second->as<Input::InputManager*>();
                }
                else if (hookType == Utils::Type::getClassType<Triggers::TriggerDatabase*>())
                {
                    (*lua)["Hook"][name] = containerMap[name].second->as<Triggers::TriggerDatabase*>();
                }
                else if (hookType == Utils::Type::getClassType<Triggers::TriggerGroup*>())
                {
                    (*lua)["Hook"][name] = containerMap[name].second->as<Triggers::TriggerGroup*>();
                }
                else if (hookType == Utils::Type::getClassType<Editor::EditorGrid*>())
                {
                    (*lua)["Hook"][name] = containerMap[name].second->as<Editor::EditorGrid*>();
                }
                else
                    throw aube::ErrorHandler::Raise("ObEngine.Script.CoreHook.UnknownHookType", {{"type", hookType}, {"name", name}});
            }
            else
                throw aube::ErrorHandler::Raise("ObEngine.Script.CoreHook.UnknownHookName", {{"name", name}});
        }

        Types::Any* CoreHook::getPointer(std::string name)
        {
            if (containerMap.find(name) != containerMap.end())
            {
                return containerMap[name].second;
            }
            throw aube::ErrorHandler::Raise("ObEngine.Script.CoreHook.UnknownPointerName", {{"name", name}});
        }

        void loadHook(kaguya::State* lua, std::string hookname)
        {
            hookCore.getValue(lua, hookname);
        }
    }
}
