/*********************************************************************************
StaticBG Header
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/17/2017
Last Update - 3/17/2017

The following header file contains the class structure for the static background
object.
*********************************************************************************/
#ifndef staticbg_h
#define staticbg_h

#include <SDL.h>
#include "header.h"

/**=====================================================**
StaticBG class

This class holds the functions and objects pertaining to
the static background object.
**======================================================**/
class StaticBG
{
protected:
    SDL_Texture *background; //SDL pointer

    SDL_Rect image; //Rect for which part of background to display
    SDL_Rect screen; //Rect for where to display on screen

public:
    StaticBG(int x = 0, int y = 0, int width = STATICBG_WIDTH, int height = STATICBG_HEIGHT); //Constructor with default values

    bool loadBG(SDL_Renderer *renderer, char *filename); //Function to load and initialize the background
    void bgRender(SDL_Renderer *renderer, int y); //Function to render the background
};

#endif //scrollbg_h
