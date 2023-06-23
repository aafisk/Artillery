    /***********************************************************************
 * Source File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock


#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied
#define _USE_MATH_DEFINES
#include <math.h>
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // _WIN32

#include "position.h"
#include "uiDraw.h"

using namespace std;

Position rotatePosition(const Position& origin, double x, double y, double rotation);


/*************************************************************************
 * QUAD
 * Four points and a color
 *************************************************************************/
struct Quad
{
    PT pt1;
    PT pt2;
    PT pt3;
    PT pt4;
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

/*************************************************************************
 * GL RESET COLOR
 * Just a more convenient way to reset the color
 *************************************************************************/
inline void glResetColor()
{
    glColor3f((GLfloat)0.0 /* red % */, (GLfloat)0.0 /* green % */, (GLfloat)0.0 /* blue % */);
}


/*************************************************************************
 * GL VERTEXT POINT
 * Just a more convenient format of glVertext2f
 *************************************************************************/
inline void glVertexPoint(const Position& pos)
{
    glVertex2f((GLfloat)pos.getPixelsX(), (GLfloat)pos.getPixelsY());
}

/*************************************************************************
 * DISPLAY the results on the screen
 *************************************************************************/
void ogstream::flush()
{
    string sOut;
    string sIn = str();

    // copy everything but the newlines
    for (string::iterator it = sIn.begin(); it != sIn.end(); ++it)
        // newline triggers an buffer flush and a move down
        if (*it == '\n')
        {
            drawText(pos, sOut.c_str());
            sOut.clear();
            pos.addPixelsY(-18);
        }
    // othewise append
        else
            sOut += *it;

    // put the text on the screen
    if (!sOut.empty())
    {
        drawText(pos, sOut.c_str());
        pos.addPixelsY(-18);
    }

    // reset the buffer
    str("");
}

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 ************************************************************************/
void ogstream::drawText(const Position& topLeft, const char* text)
{
    void* pFont = GLUT_TEXT;

    // prepare to draw the text from the top-left corner
    glRasterPos2f((GLfloat)topLeft.getPixelsX(), (GLfloat)topLeft.getPixelsY());

    // loop through the text
    for (const char* p = text; *p; p++)
        glutBitmapCharacter(pFont, *p);
}

/************************************************************************
 * DRAW PROJECTILE
 * Draw a projectile on the screen at a given point.
 *   INPUT  pt     The location of the projectile
 *          age    The age in seconds. The younger, the brighter
 *************************************************************************/
void ogstream::drawProjectile(const Position& pos, double age)
{
    const double tailLength = 5.0;

    GLfloat color = (GLfloat)(age / tailLength);

    Position posBegin;
    Position posEnd;
    posBegin.setPixelsX(pos.getPixelsX() - 1.5);
    posBegin.setPixelsY(pos.getPixelsY() - 1.5);
    posEnd.setPixelsX(pos.getPixelsX() + 1.5);
    posEnd.setPixelsY(pos.getPixelsY() + 1.5);
    drawRectangle(posBegin, posEnd, color /* red % */, color /* green % */, color /* blue % */);
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *   INPUT  begin     The position of the beginning of the line
 *          end       The position of the end of the line
 *          r/g/b     The color of the line to be drawn
 *************************************************************************/
void ogstream::drawLine(const Position& begin, const Position& end,
    double red, double green, double blue)
{
    // Get ready...
    glBegin(GL_LINES);
    glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

    // Draw the actual line
    glVertexPoint(begin);
    glVertexPoint(end);

    // Complete drawing
    glResetColor();
    glEnd();
}

/************************************************************************
* DRAW QUAD
* Draw a quad on the screen from the beginning to the end.
*   INPUT QUAD
*************************************************************************/
void drawQuad(const Quad& quad)
{
    // Get ready...
    glBegin(GL_QUADS);
    glColor3f(quad.r, quad.g, quad.b);

    // Draw the actual line
    glVertex2f((GLfloat)quad.pt1.x, (GLfloat)quad.pt1.y);
    glVertex2f((GLfloat)quad.pt2.x, (GLfloat)quad.pt2.y);
    glVertex2f((GLfloat)quad.pt3.x, (GLfloat)quad.pt3.y);
    glVertex2f((GLfloat)quad.pt4.x, (GLfloat)quad.pt4.y);

    // Complete drawing
    glResetColor();
    glEnd();
}

/************************************************************************
* DRAW QUAD
* Draw a quad on the screen from the beginning to the end.
*   INPUT QUAD
*         posRotate
*         angle
*************************************************************************/
void drawQuad(const Quad& quad, const Position posRotate, double angle)
{
    // Get ready...
    glBegin(GL_QUADS);
    glColor3f(quad.r, quad.g, quad.b);

    // Draw the actual line
    glVertexPoint(rotatePosition(posRotate, quad.pt1.x, quad.pt1.y, angle));
    glVertexPoint(rotatePosition(posRotate, quad.pt2.x, quad.pt2.y, angle));
    glVertexPoint(rotatePosition(posRotate, quad.pt3.x, quad.pt3.y, angle));
    glVertexPoint(rotatePosition(posRotate, quad.pt4.x, quad.pt4.y, angle));

    // Complete drawing
    glResetColor();
    glEnd();
}

/************************************************************************
* DRAW RECTRANGLE
* Draw a rectangle on the screen from the beginning to the end.
*   INPUT  begin     The position of the beginning of the line
*          end       The position of the end of the line
*          r/g/b     The color of the line to be drawn
*************************************************************************/
void ogstream::drawRectangle(const Position& begin, const Position& end,
    double red, double green, double blue)
{
    Quad quad =
    {
       {(GLfloat)begin.getPixelsX(), (GLfloat)begin.getPixelsY()},
       {(GLfloat)begin.getPixelsX(), (GLfloat)end.getPixelsY()},
       {(GLfloat)end.getPixelsX(),   (GLfloat)end.getPixelsY()},
       {(GLfloat)end.getPixelsX(),   (GLfloat)begin.getPixelsY()},
       (GLfloat)red, (GLfloat)green, (GLfloat)blue
    };

    drawQuad(quad);
}


/***********************************************************************
 * DRAW Target
 * Draw a target on the screen at a given point
 *    point    The position of the target on the screen
 ***********************************************************************/
void ogstream::drawTarget(const Position& pos)
{
    double size = 10.0;

    // set up to draw a solid rectangle
    glBegin(GL_QUADS);
    glColor3f((GLfloat)0.2 /* red % */, (GLfloat)0.75 /* green % */, (GLfloat)0.2 /* blue % */);

    // specify the corners
    glVertex2f((GLfloat)(pos.getPixelsX() - size / 2.0), (GLfloat)(pos.getPixelsY() - size / 2.0));
    glVertex2f((GLfloat)(pos.getPixelsX() - size / 2.0), (GLfloat)(pos.getPixelsY() + size / 2.0));
    glVertex2f((GLfloat)(pos.getPixelsX() + size / 2.0), (GLfloat)(pos.getPixelsY() + size / 2.0));
    glVertex2f((GLfloat)(pos.getPixelsX() + size / 2.0), (GLfloat)(pos.getPixelsY() - size / 2.0));

    // done
    glResetColor();
    glEnd();
}

/***********************************************************************
 * DRAW Howitzer
 * Draw a howitzer on the screen at a given point
 *    point    The position of the Howitzer on the screen
 *    angle    The angle of the barrel where 0 is straight up
 *    age      Seconds since the howitzer was fired
 ***********************************************************************/
void ogstream::drawHowitzer(const Position& pos, double angle, double age)
{
    // outline for the Muzzle, the Base, and the muzzle flash
    Quad muzzle[] =
    {
       { {-2.0, 8.0}, {2.0, 8.0}, {2.0, 6.5}, {-2.0, 6.5},
         (GLfloat)0.07, (GLfloat)0.08, (GLfloat)0.03},    // aiming stuff
       { {-0.5, 0.0}, {0.5, 0.0}, {0.5, 18.0}, {-0.8, 18.0},
         (GLfloat)0.14, (GLfloat)0.16, (GLfloat)0.06},    // barrel
       { {-1.5, 0.0}, {1.5, 0.0}, {1.5, 10.0}, {-1.5, 10.0},
         (GLfloat)0.29, (GLfloat)0.32, (GLfloat)0.12},    // recoil
    };

    Quad baseLeft[] =
    {
       {{-10.0, 0.0}, {3.0, 0.0}, {3.0, 2.0}, {-7.0, 2.0},
         (GLfloat)0.29, (GLfloat)0.32, (GLfloat)0.12},      // footing
       {{-5.0, 0.0}, {-4.0, 0.0}, {-1.0, 5.0}, {-1.0, 5.0},
         (GLfloat)0.29, (GLfloat)0.32, (GLfloat)0.12},      // muzzle brace
       {{3.0, 0.0}, {3.0, 3.0}, {2.0, 3.0}, {2.0, 0.0},
         (GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0}          // rear brace
    };
    Quad baseRight[] =
    {
       {{ 10.0, 0.0}, {-3.0, 0.0}, {-3.0, 2.0}, {7.0, 2.0},
         (GLfloat)0.29, (GLfloat)0.32, (GLfloat)0.12},      // footing
       {{5.0, 0.0}, {4.0, 0.0}, {1.0, 5.0}, {1.0, 5.0},
         (GLfloat)0.29, (GLfloat)0.32, (GLfloat)0.12},      // muzzle brace
       {{-3.0, 0.0}, {-3.0, 3.0}, {-2.0, 3.0}, {-2.0, 0.0},
         (GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0}          // rear brace
    };
    PT pointsMuzzleFlash[10][2] =
    {
       { {-11,21}, {11,21} },      // least intense
       { {-11,19}, {11,19} },
       { {-15,20}, {15,20} },
       { { -7,21}, { 7,21} },
       { { -7,19}, { 7,19} },
       { {-10,20}, {10,20} },
       { { -2,21}, { 2,21} },
       { { -2,19}, { 2,19} },
       { { -5,20}, { 5,20} },
       { { -2,20}, { 2,20} }      // most intense
    };

    // Draw the base
    for (int i = 0; i < sizeof(baseLeft) / sizeof(Quad); i++)
        if (angle <= 0.0)
            drawQuad(baseLeft[i], pos, 0.0);
        else
            drawQuad(baseRight[i], pos, 0.0);

    // Draw the muzzle
    for (int i = 0; i < sizeof(muzzle) / sizeof(Quad); i++)
        drawQuad(muzzle[i], pos, angle);

    // Now for the muzzle flash
    if (age >= 0.0 && age < 2.0) // flash duration in seconds
    {
        // draw the muzzle flash
        glBegin(GL_LINES);

        for (int i = 0; i < 10; i++)
        {
            GLfloat color = (GLfloat)((10.0 - (double)i) / 10.0);
            glColor3f(1.0 /* red % */, (GLfloat)color /* green % */, (GLfloat)color /* blue % */);
            glVertexPoint(rotatePosition(pos, pointsMuzzleFlash[i][0].x,
                pointsMuzzleFlash[i][0].y, angle));
            glVertexPoint(rotatePosition(pos, pointsMuzzleFlash[i][1].x,
                pointsMuzzleFlash[i][1].y, angle));
        }

        // complete drawing of the muzzle flash
        glResetColor();
        glEnd();
    }
}

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  origin   The center point we will rotate around
 *           x,y      Offset from center that we will be rotating
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
Position rotatePosition(const Position& origin, double x, double y, double rotation)
{
    // because sine and cosine are expensive, we want to call them only once
    double cosA = cos(rotation);
    double sinA = sin(rotation);

    // start with our original point
    Position posReturn(origin);

    // find the new values
    posReturn.addPixelsX(x * cosA + y * sinA);
    posReturn.addPixelsY(y * cosA - x * sinA);

    return posReturn;
}

/******************************************************************
 * RANDOM
 * This function generates a random number.
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int random(int min, int max)
{
    assert(min < max);
    int num = (rand() % (max - min)) + min;
    assert(min <= num && num <= max);

    return num;
}

/******************************************************************
 * RANDOM
 * This function generates a random number.
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the double
 ****************************************************************/
double random(double min, double max)
{
    assert(min <= max);
    double num = min + ((double)rand() / (double)RAND_MAX * (max - min));

    assert(min <= num && num <= max);

    return num;
}





