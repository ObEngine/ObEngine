#include <Bindings/Bindings.hpp>
#include <Scene/Scene.hpp>
#include <Script/GameObject.hpp>
#include <Script/GlobalState.hpp>
#include <Script/Script.hpp>
#include <Script/ViliLuaBridge.hpp>
#include <System/Loaders.hpp>
#include <Transform/Units.hpp>
#include <Transform/UnitVector.hpp>
#include <Triggers/Trigger.hpp>
#include <Triggers/TriggerDatabase.hpp>

#define GAMEOBJECTENV ScriptEngine["__ENVIRONMENTS"][m_envIndex]

namespace obe
{
    namespace Script
    {
        KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(useExternalTriggerProxy, GameObject, useExternalTrigger, 3, 4,
            void(GameObject::*)(std::string, std::string, std::string, std::string));

        /*kaguya::LuaTable GameObject::access(kaguya::State* lua) const
        {
            return (*m_objectScript)["Object"];
        }*/

        unsigned GameObject::getEnvIndex() const
        {
            return m_envIndex;
        }

        kaguya::LuaTable GameObject::access() const
        {
            return GAMEOBJECTENV["Object"];
        }

        kaguya::LuaFunction GameObject::getConstructor() const
        {
            return GAMEOBJECTENV["ObjectInit"];
        }

        vili::ViliParser GameObjectDatabase::allDefinitions;
        vili::ViliParser GameObjectDatabase::allRequires;
        vili::ComplexNode* GameObjectDatabase::GetRequirementsForGameObject(const std::string& type)
        {
            if (!allRequires.root().contains(type))
            {
                vili::ViliParser getGameObjectFile;
                System::Path("Data/GameObjects/").add(type).add(type + ".obj.vili").loadResource(&getGameObjectFile, System::Loaders::dataLoader);
                if (getGameObjectFile->contains("Requires"))
                {
                    vili::ComplexNode& requiresData = getGameObjectFile.at<vili::ComplexNode>("Requires");
                    getGameObjectFile->extractElement(&getGameObjectFile.at<vili::ComplexNode>("Requires"));
                    requiresData.setId(type);
                    allRequires->pushComplexNode(&requiresData);
                    return &requiresData;
                }
                return nullptr;
            }
            return &allRequires.at(type);
        }

        vili::ComplexNode* GameObjectDatabase::GetDefinitionForGameObject(const std::string& type)
        {
            if (!allDefinitions.root().contains(type))
            {
                vili::ViliParser getGameObjectFile;
                System::Path("Data/GameObjects/").add(type).add(type + ".obj.vili").loadResource(&getGameObjectFile, System::Loaders::dataLoader);
                if (getGameObjectFile->contains(type))
                {
                    vili::ComplexNode& definitionData = getGameObjectFile.at<vili::ComplexNode>(type);
                    getGameObjectFile->extractElement(&getGameObjectFile.at<vili::ComplexNode>(type));
                    definitionData.setId(type);
                    allDefinitions->pushComplexNode(&definitionData);
                    return &definitionData;
                }
                aube::ErrorHandler::Raise("ObEngine.Script.GameObjectDatabase.ObjectDefinitionNotFound", { { "objectType", type } });
                return nullptr;
            }
            return &allDefinitions.at(type);
        }

        void GameObjectDatabase::ApplyRequirements(GameObject* obj, vili::ComplexNode& requires)
        {
            for (const std::string& currentRequirement : requires.getAll())
            {
                kaguya::LuaTable requireTable = ScriptEngine["__ENVIRONMENTS"][obj->getEnvIndex()]["LuaCore"]["ObjectInitInjectionTable"];
                DataBridge::dataToLua(requireTable, requires.get(currentRequirement));
            }
        }

        //GameObject
        std::vector<unsigned int> GameObject::AllEnvs;

        GameObject::GameObject(const std::string& type, const std::string& id) : Identifiable(id), m_localTriggers(nullptr), m_objectNode(id)
        {
            m_type = type;
            m_id = id;
        }

        void GameObject::initialize()
        {
            if (!m_initialised)
            {
                Debug::Log->debug("<GameObject> Initialising GameObject '{0}'", m_id);
                m_initialised = true;
                GAMEOBJECTENV["__OBJECT_INIT"] = true;
                m_localTriggers->trigger("Init");
            }
            else
                Debug::Log->warn("<GameObject> GameObject '{0}' has already been initialised", m_id);
        }

        GameObject::~GameObject()
        {
            if (m_hasScriptEngine)
            {
                Triggers::TriggerDatabase::GetInstance()->removeNamespace(m_privateKey);
                Triggers::TriggerDatabase::GetInstance()->removeNamespace(m_publicKey);
            }
        }

        void GameObject::sendInitArgFromLua(const std::string& argName, kaguya::LuaRef value) const
        {
            Debug::Log->debug("<GameObject> Sending Local.Init argument {0} to GameObject {1} (From Lua)", argName, m_id);
            m_localTriggers->pushParameterFromLua("Init", argName, value);
        }

        void GameObject::registerTrigger(Triggers::Trigger* trg, const std::string& callbackName)
        {
            m_registeredTriggers.emplace_back(trg, callbackName);
        }

        void GameObject::loadGameObject(Scene::Scene& world, vili::ComplexNode& obj)
        {
            Debug::Log->debug("<GameObject> Loading GameObject '{0}'", m_id);
            //Script
            if (obj.contains(vili::NodeType::DataNode, "permanent"))
            {
                m_permanent = obj.getDataNode("permanent").get<bool>();
            }
            if (obj.contains(vili::NodeType::ComplexNode, "Script"))
            {
                m_hasScriptEngine = true;
                m_privateKey = Utils::String::getRandomKey(Utils::String::Alphabet + Utils::String::Numbers, 12);
                m_publicKey = Utils::String::getRandomKey(Utils::String::Alphabet + Utils::String::Numbers, 12);
                Triggers::TriggerDatabase::GetInstance()->createNamespace(m_privateKey);
                Triggers::TriggerDatabase::GetInstance()->createNamespace(m_publicKey);
                m_localTriggers = Triggers::TriggerDatabase::GetInstance()->createTriggerGroup(m_privateKey, "Local");

                m_envIndex = ScriptEngine["CreateNewEnv"]();
                AllEnvs.push_back(m_envIndex);
                //std::cout << "Environment Index is : " << m_envIndex << std::endl;

                //executeFile(m_envIndex, System::Path("Lib/Internal/ScriptInit.lua").find());
                //loadScrGameObject(this, m_objectScript.get());

                GAMEOBJECTENV["This"] = this;

                m_localTriggers
                    ->addTrigger("Init")
                    ->addTrigger("Delete");

                executeFile(m_envIndex, System::Path("Lib/Internal/ObjectInit.lua").find());

                GAMEOBJECTENV["__OBJECT_TYPE"] = m_type;
                GAMEOBJECTENV["__OBJECT_ID"] = m_id;
                GAMEOBJECTENV["__OBJECT_INIT"] = false;
                GAMEOBJECTENV["Private"] = m_privateKey;
                GAMEOBJECTENV["Public"] = m_publicKey;

                if (obj.at("Script").contains(vili::NodeType::DataNode, "source"))
                {
                    std::string getScrName = obj.at("Script").getDataNode("source").get<std::string>();
                    executeFile(m_envIndex, System::Path(getScrName).find());
                }
                else if (obj.at("Script").contains(vili::NodeType::ArrayNode, "sources"))
                {
                    int scriptListSize = obj.at("Script").getArrayNode("sources").size();
                    for (int i = 0; i < scriptListSize; i++)
                    {
                        std::string getScrName = obj.at("Script").getArrayNode("sources").get(i).get<std::string>();
                        executeFile(m_envIndex, System::Path(getScrName).find());
                    }
                }
            }
            if (obj.contains(vili::NodeType::ComplexNode, "Animator"))
            {
                m_objectAnimator = std::make_unique<Animation::Animator>();
                std::string animatorPath = obj.at("Animator").getDataNode("path").get<std::string>();
                if (animatorPath != "")
                {
                    m_objectAnimator->setPath(animatorPath);
                    m_objectAnimator->loadAnimator();
                }
                if (obj.at("Animator").contains(vili::NodeType::DataNode, "default"))
                {
                    m_objectAnimator->setKey(obj.at("Animator").getDataNode("default").get<std::string>());
                }
                if (m_hasScriptEngine)
                    GAMEOBJECTENV["Object"]["Animation"] = m_objectAnimator.get();
                m_hasAnimator = true;
            }
            //Collider
            if (obj.contains(vili::NodeType::ComplexNode, "Collider"))
            {
                m_objectCollider = world.createCollider(m_id, false);
                m_objectNode.addChild(m_objectCollider);

                std::string pointsUnit = obj.at("Collider", "unit").getDataNode("unit").get<std::string>();
                bool completePoint = true;
                double pointBuffer = 0;
                Transform::Units pBaseUnit = Transform::stringToUnits(pointsUnit);
                for (vili::DataNode* colliderPoint : obj.at("Collider").getArrayNode("points"))
                {
                    if ((completePoint = !completePoint))
                    {
                        Transform::UnitVector pVector2 = Transform::UnitVector(
                            pointBuffer,
                            colliderPoint->get<double>(),
                            pBaseUnit
                        ).to<Transform::Units::WorldPixels>();
                        m_objectCollider->addPoint(pVector2);
                    }
                    else
                        pointBuffer = colliderPoint->get<double>();
                }
                if (obj.at("Collider").contains(vili::NodeType::DataNode, "tag"))
                    m_objectCollider->addTag(Collision::ColliderTagType::Tag, obj.at<vili::DataNode>("Collider", "tag").get<std::string>());
                else if (obj.at("Collider").contains(vili::NodeType::ArrayNode, "tags"))
                {
                    for (vili::DataNode* cTag : obj.at<vili::ArrayNode>("Collider", "tags"))
                        m_objectCollider->addTag(Collision::ColliderTagType::Tag, cTag->get<std::string>());
                }
                if (obj.at("Collider").contains(vili::NodeType::DataNode, "accept"))
                    m_objectCollider->addTag(Collision::ColliderTagType::Accepted, obj.at<vili::DataNode>("Collider", "accept").get<std::string>());
                else if (obj.at("Collider").contains(vili::NodeType::ArrayNode, "accept"))
                {
                    for (vili::DataNode* aTag : obj.at<vili::ArrayNode>("Collider", "accept"))
                        m_objectCollider->addTag(Collision::ColliderTagType::Accepted, aTag->get<std::string>());
                }
                if (obj.at("Collider").contains(vili::NodeType::DataNode, "reject"))
                    m_objectCollider->addTag(Collision::ColliderTagType::Rejected, obj.at<vili::DataNode>("Collider", "reject").get<std::string>());
                else if (obj.at("Collider").contains(vili::NodeType::ArrayNode, "reject"))
                {
                    for (vili::DataNode* rTag : obj.at<vili::ArrayNode>("Collider", "reject"))
                        m_objectCollider->addTag(Collision::ColliderTagType::Rejected, rTag->get<std::string>());
                }

                if (m_hasScriptEngine)
                    GAMEOBJECTENV["Object"]["Collider"] = m_objectCollider;
                m_hasCollider = true;
            }
            //LevelSprite
            if (obj.contains(vili::NodeType::ComplexNode, "LevelSprite"))
            {
                m_objectLevelSprite = world.createLevelSprite(m_id, false);
                m_objectNode.addChild(m_objectLevelSprite);
                m_objectLevelSprite->configure(obj.at("LevelSprite"));
                if (m_hasScriptEngine)
                    GAMEOBJECTENV["Object"]["LevelSprite"] = m_objectLevelSprite;
                m_hasLevelSprite = true;
                world.reorganizeLayers();
            }
        }

        void GameObject::update()
        {
            if (m_canUpdate)
            {
                if (m_initialised)
                {
                    if (m_hasAnimator)
                    {
                        if (m_objectAnimator->getKey() != "")
                            m_objectAnimator->update();
                        if (m_hasLevelSprite)
                        {
                            m_objectLevelSprite->setTexture(m_objectAnimator->getTexture());
                        }
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

        std::string GameObject::getPublicKey() const
        {
            return m_publicKey;
        }

        bool GameObject::doesHaveAnimator() const
        {
            return m_hasAnimator;
        }

        bool GameObject::doesHaveCollider() const
        {
            return m_hasCollider;
        }

        bool GameObject::doesHaveLevelSprite() const
        {
            return m_hasLevelSprite;
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

        Graphics::LevelSprite* GameObject::getLevelSprite()
        {
            if (m_hasLevelSprite)
                return m_objectLevelSprite;
            throw aube::ErrorHandler::Raise("ObEngine.Script.GameObject.NoLevelSprite", {{"id", m_id}});
        }

        Transform::SceneNode* GameObject::getSceneNode()
        {
            return &m_objectNode;
        }

        Collision::PolygonalCollider* GameObject::getCollider()
        {
            if (m_hasCollider)
                return m_objectCollider;
            throw aube::ErrorHandler::Raise("ObEngine.Script.GameObject.NoCollider", {{"id", m_id}});
        }

        Animation::Animator* GameObject::getAnimator()
        {
            if (m_hasAnimator)
                return m_objectAnimator.get();
            throw aube::ErrorHandler::Raise("ObEngine.Script.GameObject.NoAnimator", {{"id", m_id}});
        }

        Triggers::TriggerGroup* GameObject::getLocalTriggers() const
        {
            return m_localTriggers.operator->();
        }

        void GameObject::useLocalTrigger(const std::string& trName)
        {
            this->registerTrigger(Triggers::TriggerDatabase::GetInstance()->getTrigger(m_privateKey, "Local", trName), "Local." + trName);
            Triggers::TriggerDatabase::GetInstance()->getTrigger(m_privateKey, "Local", trName)->registerEnvironment(m_envIndex, "Local." + trName);
        }

        void GameObject::useExternalTrigger(const std::string& trNsp, const std::string& trGrp, const std::string& trName, const std::string& callAlias)
        {
            if (trName == "*")
            {
                std::vector<std::string> allTrg = Triggers::TriggerDatabase::GetInstance()->getAllTriggersNameFromTriggerGroup(trNsp, trGrp);
                for (int i = 0; i < allTrg.size(); i++)
                {
                    this->useExternalTrigger(trNsp, trGrp, trName, 
                        (Utils::String::occurencesInString(callAlias, "*")) ? 
                        Utils::String::replace(callAlias, "*", allTrg[i]) : 
                        "");
                }
            }
            else 
            {
                bool triggerNotFound = true;
                for (auto& triggerPair : m_registeredTriggers)
                {
                    if (triggerPair.first == Triggers::TriggerDatabase::GetInstance()->getTrigger(trNsp, trGrp, trName))
                    {
                        triggerNotFound = false;
                    }
                }
                if (triggerNotFound)
                {
                    std::string callbackName = (callAlias.empty()) ? trNsp + "." + trGrp + "." + trName : callAlias;
                    this->registerTrigger(Triggers::TriggerDatabase::GetInstance()->getTrigger(trNsp, trGrp, trName), callbackName);
                    Triggers::TriggerDatabase::GetInstance()->getTrigger(trNsp, trGrp, trName)->registerEnvironment(m_envIndex, callbackName);
                }
            }
        }

        void GameObject::exec(const std::string& query) const
        {
            ScriptEngine["ExecuteStringOnEnv"](query, m_envIndex);
        }

        void GameObject::deleteObject()
        {
            m_localTriggers->trigger("Delete");
            this->deletable = true;
            for (auto& trigger : m_registeredTriggers)
            {
                trigger.first->unregisterEnvironment(m_envIndex);
            }
            if (m_hasLevelSprite)
                hookCore.getPointer("Scene")->as<Scene::Scene*>()->removeLevelSprite(m_objectLevelSprite->getId());
            if (m_hasCollider)
                hookCore.getPointer("Scene")->as<Scene::Scene*>()->removeCollider(m_objectCollider->getId());
            AllEnvs.erase(
                std::remove_if(
                    AllEnvs.begin(), 
                    AllEnvs.end(), 
                    [this](const unsigned int& envIndex) { return envIndex == m_envIndex; }
                ), 
                AllEnvs.end()
            );
            //GAMEOBJECTENV = nullptr;
        }

        void GameObject::setPermanent(bool permanent)
        {
            m_permanent = permanent;
        }

        bool GameObject::isPermanent() const
        {
            return m_permanent;
        }
    }
}