#include <Bindings/obe/engine/Engine.hpp>

#include <Engine/Engine.hpp>
#include <Engine/ResourceManager.hpp>

#include <Bindings/Config.hpp>

namespace obe::engine::bindings
{
    void load_class_engine(sol::state_view state)
    {
        sol::table engine_namespace = state["obe"]["engine"].get<sol::table>();
        sol::usertype<obe::engine::Engine> bind_engine
            = engine_namespace.new_usertype<obe::engine::Engine>(
                "Engine", sol::call_constructor, sol::constructors<obe::engine::Engine()>());
        bind_engine["init"] = &obe::engine::Engine::init;
        bind_engine["run"] = &obe::engine::Engine::run;
        bind_engine["Audio"] = sol::property(&obe::engine::Engine::get_audio_manager);
        bind_engine["Configuration"]
            = sol::property(&obe::engine::Engine::get_configuration_manager);
        bind_engine["Resources"] = sol::property(&obe::engine::Engine::get_resource_manager);
        bind_engine["Input"] = sol::property(&obe::engine::Engine::get_input_manager);
        bind_engine["Framerate"] = sol::property(&obe::engine::Engine::get_framerate_manager);
        bind_engine["Events"] = sol::property(&obe::engine::Engine::get_event_manager);
        bind_engine["Scene"] = sol::property(&obe::engine::Engine::get_scene);
        bind_engine["Cursor"] = sol::property(&obe::engine::Engine::get_cursor);
        bind_engine["Window"] = sol::property(&obe::engine::Engine::get_window);
    }
    void load_class_resource_managed_object(sol::state_view state)
    {
        sol::table engine_namespace = state["obe"]["engine"].get<sol::table>();
        sol::usertype<obe::engine::ResourceManagedObject> bind_resource_managed_object
            = engine_namespace.new_usertype<obe::engine::ResourceManagedObject>(
                "ResourceManagedObject", sol::call_constructor, sol::default_constructor);
        bind_resource_managed_object["remove_resource_manager"]
            = &obe::engine::ResourceManagedObject::remove_resource_manager;
        bind_resource_managed_object["attach_resource_manager"]
            = &obe::engine::ResourceManagedObject::attach_resource_manager;
    }
    void load_class_resource_manager(sol::state_view state)
    {
        sol::table engine_namespace = state["obe"]["engine"].get<sol::table>();
        sol::usertype<obe::engine::ResourceManager> bind_resource_manager
            = engine_namespace.new_usertype<obe::engine::ResourceManager>("ResourceManager",
                sol::call_constructor, sol::constructors<obe::engine::ResourceManager()>());
        bind_resource_manager["get_font"] = &obe::engine::ResourceManager::get_font;
        bind_resource_manager["get_texture"]
            = sol::overload(static_cast<const obe::graphics::Texture& (
                                obe::engine::ResourceManager::*)(const obe::system::Path&, bool)>(
                                &obe::engine::ResourceManager::get_texture),
                static_cast<const obe::graphics::Texture& (
                    obe::engine::ResourceManager::*)(const obe::system::Path&)>(
                    &obe::engine::ResourceManager::get_texture));
        bind_resource_manager["clean"] = &obe::engine::ResourceManager::clean;
        bind_resource_manager["default_anti_aliasing"]
            = &obe::engine::ResourceManager::default_anti_aliasing;
    }
};