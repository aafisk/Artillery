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

void Howitzer::draw(ogstream& og, double time)
{

}