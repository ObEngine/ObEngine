#pragma once

#include <Animation/Animator.hpp>
#include <Collision/PolygonalCollider.hpp>
#include <Debug/Logger.hpp>
#include <Graphics/Sprite.hpp>
#include <Scene/SceneNode.hpp>
#include <Types/Serializable.hpp>
#include <sol/sol.hpp>
#include <vili/node.hpp>

namespace obe::scene
{
    class Scene;
}

/**
 * \additionalinclude{Scene/Scene.hpp}
 */
namespace obe::script
{
    class GameObject;

    /**
     * \brief Manages and caches GameObject definition files and Requirements
     */
    class GameObjectDatabase
    {
    private:
        static vili::node AllRequires;
        static vili::node AllDefinitions;

    public:
        /**
         * \brief Gets the Requires ComplexNode of the GameObject
         * \param type Type of the GameObject to get the Requirements
         * \return A pointer to the Requires ComplexNode of the GameObject
         */
        static vili::node get_requirements_for_game_object(const std::string& type);
        /**
         * \brief Gets the ObjectDefinition ComplexNode of the GameObject
         * \param type Type of the GameObject to get the GameObject Definition File
         * \return A pointer to the ObjectDefinition ComplexNode
         */
        static vili::node get_definition_for_game_object(const std::string& type);
        /**
         * \brief Clears the GameObjectDatabase (cache reload)
         */
        static void clear();
    };

    enum class EnvironmentTarget
    {
        Outer,
        Inner
    };

    /**
     * \brief A GameObject is a set of Components used in the Scene
     */
    class GameObject final : public types::Identifiable, public types::Serializable
    {
    private:
        bool m_permanent = false;
        std::unique_ptr<animation::Animator> m_animator;
        graphics::Sprite* m_sprite = nullptr;
        collision::PolygonalCollider* m_collider = nullptr;
        scene::SceneNode m_object_node;
        sol::state_view m_lua;
        sol::environment m_outer_environment;
        sol::environment m_inner_environment;

        std::string m_type;

        bool m_has_script_engine = false;
        bool m_active = false;
        bool m_initialized = false;
        bool m_can_update = true;

        system::ContextualPathFactory m_filesystem_context;

        friend class scene::Scene;

    public:
        /**
         * \brief Creates a new GameObject
         * \param type Type of the GameObject
         * \param id Id of the GameObject you want to create
         */
        explicit GameObject(sol::state_view lua, const std::string& type, const std::string& id);
        /**
         * \brief Destructor of the GameObject
         */
        ~GameObject() override;
        /**
         * \brief Get the Type of the GameObject
         * \return A std::string containing the type of the GameObject
         */
        [[nodiscard]] std::string get_type() const;
        /**
         * \brief Checks if the GameObject has an Animator Component
         * \return true if the GameObject contains an Animator Component, false
         *         otherwise
         */
        [[nodiscard]] bool does_have_animator() const;
        /**
         * \brief Checks if the GameObject has a Collider Component
         * \return true if the GameObject contains the Collider Component, false
         *         otherwise
         */
        [[nodiscard]] bool does_have_collider() const;
        /**
         * \brief Checks if the GameObject has a Sprite Component
         * \return true if the GameObject contains the Sprite Component,
         *         false otherwise
         */
        [[nodiscard]] bool does_have_sprite() const;
        /**
         * \brief Checks if the GameObject has a Script Component
         * \return true if the GameObject contains the Script Component, false
         *         otherwise
         */
        [[nodiscard]] bool does_have_script_engine() const;
        /**
         * \brief Is the GameObject updated
         * \return true if the GameObject is updated, false otherwise
         */
        [[nodiscard]] bool get_update_state() const;
        /**
         * \brief Sets if the GameObject should be otherwise or not
         * \param state Should be equal to true if the GameObject must updates,
         *        false otherwise
         */
        void set_update_state(bool state);
        /**
         * \rename{Animator}
         * \asproperty
         * \brief Gets the Animator Component of the GameObject (Raises
         *        ObEngine.Script.GameObject.NoAnimator if no Animator Component)
         * \return A pointer to the Animator Component of the GameObject
         */
        [[nodiscard]] animation::Animator& get_animator() const;
        /**
         * \rename{Collider}
         * \asproperty
         * \brief Gets the Collider Component of the GameObject (Raises
         *        ObEngine.Script.GameObject.NoCollider if no Collider Component)
         * \return A pointer to the Collider Component of the GameObject
         */
        [[nodiscard]] collision::PolygonalCollider& get_collider() const;
        /**
         * \rename{Sprite}
         * \asproperty
         * \brief Gets the Sprite Component of the GameObject (Raises
         *        ObEngine.Script.GameObject.NoSprite if no Sprite Component)
         * \return A pointer to the Sprite Component of the GameObject
         */
        [[nodiscard]] graphics::Sprite& get_sprite() const;
        /**
         * \rename{SceneNode}
         * \asproperty
         * \brief Gets the Scene Node of the GameObject (SceneNode that can
         *        manipulate the position of all Scene Components) \return A reference
         * to the GameObject's Scene Node
         */
        [[nodiscard]] scene::SceneNode& get_scene_node();
        /**
         * \brief Execute a Lua String in the Lua State of the GameObject
         * \param query String to execute
         */
        void exec(const std::string& query);
        void init_from_vili(const vili::node& data);
        /**
         * \brief Loads the GameObject through the GameObject Definition File
         * \param scene Scene reference to create components
         * \param obj Vili Node containing the GameObject components
         * \param resources pointer to the ResourceManager
         */
        void load_game_object(
            scene::Scene& scene, vili::node& obj, engine::ResourceManager* resources = nullptr);
        /**
         * \brief Updates the GameObject
         */
        void update();
        /**
         * \rename{destroy}
         * \brief Deletes the GameObject
         */
        void destroy();
        /**
         * \brief Delete State of the GameObject (false = not deleted)
         */
        bool deletable = false;
        /**
         * \brief Access the exposition table of the GameObject
         * \return A reference to the exposition table of the GameObject
         */
        [[nodiscard]] sol::table access() const;
        /**
         * \brief Gets a reference to the Lua function used to build the
         *        GameObject (GameObject:init proxy)
         * \return A reference to the Lua function used to build the GameObject
         */
        [[nodiscard]] sol::protected_function get_constructor() const;
        /**
         * \brief Calls the GameObject constructor
         */
        void initialize();
        /**
         * \brief Configures the permanent parameter of the GameObject
         * \param permanent Should be true if the GameObject should be
         *        permanent, false otherwise
         */
        void set_permanent(bool permanent);
        /**
         * \brief Gets if the GameObject is permanent (Will stay after loading
         *        another map)
         * \return true if the GameObject is permanent, false otherwise
         */
        [[nodiscard]] bool is_permanent() const;

        [[nodiscard]] sol::environment get_outer_environment() const;
        void set_state(bool state);

        [[nodiscard]] vili::node schema() const override;
        [[nodiscard]] vili::node dump() const override;
        void load(const vili::node& data) override;
        void load_source(const std::string& path, EnvironmentTarget env);
    };
} // namespace obe::script
