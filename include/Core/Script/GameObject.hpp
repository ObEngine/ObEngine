#pragma once

#include <vili/node.hpp>

#include <Animation/Animator.hpp>
#include <Collision/PolygonalCollider.hpp>
#include <Debug/Logger.hpp>
#include <Graphics/Sprite.hpp>
#include <Scene/SceneNode.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Triggers/TriggerManager.hpp>
#include <Types/Serializable.hpp>

#include <sol/sol.hpp>

#include <vili/node.hpp>

namespace obe::Scene
{
    class Scene;
}

/**
 * \additionalinclude{Scene/Scene.hpp}
 */
namespace obe::Script
{
    class GameObject;

    /**
     * \brief Manages and caches GameObject definition files and Requirements
     */
    class GameObjectDatabase
    {
    private:
        static vili::node allRequires;
        static vili::node allDefinitions;

    public:
        /**
         * \brief Gets the Requires ComplexNode of the GameObject
         * \param type Type of the GameObject to get the Requirements
         * \return A pointer to the Requires ComplexNode of the GameObject
         */
        static vili::node GetRequirementsForGameObject(const std::string& type);
        /**
         * \brief Gets the ObjectDefinition ComplexNode of the GameObject
         * \param type Type of the GameObject to get the GameObject Definition File
         * \return A pointer to the ObjectDefinition ComplexNode
         */
        static vili::node GetDefinitionForGameObject(const std::string& type);
        /**
         * \brief Applies the Requirements to a GameObject using a Requires
         *        ComplexNode
         * \param obj GameObject to applies the requirements to
         * \param requires ComplexNode containing the Requirements
         */
        static void ApplyRequirements(sol::environment environment, vili::node& requires);
        /**
         * \brief Clears the GameObjectDatabase (cache reload)
         */
        static void Clear();
    };

    /**
     * \brief A GameObject is a set of Components used in the Scene
     */
    class GameObject final : public Types::Identifiable, public Types::Serializable
    {
    private:
        Triggers::TriggerManager& m_triggers;
        bool m_permanent = false;
        std::unique_ptr<Animation::Animator> m_animator;
        Graphics::Sprite* m_sprite = nullptr;
        Collision::PolygonalCollider* m_collider = nullptr;
        Triggers::TriggerGroupPtr t_local;
        Scene::SceneNode m_objectNode;
        sol::state_view m_lua;
        sol::environment m_environment;

        std::vector<std::pair<std::weak_ptr<Triggers::Trigger>, std::string>>
            m_registeredTriggers;
        std::vector<std::tuple<std::string, std::string, std::string>>
            m_registeredAliases;

        std::string m_type;
        std::string m_privateKey;

        bool m_hasScriptEngine = false;
        bool m_active = false;
        bool m_canUpdate = true;

        friend class Scene::Scene;

    public:
        /**
         * \brief Creates a new GameObject
         * \param type Type of the GameObject
         * \param id Id of the GameObject you want to create
         */
        explicit GameObject(Triggers::TriggerManager& triggers, sol::state_view lua,
            const std::string& type, const std::string& id);
        /**
         * \brief Destructor of the GameObject
         */
        ~GameObject();
        /**
         * \brief Get the Type of the GameObject
         * \return A std::string containing the type of the GameObject
         */
        [[nodiscard]] std::string getType() const;
        /**
         * \brief Checks if the GameObject has an Animator Component
         * \return true if the GameObject contains an Animator Component, false
         *         otherwise
         */
        [[nodiscard]] bool doesHaveAnimator() const;
        /**
         * \brief Checks if the GameObject has a Collider Component
         * \return true if the GameObject contains the Collider Component, false
         *         otherwise
         */
        [[nodiscard]] bool doesHaveCollider() const;
        /**
         * \brief Checks if the GameObject has a Sprite Component
         * \return true if the GameObject contains the Sprite Component,
         *         false otherwise
         */
        [[nodiscard]] bool doesHaveSprite() const;
        /**
         * \brief Checks if the GameObject has a Script Component
         * \return true if the GameObject contains the Script Component, false
         *         otherwise
         */
        [[nodiscard]] bool doesHaveScriptEngine() const;
        /**
         * \brief Is the GameObject updated
         * \return true if the GameObject is updated, false otherwise
         */
        [[nodiscard]] bool getUpdateState() const;
        /**
         * \brief Sets if the GameObject should be otherwise or not
         * \param state Should be equal to true if the GameObject must updates,
         *        false otherwise
         */
        void setUpdateState(bool state);
        /**
         * \bind{Animator}
         * \asproperty
         * \brief Gets the Animator Component of the GameObject (Raises
         *        ObEngine.Script.GameObject.NoAnimator if no Animator Component)
         * \return A pointer to the Animator Component of the GameObject
         */
        Animation::Animator& getAnimator() const;
        /**
         * \bind{Collider}
         * \asproperty
         * \brief Gets the Collider Component of the GameObject (Raises
         *        ObEngine.Script.GameObject.NoCollider if no Collider Component)
         * \return A pointer to the Collider Component of the GameObject
         */
        Collision::PolygonalCollider& getCollider() const;
        /**
         * \bind{Sprite}
         * \asproperty
         * \brief Gets the Sprite Component of the GameObject (Raises
         *        ObEngine.Script.GameObject.NoSprite if no Sprite Component)
         * \return A pointer to the Sprite Component of the GameObject
         */
        Graphics::Sprite& getSprite() const;
        /**
         * \bind{SceneNode}
         * \asproperty
         * \brief Gets the Scene Node of the GameObject (SceneNode that can
         *        manipulate the position of all Scene Components) \return A reference
         * to the GameObject's Scene Node
         */
        Scene::SceneNode& getSceneNode();
        /**
         * \brief Register a non-local Trigger for the GameObject
         * \param trNsp Namespace where the Trigger to register is
         * \param trGrp TriggerGroup where the Trigger to register is
         * \param trName Name of the Trigger to register
         * \param callAlias Alias (name of the callback) associated with the
         *        Trigger
         */
        void useTrigger(const std::string& trNsp, const std::string& trGrp,
            const std::string& trName, const std::string& callAlias = "");
        void removeTrigger(const std::string& trNsp, const std::string& trGrp,
            const std::string& trName) const;
        /**
         * \brief Execute a Lua String in the Lua State of the GameObject
         * \param query String to execute
         */
        void exec(const std::string& query);
        /**
         * \brief Send a parameter to the Local.Init trigger
         * \tparam U Template Type of the Parameter
         * \param argName Name of the Parameter to push
         * \param value Value of the Parameter
         */
        template <typename U> void sendInitArg(const std::string& argName, U value);
        /**
         * \bind{sendInitArg}
         * \brief Send a parameter to the Local.Init trigger from a Lua VM
         * \param argName Name of the Parameter to push
         * \param value Value of the Parameter
         */
        void sendInitArgFromLua(const std::string& argName, sol::object value) const;
        /**
         * \brief Register a Trigger in the GameObject
         * \param trg Pointer to the Trigger
         * \param callbackName Name of the callback to call when Trigger will be
         *        enabled
         */
        void registerTrigger(
            std::weak_ptr<Triggers::Trigger> trg, const std::string& callbackName);
        /**
         * \brief Loads the GameObject through the GameObject Definition File
         * \param scene Scene reference to create components
         * \param obj Vili Node containing the GameObject components
         * \param resources pointer to the ResourceManager
         */
        void loadGameObject(Scene::Scene& scene, vili::node& obj,
            Engine::ResourceManager* resources = nullptr);
        /**
         * \brief Updates the GameObject
         */
        void update();
        /**
         * \brief Deletes the GameObject
         */
        void deleteObject();
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
         *        GameObject (Local.Init proxy)
         * \return A reference to the Lua function used to build the GameObject
         */
        [[nodiscard]] sol::function getConstructor() const;
        /**
         * \brief Triggers the GameObject's Local.Init
         */
        void initialize();
        /**
         * \brief Configures the permanent parameter of the GameObject
         * \param permanent Should be true if the GameObject should be
         *        permanent, false otherwise
         */
        void setPermanent(bool permanent);
        /**
         * \brief Gets if the GameObject is permanent (Will stay after loading
         *        another map)
         * \return true if the GameObject is permanent, false otherwise
         */
        [[nodiscard]] bool isPermanent() const;

        sol::environment getEnvironment() const;
        void setState(bool state);

        [[nodiscard]] vili::node dump() const override;
        void load(vili::node& data) override;
    };

    template <typename U>
    void GameObject::sendInitArg(const std::string& argName, U value)
    {
        Debug::Log->debug(
            "<GameObject> Sending Local.Init argument {0} to GameObject {1}", argName,
            m_id);
        t_local->pushParameter("Init", argName, value);
    }
} // namespace obe::Script
