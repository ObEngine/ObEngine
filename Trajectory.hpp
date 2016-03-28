#pragma once

#include <string>
#include <math.h>
#include <random>

class Trajectory
{
	private:
		std::string id;
		double angle = 0;
		double speed = 0;
		double acceleration = 0;
		double* hX = nullptr;
		double* hY = nullptr;
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
		void update();
};