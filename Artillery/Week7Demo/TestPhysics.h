/*********************************
* Authors:
*	Aaron Fisk
*	Tim Orgill
*
* Project:
*	Artillery Simulator
***********************************/

#pragma once
#include "physics.h"
#include <cassert>
#include <iostream>

using namespace std;


/**************************************
TEST PHYSICS
Test the physics class.
***************************************/

class TestPhysics
{
public:
	void run()
	{
		// test functions
		testPhysics_defaultConstructor();

		testComputeVerticalComponent_smallAngle();
		testComputeVerticalComponent_bigAngle();
		
		testComputeHorizontalComponent_smallAngle();
		testComputeHorizontalComponent_bigAngle();
		
		testRadiansFromDegrees_361();
		testRadiansFromDegrees_120();
		testRadiansFromDegrees_neg1();
		
		testComputeTotalComponent_zero();
		testComputeTotalComponent_zeroXSomeY();
		testComputeTotalComponent_SomeXZeroY();
		testComputeTotalComponent_someXSomeY();
		
		testComputeVelocity_zero();
		testComputeVelocity_speedingUp();
		testComputeVelocity_slowingDown();
		
		testAreaFromRadius_zero();
		testAreaFromRadius_smallRadius();
		testAreaFromRadius_largeRadius();
		
		testForceFromDrag_noForce();
		testForceFromDrag_smallForce();
		testForceFromDrag_largeForce();

		testLinearInterpolationGravityMap_smallValue();
		testLinearInterpolationGravityMap_largeValue();

		testLinearInterpolationSoundMap_smallValue();
		testLinearInterpolationSoundMap_largeValue();

		testLinearInterpolationDensityMap_smallValue();
		testLinearInterpolationDensityMap_largeValue();
		
		testLinearInterpolationMachMap_smallValue();
		testLinearInterpolationMachMap_largeValue();
		
		testLinearInterpolationValues_smallValue();
		testLinearInterpolationValues_largeValue();

		cout << "Physics tests pass" << endl;
	}

private:
	// utility funciton because floating point numbers are approximations
	bool closeEnough(double value, double test, double tolerence) const
	{
		double difference = value - test;
		return (difference >= -tolerence) && (difference <= tolerence);
	}
	
	void testPhysics_defaultConstructor()
	{
		// setup
		Physics p;

		// exercise
		
		// verify altitudeGravity
		auto itGravity = p.altitudeGravity.begin();
		assert(itGravity->first == 0);
		assert(itGravity->second == -9.807);
		advance(itGravity, 1);
		assert(itGravity->first == 1000);
		assert(itGravity->second == -9.804);
		advance(itGravity, 1);
		assert(itGravity->first == 2000);
		assert(itGravity->second == -9.801);
		advance(itGravity, 1);
		assert(itGravity->first == 3000);
		assert(itGravity->second == -9.797);
		advance(itGravity, 1);
		assert(itGravity->first == 4000);
		assert(itGravity->second == -9.794);
		advance(itGravity, 1);
		assert(itGravity->first == 5000);
		assert(itGravity->second == -9.791);
		advance(itGravity, 1);
		assert(itGravity->first == 6000);
		assert(itGravity->second == -9.788);
		advance(itGravity, 1);
		assert(itGravity->first == 7000);
		assert(itGravity->second == -9.785);
		advance(itGravity, 1);
		assert(itGravity->first == 8000);
		assert(itGravity->second == -9.782);
		advance(itGravity, 1);
		assert(itGravity->first == 9000);
		assert(itGravity->second == -9.779);
		advance(itGravity, 1);
		assert(itGravity->first == 10000);
		assert(itGravity->second == -9.776);
		advance(itGravity, 1);
		assert(itGravity->first == 15000);
		assert(itGravity->second == -9.761);
		advance(itGravity, 1);
		assert(itGravity->first == 20000);
		assert(itGravity->second == -9.745);
		advance(itGravity, 1);
		assert(itGravity->first == 25000);
		assert(itGravity->second == -9.730);

		// verify altitudeSpeedOfSound
		auto itSound = p.altitudeSpeedOfSound.begin();
		assert(itSound->first == 0);
		assert(itSound->second == 340.0);
		advance(itSound, 1);
		assert(itSound->first == 1000);
		assert(itSound->second == 336.0);
		advance(itSound, 1);
		assert(itSound->first == 2000);
		assert(itSound->second == 332.0);
		advance(itSound, 1);
		assert(itSound->first == 3000);
		assert(itSound->second == 328.0);
		advance(itSound, 1);
		assert(itSound->first == 4000);
		assert(itSound->second == 324.0);
		advance(itSound, 1);
		assert(itSound->first == 5000);
		assert(itSound->second == 320.0);
		advance(itSound, 1);
		assert(itSound->first == 6000);
		assert(itSound->second == 316.0);
		advance(itSound, 1);
		assert(itSound->first == 7000);
		assert(itSound->second == 312.0);
		advance(itSound, 1);
		assert(itSound->first == 8000);
		assert(itSound->second == 308.0);
		advance(itSound, 1);
		assert(itSound->first == 9000);
		assert(itSound->second == 303.0);
		advance(itSound, 1);
		assert(itSound->first == 10000);
		assert(itSound->second == 299.0);
		advance(itSound, 1);
		assert(itSound->first == 15000);
		assert(itSound->second == 295.0);
		advance(itSound, 1);
		assert(itSound->first == 20000);
		assert(itSound->second == 295.0);
		advance(itSound, 1);
		assert(itSound->first == 25000);
		assert(itSound->second == 295.0);
		advance(itSound, 1);
		assert(itSound->first == 30000);
		assert(itSound->second == 305.0);
		advance(itSound, 1);
		assert(itSound->first == 40000);
		assert(itSound->second == 324.0);

		// verify altitudeAirDensity
		auto itDensity = p.altitudeAirDensity.begin();
		assert(itDensity->first == 0);
		assert(itDensity->second == 1.2250000);
		advance(itDensity, 1);
		assert(itDensity->first == 1000);
		assert(itDensity->second == 1.1120000);
		advance(itDensity, 1);
		assert(itDensity->first == 2000);
		assert(itDensity->second == 1.0070000);
		advance(itDensity, 1);
		assert(itDensity->first == 3000);
		assert(itDensity->second == 0.9093000);
		advance(itDensity, 1);
		assert(itDensity->first == 4000);
		assert(itDensity->second == 0.8194000);
		advance(itDensity, 1);
		assert(itDensity->first == 5000);
		assert(itDensity->second == 0.7364000);
		advance(itDensity, 1);
		assert(itDensity->first == 6000);
		assert(itDensity->second == 0.6601000);
		advance(itDensity, 1);
		assert(itDensity->first == 7000);
		assert(itDensity->second == 0.5900000);
		advance(itDensity, 1);
		assert(itDensity->first == 8000);
		assert(itDensity->second == 0.5258000);
		advance(itDensity, 1);
		assert(itDensity->first == 9000);
		assert(itDensity->second == 0.4671000);
		advance(itDensity, 1);
		assert(itDensity->first == 10000);
		assert(itDensity->second == 0.4135000);
		advance(itDensity, 1);
		assert(itDensity->first == 15000);
		assert(itDensity->second == 0.1948000);
		advance(itDensity, 1);
		assert(itDensity->first == 20000);
		assert(itDensity->second == 0.0889100);
		advance(itDensity, 1);
		assert(itDensity->first == 25000);
		assert(itDensity->second == 0.0400800);
		advance(itDensity, 1);
		assert(itDensity->first == 30000);
		assert(itDensity->second == 0.0184100);
		advance(itDensity, 1);
		assert(itDensity->first == 40000);
		assert(itDensity->second == 0.0039960);
		advance(itDensity, 1);
		assert(itDensity->first == 50000);
		assert(itDensity->second == 0.0010270);
		advance(itDensity, 1);
		assert(itDensity->first == 60000);
		assert(itDensity->second == 0.0003097);
		advance(itDensity, 1);
		assert(itDensity->first == 70000);
		assert(itDensity->second == 0.0000828);
		advance(itDensity, 1);
		assert(itDensity->first == 80000);
		assert(itDensity->second == 0.0000185);
		
		// verify machDrag
		auto itMach = p.machDrag.begin();
		assert(itMach->first == 0.0);
		assert(itMach->second == 0.0);
		advance(itMach, 1);
		assert(itMach->first == 0.300);
		assert(itMach->second == 0.1629);
		advance(itMach, 1);
		assert(itMach->first == 0.500);
		assert(itMach->second == 0.1659);
		advance(itMach, 1);
		assert(itMach->first == 0.700);
		assert(itMach->second == 0.2031);
		advance(itMach, 1);
		assert(itMach->first == 0.890);
		assert(itMach->second == 0.2597);
		advance(itMach, 1);
		assert(itMach->first == 0.920);
		assert(itMach->second == 0.3010);
		advance(itMach, 1);
		assert(itMach->first == 0.960);
		assert(itMach->second == 0.3287);
		advance(itMach, 1);
		assert(itMach->first == 0.980);
		assert(itMach->second == 0.4002);
		advance(itMach, 1);
		assert(itMach->first == 1.000);
		assert(itMach->second == 0.4258);
		advance(itMach, 1);
		assert(itMach->first == 1.020);
		assert(itMach->second == 0.4335);
		advance(itMach, 1);
		assert(itMach->first == 1.060);
		assert(itMach->second == 0.4483);
		advance(itMach, 1);
		assert(itMach->first == 1.240);
		assert(itMach->second == 0.4064);
		advance(itMach, 1);
		assert(itMach->first == 1.530);
		assert(itMach->second == 0.3663);
		advance(itMach, 1);
		assert(itMach->first == 1.990);
		assert(itMach->second == 0.2897);
		advance(itMach, 1);
		assert(itMach->first == 2.870);
		assert(itMach->second == 0.2297);
		advance(itMach, 1);
		assert(itMach->first == 2.890);
		assert(itMach->second == 0.2306);
		advance(itMach, 1);
		assert(itMach->first == 5.000);
		assert(itMach->second == 0.2656);

		// teardown
	}

	void testComputeVerticalComponent_smallAngle()
	{
		// setup
		Physics p;
		double angle = 0.174533; // 10 degrees in radians
		double total = 827; // muzzle velocity of Howitzer
		double verticalComp;

		// exercise
		verticalComp = p.computeVerticalComponent(angle, total);

		// verify
		assert(angle == 0.174533);
		assert(total == 827);
		assert(closeEnough(verticalComp, 814.436, 0.001));

		// teardown
	}
	void testComputeVerticalComponent_bigAngle()
	{
		// setup
		Physics p;
		double angle = -1.308997; // -75 degrees in radians
		double total = 827; // muzzle velocity of Howitzer
		double verticalComp;

		// exercise
		verticalComp = p.computeVerticalComponent(angle, total);

		// verify
		assert(angle == -1.308997);
		assert(total == 827);
		assert(closeEnough(verticalComp, 214.043, 0.001));

		// teardown
	}

	void testComputeHorizontalComponent_smallAngle()
	{
		// setup
		Physics p;
		double angle = 0.174533; // 10 degrees in radians
		double total = 827; // muzzle velocity of Howitzer
		double horizontalComp;

		// exercise
		horizontalComp = p.computeHorizontalComponent(angle, total);

		// verify
		assert(angle == 0.174533);
		assert(total == 827);
		assert(closeEnough(horizontalComp, 143.607, 0.001));

		// teardown
	}
	void testComputeHorizontalComponent_bigAngle()
	{
		// setup
		Physics p;
		double angle = -1.308997; // -75 degrees in radians
		double total = 827; // muzzle velocity of Howitzer
		double horizontalComp;

		// exercise
		horizontalComp = p.computeHorizontalComponent(angle, total);

		// verify
		assert(angle == -1.308997);
		assert(total == 827);
		assert(closeEnough(horizontalComp, -798.820, 0.001));

		// teardown
	}

	void testRadiansFromDegrees_361()
	{
		// setup
		Physics p;
		double aDegrees = 361;
		aDegrees -= 360; // simulate degree wrapping to remain w/in 360 degrees

		// exercise
		double aRadians = p.radiansFromDegrees(aDegrees);

		// verify
		assert(aDegrees == 1);
		assert(closeEnough(aRadians, 0.017, 0.001));

		// teardown
	}
	void testRadiansFromDegrees_120()
	{
		// setup
		Physics p;
		double aDegrees = 120;
		
		// exercise
		double aRadians = p.radiansFromDegrees(aDegrees);

		// verify
		assert(aDegrees == 120);
		assert(closeEnough(aRadians, 2.094, 0.001));

		// teardown
	}
	void testRadiansFromDegrees_neg1()
	{
		// setup
		Physics p;
		double aDegrees = -1;

		// exercise
		double aRadians = p.radiansFromDegrees(aDegrees);

		// verify
		assert(aDegrees == -1);
		assert(closeEnough(aRadians, -0.017, 0.001));

		// teardown
	}

	void testComputeTotalComponent_zero()
	{
		// setup
		Physics p;
		double x = 0.0;
		double y = 0.0;

		// exercise
		double total = p.computeTotalComponent(x, y);

		// verify
		assert(x == 0.0);
		assert(y == 0.0);
		assert(total == 0);

		// teardown
	}
	void testComputeTotalComponent_zeroXSomeY()
	{
		// setup
		Physics p;
		double x = 0.0;
		double y = 57.9;

		// exercise
		double total = p.computeTotalComponent(x, y);

		// verify
		assert(x == 0.0);
		assert(y == 57.9);
		assert(total == 57.9);

		// teardown
	}
	void testComputeTotalComponent_SomeXZeroY()
	{
		// setup
		Physics p;
		double x = 43.7;
		double y = 0.0;

		// exercise
		double total = p.computeTotalComponent(x, y);

		// verify
		assert(x == 43.7);
		assert(y == 0.0);
		assert(total == 43.7);

		// teardown
	}
	void testComputeTotalComponent_someXSomeY()
	{
		// setup
		Physics p;
		double x = 43.7;
		double y = 0.0;

		// exercise
		double total = p.computeTotalComponent(x, y);

		// verify
		assert(x == 43.7);
		assert(y == 0.0);
		assert(total == 43.7);

		// teardown
	}

	void testComputeVelocity_zero()
	{
		// setup
		Physics p;
		double velocity = 0.0;
		double accel = 0.0;
		double time = 0.0;

		// exercise
		double newVelocity = p.computeVelocity(velocity, accel, time);

		// verify
		assert(velocity == 0.0);
		assert(accel == 0.0);
		assert(time == 0.0);
		assert(newVelocity == 0);

		// teardown
	}
	void testComputeVelocity_speedingUp()
	{
		// setup
		Physics p;
		double velocity = 0.0;
		double accel = 827.0;
		double time = 1.0;

		// exercise
		double newVelocity = p.computeVelocity(velocity, accel, time);

		// verify
		assert(velocity == 0.0);
		assert(accel == 827.0);
		assert(time == 1.0);
		assert(newVelocity == 827);

		// teardown
	}
	void testComputeVelocity_slowingDown()
	{
		// setup
		Physics p;
		double velocity = 827.0;
		double accel = -5.0;
		double time = 10.0;

		// exercise
		double newVelocity = p.computeVelocity(velocity, accel, time);

		// verify
		assert(velocity == 827.0);
		assert(accel == -5.0);
		assert(time == 10.0);
		assert(newVelocity == 777.0);

		// teardown
	}

	void testAreaFromRadius_zero()
	{
		// setup
		Physics p;
		double radius = 0.0;

		// exercise
		double area = p.areaFromRadius(radius);

		// verify
		assert(radius == 0.0);
		assert(area == 0.0);

		// teardown
	}
	void testAreaFromRadius_smallRadius()
	{
		// setup
		Physics p;
		double radius = 1.6;

		// exercise
		double area = p.areaFromRadius(radius);

		// verify
		assert(radius == 1.6);
		assert(closeEnough(area, 8.042, 0.001));

		// teardown
	}
	void testAreaFromRadius_largeRadius()
	{
		// setup
		Physics p;
		double radius = 985.6;

		// exercise
		double area = p.areaFromRadius(radius);

		// verify
		assert(radius == 985.6);
		assert(closeEnough(area, 3051766.225, 0.001));

		// teardown
	}

	void testForceFromDrag_noForce()
	{
		// setup
		Physics p;
		double c = 0.0;
		double density = 0.0;
		double v = 0.0;
		double vv = 0.0;
		double a = 0;

		// exercise
		double d = p.forceFromDrag(c, density, v, vv, a);

		// verify
		assert(c == 0.0);
		assert(density == 0.0);
		assert(v == 0.0);
		assert(vv == 0.0);
		assert(a == 0);
		assert(d == 0);

		// teardown
	}
	void testForceFromDrag_smallForce()
	{
		// setup
		Physics p;
		double c = 0.1;
		double density = 0.5;
		double v = 10.0;
		double vv = 5.0;
		double a = 12.5;

		// exercise
		double d = p.forceFromDrag(c, density, v, vv, a);

		// verify
		assert(c == 0.1);
		assert(density == 0.5);
		assert(v == 10.0);
		assert(vv == 5.0);
		assert(a == 12.5);
		assert(d == -15.625);

		// teardown
	}
	void testForceFromDrag_largeForce()
	{
		// setup
		Physics p;
		double c = 0.4;
		double density = 0.5;
		double v = 92.7;
		double vv = 45.6;
		double a = 18.5;

		// exercise
		double d = p.forceFromDrag(c, density, v, vv, a);

		// verify
		assert(c == 0.4);
		assert(density == 0.5);
		assert(v == 92.7);
		assert(vv == 45.6);
		assert(a == 18.5);
		assert(closeEnough(d, -7820.172, 0.001));

		// teardown
	}

	void testLinearInterpolationGravityMap_smallValue()
	{
		// setup
		Physics p;
		double testValue = 15.0;

		// exercise
		double value = p.linearInterpolation(p.altitudeGravity, testValue);

		// verify
		assert(testValue == 15.0);
		auto itGravity = p.altitudeGravity.upper_bound(testValue);
		assert(itGravity->first == 1000);
		assert(itGravity->second == -9.804);
		auto itGravity2 = --itGravity;
		assert(itGravity2->first == 0);
		assert(itGravity2->second == -9.807);
		assert(closeEnough(value, -9.807, 0.001));

		// teardown
	}
	void testLinearInterpolationGravityMap_largeValue()
	{
		// setup
		Physics p;
		double testValue = 24999.0;

		// exercise
		double value = p.linearInterpolation(p.altitudeGravity, testValue);

		// verify
		assert(testValue == 24999.0);
		auto itGravity = p.altitudeGravity.upper_bound(testValue);
		assert(itGravity->first == 25000);
		assert(itGravity->second == -9.730);
		auto itGravity2 = --itGravity;
		assert(itGravity2->first == 20000);
		assert(itGravity2->second == -9.745);
		assert(closeEnough(value, -9.730, 0.001));

		// teardown
	}

	void testLinearInterpolationSoundMap_smallValue()
	{
		// setup
		Physics p;
		double testValue = 15.0;

		// exercise
		double value = p.linearInterpolation(p.altitudeSpeedOfSound, testValue);

		// verify
		assert(testValue == 15.0);
		auto itSound = p.altitudeSpeedOfSound.upper_bound(testValue);
		assert(itSound->first == 1000);
		assert(itSound->second == 336.0);
		auto itSound2 = --itSound;
		assert(itSound2->first == 0);
		assert(itSound2->second == 340.0);
		assert(closeEnough(value, 339.94, 0.001));

		// teardown
	}
	void testLinearInterpolationSoundMap_largeValue()
	{
		// setup
		Physics p;
		double testValue = 39999.0;

		// exercise
		double value = p.linearInterpolation(p.altitudeSpeedOfSound, testValue);

		// verify
		assert(testValue == 39999.0);
		auto itSound = p.altitudeSpeedOfSound.upper_bound(testValue);
		assert(itSound->first == 40000);
		assert(itSound->second == 324.0);
		auto itSound2 = --itSound;
		assert(itSound2->first == 30000);
		assert(itSound2->second == 305.0);
		assert(closeEnough(value, 323.998, 0.001));

		// teardown
	}
	
	void testLinearInterpolationDensityMap_smallValue()
	{
		// setup
		Physics p;
		double testValue = 15.0;

		// exercise
		double value = p.linearInterpolation(p.altitudeAirDensity, testValue);

		// verify
		assert(testValue == 15.0);
		auto itDensity = p.altitudeAirDensity.upper_bound(testValue);
		assert(itDensity->first == 1000);
		assert(itDensity->second == 1.112);
		auto itDensity2 = --itDensity;
		assert(itDensity2->first == 0);
		assert(itDensity2->second == 1.225);
		assert(closeEnough(value, 1.223, 0.001));

		// teardown
	}

	void testLinearInterpolationDensityMap_largeValue()
	{
		// setup
		Physics p;
		double testValue = 79999.0;

		// exercise
		double value = p.linearInterpolation(p.altitudeAirDensity, testValue);

		// verify
		assert(testValue == 79999.0);
		auto itDensity = p.altitudeAirDensity.upper_bound(testValue);
		assert(itDensity->first == 80000);
		assert(itDensity->second == 0.0000185);
		auto itDensity2 = --itDensity;
		assert(itDensity2->first == 70000);
		assert(itDensity2->second == 0.0000828);
		assert(closeEnough(value, 0.0000185, 0.0000001));

		// teardown
	}
	
	void testLinearInterpolationMachMap_smallValue()
	{
		// setup
		Physics p;
		double testValue = 0.1;

		// exercise
		double value = p.linearInterpolation(p.machDrag, testValue);

		// verify
		assert(testValue == 0.1);
		auto itMach = p.machDrag.upper_bound(testValue);
		assert(itMach->first == 0.300);
		assert(itMach->second == 0.1629);
		auto itMach2 = --itMach;
		assert(itMach2->first == 0);
		assert(itMach2->second == 0.0);
		assert(closeEnough(value, 0.0543, 0.0001));

		// teardown
	}
	void testLinearInterpolationMachMap_largeValue()
	{
		// setup
		Physics p;
		double testValue = 4.9;

		// exercise
		double value = p.linearInterpolation(p.machDrag, testValue);

		// verify
		assert(testValue == 4.9);
		auto itMach = p.machDrag.upper_bound(testValue);
		assert(itMach->first == 5.0);
		assert(itMach->second == 0.2656);
		auto itMach2 = --itMach;
		assert(itMach2->first == 2.890);
		assert(itMach2->second == 0.2306);
		assert(closeEnough(value, 0.2639, 0.0001));

		// teardown
	}

	void testLinearInterpolationValues_smallValue()
	{
		// setup
		Physics p;
		double x1 = 0.0;
		double y1 = 0.0;
		double x2 = 100.0;
		double y2 = 100.0;
		double x = 45;

		// exercise
		double y = p.linearInterpolation(y1, y2, x1, x2, x);

		// verify
		assert(x1 == 0.0);
		assert(x2 == 100.0);
		assert(y1 == 0.0);
		assert(y2 == 100.0);
		assert(x == 45);
		assert(y == 45);

		// teardown
	}
	void testLinearInterpolationValues_largeValue()
	{
		// setup
		Physics p;
		double x1 = 165.0;
		double y1 = 2498.6;
		double x2 = 1564.0;
		double y2 = 7566.5;
		double x = 3254.9;

		// exercise
		double y = p.linearInterpolation(y1, y2, x1, x2, x);

		// verify
		assert(x1 == 165.0);
		assert(y1 == 2498.6);
		assert(x2 == 1564.0);
		assert(y2 == 7566.5);
		assert(x == 3254.9);
		assert(closeEnough(y, 13691.812, 0.001));

		// teardown
	}

};