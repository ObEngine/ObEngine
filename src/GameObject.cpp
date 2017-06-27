//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "GameObject.hpp"
#include "DataParserLuaBridge.hpp"
#include "World.hpp"

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
                .addFunction("getID", &GameObject::getID)
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
            if (!Functions::Vector::isInList(type, allRequires->getAll(vili::Types::ComplexAttribute)))
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
                Script::DataBridge::complexAttributeToLuaTable(requireTable, requires);
            }
        }

        //GameObject
        GameObject::GameObject(std::string type, std::string id) : m_localTriggers(nullptr)
        {
            m_type = type;
            m_id = id;
        }

        GameObject::~GameObject()
        {
            TriggerDatabase::GetInstance()->removeNamespace(m_privateKey);
            TriggerDatabase::GetInstance()->removeNamespace(m_publicKey);
        }

        void GameObject::registerTrigger(Trigger* trg)
        {
            m_registeredTriggers.push_back(trg);
        }

        void GameObject::loadGameObject(World::World& world, vili::ComplexAttribute& obj)
        {
            //Animator
            std::string animatorPath;
            if (obj.contains(vili::Types::ComplexAttribute, "Animator"))
            {
                m_objectAnimator = std::make_unique<Animation::Animator>();
                animatorPath = obj.at("Animator").getBaseAttribute("path").get<std::string>();
                if (animatorPath != "")
                {
                    m_objectAnimator->setPath(animatorPath);
                    m_objectAnimator->loadAnimator();
                }
                if (obj.at("Animator").contains(vili::Types::BaseAttribute, "default"))
                {
                    m_objectAnimator->setKey(obj.at("Animator").getBaseAttribute("default").get<std::string>());
                }
                m_hasAnimator = true;
            }
            //Collider
            if (obj.contains(vili::Types::ComplexAttribute, "Collider"))
            {
                m_objectCollider = world.createCollider(m_id);

                std::string pointsUnit = obj.at("Collider", "unit").getBaseAttribute("unit").get<std::string>();
                bool completePoint = true;
                double pointBuffer;
                Coord::Units pBaseUnit = Coord::stringToUnits(pointsUnit);
                for (vili::BaseAttribute* colliderPoint : obj.at("Collider").getListAttribute("points"))
                {
                    if (completePoint = !completePoint)
                    {
                        Coord::UnitVector pVector2 = Coord::UnitVector(
                            pointBuffer,
                            colliderPoint->get<double>(),
                            pBaseUnit
                        ).to<Coord::WorldPixels>();
                        m_objectCollider->addPoint(pVector2.x, pVector2.y);
                    }
                    else
                        pointBuffer = colliderPoint->get<double>();
                }
                if (obj.at("Collider").contains(vili::Types::BaseAttribute, "tag"))
                    m_objectCollider->addTag(obj.at<vili::BaseAttribute>("Collider", "tag").get<std::string>());
                else if (obj.at("Collider").contains(vili::Types::ListAttribute, "tags"))
                {
                    for (vili::BaseAttribute* cTag : obj.at<vili::ListAttribute>("Collider", "tags"))
                        m_objectCollider->addTag(cTag->get<std::string>());
                }
                if (obj.at("Collider").contains(vili::Types::BaseAttribute, "accept"))
                    m_objectCollider->addAcceptedTag(obj.at<vili::BaseAttribute>("Collider", "accept").get<std::string>());
                else if (obj.at("Collider").contains(vili::Types::ListAttribute, "accept"))
                {
                    for (vili::BaseAttribute* aTag : obj.at<vili::ListAttribute>("Collider", "accept"))
                        m_objectCollider->addAcceptedTag(aTag->get<std::string>());
                }
                if (obj.at("Collider").contains(vili::Types::BaseAttribute, "exclude"))
                    m_objectCollider->addExcludedTag(obj.at<vili::BaseAttribute>("Collider", "exclude").get<std::string>());
                else if (obj.at("Collider").contains(vili::Types::ListAttribute, "exclude"))
                {
                    for (vili::BaseAttribute* eTag : obj.at<vili::ListAttribute>("Collider", "exclude"))
                        m_objectCollider->addExcludedTag(eTag->get<std::string>());
                }

                m_hasCollider = true;
            }
            //LevelSprite
            if (obj.contains(vili::Types::ComplexAttribute, "LevelSprite"))
            {
                m_objectLevelSprite = world.createLevelSprite(m_id);
                m_levelSpriteRelative = (obj.at("LevelSprite").getBaseAttribute("position").get<std::string>() == "relative") ? true : false;
                int sprOffX = 0;
                int sprOffY = 0;
                std::vector<std::string> decoAtrList;
                vili::ComplexAttribute& currentSprite = obj.at("LevelSprite");

                std::string spritePath = currentSprite.contains(vili::Types::BaseAttribute, "path") ?
                                             currentSprite.getBaseAttribute("path").get<std::string>() : "";
                Coord::UnitVector spritePos = Coord::UnitVector(
                    currentSprite.contains(vili::Types::ComplexAttribute, "pos") ?
                        currentSprite.at<vili::BaseAttribute>("pos", "x").get<double>() : 0,
                    currentSprite.contains(vili::Types::ComplexAttribute, "pos") ?
                        currentSprite.at<vili::BaseAttribute>("pos", "y").get<double>() : 0
                );
                int spriteRot = currentSprite.contains(vili::Types::BaseAttribute, "rotation") ?
                                    currentSprite.getBaseAttribute("rotation").get<int>() : 0;
                int layer = currentSprite.contains(vili::Types::BaseAttribute, "layer") ?
                                currentSprite.getBaseAttribute("layer").get<int>() : 1;
                int zdepth = currentSprite.contains(vili::Types::BaseAttribute, "z-depth") ?
                                 currentSprite.getBaseAttribute("z-depth").get<int>() : 1;

                if (obj.at("LevelSprite").contains(vili::Types::BaseAttribute, "offsetX"))
                    sprOffX = obj.at("LevelSprite").getBaseAttribute("offsetX").get<int>();
                if (obj.at("LevelSprite").contains(vili::Types::BaseAttribute, "offsetY"))
                    sprOffY = obj.at("LevelSprite").getBaseAttribute("offsetY").get<int>();
                if (obj.at("LevelSprite").contains(vili::Types::ListAttribute, "attributeList"))
                {
                    int atrListSize = obj.at("LevelSprite").getListAttribute("attributeList").size();
                    for (int j = 0; j < atrListSize; j++)
                        decoAtrList.push_back(obj.at("LevelSprite").getListAttribute("attributeList").get(j).get<std::string>());
                }

                m_objectLevelSprite->load(spritePath);
                m_objectLevelSprite->setPosition(spritePos.x, spritePos.y);
                m_objectLevelSprite->setRotation(spriteRot);
                //ADD SPRITE SIZE
                m_objectLevelSprite->setAtr(decoAtrList);
                m_objectLevelSprite->setLayer(layer);
                m_objectLevelSprite->setZDepth(zdepth);
                m_objectLevelSprite->setOffset(sprOffX, sprOffY);
                m_hasLevelSprite = true;
                world.reorganizeLayers();
            }
            //Script
            if (obj.contains(vili::Types::ComplexAttribute, "Script"))
            {
                m_objectScript = std::make_unique<kaguya::State>();
                m_hasScriptEngine = true;
                m_objectScript = std::make_unique<kaguya::State>();
                m_privateKey = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 12);
                m_publicKey = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 12);
                TriggerDatabase::GetInstance()->createNamespace(m_privateKey);
                TriggerDatabase::GetInstance()->createNamespace(m_publicKey);
                m_localTriggers = TriggerDatabase::GetInstance()->createTriggerGroup(m_privateKey, "Local");

                System::Path("Lib/GameLib/ScrInit.lua").loadResource(m_objectScript.get(), System::Loaders::luaLoader);
                loadScrGameObject(this, m_objectScript.get());

                m_localTriggers
                    ->addTrigger("Init")
                    ->setTriggerState("Init", true)
                    ->addTrigger("Update")
                    ->setPermanent("Update", true)
                    ->setTriggerState("Update", true)
                    ->addTrigger("Query")
                    ->addTrigger("Collide")
                    ->addTrigger("Click")
                    ->addTrigger("Press")
                    ->addTrigger("Delete")
                    ->addTrigger("Save");

                System::Path("Lib/GameLib/ObjectInit.lua").loadResource(m_objectScript.get(), System::Loaders::luaLoader);

                (*m_objectScript)["ID"] = m_id;
                (*m_objectScript)["Private"] = m_privateKey;
                (*m_objectScript)["Public"] = m_publicKey;
                (*m_objectScript)("protect(\"ID\")");
                (*m_objectScript)("protect(\"Private\")");
                (*m_objectScript)("protect(\"Public\")");


                if (obj.at("Script").contains(vili::Types::BaseAttribute, "source"))
                {
                    std::string getScrName = obj.at("Script").getBaseAttribute("source").get<std::string>();
                    System::Path(getScrName).loadResource(m_objectScript.get(), System::Loaders::luaLoader);
                }
                else if (obj.at("Script").contains(vili::Types::ListAttribute, "sources"))
                {
                    int scriptListSize = obj.at("Script").getListAttribute("sources").size();
                    for (int i = 0; i < scriptListSize; i++)
                    {
                        std::string getScrName = obj.at("Script").getListAttribute("sources").get(i).get<std::string>();
                        System::Path(getScrName).loadResource(m_objectScript.get(), System::Loaders::luaLoader);
                    }
                }
                if (obj.at("Script").contains(vili::Types::BaseAttribute, "priority"))
                    m_scrPriority = obj.at("Script").getBaseAttribute("priority").get<int>();
            }
        }

        void GameObject::update(double dt)
        {
            if (m_updated)
            {
                for (int i = 0; i < m_registeredTriggers.size(); i++)
                {
                    Trigger* trigger = m_registeredTriggers[i];
                    if (trigger->getState())
                    {
                        std::string useGrp = trigger->getGroup();
                        for (int j = 0; j < m_registeredAliases.size(); j++)
                        {
                            std::string alNsp, alGrp, alRep;
                            std::tie(alNsp, alGrp, alRep) = m_registeredAliases[j];
                            if (alNsp == trigger->getNamespace() && alGrp == trigger->getGroup())
                                useGrp = alRep;
                        }
                        std::string funcname = useGrp + "." + trigger->getName();
                        m_queryCounter = 0;
                        (*m_objectScript)["cpp_param"] = kaguya::NewTable();
                        (*m_objectScript)["cpp_param"]["dt"] = dt;
                        std::string triggerError = Script::injectParameters(*trigger, *m_objectScript);
                        if (!triggerError.empty())
                        {
                            throw aube::ErrorHandler::Raise("ObEngine.GameObject.GameObject.UnknownTriggerParameterType", {
                                { "parameter", triggerError },
                                { "object", m_id },
                                { "trigger", funcname }
                            });
                        }              
                        if (funcname == "Local.Init")
                        {
                            m_objectScript->dostring("LuaCore.LocalInitMirrorInjector()");
                        }
                        else
                        {
                            m_objectScript->dostring("if type(" + funcname + ") == \"function\" then " + funcname + "(cpp_param) end");
                        }
                        (*m_objectScript)["cpp_param"] = nullptr;
                    }
                }
                if (m_initialised)
                {
                    if (m_hasAnimator)
                    {
                        m_objectAnimator->update();
                        if (m_hasLevelSprite)
                        {
                            m_objectLevelSprite->setSprite(m_objectAnimator->getSprite());
                        }
                    }
                }
            }
        }

        std::string GameObject::getID() const
        {
            return m_id;
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

        TriggerGroup* GameObject::getLocalTriggers() const
        {
            return m_localTriggers.operator->();
        }

        void GameObject::useLocalTrigger(std::string trName)
        {
            this->registerTrigger(TriggerDatabase::GetInstance()->getTrigger(m_privateKey, "Local", trName));
        }

        void GameObject::useExternalTrigger(std::string trNsp, std::string trGrp, std::string trName, std::string useAs)
        {
            if (trName == "*")
            {
                std::vector<std::string> allEv = TriggerDatabase::GetInstance()->getAllTriggersNameFromTriggerGroup(trNsp, trGrp);
                for (int i = 0; i < allEv.size(); i++)
                {
                    this->registerTrigger(TriggerDatabase::GetInstance()->getTrigger(trNsp, trGrp, allEv[i]));
                }
            }
            else this->registerTrigger(TriggerDatabase::GetInstance()->getTrigger(trNsp, trGrp, trName));
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

        void GameObject::sendRequireArgumentFromLua(std::string argName, kaguya::LuaRef value) const
        {
            (*m_objectScript)["LuaCore"]["Lua_ReqList"][argName] = value;
        }

        void GameObject::deleteObject()
        {
            this->deletable = true;
        }
    }
}
