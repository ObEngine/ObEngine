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

class GameObject;

class LevelSprite
{
	private:
		std::string sprName = "None";
		std::string sprID;
		double absoluteX = 0;
		double absoluteY = 0;
		double offsetX = 0;
		double offsetY = 0;
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
		GameObject* parent = nullptr;

	public:
		LevelSprite(std::string sprName, std::string sprID, anim::RessourceManager* rsMan = NULL);
		LevelSprite(std::string sprID);
		void useDirtyAnimation(bool state, bool candraw = true);
		void setSprite(sfe::ComplexSprite* spr);
		void setSprite(sf::Sprite* spr);
		void setLayer(int layer);
		void setZDepth(int zdepth);
		void rotate(double addRotate);
		void setRotation(double rotate);
		void scale(double scaleX, double scaleY);
		void setScale(double scaleX, double scaleY);
		void setTranslationOrigin(int x, int y);
		void setRotationOrigin(int x, int y);
		void setPosition(double x, double y);
		void setOffset(double offx, double offy);
		double getX();
		double getY();
		double getOffsetX();
		double getOffsetY();
		void setAtr(std::vector<std::string> atrList);
		void addAtr(std::string atr);
		std::vector<std::string> getAttributes();
		void removeAtrByIndex(int index);
		void removeAtrByName(std::string name);
		void textureUpdate(bool forceUpdate = false);
		sfe::ComplexSprite* getSprite();
		void setColor(sf::Color newColor);	
		void move(double x, double y);
		double getScaleX();
		double getScaleY();
		float getRotation();
		int getLayer();
		int getZDepth();
		std::string getID();
		std::string getName();
		int getW();
		int getH();
		void calculateRealCoordinates();
		sf::FloatRect getRect();
		bool isDrawable();
		void setVisible(bool visible);
		bool isVisible();
		GameObject* getParent();
		void setParent(GameObject* parent);
};