//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <vili/Vili.hpp>

#include "Camera.hpp"
#include "DataParserLuaBridge.hpp"
#include "Functions.hpp"
#include "GameObject.hpp"
#include "LevelSprite.hpp"
#include "Light.hpp"
#include "Script.hpp"
#include "TimeManager.hpp"

namespace obe
{
    namespace World
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
            Coord::UnitVector m_cameraInitialPosition;
            kaguya::State* m_worldScriptEngine;
            bool m_updateState = true;
            bool m_needToOrderUpdateArray = true;

            std::vector<std::unique_ptr<Graphics::LevelSprite>> m_spriteArray;
            std::vector<std::unique_ptr<Collision::PolygonalCollider>> m_colliderArray;
            std::map<std::string, std::unique_ptr<Script::GameObject>> m_gameObjectMap;
            std::vector<Script::GameObject*> m_updateObjArray;
            std::map<std::string, std::unique_ptr<Light::PointLight>> m_lightMap;
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
            std::vector<Script::GameObject*> getAllGameObjects(std::vector<std::string> filters = std::vector<std::string>());
            Script::GameObject* createGameObject(std::string id, std::string obj);
            void orderUpdateScrArray();
            //Camera
            Camera* getCamera();
            void setCameraLock(bool state);
            bool isCameraLocked() const;
            //Lights
            void addLight(Light::PointLight* lgt);
            //LevelSprites
            Graphics::LevelSprite* createLevelSprite(std::string id);
            void reorganizeLayers();
            void displaySprites(sf::RenderWindow& target);
            Graphics::LevelSprite* getSpriteByIndex(int index);
            int getSpriteArraySize() const;
            std::vector<Graphics::LevelSprite*> getAllSprites();
            std::vector<Graphics::LevelSprite*> getSpritesByLayer(int layer);
            Graphics::LevelSprite* getSpriteByPos(int x, int y, int layer);
            Graphics::LevelSprite* getSpriteByID(std::string ID);
            bool doesSpriteExists(const std::string& id);
            void deleteSpriteByID(std::string sprID);
            void deleteSprite(Graphics::LevelSprite* sprToDelete);
            //Colliders
            Collision::PolygonalCollider* createCollider(std::string id);
            std::vector<Collision::PolygonalCollider*> getColliders() const;
            std::pair<Collision::PolygonalCollider*, int> getCollisionPointByPos(int x, int y);
            Collision::PolygonalCollider* getCollisionMasterByPos(int x, int y);
            Collision::PolygonalCollider* getCollisionByID(std::string id);
            std::vector<Collision::PolygonalCollider*> getAllCollidersByCollision(Collision::PolygonalCollider* col, int offx, int offy);
            void deleteCollisionByID(std::string id);
            void deleteCollision(Collision::PolygonalCollider* colToDelete);
            void createCollisionAtPos(int x, int y);
            void enableShowCollision(bool drawLines = false, bool drawPoints = false, bool drawMasterPoint = false, bool drawSkel = false);
            //Other
            kaguya::State* getScriptEngine() const;
            std::string getBaseFolder() const;
        };
    }
}
