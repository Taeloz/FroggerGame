/*********************************************************************************
FroggerGame
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/17/2017
Last Update - 4/04/2017

This file provides the main FroggerGame functions.
*********************************************************************************/
#include <SDL.h>
#include <string>
#include "frogger.h"
#include "scrollbg.h"

/**=====================================================**
Game Constructor

This function sets all the game variables to their
starting values.
**======================================================**/
Game::Game()
{
    score = 0;
    lives = 5;
    farthestLane = 500;
    running = true;
    numSmall = START_SMALL_VEHICLES;
    numMed = START_MED_VEHICLES;
}



/**=====================================================**
onExecute Function

This function runs the game and contains the main game
loop.
**======================================================**/
int Game::onExecute()
{
    if (!onInit()) return -1; //Initialize and continue if successful

    Mix_VolumeMusic(128);
    Mix_FadeInMusic(music, -1, 5000);

    while(running)
    {
        //Poll and check for events.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            onEvent(&event);
        }

        onLoop(); //Game loop

        onRender(); //Render scene

        SDL_RenderPresent(renderer); //Push frame to screen

        SDL_Delay(7);

    }

    if (lives == 0) //Only show game over if all lives were lost
    {
        fadeOut(); //Fade to black on game over

        SDL_Delay(4000); //Pause so user can see game over and score
    }


    onQuit(); //Cleanup

    return 0;
}



/**=====================================================**
fadeOut Function

This function fades to black after game is over.
**======================================================**/
void Game::fadeOut()
{
    Mix_FadeOutMusic(3000);

    //set fade transparency
    int op = 0;

    //Create black screen texture
    SDL_Texture *fadeTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, 800, 600); //Create texture
    SDL_SetTextureBlendMode(fadeTex, SDL_BLENDMODE_BLEND); //Set blend mode
    SDL_SetRenderTarget(renderer, fadeTex); //Change rendering target
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //Color is black
    SDL_RenderClear(renderer); //Clear the target
    SDL_SetRenderTarget(renderer, NULL); //Change renderer back

    //Loop through transparency until fully opaque
    while (op < 255)
    {
        //Set the transparency to the current loop
        SDL_SetTextureAlphaMod(fadeTex, op);

        //Render last viewed game screen
        onRender();

        //Copy the black screen on top
        SDL_RenderCopy(renderer, fadeTex, NULL, NULL);

        renderText("Game Over", SCREEN_WIDTH/2 - 100, op, 60, 28, (SDL_Color){200, 20, 20});
        renderText("SCORE", 5 + 350*op/255, 5 + 375*op/255, 28, 15, (SDL_Color){255, 255, 255});
        renderText(scoreToString(score), 5 + 350*op/255, 30 + 375*op/255, 36, 20,(SDL_Color){255, 255, 255});

        //Push to screen
        SDL_RenderPresent(renderer);

        SDL_Delay(5);

        op++; //Increase transparency counter
    }

}



/**=====================================================**
onQuit Function

This function cleans up and quits SDL and its libraries.
**======================================================**/
void Game::onQuit()
{
    Mix_HaltMusic();
    Mix_FreeMusic(music);

    Mix_FreeChunk(hit);
    Mix_FreeChunk(hop);
    Mix_FreeChunk(landed);
    Mix_FreeChunk(complete);

    Mix_CloseAudio();
    Mix_Quit();

    TTF_Quit();
    SDL_Quit();
}



/**=====================================================**
                        Main
**======================================================**/
int main(int argc, char* argv[])
{
    Game froggerGame;

    return froggerGame.onExecute();
}
