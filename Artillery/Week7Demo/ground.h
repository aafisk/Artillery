/***********************************************************************
 * Header File:
 *    Ground : Represents the ground in the artillery simulation
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything about the ground
 ************************************************************************/

#pragma once

#include "position.h"   // for Point
#include "uiDraw.h"

 // forward declaration for the Ground unit tests
class TestGround;

/***********************************************************
 * GROUND
 * The ground class
 ***********************************************************/
class Ground
{
public:
	// the constructor generates the ground
	Ground(const Position& posUpperRight);
	Ground() : ground(nullptr), iHowitzer(0), iTarget(0) {}

	// reset the ground and set the vertical position of the howitzer
	double reset(Position posHowitzer);

	// draw the ground on the screen
	void draw(ogstream& gout) const;

	// determine how high the Position is off the ground
	double getElevationMeters(const Position& pos) const;

	// where the the target located?
	Position getTarget() const;

	// unit test access
	friend TestGround;

private:
	double* ground;               // elevation of the ground, in pixels 
	int iTarget;                   // the location of the target, in pixels
	int iHowitzer;                 // the location of the howitzer, in pixels
	Position posUpperRight;        // size of the screen
};
