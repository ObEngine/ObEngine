//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <string>
#include <math.h>
#include <random>
#include <vector>

#include "Functions.hpp"

class Trajectory
{
	private:
		std::string id;
		double angle = 0;
		double speed = 0;
		double acceleration = 0;
		double* hX = nullptr;
		double* hY = nullptr;
		std::map<std::string, std::string> luaConstraints;
	public:
		Trajectory(std::string id, double angle, double speed, double acceleration);
		void setAngle(double angle);
		double getAngle();
		void setSpeed(double speed);
		double getSpeed();
		void setAcceleration(double acceleration);
		double getAcceleration();
		void hookX(double* xptr);
		void hookY(double* yptr);
		void setConstraint(std::string id, std::string constraint);
		void removeConstraint(std::string id);
		void removeAllConstraints();
		std::vector<std::string> getAllConstraints();
		void update();
};