/*********************************************************************************
FroggerGame - ScrollBG functions
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 2/15/2017
Last Update - 3/24/2017

This file provides the functions used by the ScrollBG class.
*********************************************************************************/
#include <SDL.h>
#include <fstream>

#include "header.h"
#include "scrollbg.h"

/**=====================================================**
ScrollBG Constructor

This function sets the inital SDL Rects.

Input
    -   x and y coordinates to output on screen
    -   width and height of image
**======================================================**/
ScrollBG::ScrollBG(SDL_Color color, int x, int y, int width, int height):
        StaticBG(x, y, width, height)
{
    //Set the image rect to the bottom part of the image and the size of the screen
    image = {width - SCREEN_WIDTH, 0, SCREEN_WIDTH, height};

    //Screen size starts at the full size. Will shrink when infinite scrolling is invoked
    screen = {x, y, SCREEN_WIDTH, height};

    //Set offset image rect to start at the bottom of the image with no thickness
    //Thickness will grow when infinite scrolling is invoked
    offset = {width, 0, 0, height};

    //Set the size of the screen for the next image iteration. Starts with no thickness at top of screen
    //Will grow when infinite scrolling is invoked
    offsetScreen = {x, y, 0, height};

    bgColor = color;
}



/**=====================================================**
bgScroll Function

This function scrolls the background.

Input
    -   x-scroll value
    -   y-scroll value
Output
    -   true if 1 revolution is completed, otherwise false.
**======================================================**/
bool ScrollBG::bgScroll(int dx)
{
    //If speed is positive and the x-location in image is 0
    //Means the location being pulled from the image has reached
    //the top of the image so we need to start rendering the second image
    if (dx > 0 && image.x <= 0)
    {

        //Move the starting position in the offset image up. The image starts at the bottom
        //and grows upward.
        offset.x -= dx;

        //Grow the offset screen and the location on the screen it is being rendered to
        //The offset image starts as a sliver at the left of the screen and grows
        //to the right
        offset.w += dx;
        offsetScreen.w += dx;

        //Shrink the first image
        image.w -= dx; //rect being pulled from image shrinks
        screen.x += dx; //part of the screen it starts from moves down
        screen.w -= dx; //part of the screen being sent to shrinks

        //If the offset image becomes the full size of the screen, reset so the process
        //can begin again.
        if (offset.w >= SCREEN_WIDTH)
        {
            screen.x = 0;
            screen.w = SCREEN_WIDTH;

            image.x = SCROLLBG_WIDTH - SCREEN_WIDTH;
            image.w = SCREEN_WIDTH;

            offsetScreen.w = 0;
            offset.w = 0;
            offset.x = SCROLLBG_WIDTH;

            return true; //Increment the distance since the screen has scrolled once
        }

    } else {
        image.x += dx; //Regular scroll of the image
    }

    return false;
}



/**=====================================================**
bgRender Function

This function renders the background.

Input
    -   renderer
**======================================================**/
void ScrollBG::bgRender(SDL_Renderer *renderer, int y)
{
    screen.y = y;
    offsetScreen.y = y;

    //Set the blendmode
    SDL_SetTextureBlendMode(background, SDL_BLENDMODE_BLEND);

    //Set the opacity
    SDL_SetTextureAlphaMod(background, bgColor.a);

    //Set the color
    SDL_SetTextureColorMod(background, bgColor.r, bgColor.g, bgColor.b);

    //Render both background images (for infinite scrolling) to the renderer
    SDL_RenderCopy(renderer, background, &image, &screen);
    SDL_RenderCopy(renderer, background, &offset, &offsetScreen);
}
