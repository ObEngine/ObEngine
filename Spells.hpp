#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Functions.hpp"
#include "Entity.hpp"
#include "Animation.hpp"
#include "DataParser.hpp"

//FICHIER EN COURS DE DEBUG

namespace Spells
{
	class Spell
	{
		protected:
			std::string spellName = "";
			std::string spellID = "";
			Spell(std::string ID);
			bool castable;
			anim::Animator spellAnimator;

		protected:
			Spell();
	};

	class Projectile : public Spell
	{
		private:
			std::string spellName = "";
			std::string spellID = "";
			bool castable;
			int x;
			int y;
			int velocity;
			int angle;
			float xVelocity;
			float yVelocity;
			int range;
			int currentRange;
			int damage;
			bool isAlive = true;
			int knockbackForce;
			float knockbackAngle;
			bool destroyedOnHit;
			bool passThroughShapes;
			bool callSpecialOnHit; //Call special Method when target hitted
			std::map<std::string, std::vector<sf::Texture*>> textureDict;
			std::vector<sf::Texture*> textureList;
			Entity* entityTarget;
			int xTarget;
			int yTarget;
			std::string targetMode = "NONE";
			sf::Texture spellTexture;
			sf::Sprite* spellSprite;
			sf::Sprite spellMask;
			int rotateAngle;
		public:
			Projectile(std::string id, std::string name, int rotation, DataParser* spellInfo, anim::RessourceManager* spellRessource);
			virtual void update(double dt);
			virtual int getDamage();
			virtual void specialOnHit();
			void setX(int newX);
			void setY(int newY);
			virtual int getX();
			virtual int getY();
			virtual bool isSpellAlive();
			virtual void setEntityTarget(Entity* target);
			virtual void setPosTarget(int tx, int ty);
			sf::Sprite* getSprite();
	};

	class Beam
	{
		private:
			int x1;
			int y1;
			int x2;
			int y2;
			int velocity;
			int damageCount;
			int damagePerHit;
			bool passThroughEntities;
			bool passThroughShapes;
			float knockbackForce;
			float knockbackAngle;
			bool callSpecialOnHit; //Call special Method when target hitted
			std::map<std::string, std::vector<sf::Texture*>> textureDict;
			std::vector<sf::Texture*> textureList;
			std::string textureGroup = "DEFAULT";
			std::string lastTextureGroup = "NONE";
			double lastAnimUpdate = 0.0;
			float delayAnimation = 0.07;
			sf::Texture* lastTextureAddress = NULL;
			sf::Texture spellTexture;
			sf::Sprite spellSprite;
			sf::Sprite spellMask;
		public:
	};

	class InstantZone
	{
	private:
	public:
	};

	class InstantTarget
	{
	private:
	public:
	};

	class Placeable
	{
	private:
	public:
	};

	class Booster
	{
	private:
	public:
	};

	class Circular
	{
	private:
	public:
	};
}