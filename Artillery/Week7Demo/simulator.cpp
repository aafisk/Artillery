/*************************************************************
 * 1. Name:
 *      The Key
 * 2. Assignment Name:
 *      Lab 08: M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "test.h"
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "bullet.h"     // for BULLET
#include "ground.h"     // for GROUND
#include "howitzer.h"   // for HOWITZER
#include "position.h"   // for POSITION

#define MUZZLE_VELOCITY 827.0
#define INTERVAL 0.5
#define RADIUS 0.15489 / 2
#define SHELL_MASS 46.7

using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
    Demo(Position ptUpperRight) :
        ptUpperRight(ptUpperRight),
        ground(ptUpperRight),
        time(0.0)
        //angle(0.0)
    {
        // Set the horizontal position of the howitzer. This should be random.
        howitzer.setHorizontalPosition(ptUpperRight);
        //ptHowitzer.setPixelsX(Position(ptUpperRight).getPixelsX() / 2.0);

        // Generate the ground and set the vertical position of the howitzer.
        //Position* posHowitzer = howitzer.getPosition();
        /*cout << posHowitzer.getMetersX() << ", " << posHowitzer.getMetersY();*/
        //ground.reset(ptHowitzer);
        double howitzerElevation = ground.reset(howitzer.getPosition());
        howitzer.setVerticalPosition(howitzerElevation);

        // This is to make the bullet travel across the screen. Notice how there are 
        // 20 pixels, each with a different age. This gives the appearance
        // of a trail that fades off in the distance.
        for (int i = 0; i < 20; i++)
        {
            projectilePath[i].setPixelsX((double)i * 2.0);
            projectilePath[i].setPixelsY(ptUpperRight.getPixelsY() / 1.5);
        }
    }

    Ground ground;                      // the ground
    Position  projectilePath[20];       // path of the projectile
    //Position  ptHowitzer;               // location of the howitzer
    Position  ptUpperRight;             // size of the screen
    Bullet bullet;                      // Bullet object
    Howitzer howitzer;                  // Howitzer object
    Physics physics; // All the phyics and other calc
    double time;                        // amount of time since the last firing
    
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
    // the first step is to cast the void pointer into a game object. This
    // is the first step of every single callback function in OpenGL. 
    Demo* pDemo = (Demo*)p;
    //Physics p = pDemo->physics;

    //
    // accept input
    //

    // move a large amount
    if (pUI->isRight())
        //pDemo->angle += 0.05;
        pDemo->howitzer.rotateRight();
    if (pUI->isLeft())
        //pDemo->angle -= 0.05;
        pDemo->howitzer.rotateLeft();
    // move by a little
    if (pUI->isUp())
        //pDemo->angle += (pDemo->angle >= 0 ? -0.003 : 0.003);
        pDemo->howitzer.rotateUp();
    if (pUI->isDown())
        //pDemo->angle += (pDemo->angle >= 0 ? 0.003 : -0.003);
        pDemo->howitzer.rotateDown();
    
    // fire that gun
    if (pUI->isSpace())
    {
        //physics.computeHorizontalComponent(pDemo->howitzer.getAngle(), MUZZLE_VELOCITY);
		//physics.computeVerticalComponent(pDemo->howitzer.getAngle(), MUZZLE_VELOCITY);
        //pDemo->howitzer.fire();
        pDemo->bullet.launch(pDemo->howitzer.getPosition(), 
            Velocity(pDemo->physics.computeHorizontalComponent(pDemo->howitzer.getAngle(), MUZZLE_VELOCITY), 
            pDemo->physics.computeVerticalComponent(pDemo->howitzer.getAngle(), MUZZLE_VELOCITY)));
        pDemo->time = 0.0;
    }

    //
    // perform all the game logic
    //

    // Update the bullet's position if airborne
    if (pDemo->bullet.getIsAirborne())
    {
        // Various environmental factors
        // double velocity = pDemo->physics.computeTotalComponent(dx, dy);
        double altitude = pDemo->bullet.getPosition().getMetersY();
        Velocity velocity;
        double dx = pDemo->bullet.getDx();
        double dy = pDemo->bullet.getDy();
        Position position;
        double x = pDemo->bullet.getPosition().getMetersX();

        double airDensity = pDemo->physics.airDensityFromAltitude(altitude);
        double machAtAltitude = pDemo->physics.speedOfSoundFromAltitude(altitude);
        double mach = pDemo->bullet.getVelocity() / machAtAltitude;
        //cout << "mach: " << mach;
        double dragCoefficient = pDemo->physics.dragFromMach(mach);
        double surfaceArea = pDemo->physics.areaFromRadius(RADIUS);

        // Acceleration
        // Expected: Distance: 19988.3m   Altitude: -1.50481m   Hang Time: 37.01s
        double ddx = pDemo->physics.forceFromDrag(dragCoefficient, airDensity, dx, pDemo->bullet.getVelocity(), surfaceArea) / SHELL_MASS;

        double ddy = pDemo->physics.gravityFromAltitude(altitude) +
            pDemo->physics.forceFromDrag(dragCoefficient, airDensity, dy, pDemo->bullet.getVelocity(), surfaceArea) / SHELL_MASS;

        //cout << "\tddx/ddy: " << ddx  << "/" << ddy;

        // Velocity
        dx = pDemo->physics.computeVelocity(dx, ddx, INTERVAL);
        dy = pDemo->physics.computeVelocity(dy, ddy, INTERVAL);

        velocity.setDx(dx);
        velocity.setDy(dy);

        pDemo->bullet.updateVelocity(velocity);

        //cout << "\dx/dy: " << dx << "/" << dy;

       // velocity = physics.computeTotalComponent(dx, dy)

       // Calculate horizontal and vertical distance
       
        x = pDemo->physics.computeDistance(x, dx, ddx, INTERVAL);
        altitude = pDemo->physics.computeDistance(altitude, dy, ddy, INTERVAL);

        // Update position
        position.setMetersX(x);
        position.setMetersY(altitude);

        pDemo->bullet.updatePosition(position);

        //cout << "\tx/y: " << x << "/" << y << endl;

        // Update altitude
        // altitude = position.getMetersY();

        // hangTime += interval;

        //// Previous and current distance for interpolation
        //flightPath[0] = flightPath[1];
        //flightPath[1] = position.getMetersX();

        //// Previous and current altitude for interpolation
        //flightPath[2] = flightPath[3];
        //flightPath[3] = position.getMetersY();

        //cout << "Distance: " << position.getMetersX() << " m"
        //    << "\tAltitude: " << position.getMetersY() << " m"
        //    << "\tHang Time: " << hangTime << " s" << endl;

     }

 

    // Check if the ground is hit

    if (pDemo->ground.getElevationMeters(pDemo->bullet.getPosition()) > pDemo->bullet.getPosition().getMetersY())
    {
        pDemo->bullet.setIsAirborne(false);

        pDemo->bullet.setHitGround(true);
        pDemo->time = 0.0;

        // Check if the target is hit
        if ((pDemo->ground.getTarget().getPixelsX() + 5 > pDemo->bullet.getPosition().getPixelsX() &&
			pDemo->ground.getTarget().getPixelsX() - 5 < pDemo->bullet.getPosition().getPixelsX()))
		{
			pDemo->bullet.setTargetHit(true);
			cout << "target" << endl;
		}
    }


    // advance time by half a second.
    if (pDemo->bullet.getIsAirborne())
        pDemo->time += 0.5;

    //
    // draw everything
    //

    // ***************************************************************************************88
    // TO-DO
    ogstream gout(Position(pDemo->ptUpperRight.getPixelsY() - 50.0, pDemo->ptUpperRight.getPixelsY() - 20.0));

    // draw the ground first
    pDemo->ground.draw(gout);

    // draw the howitzer
    //gout.drawHowitzer(pDemo->ptHowitzer, pDemo->angle, pDemo->time);
    pDemo->howitzer.draw(gout, pDemo->time);

    // draw the projectile and its trail
    pDemo->bullet.draw(gout);


    /* 
    Draw the stats
    */
    // draw some text on the screen
    gout.setf(ios::fixed | ios::showpoint);
	gout.precision(2);
    //gout << "Time since the bullet was fired: "
    //    << pDemo->time << "s\n";

	// Draw the HUD
	//gout.setPosition(Point(15.0, 400.0 - 15.0));

    double horizontalDistanceTraveled = pDemo->bullet.getPosition().getMetersX() - pDemo->howitzer.getPosition().getMetersX();

	// Set decimal precision
	//gout.setf(ios::fixed);

	gout << "Altitude:       " << pDemo->bullet.getPosition().getMetersY() << " m\n" <<
		"Speed:  " << pDemo->bullet.getVelocity() << " m/s\n"                                   
		"Distance:    " << horizontalDistanceTraveled << "m\n"               
	    "Hang Time: " << pDemo->time << "seconds\n";
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ PWSTR pCmdLine,
    _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
    // Run tests
    //TestRunner().run();

    // Initialize OpenGL
    Position ptUpperRight;
    ptUpperRight.setPixelsX(700.0);
    ptUpperRight.setPixelsY(500.0);
    Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
    Interface ui(0, NULL,
        "Demo",   /* name on the window */
        ptUpperRight);

    // Initialize the demo
    Demo demo(ptUpperRight);

    // set everything into action
    ui.run(callBack, &demo);


    return 0;
}
