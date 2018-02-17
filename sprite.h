/*********************************************************************************
Sprite Header
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/23/2017
Last Update - 4/24/2017

The following header file contains the class structure for the sprite object.
*********************************************************************************/
#ifndef sprite_h
#define sprite_h

#include <SDL.h>

/**=====================================================**
Sprite class

This class holds the functions and objects pertaining to
spritesheet objects.
**======================================================**/
class Sprite
{
protected:
    SDL_Texture *spriteSheet; //SDL pointer

    //Values to establish sprites within a spritesheet
    int frameWidth, frameHeight, numFrames, numSprites;

    //Values for rotation and transparency
    int rotation, alpha;

    //Counter to control animation speed
    int animCounter;

    SDL_Rect image; //Rect for which part of background to display
    SDL_Rect screen; //Rect for where to display on screen

public:
    //Constructor
    Sprite(int fwidth = 50, int fheight = 50, int nframes = 4, int nsprites = 1);

    //Function to load image
    bool loadSprite(SDL_Renderer *renderer, char *filename);

    //Setter functions
    void setSprite(int fwidth, int fheight, int nframes, int nsprites); //Spritesheet values
    void setAlpha(int a); //Transparency
    void rotateSprite(int newAngle); //Rotation
    void selectSprite(int spriteNum); //Which sprite image to use in sheet
    void randomSprite(); //Selects random sprite to use

    //Getter functions
    int getY();
    int getX();
    int getAlpha();

    //Animate the sprite
    void animate();

    //Render the sprite
    void render(SDL_Renderer *renderer);

    //Make Sprite an abstract class
    virtual void moveSprite() = 0;
};

#endif // sprite_h
