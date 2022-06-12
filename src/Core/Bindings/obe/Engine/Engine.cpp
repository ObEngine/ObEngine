#include <Bindings/obe/Engine/Engine.hpp>

#include <Engine/Engine.hpp>
#include <Engine/ResourceManager.hpp>

#include <Bindings/Config.hpp>

namespace obe::engine::Bindings
{
    void LoadClassEngine(sol::state_view state)
    {
        sol::table EngineNamespace = state["obe"]["engine"].get<sol::table>();
        sol::usertype<obe::engine::Engine> bindEngine
            = EngineNamespace.new_usertype<obe::engine::Engine>(
                "engine", sol::call_constructor, sol::constructors<obe::engine::Engine()>());
        bindEngine["init"] = &obe::engine::Engine::init;
        bindEngine["run"] = &obe::engine::Engine::run;
        bindEngine["Audio"] = sol::property(&obe::engine::Engine::get_audio_manager);
        bindEngine["Configuration"] = sol::property(&obe::engine::Engine::get_configuration_manager);
        bindEngine["Resources"] = sol::property(&obe::engine::Engine::get_resource_manager);
        bindEngine["Input"] = sol::property(&obe::engine::Engine::get_input_manager);
        bindEngine["Framerate"] = sol::property(&obe::engine::Engine::get_framerate_manager);
        bindEngine["Events"] = sol::property(&obe::engine::Engine::get_event_manager);
        bindEngine["Scene"] = sol::property(&obe::engine::Engine::get_scene);
        bindEngine["Cursor"] = sol::property(&obe::engine::Engine::get_cursor);
        bindEngine["Window"] = sol::property(&obe::engine::Engine::get_window);
    }
    void LoadClassResourceManagedObject(sol::state_view state)
    {
        sol::table EngineNamespace = state["obe"]["engine"].get<sol::table>();
        sol::usertype<obe::engine::ResourceManagedObject> bindResourceManagedObject
            = EngineNamespace.new_usertype<obe::engine::ResourceManagedObject>(
                "ResourceManagedObject", sol::call_constructor, sol::default_constructor);
        bindResourceManagedObject["remove_resource_manager"]
            = &obe::engine::ResourceManagedObject::remove_resource_manager;
        bindResourceManagedObject["attach_resource_manager"]
            = &obe::engine::ResourceManagedObject::attach_resource_manager;
    }
    void LoadClassResourceManager(sol::state_view state)
    {
        sol::table EngineNamespace = state["obe"]["engine"].get<sol::table>();
        sol::usertype<obe::engine::ResourceManager> bindResourceManager
            = EngineNamespace.new_usertype<obe::engine::ResourceManager>("ResourceManager",
                sol::call_constructor, sol::constructors<obe::engine::ResourceManager()>());
        bindResourceManager["get_font"] = &obe::engine::ResourceManager::get_font;
        bindResourceManager["get_texture"]
            = sol::overload(static_cast<const obe::graphics::Texture& (
                                obe::engine::ResourceManager::*)(const obe::System::Path&, bool)>(
                                &obe::engine::ResourceManager::get_texture),
                static_cast<const obe::graphics::Texture& (
                    obe::engine::ResourceManager::*)(const obe::System::Path&)>(
                    &obe::engine::ResourceManager::get_texture));
        bindResourceManager["clean"] = &obe::engine::ResourceManager::clean;
        bindResourceManager["default_anti_aliasing"]
            = &obe::engine::ResourceManager::default_anti_aliasing;
    }
};