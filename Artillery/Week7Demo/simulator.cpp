#include "simulator.h"

Simulator::Simulator()
{
    hangTime = 0.0;
    interval = 0.01;
    diameterOfShell = 0.15489; // m
    radius = diameterOfShell / 2;
    shellMass = 46.7; // kg
    initialVelocity = 827.0; // m/s (upon firing)
    //position = Position(0.0, 0.0);
    ddx = 0.0;
    ddy = 0.0;
    velocity = initialVelocity;
    altitude = position.getMetersY();
    surfaceArea = physics.areaFromRadius(radius);
    airDensity = physics.airDensityFromAltitude(altitude);
    machAtAltitude = physics.speedOfSoundFromAltitude(altitude);
    mach = velocity / machAtAltitude;
    dragCoefficient = physics.dragFromMach(mach);
    flightPath = { 0.0, 0.0, 0.0, 0.0 };
}
void Simulator::resetVariables()
{
    Position position(0.0, 0.0);
    hangTime = 0.0;
    interval = 0.01;
    diameterOfShell = 0.15489; // m
    radius = diameterOfShell / 2;
    shellMass = 46.7; // kg
    initialVelocity = 827.0; // m/s (upon firing)
    //position = Position(0.0, 0.0);
    ddx = 0.0;
    ddy = 0.0;
    velocity = initialVelocity;
    altitude = position.getMetersY();
    surfaceArea = physics.areaFromRadius(radius);
    airDensity = physics.airDensityFromAltitude(altitude);
    machAtAltitude = physics.speedOfSoundFromAltitude(altitude);
    mach = velocity / machAtAltitude;
    dragCoefficient = physics.dragFromMach(mach);
    flightPath = { 0.0, 0.0, 0.0, 0.0 };

    //cout << "hangTime: " << hangTime << endl;
    //cout << "interval: " << interval << endl;
    //cout << "diameterOfShell: " << diameterOfShell << endl;
    //cout << "radius: " << radius << endl;
    //cout << "shellMass: " << shellMass << endl;
    //cout << "initialVelocity: " << initialVelocity << endl;
    //// cout << "position: (" << position.getX() << ", " << position.getY() << ")" << endl;
    //cout << "ddx: " << ddx << endl;
    //cout << "ddy: " << ddy << endl;
    //cout << "velocity: " << velocity << endl;
    //cout << "altitude: " << altitude << endl;
    //cout << "surfaceArea: " << surfaceArea << endl;
    //cout << "airDensity: " << airDensity << endl;
    //cout << "machAtAltitude: " << machAtAltitude << endl;
    //cout << "mach: " << mach << endl;
    //cout << "dragCoefficient: " << dragCoefficient << endl;
}

void Simulator::run(double angle)
{
    resetVariables();
    aRadians = physics.radiansFromDegrees(angle);
	dx = physics.computeHorizontalComponent(aRadians, initialVelocity);
	dy = physics.computeVerticalComponent(aRadians, initialVelocity);

    while (position.getMetersY() >= 0.0)
    {
        // Various environmental factors
        velocity = physics.computeTotalComponent(dx, dy);
        airDensity = physics.airDensityFromAltitude(altitude);
        machAtAltitude = physics.speedOfSoundFromAltitude(altitude);
        mach = velocity / machAtAltitude;
        //cout << "mach: " << mach;
        dragCoefficient = physics.dragFromMach(mach);

        // Acceleration
        // Expected: Distance: 19988.3m   Altitude: -1.50481m   Hang Time: 37.01s
        ddx = physics.forceFromDrag(dragCoefficient, airDensity, dx, velocity, surfaceArea) / shellMass;

        ddy = physics.gravityFromAltitude(altitude) +
            physics.forceFromDrag(dragCoefficient, airDensity, dy, velocity, surfaceArea) / shellMass;

         //cout << "\tddx/ddy: " << ddx  << "/" << ddy;


        // Velocity
        dx = physics.computeVelocity(dx, ddx, interval);
        dy = physics.computeVelocity(dy, ddy, interval);

         //cout << "\dx/dy: " << dx << "/" << dy;

        // velocity = physics.computeTotalComponent(dx, dy)

        // Calculate horizontal and vertical distance
        double x = physics.computeDistance(position.getMetersX(), dx, ddx, interval);
        double y = physics.computeDistance(altitude, dy, ddy, interval);

        // Update position
        position.setMetersX(x);
        position.setMetersY(y);

         //cout << "\tx/y: " << x << "/" << y << endl;

        // Update altitude
        altitude = position.getMetersY();

        hangTime += interval;

        // Previous and current distance for interpolation
        flightPath[0] = flightPath[1];
        flightPath[1] = position.getMetersX();

        // Previous and current altitude for interpolation
        flightPath[2] = flightPath[3];
        flightPath[3] = position.getMetersY();

        //cout << "Distance: " << position.getMetersX() << " m"
        //    << "\tAltitude: " << position.getMetersY() << " m"
        //    << "\tHang Time: " << hangTime << " s" << endl;

    }

    // Perform linear interpolation to find distance and time upon ground 
    // impact
    position.setMetersX(physics.linearInterpolation(
        flightPath[0], flightPath[1], flightPath[2], flightPath[3], 0.0));

    hangTime = physics.linearInterpolation(
        hangTime - 0.01, hangTime, flightPath[2], flightPath[3], 0.0);

    cout.setf(ios::fixed | ios::showpoint);
    cout.precision(1);

    // Stats at ground impact
    cout << "Distance: " << position.getMetersX() << " m"
        << "\tHang Time: " << hangTime << " s" << endl;
}


