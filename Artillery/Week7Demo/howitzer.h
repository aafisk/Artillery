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
	void rotateUp();
	void rotateDown();
	void rotateRight();
	void rotateLeft();
	void fire();
	void draw(ogstream& og, Position pos, double time);
	double getAngle();
	Position getPosition();
	void setPosition(double x, double y);
};

