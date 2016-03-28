#include "Trajectory.hpp"

Trajectory::Trajectory(std::string id, double angle, double speed, double acceleration)
{
	this->id = id;
	this->angle = angle;
	this->speed = speed;
	this->acceleration = acceleration;
}

void Trajectory::setAngle(double angle)
{
	this->angle = angle;
}

double Trajectory::getAngle()
{
	return angle;
}

void Trajectory::setSpeed(double speed)
{
	this->speed = speed;
}

double Trajectory::getSpeed()
{
	return speed;
}

void Trajectory::setAcceleration(double acceleration)
{
	this->acceleration = acceleration;
}

double Trajectory::getAcceleration()
{
	return acceleration;
}

void Trajectory::hookX(double* xptr)
{
	this->hX = xptr;
}

void Trajectory::hookY(double* yptr)
{
	this->hY = yptr;
}

void Trajectory::update()
{
	speed += acceleration;
	double radAngle = (std::_Pi / 180) * angle;
	double addX = std::cos(radAngle) * speed;
	double addY = std::sin(radAngle) * speed;
	*(this->hX) += addX;
	*(this->hY) += addY;
}
