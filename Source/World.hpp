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
#include "Spells.hpp"
#include "DataParser.hpp"
#include "GameObject.hpp"
#include "TimeManager.hpp"
#include "LevelSprite.hpp"
#include "Light.hpp"
#include "Particle.hpp"
#include "Script.hpp"
#include "GameObject.hpp"

void loadWorldScriptEngineBaseLib(kaguya::State* lua);

class World
{
	private:
		std::string levelName = "";
		int sizeX = 0;
		int sizeY = 0;
		double camX = 0;
		double camY = 0;
		int startX = 0;
		int startY = 0;
		kaguya::State* worldScriptEngine;

		std::vector<LevelSprite*> backSpriteArray;
		std::vector<LevelSprite*> frontSpriteArray;
		std::vector<Collision::PolygonalCollider*> collidersArray;
		std::map<std::string, GameObject*> gameObjectsMap;
		std::vector<GameObject*> updateObjArray;
		std::map<std::string, Light::PointLight*> lightsMap;
		std::vector<MathParticle*> particleArray;
		std::vector<Character*> charArray;
		std::vector<std::string> scriptArray;
		
		double blurMul = 0.0003;
		sf::Shader blurShader;
		sf::Shader lightShader;
		sf::Shader normalShader;
		
		anim::RessourceManager sprRsMan;
		double gameSpeed;
		std::map<std::string, bool> showCollisionModes;

	public:
		//World
		World();
		void loadFromFile(std::string filename);
		DataParser* saveData();
		void update(double dt);
		void display(sf::RenderWindow* surf);
		int getSizeX();
		int getSizeY();
		int getStartX();
		int getStartY();
		//GameObjects
		GameObject* getGameObject(std::string id);
		std::vector<GameObject*> getAllGameObject(std::vector<std::string> filters = std::vector<std::string>());
		GameObject* createGameObject(std::string id, std::string type, std::string obj);
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
		void addLevelSprite(LevelSprite* spr);
		void reorganizeLayers();
		void setBlurMul(double newBlur);
		void visualDisplayBack(sf::RenderWindow* surf);
		void visualDisplayFront(sf::RenderWindow* surf);
		LevelSprite* getSpriteByIndex(std::string backOrFront, int index);
		int getSpriteArraySize(std::string backOrFront);
		std::vector<LevelSprite*> getAllSprites();
		std::vector<LevelSprite*> getSpritesByLayer(int layer);
		LevelSprite* getSpriteByPos(int x, int y, int layer);
		LevelSprite* getSpriteByID(std::string ID);
		void deleteSprite(LevelSprite* sprToDelete, bool freeMemory = true);
		//Colliders
		std::vector<Collision::PolygonalCollider*> getColliders();
		void addCollider(Collision::PolygonalCollider* col);
		std::pair<Collision::PolygonalCollider*, int> getCollisionPointByPos(int x, int y);
		Collision::PolygonalCollider* getCollisionMasterByPos(int x, int y);
		Collision::PolygonalCollider* getCollisionByID(std::string id);
		std::vector<Collision::PolygonalCollider*> getAllCollidersByCollision(Collision::PolygonalCollider* col, int offx, int offy);
		void deleteCollisionByID(std::string id);
		void createCollisionAtPos(int x, int y);
		void enableShowCollision(bool drawLines = false, bool drawPoints = false, bool drawMasterPoint = false, bool drawSkel = false);
		//Other
		void addParticle(MathParticle* particle);
		anim::RessourceManager* getRessourceManager();
		kaguya::State* getScriptEngine();
};