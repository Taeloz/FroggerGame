/*********************************************************************************
WaterVehicle Header
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/28/2017
Last Update - 4/24/2017

The following header file contains the class structure for the WaterVehicle object.

Inherits from GameObject.
*********************************************************************************/
#ifndef watervehicle_h
#define watervehicle_h

#include <SDL.h>
#include "gameObject.h"

/**=====================================================**
Vehicle class

This class holds the functions and objects pertaining to
the watervehicle game objects. Inherits from GameObject.
**======================================================**/
class WaterVehicle: public GameObject
{
private:
    bool isBoat;

public:
    WaterVehicle(bool isABoat = false, int fwidth = 50, int fheight = 50, int nframes = 4, int nsprites = 1);

    void moveSprite(); //Moves the vehicle
};

#endif // watervehicle_h
