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

        class World
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

            sf::Shader m_lightShader;

            double m_gameSpeed;
            std::map<std::string, bool> m_showCollisionModes;

        public:
            //World
            World();
            ~World();
            void loadFromFile(std::string filename);
            void clearWorld();
            vili::DataParser* saveData();
            void update(double dt);
            void display(sf::RenderWindow& target);
            std::string getLevelName() const;
            void setLevelName(std::string newName);
            void setUpdateState(bool state);
            //GameObjects
            Script::GameObject* getGameObject(std::string id);
            std::vector<Script::GameObject*> getAllGameObjects(const std::vector<std::string>& filters = {});
            Script::GameObject* createGameObject(const std::string& id, const std::string& obj);
            void orderUpdateScrArray();
            //Camera
            Camera* getCamera();
            void setCameraLock(bool state);
            bool isCameraLocked() const;
            //LevelSprites
            Graphics::LevelSprite* createLevelSprite(const std::string& id);
            void reorganizeLayers();
            void displaySprites(sf::RenderWindow& target);
            Graphics::LevelSprite* getSpriteByIndex(int index);
            int getSpriteArraySize() const;
            std::vector<Graphics::LevelSprite*> getAllSprites();
            std::vector<Graphics::LevelSprite*> getSpritesByLayer(int layer);
            Graphics::LevelSprite* getSpriteByPos(int x, int y, int layer);
            Graphics::LevelSprite* getSpriteByID(const std::string& ID);
            bool doesSpriteExists(const std::string& id);
            void deleteSpriteByID(const std::string& sprID);
            void deleteSprite(Graphics::LevelSprite* sprToDelete);
            //Colliders
            Collision::PolygonalCollider* createCollider(const std::string& id);
            std::vector<Collision::PolygonalCollider*> getColliders() const;
            std::pair<Collision::PolygonalCollider*, int> getCollisionPointByPos(int x, int y);
            Collision::PolygonalCollider* getCollisionMasterByPos(int x, int y);
            Collision::PolygonalCollider* getCollisionByID(const std::string& id);
            std::vector<Collision::PolygonalCollider*> getAllCollidersByCollision(Collision::PolygonalCollider* col, int offx, int offy);
            void deleteCollisionByID(const std::string& id);
            void deleteCollision(Collision::PolygonalCollider* colToDelete);
            void createCollisionAtPos(int x, int y);
            void enableShowCollision(bool drawLines = false, bool drawPoints = false, bool drawMasterPoint = false, bool drawSkel = false);
            //Other
            std::string getBaseFolder() const;
        };
    }
}
