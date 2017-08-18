#pragma once

#include <kaguya/kaguya.hpp>
#include <vili/Vili.hpp>

#include <Animation/Animator.hpp>
#include <Collision/PolygonalCollider.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Triggers/TriggerGroup.hpp>

namespace obe
{
    namespace Scene
    {
        class Scene;
    }

    namespace Script
    {
        class GameObject;

        class GameObjectRequires
        {
        private:
            static GameObjectRequires* instance;
            vili::ViliParser allRequires;
        public:
            static GameObjectRequires* getInstance();
            vili::ComplexNode* getRequiresForObjectType(const std::string& type) const;
            void applyBaseRequires(GameObject* obj, vili::ComplexNode& requires);
            static void ApplyRequirements(GameObject* obj, vili::ComplexNode& requires);
        };

        /**
         * \brief A GameObject is a set of Components used in the Scene
         */
        class GameObject : public Types::Identifiable
        {
        private:
            std::unique_ptr<Animation::Animator> m_objectAnimator;
            std::unique_ptr<kaguya::State> m_objectScript;
            Graphics::LevelSprite* m_objectLevelSprite;
            Collision::PolygonalCollider* m_objectCollider;
            Triggers::TriggerGroupPtr m_localTriggers;

            std::vector<std::pair<Triggers::Trigger*, std::string>> m_registeredTriggers;
            std::vector<std::tuple<std::string, std::string, std::string>> m_registeredAliases;

            std::string m_id;
            std::string m_type;
            std::string m_privateKey;
            std::string m_publicKey;
            int m_scrPriority = 0;

            bool m_hasAnimator = false;
            bool m_hasCollider = false;
            bool m_hasLevelSprite = false;
            bool m_hasScriptEngine = false;
            bool m_initialised = false;
            bool m_canUpdate = true;

            friend class Scene::Scene;
        public:
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
             * \brief Get the public key of the GameObject
             * \return A std::string containing the public key of the GameObject
             */
            std::string getPublicKey() const;
            /**
             * \brief Get the script execution priority of the GameObject
             * \return An int containing the script execution priority of the GameObject
             */
            int getPriority() const;
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
            * \brief Gets the Script Component of the GameObject (Raises ObEngine.Script.GameObject.NoScript if no Script Component)
            * \return A pointer to the Script Component of the GameObject
            */
            kaguya::State* getScript();

            /**
             * \brief Gets the TriggerGroup managing Local Triggers of the GameObject
             * \return A pointer to the TriggerGroup of the GameObject
             */
            Triggers::TriggerGroup* getLocalTriggers() const;
            /**
             * \brief Enables the use of a LocalTrigger (Internal Use Only)
             * \param trName Name of the Local Trigger to enable (Init, Update, etc..)
             */
            void useLocalTrigger(const std::string& trName);
            /**
             * \brief Register a non-local Trigger for the GameObject
             * \param trNsp Namespace where the Trigger to register is
             * \param trGrp TriggerGroup where the Trigger to register is
             * \param trName Name of the Trigger to register
             * \param callAlias Alias (name of the callback) associated with the Trigger
             */
            void useExternalTrigger(const std::string& trNsp, const std::string& trGrp, const std::string& trName, const std::string& callAlias = "");
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
        };

        void loadScrGameObject(GameObject* obj, kaguya::State* lua);
        void loadScrGameObjectLib(kaguya::State* lua);
        bool orderScrPriority(GameObject* g1, GameObject* g2);
        void loadLibBridge(GameObject* object, std::string lib);
        void loadHookBridge(GameObject* object, std::string hookname);

        template <typename U>
        void GameObject::sendInitArg(const std::string& argName, U value)
        {
            m_localTriggers->pushParameter("Init", argName, value);
        }
    };
};
