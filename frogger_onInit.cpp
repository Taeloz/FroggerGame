/*********************************************************************************
FroggerGame - onInit functions
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/17/2017
Last Update - 4/26/2017

This file provides the onInit functions used by the Game class.
*********************************************************************************/
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>

#include "header.h"
#include "frogger.h"
#include "scrollbg.h"
#include "vehicle.h"

using namespace std;

/**=====================================================**
onInit Function

This function initializes everything required for the
game to run.

Output
    - true if everything is successful, false otherwise.
**======================================================**/
bool Game::onInit()
{
    srand(time(0)); //Seed the random number generator.

    //Initialize SDL libraries and create a window and renderer
    if(!initializeSDL()) return false;

    //Load the audio files
    if(!loadAudio()) return false;

    //Load font
    font = TTF_OpenFont("fonts/MontserratAlternates-Regular.ttf", 48);
    textColor = {0, 0, 0}; //Set text color for score

    //Load the destination lily pads
    for (int i = 0; i < 4; i++){
        pad[i] = GameObject(50, 50, 4, 1);
        pad[i].loadSprite(renderer, "images/pad.bmp");
        pad[i].setPosition(100 + i * 200, 100);
    }

    //Load the grass strips
    grass.loadBG(renderer, "images/grass.bmp");

    //Load the road
    road.loadBG(renderer, "images/road.bmp");

    //Load the water
    water = ScrollBG({0, 0, 255, 160});
    water.loadBG(renderer, "images/bottomwater.bmp");

    topWater = ScrollBG({0, 0, 255, 100});
    topWater.loadBG(renderer, "images/topwater.bmp");

    //Load the small cars
    for (int i = 0; i < MAX_SMALL_VEHICLES; i++){
        small[i] = Vehicle(50, 50, 4, 4);
        small[i].loadSprite(renderer, "images/vehicleSmall.bmp");
    }

    //Load the trucks
    for (int i = 0; i < MAX_MED_VEHICLES; i++){
        med[i] = Vehicle(75, 50, 4, 4);
        med[i].loadSprite(renderer, "images/vehicleMed.bmp");
    }

    //Initialize the vehicles on the road
    initializeVehicles();

    //Load the boats
    for (int i = 0; i < 3; i++){
        boat[i] = WaterVehicle(true, 75, 50, 4, 2);
        boat[i].loadSprite(renderer, "images/boat.bmp");
        boat[i].setPosition(100 + i * 325, 200);
    }

    //Load the logs
    for (int i = 0; i < 7; i++){
        logs[i].loadSprite(renderer, "images/log.bmp");
        logs[i].setSprite(125, 50, 1, 1);
    }

    //Set the log positions
    for (int i = 0; i < 3; i++) logs[i].setPosition(100 + i * 325, 150);
    for (int i = 3; i < 7; i++) logs[i].setPosition(i * 250 - 600, 250);

    //Load the player
    player = Frog(50, 50, 4, 2);
    player.loadSprite(renderer, "images/frogSheet.bmp");

    //Load the frog icon
    frogIcon = GameObject(50, 50, 1, 1);
    frogIcon.loadSprite(renderer, "images/frogIcon.bmp");

    //Load the squash image
    squash = GameObject(50, 50, 1, 1);
    squash.loadSprite(renderer, "images/squash.bmp");
    squash.setAlpha(0);

    //Load the fly
    fly = GameObject(50, 50, 4, 1);
    fly.loadSprite(renderer, "images/flysmall.bmp");
    fly.randomPosition(0, SCREEN_WIDTH, 150, 340, 50, 50);

    //Assign the game objects to the vector of all game objects
    for (int i = 0; i < 4; i++) allGameObjects.push_back(&pad[i]);
    for (int i = 0; i < 7; i++) allGameObjects.push_back(&logs[i]);
    for (int i = 0; i < 3; i++) allGameObjects.push_back(&boat[i]);
    allGameObjects.push_back(&fly);
    for (int i = 0; i < numSmall; i++) allGameObjects.push_back(&small[i]);
    for (int i = 0; i < numMed; i++) allGameObjects.push_back(&med[i]);

    return true;
}



/**=====================================================**
initializeSDL Function

This function initializes SDL, creates the window and
renderer, and initializes the audio and font libraries.

Output
    - True if everything was successful, false otherwise
**======================================================**/
bool Game::initializeSDL()
{
    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1"); ///Needed to use the debugger without RaiseException problems

    //Initialize SDL.
    if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) < 0) return false;

    //Create window and renderer
    if (!(window = SDL_CreateWindow("FroggerGame", 400, 50, SCREEN_WIDTH, SCREEN_HEIGHT, 0))) return false;
    if (!(renderer = SDL_CreateRenderer(window, -1, 0))) return false;

    //Initialize the TTF library.
    if (TTF_Init() < 0) return false;

    //Initialize SDL_mixer
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }

    return true;
}



/**=====================================================**
loadAudio Function

This function loads the sound effects and music.

Output
    - True if everything was successful, false otherwise
**======================================================**/
bool Game::loadAudio()
{
    //Load the sound effects
    hop = Mix_LoadWAV("sounds/hop.wav");
    if(!hop)
    {
        printf( "Could not load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }
    hit = Mix_LoadWAV("sounds/squash.wav");
    if(!hit)
    {
        printf( "Could not load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }
    landed = Mix_LoadWAV("sounds/landed.wav");
    if(!landed)
    {
        printf( "Could not load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }
    complete = Mix_LoadWAV("sounds/complete.wav");
    if(!complete)
    {
        printf( "Could not load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }

    //Load music
    if (!(music = Mix_LoadMUS("sounds/mpprel-e.mid")))
    {
        printf( "Could not load music! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }

    return true;
}



/**=====================================================**
initializeVehicles Function

This function initializes all the vehicles to random
positions in the lane they were created in.

It makes sure that the vehicles aren't placed on top of
another vehicle.
**======================================================**/
void Game::initializeVehicles()
{
    for (int i = 0; i < numSmall; i++)
    {
        do {
            small[i].randomPosition(-100, SCREEN_WIDTH + 100, small[i].getY(), small[i].getY(), 1, 1);
            small[i].active = true;
        } while (vehicleCollide(small[i].getX(), small[i].getY(), 50));
    }
    for (int i = 0; i < numMed; i++)
    {
        do {
            med[i].randomPosition(-100, SCREEN_WIDTH + 100, med[i].getY(), med[i].getY(), 1, 1);
            med[i].active = true;
        } while (vehicleCollide(med[i].getX(), med[i].getY(), 75));
    }

}



/**=====================================================**
vehicleCollide Function

This function checks a given coordinate and width to
see if it collides with any vehicles.

It also uses SMALL_CLEARANCE to keep a space between
vehicles.

Input
    - x,y to check
    - width to check

Output
    - true if given values collide with a vehicle
    - false otherwise
**======================================================**/
bool Game::vehicleCollide(int x, int y, int width)
{
    for (int i = 0; i < numSmall; i++)
    {
        if (!(y == small[i].getY() && x == small[i].getX()))
        {
            if (y == small[i].getY())
            {
                if (x + width >= small[i].getX() - SMALL_CLEARANCE && x <= small[i].getX() + 50 + SMALL_CLEARANCE)
                {
                    return true;
                }
            }
        }
    }
    for (int i = 0; i < numMed; i++)
    {
        if (!(y == med[i].getY() && x == med[i].getX()))
        {
            if (y == med[i].getY())
            {
                if (x + width >= med[i].getX() - MED_CLEARANCE && x <= med[i].getX() + 75 + MED_CLEARANCE)
                {
                    return true;
                }
            }
        }
    }

    return false;
}
