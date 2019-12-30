#pragma once

#include <optional>

#include <Collision/PolygonalCollider.hpp>
#include <Component/Component.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Scene/Camera.hpp>
#include <Scene/SceneNode.hpp>
#include <Script/GameObject.hpp>
#include <Types/Registrable.hpp>
#include <Types/Serializable.hpp>
#include <Utils/TypeUtils.hpp>

namespace obe::Scene
{
#define LUAENV Script::ScriptEngine["__ENVIRONMENTS"][m_envIndex]

    class Capsule
    {
    public:
        template <class T> T& get(const std::string& id);
    };

    enum class ExecuteType
    {
        FilePath,
        Source
    };

    class LuaComponent : public Types::Serializable
    {
    private:
        unsigned int m_envIndex;
        Triggers::TriggerGroupPtr m_localTriggers;
        std::vector<std::tuple<ExecuteType, std::string>> m_sources;

        std::vector<std::pair<Triggers::Trigger*, std::string>>
            m_registeredTriggers;
        std::vector<std::tuple<std::string, std::string, std::string>>
            m_registeredAliases;
        std::string m_triggerNamespace;

    public:
        static std::vector<unsigned int> AllEnvs;
        explicit LuaComponent();
        /**
         * \brief Access the exposition table of the GameObject
         * \return A reference to the exposition table of the GameObject
         */
        kaguya::LuaTable access() const;
        /**
         * \brief Gets a reference to the Lua function used to build the
         * GameObject (Local.Init proxy) \return A reference to the Lua function
         * used to build the GameObject
         */
        kaguya::LuaFunction getConstructor() const;
        /**
         * \brief Gets the id (index) of the GameObject Lua environement
         * \return An unsigned int representing the id (index) of the GameObject
         * Lua environement
         */
        unsigned int getEnvIndex() const;
        /**
         * \brief Triggers the GameObject's Local.Init
         */
        void initialize();

        void execute(ExecuteType type, const std::string& source) const;
        void addSource(ExecuteType type, const std::string& path);

        void dump(vili::ComplexNode& target) const override;
        void load(vili::ComplexNode& data) override;
    };

    class TXScene : public Types::Serializable, public Types::Identifiable
    {
    private:
        bool m_permanent = false;
        std::vector<Component::ComponentBase*> m_components;
        std::vector<std::unique_ptr<TXScene>> m_children;
        std::unique_ptr<LuaComponent> m_script;
        std::string m_name;

    public:
        static TXScene CreateRootScene();
        explicit TXScene(const std::string& id, bool scriptable = false);
        TXScene(TXScene&& scene);

        ~TXScene();

        /**
         * \brief Configures the permanent parameter of the GameObject
         * \param permanent Should be true if the GameObject should be
         * permanent, false otherwise
         */
        void setPermanent(bool permanent);
        /**
         * \brief Gets if the GameObject is permanent (Will stay after loading
         * another map) \return true if the GameObject is permanent, false
         * otherwise
         */
        bool isPermanent() const;
        /**
         * \brief Deletes the GameObject
         */
        void remove();

        template <class T> T& add(const std::string& id);

        Component::ComponentBase& get(const std::string& id);
        template <class T> T& get(const std::string& id);

        template <class T> std::vector<T&> getAll();

        /**
         * \brief Removes all elements in the Scene
         */
        void clear();

        void dump(vili::ComplexNode& target) const override;
        void load(vili::ComplexNode& data) override;

        void setName(const std::string& name);
        std::string getName() const;

        /**
         * \brief Delete State of the GameObject (false = not deleted)
         */
        bool deletable = false;
    };

    template <class T> T& TXScene::add(const std::string& id)
    {
        static_assert(std::is_base_of<Component::ComponentBase, T>::value,
            "Scene.add<T>(id) requires T to have Component as base class");

        /*T* reference =
        static_cast<T*>(m_components.emplace_back(&T::create(id))); if
        (m_script)
        {
            reference->inject(m_script->getEnvIndex());
        }*/
        T* reference = nullptr;

        return *reference;
    }
    template <class T> inline T& TXScene::get(const std::string& id)
    {
        static_assert(std::is_base_of<Component::ComponentBase, T>::value,
            "Scene.get<T>(id) requires T to have Component as base class");
        if (T* castedComponent = dynamic_cast<T*>(this->get(id));
            castedComponent != nullptr)
        {
            return *castedComponent;
        }
        else
        {
            throw aube::ErrorHandler::Raise(
                "obe.Scene.Scene.WrongComponentType",
                { { "type", this->get(id).type() },
                    { "expected", T::ComponentType } });
        }
    }

    template <class T> std::vector<T&> TXScene::getAll()
    {
        static_assert(std::is_base_of<Component::ComponentBase, T>::value,
            "Scene.getAll<T>() requires T to have Component as base class");
        std::vector<T&> componentsOfTypeT;
        for (Component::ComponentBase* component : m_components)
        {
            if (T* castedComponent = dynamic_cast<T*>(component);
                castedComponent != nullptr)
            {
                componentsOfTypeT.push_back(*castedComponent);
            }
        }

        return componentsOfTypeT;
    }
} // namespace obe::Scene
