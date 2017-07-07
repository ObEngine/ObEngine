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
        class World;
    }

    namespace Script
    {
        class GameObject;

        class GameObjectRequires
        {
        private:
            static GameObjectRequires* instance;
            vili::DataParser allRequires;
        public:
            static GameObjectRequires* getInstance();
            vili::ComplexAttribute* getRequiresForObjectType(std::string type) const;
            void applyBaseRequires(GameObject* obj, vili::ComplexAttribute& requires);
            static void ApplyRequirements(GameObject* obj, vili::ComplexAttribute& requires);
        };

        class GameObject
        {
        private:
            std::unique_ptr<Animation::Animator> m_objectAnimator;
            std::unique_ptr<kaguya::State> m_objectScript;
            Graphics::LevelSprite* m_objectLevelSprite = nullptr;
            Collision::PolygonalCollider* m_objectCollider = nullptr;
            Triggers::TriggerGroup::Ptr m_localTriggers;

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

            int m_queryCounter = 0;

            friend class Scene::World;
        public:
            GameObject(std::string type, std::string id);
            ~GameObject();

            std::string getID() const;
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
            void useLocalTrigger(std::string trName);
            void useExternalTrigger(std::string trNsp, std::string trGrp, std::string trName, std::string useAs = "");
            void setInitialised(bool init);
            bool getInitialised() const;
            void exec(std::string query) const;
            template <typename U>
            void sendQuery(U query);
            template <typename U>
            void sendRequireArgumentFromCPP(std::string argName, U value);
            void sendRequireArgumentFromLua(std::string argName, kaguya::LuaRef value) const;

            void registerTrigger(Triggers::Trigger* trg);
            void loadGameObject(Scene::World& world, vili::ComplexAttribute& obj);
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
        void GameObject::sendRequireArgumentFromCPP(std::string argName, U value)
        {
            (*m_objectScript.get())["LuaCore"]["Lua_ReqList"][argName] = value;
        }

        template <typename U>
        void GameObject::sendQuery(U query)
        {
            if (Utils::Vector::isInList(m_localTriggers->getTrigger("Query"), m_registeredTriggers))
            {
                m_localTriggers->pushParameter("Query", std::to_string(m_queryCounter), query);
                m_localTriggers->setTriggerState("Query", true);
                m_queryCounter++;
            }
        }
    };
};
