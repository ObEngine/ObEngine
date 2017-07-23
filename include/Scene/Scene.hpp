#pragma once

#include <Collision/PolygonalCollider.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Scene/Camera.hpp>
#include <Script/GameObject.hpp>

namespace obe
{
    namespace Scene
    {
        void loadWorldLib(kaguya::State* lua);
        void loadWorldScriptEngineBaseLib(kaguya::State* lua);

        class Scene
        {
        private:
            std::string m_levelName = "";
            std::string m_baseFolder = "";
            Camera m_camera;
            bool m_cameraLocked = true;
            Transform::UnitVector m_cameraInitialPosition;
            bool m_updateState = true;
            bool m_needToOrderUpdateArray = true;

            std::vector<std::unique_ptr<Graphics::LevelSprite>> m_spriteArray;
            std::vector<std::unique_ptr<Collision::PolygonalCollider>> m_colliderArray;
            std::map<std::string, std::unique_ptr<Script::GameObject>> m_gameObjectMap;
            std::vector<Script::GameObject*> m_updateObjArray;
            std::vector<std::string> m_scriptArray;

            std::map<std::string, bool> m_showCollisionModes;
            void orderGameObjectExecutionByPriority();
            void displaySprites(sf::RenderWindow& target);
        public:
            //World
            Scene();
            ~Scene();

            void loadFromFile(const std::string& filename);
            void clearWorld();
            vili::DataParser* dump();
            void update(double dt);
            void display(sf::RenderWindow& target);
            std::string getLevelName() const;
            void setLevelName(const std::string& newName);
            void setUpdateState(bool state);
            //GameObjects
            Script::GameObject* createGameObject(const std::string& id, const std::string& object);
            unsigned int getGameObjectAmount();
            std::vector<Script::GameObject*> getAllGameObjects(const std::vector<std::string>& filters = {});
            Script::GameObject* getGameObjectById(const std::string& id);
            bool doesGameObjectExists(const std::string& id);
            void removeGameObjectById(const std::string& id);
            //Camera
            Camera* getCamera();
            void setCameraLock(bool state);
            bool isCameraLocked() const;
            //LevelSprites
            void reorganizeLayers();
            Graphics::LevelSprite* createLevelSprite(const std::string& id);
            unsigned int getLevelSpriteAmount() const;
            std::vector<Graphics::LevelSprite*> getAllLevelSprites();
            std::vector<Graphics::LevelSprite*> getLevelSpritesByLayer(int layer);
            Graphics::LevelSprite* getLevelSpriteByPosition(const Transform::UnitVector& position, int layer);
            Graphics::LevelSprite* getLevelSpriteById(const std::string& id);
            bool doesLevelSpriteExists(const std::string& id);
            void removeLevelSpriteById(const std::string& id);
            //Colliders
            Collision::PolygonalCollider* createCollider(const std::string& id);
            unsigned int getColliderAmount();
            std::vector<Collision::PolygonalCollider*> getAllColliders() const;
            std::pair<Collision::PolygonalCollider*, int> getColliderPointByPosition(const Transform::UnitVector& position);
            Collision::PolygonalCollider* getColliderCentroidByPosition(const Transform::UnitVector& position);
            Collision::PolygonalCollider* getColliderById(const std::string& id);
            bool doesColliderExists(const std::string& id);
            void removeColliderById(const std::string& id);
            //Other
            std::string getBaseFolder() const;
            void enableShowCollision(bool drawLines = false, bool drawPoints = false, bool drawMasterPoint = false, bool drawSkel = false);
        };
    }
}
