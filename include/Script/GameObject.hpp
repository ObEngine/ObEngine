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
            vili::ComplexNode* getRequiresForObjectType(std::string type) const;
            void applyBaseRequires(GameObject* obj, vili::ComplexNode& requires);
            static void ApplyRequirements(GameObject* obj, vili::ComplexNode& requires);
        };

        class GameObject : public Types::Identifiable
        {
        private:
            std::unique_ptr<Animation::Animator> m_objectAnimator;
            std::unique_ptr<kaguya::State> m_objectScript;
            Graphics::LevelSprite* m_objectLevelSprite;
            Collision::PolygonalCollider* m_objectCollider;
            Triggers::TriggerGroupPtr m_localTriggers;

            std::vector<Triggers::Trigger*> m_registeredTriggers;
            std::vector<std::tuple<std::string, std::string, std::string>> m_registeredAliases;

            std::string m_id;
            std::string m_type;
            std::string m_privateKey;
            std::string m_publicKey;
            int m_scrPriority = 0;

            bool m_hasAnimator = false;
            bool m_hasCollider = false;
            bool m_colliderSolid = false;
            bool m_colliderClick = false;
            bool m_levelSpriteRelative = true;
            bool m_hasLevelSprite = false;
            bool m_hasScriptEngine = false;
            bool m_initialised = false;
            bool m_updated = true;

            //int m_queryCounter = 0;

            friend class Scene::Scene;
        public:
            explicit GameObject(const std::string& type, const std::string& id);
            ~GameObject();

            std::string getType() const;
            std::string getPublicKey() const;
            int getPriority() const;
            bool canDisplay() const;
            bool canCollide() const;
            bool canClick() const;
            bool doesHaveAnimator() const;
            bool doesHaveCollider() const;
            bool doesHaveLevelSprite() const;
            bool doesHaveScriptEngine() const;
            bool isLevelSpriteRelative() const;
            bool getUpdateState() const;
            void setUpdateState(bool state);

            Animation::Animator* getAnimator();
            Collision::PolygonalCollider* getCollider();
            Graphics::LevelSprite* getLevelSprite();
            kaguya::State* getScript();

            Triggers::TriggerGroup* getLocalTriggers() const;
            void useLocalTrigger(const std::string& trName);
            void useExternalTrigger(const std::string& trNsp, const std::string& trGrp, const std::string& trName, const std::string& useAs = "");
            void setInitialised(bool init);
            bool getInitialised() const;
            void exec(std::string query) const;
            template <typename U>
            void sendQuery(U query);
            template <typename U>
            void sendRequireArgumentFromCPP(const std::string& argName, U value);
            void sendRequireArgumentFromLua(const std::string& argName, kaguya::LuaRef value) const;

            void registerTrigger(Triggers::Trigger* trg);
            void loadGameObject(Scene::Scene& world, vili::ComplexNode& obj);
            void update(double dt);

            void deleteObject();
            bool deletable = false;
        };

        void loadScrGameObject(GameObject* obj, kaguya::State* lua);
        void loadScrGameObjectLib(kaguya::State* lua);
        bool orderScrPriority(GameObject* g1, GameObject* g2);
        void loadLibBridge(GameObject* object, std::string lib);
        void loadHookBridge(GameObject* object, std::string hookname);

        template <typename U>
        void GameObject::sendRequireArgumentFromCPP(const std::string& argName, U value)
        {
            (*m_objectScript.get())["LuaCore"]["Lua_ReqList"][argName] = value;
        }

        template <typename U>
        void GameObject::sendQuery(U query)
        {
            if (Utils::Vector::isInList(m_localTriggers->getTrigger("Query"), m_registeredTriggers))
            {
                m_localTriggers->pushParameter("Query", std::to_string(0), query);
                m_localTriggers->trigger("Query");
                //m_queryCounter++;
            }
        }
    };
};
