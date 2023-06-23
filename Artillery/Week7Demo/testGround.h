/***********************************************************************
 * Header File:
 *    Test Ground : Test the ground class
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the unit tests for the Ground class
 ************************************************************************/


#pragma once

#include "ground.h"
#include <cassert>
#include <vector>


using namespace std;

/*******************************
 * TEST GROUND
 * A friend class for Ground which contains the Ground unit tests
 ********************************/
class TestGround
{
public:
    void run()
    {
        constructor();

        getElevationMeters_out();
        getElevationMeters_two();

        reset_two();

        getTarget_two();
        getTarget_seven();

        draw();
    }

private:

    // Test the default constructor
    void constructor()
    {  // setup
        Position posUpperRight;
        posUpperRight.setPixelsX(4);
        posUpperRight.setPixelsY(5);
        // exercise
        Ground g(posUpperRight);
        // verify
        assert(g.iHowitzer == 0);
        assert(g.ground != nullptr);
        assert(g.posUpperRight.getPixelsX() == 4);
        assert(g.posUpperRight.getPixelsY() == 5);
        assert(posUpperRight.getPixelsX() == 4);
        assert(posUpperRight.getPixelsY() == 5);
    }  // teardown

    // when the shell is out of range
    void getElevationMeters_out()
    {  // setup
        Position pos;
        double zoom = pos.getZoom();
        pos.setZoom(1100.0);
        pos.setPixelsX(-1);
        pos.setPixelsY(4);
        Ground g;
        setupStandardFixture(g);
        // exercise
        double elevation = g.getElevationMeters(pos);
        // verify
        assert(elevation == 0.0);
        verifyStandardFixture(g);
        // teardown
        pos.setZoom(zoom);
    }  // teardown

    // The shell is 2 pixels above the ground
    void getElevationMeters_two()
    {  // setup
        Position pos;
        double zoom = pos.getZoom();
        pos.setZoom(1100.0);
        pos.setPixelsX(2);
        pos.setPixelsY(9);
        Ground g;
        setupStandardFixture(g);
        // exercise
        double elevation = g.getElevationMeters(pos);
        // verify
        assert(elevation == 7700.0);  // 7 pixels high or 7700m
        verifyStandardFixture(g);
        // teardown
        pos.setZoom(zoom);
    }

    // The shell is 2 pixels above the ground
    void reset_two()
    {  // setup
        Position posHowitzer;
        Ground g;
        setupStandardFixture(g);
        posHowitzer.setPixelsX(3.0);
        posHowitzer.setPixelsY(4.0);
        // exercise
        g.reset(posHowitzer);
        // verify
        assert(g.iHowitzer == 3);
        assert(g.iTarget >= 0 && g.iTarget < 10);
        assert(g.posUpperRight.getPixelsX() == 10.0);
        assert(g.posUpperRight.getPixelsY() == 10.0);
        assert(g.ground != nullptr);
        if (g.ground != nullptr)
        {
            assert(g.ground[0] >= 0.0 && g.ground[0] < 10.0);
            assert(g.ground[1] >= 0.0 && g.ground[1] < 10.0);
            assert(g.ground[2] >= 0.0 && g.ground[2] < 10.0);
            assert(g.ground[3] >= 0.0 && g.ground[3] < 10.0);
            assert(g.ground[4] >= 0.0 && g.ground[4] < 10.0);
            assert(g.ground[5] >= 0.0 && g.ground[5] < 10.0);
            assert(g.ground[6] >= 0.0 && g.ground[6] < 10.0);
            assert(g.ground[7] >= 0.0 && g.ground[7] < 10.0);
            assert(g.ground[8] >= 0.0 && g.ground[8] < 10.0);
            assert(g.ground[9] >= 0.0 && g.ground[9] < 10.0);
        }
    }  // teardown


    // The shell is 2 pixels above the ground
    void getTarget_two()
    {  // setup
        Position pos;
        Ground g;
        setupStandardFixture(g);
        int iTargetSave = g.iTarget;
        g.iTarget = 2;
        // exercise
        Position posTarget = g.getTarget();
        // verify
        assert(posTarget.getPixelsX() == 2.0);
        assert(posTarget.getPixelsY() == 7.0);
        g.iTarget = iTargetSave;
        verifyStandardFixture(g);
    }  // teardown

    // The shell is 7 pixels above the ground
    void getTarget_seven()
    {  // setup
        Position pos;
        Ground g;
        setupStandardFixture(g);
        int iTargetSave = g.iTarget;
        g.iTarget = 7;
        // exercise
        Position posTarget = g.getTarget();
        // verify
        assert(posTarget.getPixelsX() == 7.0);
        assert(posTarget.getPixelsY() == 2.0);
        g.iTarget = iTargetSave;
        verifyStandardFixture(g);
    }  // teardown

    // Spy to see exactly what ogstream::draw*() methods are called... and how.
    class ogstreamSpy : public ogstreamDummy
    {
    public:
        // ignore lines
        void drawLine(const Position& begin, const Position& end,
            double red, double green, double blue) { }
        // ignore text
        void drawText(const Position& topLeft, const char* text) { }
        // flush is a no-op
        void flush() { }
        // remember target
        void drawTarget(const Position& pos)
        {
            targets.push_back(pos);
        }
        // remember rectangles
        void drawRectangle(const Position& begin, const Position& end,
            double red, double green, double blue)
        {
            rectanglesBegin.push_back(begin);
            rectanglesEnd.push_back(end);
        }
        vector <Position>  targets;
        vector <Position>  rectanglesBegin;
        vector <Position>  rectanglesEnd;
    };

    // draw
    void draw()
    {  // setup
        Position pos;
        Ground g;
        setupStandardFixture(g);
        ogstreamSpy goutSpy;
        // exercise
        g.draw(goutSpy);
        // verify
        assert(goutSpy.targets.size() == 1);
        assert(0 <= goutSpy.targets.front().getPixelsX() && goutSpy.targets.front().getPixelsX() < 10);
        assert(0 <= goutSpy.targets.front().getPixelsY() && goutSpy.targets.front().getPixelsY() < 10);
        assert(goutSpy.rectanglesBegin.size() == 10);
        assert(goutSpy.rectanglesEnd.size() == 10);
        assert(goutSpy.rectanglesBegin[0].getPixelsX() == 0);
        assert(goutSpy.rectanglesBegin[1].getPixelsX() == 1);
        assert(goutSpy.rectanglesBegin[2].getPixelsX() == 2);
        assert(goutSpy.rectanglesBegin[3].getPixelsX() == 3);
        assert(goutSpy.rectanglesBegin[4].getPixelsX() == 4);
        assert(goutSpy.rectanglesBegin[5].getPixelsX() == 5);
        assert(goutSpy.rectanglesBegin[6].getPixelsX() == 6);
        assert(goutSpy.rectanglesBegin[7].getPixelsX() == 7);
        assert(goutSpy.rectanglesBegin[8].getPixelsX() == 8);
        assert(goutSpy.rectanglesBegin[9].getPixelsX() == 9);
        assert(goutSpy.rectanglesBegin[0].getPixelsY() == 0);
        assert(goutSpy.rectanglesBegin[1].getPixelsY() == 0);
        assert(goutSpy.rectanglesBegin[2].getPixelsY() == 0);
        assert(goutSpy.rectanglesBegin[3].getPixelsY() == 0);
        assert(goutSpy.rectanglesBegin[4].getPixelsY() == 0);
        assert(goutSpy.rectanglesBegin[5].getPixelsY() == 0);
        assert(goutSpy.rectanglesBegin[6].getPixelsY() == 0);
        assert(goutSpy.rectanglesBegin[7].getPixelsY() == 0);
        assert(goutSpy.rectanglesBegin[8].getPixelsY() == 0);
        assert(goutSpy.rectanglesBegin[9].getPixelsY() == 0);
        assert(goutSpy.rectanglesEnd[0].getPixelsX() == 1);
        assert(goutSpy.rectanglesEnd[1].getPixelsX() == 2);
        assert(goutSpy.rectanglesEnd[2].getPixelsX() == 3);
        assert(goutSpy.rectanglesEnd[3].getPixelsX() == 4);
        assert(goutSpy.rectanglesEnd[4].getPixelsX() == 5);
        assert(goutSpy.rectanglesEnd[5].getPixelsX() == 6);
        assert(goutSpy.rectanglesEnd[6].getPixelsX() == 7);
        assert(goutSpy.rectanglesEnd[7].getPixelsX() == 8);
        assert(goutSpy.rectanglesEnd[8].getPixelsX() == 9);
        assert(goutSpy.rectanglesEnd[9].getPixelsX() == 10);
        assert(goutSpy.rectanglesEnd[0].getPixelsY() == 9);
        assert(goutSpy.rectanglesEnd[1].getPixelsY() == 8);
        assert(goutSpy.rectanglesEnd[2].getPixelsY() == 7);
        assert(goutSpy.rectanglesEnd[3].getPixelsY() == 6);
        assert(goutSpy.rectanglesEnd[4].getPixelsY() == 5);
        assert(goutSpy.rectanglesEnd[5].getPixelsY() == 4);
        assert(goutSpy.rectanglesEnd[6].getPixelsY() == 3);
        assert(goutSpy.rectanglesEnd[7].getPixelsY() == 2);
        assert(goutSpy.rectanglesEnd[8].getPixelsY() == 1);
        assert(goutSpy.rectanglesEnd[9].getPixelsY() == 0);
        verifyStandardFixture(g);
    }  // teardown


    //
    // STANDARD FIXTURE
    //


    // standard fixture: 10 x 10 with howitzer at 5 and target at 7
    void setupStandardFixture(Ground& g)
    {
        // delete the old
        if (g.ground != nullptr)
            delete[] g.ground;
        g.ground = new double[10];

        for (int i = 0; i < 10; i++)
            g.ground[i] = 9.0 - (double)i;

        g.posUpperRight.setPixelsX(10.0);
        g.posUpperRight.setPixelsY(10.0);
        g.iHowitzer = 5;
        g.iTarget = 7;
    }

    // verify the standard fixture: 10 x 10 with howitzer at 5 and target at 7
    void verifyStandardFixture(Ground& g)
    {
        assert(g.iHowitzer == 5);
        assert(g.iTarget == 7);
        assert(g.posUpperRight.getPixelsX() == 10);
        assert(g.posUpperRight.getPixelsY() == 10);
        assert(g.ground != nullptr);
        if (g.ground != nullptr)
        {
            assert(g.ground[0] == 9.0);
            assert(g.ground[1] == 8.0);
            assert(g.ground[2] == 7.0);
            assert(g.ground[3] == 6.0);
            assert(g.ground[4] == 5.0);
            assert(g.ground[5] == 4.0);
            assert(g.ground[6] == 3.0);
            assert(g.ground[7] == 2.0);
            assert(g.ground[8] == 1.0);
            assert(g.ground[9] == 0.0);
        }
    }
};
