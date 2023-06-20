#include "velocity.h"

Velocity::Velocity()
{
	dx = 0.0;
	dy = 0.0;
	speed = 0.0;
}

Velocity::Velocity(double dx, double dy)
{
	this->dx = dx;
	this->dy = dy;
	setSpeed(dx, dy);
}

double Velocity::getDx()
{
	return dx;
}

double Velocity::getDy()
{
	return dy;
}

double Velocity::getSpeed()
{
	return speed;
}

void Velocity::setDx(double dx)
{
	this->dx = dx;
	setSpeed(dx, dy);
}

void Velocity::setDy(double dy)
{
	this->dy = dy;
	setSpeed(dx, dy);
}

void Velocity::setSpeed(double dx, double dy)
{
	speed = physics.computeTotalComponent(dx, dy);
}