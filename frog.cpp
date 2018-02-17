/*********************************************************************************
FroggerGame - Frog functions
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/27/2017
Last Update - 4/24/2017

This file provides the functions used by the Frog class.
*********************************************************************************/
#include <SDL.h>

#include "frog.h"
#include "header.h"

//Global declaration for the static variable
bool Frog::occupied[4] = {false, false, false, false};

/**=====================================================**
Frog Constructor

This function initializes the movement variables.
**======================================================**/
Frog::Frog(int fwidth, int fheight, int nframes, int nsprites):
    GameObject(fwidth, fheight, nframes, nsprites)
{
    inMotion = false;
    dx = 0;
    dy = 0;
    destX = 0;
    destY = 0;
    onUpperLog = false;
    onLowerLog = false;
    onBoat = false;

    reset();
}



/**=====================================================**
moveFrog Function

This function moves the frog and checks screen boundaries.
It also stops the frog once it has finished moving.
**======================================================**/
void Frog::moveFrog()
{

    translate(dx, dy); //move the frog

    //make sure the frog doesn't go past the screen edge
    //and stop the movement if it does.
    if (getX() < 0) {
        //If trying to move off the left of the screen
        //set the position to the edge and stop movement
        setPosition(0, getY());
        inMotion = false;
    }
    if (getX() > SCREEN_WIDTH - 50) {
        //If trying to move off the right of the screen
        //set the position to the edge and stop movement
        setPosition(SCREEN_WIDTH - 50, getY());
        inMotion = false;
    }
    if (getY() < 150)
    {
        //If frog is trying to move at top of screen
        //check to see if it is a pad and if the pad is available
        inMotion = false; //Default to stopping movement unless pad is available
        for (int i = 0; i < 4; i++)
        {
            //Set movement to true if the pad is available
            if (getX() + 20 > 100 + i * 200 && getX() + 40 < 100 + i * 200 + 50 && occupied[i] == false) inMotion = true;
        }
        if (inMotion == false) setPosition(getX(), 150); //If no pad is available, reset position to original y-value
    }

    //Stop movement once destination is reached.
    if (dx > 0 && getX() >= destX) inMotion = false;
    if (dx < 0 && getX() <= destX) inMotion = false;
    if (dy != 0 && getY() == destY) inMotion = false;

    //If movement is stopped, restore the "at rest" sprite
    if (inMotion == false) selectSprite(1);
}



/**=====================================================**
setDest Function

This function sets the destination on the screen that the
frog will move to. This is for the discrete movement.
**======================================================**/
void Frog::setDest(int x, int y)
{
    destX = x;
    destY = y;
}



/**=====================================================**
getDestX Function

This function returns the x-coordinate of the destination.
**======================================================**/
int Frog::getDestX()
{
    return destX;
}



/**=====================================================**
setMotion Function

This function begins the motion of the frog.
**======================================================**/
void Frog::setMotion(double motionx, double motiony)
{
    //Set the speed
    dx = motionx;
    dy = motiony;

    //set the motion flag to true
    inMotion = true;

    //show the movement sprite
    selectSprite(2);
}



/**=====================================================**
reset Function

This function resets the frog to the starting location
with starting parameters.
**======================================================**/
void Frog::reset()
{
    setSprite(50, 50, 4, 2); //Set the sprite
    setPosition(350, 500); //Set the starting position
    setAlpha(255); //make the frog completely visible
    inMotion = false; //Set the motion flag false
    rotation = 0; //Set rotation to face up
}



/**=====================================================**
resetPads Function

This function resets the occupied condition of the lily
pads to false.
**======================================================**/
void Frog::resetPads()
{
    for (int i = 0; i < 4; i++) occupied[i] = false; //reset occupied array
}



/**=====================================================**
setOccupied Function

This function sets the occupied status of a specific
lily pad.

Inputs
    - number of the lily pad to set to occupied
**======================================================**/
void Frog::setOccupied(int i)
{
    occupied[i] = true;
}



/**=====================================================**
isOccupied Function

This function returns whether a specific lily pad is
occupied or not.

Inputs
    - number of the lily pad to check

Outputs
    - true if occupied, false otherwise
**======================================================**/
bool Frog::isOccupied(int i)
{
    return occupied[i];
}



/**=====================================================**
isInMotion Function

This function returns the value of the inMotion flag.

Outputs true if the frog is moving, false otherwise.
**======================================================**/
bool Frog::isInMotion()
{
    return inMotion;
}



/**=====================================================**
allPadsOccupied Function

This function returns whether all pads are occupied or
not.

Outputs true if all pads are occupied, false otherwise.
**======================================================**/
bool Frog::allPadsOccupied()
{
    bool check = true;
    for (int i = 0; i < 4; i++) if (occupied[i]==false) check = false;
    return check;
}
