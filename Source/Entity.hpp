//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <map>

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
		mse::Animation::Animator entityAnimator;
		sf::Sprite* entitySprite;
		mse::Collision::PolygonalCollider* entityCollider;
		std::vector<mse::Collision::PolygonalCollider*>* collidersList;
		int worldCamX = 0;
		int worldCamY = 0;
		int life = 100;
		int maxLife = 100;
		double currentDeltaTime = 0.0;

	public:
		Entity();
		double getX(); //Renvoie absoluteX
		double getY(); //Renvoie absoluteY
		void draw(sf::RenderWindow* surf);
		void update(); //Mise a jour de l'Entity
		mse::Collision::PolygonalCollider* getEntityCollider();
		void setColliders(std::vector<mse::Collision::PolygonalCollider*>* collideList); //Modifie les colliders internes
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
};