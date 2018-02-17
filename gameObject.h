/*********************************************************************************
GameObject Header
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/24/2017
Last Update - 4/24/2017

The following header file contains the class structure for the game object.

GameObject inherits from Sprite.
*********************************************************************************/
#ifndef gameObject_h
#define gameObject_h

#include "sprite.h"

/**=====================================================**
GameObject class

This class holds the functions and objects pertaining to
a game object. Inherits from Sprite.
**======================================================**/
class GameObject: public Sprite
{
protected:
    //position on screen as doubles for more precise movements
    double posX, posY;

public:
    //Constructor
    GameObject(int fwidth = 50, int fheight = 50, int nframes = 4, int nsprites = 1);

    //Setter functions
    void setPosition(int x, int y); //Specific x and y coordinate on screen
    void randomPosition(int minX, int maxX, int minY, int maxY, int stepX, int stepY); //Random position within bounds and at step values

    //Move the game object
    void translate(double dx, double dy);

    void moveSprite(){};

};

#endif // gameObject_h
