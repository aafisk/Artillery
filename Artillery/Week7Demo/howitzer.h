#pragma once

#include "position.h"
#include "uiDraw.h"

class Howitzer
{
private:
	double angle;
	Position pos;

public:
	Howitzer();
	Howitzer(Position pos, double angle);
	void draw(ogstream& og, double time);
	void rotateClock();
	void rotateCounterClock();
	double getAngle();
	Position getPosition();
	void setPosition(Position pos);
};

