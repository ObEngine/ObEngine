#include <Bindings/Engine/Engine.hpp>

#include <Engine/Engine.hpp>
#include <Engine/ResourceManager.hpp>

#include <sol/sol.hpp>

namespace obe::Engine::Bindings
{
    void LoadClassEngine(sol::state_view state)
    {
        sol::table EngineNamespace = state["obe"]["Engine"].get<sol::table>();
        sol::usertype<obe::Engine::Engine> bindEngine
            = EngineNamespace.new_usertype<obe::Engine::Engine>("Engine",
                sol::call_constructor, sol::constructors<obe::Engine::Engine()>());
        bindEngine["Window"] = sol::property(&obe::Engine::Engine::getWindow);
        bindEngine["Framerate"]
            = sol::property(&obe::Engine::Engine::getFramerateManager);
        bindEngine["Audio"] = sol::property(&obe::Engine::Engine::getAudioManager);
        bindEngine["Scene"] = sol::property(&obe::Engine::Engine::getScene);
        bindEngine["Configuration"]
            = sol::property(&obe::Engine::Engine::getConfigurationManager);
        bindEngine["Input"] = sol::property(&obe::Engine::Engine::getInputManager);
        bindEngine["Resources"] = sol::property(&obe::Engine::Engine::getResourceManager);
        bindEngine["Triggers"] = sol::property(&obe::Engine::Engine::getTriggerManager);
        bindEngine["Cursor"] = sol::property(&obe::Engine::Engine::getCursor);
    }
    void LoadClassResourceManagedObject(sol::state_view state)
    {
        sol::table EngineNamespace = state["obe"]["Engine"].get<sol::table>();
        sol::usertype<obe::Engine::ResourceManagedObject> bindResourceManagedObject
            = EngineNamespace.new_usertype<obe::Engine::ResourceManagedObject>(
                "ResourceManagedObject", sol::call_constructor, sol::default_constructor);
        bindResourceManagedObject["removeResourceManager"]
            = &obe::Engine::ResourceManagedObject::removeResourceManager;
        bindResourceManagedObject["attachResourceManager"]
            = &obe::Engine::ResourceManagedObject::attachResourceManager;
    }
    void LoadClassResourceManager(sol::state_view state)
    {
        sol::table EngineNamespace = state["obe"]["Engine"].get<sol::table>();
        sol::usertype<obe::Engine::ResourceManager> bindResourceManager
            = EngineNamespace.new_usertype<obe::Engine::ResourceManager>(
                "ResourceManager", sol::call_constructor,
                sol::constructors<obe::Engine::ResourceManager()>());
        bindResourceManager["getFont"] = &obe::Engine::ResourceManager::getFont;
        bindResourceManager["getTexture"] = sol::overload(
            static_cast<std::shared_ptr<Graphics::Texture> (
                obe::Engine::ResourceManager::*)(const std::string&, bool)>(
                &obe::Engine::ResourceManager::getTexture),
            static_cast<std::shared_ptr<Graphics::Texture> (
                obe::Engine::ResourceManager::*)(const std::string&)>(
                &obe::Engine::ResourceManager::getTexture));
        bindResourceManager["defaultAntiAliasing"]
            = sol::readonly(&obe::Engine::ResourceManager::defaultAntiAliasing);
    }
};