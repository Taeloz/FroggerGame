/*********************************************************************************
FroggerGame - onRender function
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/17/2017
Last Update - 4/26/2017

This file provides the onRender function used by the Game class.
*********************************************************************************/
#include <SDL.h>
#include <string>
#include <sstream>
#include "frogger.h"
#include "scrollbg.h"

/**=====================================================**
onRender Function

This function renders everything to the screen.
**======================================================**/
void Game::onRender()
{
    //Prepare render surface
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    //Render background grass strips
    for (int i = 0; i < 600; i+=50) grass.bgRender(renderer, i);

    //Render the bottom layer of the water
    water.bgRender(renderer, 150);

    //Render the road
    road.bgRender(renderer, 350);

    for (int i = 0; i < 4; i++) allGameObjects[i]->render(renderer); //Render lily pads

    for (int i = 0; i < 4; i++){
        //Render an icon on the pad if the pad is occupied
        if (player.isOccupied(i))
        {
            frogIcon.setPosition(pad[i].getX(), pad[i].getY());
            frogIcon.render(renderer);
        }
    }

    squash.render(renderer); //Render the squash image. Only visible when hit or drowned
    topWater.bgRender(renderer, 150); //Render the top layer of the water

    for (int i = 4; i < 15; i++) allGameObjects[i]->render(renderer); //Render boats and logs and fly

    player.render(renderer); //Render player frog

    for (int i = 15; i < 15 + numSmall + numMed; i++) allGameObjects[i]->render(renderer); //Render all cars

    //Render the score
    updateScore();

    //Render the lives
    for (int i = 0; i < lives; i++)
    {
        frogIcon.setPosition(5 + i * 40, SCREEN_HEIGHT - 55);
        frogIcon.render(renderer);
    }

}



/**=====================================================**
updateScore Function

This function renders the text.
**======================================================**/
void Game::updateScore()
{
    std::string stringScore;

    ///Render the score as texture
    renderText(scoreToString(score), 5, 30, 36, 20, textColor);

    ///Render the text "score"
    stringScore = "SCORE";
    renderText(stringScore, 5, 5, 28, 15, textColor);

    ///Render the text "FroggerGame"
    stringScore = "FroggerGame";
    renderText(stringScore, SCREEN_WIDTH/2-(stringScore.length() * 20)/2, 5, 36, 20, textColor);

    #if IS_DEMO == 1
    ///Render name
    stringScore = "Matthew Brunton";
    renderText(stringScore, SCREEN_WIDTH - 175, SCREEN_HEIGHT-20, 20, 10, (SDL_Color){255, 255, 255});
    #endif
}



/**=====================================================**
scoreToString Function

This function converts an integer score into a string
that can be rendered as text.

Input
    -   score as an integer

Output
    -   score as a string
**======================================================**/
std::string Game::scoreToString(int score)
{
    //create a temporary stringstream to hold the numbers
    std::string stringScore;
    std::stringstream ss;

    ///Convert score to string
    ss << score; //Pass the score to the stringstream
    stringScore = ss.str(); //Store the stringstream into a temporary string
    ss.str(""); //Clear the stringstream

    return stringScore;
}



/**=====================================================**
renderText Function

This function renders given text to the screen.

Input
    -   text to be rendered
    -   x and y position on screen
    -   height of text
    -   width of characters
    -   color of text as SDL_Color
**======================================================**/
void Game::renderText(std::string text, int x, int y, int height, int charWidth, SDL_Color color)
{
    textSurface = TTF_RenderText_Blended(font, text.c_str(), color); //Convert text to temporary surface
    scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface); //Convert surface to texture
    SDL_FreeSurface(textSurface); //Free the temporary surface
    scoreRect = {x, y, (int)(text.length() * charWidth), height}; //Set the display rect based on string length
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect); //Render to renderer
    SDL_DestroyTexture(scoreTexture); //Destroy the texture
}
