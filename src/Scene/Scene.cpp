#include <Bindings/Bindings.hpp>
#include <Scene/Scene.hpp>
#include <Script/GlobalState.hpp>
#include <Script/Script.hpp>
#include <Script/ViliLuaBridge.hpp>
#include <System/Loaders.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Scene
    {
        Scene::Scene()
        {
            loadWorldScriptEngineBaseLib(&Script::ScriptEngine);
            Script::ScriptEngine["Scene"] = this;
            System::Path("Lib/Internal/SceneInit.lua").loadResource(&Script::ScriptEngine, System::Loaders::luaLoader);
            Triggers::TriggerDatabase::GetInstance()->createNamespace("Map");
            m_showCollisionModes["drawLines"] = false;
            m_showCollisionModes["drawPoints"] = false;
            m_showCollisionModes["drawMasterPoint"] = false;
            m_showCollisionModes["drawSkel"] = false;
        }

        Scene::~Scene()
        {
            Triggers::TriggerDatabase::GetInstance()->removeNamespace("Map");
        }

        Graphics::LevelSprite* Scene::createLevelSprite(const std::string& id)
        {
            if (!this->doesLevelSpriteExists(id))
            {
                std::unique_ptr<Graphics::LevelSprite> newLevelSprite = std::make_unique<Graphics::LevelSprite>(id);

                Graphics::LevelSprite* returnLevelSprite = newLevelSprite.get();
                m_spriteArray.push_back(move(newLevelSprite));

                this->reorganizeLayers();
                return returnLevelSprite;
            }
            else
            {
                throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.SpriteAlreadyExists", { {"id", id}, {"mapfile", m_levelName} });
            }
        }

        Collision::PolygonalCollider* Scene::createCollider(const std::string& id)
        {
            if (!this->doesColliderExists(id))
            {
                std::unique_ptr<Collision::PolygonalCollider> newCollider = std::make_unique<Collision::PolygonalCollider>(id);
                Collision::PolygonalCollider* returnCollider = newCollider.get();
                m_colliderArray.push_back(move(newCollider));
                return returnCollider;
            }
            else
            {
                throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.ColliderAlreadyExists", { {"id", id}, {"mapfile", m_levelName} });
            }
        }

        unsigned Scene::getColliderAmount() const
        {
            return m_colliderArray.size();
        }

        std::string Scene::getBaseFolder() const
        {
            return m_baseFolder;
        }

        void Scene::loadFromFile(const std::string& filename)
        {
            this->clearWorld();
            vili::ViliParser mapParse;
            m_baseFolder = System::Path("Data/Maps").add(filename).loadResource(&mapParse, System::Loaders::dataLoader);
            std::cout << "Base Folder : " << m_baseFolder << std::endl;

            if (mapParse->contains(vili::NodeType::ComplexNode, "Meta"))
            {
                vili::ComplexNode& meta = mapParse.at("Meta");
                m_levelName = meta.getDataNode("name").get<std::string>();
            }
            else
                throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.NoMeta", {{"map", filename}});

            if (mapParse->contains(vili::NodeType::ComplexNode, "View"))
            {
                vili::ComplexNode& view = mapParse.at("View");
                m_camera.setSize(view.at<vili::DataNode>("size").get<double>());
                m_cameraInitialPosition = Transform::UnitVector(
                    view.at<vili::DataNode>("pos", "x").get<double>(),
                    view.at<vili::DataNode>("pos", "y").get<double>(),
                    Transform::stringToUnits(view.at<vili::DataNode>("pos", "unit").get<std::string>()));
                m_cameraInitialReferencial = Transform::Referencial::Center;
                if (mapParse->at("View").contains(vili::NodeType::ComplexNode, "referencial"))
                {
                    m_cameraInitialReferencial = Transform::stringToReferencial(
                        mapParse->at("View", "referencial").getDataNode("referencial").get<std::string>()
                    );
                }
                m_camera.setPosition(m_cameraInitialPosition, m_cameraInitialReferencial);
            }
            else
                throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.NoView", {{"map", filename}});

            if (mapParse->contains(vili::NodeType::ComplexNode, "LevelSprites"))
            {
                vili::ComplexNode& levelSprites = mapParse.at("LevelSprites");

                for (std::string& currentSpriteName : levelSprites.getAll(vili::NodeType::ComplexNode))
                {
                    this->createLevelSprite(currentSpriteName)->configure(levelSprites.at(currentSpriteName));
                }
            }

            this->reorganizeLayers();

            if (mapParse->contains(vili::NodeType::ComplexNode, "Collisions"))
            {
                vili::ComplexNode& collisions = mapParse.at("Collisions");
                for (std::string& collisionName : collisions.getAll(vili::NodeType::ComplexNode))
                {
                    vili::ComplexNode& currentCollision = collisions.at(collisionName);
                    std::cout << "New Collider : " << collisionName << std::endl;
                    std::unique_ptr<Collision::PolygonalCollider> tempCollider = std::make_unique<Collision::PolygonalCollider>(collisionName);

                    std::string pointsUnit = currentCollision.at<vili::DataNode>("unit", "unit").get<std::string>();
                    bool completePoint = true;
                    double pointBuffer = 0;
                    Transform::Units pBaseUnit = Transform::stringToUnits(pointsUnit);
                    for (vili::DataNode* colliderPoint : currentCollision.getArrayNode("points"))
                    {
                        if ((completePoint = !completePoint))
                        {
                            Transform::UnitVector pVector2 = Transform::UnitVector(
                                pointBuffer,
                                colliderPoint->get<double>(),
                                pBaseUnit
                            );
                            std::cout << "Add Vector Pt : " << pVector2 << std::endl;
                            tempCollider->addPoint(pVector2);
                        }
                        else
                            pointBuffer = colliderPoint->get<double>();
                    }
                    tempCollider->setWorkingUnit(pBaseUnit);
                    m_colliderArray.push_back(move(tempCollider));
                }
            }

            if (mapParse->contains(vili::NodeType::ComplexNode, "GameObjects"))
            {
                vili::ComplexNode& gameObjects = mapParse.at("GameObjects");
                for (std::string& currentObjectName : gameObjects.getAll(vili::NodeType::ComplexNode))
                {
                    if (!this->doesGameObjectExists(currentObjectName))
                    {
                        vili::ComplexNode& currentObject = gameObjects.at(currentObjectName);
                        std::string gameObjectType = currentObject.getDataNode("type").get<std::string>();
                        Script::GameObject* newObject = this->createGameObject(gameObjectType, currentObjectName);
                        if (currentObject.contains(vili::NodeType::ComplexNode, "Requires"))
                        {
                            vili::ComplexNode& objectRequirements = currentObject.at("Requires");
                            currentObject.removeOwnership(&objectRequirements);
                            Script::GameObjectDatabase::ApplyRequirements(newObject, objectRequirements);
                            objectRequirements.setParent(&currentObject);
                        }
                        newObject->exec("LuaCore.InjectInitInjectionTable()");
                        newObject->initialize();
                    }
                    else if (!this->getGameObject(currentObjectName)->isPermanent())
                    {
                        aube::ErrorHandler::Warn("ObEngine.Scene.Scene.GameObjectAlreadyInScene", {{"object", currentObjectName}, {"mapfile", m_levelName}});
                    }
                }
            }

            if (mapParse->contains(vili::NodeType::ComplexNode, "Script"))
            {
                vili::ComplexNode& script = mapParse.at("Script");
                for (vili::DataNode* scriptName : script.getArrayNode("gameScripts"))
                {
                    System::Path(*scriptName).loadResource(&Script::ScriptEngine, System::Loaders::luaLoader);
                    m_scriptArray.push_back(*scriptName);
                }
            }
        }

        void Scene::setFutureLoadFromFile(const std::string& filename)
        {
            m_futureLoad = filename;
        }

        void Scene::clearWorld()
        {
            for (auto& gameObject : m_gameObjectArray)
            {
                if (!gameObject->isPermanent())
                {
                    gameObject->deleteObject();
                }
            }
            m_gameObjectArray.erase(std::remove_if(m_gameObjectArray.begin(), m_gameObjectArray.end(), 
            [](const std::unique_ptr<Script::GameObject>& ptr){
                return (!ptr->isPermanent());
            }), m_gameObjectArray.end());
            m_spriteArray.erase(std::remove_if(m_spriteArray.begin(), m_spriteArray.end(), 
            [this](const std::unique_ptr<Graphics::LevelSprite>& ptr){
                if (!ptr->getParentId().empty() && this->doesGameObjectExists(ptr->getParentId()))
                    return false;
                return true;
            }), m_spriteArray.end());
            m_colliderArray.erase(std::remove_if(m_colliderArray.begin(), m_colliderArray.end(), 
            [this](const std::unique_ptr<Collision::PolygonalCollider>& ptr){
                if (!ptr->getParentId().empty() && this->doesGameObjectExists(ptr->getParentId()))
                    return false;
                return true;
            }), m_colliderArray.end());
            m_scriptArray.clear();
        }

        vili::ViliParser* Scene::dump()
        {
            vili::ViliParser* dataStore = new vili::ViliParser;
            dataStore->addFlag("Map");
            dataStore->addFlag("Lock");
            dataStore->includeFile("Obe");

            //Meta
            (*dataStore)->createComplexNode("Meta");
            dataStore->at("Meta").createDataNode("name", m_levelName);

            //View
            (*dataStore)->createComplexNode("View");
            dataStore->at("View").createDataNode("size", m_camera.getSize().y / 2);
            dataStore->at("View").createComplexNode("pos");
            dataStore->at("View", "pos").createDataNode("unit", unitsToString(m_cameraInitialPosition.unit));
            dataStore->at("View", "pos").createDataNode("x", m_cameraInitialPosition.x);
            dataStore->at("View", "pos").createDataNode("y", m_cameraInitialPosition.y);
            dataStore->at("View", "pos").useTemplate(dataStore->getTemplate(
                "Vector2<" + Transform::unitsToString(m_cameraInitialPosition.unit) + ">")
            );
            dataStore->at("View").createComplexNode("referencial");
            dataStore->at("View", "referencial").createDataNode("referencial", Transform::referencialToString(m_cameraInitialReferencial));
            dataStore->at("View", "referencial").useTemplate(dataStore->getTemplate(
                "Referencial<" + Transform::referencialToString(m_cameraInitialReferencial) + ">"
            ));

            //LevelSprites
            if (m_spriteArray.size() > 0) (*dataStore)->createComplexNode("LevelSprites");
            for (unsigned int i = 0; i < m_spriteArray.size(); i++)
            {
                if (m_spriteArray[i]->getParentId() == "")
                {
                    vili::ComplexNode& currentSprite = dataStore->at("LevelSprites").createComplexNode(m_spriteArray[i]->getId());
                    currentSprite.createDataNode("path", m_spriteArray[i]->getPath());
                    currentSprite.createComplexNode("rect");
                    Transform::UnitVector spritePositionRect = m_spriteArray[i]->getPosition().to<Transform::Units::WorldUnits>(/*m_spriteArray[i]->getWorkingUnit()*/);
                    currentSprite.at("rect").createDataNode("x", spritePositionRect.x);
                    currentSprite.at("rect").createDataNode("y", spritePositionRect.y);
                    Transform::UnitVector spriteSizeRect = Transform::UnitVector(
                        m_spriteArray[i]->getSpriteWidth() * m_spriteArray[i]->getXScaleFactor(),
                        m_spriteArray[i]->getSpriteHeight() * m_spriteArray[i]->getYScaleFactor(),
                        Transform::Units::WorldPixels).to<Transform::Units::WorldUnits>(/*m_spriteArray[i]->getWorkingUnit()*/);
                    currentSprite.at("rect").createDataNode("w", spriteSizeRect.x);
                    currentSprite.at("rect").createDataNode("h", spriteSizeRect.y);
                    currentSprite.at("rect").useTemplate(
                        dataStore->getTemplate("Rect<" + unitsToString(m_spriteArray[i]->getWorkingUnit()) + ">")
                    );
                    currentSprite.createDataNode("rotation", m_spriteArray[i]->getRotation());
                    currentSprite.createDataNode("layer", m_spriteArray[i]->getLayer());
                    currentSprite.createDataNode("z-depth", m_spriteArray[i]->getZDepth());
                    currentSprite.createDataNode("xTransform", m_spriteArray[i]->getPositionTransformer().getXTransformerName());
                    currentSprite.createDataNode("yTransform", m_spriteArray[i]->getPositionTransformer().getYTransformerName());
                }
            }
            if (m_colliderArray.size() > 0) (*dataStore)->createComplexNode("Collisions");
            for (unsigned int i = 0; i < m_colliderArray.size(); i++)
            {
                if (m_colliderArray[i]->getParentId() == "")
                {
                    dataStore->at("Collisions").createComplexNode(m_colliderArray[i]->getId());
                    dataStore->at("Collisions", m_colliderArray[i]->getId()).createComplexNode("unit");
                    dataStore->at("Collisions", m_colliderArray[i]->getId(), "unit").useTemplate(
                        dataStore->getTemplate("Unit<" + unitsToString(m_colliderArray[i]->getWorkingUnit()) + ">")
                    );
                    dataStore->at("Collisions", m_colliderArray[i]->getId()).createArrayNode("points");
                    for (unsigned int j = 0; j < m_colliderArray[i]->getPointsAmount(); j++)
                    {
                        Transform::UnitVector pVec = m_colliderArray[i]->getPointPosition(j);
                        dataStore->at("Collisions", m_colliderArray[i]->getId()).getArrayNode("points").push(pVec.x);
                        dataStore->at("Collisions", m_colliderArray[i]->getId()).getArrayNode("points").push(pVec.y);
                    }
                }
            }
            if (m_gameObjectArray.size() > 0) (*dataStore)->createComplexNode("GameObjects");
            for (auto& gameObject : m_gameObjectArray)
            {
                dataStore->at("GameObjects").createComplexNode(gameObject->getId());
                dataStore->at("GameObjects", gameObject->getId()).createDataNode("type", gameObject->getType());
                /*(*it->second->m_objectScript)("inspect = require('Lib/StdLib/Inspect');");
                //kaguya::LuaRef saveTableRef = (*it->second->m_objectScript)["Local"]["Save"]();
                //(*it->second->m_objectScript)("print('Saving : ', This:getId())");
                //(*it->second->m_objectScript)("print(inspect(Local.Save()));");
                //(*it->second->m_objectScript)("print('Processing...')");
                vili::ComplexNode* saveRequirements = Script::DataBridge::luaTableToComplexNode(
                    "Requires", saveTableRef);
                if (saveRequirements->getAll().size() > 0)
                    dataStore->at("LevelObjects", it->first).pushComplexNode(saveRequirements);
                //(*it->second->m_objectScript)("print('Saving over for : ', This:getId())");*/
            }
            if (m_scriptArray.size() > 0)
            {
                (*dataStore)->createComplexNode("Script");
                dataStore->at("Script").createArrayNode("gameScripts");
                for (int i = 0; i < m_scriptArray.size(); i++)
                {
                    dataStore->at("Script").getArrayNode("gameScripts").push(m_scriptArray[i]);
                }
            }
            return dataStore;
        }

        void Scene::update(double dt)
        {
            if (m_futureLoad != "")
            {
                std::cout << "FUTURE LOAD NOW : " << m_futureLoad << std::endl;
                this->loadFromFile(m_futureLoad);
                m_futureLoad.clear();
            }
            //std::cout << "LevelSprite Array Size (" << m_spriteArray.size() << ")" << std::endl;
            for (auto& sprite : m_spriteArray)
            {
                /*if (Utils::String::contains(sprite->getId(), "bomb_") && sprite->getId().at(0) != '_')
                {
                    std::cout << "  Id : " << sprite->getId() << std::endl;
                    std::cout << "  Position : " << sprite->getPosition() << std::endl;
                    std::cout << "  Size : " << sprite->getSize() << std::endl;
                    std::cout << "  Texture : " << sprite->getTexture().getSize().x << ", " << sprite->getTexture().getSize().y << std::endl;
                    std::cout << "  Visible : " << sprite->isVisible() << std::endl;
                    std::cout << "  Alpha : " << sprite->getColor().a << std::endl;
                    std::cout << "  Camera Position : " << sprite->getDrawPosition(m_camera.getPosition()).to<Transform::Units::WorldPixels>() << std::endl;
                    std::cout << "  SpriteSize : " << sprite->getSpriteWidth() << ", " << sprite->getSpriteHeight() << std::endl;
                }*/
            }
            if (m_updateState)
            {
                for (auto& gameObject : m_gameObjectArray)
                {
                    if (!gameObject->deletable)
                        gameObject->update();
                }
            }
        }

        void Scene::display(sf::RenderWindow& target)
        {
            this->displaySprites(target);
            if (m_showCollisionModes["drawLines"] || m_showCollisionModes["drawPoints"] || m_showCollisionModes["drawMasterPoint"] || m_showCollisionModes["drawSkel"])
            {
                for (unsigned int i = 0; i < m_colliderArray.size(); i++)
                {
                    m_colliderArray[i]->draw(target, m_camera,
                                             m_showCollisionModes["drawLines"],
                                             m_showCollisionModes["drawPoints"],
                                             m_showCollisionModes["drawMasterPoint"],
                                             m_showCollisionModes["drawSkel"]);
                }
            }
        }

        void Scene::displaySprites(sf::RenderWindow& target)
        {
            Transform::UnitVector pixelCamera = m_camera.getPosition().to<Transform::Units::WorldPixels>();
            for (unsigned int i = 0; i < m_spriteArray.size(); i++)
            {
                Transform::UnitVector spritePosition = m_spriteArray[i]->getDrawPosition(pixelCamera);
                sfe::ComplexSprite& tAffSpr = m_spriteArray[i]->getSprite();

                //std::cout << "Draw Position of Sprite : " << spritePosition << std::endl;

                tAffSpr.setPosition(spritePosition.x, spritePosition.y);
                //tAffSpr.setScalingOrigin(-layeredX, -layeredY); Work on this later :)
                //tAffSpr.scale(m_camera.getHeight() / 2, m_camera.getHeight() / 2);
                
                if (m_spriteArray[i]->isVisible())
                {
                    target.draw(tAffSpr);
                    if (m_spriteArray[i]->isSelected())
                    {
                        m_spriteArray[i]->drawHandle(target, spritePosition.x, spritePosition.y);
                    }
                        
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

        void Scene::setCameraLock(bool state)
        {
            m_cameraLocked = state;
        }

        bool Scene::isCameraLocked() const
        {
            return m_cameraLocked;
        }

        void Scene::setUpdateState(bool state)
        {
            m_updateState = state;
        }

        Script::GameObject* Scene::getGameObject(const std::string& id)
        {
            for (auto& gameObject : m_gameObjectArray)
            {
                if (gameObject->getId() == id)
                    return gameObject.get();
            }
            throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.UnknownGameObject", {{"id", id}, {"map", m_levelName}});
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
            m_gameObjectArray.erase(std::remove_if(m_gameObjectArray.begin(), m_gameObjectArray.end(), [&id](const std::unique_ptr<Script::GameObject>& ptr){
                if (ptr->getId() == id)
                    return true;
            }), m_gameObjectArray.end());
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
                    useId = Utils::String::getRandomKey(Utils::String::Alphabet + Utils::String::Numbers, 8);
                }
            }
            else if (this->doesGameObjectExists(useId))
            {
                aube::ErrorHandler::Warn("ObEngine.Scene.Scene.OverridedObject", { {"id", id}, {"mapfile", m_levelName} });
            }

            std::unique_ptr<Script::GameObject> newGameObject = std::make_unique<Script::GameObject>(obj, useId);
            vili::ComplexNode& gameObjectData = *Script::GameObjectDatabase::GetDefinitionForGameObject(obj);
            newGameObject->loadGameObject(*this, gameObjectData);
            if (newGameObject->m_hasScriptEngine)
            {
                //loadWorldLib(newGameObject->m_objectScript.get());
                //(*newGameObject.get()->m_objectScript)["Scene"] = this;
            }

            if (newGameObject->doesHaveLevelSprite())
            {
                newGameObject->getLevelSprite()->setPosition(0, 0);
                newGameObject->getLevelSprite()->setParentId(useId);
            }

            if (newGameObject->doesHaveCollider())
            {
                newGameObject->getCollider()->setParentId(useId);
            }

            m_gameObjectArray.push_back(move(newGameObject));

            //std::cout << "<World> Created new object : " << id << " of type : " << obj << std::endl;

            return m_gameObjectArray.back().get();
        }

        unsigned Scene::getGameObjectAmount() const
        {
            return m_gameObjectArray.size();
        }

        void Scene::reorganizeLayers()
        {
            bool noChange = false;
            while (noChange == false)
            {
                noChange = true;
                for (unsigned int i = 0; i < m_spriteArray.size(); i++)
                {
                    if (i != m_spriteArray.size() - 1 && m_spriteArray[i]->getLayer() < m_spriteArray[i + 1]->getLayer())
                    {
                        swap(m_spriteArray[i], m_spriteArray[i + 1]);
                        noChange = false;
                    }
                }
            }
            noChange = false;
            while (noChange == false)
            {
                noChange = true;
                for (unsigned int i = 0; i < m_spriteArray.size(); i++)
                {
                    if (i != m_spriteArray.size() - 1 && m_spriteArray[i]->getLayer() == m_spriteArray[i + 1]->getLayer() && m_spriteArray[i]->getZDepth() < m_spriteArray[i + 1]->getZDepth())
                    {
                        swap(m_spriteArray[i], m_spriteArray[i + 1]);
                        noChange = false;
                    }
                }
            }
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

        std::vector<Graphics::LevelSprite*> Scene::getLevelSpritesByLayer(int layer)
        {
            std::vector<Graphics::LevelSprite*> returnLayer;

            for (unsigned int i = 0; i < m_spriteArray.size(); i++)
            {
                if (m_spriteArray[i]->getLayer() == layer)
                    returnLayer.push_back(m_spriteArray[i].get());
            }

            return returnLayer;
        }

        Graphics::LevelSprite* Scene::getLevelSpriteByPosition(const Transform::UnitVector& position, int layer)
        {
            Graphics::LevelSprite* returnSpr = nullptr;
            Transform::UnitVector pixelPosition = position.to<Transform::Units::WorldPixels>();
            std::vector<Graphics::LevelSprite*> getSpriteVec = this->getLevelSpritesByLayer(layer);
            for (unsigned int i = 0; i < getSpriteVec.size(); i++)
            {
                if (pixelPosition.x > getSpriteVec[i]->getRect().left && pixelPosition.x < getSpriteVec[i]->getRect().left + getSpriteVec[i]->getSpriteWidth())
                {
                    if (pixelPosition.y > getSpriteVec[i]->getRect().top && pixelPosition.y < getSpriteVec[i]->getRect().top + getSpriteVec[i]->getSpriteHeight())
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
            throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.UnknownLevelSprite", {{"id", id}, {"map", m_levelName}});
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
            m_spriteArray.erase(std::remove_if(m_spriteArray.begin(), m_spriteArray.end(), [&id](std::unique_ptr<Graphics::LevelSprite>& levelSprite)
            {
                return (levelSprite->getId() == id);
            }), m_spriteArray.end());
        }

        void Scene::enableShowCollision(bool drawLines, bool drawPoints, bool drawMasterPoint, bool drawSkel)
        {
            m_showCollisionModes["drawLines"] = drawLines;
            m_showCollisionModes["drawPoints"] = drawPoints;
            m_showCollisionModes["drawMasterPoint"] = drawMasterPoint;
            m_showCollisionModes["drawSkel"] = drawSkel;
        }

        std::pair<Collision::PolygonalCollider*, int> Scene::getColliderPointByPosition(const Transform::UnitVector& position)
        {
            Transform::UnitVector pPos = position.to<Transform::Units::WorldPixels>();
            const Transform::UnitVector pTolerance = Transform::UnitVector(6, 6, Transform::Units::WorldPixels);
            for (unsigned int i = 0; i < m_colliderArray.size(); i++)
            {
                if (m_colliderArray[i]->hasPoint(pPos, pTolerance) != -1)
                {
                    return std::pair<Collision::PolygonalCollider*, int>(m_colliderArray[i].get(), m_colliderArray[i]->hasPoint(pPos, pTolerance));
                }
            }
            return std::pair<Collision::PolygonalCollider*, int>(nullptr, 0);
        }

        Collision::PolygonalCollider* Scene::getColliderByCentroidPosition(const Transform::UnitVector& position)
        {
            Transform::UnitVector pPos = position.to<Transform::Units::WorldPixels>();
            const Transform::UnitVector pTolerance = Transform::UnitVector(6, 6, Transform::Units::WorldPixels);
            for (unsigned int i = 0; i < m_colliderArray.size(); i++)
            {
                if (m_colliderArray[i]->hasMasterPoint(pPos, pTolerance))
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
            throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.UnknownCollider", { {"id", id}, {"scene", m_levelName} });
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
            m_colliderArray.erase(std::remove_if(m_colliderArray.begin(), m_colliderArray.end(), [&id](std::unique_ptr<Collision::PolygonalCollider>& collider)
            {
                return (collider->getId() == id);
            }), m_colliderArray.end());
        }


        void loadWorldLib(kaguya::State* lua)
        {
            if (!static_cast<bool>((*lua)["Core"])) (*lua)["Core"] = kaguya::NewTable();
            (*lua)["Core"]["Scene"] = kaguya::NewTable();
            (*lua)["Core"]["Scene"]["Scene"].setClass(kaguya::UserdataMetatable<Scene>()
                .addFunction("loadFromFile", &Scene::loadFromFile)
            );
        }

        void loadWorldScriptEngineBaseLib(kaguya::State* lua)
        {
            //TOB
            (*lua)["CPP_Import"] = &Bindings::Load;
            (*lua)["CPP_Hook"] = &Script::loadHook;
            loadWorldLib(lua);
            (*lua)["This"] = lua;
        }
    };
};
