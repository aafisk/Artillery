#pragma once
#include <map>

using namespace std;
class TestPhysics;

class Physics
{
    friend TestPhysics;

public:
    Physics();
    double computeVerticalComponent(double a, double total);
    double computeHorizontalComponent(double a, double total);
    double radiansFromDegrees(double d);
    double computeTotalComponent(double x, double y);
    double computeVelocity(double v, double a, double t);
    double computeDistance(double s, double v, double a, double t);
    double areaFromRadius(double r);
    double forceFromDrag(double c, double p, double v, double vv, double a);
    double linearInterpolation(map<double, double>& map, double value);
    double linearInterpolation(double x1, double x2, double y1, double y2, double value);
    double gravityFromAltitude(double altitude);
    double dragFromMach(double mach);
    double airDensityFromAltitude(double altitude);
    double speedOfSoundFromAltitude(double altitude);

private:
    map<double, double>altitudeGravity;
    map<double, double>altitudeSpeedOfSound;
    map<double, double>altitudeAirDensity;
    map<double, double>machDrag;
};

