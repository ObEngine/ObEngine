#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>

#include "Functions.hpp"
#include "Entity.hpp"

class Character : public Entity
{
	private:
		//Movement Bool
		bool isMoving = false;
		bool isJumping = false;
		bool isFalling = false;
		bool isSprinting = false;
		bool isCrouching = false;
		bool fallByJump = false;
		//Jump-Fall
		double jumpIterate = 0;
		double jumpInc = 0;
		double speedFall = 0;
		double fallIterate = 0;
		int fallCounter = 0;
		int maxJumpHeight = 25;
		//Move
		double speed = 0;
		int maxWalkSpeed = 8;
		int maxRunSpeed = 35;
		int maxSpeed = 8;
		double speedIterate = 0;
		double maxSpeedIterate = 0;
		std::string direction = "Right";
		std::string lastDirection = "None";
		double downLineClimb = 0;
		double upLineClimb = 0;
		double velocity;

	public:
		Character(std::string name);
		void setDirectionAnimation(std::string animation);
		void melee(int x, int y);
		void verticalUpdate();
		void jump();
		void move(std::string cdirection);
		void sprint(bool activSprint);
		std::string getDirection(); //Revoie la derniere direction horizontale
		int getHSpeed(); //Renvoie la vitesse horizontale
		int getVSpeed(); //Renvoie la vitesse verticale
		void triggerCrouch(bool isCrouching);
		virtual void textureUpdate();
		virtual void moveUpdate();
		virtual void specialUpdate();
		void applyMove(int hWidth);
		void cancelMoves();
		void setVelocity(double newinerty);
		void addVelocity(double addinerty);
		double getVelocity();
};