#pragma once
#include "bullet.h"
#include <cassert>

class BulletTest: Bullet
{
public:
	void run()
	{
		// Insert other test cases here
		test_UpdatePosition_noChange();
		test_UpdatePosition_significantChange();
		test_UpdateVelocity_noChange();
		test_UpdateVelocity_bigChange();
		test_UpdateVelocity_negativeChange();
		test_SetIsAirborne_different();
		test_SetIsAirborne_same();
		test_SetTargetHit_different();
		test_SetTargetHit_same();
		test_SetHitGround_different();
		test_SetHitGround_same();
	}

private:

	/********************************************************
	Test cases for updatePosition()
	********************************************************/

	void test_UpdatePosition_noChange()
	{
		// Setup
		Bullet b;
		Position updatedPosition;
		updatedPosition.setMeters(0.0, 0.0);
		Position oldPosition = b.position;

		// Exercise
		b.updatePosition(updatedPosition);

		// Verify
		assert(b.position.getMetersX() == updatedPosition.getMetersX());
		assert(b.position.getMetersY() == updatedPosition.getMetersY());
		assert(b.position.getMetersX() == oldPosition.getMetersX());
		assert(b.position.getMetersY() == oldPosition.getMetersY());

		// Teardown
	}

	void test_UpdatePosition_significantChange()
	{
		// Setup
		Bullet b;
		Position updatedPosition;
		updatedPosition.setMeters(9999.9, 999999.999);
		Position oldPosition = b.position;

		// Exercise
		b.updatePosition(updatedPosition);

		// Verify
		assert(b.position.getMetersX() == updatedPosition.getMetersX());
		assert(b.position.getMetersY() == updatedPosition.getMetersY());
		assert(b.position.getMetersX() != oldPosition.getMetersX());
		assert(b.position.getMetersY() != oldPosition.getMetersY());

		// Teardown
	}

	/********************************************************
	Test cases for updateVelocity()
	********************************************************/

	void test_UpdateVelocity_noChange()
	{
		// Setup
		Bullet b;
		Velocity updatedVelocity(0.0, 0.0);
		Velocity oldVelocity = b.velocity;

		// Exercise
		b.updateVelocity(updatedVelocity);

		// Verify
		assert(b.velocity.getSpeed() == updatedVelocity.getSpeed());
		assert(b.velocity.getSpeed() != oldVelocity.getSpeed());

		// Teardown
	}

	void test_UpdateVelocity_bigChange()
	{
		// Setup
		Bullet b;
		Velocity updatedVelocity(9999.9, 999999.999);
		Velocity oldVelocity = b.velocity;

		// Exercise
		b.updateVelocity(updatedVelocity);

		// Verify
		assert(b.velocity.getSpeed() == updatedVelocity.getSpeed());
		assert(b.velocity.getSpeed() != oldVelocity.getSpeed());

		// Teardown
	}

	void test_UpdateVelocity_negativeChange()
	{
		// Setup
		Bullet b;
		Velocity updatedVelocity(-12.3, -56.7);
		Velocity oldVelocity = b.velocity;

		// Exercise
		b.updateVelocity(updatedVelocity);

		// Verify
		assert(b.velocity.getSpeed() == updatedVelocity.getSpeed());
		assert(b.velocity.getSpeed() != oldVelocity.getSpeed());

		// Teardown
	}

	/********************************************************
	Test cases for setIsAirborne()
	********************************************************/

	void test_SetIsAirborne_different()
	{
		// Setup
		Bullet b;
		bool newValue = false;
		b.isAirborne = true;

		// Exercise
		b.setIsAirborne(newValue);

		// Verify
		assert(b.isAirborne == newValue);
		assert(b.isAirborne != true);

		// Teardown
	}

	void test_SetIsAirborne_same()
	{
		// Setup
		Bullet b;
		bool newValue = true;
		b.isAirborne = true;

		// Exercise
		b.setIsAirborne(newValue);

		// Verify
		assert(b.isAirborne == newValue);
		assert(b.isAirborne != false);

		// Teardown
	}

	/********************************************************
	Test cases for setTargetHit()
	********************************************************/

	void test_SetTargetHit_different()
	{
		// Setup
		Bullet b;
		bool newValue = false;
		b.targetHit = true;

		// Exercise
		b.setTargetHit(newValue);

		// Verify
		assert(b.targetHit == newValue);
		assert(b.targetHit != true);

		// Teardown
	}
	
	void test_SetTargetHit_same()
	{
		// Setup
		Bullet b;
		bool newValue = true;
		b.targetHit = true;

		// Exercise
		b.setTargetHit(newValue);

		// Verify
		assert(b.targetHit == newValue);
		assert(b.targetHit != false);

		// Teardown
	}

	/********************************************************
	Test cases for setHitGround()
	********************************************************/

	void test_SetHitGround_different()
	{
		// Setup
		Bullet b;
		bool newValue = false;
		b.hitGround = true;

		// Exercise
		b.setHitGround(newValue);

		// Verify
		assert(b.hitGround == newValue);
		assert(b.hitGround != true);

		// Teardown
	}

	void test_SetHitGround_same()
	{
		// Setup
		Bullet b;
		bool newValue = true;
		b.hitGround = true;

		// Exercise
		b.setHitGround(newValue);

		// Verify
		assert(b.hitGround == newValue);
		assert(b.hitGround != false);

		// Teardown
	}
};