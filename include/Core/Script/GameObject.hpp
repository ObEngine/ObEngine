#pragma once

#include <kaguya/kaguya.hpp>
#include <vili/Vili.hpp>

#include <Animation/Animator.hpp>
#include <Collision/PolygonalCollider.hpp>
#include <Debug/Logger.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Scene/SceneNode.hpp>
#include <Triggers/TriggerGroup.hpp>

namespace obe::Scene
{
    class Scene;
}

namespace obe::Script
{
    class GameObject;

    /**
    * \brief Manages and caches GameObject GODF and Requirements
    */
    class GameObjectDatabase
    {
    private:
        static vili::ViliParser allRequires;
        static vili::ViliParser allDefinitions;
    public:
        /**
        * \brief Gets the Requires ComplexNode of the GameObject
        * \param type Type of the GameObject to get the Requirements
        * \return A pointer to the Requires ComplexNode of the GameObject
        */
        static vili::ComplexNode* GetRequirementsForGameObject(const std::string& type);
        /**
        * \brief Gets the ObjectDefintion ComplexNode of the GameObject
        * \param type Type of the GameObject to get the GODF
        * \return A pointer to the ObjectDefintion ComplexNode
        */
        static vili::ComplexNode* GetDefinitionForGameObject(const std::string& type);
        /**
        * \brief Applies the Requirements to a GameObject using a Requires ComplexNode
        * \param obj GameObject to applies the requirements to
        * \param requires ComplexNode containing the Requirements
        */
        static void ApplyRequirements(GameObject* obj, vili::ComplexNode& requires);
    };

    /**
    * \brief A GameObject is a set of Components used in the Scene
    */
    class GameObject : public Types::Identifiable
    {
    private:
        unsigned int m_envIndex;
        bool m_permanent = false;
        std::unique_ptr<Animation::Animator> m_objectAnimator;
        Graphics::LevelSprite* m_objectLevelSprite;
        Collision::PolygonalCollider* m_objectCollider;
        Triggers::TriggerGroupPtr m_localTriggers;
        Scene::SceneNode m_objectNode;

        std::vector<std::pair<Triggers::Trigger*, std::string>> m_registeredTriggers;
        std::vector<std::tuple<std::string, std::string, std::string>> m_registeredAliases;

        std::string m_type;
        std::string m_privateKey;

        bool m_hasAnimator = false;
        bool m_hasCollider = false;
        bool m_hasLevelSprite = false;
        bool m_hasScriptEngine = false;
        bool m_active = false;
        bool m_canUpdate = true;

        friend class Scene::Scene;
    public:
        static std::vector<unsigned int> AllEnvs;
        /**
        * \brief Creates a new GameObject
        * \param type Type of the GameObject
        * \param id Id of the GameObject you want to create
        */
        explicit GameObject(const std::string& type, const std::string& id);
        /**
        * \brief Destructor of the GameObject
        */
        ~GameObject();
        /**
        * \brief Get the Type of the GameObject
        * \return A std::string containing the type of the GameObject
        */
        std::string getType() const;
        /**
        * \brief Checks if the GameObject has an Animator Component
        * \return true if the GameObject contains an Animator Component, false otherwise
        */
        bool doesHaveAnimator() const;
        /**
        * \brief Checks if the GameObject has a Collider Component
        * \return true if the GameObejct contains the Collider Component, false otherwise
        */
        bool doesHaveCollider() const;
        /**
        * \brief Checks if the GameObject has a LevelSprite Component
        * \return true if the GameObject contains the LevelSprite Component, false otherwise
        */
        bool doesHaveLevelSprite() const;
        /**
        * \brief Checks if the GameObject has a Script Component
        * \return true if the GameObject contains the Script Component, false otherwise
        */
        bool doesHaveScriptEngine() const;
        /**
        * \brief Is the GameObject updated
        * \return true if the GameObject is updated, false otherwise
        */
        bool getUpdateState() const;
        /**
        * \brief Sets if the GameObject should be otherwise or not
        * \param state Should be equal to true if the GameObject must updates, false otherwise
        */
        void setUpdateState(bool state);
        /**
        * \brief Gets the Animator Component of the GameObject (Raises ObEngine.Script.GameObject.NoAnimator if no Animator Component)
        * \return A pointer to the Animator Component of the GameObject
        */
        Animation::Animator* getAnimator();
        /**
        * \brief Gets the Collider Component of the GameObject (Raises ObEngine.Script.GameObject.NoCollider if no Collider Component)
        * \return A pointer to the Collider Component of the GameObject
        */
        Collision::PolygonalCollider* getCollider();
        /**
        * \brief Gets the LevelSprite Component of the GameObject (Raises ObEngine.Script.GameObject.NoLevelSprite if no LevelSprite Component)
        * \return A pointer to the LevelSprite Component of the GameObject
        */
        Graphics::LevelSprite* getLevelSprite();
        /**
        * \brief Gets the Scene Node of the GameObject (SceneNode that can manipulate the position of all Scene Components)
        * \return A reference to the GameObject's Scene Node
        */
        Scene::SceneNode* getSceneNode();
        /**
        * \brief Register a non-local Trigger for the GameObject
        * \param trNsp Namespace where the Trigger to register is
        * \param trGrp TriggerGroup where the Trigger to register is
        * \param trName Name of the Trigger to register
        * \param callAlias Alias (name of the callback) associated with the Trigger
        */
        void useTrigger(const std::string& trNsp, const std::string& trGrp, const std::string& trName, const std::string& callAlias = "");
        void removeTrigger(const std::string& trNsp, const std::string& trGrp, const std::string& trName) const;
        /**
        * \brief Execute a Lua String in the Lua State of the GameObject
        * \param query String to execute
        */
        void exec(const std::string& query) const;
        /**
        * \brief Send a parameter to the Local.Init trigger
        * \tparam U Template Type of the Parameter
        * \param argName Name of the Parameter to push
        * \param value Value of the Parameter
        */
        template <typename U>
        void sendInitArg(const std::string& argName, U value);
        /**
        * \brief Send a parameter to the Local.Init trigger from a Lua VM
        * \param argName Name of the Parameter to push
        * \param value Value of the Parameter
        */
        void sendInitArgFromLua(const std::string& argName, kaguya::LuaRef value) const;
        /**
        * \brief Register a Trigger in the GameObject
        * \param trg Pointer to the Trigger
        * \param callbackName Name of the callback to call when Trigger will be enabled
        */
        void registerTrigger(Triggers::Trigger* trg, const std::string& callbackName);
        /**
        * \brief Loads the GameObject through the GameObject Definition File
        * \param scene Scene reference to create components
        * \param obj Vili ComplexNode containing the GameObject components
        */
        void loadGameObject(Scene::Scene& scene, vili::ComplexNode& obj);
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
        kaguya::LuaTable access() const;
        /**
        * \brief Gets a reference to the Lua function used to build the GameObject (Local.Init proxy)
        * \return A reference to the Lua function used to build the GameObject
        */
        kaguya::LuaFunction getConstructor() const;
        /**
        * \brief Gets the id (index) of the GameObject Lua environement
        * \return An unsigned int representing the id (index) of the GameObject Lua environement
        */
        unsigned int getEnvIndex() const;
        /**
        * \brief Triggers the GameObject's Local.Init
        */
        void initialize();
        /**
        * \brief Configures the permanent parameter of the GameObject
        * \param permanent Should be true if the GameObject should be permanent, false otherwise
        */
        void setPermanent(bool permanent);
        /**
        * \brief Gets if the GameObject is permanent (Will stay after loading another map)
        * \return true if the GameObject is permanent, false otherwise
        */
        bool isPermanent() const;
    };

    template <typename U>
    void GameObject::sendInitArg(const std::string& argName, U value)
    {
        Debug::Log->debug("<GameObject> Sending Local.Init argument {0} to GameObject {1}", argName, m_id);
        m_localTriggers->pushParameter("Init", argName, value);
    }
}