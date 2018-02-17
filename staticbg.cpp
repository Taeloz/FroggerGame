/*********************************************************************************
FroggerGame - StaticBG functions
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/17/2017
Last Update - 3/23/2017

This file provides the functions used by the ScrollBG class.
*********************************************************************************/
#include <SDL.h>
#include <fstream>

#include "header.h"
#include "staticbg.h"

/**=====================================================**
StaticBG Constructor

This function sets the inital SDL Rects.

Input
    -   x and y coordinates to output on screen
    -   width and height of image
**======================================================**/
StaticBG::StaticBG(int x, int y, int width, int height)
{
    //Set the image rect
    image = {0, 0, width, height};

    //Set the screen rect
    screen = {x, y, width, height};
}



/**=====================================================**
loadBG Function

This function loads the background image.

Input
    -   renderer
    -   filename
Output
    -   true if successful, false otherwise
**======================================================**/
bool StaticBG::loadBG(SDL_Renderer *renderer, char *filename)
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

    //Create the texture from the temporary surface
    background = SDL_CreateTextureFromSurface(renderer, temp);

    //Check if successful
    if (!background)
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
bgRender Function

This function renders the background.

Input
    -   renderer
    -   y-position to render the background strip
**======================================================**/
void StaticBG::bgRender(SDL_Renderer *renderer, int y)
{
    screen.y = y;
    SDL_RenderCopy(renderer, background, &image, &screen);
}
