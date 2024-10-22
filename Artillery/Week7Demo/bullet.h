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
#include "velocity.h"
#include "uiDraw.h"
#include <vector>

using namespace std;
class TestBullet;

class Bullet
{
	friend TestBullet;
public:
	Bullet();
	Bullet(Position position, Velocity velocity);
	void draw(ogstream& gout);
	void updatePosition(Position position);
	void updateVelocity(Velocity velocity);
	double getVelocity();
	double getDx();
	double getDy();
	Position getPosition();
	void setIsAirborne(bool isAirborne);
	void setTargetHit(bool targetHit);
	void setHitGround(bool groundHit);
	bool getIsAirborne();
	vector<Position> getTrailForInterpolation();
	void launch(Position howitzerLocation, Velocity muzzleVelocity);
	void determineImpact();

private:
	Position position;
	vector<Position> trail;
	Velocity velocity;
	bool isAirborne;
	bool targetHit;
	bool hitGround;
};

// TODO - Add a struct to hold Position, Velocity, etc.
//		- Figure out anything else that needs held in struct

