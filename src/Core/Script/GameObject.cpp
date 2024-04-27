#include <utility>

#include <vili/parser.hpp>

#include <Scene/Scene.hpp>
#include <Script/GameObject.hpp>
#include <System/Project.hpp>

namespace obe::script
{
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
                throw exceptions::ObjectDefinitionNotFound(type);

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
    GameObject::GameObject(const std::string& type, const std::string& id)
        : Identifiable(id)
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
            const std::string collider_id = fmt::format("{}_collider", m_id);
            m_collider = &scene.create_collider(collider_id, false);
            m_object_node.add_child(*m_collider->get_inner_collider());
            m_collider->load(obj.at("Collider"));
            m_component_ids.insert(collider_id);
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
        throw exceptions::NoSuchComponent("Sprite", m_type, m_id);
    }

    scene::SceneNode& GameObject::get_scene_node()
    {
        return m_object_node;
    }

    collision::ColliderComponent& GameObject::get_collider() const
    {
        if (m_collider)
            return *m_collider;
        throw exceptions::NoSuchComponent("Collider", m_type, m_id);
    }

    animation::Animator& GameObject::get_animator() const
    {
        if (m_animator)
            return *m_animator;
        throw exceptions::NoSuchComponent("Animator", m_type, m_id);
    }

    void GameObject::exec(const std::string& query)
    {
    }

    void GameObject::init_from_vili(const vili::node& data)
    {
        debug::Log->debug("<GameObject> Initializing GameObject {} ({}) (From Vili)", m_id, m_type);
    }

    void GameObject::destroy()
    {
        if (!this->deletable)
        {
            debug::Log->debug("GameObject::destroy called for '{0}' ({1})", m_id, m_type);

            if (m_has_script_engine)
            {
            }

            this->deletable = true;
            m_active = false;
            if (m_has_script_engine)
            {
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

        return result;
    }

    void GameObject::load(const vili::node& data)
    {
        // TODO: Do something
    }

    void GameObject::load_source(const std::string& path, EnvironmentTarget env)
    {
    }

    bool GameObject::is_parent_of_component(const std::string& component_id) const
    {
        return m_component_ids.contains(component_id);
    }
} // namespace obe::script
