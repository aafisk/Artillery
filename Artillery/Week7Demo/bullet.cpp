/*********************************
* Authors:
*	Aaron Fisk
*	Tim Orgill
*
* Project:
*	Artillery Simulator
***********************************/

#include "bullet.h"

Bullet::Bullet()
{
	isAirborne = true;
	targetHit = false;
	hitGround = false;
}

Bullet::Bullet(Position position, Velocity velocity)
{
	this->position = position;
	this->velocity = velocity;
	bool isAirborne = true;
	bool targetHit = false;
	bool hitGround = false;

}


/**************************************
* Draw the bullet to the screen
**************************************/
void Bullet::draw(ogstream& gout)
{
	trail.push_back(position);

	// Draw the bullet and the trail 
	for (int i = 0; (trail.size() < 20) ? i < trail.size() : i < 20; i++)
	{
		Position current = trail[trail.size() - i];
		gout.drawProjectile(current, 0.5 * (double)i);
	}
}

void Bullet::updatePosition(Position position) { this->position = position; }

void Bullet::updateVelocity(Velocity velocity) { this->velocity = velocity; }

double Bullet::getVelocity() { return velocity.getSpeed(); }

void Bullet::setIsAirborne(bool isAirborne) { this->isAirborne = isAirborne; }

void Bullet::setTargetHit(bool targetHit) { this->targetHit = targetHit; }

void Bullet::setHitGround(bool groundHit) { this->hitGround = groundHit; }

void Bullet::determineImpact()
{
	// Determine the impact here
}
