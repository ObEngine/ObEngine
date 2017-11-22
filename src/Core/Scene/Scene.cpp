#include <Bindings/Bindings.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Scene/Scene.hpp>
#include <Script/GlobalState.hpp>
#include <Script/ViliLuaBridge.hpp>
#include <System/Loaders.hpp>
#include <System/Window.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/StringUtils.hpp>

namespace obe
{
    namespace Scene
    {
        Scene::Scene() : m_sceneRoot("root")
        {
            Collision::PolygonalCollider::m_sceneRef = this;
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

        Graphics::LevelSprite* Scene::createLevelSprite(const std::string& id, bool addToSceneRoot)
        {
            if (!this->doesLevelSpriteExists(id))
            {
                std::unique_ptr<Graphics::LevelSprite> newLevelSprite = std::make_unique<Graphics::LevelSprite>(id);

                Graphics::LevelSprite* returnLevelSprite = newLevelSprite.get();
                m_spriteArray.push_back(move(newLevelSprite));

                if (addToSceneRoot)
                    m_sceneRoot.addChild(returnLevelSprite);

                this->reorganizeLayers();
                return returnLevelSprite;
            }
            else
            {
                throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.SpriteAlreadyExists", { {"id", id}, {"mapfile", m_levelName} });
            }
        }

        Collision::PolygonalCollider* Scene::createCollider(const std::string& id, bool addToSceneRoot)
        {
            if (!this->doesColliderExists(id))
            {
                m_colliderArray.push_back(std::make_unique<Collision::PolygonalCollider>(id));
                if (addToSceneRoot)
                    m_sceneRoot.addChild(m_colliderArray.back().get());
                return m_colliderArray.back().get();
            }
            else
            {
                Debug::Log->warn("<Scene> Collider '{0}' already exists !", id);
                return this->getCollider(id);
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
                m_baseFolder = System::Path("Data/Maps").add(filename).loadResource(&m_levelFile, System::Loaders::dataLoader);
                m_levelFileName = filename;
            }

            if (m_levelFile->contains(vili::NodeType::ComplexNode, "Meta"))
            {
                vili::ComplexNode& meta = m_levelFile.at("Meta");
                m_levelName = meta.getDataNode("name").get<std::string>();
            }
            else
                throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.NoMeta", {{"map", filename}});

            if (m_levelFile->contains(vili::NodeType::ComplexNode, "View"))
            {
                vili::ComplexNode& view = m_levelFile.at("View");
                m_camera.setSize(view.at<vili::DataNode>("size").get<double>());
                m_cameraInitialPosition = Transform::UnitVector(
                    view.at<vili::DataNode>("pos", "x").get<double>(),
                    view.at<vili::DataNode>("pos", "y").get<double>(),
                    Transform::stringToUnits(view.at<vili::DataNode>("pos", "unit").get<std::string>()));
                m_cameraInitialReferencial = Transform::Referencial::TopLeft;
                if (m_levelFile->at("View").contains(vili::NodeType::ComplexNode, "referencial"))
                {
                    m_cameraInitialReferencial = Transform::stringToReferencial(
                        m_levelFile->at("View", "referencial").getDataNode("referencial").get<std::string>()
                    );
                }
                Debug::Log->debug("<Scene> Set Camera Position at : {0}, {1} using Referencial {2}", 
                    m_cameraInitialPosition.x, 
                    m_cameraInitialPosition.y, 
                    Transform::referencialToString(m_cameraInitialReferencial));
                m_camera.setPosition(m_cameraInitialPosition, m_cameraInitialReferencial);
                std::cout << m_camera.getPosition() << std::endl;
            }
            else
                throw aube::ErrorHandler::Raise("ObEngine.Scene.Scene.NoView", {{"map", filename}});

            if (m_levelFile->contains(vili::NodeType::ComplexNode, "LevelSprites"))
            {
                vili::ComplexNode& levelSprites = m_levelFile.at("LevelSprites");

                for (std::string& currentSpriteName : levelSprites.getAll(vili::NodeType::ComplexNode))
                {
                    this->createLevelSprite(currentSpriteName)->configure(levelSprites.at(currentSpriteName));
                }
            }

            this->reorganizeLayers();

            if (m_levelFile->contains(vili::NodeType::ComplexNode, "Collisions"))
            {
                vili::ComplexNode& collisions = m_levelFile.at("Collisions");
                for (std::string& collisionName : collisions.getAll(vili::NodeType::ComplexNode))
                {
                    vili::ComplexNode& currentCollision = collisions.at(collisionName);
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
                            tempCollider->addPoint(pVector2);
                        }
                        else
                            pointBuffer = colliderPoint->get<double>();
                    }
                    tempCollider->setWorkingUnit(pBaseUnit);
                    m_colliderArray.push_back(move(tempCollider));
                }
            }

            if (m_levelFile->contains(vili::NodeType::ComplexNode, "GameObjects"))
            {
                vili::ComplexNode& gameObjects = m_levelFile.at("GameObjects");
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
                    }
                    else if (!this->getGameObject(currentObjectName)->isPermanent())
                    {
                        aube::ErrorHandler::Warn("ObEngine.Scene.Scene.GameObjectAlreadyInScene", {{"object", currentObjectName}, {"mapfile", m_levelName}});
                    }
                }
            }

            if (m_levelFile->contains(vili::NodeType::ComplexNode, "Script"))
            {
                vili::ComplexNode& script = m_levelFile.at("Script");
                if (script.contains(vili::NodeType::DataNode, "source"))
                {
                    System::Path(script.at<vili::DataNode>("source")).loadResource(&Script::ScriptEngine, System::Loaders::luaLoader);
                    m_scriptArray.push_back(script.at<vili::DataNode>("source"));
                }
                else if (script.contains(vili::NodeType::ArrayNode, "sources"))
                {
                    for (vili::DataNode* scriptName : script.getArrayNode("sources"))
                    {
                        System::Path(*scriptName).loadResource(&Script::ScriptEngine, System::Loaders::luaLoader);
                        m_scriptArray.push_back(*scriptName);
                    }
                }
            }
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
            [](const std::unique_ptr<Script::GameObject>& ptr){
                return (!ptr->isPermanent());
            }), m_gameObjectArray.end());
            Debug::Log->debug("<Scene> Cleaning LevelSprite Array");
            m_spriteArray.erase(std::remove_if(m_spriteArray.begin(), m_spriteArray.end(), 
            [this](const std::unique_ptr<Graphics::LevelSprite>& ptr){
                if (!ptr->getParentId().empty() && this->doesGameObjectExists(ptr->getParentId()))
                    return false;
                return true;
            }), m_spriteArray.end());
            Debug::Log->debug("<Scene> Cleaning LevelSprite Array");
            m_colliderArray.erase(std::remove_if(m_colliderArray.begin(), m_colliderArray.end(), 
            [this](const std::unique_ptr<Collision::PolygonalCollider>& ptr){
                if (!ptr->getParentId().empty() && this->doesGameObjectExists(ptr->getParentId()))
                    return false;
                return true;
            }), m_colliderArray.end());
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

            //Meta
            (*dataStore)->createComplexNode("Meta");
            dataStore->at("Meta").createDataNode("name", m_levelName);

            //View
            (*dataStore)->createComplexNode("View");
            dataStore->at("View").createDataNode("size", m_camera.getSize().y / 2);
            dataStore->at("View").createComplexNode("pos");
            dataStore->at("View", "pos").createDataNode("unit", unitsToString(m_cameraInitialPosition.unit));
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
                    Transform::UnitVector spritePositionRect = m_spriteArray[i]->getPosition().to(m_spriteArray[i]->getWorkingUnit());
                    currentSprite.at("rect").createDataNode("x", spritePositionRect.x);
                    currentSprite.at("rect").createDataNode("y", spritePositionRect.y);
                    Transform::UnitVector spriteSizeRect = m_spriteArray[i]->getSize().to(m_spriteArray[i]->getWorkingUnit());
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
                        Transform::UnitVector pVec = m_colliderArray[i]->getPointPosition(j).to(m_colliderArray[i]->getWorkingUnit());
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

        void Scene::update(double dt)
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
                for (auto& gameObject : m_gameObjectArray)
                {
                    if (!gameObject->deletable)
                        gameObject->update();
                }
                /*m_gameObjectArray.erase(std::remove_if(m_gameObjectArray.begin(), m_gameObjectArray.end(), [this](const std::unique_ptr<Script::GameObject>& ptr) {
                    if (ptr->deletable)
                    {
                        if (ptr->m_hasLevelSprite)
                            this->removeLevelSprite(ptr->getLevelSprite()->getId());
                        if (ptr->m_hasCollider)
                            this->removeCollider(ptr->getCollider()->getId());
                        return true;
                    }
                }), m_gameObjectArray.end());*/
            }
        }

        void Scene::display()
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
            this->displaySprites();
            if (m_showCollisionModes["drawLines"] || m_showCollisionModes["drawPoints"] || m_showCollisionModes["drawMasterPoint"] || m_showCollisionModes["drawSkel"])
            {
                for (unsigned int i = 0; i < m_colliderArray.size(); i++)
                {
                    m_colliderArray[i]->draw(m_camera,
                        m_showCollisionModes["drawLines"],
                        m_showCollisionModes["drawPoints"],
                        m_showCollisionModes["drawMasterPoint"],
                        m_showCollisionModes["drawSkel"]);
                }
            }
        }

        void Scene::displaySprites()
        {
            Transform::UnitVector pixelCamera = m_camera.getPosition().to<Transform::Units::WorldPixels>();
            for (unsigned int i = 0; i < m_spriteArray.size(); i++)
            {
                Transform::UnitVector spritePosition = m_spriteArray[i]->getDrawPosition(pixelCamera, Transform::Referencial::Center);
                Transform::UnitVector bsp = m_spriteArray[i]->getDrawPosition(pixelCamera, Transform::Referencial::TopLeft);
                sfe::ComplexSprite& tAffSpr = m_spriteArray[i]->getSprite();

                //std::cout << "Draw Position of Sprite : " << spritePosition << std::endl;

                Transform::UnitVector middle = (m_spriteArray[i]->getSize() / Transform::UnitVector(2, 2)).to<Transform::Units::WorldPixels>();

                tAffSpr.setTranslationOrigin(middle.x, middle.y);
                tAffSpr.setPosition(spritePosition.x, spritePosition.y);

                /*std::cout << "Sprite @" << m_spriteArray[i]->getId() << std::endl;
                std::cout << "Bounds : " << tAffSpr.getGlobalBounds().left << ", " << tAffSpr.getGlobalBounds().top << ", " << tAffSpr.getGlobalBounds().width << ", " << tAffSpr.getGlobalBounds().height << std::endl;
                std::cout << "CPos : " << spritePosition << std::endl;*/

                if (m_spriteArray[i]->isVisible())
                {
                    System::MainWindow.draw(tAffSpr);
                    if (m_spriteArray[i]->isSelected())
                    {
                        //std::cout << "Middle : " << middle << std::endl;
                        std::cout << "Sprite position : " << spritePosition << std::endl;
                        Transform::UnitVector handlePos = m_spriteArray[i]->getDrawPosition(pixelCamera, Transform::Referencial::TopLeft);
                        m_spriteArray[i]->drawHandle(handlePos.x, handlePos.y);
                        Graphics::Utils::drawPoint(spritePosition.x, spritePosition.y, 3, sf::Color::Blue);
                        Graphics::Utils::drawPoint(bsp.x + middle.x, bsp.y + middle.y, 3, sf::Color::Red);
                        middle += pixelCamera;
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

        void Scene::setUpdateState(bool state)
        {
            m_updateState = state;
            unsigned int envCount = Script::ScriptEngine["__ENV_COUNT"];
            for (unsigned int i = 0; i < envCount; i++)
            {
                bool exists = Script::ScriptEngine["LuaUtil"]["Exists"]("__ENVIRONMENTS[" + std::to_string(i) + "]");
                if (exists)
                {
                    Script::ScriptEngine["__ENVIRONMENTS"][i]["__ENV_ENABLED"] = state;
                }
            }
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

            if (newGameObject->doesHaveLevelSprite())
            {
                Transform::UnitVector zero(0, 0);
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
            std::sort(m_spriteArray.begin(), m_spriteArray.end(), [](auto& sprite1, auto& sprite2)
            {
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

        Graphics::LevelSprite* Scene::getLevelSpriteByPosition(const Transform::UnitVector& position, const Transform::UnitVector& camera, int layer)
        {
            Graphics::LevelSprite* returnSpr = nullptr;
            std::vector<Transform::Referencial> rectPts = { 
              Transform::Referencial::TopLeft, Transform::Referencial::TopRight,
              Transform::Referencial::BottomRight, Transform::Referencial::BottomLeft 
            };
            Transform::UnitVector pixelPosition = position.to<Transform::Units::WorldPixels>();
            Transform::UnitVector zeroOffset(0, 0);
            
            std::vector<Graphics::LevelSprite*> getSpriteVec = this->getLevelSpritesByLayer(layer);
            for (unsigned int i = 0; i < getSpriteVec.size(); i++)
            {
                Collision::PolygonalCollider positionCollider("positionCollider");
                positionCollider.addPoint(getSpriteVec[i]->getPositionTransformer()(position, camera, layer));
                Collision::PolygonalCollider sprCollider("sprCollider");
                for (Transform::Referencial& ref : rectPts)
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
            Debug::Log->debug("<Scene> Removing LevelSprite {0}", id);
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

        Transform::SceneNode& Scene::getSceneRootNode()
        {
            return m_sceneRoot;
        }

        std::string Scene::getLevelFile() const
        {
            return m_levelFileName;
        }
    };
};
