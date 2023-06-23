/***********************************************************************
 * Source File:
 *    Test : Test runner
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/

#include "test.h"
#include "testPosition.h"
#include "testGround.h"
#include "testBullet.h"
#include "testPhysics.h"

 /*****************************************************************
  * TEST RUNNER
  * Runs all the unit tests
  ****************************************************************/
void TestRunner::run()
{
	TestPosition().run();
	TestGround().run();
	TestBullet().run();
	TestPhysics().run();
	
}
