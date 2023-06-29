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
	Howitzer(Position pos);
	void rotateUp();
	void rotateDown();
	void rotateRight();
	void rotateLeft();
	//void fire();
	void draw(ogstream& og, Position position, double time);
	double getAngle();
	Position getPosition();
	void setHorizontalPosition(Position position);
};

