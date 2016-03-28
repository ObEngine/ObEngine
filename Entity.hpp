#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>

#include "Functions.hpp"
#include "Animation.hpp"
#include "Console.hpp"
#include "Collisions.hpp"

class Entity
{
	protected:
		std::string entityType;
		double x;
		double y;
		anim::Animator entityAnimator;
		sf::Sprite* entitySprite;
		Collision::PolygonalCollider* entityCollider;
		std::vector<Collision::PolygonalCollider*>* collidersList;
		int worldCamX = 0;
		int worldCamY = 0;
		int life = 100;
		int maxLife = 100;
		double currentDeltaTime = 0.0;
		Console::Stream* streamLink;

	public:
		Entity();
		double getX(); //Renvoie absoluteX
		double getY(); //Renvoie absoluteY
		void draw(sf::RenderWindow* surf);
		void update(); //Mise a jour de l'Entity
		Collision::PolygonalCollider* getEntityCollider();
		void setColliders(std::vector<Collision::PolygonalCollider*>* collideList); //Modifie les colliders internes
		void setColliderDrawOffset(int x, int y);
		bool collide(int tx, int ty);
		void getCamPos(int camX, int camY);
		virtual void textureUpdate();
		virtual void moveUpdate();
		int getLife();
		int getMaxLife();
		void setKey(std::string key);
		void setDeltaTime(double dt);
		void setPos(double newx, double newy);
		void addPos(double addx, double addy);
		void addDtPos(double addx, double addy);
		void setStreamLink(Console::Stream* link);
};