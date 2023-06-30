/***********************************************************************
 * Source File:
 *    Ground : Represents the ground in the artillery simulation
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Where the ground is located and where the target is drawn
 ************************************************************************/

#include "ground.h"   // for the Ground class definition
#include "uiDraw.h"   // for random() and drawLine()
#include <cassert>

const int WIDTH_HOWITZER = 14;

const double MIN_ALTITUDE = 300.0;  // min altitude is at 984ft
const double MAX_ALTITUDE = 3000.0; // max altitude is 3,000m or 9842.52ft
const double MAX_SLOPE = 1.0;       // steepness of the features. Smaller number is flatter
const double LUMPINESS = 0.15;      // size of the hills. Smaller number is bigger features
const double TEXTURE = 3.0;         // size of the small features such as rocks

/************************************************************************
 * GROUND :: CONSTRUCTOR
 * Set everything up, but do not initialize it yet.
 ************************************************************************/
Ground::Ground(const Position& posUpperRight) :
    posUpperRight(posUpperRight),
    iHowitzer(0),
    iTarget(0),
    ground(nullptr)
{
    // allocate the array
    ground = new double[(int)posUpperRight.getPixelsX()];
}

/************************************************************************
 * GROUND :: GET ELEVATION METERS
 * Determine the elevation of the ground at pos.getMetersX().
 * This will be the elevation in meters above sea level,
 * where sea level is getMetersY() == 0
 ************************************************************************/
double Ground::getElevationMeters(const Position& pos) const
{
    Position posImpact(pos);

    if (pos.getPixelsX() >= 0.0 && pos.getPixelsX() < (int)posUpperRight.getPixelsX())
        posImpact.setPixelsY(ground[(int)pos.getPixelsX()]);
    else
        posImpact.setPixelsY(0.0);

    return posImpact.getMetersY();
}

/************************************************************************
 * GROUND :: GET TARGET
 * Where the the target located?
 ************************************************************************/
Position Ground::getTarget() const
{
    assert(iTarget >= 0 && iTarget < posUpperRight.getPixelsX());
    Position posTarget;
    posTarget.setPixelsX(iTarget);
    posTarget.setPixelsY(ground[iTarget]);
    return posTarget;
}


/************************************************************************
 * GROUND :: RESET
 * Note that the howitzer's Y position will be updated when the ground is
 * reset because only then can we know its elevation. posHowitzer is by-reference
 * and not const-by-reference for this purpose.
 *************************************************************************/
double Ground::reset(Position posHowitzer)
{
    // remember the integer width for later. It will come in handy
    int width = (int)posUpperRight.getPixelsX();
    assert(width > 0);

    // determine the location of the target
    iHowitzer = (int)(posHowitzer.getPixelsX());
    if (iHowitzer > width / 2)
        iTarget = random((int)(width * 0.05), (int)(width * 0.45));
    else
        iTarget = random((int)(width * 0.55), (int)(width * 0.95));
    assert(iTarget >= 0 && iTarget < width);
    assert(iHowitzer >= 0 && iHowitzer < width);

    // determine the maximum and minimum altitude
    Position posMinimum(0.0, MIN_ALTITUDE);
    Position posMaximum(posUpperRight.getMetersX(), MAX_ALTITUDE);

    // give each location on the ground an elevation
    ground[0] = posMinimum.getPixelsY(); // the initial elevation is low
    double dy = MAX_SLOPE / 2.0;  // the initial slope is heavily biased to up
    for (int i = 1; i < width; i++)
    {
        // put the howitzer on flat ground
        if (i > iHowitzer - WIDTH_HOWITZER / 2 &&
            i < iHowitzer + WIDTH_HOWITZER / 2)
        {
            ground[i] = ground[i - 1];
        }
        else
        {
            // what percentage of the elevation were we at?
            double percent = (ground[i - 1] - posMinimum.getPixelsY()) /
                (posMaximum.getPixelsY() - posMinimum.getPixelsY());

            // set the slope of the ground
            dy += (1.0 - percent) * random(0.0, LUMPINESS) +
                (percent)*random(-LUMPINESS, 0.0);
            if (dy > MAX_SLOPE)
                dy = MAX_SLOPE;
            if (dy < -MAX_SLOPE)
                dy = -MAX_SLOPE;

            // determine the elevation according to the slope
            ground[i] = ground[i - 1] + dy + random(-TEXTURE, TEXTURE);
            assert(ground[i] >= 0.0 && ground[i] <= posUpperRight.getPixelsY());
        }
    }

    // set the howitzer's elevation
    // posHowitzer.setPixelsY(ground[iHowitzer]);
    return ground[iHowitzer];
}

/*****************************************************************
 * GROUND :: DRAW
 * Draw the ground on the screen
 ****************************************************************/
void Ground::draw(ogstream& gout) const
{
    // put the meter markers along the side
    for (Position pos(0.0, 1000.0); pos.getPixelsY() < posUpperRight.getPixelsY(); pos.addMetersY(1000.0))
    {
        Position posLeft(pos);
        Position posRight(pos);
        posRight.setPixelsX(posUpperRight.getPixelsX());
        gout.drawLine(posLeft, posRight, 0.85, 0.85, 0.85);
    }

    // iterate through the entire ground and draw it all
    int width = (int)posUpperRight.getPixelsX();
    for (int i = 0; i < width; i++)
    {
        Position posBottom;
        Position posTop;
        posBottom.setPixelsX((double)i);
        posTop.setPixelsX((double)i + 1.0);
        posTop.setPixelsY(ground[i]);
        gout.drawRectangle(posBottom, posTop, 0.6 /*red*/, 0.4 /*green*/, 0.2 /*blue*/);
    }

    // draw the target
    Position posTarget = getTarget();
    gout.drawTarget(posTarget);

    // put the kilometer markers along the bottom
    for (Position pos(1000.0, 0.0); pos.getPixelsX() < posUpperRight.getPixelsX(); pos.addMetersX(1000.0))
    {
        Position posBottom(pos);
        Position posTop(pos);
        posTop.addPixelsY(10);
        gout.drawLine(posTop, posBottom, 0.6, 0.6, 0.6);
    }

    // put the kilometer labels along the bottom
    for (Position pos(5000.0, 0.0); pos.getPixelsX() < posUpperRight.getPixelsX(); pos.addMetersX(5000.0))
    {
        Position posText(pos);
        posText.addPixelsY(15);
        posText.addPixelsX(-10);

        gout = posText;
        gout << (int)(pos.getMetersX() / 1000.0) << "km";
    }

    // draw the altitude labels along the side
    for (Position pos(0.0, 2000.0); pos.getPixelsY() < posUpperRight.getPixelsY(); pos.addMetersY(2000.0))
    {
        Position posText(pos);
        posText.addPixelsX(5);
        posText.addPixelsY(-2);

        gout = posText;
        gout << (int)(pos.getMetersY()) << "m";
    }
}
