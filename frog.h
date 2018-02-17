/*********************************************************************************
Frog Header
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/27/2017
Last Update - 4/24/2017

The following header file contains the class structure for the Frog object.

Inherits from GameObject.
*********************************************************************************/
#ifndef frog_h
#define frog_h

#include "gameObject.h"

/**=====================================================**
Frog class

This class holds the functions and objects pertaining to
the Frog player object. Inherits from GameObject.
**======================================================**/
class Frog: public GameObject
{
protected:
    //Flag to prevent player control while frog is moving
    bool inMotion;

    //Values for the destination coordinate on screen. Required for movement by step-value.
    int destX, destY;

    //Speed as double values for more precise movement
    double dx, dy;


public:
    static bool occupied[4];

    //Constructor
    Frog(int fwidth = 50, int fheight = 50, int nframes = 4, int nsprites = 1);

    //Flags to keep track if frog is on logs or boats. Used for drowing check.
    bool onUpperLog, onLowerLog, onBoat;

    //Setter functions
    void setDest(int x, int y); //Set destination coordinate
    void setOccupied(int i); //Set specific pad to occupied

    //Getter functions
    int getDestX(); //Gets destX
    int getDestY(); //Gets destY
    bool isInMotion(); //Returns value of inMotion
    bool isOccupied(int i);
    bool allPadsOccupied();

    //Set the frog in motion
    void setMotion(double motionx, double motiony);

    //Moves the frog
    void moveFrog();

    //Resets the frog to starting conditions
    void reset();

    //Reset the pads
    void resetPads();

};


#endif // frog_h
