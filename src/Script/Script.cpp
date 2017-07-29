#include <SFML/Audio.hpp>
#include <vili/Vili.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Debug/Console.hpp>
#include <Graphics/Canvas.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Input/InputManager.hpp>
#include <Scene/Camera.hpp>
#include <Script/Script.hpp>
#include <Sound/Music.hpp>
#include <Sound/Sound.hpp>
#include <System/Cursor.hpp>
#include <System/Loaders.hpp>
#include <System/Package.hpp>
#include <System/Path.hpp>
#include <Transform/UnitVector.hpp>
#include <Triggers/Trigger.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Types/Selectable.hpp>
#include <Utils/MathUtils.hpp>
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
                    (*lua)["Hook"][name] = containerMap[name].second->as<Debug::Console*>();
                else if (hookType == Utils::Type::getClassType<System::Cursor*>())
                    (*lua)["Hook"][name] = containerMap[name].second->as<System::Cursor*>();
                else if (hookType == Utils::Type::getClassType<Input::InputManager*>())
                    (*lua)["Hook"][name] = containerMap[name].second->as<Input::InputManager*>();
                else if (hookType == Utils::Type::getClassType<Triggers::TriggerDatabase*>())
                    (*lua)["Hook"][name] = containerMap[name].second->as<Triggers::TriggerDatabase*>();
                else if (hookType == Utils::Type::getClassType<Triggers::TriggerGroup*>())
                    (*lua)["Hook"][name] = containerMap[name].second->as<Triggers::TriggerGroup*>();
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
