#include <Scene/Scene.hpp>
#include <Script/GlobalState.hpp>
#include <Script/ViliLuaBridge.hpp>
#include <System/Loaders.hpp>
#include <System/Window.hpp>
#include <Triggers/TriggerManager.hpp>
#include <Utils/MathUtils.hpp>
#include <Utils/StringUtils.hpp>

namespace obe::Scene
{
    Scene::Scene(Triggers::TriggerManager& triggers, sol::state_view lua)
        : m_lua(lua)
        , m_triggers(triggers)
        , t_scene(triggers.createTriggerGroup("Global", "Scene"))

    {
        triggers.createNamespace("Map"); // TODO: Add namespace handle
        m_showElements["SceneNodes"] = false;

        t_scene->add("Loaded");
    }

    void Scene::attachResourceManager(Engine::ResourceManager& resources)
    {
        m_resources = &resources;
    }

    Graphics::Sprite& Scene::createSprite(const std::string& id, bool addToSceneRoot)
    {
        std::string createId = id;
        if (createId.empty())
        {
            int i = 0;
            std::string testId = "sprite" + std::to_string(this->getColliderAmount() + i);
            while (this->doesSpriteExists(testId))
            {
                testId = "sprite" + std::to_string(this->getSpriteAmount() + i++);
            }
            createId = testId;
        }
        if (!this->doesSpriteExists(createId))
        {
            std::unique_ptr<Graphics::Sprite> newSprite
                = std::make_unique<Graphics::Sprite>(createId);
            if (m_resources)
                newSprite->attachResourceManager(*m_resources);

            Graphics::Sprite* returnSprite = newSprite.get();
            m_spriteArray.push_back(move(newSprite));

            if (addToSceneRoot)
                m_sceneRoot.addChild(*returnSprite);

            this->reorganizeLayers();
            return *returnSprite;
        }
        else
        {
            Debug::Log->warn("<Scene> Sprite '{0}' already exists !", createId);
            return this->getSprite(createId);
        }
    }

    Collision::PolygonalCollider& Scene::createCollider(
        const std::string& id, bool addToSceneRoot)
    {
        std::string createId = id;
        if (createId.empty())
        {
            int i = 0;
            std::string testId
                = "collider" + std::to_string(this->getColliderAmount() + i);
            while (this->doesColliderExists(testId))
            {
                testId = "collider" + std::to_string(this->getColliderAmount() + i++);
            }
            createId = testId;
        }
        if (!this->doesColliderExists(createId))
        {
            m_colliderArray.push_back(
                std::make_unique<Collision::PolygonalCollider>(createId));
            if (addToSceneRoot)
                m_sceneRoot.addChild(*m_colliderArray.back());
            return *m_colliderArray.back().get();
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

    void Scene::reload(const OnSceneLoadCallback& callback)
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
            throw aube::ErrorHandler::Raise(
                "ObEngine.Scene.Scene.NoMeta", { { "map", filename } });

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
            if (m_levelFile->at("View").contains(
                    vili::NodeType::ComplexNode, "referential"))
            {
                m_cameraInitialReferential = Transform::Referential::FromString(
                    m_levelFile->at("View", "referential")
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
            throw aube::ErrorHandler::Raise(
                "ObEngine.Scene.Scene.NoView", { { "map", filename } });

        if (m_levelFile->contains(vili::NodeType::ComplexNode, "Sprites"))
        {
            vili::ComplexNode& Sprites = m_levelFile.at("Sprites");

            for (vili::ComplexNode* currentSprite : Sprites.getAll<vili::ComplexNode>())
            {
                this->createSprite(currentSprite->getId()).load(*currentSprite);
            }
        }

        this->reorganizeLayers();

        if (m_levelFile->contains(vili::NodeType::ComplexNode, "Collisions"))
        {
            vili::ComplexNode& collisions = m_levelFile.at("Collisions");
            for (vili::ComplexNode* currentCollision :
                collisions.getAll<vili::ComplexNode>())
            {
                this->createCollider(currentCollision->getId()).load(*currentCollision);
            }
        }

        if (m_levelFile->contains(vili::NodeType::ComplexNode, "GameObjects"))
        {
            vili::ComplexNode& gameObjects = m_levelFile.at("GameObjects");
            for (vili::ComplexNode* currentObject :
                gameObjects.getAll<vili::ComplexNode>())
            {
                if (!this->doesGameObjectExists(currentObject->getId()))
                {
                    const std::string gameObjectType
                        = currentObject->getDataNode("type").get<std::string>();
                    Script::GameObject& newObject
                        = this->createGameObject(gameObjectType, currentObject->getId());
                    if (currentObject->contains(vili::NodeType::ComplexNode, "Requires"))
                    {
                        vili::ComplexNode& objectRequirements
                            = currentObject->at("Requires");
                        currentObject->removeOwnership(&objectRequirements);
                        Script::GameObjectDatabase::ApplyRequirements(
                            newObject.getEnvironment(), objectRequirements);
                        objectRequirements.setParent(currentObject);
                    }
                    newObject.exec("LuaCore.InjectInitInjectionTable()");
                }
                else if (!this->getGameObject(currentObject->getId()).isPermanent())
                {
                    aube::ErrorHandler::Warn(
                        "ObEngine.Scene.Scene.GameObjectAlreadyInScene",
                        { { "object", currentObject->getId() },
                            { "scene_file", m_levelName } });
                }
            }
        }

        if (m_levelFile->contains(vili::NodeType::ComplexNode, "Script"))
        {
            vili::ComplexNode& script = m_levelFile.at("Script");
            if (script.contains(vili::NodeType::DataNode, "source"))
            {
                m_lua.script_file(
                    System::Path(script.at<vili::DataNode>("source")).find());
                m_scriptArray.push_back(script.at<vili::DataNode>("source"));
            }
            else if (script.contains(vili::NodeType::ArrayNode, "sources"))
            {
                for (vili::DataNode* scriptName : script.getArrayNode("sources"))
                {
                    m_lua.script_file(System::Path(*scriptName).find());
                    m_scriptArray.push_back(*scriptName);
                }
            }
        }
        t_scene->pushParameter("Loaded", "name", filename);
        t_scene->trigger("Loaded");
    }

    void Scene::setFutureLoadFromFile(const std::string& filename)
    {
        m_futureLoad = filename;
    }

    void Scene::setFutureLoadFromFile(
        const std::string& filename, const OnSceneLoadCallback& callback)
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
        m_gameObjectArray.erase(
            std::remove_if(m_gameObjectArray.begin(), m_gameObjectArray.end(),
                [](const std::unique_ptr<Script::GameObject>& ptr) {
                    return (!ptr->isPermanent());
                }),
            m_gameObjectArray.end());
        Debug::Log->debug("<Scene> Cleaning Sprite Array");
        m_spriteArray.erase(std::remove_if(m_spriteArray.begin(), m_spriteArray.end(),
                                [this](const std::unique_ptr<Graphics::Sprite>& ptr) {
                                    if (!ptr->getParentId().empty()
                                        && this->doesGameObjectExists(ptr->getParentId()))
                                        return false;
                                    return true;
                                }),
            m_spriteArray.end());
        Debug::Log->debug("<Scene> Cleaning Sprite Array");
        m_colliderArray.erase(
            std::remove_if(m_colliderArray.begin(), m_colliderArray.end(),
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

    vili::ViliParser Scene::dump(bool saveCameraPosition)
    {
        vili::ViliParser dataStore;
        dataStore.addFlag("Map");
        dataStore.addFlag("Lock");
        dataStore.includeFile("Obe");

        // Meta
        dataStore->createComplexNode("Meta");
        dataStore.at("Meta").createDataNode("name", m_levelName);

        // View
        dataStore->createComplexNode("View");
        dataStore.at("View").createDataNode("size", m_camera.getSize().y / 2);
        dataStore.at("View").createComplexNode("pos");
        dataStore.at("View", "pos")
            .createDataNode("unit", unitsToString(m_cameraInitialPosition.unit));
        if (!saveCameraPosition)
        {
            dataStore.at("View", "pos").createDataNode("x", m_cameraInitialPosition.x);
            dataStore.at("View", "pos").createDataNode("y", m_cameraInitialPosition.y);
        }
        else
        {
            dataStore.at("View", "pos").createDataNode("x", m_camera.getPosition().x);
            dataStore.at("View", "pos").createDataNode("y", m_camera.getPosition().y);
        }
        dataStore->at("View", "pos")
            .useTemplate(dataStore.getTemplate("Vector2<"
                + Transform::unitsToString(m_cameraInitialPosition.unit) + ">"));
        dataStore.at("View").createComplexNode("referential");
        dataStore.at("View", "referential")
            .createDataNode("referential", m_cameraInitialReferential.toString("{}"));
        if (m_cameraInitialReferential.isKnown())
            dataStore.at("View", "referential")
                .useTemplate(
                    dataStore.getTemplate(m_cameraInitialReferential.toString()));

        // Sprites
        if (m_spriteArray.size() > 0)
            dataStore->createComplexNode("Sprites");
        for (unsigned int i = 0; i < m_spriteArray.size(); i++)
        {
            if (m_spriteArray[i]->getParentId() == "")
            {
                m_spriteArray[i]->dump(dataStore.at("Sprites"));
                dataStore.at("Sprites", m_spriteArray[i]->getId(), "rect")
                    .useTemplate(dataStore.getTemplate("Rect<"
                        + unitsToString(m_spriteArray[i]->getWorkingUnit()) + ">"));
            }
        }
        if (m_colliderArray.size() > 0)
            dataStore->createComplexNode("Collisions");
        for (unsigned int i = 0; i < m_colliderArray.size(); i++)
        {
            if (m_colliderArray[i]->getParentId() == "")
            {
                m_colliderArray[i]->dump(dataStore.at("Collisions"));
            }
        }
        if (m_gameObjectArray.size() > 0)
            dataStore->createComplexNode("GameObjects");
        for (auto& gameObject : m_gameObjectArray)
        {
            dataStore.at("GameObjects").createComplexNode(gameObject->getId());
            dataStore.at("GameObjects", gameObject->getId())
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
            dataStore->createComplexNode("Script");
            if (m_scriptArray.size() == 1)
            {
                dataStore.at("Script").createDataNode("source", m_scriptArray[0]);
            }
            else
            {
                dataStore.at("Script").createArrayNode("sources");
                for (int i = 0; i < m_scriptArray.size(); i++)
                {
                    dataStore.at("Script").getArrayNode("sources").push(m_scriptArray[i]);
                }
            }
        }
        return dataStore;
    }

    void Scene::update()
    {
        if (m_futureLoad != "")
        {
            const std::string futureLoadBuffer = std::move(m_futureLoad);
            this->loadFromFile(futureLoadBuffer);
            if (m_onLoadCallback)
                m_onLoadCallback(futureLoadBuffer);
        }
        if (m_updateState)
        {
            const size_t arraySize = m_gameObjectArray.size();
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
                            Debug::Log->debug(
                                "<Scene> Removing GameObject {}", ptr->getId());
                            if (ptr->m_sprite)
                                this->removeSprite(ptr->getSprite().getId());
                            if (ptr->m_collider)
                                this->removeCollider(ptr->getCollider().getId());
                            return true;
                        }
                        return false;
                    }),
                m_gameObjectArray.end());
        }
    }

    void Scene::draw(sf::RenderTarget& surface)
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

        const Transform::UnitVector pixelCamera
            = m_camera.getPosition().to<Transform::Units::ScenePixels>();
        for (unsigned int i = 0; i < m_spriteArray.size(); i++)
        {
            if (m_spriteArray[i]->isVisible())
            {
                m_spriteArray[i]->draw(surface, pixelCamera);
            }
        }

        if (m_showElements["SceneNodes"])
        {
            for (auto& gameObject : m_gameObjectArray)
            {
                sf::CircleShape sceneNodeCircle;
                SceneNode& sceneNode = gameObject->getSceneNode();
                const Transform::UnitVector sceneNodePosition
                    = sceneNode.getPosition().to<Transform::Units::ViewPixels>();
                sceneNodeCircle.setPosition(
                    sceneNodePosition.x - 3, sceneNodePosition.y - 3);
                if (sceneNode.isSelected())
                    sceneNodeCircle.setFillColor(sf::Color::Green);
                else
                    sceneNodeCircle.setFillColor(sf::Color::Red);
                sceneNodeCircle.setOutlineColor(sf::Color::Black);
                sceneNodeCircle.setOutlineThickness(2);
                sceneNodeCircle.setRadius(6);
                surface.draw(sceneNodeCircle);
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

    Camera& Scene::getCamera()
    {
        return m_camera;
    }

    void Scene::setUpdateState(bool state)
    {
        m_updateState = state;
        for (auto& gameObject : m_gameObjectArray)
        {
            gameObject->setState(state);
        }
    }

    Script::GameObject& Scene::getGameObject(const std::string& id)
    {
        for (auto& gameObject : m_gameObjectArray)
        {
            if (gameObject->getId() == id)
                return *gameObject.get();
        }
        throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.UnknownGameObject",
            { { "id", id }, { "map", m_levelName } });
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
        m_gameObjectArray.erase(
            std::remove_if(m_gameObjectArray.begin(), m_gameObjectArray.end(),
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

    Script::GameObject& Scene::createGameObject(
        const std::string& obj, const std::string& id)
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
            aube::ErrorHandler::Warn("ObEngine.Scene.Scene.OverridenObject",
                { { "id", id }, { "scene_file", m_levelName } });
        }

        std::unique_ptr<Script::GameObject> newGameObject
            = std::make_unique<Script::GameObject>(m_triggers, m_lua, obj, useId);
        vili::ComplexNode& gameObjectData
            = *Script::GameObjectDatabase::GetDefinitionForGameObject(obj);
        newGameObject->loadGameObject(*this, gameObjectData, m_resources);

        if (newGameObject->doesHaveSprite())
        {
            const Transform::UnitVector zero(0, 0);
            newGameObject->getSprite().setPosition(zero);
            newGameObject->getSprite().setParentId(useId);
        }

        if (newGameObject->doesHaveCollider())
        {
            newGameObject->getCollider().setParentId(useId);
        }

        m_gameObjectArray.push_back(move(newGameObject));

        return *m_gameObjectArray.back().get();
    }

    unsigned Scene::getGameObjectAmount() const
    {
        return m_gameObjectArray.size();
    }

    void Scene::reorganizeLayers()
    {
        std::sort(
            m_spriteArray.begin(), m_spriteArray.end(), [](auto& sprite1, auto& sprite2) {
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

    unsigned int Scene::getSpriteAmount() const
    {
        return m_spriteArray.size();
    }

    std::vector<Graphics::Sprite*> Scene::getAllSprites()
    {
        std::vector<Graphics::Sprite*> allSprites;
        for (int i = 0; i < m_spriteArray.size(); i++)
            allSprites.push_back(m_spriteArray[i].get());
        return allSprites;
    }

    std::vector<Graphics::Sprite*> Scene::getSpritesByLayer(const int layer)
    {
        std::vector<Graphics::Sprite*> returnLayer;

        for (unsigned int i = 0; i < m_spriteArray.size(); i++)
        {
            if (m_spriteArray[i]->getLayer() == layer)
                returnLayer.push_back(m_spriteArray[i].get());
        }

        return returnLayer;
    }

    Graphics::Sprite* Scene::getSpriteByPosition(const Transform::UnitVector& position,
        const Transform::UnitVector& camera, const int layer)
    {
        std::vector<Transform::Referential> rectPts = { Transform::Referential::TopLeft,
            Transform::Referential::TopRight, Transform::Referential::BottomRight,
            Transform::Referential::BottomLeft };
        const Transform::UnitVector zeroOffset(0, 0);

        std::vector<Graphics::Sprite*> getSpriteVec = this->getSpritesByLayer(layer);
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
                return getSpriteVec[i];
            }
        }
        return nullptr;
    }

    Graphics::Sprite& Scene::getSprite(const std::string& id)
    {
        for (int i = 0; i < m_spriteArray.size(); i++)
        {
            if (m_spriteArray[i].get()->getId() == id)
                return *m_spriteArray[i].get();
        }
        throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.UnknownSprite",
            { { "id", id }, { "map", m_levelName } });
    }

    bool Scene::doesSpriteExists(const std::string& id)
    {
        for (int i = 0; i < m_spriteArray.size(); i++)
        {
            if (m_spriteArray[i].get()->getId() == id)
                return true;
        }
        return false;
    }

    void Scene::removeSprite(const std::string& id)
    {
        Debug::Log->debug("<Scene> Removing Sprite {0}", id);
        m_spriteArray.erase(std::remove_if(m_spriteArray.begin(), m_spriteArray.end(),
                                [&id](std::unique_ptr<Graphics::Sprite>& Sprite) {
                                    return (Sprite->getId() == id);
                                }),
            m_spriteArray.end());
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
                = gameObject->getSceneNode().getPosition();
            const Transform::UnitVector pVec
                = position.to<Transform::Units::SceneUnits>();
            const Transform::UnitVector pTolerance
                = Transform::UnitVector(6, 6, Transform::Units::ScenePixels)
                      .to<Transform::Units::SceneUnits>();

            if (Utils::Math::isBetween(pVec.x, sceneNodePosition.x - pTolerance.x,
                    sceneNodePosition.x + pTolerance.x))
            {
                if (Utils::Math::isBetween(pVec.y, sceneNodePosition.y - pTolerance.x,
                        sceneNodePosition.y + pTolerance.y))
                    return &gameObject->getSceneNode();
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

    Collision::PolygonalCollider& Scene::getCollider(const std::string& id)
    {
        for (unsigned int i = 0; i < m_colliderArray.size(); i++)
        {
            if (id == m_colliderArray[i]->getId())
            {
                return *m_colliderArray[i].get();
            }
        }
        throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.UnknownCollider",
            { { "id", id }, { "scene", m_levelName } });
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
        m_colliderArray.erase(
            std::remove_if(m_colliderArray.begin(), m_colliderArray.end(),
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