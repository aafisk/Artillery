#pragma once

#include "position.h"
#include "uiDraw.h"

class Howitzer
{
private:
	double angle;
	Position pos;
	void draw(ogstream& og, double time);

public:
	Howitzer();
	Howitzer(Position pos, double angle);
	void rotateUp();
	void rotateDown();
	void rotateRight();
	void rotateLeft();
	void fire(double time);
	double getAngle();
	Position getPosition();
	void setPosition(double x, double y);
};

