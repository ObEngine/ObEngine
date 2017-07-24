#include <Scene/Scene.hpp>
#include <Script/GameObject.hpp>
#include <Script/Script.hpp>
#include <Script/ViliLuaBridge.hpp>
#include <System/Loaders.hpp>
#include <Transform/Units.hpp>
#include <Transform/UnitVector.hpp>
#include <Triggers/Trigger.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Script
    {
        KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(useExternalTriggerProxy, GameObject, useExternalTrigger, 3, 4,
            void(GameObject::*)(std::string, std::string, std::string, std::string));

        void loadScrGameObject(GameObject* obj, kaguya::State* lua)
        {
            (*lua)["CPP_Import"] = &loadLibBridge;
            (*lua)["CPP_Hook"] = &loadHookBridge;
            loadScrGameObjectLib(lua);
            (*lua)["This"] = obj;
        }

        void loadScrGameObjectLib(kaguya::State* lua)
        {
            (*lua)["CPP_GameObject"].setClass(kaguya::UserdataMetatable<GameObject>()
                .addFunction("LevelSprite", &GameObject::getLevelSprite)
                .addFunction("Collider", &GameObject::getCollider)
                .addFunction("Animator", &GameObject::getAnimator)
                .addFunction("State", &GameObject::getScript)
                .addFunction("canCollide", &GameObject::canCollide)
                .addFunction("canClick", &GameObject::canClick)
                .addFunction("canDisplay", &GameObject::canDisplay)
                .addFunction("delete", &GameObject::deleteObject)
                .addFunction("exec", &GameObject::exec)
                .addFunction("getInitialised", &GameObject::getInitialised)
                .addFunction("getPriority", &GameObject::getPriority)
                .addFunction("getPublicKey", &GameObject::getPublicKey)
                .addFunction("useLocalTrigger", &GameObject::useLocalTrigger)
                .addFunction("useExternalTrigger", useExternalTriggerProxy())
                .addOverloadedFunctions("sendQuery",
                                        &GameObject::sendQuery<int>,
                                        &GameObject::sendQuery<float>,
                                        &GameObject::sendQuery<std::string>,
                                        &GameObject::sendQuery<bool>,
                                        &GameObject::sendQuery<std::vector<int>>,
                                        &GameObject::sendQuery<std::vector<float>>,
                                        &GameObject::sendQuery<std::vector<std::string>>,
                                        &GameObject::sendQuery<std::vector<bool>>,
                                        &GameObject::sendQuery<std::map<int, int>>,
                                        &GameObject::sendQuery<std::map<int, float>>,
                                        &GameObject::sendQuery<std::map<int, std::string>>,
                                        &GameObject::sendQuery<std::map<int, bool>>,
                                        &GameObject::sendQuery<std::map<std::string, int>>,
                                        &GameObject::sendQuery<std::map<std::string, float>>,
                                        &GameObject::sendQuery<std::map<std::string, std::string>>,
                                        &GameObject::sendQuery<std::map<std::string, bool>>
                )
                .addFunction("sendRequireArgument", &GameObject::sendRequireArgumentFromLua)
                .addFunction("setInitialised", &GameObject::setInitialised)
            );
        }

        void loadLibBridge(GameObject* object, std::string lib)
        {
            loadLib(object->getScript(), lib);
        }

        void loadHookBridge(GameObject* object, std::string hookname)
        {
            loadHook(object->getScript(), hookname);
        }

        bool orderScrPriority(GameObject* g1, GameObject* g2)
        {
            return (g1->getPriority() > g2->getPriority());
        }


        //GameObjectRequires
        GameObjectRequires* GameObjectRequires::instance = nullptr;

        GameObjectRequires* GameObjectRequires::getInstance()
        {
            if (!instance)
                instance = new GameObjectRequires();
            return instance;
        }

        vili::ComplexAttribute* GameObjectRequires::getRequiresForObjectType(std::string type) const
        {
            if (!Utils::Vector::isInList(type, allRequires->getAll(vili::AttributeType::ComplexAttribute)))
            {
                vili::DataParser getGameObjectFile;
                System::Path("Data/GameObjects/").add(type).add(type + ".obj.vili").loadResource(&getGameObjectFile, System::Loaders::dataLoader);
                if (getGameObjectFile->contains("Requires"))
                {
                    vili::ComplexAttribute& requiresData = getGameObjectFile.at<vili::ComplexAttribute>("Requires");
                    getGameObjectFile->extractElement(&getGameObjectFile.at<vili::ComplexAttribute>("Requires"));
                    requiresData.setID(type);
                    allRequires->pushComplexAttribute(&requiresData);
                    return &requiresData;
                }
                return nullptr;
            }
            return &allRequires.at(type);
        }

        void GameObjectRequires::ApplyRequirements(GameObject* obj, vili::ComplexAttribute& requires)
        {
            for (std::string currentRequirement : requires.getAll())
            {
                requires.setID("Lua_ReqList");
                kaguya::LuaTable requireTable = ((*obj->getScript())["LuaCore"]);
                DataBridge::complexAttributeToLuaTable(requireTable, requires);
            }
        }

        //GameObject
        GameObject::GameObject(const std::string& type, const std::string& id) : Identifiable(id), m_localTriggers(nullptr)
        {
            m_type = type;
            m_id = id;
        }

        GameObject::~GameObject()
        {
            Triggers::TriggerDatabase::GetInstance()->removeNamespace(m_privateKey);
            Triggers::TriggerDatabase::GetInstance()->removeNamespace(m_publicKey);
        }

        void GameObject::registerTrigger(Triggers::Trigger* trg)
        {
            m_registeredTriggers.push_back(trg);
        }

        void GameObject::loadGameObject(Scene::Scene& world, vili::ComplexAttribute& obj)
        {
            //Animator
            std::string animatorPath;
            if (obj.contains(vili::AttributeType::ComplexAttribute, "Animator"))
            {
                m_objectAnimator = std::make_unique<Animation::Animator>();
                animatorPath = obj.at("Animator").getBaseAttribute("path").get<std::string>();
                if (animatorPath != "")
                {
                    m_objectAnimator->setPath(animatorPath);
                    m_objectAnimator->loadAnimator();
                }
                if (obj.at("Animator").contains(vili::AttributeType::BaseAttribute, "default"))
                {
                    m_objectAnimator->setKey(obj.at("Animator").getBaseAttribute("default").get<std::string>());
                }
                m_hasAnimator = true;
            }
            //Collider
            if (obj.contains(vili::AttributeType::ComplexAttribute, "Collider"))
            {
                m_objectCollider = world.createCollider(m_id);

                std::string pointsUnit = obj.at("Collider", "unit").getBaseAttribute("unit").get<std::string>();
                bool completePoint = true;
                double pointBuffer;
                Transform::Units pBaseUnit = Transform::stringToUnits(pointsUnit);
                for (vili::BaseAttribute* colliderPoint : obj.at("Collider").getListAttribute("points"))
                {
                    if (completePoint = !completePoint)
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
                if (obj.at("Collider").contains(vili::AttributeType::BaseAttribute, "tag"))
                    m_objectCollider->addTag(Collision::ColliderTagType::Tag, obj.at<vili::BaseAttribute>("Collider", "tag").get<std::string>());
                else if (obj.at("Collider").contains(vili::AttributeType::ListAttribute, "tags"))
                {
                    for (vili::BaseAttribute* cTag : obj.at<vili::ListAttribute>("Collider", "tags"))
                        m_objectCollider->addTag(Collision::ColliderTagType::Tag, cTag->get<std::string>());
                }
                if (obj.at("Collider").contains(vili::AttributeType::BaseAttribute, "accept"))
                    m_objectCollider->addTag(Collision::ColliderTagType::Accepted, obj.at<vili::BaseAttribute>("Collider", "accept").get<std::string>());
                else if (obj.at("Collider").contains(vili::AttributeType::ListAttribute, "accept"))
                {
                    for (vili::BaseAttribute* aTag : obj.at<vili::ListAttribute>("Collider", "accept"))
                        m_objectCollider->addTag(Collision::ColliderTagType::Accepted, aTag->get<std::string>());
                }
                if (obj.at("Collider").contains(vili::AttributeType::BaseAttribute, "reject"))
                    m_objectCollider->addTag(Collision::ColliderTagType::Rejected, obj.at<vili::BaseAttribute>("Collider", "reject").get<std::string>());
                else if (obj.at("Collider").contains(vili::AttributeType::ListAttribute, "reject"))
                {
                    for (vili::BaseAttribute* rTag : obj.at<vili::ListAttribute>("Collider", "reject"))
                        m_objectCollider->addTag(Collision::ColliderTagType::Rejected, rTag->get<std::string>());
                }

                m_hasCollider = true;
            }
            //LevelSprite
            if (obj.contains(vili::AttributeType::ComplexAttribute, "LevelSprite"))
            {
                m_objectLevelSprite = world.createLevelSprite(m_id);
                m_levelSpriteRelative = (obj.at("LevelSprite").getBaseAttribute("position").get<std::string>() == "relative") ? true : false;
                int sprOffX = 0;
                int sprOffY = 0;
                std::string spriteXTransformer;
                std::string spriteYTransformer;
                vili::ComplexAttribute& currentSprite = obj.at("LevelSprite");

                std::string spritePath = currentSprite.contains(vili::AttributeType::BaseAttribute, "path") ?
                                             currentSprite.getBaseAttribute("path").get<std::string>() : "";
                Transform::UnitVector spritePos = Transform::UnitVector(
                    currentSprite.contains(vili::AttributeType::ComplexAttribute, "pos") ?
                        currentSprite.at<vili::BaseAttribute>("pos", "x").get<double>() : 0,
                    currentSprite.contains(vili::AttributeType::ComplexAttribute, "pos") ?
                        currentSprite.at<vili::BaseAttribute>("pos", "y").get<double>() : 0
                );
                int spriteRot = currentSprite.contains(vili::AttributeType::BaseAttribute, "rotation") ?
                                    currentSprite.getBaseAttribute("rotation").get<int>() : 0;
                int layer = currentSprite.contains(vili::AttributeType::BaseAttribute, "layer") ?
                                currentSprite.getBaseAttribute("layer").get<int>() : 1;
                int zdepth = currentSprite.contains(vili::AttributeType::BaseAttribute, "z-depth") ?
                                 currentSprite.getBaseAttribute("z-depth").get<int>() : 1;

                if (currentSprite.contains(vili::AttributeType::BaseAttribute, "xTransform"))
                {
                    spriteXTransformer = currentSprite.at<vili::BaseAttribute>("xTransform").get<std::string>();
                }
                else
                {
                    spriteXTransformer = "None";
                }
                if (currentSprite.contains(vili::AttributeType::BaseAttribute, "yTransform"))
                {
                    spriteYTransformer = currentSprite.at<vili::BaseAttribute>("yTransform").get<std::string>();
                }
                else
                {
                    spriteYTransformer = "None";
                }

                m_objectLevelSprite->load(spritePath);
                m_objectLevelSprite->setPosition(spritePos.x, spritePos.y);
                m_objectLevelSprite->setRotation(spriteRot);
                //ADD SPRITE SIZE
                Graphics::PositionTransformers::PositionTransformer positionTransformer(spriteXTransformer, spriteYTransformer);
                m_objectLevelSprite->setPositionTransformer(positionTransformer);
                m_objectLevelSprite->setLayer(layer);
                m_objectLevelSprite->setZDepth(zdepth);
                m_hasLevelSprite = true;
                world.reorganizeLayers();
            }
            //Script
            if (obj.contains(vili::AttributeType::ComplexAttribute, "Script"))
            {
                m_objectScript = std::make_unique<kaguya::State>();
                m_hasScriptEngine = true;
                m_objectScript = std::make_unique<kaguya::State>();
                m_privateKey = Utils::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 12);
                m_publicKey = Utils::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 12);
                Triggers::TriggerDatabase::GetInstance()->createNamespace(m_privateKey);
                Triggers::TriggerDatabase::GetInstance()->createNamespace(m_publicKey);
                m_localTriggers = Triggers::TriggerDatabase::GetInstance()->createTriggerGroup(m_privateKey, "Local");

                System::Path("Lib/Internal/ScriptInit.lua").loadResource(m_objectScript.get(), System::Loaders::luaLoader);
                loadScrGameObject(this, m_objectScript.get());

                m_localTriggers
                    ->addTrigger("Init")
                    ->addTrigger("Update")
                    ->trigger("Update")
                    ->addTrigger("Query")
                    ->addTrigger("Collide")
                    ->addTrigger("Click")
                    ->addTrigger("Press")
                    ->addTrigger("Delete")
                    ->addTrigger("Save");

                System::Path("Lib/Internal/ObjectInit.lua").loadResource(m_objectScript.get(), System::Loaders::luaLoader);

                (*m_objectScript)["Private"] = m_privateKey;
                (*m_objectScript)["Public"] = m_publicKey;

                if (obj.at("Script").contains(vili::AttributeType::BaseAttribute, "source"))
                {
                    std::string getScrName = obj.at("Script").getBaseAttribute("source").get<std::string>();
                    System::Path(getScrName).loadResource(m_objectScript.get(), System::Loaders::luaLoader);
                }
                else if (obj.at("Script").contains(vili::AttributeType::ListAttribute, "sources"))
                {
                    int scriptListSize = obj.at("Script").getListAttribute("sources").size();
                    for (int i = 0; i < scriptListSize; i++)
                    {
                        std::string getScrName = obj.at("Script").getListAttribute("sources").get(i).get<std::string>();
                        System::Path(getScrName).loadResource(m_objectScript.get(), System::Loaders::luaLoader);
                    }
                }
                if (obj.at("Script").contains(vili::AttributeType::BaseAttribute, "priority"))
                    m_scrPriority = obj.at("Script").getBaseAttribute("priority").get<int>();
            }
        }

        void GameObject::update(double dt)
        {
            if (m_updated)
            {
                std::cout << "UPDATE" << std::endl;
                m_localTriggers->pushParameter("Init", "Lol", 3);
                m_localTriggers->pushParameter("Init", "Mdr", 10);
                m_localTriggers->trigger("Init");
                m_localTriggers->pushParameter("Init", "Lol", 22);
                m_localTriggers->pushParameter("Init", "Mdr", 44);
                m_localTriggers->trigger("Init");
                for (int i = 0; i < m_registeredTriggers.size(); i++)
                {
                    Triggers::Trigger* trigger = m_registeredTriggers[i];
                    if (trigger->getState())
                    {
                        std::string useGrp = trigger->getGroup();
                        for (int j = 0; j < m_registeredAliases.size(); j++)
                        {
                            std::string alNsp, alGrp, alRep;
                            tie(alNsp, alGrp, alRep) = m_registeredAliases[j];
                            if (alNsp == trigger->getNamespace() && alGrp == trigger->getGroup())
                                useGrp = alRep;
                        }
                        std::string funcname = useGrp + "." + trigger->getName();
                        (*m_objectScript)["cpp_param"] = kaguya::NewTable();
                        (*m_objectScript)["cpp_param"]["dt"] = dt;
                        trigger->execute(m_objectScript.get(), funcname);
                        if (funcname == "Local.Init")
                        {
                            this->setInitialised(true);
                        }
                    }
                }
                if (m_initialised)
                {
                    if (m_hasAnimator)
                    {
                        m_objectAnimator->update();
                        if (m_hasLevelSprite)
                        {
                            m_objectLevelSprite->setTexture(m_objectAnimator->getTexture());
                        }
                    }
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

        int GameObject::getPriority() const
        {
            return m_scrPriority;
        }

        bool GameObject::canDisplay() const
        {
            return m_hasLevelSprite;
        }

        bool GameObject::canCollide() const
        {
            return (m_hasCollider && m_colliderSolid);
        }

        bool GameObject::canClick() const
        {
            return (m_hasCollider && m_colliderClick);
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

        bool GameObject::isLevelSpriteRelative() const
        {
            return m_levelSpriteRelative;
        }

        bool GameObject::getUpdateState() const
        {
            return m_updated;
        }

        void GameObject::setUpdateState(bool state)
        {
            m_updated = state;
        }

        Graphics::LevelSprite* GameObject::getLevelSprite()
        {
            if (m_hasLevelSprite)
                return m_objectLevelSprite;
            throw aube::ErrorHandler::Raise("ObEngine.GameObject.GameObject.NoLevelSprite", {{"id", m_id}});
        }

        Collision::PolygonalCollider* GameObject::getCollider()
        {
            if (m_hasCollider)
                return m_objectCollider;
            throw aube::ErrorHandler::Raise("ObEngine.GameObject.GameObject.NoCollider", {{"id", m_id}});
        }

        Animation::Animator* GameObject::getAnimator()
        {
            if (m_hasAnimator)
                return m_objectAnimator.get();
            throw aube::ErrorHandler::Raise("ObEngine.GameObject.GameObject.NoAnimator", {{"id", m_id}});
        }

        kaguya::State* GameObject::getScript()
        {
            if (m_hasScriptEngine)
                return m_objectScript.get();
            throw aube::ErrorHandler::Raise("ObEngine.GameObject.GameObject.NoScript", {{"id", m_id}});
        }

        Triggers::TriggerGroup* GameObject::getLocalTriggers() const
        {
            return m_localTriggers.operator->();
        }

        void GameObject::useLocalTrigger(const std::string& trName)
        {
            this->registerTrigger(Triggers::TriggerDatabase::GetInstance()->getTrigger(m_privateKey, "Local", trName));
            Triggers::TriggerDatabase::GetInstance()->getTrigger(m_privateKey, "Local", trName)->registerState(m_objectScript.get());
        }

        void GameObject::useExternalTrigger(const std::string& trNsp, const std::string& trGrp, const std::string& trName, const std::string& useAs)
        {
            if (trName == "*")
            {
                std::vector<std::string> allEv = Triggers::TriggerDatabase::GetInstance()->getAllTriggersNameFromTriggerGroup(trNsp, trGrp);
                for (int i = 0; i < allEv.size(); i++)
                {
                    this->registerTrigger(Triggers::TriggerDatabase::GetInstance()->getTrigger(trNsp, trGrp, allEv[i]));
                }
            }
            else this->registerTrigger(Triggers::TriggerDatabase::GetInstance()->getTrigger(trNsp, trGrp, trName));
            if (useAs != "")
            {
                m_registeredAliases.push_back(std::tuple<std::string, std::string, std::string>(trNsp, trGrp, useAs));
            }
        }

        void GameObject::setInitialised(bool init)
        {
            m_initialised = init;
        }

        bool GameObject::getInitialised() const
        {
            return m_initialised;
        }

        void GameObject::exec(std::string query) const
        {
            m_objectScript->dostring(query);
        }

        void GameObject::sendRequireArgumentFromLua(const std::string& argName, kaguya::LuaRef value) const
        {
            (*m_objectScript)["LuaCore"]["Lua_ReqList"][argName] = value;
        }

        void GameObject::deleteObject()
        {
            this->deletable = true;
        }
    }
}
