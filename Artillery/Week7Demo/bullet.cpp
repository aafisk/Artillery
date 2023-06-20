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

void Bullet::draw()
{
	// Draw stuff
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
