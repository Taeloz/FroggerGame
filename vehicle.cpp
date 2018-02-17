/*********************************************************************************
FroggerGame - Vehicle functions
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/24/2017
Last Update - 4/24/2017

This file provides the functions used by the Vehicle class.
*********************************************************************************/
#include <SDL.h>

#include "header.h"
#include "vehicle.h"

/**=====================================================**
Vehicle Constructor

This function initializes the vehicle object.
**======================================================**/
Vehicle::Vehicle(int fwidth, int fheight, int nframes, int nsprites):
    GameObject(fwidth, fheight, nframes, nsprites)
{
    reset();
}



/**=====================================================**
reset Function

This function sets the vehicle object to a random lane
on the road and positions it just offscreen to the left.

If it is in the middle lane, the vehicle is rotated and
set offscreen to the right.
**======================================================**/
void Vehicle::reset()
{
    randomSprite();
    randomPosition(0, 0, 350, 490, 50, 50);
    rotation = (screen.y == 400) ? 180 : 0;
    screen.x = (screen.y == 400) ? SCREEN_WIDTH : -image.w;
}



/**=====================================================**
moveSprite Function

Moves the vehicle to the right, or to the left if the
vehicle is in the middle lane.
**======================================================**/
void Vehicle::moveSprite()
{
    if (screen.y == 350) {
        translate(FAST_VEHICLE_SPEED, 0);
        if (screen.x > SCREEN_WIDTH){
            reset();
            active = false;
        }
    } else if (screen.y == 400) {
        translate(-1 * VEHICLE_SPEED, 0);
        if (screen.x < -image.w){
            reset();
            active = false;
        }
    } else {
        translate(VEHICLE_SPEED, 0);
        if (screen.x > SCREEN_WIDTH){
            reset();
            active = false;
        }
    }
}
