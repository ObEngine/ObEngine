//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "Functions.hpp"
#include "Character.hpp"
#include "DataParser.hpp"
#include "DataParserLuaBridge.hpp"
#include "GameObject.hpp"
#include "TimeManager.hpp"
#include "LevelSprite.hpp"
#include "Light.hpp"
#include "Particle.hpp"
#include "Script.hpp"

namespace mse
{
	namespace World
	{
		void loadWorldLib(kaguya::State* lua);
		void loadWorldScriptEngineBaseLib(kaguya::State* lua);

		class World
		{
			private:
				std::string levelName = "";
				std::string baseFolder = "";
				int sizeX = 0;
				int sizeY = 0;
				double camX = 0;
				double camY = 0;
				int startX = 0;
				int startY = 0;
				kaguya::State* worldScriptEngine;
				bool updateState = true;

				std::vector<Graphics::LevelSprite*> backSpriteArray;
				std::vector<Graphics::LevelSprite*> frontSpriteArray;
				std::vector<Collision::PolygonalCollider*> collidersArray;
				std::map<std::string, mse::Script::GameObject*> gameObjectsMap;
				std::vector<mse::Script::GameObject*> updateObjArray;
				std::map<std::string, Light::PointLight*> lightsMap;
				std::vector<Graphics::MathParticle*> particleArray;
				std::vector<Character*> charArray;
				std::vector<std::string> scriptArray;

				double blurMul = 0.0003;
				sf::Shader blurShader;
				sf::Shader lightShader;
				sf::Shader normalShader;

				double gameSpeed;
				std::map<std::string, bool> showCollisionModes;

			public:
				//World
				World();
				void loadFromFile(std::string filename);
				void clearWorld();
				Data::DataParser* saveData();
				void update(double dt);
				void display(sf::RenderWindow* surf);
				void setSize(int sizeX, int sizeY);
				int getSizeX();
				int getSizeY();
				int getStartX();
				int getStartY();
				void setUpdateState(bool state);
				//GameObjects
				mse::Script::GameObject* getGameObject(std::string id);
				std::vector<mse::Script::GameObject*> getAllGameObjects(std::vector<std::string> filters = std::vector<std::string>());
				mse::Script::GameObject* createGameObject(std::string id, std::string obj);
				void orderUpdateScrArray();
				//Camera
				void setCameraPosition(double tX, double tY, std::string setMode = "SET");
				double getCamX();
				double getCamY();
				//Lights
				void addLight(Light::PointLight* lgt);
				//Character
				void addCharacter(Character* character);
				Character* getCharacter(int index);
				//LevelSprites
				void addLevelSprite(Graphics::LevelSprite* spr);
				void reorganizeLayers();
				void setBlurMul(double newBlur);
				void visualDisplayBack(sf::RenderWindow* surf);
				void visualDisplayFront(sf::RenderWindow* surf);
				Graphics::LevelSprite* getSpriteByIndex(std::string backOrFront, int index);
				int getSpriteArraySize(std::string backOrFront);
				std::vector<Graphics::LevelSprite*> getAllSprites();
				std::vector<Graphics::LevelSprite*> getSpritesByLayer(int layer);
				Graphics::LevelSprite* getSpriteByPos(int x, int y, int layer);
				Graphics::LevelSprite* getSpriteByID(std::string ID);
				void deleteSpriteByID(std::string sprID, bool freeMemory = true);
				void deleteSprite(Graphics::LevelSprite* sprToDelete, bool freeMemory = true);
				//Colliders
				std::vector<Collision::PolygonalCollider*> getColliders();
				void addCollider(Collision::PolygonalCollider* col);
				std::pair<Collision::PolygonalCollider*, int> getCollisionPointByPos(int x, int y);
				Collision::PolygonalCollider* getCollisionMasterByPos(int x, int y);
				Collision::PolygonalCollider* getCollisionByID(std::string id);
				std::vector<Collision::PolygonalCollider*> getAllCollidersByCollision(Collision::PolygonalCollider* col, int offx, int offy);
				void deleteCollisionByID(std::string id, bool freeMemory = true);
				void deleteCollision(Collision::PolygonalCollider* colToDelete, bool freeMemory = true);
				void createCollisionAtPos(int x, int y);
				void enableShowCollision(bool drawLines = false, bool drawPoints = false, bool drawMasterPoint = false, bool drawSkel = false);
				//Other
				void addParticle(Graphics::MathParticle* particle);
				kaguya::State* getScriptEngine();
				std::string getBaseFolder();
		};
	}
}