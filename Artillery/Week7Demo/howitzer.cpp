#include "howitzer.h"

Howitzer::Howitzer()
{
	angle = 0;
	pos.setPixelsX(0.0);
	pos.setPixelsY(0.0);
}

Howitzer::Howitzer(Position pos, double angle)
{
	angle = 0;
	pos.setPixelsX(Position(pos).getPixelsX() / 2.0);
}

void Howitzer::draw(ogstream& og, Position pos, double time)
{
	og.drawHowitzer(pos, angle, time);
}

void Howitzer::rotateUp()
{
	angle += (angle >= 0 ? -0.003 : 0.003);
}

void Howitzer::rotateDown()
{
	angle += (angle >= 0 ? 0.003 : -0.003);
}

void Howitzer::rotateRight()
{
	angle += 0.05;
}

void Howitzer::rotateLeft()
{
	angle -= 0.05;
}

void Howitzer::fire()
{
	
}

double Howitzer::getAngle()
{
	return angle;
}

Position Howitzer::getPosition()
{
	return pos;
}

void Howitzer::setPosition(double x, double y)
{
	pos.setMetersX(x);
	pos.setMetersY(y);
}
