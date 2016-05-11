//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <Windows.h>

#include "SpriteFunc.hpp"
#include "Functions.hpp"
#include "Animation.hpp"
#include "ComplexSprite.hpp"
#include "Collisions.hpp"

class LevelSprite
{
	private:
		std::string sprName = "None";
		std::string sprID;
		double absoluteX = 0;
		double absoluteY = 0;
		bool drawable = true;
		bool visible = true;
		int lAbsX = 0;
		int lAbsY = 0;
		int width = 0;
		int height = 0;
		double rotation = 0;
		double scaleX = 1;
		double scaleY = 1;
		int originTraX = 0;
		int originTraY = 0;
		int originRotX = 0;
		int originRotY = 0;
		std::vector<std::string> currentAtr = {};
		int layer = 1;
		int zdepth = 0;
		bool useDefaultAnimationSystem = true;
		anim::DirtyAnimation sprAnim;
		std::string textureGroup = "DEFAULT";
		std::string lastTextureGroup = "NONE";
		sf::Texture actualTexture;
		sfe::ComplexSprite* returnSprite;
		sf::Color spriteColor = sf::Color(255,255,255);
		int textureIndex = 0;
		Collision::PolygonalCollider* collisionHook = nullptr;

	public:
		LevelSprite(std::string sprName, std::string sprID, anim::RessourceManager* rsMan = NULL);
		LevelSprite(std::string sprID);
		void useDirtyAnimation(bool state, bool candraw = true);
		void setSprite(sfe::ComplexSprite* spr);
		void setSprite(sf::Sprite* spr);
		void setLayer(int layer); //Change le layer
		void setZDepth(int zdepth);
		void rotate(double addRotate); //Ajoute une rotation
		void setRotation(double rotate); //Change la rotation
		void scale(double scaleX, double scaleY);
		void setScale(double scaleX, double scaleY);
		void setTranslationOrigin(int x, int y);
		void setRotationOrigin(int x, int y);
		void setAtr(std::vector<std::string> atrList); //Remplace une liste d'attributs
		void addAtr(std::string atr); //Ajoute un attribut
		std::vector<std::string> getAttributes(); //Retourne la liste des attributs
		void removeAtrByIndex(int index); //Supprime un attribut par index
		void removeAtrByName(std::string name); //Supprime un attribut par nom
		void textureUpdate(bool forceUpdate = false); //Update la texture
		sfe::ComplexSprite* getSprite(); //Renvoie la Sprite de la Sprite
		void setSpriteColor(sf::Color newColor);
		double getX(); //Renvoie absoluteX
		double getY(); //Renvoie absoluteY
		void setPosition(double x, double y);
		void move(double x, double y);
		double getScaleX();
		double getScaleY();
		float getRotation();
		int getLayer(); //Renvoie le layer de la Sprite
		int getZDepth();
		std::string getID(); //Renvoie l'ID de la Sprite
		std::string getName(); //Renvoie le nom (type) de la Sprite
		int getW();
		int getH();
		void calculateRealCoordinates();
		sf::FloatRect getRect();
		bool isDrawable();
		void setVisible(bool visible);
		bool isVisible();
		Collision::PolygonalCollider* getCollisionHook();
		void hookToCollision(Collision::PolygonalCollider* hook);
};