#include <vili/Vili.hpp>

#include <Scene/TXScene.hpp>
#include <Script/GlobalState.hpp>
#include <System/Loaders.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/StringUtils.hpp>

#define LUA_COMPONENT_ENV Script::ScriptEngine["__ENVIRONMENTS"][m_envIndex]

namespace obe::Scene
{
    TXScene TXScene::CreateRootScene()
    {
        Triggers::TriggerDatabase::GetInstance().createNamespace("Map");

        return TXScene("Root");
    }

    TXScene::TXScene(const std::string& id, bool scriptable)
        : Types::Identifiable(id)
    {
        if (scriptable)
        {
            m_script = std::make_unique<LuaComponent>();
        }
        Script::ScriptEngine["Scenes"][id] = this;
    }

    TXScene::TXScene(TXScene&& scene)
        : Identifiable(scene.getId())
    {
        m_permanent = scene.m_permanent;
        m_components = std::move(scene.m_components);
        m_children = std::move(scene.m_children);
        m_script.reset(scene.m_script.release());
        m_name = std::move(scene.m_name);
    }

    TXScene::~TXScene()
    {
    }

    void TXScene::setPermanent(bool permanent)
    {
        m_permanent = permanent;
    }

    bool TXScene::isPermanent() const
    {
        return m_permanent;
    }

    void TXScene::remove()
    {
    }

    Component::ComponentBase& TXScene::get(const std::string& id)
    {
        for (Component::ComponentBase* component : m_components)
        {
            if (component->getId() == id)
            {
                return *component;
            }
        }

        throw aube::ErrorHandler::Raise(
            "obe.Scene.Scene.ComponentNotFound", { { "sceneId", m_id }, { "componentId", id } });
    }

    void TXScene::clear()
    {
        for (auto& component : m_components)
        {
            component->remove();
        }
        m_components.clear();
    }

    void TXScene::dump(vili::ComplexNode& target) const
    {
    }

    void TXScene::load(vili::ComplexNode& data)
    {
        Debug::Log->debug("<Scene> Loading Scene");
        this->clear();
        Debug::Log->debug("<Scene> Cleared Scene");

        if (data.contains(vili::NodeType::DataNode, "name"))
        {
            m_name = data.getDataNode("name").get<std::string>();
        }
        else
            throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.NoName", { { "id", m_id } });

        /*if (data.contains(vili::NodeType::ComplexNode, "View"))
        {
            vili::ComplexNode& view = m_levelFile.at("View");
            m_camera.setSize(view.at<vili::DataNode>("size").get<double>());
            m_cameraInitialPosition = Transform::UnitVector(
                view.at<vili::DataNode>("pos", "x").get<double>(),
                view.at<vili::DataNode>("pos", "y").get<double>(),
                Transform::stringToUnits(view.at<vili::DataNode>("pos",
        "unit").get<std::string>())); m_cameraInitialReferential =
        Transform::Referential::TopLeft; if
        (m_levelFile->at("View").contains(vili::NodeType::ComplexNode,
        "referential"))
            {
                m_cameraInitialReferential = Transform::stringToReferential(
                    m_levelFile->at("View",
        "referential").getDataNode("referential").get<std::string>()
                );
            }
            Debug::Log->debug("<Scene> Set Camera Position at : {0}, {1} using
        Referential {2}", m_cameraInitialPosition.x, m_cameraInitialPosition.y,
                Transform::referentialToString(m_cameraInitialReferential));
            m_camera.setPosition(m_cameraInitialPosition,
        m_cameraInitialReferential); std::cout << m_camera.getPosition() <<
        std::endl;
        }
        else
            throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.NoView", { {
        "map", filename } });*/

        if (data.contains(vili::NodeType::ComplexNode, "Components"))
        {
            vili::ComplexNode& components = data.at("Components");

            for (vili::ComplexNode* component : components.getAll<vili::ComplexNode>())
            {
                const std::string componentType = component->getDataNode("type");
                if (componentType == "Sprite")
                {
                    this->add<Graphics::LevelSprite>(component->getDataNode("id")).load(*component);
                }
                else if (componentType == "Collider")
                {
                    this->add<Collision::PolygonalCollider>(component->getDataNode("id"))
                        .load(*component);
                }
                else if (componentType == "Script")
                {
                    m_script = std::make_unique<LuaComponent>();
                    m_script->load(*component);
                }
            }
        }

        /*if (m_levelFile->contains(vili::NodeType::ComplexNode, "GameObjects"))
        {
            vili::ComplexNode& gameObjects = m_levelFile.at("GameObjects");
            for (vili::ComplexNode* currentObject :
        gameObjects.getAll<vili::ComplexNode>())
            {
                if (!this->doesGameObjectExists(currentObject->getId()))
                {
                    const std::string gameObjectType =
        currentObject->getDataNode("type").get<std::string>();
                    Script::GameObject* newObject =
        this->createGameObject(gameObjectType, currentObject->getId()); if
        (currentObject->contains(vili::NodeType::ComplexNode, "Requires"))
                    {
                        vili::ComplexNode& objectRequirements =
        currentObject->at("Requires");
                        currentObject->removeOwnership(&objectRequirements);
                        Script::GameObjectDatabase::ApplyRequirements(newObject,
        objectRequirements); objectRequirements.setParent(currentObject);
                    }
                    newObject->exec("LuaCore.InjectInitInjectionTable()");
                }
                else if
        (!this->getGameObject(currentObject->getId())->isPermanent())
                {
                    aube::ErrorHandler::Warn("ObEngine.Scene.Scene.GameObjectAlreadyInScene",
        { { "object", currentObject->getId() },{ "mapfile", m_levelName } });
                }
            }
        }

        if (m_levelFile->contains(vili::NodeType::ComplexNode, "Script"))
        {
            vili::ComplexNode& script = m_levelFile.at("Script");
            if (script.contains(vili::NodeType::DataNode, "source"))
            {
                System::Path(script.at<vili::DataNode>("source")).loadResource(&Script::ScriptEngine,
        System::Loaders::luaLoader);
                m_scriptArray.push_back(script.at<vili::DataNode>("source"));
            }
            else if (script.contains(vili::NodeType::ArrayNode, "sources"))
            {
                for (vili::DataNode* scriptName :
        script.getArrayNode("sources"))
                {
                    System::Path(*scriptName).loadResource(&Script::ScriptEngine,
        System::Loaders::luaLoader); m_scriptArray.push_back(*scriptName);
                }
            }
        }
        m_sceneTriggers->pushParameter("MapLoaded", "name", filename);
        m_sceneTriggers->trigger("MapLoaded");*/
    }

    void TXScene::setName(const std::string& name)
    {
        m_name = name;
    }

    std::string TXScene::getName() const
    {
        return m_name;
    }

    std::vector<unsigned int> LuaComponent::AllEnvs;
    LuaComponent::LuaComponent()
    {
        m_triggerNamespace
            = Utils::String::getRandomKey(Utils::String::Alphabet + Utils::String::Numbers, 12);
        Triggers::TriggerDatabase::GetInstance().createNamespace(m_triggerNamespace);
        m_localTriggers.reset(Triggers::TriggerDatabase::GetInstance().createTriggerGroup(
                                  m_triggerNamespace, "Local"),
            Triggers::TriggerGroupPtrRemover);

        m_envIndex = Script::CreateNewEnvironment();
        AllEnvs.push_back(m_envIndex);
        // std::cout << "Environment Index is : " << m_envIndex << std::endl;

        // executeFile(m_envIndex,
        // System::Path("Lib/Internal/ScriptInit.lua").find());
        // loadScrGameObject(this, m_objectScript.get());

        LUAENV["This"] = this;

        m_localTriggers->addTrigger("Init")->addTrigger("Delete");

        // LUAENV["__OBJECT_TYPE"] = m_type;
        // LUAENV["__OBJECT_ID"] = m_id;
        LUAENV["__OBJECT_INIT"] = false;
        LUAENV["Private"] = m_triggerNamespace;

        Script::executeFile(m_envIndex, System::Path("Lib/Internal/ObjectInit.lua").find());
    }

    kaguya::LuaTable LuaComponent::access() const
    {
        return LUA_COMPONENT_ENV["Object"];
    }

    kaguya::LuaFunction LuaComponent::getConstructor() const
    {
        return LUA_COMPONENT_ENV["ObjectInit"];
    }

    unsigned LuaComponent::getEnvIndex() const
    {
        return m_envIndex;
    }

    void LuaComponent::execute(ExecuteType type, const std::string& source) const
    {
        if (type == ExecuteType::FilePath)
            Script::executeFile(m_envIndex, System::Path(source).find());
        else if (type == ExecuteType::Source)
            Script::executeString(m_envIndex, source);
    }

    void LuaComponent::addSource(ExecuteType type, const std::string& path)
    {
        m_sources.push_back(std::make_tuple(type, path));
    }

    void LuaComponent::dump(vili::ComplexNode& target) const
    {
    }

    void LuaComponent::load(vili::ComplexNode& data)
    {
        if (data.contains(vili::NodeType::DataNode, "source"))
        {
            this->execute(ExecuteType::FilePath, data.at<vili::DataNode>("source"));
            this->addSource(ExecuteType::FilePath, data.at<vili::DataNode>("source"));
        }
        else if (data.contains(vili::NodeType::ArrayNode, "sources"))
        {
            for (vili::DataNode* scriptName : data.getArrayNode("sources"))
            {
                this->execute(ExecuteType::FilePath, *scriptName);
                this->addSource(ExecuteType::FilePath, *scriptName);
            }
        }
        if (data.contains(vili::NodeType::DataNode, "string"))
        {
            this->execute(ExecuteType::Source, data.at<vili::DataNode>("string"));
            this->addSource(ExecuteType::Source, data.at<vili::DataNode>("string"));
        }
        else if (data.contains(vili::NodeType::ArrayNode, "strings"))
        {
            for (vili::DataNode* sourceString : data.getArrayNode("strings"))
            {
                this->execute(ExecuteType::Source, *sourceString);
                this->addSource(ExecuteType::Source, *sourceString);
            }
        }
    }
} // namespace obe::Scene
