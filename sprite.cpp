/*********************************************************************************
FroggerGame - Sprite functions
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/23/2017
Last Update - 4/24/2017

This file provides the functions used by the Sprite class.
*********************************************************************************/
#include <SDL.h>
#include <fstream>
#include <cstdlib>

#include "header.h"
#include "sprite.h"

/**=====================================================**
Sprite Constructor

This function initializes the animation counter and the
rotation angle.
**======================================================**/
Sprite::Sprite(int fwidth, int fheight, int nframes, int nsprites)
{
    //initialize object variables
    animCounter = 0;
    rotation = 0;
    alpha = 255;
    frameWidth = fwidth;
    frameHeight = fheight;
    numFrames = nframes;
    numSprites = nsprites;
    image = {0, 0, fwidth, fheight};
    screen = {0, 350, fwidth, fheight};
}



/**=====================================================**
getY Function

This function returns the y-position of the sprite.
**======================================================**/
int Sprite::getY()
{
    return screen.y;
}



/**=====================================================**
getX Function

This function returns the x-position of the sprite.
**======================================================**/
int Sprite::getX()
{
    return screen.x;
}



/**=====================================================**
setAlpha Function

This function sets the transparency value.
**======================================================**/
void Sprite::setAlpha(int a)
{
    alpha = a;
}



/**=====================================================**
getAlpha Function

This function sets the transparency value.
**======================================================**/
int Sprite::getAlpha()
{
    return alpha;
}



/**=====================================================**
randomSprite Function

This function selects a random sprite from the
spritesheet.
**======================================================**/
void Sprite::randomSprite()
{
    image.y = rand()%numSprites * frameHeight;
}



/**=====================================================**
selectSprite Function

This function selects a specific sprite from the
spritesheet.
**======================================================**/
void Sprite::selectSprite(int spriteNum)
{
    image.y = (spriteNum - 1) * frameHeight;
}



/**=====================================================**
rotateSprite Function

This function sets the rotation of the sprite to be used
when rendering.

Input
    -   The desired rotation angle
**======================================================**/
void Sprite::rotateSprite(int newAngle)
{
    rotation = newAngle;
}



/**=====================================================**
animate Function

This function animates a sprite using the classes
frameWidth and numFrames variables. It uses the
ANIMATION_SPEED to determine the time between animation
frames.
**======================================================**/
void Sprite::animate()
{
    if (animCounter >= ANIMATION_SPEED)
    {
        image.x = ( image.x >= frameWidth * (numFrames - 1) ) ? 0 : image.x + frameWidth;

        animCounter = 0;
    } else {
        animCounter ++;
    }
}



/**=====================================================**
setSprite Function

This function sets the frame size and number of frames.

Input
    -   frame width and height
    -   number of frames
**======================================================**/
void Sprite::setSprite(int fwidth, int fheight, int nframes, int nsprites)
{
    frameWidth = fwidth;
    frameHeight = fheight;
    numFrames = nframes;
    numSprites = nsprites;
    image = {0, 0, fwidth, fheight};
    screen = {0, 350, fwidth, fheight};
}



/**=====================================================**
loadSprite Function

This function loads the spritesheet.

Input
    -   renderer
    -   filename
Output
    -   true if successful, false otherwise
**======================================================**/
bool Sprite::loadSprite(SDL_Renderer *renderer, char* filename)
{
    //Load the file into a temporary surface
    SDL_Surface *temp;
    temp = SDL_LoadBMP(filename);

    //Check if successful
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s", filename, SDL_GetError());
        return false;
    }

    //Set transparent pixel to white
    SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format,255,255,255));

    //Create the texture from the temporary surface
    spriteSheet = SDL_CreateTextureFromSurface(renderer, temp);

    //Check if successful
    if (!spriteSheet)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return false;
    }

    //Free the temporary surface
    SDL_FreeSurface(temp);

    return true;
}



/**=====================================================**
render Function

This function renders the sprite.

Input
    -   renderer
**======================================================**/
void Sprite::render(SDL_Renderer *renderer)
{
    SDL_SetTextureAlphaMod(spriteSheet, alpha);
    SDL_RenderCopyEx(renderer, spriteSheet, &image, &screen, rotation, NULL, SDL_FLIP_NONE);
}
