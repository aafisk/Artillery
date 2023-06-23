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
#include <queue>

using namespace std;
class TestBullet;

class Bullet
{
	friend TestBullet;
public:
	Bullet();
	Bullet(Position position, Velocity velocity);
	void draw();
	void updatePosition(Position position);
	void updateVelocity(Velocity velocity);
	double getVelocity();
	void setIsAirborne(bool isAirborne);
	void setTargetHit(bool targetHit);
	void setHitGround(bool groundHit);
	void determineImpact();

private:
	Position position;
	queue<Position> trail;
	Velocity velocity;
	bool isAirborne;
	bool targetHit;
	bool hitGround;
};

// TODO - Add a struct to hold Position, Velocity, etc.
//		- Figure out anything else that needs held in struct

