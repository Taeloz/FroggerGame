/*********************************************************************************
FroggerGame - onEvent function
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 2/15/2017
Last Update - 3/31/2017

This file provides the onEvent function used by the Game class.
*********************************************************************************/
#include <SDL.h>
#include "frogger.h"

/**=====================================================**
onEvent Function

This function checks for events and processes them.
**======================================================**/
void Game::onEvent(SDL_Event* event)
{
    //If the window is closed, quit the program
    if(event->type == SDL_QUIT) {
        running = false;
    }

    //If the Escape key is pressed, quit the program
    if (event->type == SDL_KEYDOWN){
        switch (event->key.keysym.sym){
        case SDLK_ESCAPE:
            running = false;
            break;

        //Move player left
        case SDLK_LEFT:
            if (!player.isInMotion() && player.getX() != 0 && squash.getAlpha() == 0){
                player.rotateSprite(270);
                if (player.getX() - 50 <= 0) {
                    player.setDest(0, player.getY());
                } else {
                    player.setDest(player.getX() - 50, player.getY());
                }
                player.setMotion(-2, 0);
                Mix_PlayChannel(-1, hop, 0);
            }
            break;

        //Move player right
        case SDLK_RIGHT:
            if (!player.isInMotion() && player.getX() != SCREEN_WIDTH - 50 && squash.getAlpha() == 0){
                player.rotateSprite(90);
                if (player.getX() + 50 >= SCREEN_WIDTH) {
                    player.setDest(SCREEN_WIDTH - 50, player.getY());
                } else {
                    player.setDest(player.getX() + 50, player.getY());
                }
                player.setMotion(2, 0);
                Mix_PlayChannel(-1, hop, 0);
            }
            break;

        //Move player down
        case SDLK_DOWN:
            if (!player.isInMotion() && player.getY() != 500 && squash.getAlpha() == 0){
                player.rotateSprite(180);
                player.setDest(player.getX(), player.getY()+50);
                player.setMotion(0, 2);
                Mix_PlayChannel(-1, hop, 0);
            }
            break;

        //Move player up
        case SDLK_UP:
            if (!player.isInMotion() && player.getY() != 100 && squash.getAlpha() == 0){
                player.rotateSprite(0);
                player.setDest(player.getX(), player.getY()-50);
                if (farthestLane > player.getY() - 50){
                    score += 10;
                    farthestLane -= 50;
                }
                player.setMotion(0, -2);
                Mix_PlayChannel(-1, hop, 0);
            }
            break;


        case SDLK_RETURN:
            //fly.randomPosition(0, SCREEN_WIDTH, 150, 340, 50, 50);
            break;
        }
    }
}
