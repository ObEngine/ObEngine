#include <Bindings/Bindings.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Scene/Scene.hpp>
#include <Script/GlobalState.hpp>
#include <Script/ViliLuaBridge.hpp>
#include <System/Loaders.hpp>
#include <System/Window.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/MathUtils.hpp>
#include <Utils/StringUtils.hpp>

namespace obe::Scene
{
    Scene::Scene()
        : Registrable("Scene")
        , m_sceneTriggers(
              Triggers::TriggerDatabase::GetInstance().createTriggerGroup("Global", "Scene"),
              Triggers::TriggerGroupPtrRemover)

    {
        System::Path("Lib/Internal/GameInit.lua")
            .load(System::Loaders::luaLoader, Script::ScriptEngine);
        Triggers::TriggerDatabase::GetInstance().createNamespace("Map");
        m_showElements["CollisionLines"] = false;
        m_showElements["CollisionPoints"] = false;
        m_showElements["CollisionMasterPoint"] = false;
        m_showElements["CollisionSkeleton"] = false;
        m_showElements["SceneNodes"] = false;

        m_sceneTriggers->addTrigger("MapLoaded");
    }

    Scene::~Scene()
    {
        Triggers::TriggerDatabase::GetInstance().removeNamespace("Map");
    }

    Graphics::LevelSprite* Scene::createLevelSprite(const std::string& id, bool addToSceneRoot)
    {
        std::string createId = id;
        if (createId.empty())
        {
            int i = 0;
            std::string testId = "sprite" + std::to_string(this->getColliderAmount() + i);
            while (this->doesLevelSpriteExists(testId))
            {
                testId = "sprite" + std::to_string(this->getLevelSpriteAmount() + i++);
            }
            createId = testId;
        }
        if (!this->doesLevelSpriteExists(createId))
        {
            std::unique_ptr<Graphics::LevelSprite> newLevelSprite
                = std::make_unique<Graphics::LevelSprite>(createId);

            Graphics::LevelSprite* returnLevelSprite = newLevelSprite.get();
            m_spriteArray.push_back(move(newLevelSprite));

            if (addToSceneRoot)
                m_sceneRoot.addChild(returnLevelSprite);

            this->reorganizeLayers();
            return returnLevelSprite;
        }
        else
        {
            Debug::Log->warn("<Scene> Sprite '{0}' already exists !", createId);
            return this->getLevelSprite(createId);
        }
    }

    Collision::PolygonalCollider* Scene::createCollider(const std::string& id, bool addToSceneRoot)
    {
        std::string createId = id;
        if (createId.empty())
        {
            int i = 0;
            std::string testId = "collider" + std::to_string(this->getColliderAmount() + i);
            while (this->doesColliderExists(testId))
            {
                testId = "collider" + std::to_string(this->getColliderAmount() + i++);
            }
            createId = testId;
        }
        if (!this->doesColliderExists(createId))
        {
            m_colliderArray.push_back(std::make_unique<Collision::PolygonalCollider>(createId));
            if (addToSceneRoot)
                m_sceneRoot.addChild(m_colliderArray.back().get());
            return m_colliderArray.back().get();
        }
        else
        {
            Debug::Log->warn("<Scene> Collider '{0}' already exists !", createId);
            return this->getCollider(createId);
        }
    }

    unsigned Scene::getColliderAmount() const
    {
        return m_colliderArray.size();
    }

    std::string Scene::getFilePath() const
    {
        return m_baseFolder;
    }

    void Scene::reload()
    {
        Debug::Log->debug("<Scene> Reloading Scene");
        m_futureLoad = m_levelFileName;
    }

    void Scene::reload(kaguya::LuaFunction callback)
    {
        Debug::Log->debug("<Scene> Reloading Scene");
        m_futureLoad = m_levelFileName;
        m_onLoadCallback = callback;
    }

    void Scene::loadFromFile(const std::string& filename)
    {
        Debug::Log->debug("<Scene> Loading Scene from map file : '{0}'", filename);
        this->clear();
        Debug::Log->debug("<Scene> Cleared Scene");
        if (filename != m_levelFileName)
        {
            m_levelFile = vili::ViliParser();
            m_baseFolder = System::Path("Data/Maps")
                               .add(filename)
                               .load(System::Loaders::dataLoader, m_levelFile)
                               .path();
            Debug::Log->debug("Scene File base folder : {}", m_baseFolder);
            m_levelFileName = filename;
        }

        if (m_levelFile->contains(vili::NodeType::ComplexNode, "Meta"))
        {
            vili::ComplexNode& meta = m_levelFile.at("Meta");
            m_levelName = meta.getDataNode("name").get<std::string>();
        }
        else
            throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.NoMeta", { { "map", filename } });

        if (m_levelFile->contains(vili::NodeType::ComplexNode, "View"))
        {
            vili::ComplexNode& view = m_levelFile.at("View");
            m_camera.setSize(view.at<vili::DataNode>("size").get<double>());
            m_cameraInitialPosition
                = Transform::UnitVector(view.at<vili::DataNode>("pos", "x").get<double>(),
                    view.at<vili::DataNode>("pos", "y").get<double>(),
                    Transform::stringToUnits(
                        view.at<vili::DataNode>("pos", "unit").get<std::string>()));
            m_cameraInitialReferential = Transform::Referential::TopLeft;
            if (m_levelFile->at("View").contains(vili::NodeType::ComplexNode, "referential"))
            {
                m_cameraInitialReferential
                    = Transform::Referential::FromString(m_levelFile->at("View", "referential")
                                                             .getDataNode("referential")
                                                             .get<std::string>());
            }
            Debug::Log->debug("<Scene> Set Camera Position at : {0}, {1} using "
                              "Referential {2}",
                m_cameraInitialPosition.x, m_cameraInitialPosition.y,
                m_cameraInitialReferential.toString());
            m_camera.setPosition(m_cameraInitialPosition, m_cameraInitialReferential);
        }
        else
            throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.NoView", { { "map", filename } });

        if (m_levelFile->contains(vili::NodeType::ComplexNode, "LevelSprites"))
        {
            vili::ComplexNode& levelSprites = m_levelFile.at("LevelSprites");

            for (vili::ComplexNode* currentSprite : levelSprites.getAll<vili::ComplexNode>())
            {
                this->createLevelSprite(currentSprite->getId())->load(*currentSprite);
            }
        }

        this->reorganizeLayers();

        if (m_levelFile->contains(vili::NodeType::ComplexNode, "Collisions"))
        {
            vili::ComplexNode& collisions = m_levelFile.at("Collisions");
            for (vili::ComplexNode* currentCollision : collisions.getAll<vili::ComplexNode>())
            {
                this->createCollider(currentCollision->getId())->load(*currentCollision);
            }
        }

        if (m_levelFile->contains(vili::NodeType::ComplexNode, "GameObjects"))
        {
            vili::ComplexNode& gameObjects = m_levelFile.at("GameObjects");
            for (vili::ComplexNode* currentObject : gameObjects.getAll<vili::ComplexNode>())
            {
                if (!this->doesGameObjectExists(currentObject->getId()))
                {
                    const std::string gameObjectType
                        = currentObject->getDataNode("type").get<std::string>();
                    Script::GameObject* newObject
                        = this->createGameObject(gameObjectType, currentObject->getId());
                    if (currentObject->contains(vili::NodeType::ComplexNode, "Requires"))
                    {
                        vili::ComplexNode& objectRequirements = currentObject->at("Requires");
                        currentObject->removeOwnership(&objectRequirements);
                        Script::GameObjectDatabase::ApplyRequirements(
                            newObject, objectRequirements);
                        objectRequirements.setParent(currentObject);
                    }
                    newObject->exec("LuaCore.InjectInitInjectionTable()");
                }
                else if (!this->getGameObject(currentObject->getId())->isPermanent())
                {
                    aube::ErrorHandler::Warn("ObEngine.Scene.Scene.GameObjectAlreadyInScene",
                        { { "object", currentObject->getId() }, { "mapfile", m_levelName } });
                }
            }
        }

        if (m_levelFile->contains(vili::NodeType::ComplexNode, "Script"))
        {
            vili::ComplexNode& script = m_levelFile.at("Script");
            if (script.contains(vili::NodeType::DataNode, "source"))
            {
                System::Path(script.at<vili::DataNode>("source"))
                    .load(System::Loaders::luaLoader, Script::ScriptEngine);
                m_scriptArray.push_back(script.at<vili::DataNode>("source"));
            }
            else if (script.contains(vili::NodeType::ArrayNode, "sources"))
            {
                for (vili::DataNode* scriptName : script.getArrayNode("sources"))
                {
                    System::Path(*scriptName)
                        .load(System::Loaders::luaLoader, Script::ScriptEngine);
                    m_scriptArray.push_back(*scriptName);
                }
            }
        }
        m_sceneTriggers->pushParameter("MapLoaded", "name", filename);
        m_sceneTriggers->trigger("MapLoaded");
    }

    void Scene::setFutureLoadFromFile(const std::string& filename)
    {
        m_futureLoad = filename;
    }

    void Scene::setFutureLoadFromFile(const std::string& filename, kaguya::LuaFunction callback)
    {
        m_futureLoad = filename;
        m_onLoadCallback = callback;
    }

    void Scene::clear()
    {
        for (auto& gameObject : m_gameObjectArray)
        {
            if (!gameObject->isPermanent())
            {
                Debug::Log->debug("<Scene> Deleting GameObject {0}", gameObject->getId());
                gameObject->deleteObject();
            }
        }
        Debug::Log->debug("<Scene> Cleaning GameObject Array");
        m_gameObjectArray.erase(std::remove_if(m_gameObjectArray.begin(), m_gameObjectArray.end(),
                                    [](const std::unique_ptr<Script::GameObject>& ptr) {
                                        return (!ptr->isPermanent());
                                    }),
            m_gameObjectArray.end());
        Debug::Log->debug("<Scene> Cleaning LevelSprite Array");
        m_spriteArray.erase(std::remove_if(m_spriteArray.begin(), m_spriteArray.end(),
                                [this](const std::unique_ptr<Graphics::LevelSprite>& ptr) {
                                    if (!ptr->getParentId().empty()
                                        && this->doesGameObjectExists(ptr->getParentId()))
                                        return false;
                                    return true;
                                }),
            m_spriteArray.end());
        Debug::Log->debug("<Scene> Cleaning LevelSprite Array");
        m_colliderArray.erase(std::remove_if(m_colliderArray.begin(), m_colliderArray.end(),
                                  [this](const std::unique_ptr<Collision::PolygonalCollider>& ptr) {
                                      if (!ptr->getParentId().empty()
                                          && this->doesGameObjectExists(ptr->getParentId()))
                                          return false;
                                      return true;
                                  }),
            m_colliderArray.end());
        Debug::Log->debug("<Scene> Clearing MapScript Array");
        m_scriptArray.clear();
        Debug::Log->debug("<Scene> Scene Cleared !");
    }

    vili::ViliParser* Scene::dump(bool saveCameraPosition)
    {
        vili::ViliParser* dataStore = new vili::ViliParser;
        dataStore->addFlag("Map");
        dataStore->addFlag("Lock");
        dataStore->includeFile("Obe");

        // Meta
        (*dataStore)->createComplexNode("Meta");
        dataStore->at("Meta").createDataNode("name", m_levelName);

        // View
        (*dataStore)->createComplexNode("View");
        dataStore->at("View").createDataNode("size", m_camera.getSize().y / 2);
        dataStore->at("View").createComplexNode("pos");
        dataStore->at("View", "pos")
            .createDataNode("unit", unitsToString(m_cameraInitialPosition.unit));
        if (!saveCameraPosition)
        {
            dataStore->at("View", "pos").createDataNode("x", m_cameraInitialPosition.x);
            dataStore->at("View", "pos").createDataNode("y", m_cameraInitialPosition.y);
        }
        else
        {
            dataStore->at("View", "pos").createDataNode("x", m_camera.getPosition().x);
            dataStore->at("View", "pos").createDataNode("y", m_camera.getPosition().y);
        }
        dataStore->at("View", "pos")
            .useTemplate(dataStore->getTemplate(
                "Vector2<" + Transform::unitsToString(m_cameraInitialPosition.unit) + ">"));
        dataStore->at("View").createComplexNode("referential");
        dataStore->at("View", "referential")
            .createDataNode("referential", m_cameraInitialReferential.toString("{}"));
        if (m_cameraInitialReferential.isKnown())
            dataStore->at("View", "referential")
                .useTemplate(dataStore->getTemplate(m_cameraInitialReferential.toString()));

        // LevelSprites
        if (m_spriteArray.size() > 0)
            (*dataStore)->createComplexNode("LevelSprites");
        for (unsigned int i = 0; i < m_spriteArray.size(); i++)
        {
            if (m_spriteArray[i]->getParentId() == "")
            {
                m_spriteArray[i]->dump(dataStore->at("LevelSprites"));
                dataStore->at("LevelSprites", m_spriteArray[i]->getId(), "rect")
                    .useTemplate(dataStore->getTemplate(
                        "Rect<" + unitsToString(m_spriteArray[i]->getWorkingUnit()) + ">"));
            }
        }
        if (m_colliderArray.size() > 0)
            (*dataStore)->createComplexNode("Collisions");
        for (unsigned int i = 0; i < m_colliderArray.size(); i++)
        {
            if (m_colliderArray[i]->getParentId() == "")
            {
                m_colliderArray[i]->dump(dataStore->at("Collisions"));
            }
        }
        if (m_gameObjectArray.size() > 0)
            (*dataStore)->createComplexNode("GameObjects");
        for (auto& gameObject : m_gameObjectArray)
        {
            dataStore->at("GameObjects").createComplexNode(gameObject->getId());
            dataStore->at("GameObjects", gameObject->getId())
                .createDataNode("type", gameObject->getType());

            if (auto dumpFunction = gameObject->access()["Dump"])
            {
                kaguya::LuaRef saveTableRef = dumpFunction();
                vili::ComplexNode* saveRequirements
                    = Script::DataBridge::luaTableToComplexNode("Requires", saveTableRef);
                if (saveRequirements->getAll().size() > 0)
                    dataStore->at("GameObjects", gameObject->getId())
                        .pushComplexNode(saveRequirements);
            }
        }
        if (m_scriptArray.size() > 0)
        {
            (*dataStore)->createComplexNode("Script");
            if (m_scriptArray.size() == 1)
            {
                dataStore->at("Script").createDataNode("source", m_scriptArray[0]);
            }
            else
            {
                dataStore->at("Script").createArrayNode("sources");
                for (int i = 0; i < m_scriptArray.size(); i++)
                {
                    dataStore->at("Script").getArrayNode("sources").push(m_scriptArray[i]);
                }
            }
        }
        return dataStore;
    }

    void Scene::update()
    {
        if (m_futureLoad != "")
        {
            std::string futureLoadBuffer = std::move(m_futureLoad);
            this->loadFromFile(futureLoadBuffer);
            if (!m_onLoadCallback.isNilref())
                m_onLoadCallback(futureLoadBuffer);
        }
        if (m_updateState)
        {
            size_t arraySize = m_gameObjectArray.size();
            for (size_t i = 0; i < arraySize; i++)
            {
                Script::GameObject& gameObject = *m_gameObjectArray[i];
                if (!gameObject.deletable)
                    gameObject.update();
            }
            m_gameObjectArray.erase(
                std::remove_if(m_gameObjectArray.begin(), m_gameObjectArray.end(),
                    [this](const std::unique_ptr<Script::GameObject>& ptr) {
                        if (ptr->deletable)
                        {
                            Debug::Log->debug("<Scene> Removing GameObject {}", ptr->getId());
                            if (ptr->m_sprite)
                                this->removeLevelSprite(ptr->getLevelSprite()->getId());
                            if (ptr->m_collider)
                                this->removeCollider(ptr->getCollider()->getId());
                            return true;
                        }
                        return false;
                    }),
                m_gameObjectArray.end());
        }
    }

    void Scene::draw()
    {
        for (auto it = m_spriteArray.begin(); it != m_spriteArray.end(); ++it)
        {
            if (it->get()->m_layerChanged)
            {
                for (auto it2 = it; it2 != m_spriteArray.end(); ++it2)
                {
                    it2->get()->m_layerChanged = false;
                }
                this->reorganizeLayers();
                break;
            }
        }

        Transform::UnitVector pixelCamera
            = m_camera.getPosition().to<Transform::Units::ScenePixels>();
        for (unsigned int i = 0; i < m_spriteArray.size(); i++)
        {
            if (m_spriteArray[i]->isVisible())
            {
                m_spriteArray[i]->draw(pixelCamera);
            }
        }

        if (m_showElements["CollisionLines"] || m_showElements["CollisionPoints"]
            || m_showElements["CollisionMasterPoint"] || m_showElements["CollisionSkeleton"])
        {
            for (unsigned int i = 0; i < m_colliderArray.size(); i++)
            {
                m_colliderArray[i]->draw(m_camera, m_showElements["CollisionLines"],
                    m_showElements["CollisionPoints"], m_showElements["CollisionMasterPoint"],
                    m_showElements["CollisionSkeleton"]);
            }
        }
        if (m_showElements["SceneNodes"])
        {
            for (auto& gameObject : m_gameObjectArray)
            {
                sf::CircleShape sceneNodeRepr;
                SceneNode* sceneNode = gameObject->getSceneNode();
                Transform::UnitVector sceneNodePosition
                    = sceneNode->getPosition().to<Transform::Units::ViewPixels>();
                sceneNodeRepr.setPosition(sceneNodePosition.x - 3, sceneNodePosition.y - 3);
                if (sceneNode->isSelected())
                    sceneNodeRepr.setFillColor(sf::Color::Green);
                else
                    sceneNodeRepr.setFillColor(sf::Color::Red);
                sceneNodeRepr.setOutlineColor(sf::Color::Black);
                sceneNodeRepr.setOutlineThickness(2);
                sceneNodeRepr.setRadius(6);
                System::MainWindow.draw(sceneNodeRepr);
            }
        }
    }

    std::string Scene::getLevelName() const
    {
        return m_levelName;
    }

    void Scene::setLevelName(const std::string& newName)
    {
        m_levelName = newName;
    }

    std::vector<Collision::PolygonalCollider*> Scene::getAllColliders() const
    {
        std::vector<Collision::PolygonalCollider*> allColliders;
        for (auto& collider : m_colliderArray)
            allColliders.push_back(collider.get());
        return allColliders;
    }

    Camera* Scene::getCamera()
    {
        return &m_camera;
    }

    void Scene::setUpdateState(bool state)
    {
        m_updateState = state;
        for (auto& gameObject : m_gameObjectArray)
        {
            gameObject->setState(state);
        }
    }

    Script::GameObject* Scene::getGameObject(const std::string& id)
    {
        for (auto& gameObject : m_gameObjectArray)
        {
            if (gameObject->getId() == id)
                return gameObject.get();
        }
        throw aube::ErrorHandler::Raise(
            "ObEngine.Scene.Scene.UnknownGameObject", { { "id", id }, { "map", m_levelName } });
    }

    bool Scene::doesGameObjectExists(const std::string& id)
    {
        for (auto& gameObject : m_gameObjectArray)
        {
            if (gameObject->getId() == id)
                return true;
        }
        return false;
    }

    void Scene::removeGameObject(const std::string& id)
    {
        m_gameObjectArray.erase(std::remove_if(m_gameObjectArray.begin(), m_gameObjectArray.end(),
                                    [&id](const std::unique_ptr<Script::GameObject>& ptr) {
                                        return (ptr->getId() == id);
                                    }),
            m_gameObjectArray.end());
    }

    std::vector<Script::GameObject*> Scene::getAllGameObjects()
    {
        std::vector<Script::GameObject*> returnVec;
        for (auto& gameObject : m_gameObjectArray)
        {
            returnVec.push_back(gameObject.get());
        }
        return returnVec;
    }

    Script::GameObject* Scene::createGameObject(const std::string& obj, const std::string& id)
    {
        std::string useId = id;
        if (useId.empty())
        {
            while (useId.empty() || this->doesGameObjectExists(useId))
            {
                useId = Utils::String::getRandomKey(
                    Utils::String::Alphabet + Utils::String::Numbers, 8);
            }
        }
        else if (this->doesGameObjectExists(useId))
        {
            aube::ErrorHandler::Warn("ObEngine.Scene.Scene.OverridedObject",
                { { "id", id }, { "mapfile", m_levelName } });
        }

        std::unique_ptr<Script::GameObject> newGameObject
            = std::make_unique<Script::GameObject>(obj, useId);
        vili::ComplexNode& gameObjectData
            = *Script::GameObjectDatabase::GetDefinitionForGameObject(obj);
        newGameObject->loadGameObject(*this, gameObjectData);

        if (newGameObject->doesHaveLevelSprite())
        {
            const Transform::UnitVector zero(0, 0);
            newGameObject->getLevelSprite()->setPosition(zero);
            newGameObject->getLevelSprite()->setParentId(useId);
        }

        if (newGameObject->doesHaveCollider())
        {
            newGameObject->getCollider()->setParentId(useId);
        }

        m_gameObjectArray.push_back(move(newGameObject));

        return m_gameObjectArray.back().get();
    }

    unsigned Scene::getGameObjectAmount() const
    {
        return m_gameObjectArray.size();
    }

    void Scene::reorganizeLayers()
    {
        std::sort(m_spriteArray.begin(), m_spriteArray.end(), [](auto& sprite1, auto& sprite2) {
            if (sprite1->getLayer() == sprite2->getLayer())
            {
                return sprite1->getZDepth() > sprite2->getZDepth();
            }
            else
            {
                return sprite1->getLayer() > sprite2->getLayer();
            }
        });
    }

    unsigned int Scene::getLevelSpriteAmount() const
    {
        return m_spriteArray.size();
    }

    std::vector<Graphics::LevelSprite*> Scene::getAllLevelSprites()
    {
        std::vector<Graphics::LevelSprite*> allSprites;
        for (int i = 0; i < m_spriteArray.size(); i++)
            allSprites.push_back(m_spriteArray[i].get());
        return allSprites;
    }

    std::vector<Graphics::LevelSprite*> Scene::getLevelSpritesByLayer(const int layer)
    {
        std::vector<Graphics::LevelSprite*> returnLayer;

        for (unsigned int i = 0; i < m_spriteArray.size(); i++)
        {
            if (m_spriteArray[i]->getLayer() == layer)
                returnLayer.push_back(m_spriteArray[i].get());
        }

        return returnLayer;
    }

    Graphics::LevelSprite* Scene::getLevelSpriteByPosition(
        const Transform::UnitVector& position, const Transform::UnitVector& camera, const int layer)
    {
        Graphics::LevelSprite* returnSpr = nullptr;
        std::vector<Transform::Referential> rectPts
            = { Transform::Referential::TopLeft, Transform::Referential::TopRight,
                  Transform::Referential::BottomRight, Transform::Referential::BottomLeft };
        const Transform::UnitVector zeroOffset(0, 0);

        std::vector<Graphics::LevelSprite*> getSpriteVec = this->getLevelSpritesByLayer(layer);
        for (unsigned int i = 0; i < getSpriteVec.size(); i++)
        {
            Collision::PolygonalCollider positionCollider("positionCollider");
            positionCollider.addPoint(
                getSpriteVec[i]->getPositionTransformer()(position, camera, layer));
            Collision::PolygonalCollider sprCollider("sprCollider");
            for (Transform::Referential& ref : rectPts)
            {
                sprCollider.addPoint(getSpriteVec[i]->getPosition(ref));
            }
            if (sprCollider.doesCollide(positionCollider, zeroOffset))
            {
                returnSpr = getSpriteVec[i];
            }
        }
        return returnSpr;
    }

    Graphics::LevelSprite* Scene::getLevelSprite(const std::string& id)
    {
        for (int i = 0; i < m_spriteArray.size(); i++)
        {
            if (m_spriteArray[i].get()->getId() == id)
                return m_spriteArray[i].get();
        }
        throw aube::ErrorHandler::Raise(
            "ObEngine.Scene.Scene.UnknownLevelSprite", { { "id", id }, { "map", m_levelName } });
    }

    bool Scene::doesLevelSpriteExists(const std::string& id)
    {
        for (int i = 0; i < m_spriteArray.size(); i++)
        {
            if (m_spriteArray[i].get()->getId() == id)
                return true;
        }
        return false;
    }

    void Scene::removeLevelSprite(const std::string& id)
    {
        Debug::Log->debug("<Scene> Removing LevelSprite {0}", id);
        m_spriteArray.erase(std::remove_if(m_spriteArray.begin(), m_spriteArray.end(),
                                [&id](std::unique_ptr<Graphics::LevelSprite>& levelSprite) {
                                    return (levelSprite->getId() == id);
                                }),
            m_spriteArray.end());
    }

    void Scene::enableShowCollision(const bool drawLines, const bool drawPoints,
        const bool drawMasterPoint, const bool drawSkel)
    {
        m_showElements["CollisionLines"] = drawLines;
        m_showElements["CollisionPoints"] = drawPoints;
        m_showElements["CollisionMasterPoint"] = drawMasterPoint;
        m_showElements["CollisionSkeleton"] = drawSkel;
    }

    void Scene::enableShowSceneNodes(bool showNodes)
    {
        m_showElements["SceneNodes"] = showNodes;
    }

    SceneNode* Scene::getSceneNodeByPosition(const Transform::UnitVector& position) const
    {
        for (auto& gameObject : m_gameObjectArray)
        {
            const Transform::UnitVector sceneNodePosition
                = gameObject->getSceneNode()->getPosition();
            const Transform::UnitVector pVec = position.to<Transform::Units::SceneUnits>();
            const Transform::UnitVector pTolerance
                = Transform::UnitVector(6, 6, Transform::Units::ScenePixels)
                      .to<Transform::Units::SceneUnits>();

            if (Utils::Math::isBetween(
                    pVec.x, sceneNodePosition.x - pTolerance.x, sceneNodePosition.x + pTolerance.x))
            {
                if (Utils::Math::isBetween(pVec.y, sceneNodePosition.y - pTolerance.x,
                        sceneNodePosition.y + pTolerance.y))
                    return gameObject->getSceneNode();
            }
        }
        return nullptr;
    }

    std::pair<Collision::PolygonalCollider*, int> Scene::getColliderPointByPosition(
        const Transform::UnitVector& position)
    {
        const Transform::UnitVector pPos = position.to<Transform::Units::ScenePixels>();
        const Transform::UnitVector pTolerance
            = Transform::UnitVector(6, 6, Transform::Units::ScenePixels);
        for (unsigned int i = 0; i < m_colliderArray.size(); i++)
        {
            // Fix here
            if (auto point = m_colliderArray[i]->getPointAroundPosition(pPos, pTolerance);
                point.has_value())
            {
                return std::pair<Collision::PolygonalCollider*, int>(
                    m_colliderArray[i].get(), point.value()->index);
            }
        }
        return std::pair<Collision::PolygonalCollider*, int>(nullptr, 0);
    }

    Collision::PolygonalCollider* Scene::getColliderByCentroidPosition(
        const Transform::UnitVector& position)
    {
        const Transform::UnitVector pPos = position.to<Transform::Units::ScenePixels>();
        const Transform::UnitVector pTolerance
            = Transform::UnitVector(6, 6, Transform::Units::ScenePixels);
        for (unsigned int i = 0; i < m_colliderArray.size(); i++)
        {
            if (m_colliderArray[i]->isCentroidAroundPosition(pPos, pTolerance))
                return m_colliderArray[i].get();
        }
        return nullptr;
    }

    Collision::PolygonalCollider* Scene::getCollider(const std::string& id)
    {
        for (unsigned int i = 0; i < m_colliderArray.size(); i++)
        {
            if (id == m_colliderArray[i]->getId())
            {
                return m_colliderArray[i].get();
            }
        }
        throw aube::ErrorHandler::Raise(
            "ObEngine.Scene.Scene.UnknownCollider", { { "id", id }, { "scene", m_levelName } });
    }

    bool Scene::doesColliderExists(const std::string& id)
    {
        for (auto& collider : m_colliderArray)
        {
            if (collider->getId() == id)
            {
                return true;
            }
        }
        return false;
    }

    void Scene::removeCollider(const std::string& id)
    {
        m_colliderArray.erase(std::remove_if(m_colliderArray.begin(), m_colliderArray.end(),
                                  [&id](std::unique_ptr<Collision::PolygonalCollider>& collider) {
                                      return (collider->getId() == id);
                                  }),
            m_colliderArray.end());
    }

    SceneNode& Scene::getSceneRootNode()
    {
        return m_sceneRoot;
    }

    std::string Scene::getLevelFile() const
    {
        return m_levelFileName;
    }
} // namespace obe::Scene