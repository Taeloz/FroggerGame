/*********************************************************************************
FroggerGame - GameObject functions
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/24/2017
Last Update - 3/27/2017

This file provides the functions used by the GameObject class.
*********************************************************************************/
#include <SDL.h>
#include <cstdlib>

#include "gameObject.h"

/**=====================================================**
GameObject Constructor

This function initializes the position variables.
**======================================================**/
GameObject::GameObject(int fwidth, int fheight, int nframes, int nsprites):
    Sprite(fwidth, fheight, nframes, nsprites)
{
    posX = screen.x;
    posY = screen.y;
}



/**=====================================================**
translate Function

This function translates the game object on the screen.

Input
    -   The desired change in x and y positions.
**======================================================**/
void GameObject::translate(double dx, double dy)
{
    posX += dx;
    posY += dy;

    screen.x = posX;
    screen.y = posY;
}



/**=====================================================**
setPosition Function

This function sets the position of the object to the
given coordinates.

Input
    -   The desired position in x and y coordinates.
**======================================================**/
void GameObject::setPosition(int x, int y)
{
    posX = x;
    posY = y;

    screen.x = posX;
    screen.y = posY;
}



/**=====================================================**
randomPosition Function

This function sets the object to a random position on the
screen based on the inputs.

Input
    -   minX and maxX for x-position.
    -   minY and maxY for y-position.
    -   stepX and stepY to lock the positions
        to a set grid.
**======================================================**/
void GameObject::randomPosition(int minX, int maxX, int minY, int maxY, int stepX, int stepY)
{
    screen.x = ((rand()%((maxX+1)-minX) + minX)/(stepX)) * stepX;
    screen.y = ((rand()%((maxY+1)-minY) + minY)/(stepY)) * stepY;

    posX = screen.x;
    posY = screen.y;
}
