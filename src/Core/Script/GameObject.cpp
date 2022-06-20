#include <utility>

#include <vili/parser.hpp>

#include <Scene/Scene.hpp>
#include <Script/GameObject.hpp>
#include <Script/ViliLuaBridge.hpp>
#include <System/Project.hpp>

namespace obe::script
{
    static std::unordered_map<std::string, sol::bytecode> ScriptCache;

    sol::table GameObject::access() const
    {
        if (m_has_script_engine)
        {
            const auto get_storage_wrapper
                = m_outer_environment["__WRAP_GET_STORAGE"].get<sol::protected_function>();
            return safe_lua_call<sol::table>(get_storage_wrapper);
        }
        throw exceptions::NoSuchComponent("Script", m_type, m_id, EXC_INFO);
    }

    sol::protected_function GameObject::get_constructor() const
    {
        if (m_has_script_engine)
            return m_outer_environment["__WRAP_CALL_INIT"].get<sol::protected_function>();
        throw exceptions::NoSuchComponent("Script", m_type, m_id, EXC_INFO);
    }

    vili::node GameObjectDatabase::AllDefinitions = vili::object {};
    vili::node GameObjectDatabase::AllRequires = vili::object {};
    vili::node GameObjectDatabase::get_requirements_for_game_object(const std::string& type)
    {
        if (!AllRequires.contains(type))
        {
            vili::node get_game_object_file = vili::parser::from_file(
                system::Path("Data/GameObjects/").add(type).add(type + ".obj.vili").find());
            if (get_game_object_file.contains("Requires"))
            {
                vili::node& requires_data = get_game_object_file.at("Requires");
                AllRequires[type] = requires_data;
                return requires_data;
            }
            return vili::node {};
        }
        return AllRequires.at(type);
    }

    vili::node GameObjectDatabase::get_definition_for_game_object(const std::string& type)
    {
        if (!AllDefinitions.contains(type))
        {
            const std::string object_definition_path
                = system::Path(system::project::Prefixes::objects, type)
                      .add(type + ".obj.vili")
                      .find();
            if (object_definition_path.empty())
                throw exceptions::ObjectDefinitionNotFound(type, EXC_INFO);

            vili::node definition_data = vili::parser::from_file(object_definition_path);

            AllDefinitions[type] = definition_data;
            return definition_data;
        }
        return AllDefinitions.at(type);
    }

    void GameObjectDatabase::clear()
    {
        AllDefinitions.clear();
        AllRequires.clear();
    }

    // GameObject
    GameObject::GameObject(sol::state_view lua, const std::string& type, const std::string& id)
        : Identifiable(id)
        , m_lua(std::move(lua))
        , m_type(type)
        , m_filesystem_context(system::Path(system::project::Prefixes::objects, type)
                                   .find(system::PathType::Directory))
    {
    }

    void GameObject::initialize()
    {
        if (!m_initialized)
        {
            debug::Log->debug("<GameObject> Initializing GameObject '{0}' ({1})", m_id, m_type);
            m_initialized = true;
            if (m_has_script_engine)
            {
                try
                {
                    safe_lua_call(this->get_constructor());
                }
                catch (const BaseException& e)
                {
                    throw exceptions::GameObjectScriptError(m_type, m_id, "GameObject:init", EXC_INFO)
                        .nest(e);
                }
            }
            m_active = true;
        }
        else
        {
            debug::Log->warn("<GameObject> GameObject '{0}' ({1}) has already "
                             "been initialized",
                m_id, m_type);
        }
    }

    GameObject::~GameObject()
    {
        debug::Log->debug("<GameObject> Deleting GameObject '{0}' ({1})", m_id, m_type);
        if (m_has_script_engine)
        {
            m_outer_environment = sol::lua_nil;
            m_inner_environment = sol::lua_nil;
        }
    }

    void GameObject::load_game_object(
        scene::Scene& scene, vili::node& obj, engine::ResourceManager* resources)
    {
        debug::Log->debug("<GameObject> Loading GameObject '{0}' ({1})", m_id, m_type);

        if (obj.contains("permanent"))
        {
            m_permanent = obj.at("permanent");
        }
        // Script
        if (obj.contains("Script"))
        {
            vili::node& script = obj.at("Script");
            m_has_script_engine = true;
            m_outer_environment = sol::environment(m_lua, sol::create, m_lua.globals());
            m_inner_environment = sol::environment(m_lua, sol::create, m_outer_environment);

            m_outer_environment["This"] = this;

            load_source("obe://Lib/Internal/ObjectInit.lua", EnvironmentTarget::Outer);

            if (script.contains("source"))
            {
                const vili::node& source_node = script.at("source");
                if (source_node.is<vili::string>())
                {
                    load_source(source_node, EnvironmentTarget::Inner);
                }
                else
                {
                    throw exceptions::WrongSourceAttributeType(m_type, "source",
                        vili::string_typename, vili::to_string(source_node.type()), EXC_INFO);
                }
            }
            else if (script.contains("sources"))
            {
                vili::node& source_node = script.at("sources");
                if (source_node.is<vili::array>())
                {
                    for (const vili::node& source : source_node)
                    {
                        load_source(source, EnvironmentTarget::Inner);
                    }
                }
                else
                {
                    throw exceptions::WrongSourceAttributeType(m_type, "sources",
                        vili::array_typename, vili::to_string(source_node.type()), EXC_INFO);
                }
            }
        }
        // Sprite
        if (obj.contains("Sprite"))
        {
            m_sprite = &scene.create_sprite(m_id, false);
            m_object_node.add_child(*m_sprite);
            m_sprite->load(obj.at("Sprite"));
            m_sprite->set_parent_id(m_id);
            scene.reorganize_layers();
        }
        if (obj.contains("Animator"))
        {
            m_animator = std::make_unique<animation::Animator>();
            vili::node& animator = obj.at("Animator");
            std::string animator_path;
            if (animator.contains("path"))
            {
                animator_path = animator.at("path");
            }

            animation::AnimatorTargetScaleMode scale_mode = animation::AnimatorTargetScaleMode::Fit;
            if (animator.contains("scaling"))
            {
                scale_mode
                    = animation::AnimatorTargetScaleModeMeta::from_string(animator.at("scaling"));
            }
            if (m_sprite)
                m_animator->set_target(*m_sprite, scale_mode);
            if (!animator_path.empty())
            {
                m_animator->load(m_filesystem_context(animator_path), resources);
            }
            if (animator.contains("default"))
            {
                m_animator->set_animation(animator.at("default"));
            }
        }
        // Collider
        if (obj.contains("Collider"))
        {
            m_collider = &scene.create_collider(m_id, false);
            m_object_node.add_child(*m_collider);
            m_collider->load(obj.at("Collider"));
            m_collider->set_parent_id(m_id);
        }
    }

    void GameObject::update()
    {
        if (m_can_update)
        {
            if (m_active)
            {
                if (m_animator)
                {
                    if (!m_animator->get_current_animation_name().empty())
                        m_animator->update();
                    /*if (m_sprite)
                    {
                        m_sprite->set_texture(m_animator->get_current_texture());
                    }*/
                }
            }
            else
            {
                this->initialize();
            }
        }
    }

    std::string GameObject::get_type() const
    {
        return m_type;
    }

    bool GameObject::does_have_animator() const
    {
        return static_cast<bool>(m_animator);
    }

    bool GameObject::does_have_collider() const
    {
        return static_cast<bool>(m_collider);
    }

    bool GameObject::does_have_sprite() const
    {
        return static_cast<bool>(m_sprite);
    }

    bool GameObject::does_have_script_engine() const
    {
        return m_has_script_engine;
    }

    bool GameObject::get_update_state() const
    {
        return m_can_update;
    }

    void GameObject::set_update_state(bool state)
    {
        m_can_update = state;
    }

    graphics::Sprite& GameObject::get_sprite() const
    {
        if (m_sprite)
            return *m_sprite;
        throw exceptions::NoSuchComponent("Sprite", m_type, m_id, EXC_INFO);
    }

    scene::SceneNode& GameObject::get_scene_node()
    {
        return m_object_node;
    }

    collision::PolygonalCollider& GameObject::get_collider() const
    {
        if (m_collider)
            return *m_collider;
        throw exceptions::NoSuchComponent("Collider", m_type, m_id, EXC_INFO);
    }

    animation::Animator& GameObject::get_animator() const
    {
        if (m_animator)
            return *m_animator;
        throw exceptions::NoSuchComponent("Animator", m_type, m_id, EXC_INFO);
    }

    void GameObject::exec(const std::string& query)
    {
        m_lua.safe_script(query, m_outer_environment);
    }

    void GameObject::init_from_vili(const vili::node& data)
    {
        debug::Log->debug("<GameObject> Sending Local.Init table to "
                          "GameObject {1} ({2}) (From Vili)",
            m_id, m_type);
        auto constructor_args = vili_lua_bridge::vili_to_lua(data);
        safe_lua_call(this->get_constructor(), constructor_args);
    }

    void GameObject::destroy()
    {
        if (!this->deletable)
        {
            debug::Log->debug("GameObject::destroy called for '{0}' ({1})", m_id, m_type);

            if (m_has_script_engine)
            {
                try
                {
                    safe_lua_call(
                        m_outer_environment["__WRAP_CALL_DESTROY"].get<sol::protected_function>());
                }
                catch (const BaseException& e)
                {
                    throw exceptions::GameObjectScriptError(m_type, m_id, "GameObject:destroy", EXC_INFO)
                        .nest(e);
                }
            }

            this->deletable = true;
            m_active = false;
            if (m_has_script_engine)
            {
                for (const auto& [k, _] : m_outer_environment)
                {
                    m_outer_environment[k] = sol::lua_nil;
                }
                for (const auto& [k, _] : m_inner_environment)
                {
                    m_inner_environment[k] = sol::lua_nil;
                }
            }
        }
    }

    void GameObject::set_permanent(bool permanent)
    {
        m_permanent = permanent;
    }

    bool GameObject::is_permanent() const
    {
        return m_permanent;
    }

    sol::environment GameObject::get_outer_environment() const
    {
        return m_inner_environment;
    }

    void GameObject::set_state(bool state)
    {
        m_active = state;
    }

    vili::node GameObject::schema() const
    {
        return vili::object {};
    }

    vili::node GameObject::dump() const
    {
        vili::node result = vili::object {};
        result["type"] = this->get_type();

        if (auto dump_function = this->access()["Dump"]; dump_function.valid())
        {
            const sol::table save_table_ref = dump_function().get<sol::table>();
            vili::node save_requirements
                = script::vili_lua_bridge::lua_table_to_vili_object(save_table_ref);
            result["Requires"] = save_requirements;
        }

        return result;
    }

    void GameObject::load(const vili::node& data)
    {
        // TODO: Do something
    }

    void GameObject::load_source(const std::string& path, EnvironmentTarget env)
    {
        const sol::environment& environment
            = (env == EnvironmentTarget::Outer) ? m_outer_environment : m_inner_environment;
        const std::string full_path = m_filesystem_context(path).find();
        if (full_path.empty())
        {
            throw exceptions::ScriptFileNotFound(m_type, m_id, path, EXC_INFO);
        }
        if (!ScriptCache.contains(full_path))
        {
            const sol::load_result target = m_lua.load_file(full_path);
            if (!target.valid())
            {
                throw exceptions::InvalidScript(
                    full_path, target.get<sol::error>().what(), EXC_INFO);
            }
            const sol::protected_function bytecode = target.get<sol::protected_function>();
            ScriptCache.emplace(full_path, bytecode.dump());
        }
        const std::string_view source = ScriptCache.at(full_path).as_string_view();
        if (const sol::protected_function_result load_result
            = m_lua.safe_script(source, environment);
            !load_result.valid())
        {
            throw exceptions::InvalidScript(
                full_path, load_result.get<sol::error>().what(), EXC_INFO);
        }
    }
} // namespace obe::script
