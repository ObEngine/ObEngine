#include <utility>

#include <vili/parser.hpp>

#include <Scene/Scene.hpp>
#include <Script/GameObject.hpp>
#include <Script/ViliLuaBridge.hpp>
#include <System/Project.hpp>

namespace obe::Script
{
    static std::unordered_map<std::string, sol::bytecode> ScriptCache;

    sol::table GameObject::access() const
    {
        if (m_hasScriptEngine)
            return m_inner_storage;
        throw Exceptions::NoSuchComponent("Script", m_type, m_id, EXC_INFO);
    }

    sol::function GameObject::getConstructor() const
    {
        if (m_hasScriptEngine)
            return m_outer_environment["ObjectInitFromLua"].get<sol::function>();
        throw Exceptions::NoSuchComponent("Script", m_type, m_id, EXC_INFO);
    }

    vili::node GameObjectDatabase::allDefinitions = vili::object {};
    vili::node GameObjectDatabase::allRequires = vili::object {};
    vili::node GameObjectDatabase::GetRequirementsForGameObject(const std::string& type)
    {
        if (!allRequires.contains(type))
        {
            vili::node getGameObjectFile = vili::parser::from_file(
                System::Path("Data/GameObjects/").add(type).add(type + ".obj.vili").find());
            if (getGameObjectFile.contains("Requires"))
            {
                vili::node& requiresData = getGameObjectFile.at("Requires");
                allRequires[type] = requiresData;
                return requiresData;
            }
            return vili::node {};
        }
        return allRequires.at(type);
    }

    vili::node GameObjectDatabase::GetDefinitionForGameObject(const std::string& type)
    {
        if (!allDefinitions.contains(type))
        {
            const std::string objectDefinitionPath
                = System::Path(System::Project::Prefixes::objects, type)
                      .add(type + ".obj.vili")
                      .find();
            if (objectDefinitionPath.empty())
                throw Exceptions::ObjectDefinitionNotFound(type, EXC_INFO);

            vili::node definitionData = vili::parser::from_file(
                objectDefinitionPath);

            allDefinitions[type] = definitionData;
            return definitionData;
        }
        return allDefinitions.at(type);
    }

    void GameObjectDatabase::ApplyRequirements(
        sol::environment environment, const vili::node& requirements)
    {
        environment["__INIT_ARG_TABLE"] = ViliLuaBridge::viliToLua(requirements);
    }

    void GameObjectDatabase::Clear()
    {
        allDefinitions.clear();
        allRequires.clear();
    }

    // GameObject
    GameObject::GameObject(sol::state_view lua, const std::string& type, const std::string& id)
        : Identifiable(id)
        , m_lua(std::move(lua))
        , GameObjectPath(System::Path(System::Project::Prefixes::objects, type)
                             .find(System::PathType::Directory))
    {
        m_type = type;
    }

    void GameObject::initialize()
    {
        if (!m_initialized)
        {
            Debug::Log->debug("<GameObject> Initializing GameObject '{0}' ({1})", m_id, m_type);
            m_initialized = true;
            if (m_hasScriptEngine)
            {
                m_outer_environment["__OBJECT_INIT"] = true;
                try
                {
                    safeLuaCall(m_outer_environment["ObjectInit"].get<sol::protected_function>());
                }
                catch (const BaseException& e)
                {
                    throw Exceptions::GameObjectScriptError(m_type, m_id, "ObjectInit", EXC_INFO)
                        .nest(e);
                }
            }
            m_active = true;
        }
        else
        {
            Debug::Log->warn("<GameObject> GameObject '{0}' ({1}) has already "
                             "been initialized",
                m_id, m_type);
        }
    }

    GameObject::~GameObject()
    {
        Debug::Log->debug("<GameObject> Deleting GameObject '{0}' ({1})", m_id, m_type);
        if (m_hasScriptEngine)
        {
            m_outer_environment = sol::lua_nil;
            m_inner_environment = sol::lua_nil;
        }
    }

    void GameObject::sendInitArgFromLua(const std::string& argName, sol::object value)
    {
        Debug::Log->debug("<GameObject> Sending Local.Init argument {0} to "
                          "GameObject {1} ({2}) (From Lua)",
            argName, m_id, m_type);
        m_outer_environment["__INIT_ARG_TABLE"][argName] = value;
    }

    void GameObject::loadGameObject(
        Scene::Scene& scene, vili::node& obj, Engine::ResourceManager* resources)
    {
        Debug::Log->debug("<GameObject> Loading GameObject '{0}' ({1})", m_id, m_type);

        if (obj.contains("permanent"))
        {
            m_permanent = obj.at("permanent");
        }
        // Script
        if (obj.contains("Script"))
        {
            vili::node& script = obj.at("Script");
            m_hasScriptEngine = true;
            m_outer_environment = sol::environment(m_lua, sol::create, m_lua.globals());
            m_inner_storage = m_lua.create_table();
            m_inner_environment = sol::environment(
                m_lua, sol::create, m_outer_environment);
            sol::table inner_environment_mt = m_inner_environment[sol::metatable_key];
            inner_environment_mt["__index"] = m_lua["Helpers"]["fetch_from_one_of"](
                m_inner_storage.as<sol::table>(), m_outer_environment.as<sol::table>());
            inner_environment_mt["__newindex"] = m_inner_storage;
            inner_environment_mt["__len"] = m_lua["Helpers"]["len_from"](m_inner_storage);
            inner_environment_mt["__pairs"] = m_lua["Helpers"]["pairs_from"](m_inner_storage);

            m_outer_environment["This"] = this;

            m_outer_environment["__OBJECT_TYPE"] = m_type;
            m_outer_environment["__OBJECT_ID"] = m_id;
            m_outer_environment["__OBJECT_INIT"] = false;

            loadSource("obe://Lib/Internal/ObjectInit.lua", EnvironmentTarget::Outer);

            if (script.contains("source"))
            {
                const vili::node& sourceNode = script.at("source");
                if (sourceNode.is<vili::string>())
                {
                    loadSource(sourceNode, EnvironmentTarget::Inner);
                }
                else
                {
                    throw Exceptions::WrongSourceAttributeType(m_type, "source",
                        vili::string_typename, vili::to_string(sourceNode.type()), EXC_INFO);
                }
            }
            else if (script.contains("sources"))
            {
                vili::node& sourceNode = script.at("sources");
                if (sourceNode.is<vili::array>())
                {
                    for (const vili::node& source : sourceNode)
                    {
                        loadSource(source, EnvironmentTarget::Inner);
                    }
                }
                else
                {
                    throw Exceptions::WrongSourceAttributeType(m_type, "sources",
                        vili::array_typename, vili::to_string(sourceNode.type()), EXC_INFO);
                }
            }
        }
        if (m_hasScriptEngine)
        {
            m_outer_environment["Components"]["SceneNode"] = &m_objectNode;
        }
        // Sprite
        if (obj.contains("Sprite"))
        {
            m_sprite = &scene.createSprite(m_id, false);
            m_objectNode.addChild(*m_sprite);
            m_sprite->load(obj.at("Sprite"));
            m_sprite->setParentId(m_id);
            if (m_hasScriptEngine)
                m_outer_environment["Components"]["Sprite"] = m_sprite;
            scene.reorganizeLayers();
        }
        if (obj.contains("Animator"))
        {
            m_animator = std::make_unique<Animation::Animator>();
            vili::node& animator = obj.at("Animator");
            std::string animatorPath;
            if (animator.contains("path"))
            {
                animatorPath = animator.at("path");
            }

            Animation::AnimatorTargetScaleMode scaleMode = Animation::AnimatorTargetScaleMode::Fit;
            if (animator.contains("scaling"))
            {
                scaleMode = Animation::AnimatorTargetScaleModeMeta::fromString(animator.at("scaling"));
            }
            if (m_sprite)
                m_animator->setTarget(*m_sprite, scaleMode);
            if (!animatorPath.empty())
            {
                m_animator->load(GameObjectPath(animatorPath), resources);
            }
            if (animator.contains("default"))
            {
                m_animator->setKey(animator.at("default"));
            }
            if (m_hasScriptEngine)
                m_outer_environment["Components"]["Animation"] = m_animator.get();
        }
        // Collider
        if (obj.contains("Collider"))
        {
            m_collider = &scene.createCollider(m_id, false);
            m_objectNode.addChild(*m_collider);
            m_collider->load(obj.at("Collider"));
            m_collider->setParentId(m_id);

            if (m_hasScriptEngine)
                m_outer_environment["Components"]["Collider"] = m_collider;
        }
    }

    void GameObject::update()
    {
        if (m_canUpdate)
        {
            if (m_active)
            {
                if (m_animator)
                {
                    if (!m_animator->getKey().empty())
                        m_animator->update();
                    /*if (m_sprite)
                    {
                        m_sprite->setTexture(m_animator->getTexture());
                    }*/
                }
            }
            else
            {
                this->initialize();
            }
        }
    }

    std::string GameObject::getType() const
    {
        return m_type;
    }

    bool GameObject::doesHaveAnimator() const
    {
        return static_cast<bool>(m_animator);
    }

    bool GameObject::doesHaveCollider() const
    {
        return static_cast<bool>(m_collider);
    }

    bool GameObject::doesHaveSprite() const
    {
        return static_cast<bool>(m_sprite);
    }

    bool GameObject::doesHaveScriptEngine() const
    {
        return m_hasScriptEngine;
    }

    bool GameObject::getUpdateState() const
    {
        return m_canUpdate;
    }

    void GameObject::setUpdateState(bool state)
    {
        m_canUpdate = state;
    }

    Graphics::Sprite& GameObject::getSprite() const
    {
        if (m_sprite)
            return *m_sprite;
        throw Exceptions::NoSuchComponent("Sprite", m_type, m_id, EXC_INFO);
    }

    Scene::SceneNode& GameObject::getSceneNode()
    {
        return m_objectNode;
    }

    Collision::PolygonalCollider& GameObject::getCollider() const
    {
        if (m_collider)
            return *m_collider;
        throw Exceptions::NoSuchComponent("Collider", m_type, m_id, EXC_INFO);
    }

    Animation::Animator& GameObject::getAnimator() const
    {
        if (m_animator)
            return *m_animator.get();
        throw Exceptions::NoSuchComponent("Animator", m_type, m_id, EXC_INFO);
    }

    void GameObject::exec(const std::string& query)
    {
        m_lua.safe_script(query, m_outer_environment);
    }

    void GameObject::initFromVili(const vili::node& data)
    {
        Debug::Log->debug("<GameObject> Sending Local.Init table to "
                          "GameObject {1} ({2}) (From Vili)",
            m_id, m_type);
        m_outer_environment["__INIT_ARG_TABLE"] = ViliLuaBridge::viliToLua(data);
    }

    void GameObject::deleteObject()
    {
        if (!this->deletable)
        {
            Debug::Log->debug("GameObject::deleteObject called for '{0}' ({1})", m_id, m_type);

            if (m_hasScriptEngine)
            {
                try
                {
                    safeLuaCall(m_outer_environment["ObjectDelete"].get<sol::protected_function>());
                }
                catch (const BaseException& e)
                {
                    throw Exceptions::GameObjectScriptError(m_type, m_id, "ObjectDelete", EXC_INFO)
                        .nest(e);
                }
            }

            this->deletable = true;
            m_active = false;
            if (m_hasScriptEngine)
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

    void GameObject::setPermanent(bool permanent)
    {
        m_permanent = permanent;
    }

    bool GameObject::isPermanent() const
    {
        return m_permanent;
    }

    sol::environment GameObject::getOuterEnvironment() const
    {
        return m_inner_environment;
    }

    void GameObject::setState(bool state)
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
        result["type"] = this->getType();

        if (auto dumpFunction = this->access()["Dump"]; dumpFunction.valid())
        {
            const sol::table saveTableRef = dumpFunction().get<sol::table>();
            vili::node saveRequirements = Script::ViliLuaBridge::luaTableToViliObject(saveTableRef);
            result["Requires"] = saveRequirements;
        }

        return result;
    }

    void GameObject::load(const vili::node& data)
    {
        // TODO: Do something
    }

    void GameObject::loadSource(const std::string& path, EnvironmentTarget env)
    {
        const sol::environment& environment
            = (env == EnvironmentTarget::Outer) ? m_outer_environment : m_inner_environment;
        const std::string fullPath = GameObjectPath(path).find();
        if (fullPath.empty())
        {
            throw Exceptions::ScriptFileNotFound(m_type, m_id, path, EXC_INFO);
        }
        if (!ScriptCache.contains(fullPath))
        {
            const sol::load_result target = m_lua.load_file(fullPath);
            if (!target.valid())
            {
                throw Exceptions::InvalidScript(
                    fullPath, target.get<sol::error>().what(), EXC_INFO);
            }
            const sol::protected_function bytecode = target.get<sol::protected_function>();
            ScriptCache.emplace(fullPath, bytecode.dump());
        }
        const std::string_view source = ScriptCache.at(fullPath).as_string_view();
        if (const sol::protected_function_result loadResult = m_lua.safe_script(source, environment); !loadResult.valid())
        {
            throw Exceptions::InvalidScript(
                fullPath, loadResult.get<sol::error>().what(), EXC_INFO);
        }
    }
} // namespace obe::Script
