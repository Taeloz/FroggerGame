/*********************************************************************************
FroggerGame Header
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/17/2017
Last Update - 4/26/2017

The following header file contains the class structure for the FroggerGame.
*********************************************************************************/
#ifndef froggerGame_h
#define froggerGame_h

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

#include "scrollbg.h"
#include "vehicle.h"
#include "header.h"
#include "frog.h"
#include "watervehicle.h"

using namespace std;

/**=====================================================**
Game class

This class holds the functions and objects pertaining to
the main FroggerGame.
**======================================================**/
class Game
{
private:
    //Flag to trigger game to quit.
    bool running;

    //score and lives tracking.
    int score, farthestLane, lives;

    //Current number of vehicles
    int numSmall, numMed;

    //SDL pointers
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *textSurface;
    SDL_Texture *scoreTexture;
    Mix_Chunk *hop, *hit, *landed, *complete;
    Mix_Music *music;
    TTF_Font *font;

    //Rects for score display
    SDL_Rect scoreRect;
    SDL_Color textColor;

    //Game objects
    GameObject pad[4];
    GameObject frogIcon;
    GameObject fly;

    //Background objects
    ScrollBG water, topWater, road;
    StaticBG grass;

    //Vehicle objects
    Vehicle small[MAX_SMALL_VEHICLES];
    Vehicle med[MAX_MED_VEHICLES];
    WaterVehicle boat[3];
    WaterVehicle logs[6];
    WaterVehicle lowerLogs[3];

    //Player object
    Frog player;
    GameObject squash;

    //Array of pointers to game objects
    vector<Sprite*> allGameObjects;
    //Sprite *allGameObjects[MAX_SMALL_VEHICLES + MAX_MED_VEHICLES + 15];

public:
    //Constructor
    Game();

    //Function to start game
    int onExecute();

    //Initialization functions
    bool onInit();
    bool initializeSDL();
    bool loadAudio();
    void initializeVehicles();

    //Processing functions
    void onLoop();
    void processVehicles();
    void checkCollisions();
    void updateScore();
    void onEvent(SDL_Event* event);
    void loseLife();
    bool vehicleCollide(int x, int y, int width);

    //Rendering functions
    void onRender(); //Render main game scene
    std::string scoreToString(int score); //Convert a score value to a string
    void renderText(std::string text, int x, int y, int height, int charWidth, SDL_Color color); //Render text to the screen

    //Fade to black Game Over
    void fadeOut();

    //Cleanup function
    void onQuit();

};


#endif // froggerGame_h
