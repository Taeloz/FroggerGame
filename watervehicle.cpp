/*********************************************************************************
FroggerGame - WaterVehicle functions
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/28/2017
Last Update - 4/24/2017

This file provides the functions used by the WaterVehicle class.
*********************************************************************************/
#include <SDL.h>

#include "header.h"
#include "watervehicle.h"

/**=====================================================**
WaterVehicle Constructor

This function initializes the WaterVehicle object.
**======================================================**/
WaterVehicle::WaterVehicle(bool isABoat, int fwidth, int fheight, int nframes, int nsprites):GameObject(fwidth, fheight, nframes, nsprites)
{
    isBoat = isABoat;
}



/**=====================================================**
moveVehicle Function

Moves the vehicle to the right, or to the left if the
vehicle is in the middle lane.
**======================================================**/
void WaterVehicle::moveSprite()
{
    if (isBoat)
    {
        translate(-1 * BOAT_SPEED, 0);
    } else {
        if (getY() == 150) translate(UPPER_LOG_SPEED, 0);
        if (getY() == 250) translate(LOWER_LOG_SPEED, 0);
    }

    if (getY() == 200 && getX() <= -75)
    {
        setPosition(SCREEN_WIDTH + 75, getY());
    } else if (getX() >= SCREEN_WIDTH + 125)
    {
        setPosition(-125, getY());
    }

}
