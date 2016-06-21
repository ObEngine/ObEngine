//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

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

void Trajectory::setConstraint(std::string id, std::string constraint)
{
	luaConstraints[id] = constraint;
}

void Trajectory::removeConstraint(std::string id)
{
	auto remIt = luaConstraints.find(id);
	if (remIt != luaConstraints.end())
		luaConstraints.erase(remIt);
	else
		std::cout << "<Warning:Trajectory:Trajectory>[removeConstraint] : Can't remove inexistant Constraint : " << id << std::endl;
}

void Trajectory::removeAllConstraints()
{
	luaConstraints.clear();
}

std::vector<std::string> Trajectory::getAllConstraints()
{
	std::vector<std::string> allConstraints;
	std::transform(luaConstraints.begin(), luaConstraints.end(), std::back_inserter(allConstraints),
		[](const std::map<std::string, std::string>::value_type &pair) {return pair.first; });
	return allConstraints;
}

void Trajectory::update()
{
	speed += acceleration;
	double radAngle = (fn::Math::pi / 180) * angle;
	double addX = std::cos(radAngle) * speed;
	double addY = std::sin(radAngle) * speed;
	*(this->hX) += addX;
	*(this->hY) += addY;
}
