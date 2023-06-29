#include "howitzer.h"

Howitzer::Howitzer()
{
	angle = 0;
	pos.setPixelsX(0.0);
	pos.setPixelsY(0.0);
}

Howitzer::Howitzer(Position position)
{
	angle = 0.0;
	pos.setPixelsX(0.0);
	pos.setPixelsY(0.0);
}

void Howitzer::draw(ogstream& og, Position position, double time)
{
	og.drawHowitzer(position, angle, time);
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

//void Howitzer::fire()
//{
//	
//}

double Howitzer::getAngle()
{
	return angle;
}

Position Howitzer::getPosition()
{
	return pos;
}

void Howitzer::setHorizontalPosition(Position position)
{
	pos.setPixelsX(Position(position).getPixelsX() / 2.0);
}
