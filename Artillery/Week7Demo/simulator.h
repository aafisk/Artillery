/*********************************
* Authors:
*	Aaron Fisk
*	Tim Orgill
*
* Project:
*	Artillery Simulator
***********************************/

#pragma once
#include "position.h"
#include "physics.h"

#include <iostream>
#include <cmath>
#include <map>
#include <vector>

class Simulator
{
public:
	Simulator();
	void run(double angle); 
	void resetVariables();

private:
	Physics physics;
	double hangTime;
	double interval;
	double aRadians;
	double diameterOfShell; // m
	double radius;
	double shellMass; // kg
	double initialVelocity; // m/s (upon firing)
	Position position;
	double dx;
	double dy;
	double ddx;
	double ddy;
	double velocity;
	double altitude;
	double surfaceArea;
	double airDensity;
	double machAtAltitude;
	// speed / speed of sound
	double mach;
	double dragCoefficient;
	vector<double> flightPath;

	
};

