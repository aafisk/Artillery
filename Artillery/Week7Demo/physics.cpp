/*********************************
* Authors:
*	Aaron Fisk
*	Tim Orgill
*
* Project:
*	Artillery Simulator
***********************************/

#include "physics.h"
#include <iostream>

using namespace std;

#define PI 3.1415926535897

Physics::Physics()
{
    altitudeGravity = { {0,     -9.807},
                        {1000,  -9.804},
                        {2000,  -9.801},
                        {3000,  -9.797},
                        {4000,  -9.794},
                        {5000,  -9.791},
                        {6000,  -9.788},
                        {7000,  -9.785},
                        {8000,  -9.782},
                        {9000,  -9.779},
                        {10000, -9.776},
                        {15000, -9.761},
                        {20000, -9.745},
                        {25000, -9.730} };

    // The speed of sound at different altitudes {altitude, speed of sound}
    altitudeSpeedOfSound = { {0,     340.0},
                             {1000,  336.0},
                             {2000,  332.0},
                             {3000,  328.0},
                             {4000,  324.0},
                             {5000,  320.0},
                             {6000,  316.0},
                             {7000,  312.0},
                             {8000,  308.0},
                             {9000,  303.0},
                             {10000, 299.0},
                             {15000, 295.0},
                             {20000, 295.0},
                             {25000, 295.0},
                             {30000, 305.0},
                             {40000, 324.0} };

    // Air density at different altitudes {altitude, air density}
    altitudeAirDensity = { {0,     1.2250000},
                           {1000,  1.1120000},
                           {2000,  1.0070000},
                           {3000,  0.9093000},
                           {4000,  0.8194000},
                           {5000,  0.7364000},
                           {6000,  0.6601000},
                           {7000,  0.5900000},
                           {8000,  0.5258000},
                           {9000,  0.4671000},
                           {10000, 0.4135000},
                           {15000, 0.1948000},
                           {20000, 0.0889100},
                           {25000, 0.0400800},
                           {30000, 0.0184100},
                           {40000, 0.0039960},
                           {50000, 0.0010270},
                           {60000, 0.0003097},
                           {70000, 0.0000828},
                           {80000, 0.0000185} };

    // The drag coefficient at different machs {mach, drag coefficient}
    machDrag = { {0.0,   0.0},
                 {0.300, 0.1629},
                 {0.500, 0.1659},
                 {0.700, 0.2031},
                 {0.890, 0.2597},
                 {0.920, 0.3010},
                 {0.960, 0.3287},
                 {0.980, 0.4002},
                 {1.000, 0.4258},
                 {1.020, 0.4335},
                 {1.060, 0.4483},
                 {1.240, 0.4064},
                 {1.530, 0.3663},
                 {1.990, 0.2897},
                 {2.870, 0.2297},
                 {2.890, 0.2306},
                 {5.000, 0.2656} };
}

/***********************************************
* COMPUTE VERTICAL COMPONENT
* Find the vertical component of a velocity or acceleration.
* The equation is:
*     cos(a) = y / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     y : the vertical component of the total
***********************************************/
double Physics::computeVerticalComponent(double a, double total)
{
    double y = cos(a) * total;
    return y;
}

/***********************************************
* COMPUTE HORIZONTAL COMPONENT
* Find the horizontal component of a velocity or acceleration.
* The equation is:
*     sin(a) = x / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     x : the vertical component of the total
***********************************************/
double Physics::computeHorizontalComponent(double a, double total)
{
    double y = sin(a) * total;
    return y;
}

/*************************************************
* RADIANS FROM DEGEES
* Convert degrees to radians:
*     radians / 2pi = degrees / 360
* INPUT
*     d : degrees from 0 to 360
* OUTPUT
*     r : radians from 0 to 2pi
**************************************************/
double Physics::radiansFromDegrees(double d)
{
    double r = (d / 360) * 2 * PI;
    return r;
}

/************************************************
* COMPUTE TOTAL COMPONENT
* Given the horizontal and vertical components of
* something (velocity or acceleration), determine
* the total component. To do this, use the Pythagorean Theorem:
*    x^2 + y^2 = t^2
* where:
*      x
*    +-----
*    |   /
*  y |  / total
*    | /
*    |/
* INPUT
*    x : horizontal component
*    y : vertical component
* OUTPUT
*    total : total component
***********************************************/
double Physics::computeTotalComponent(double x, double y)
{
    double total = (x * x) + (y * y);
    return sqrt(total);
}

/***************************************************
* COMPUTE DISTANCE
* Apply inertia to compute a new position using the distance equation.
* The equation is:
*     s = s + v t + 1/2 a t^2
* INPUT
*     s : original position, in meters
*     v : velocity, in meters/second
*     a : acceleration, in meters/second^2
*     t : time, in seconds
* OUTPUT
*     s : new position, in meters
**************************************************/
double Physics::computeDistance(double s, double v, double a, double t)
{
    double newposition = s + (v * t) + (0.5 * a * t * t);
    return newposition;
}

/***********************************************
* COMPUTE VELOCITY
* Starting with a given velocity, find the new
* velocity once acceleration is applied. This is
* called the Kinematics equation. The
* equation is:
*     v = v + a t
* INPUT
*     v : velocity, in meters/second
*     a : acceleration, in meters/second^2
*     t : time, in seconds
* OUTPUT
*     v : new velocity, in meters/second
***********************************************/
double Physics::computeVelocity(double v, double a, double t)
{
    double newVelocity = v + (a * t);
    return newVelocity;
}

/******************************************************
* AREA OF A CIRCLE FORMULA
* Find the surface area of an object. The equation is
*   a = PI r^2
* INPUT
*   r = radius of circle
* OUTPUT
*   a = area of a circle (m^2)
******************************************************/
double Physics::areaFromRadius(double r)
{
    return PI * (r * r);
}

/******************************************************
* DRAG FORCE EQUATION
* Find the drag force of an object. The equation is
*   d = .5c p v^2 a
* INPUT
*   c = drag coefficient
*   p = density of fluid/gas
*   v = total velocity
*   vv = velocity in given direction
*   a = surface area
* OUTPUT
*   d = force in newtons (N)
******************************************************/
double Physics::forceFromDrag(double c, double p, double v, double vv, double a)
{
    return -(0.5 * c * p * v * vv * a);
}

/*************************************************
Linear Interpolation
x1, y1 = coordinates of one point
x2, y2 = coordinates of another point
x (value), y   = coordinates of point in middle
solving for y
**************************************************/
double Physics::linearInterpolation(map<double, double>& map, double value)
{
    double x1 = 0.0;
    double y1 = 0.0;
    auto x2 = map.begin()->first;
    auto y2 = map.begin()->second;

    bool proceed = true;
    auto it = map.begin();
    int count = 0;

    while (it != map.end() && proceed == true)
    {
        if (it != map.begin())
        {
            x1 = x2;
            y1 = y2;
            x2 = it->first;
            y2 = it->second;

            if (x1 <= value && x2 >= value)
            {
                proceed = false;
            }
        }

        it++;
    }

    double y = linearInterpolation(y1, y2, x1, x2, value);
    //double y = y1 + (((value - x1) * (y2 - y1)) / (x2 - x1));
    //cout << "y: " << y << endl;

    return y;
}

double Physics::linearInterpolation(double y1, double y2, double x1, double x2, double value)
{
    double y = y1 + (((value - x1) * (y2 - y1)) / (x2 - x1));
    return y;
}

double Physics::gravityFromAltitude(double altitude)
{
    double gravity = linearInterpolation(altitudeGravity, altitude);
    //cout << "gravity: " << gravity << endl;
    return gravity;
}

double Physics::dragFromMach(double mach)
{
    double drag = linearInterpolation(machDrag, mach);
    return drag;
}

double Physics::airDensityFromAltitude(double altitude)
{
    double airDensity = linearInterpolation(altitudeAirDensity, altitude);
    return airDensity;
}

double Physics::speedOfSoundFromAltitude(double altitude)
{
    double speedOfSound = linearInterpolation(altitudeSpeedOfSound, altitude);
    return speedOfSound;
}