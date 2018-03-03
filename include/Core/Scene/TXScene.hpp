#pragma once

#include <optional>

#include <Collision/PolygonalCollider.hpp>
#include <Component/Component.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Scene/Camera.hpp>
#include <Script/GameObject.hpp>
#include <Transform/SceneNode.hpp>
#include <Types/Registrable.hpp>
#include <Types/Serializable.hpp>

namespace obe
{
    namespace Scene
    {
        #define LUAENV Script::ScriptEngine["__ENVIRONMENTS"][m_envIndex]

        class Capsule
        {
        public:
            template <class T>
            T& get(const std::string& id);
        };

        class LuaComponent
        {
        private:
            unsigned int m_envIndex;
            Triggers::TriggerGroupPtr m_localTriggers;

            std::vector<std::pair<Triggers::Trigger*, std::string>> m_registeredTriggers;
            std::vector<std::tuple<std::string, std::string, std::string>> m_registeredAliases;
            std::string m_triggerNamespace;
        public:
            static std::vector<unsigned int> AllEnvs;
            LuaComponent();
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

            void execute(const std::string& code);
        };

        class TXScene : public Types::Serializable, public Types::Identifiable
        {
        private:
            bool m_permanent = false;
            std::string m_sceneName;
            uint32_t m_entityId;
            std::vector<Component::ComponentBase*> m_components;
            std::optional<std::unique_ptr<LuaComponent>> m_script;
        public:
            explicit TXScene(const std::string& name, const std::string& id, bool scriptable);

            ~TXScene();

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
            /**
            * \brief Deletes the GameObject
            */
            void deleteObject();
            /**
            * \brief Delete State of the GameObject (false = not deleted)
            */
            bool deletable = false;
        };
    }
}