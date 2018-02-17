/*********************************************************************************
ScrollBG Header
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 2/15/2017
Last Update - 3/23/2017

The following header file contains the class structure for the scrolling
background object, which inherits from the static background object class.
*********************************************************************************/
#ifndef scrollbg_h
#define scrollbg_h

#include <SDL.h>
#include "staticbg.h"
#include "header.h"

/**=====================================================**
ScrollBG class

This class holds the functions and objects pertaining to
the scrolling background object. Inherits from StaticBG.
**======================================================**/
class ScrollBG: public StaticBG
{
protected:
    SDL_Rect offset; //Rect for which part of second background to display
    SDL_Rect offsetScreen; //Rect for where to display it on screen

public:
    ScrollBG(SDL_Color color = {255, 255, 255, 255}, int x = 0, int y = 0, int width = SCROLLBG_WIDTH, int height = SCROLLBG_HEIGHT);//Constructor with default values
    SDL_Color bgColor; //Color and opacity of background

    bool bgScroll(int dx); //Function to scroll the background
    void bgRender(SDL_Renderer *renderer, int y); //Function to render the background
};

#endif //scrollbg_h
