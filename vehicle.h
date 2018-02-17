/*********************************************************************************
Vehicle Header
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/24/2017
Last Update - 4/24/2017

The following header file contains the class structure for the vehicle object.

Inherits from GameObject.
*********************************************************************************/
#ifndef vehicle_h
#define vehicle_h

#include <SDL.h>
#include "gameObject.h"

/**=====================================================**
Vehicle class

This class holds the functions and objects pertaining to
the vehicle game objects. Inherits from GameObject.
**======================================================**/
class Vehicle: public GameObject
{
public:
    Vehicle(int fwidth = 50, int fheight = 50, int nframes = 4, int nsprites = 1);

    bool active; //Determines if the vehicle needs to be given a new position or not

    void reset(); //Resets the vehicle to a random lane with a random sprite
    void moveSprite(); //Moves the vehicle
};

#endif // vehicle_h
