/*********************************************************************************
FroggerGame - onLoop functions
GAME202 - Lab 6 - Part 3
Matthew Brunton
Created - 3/23/2017
Last Update - 4/26/2017

This file provides the functions used by the Game class during a game loop.
*********************************************************************************/
#include <SDL.h>
#include <vector>

#include "frogger.h"
#include "header.h"

using namespace std;

/**=====================================================**
onLoop Function

This function processes everything that must occur
during a game loop.
**======================================================**/
void Game::onLoop()
{
    //Reset the flags tracking if user is on boat or log
    player.onBoat = false;
    player.onUpperLog = false;
    player.onLowerLog = false;

    //Scroll the water
    water.bgScroll(1);
    topWater.bgScroll(2);

    //Move and animate the game objects
    for (int i = 0; i < 15 + numSmall + numMed; i++)
    {
        allGameObjects[i]->moveSprite();
        allGameObjects[i]->animate();
    }

    //Process the vehicle objects
    processVehicles();

    //Animate the squash, or move and animate the player
    if (squash.getAlpha() > 0)
    {
        squash.setAlpha(squash.getAlpha() - 2); //gradually make the squash transparent
        if (squash.getAlpha() == 0) {
            player.reset(); //When squash is gone, reset player
            squash.setPosition(0,0);
        }
    } else {
        player.animate();
        if (player.isInMotion())
        {
            player.moveFrog();
        }
        checkCollisions();
    }

    //If all pads occupied
    if (player.allPadsOccupied())
    {
        score += 1000; //increase score
        player.resetPads();
        if (numSmall < MAX_SMALL_VEHICLES){
            allGameObjects.insert(allGameObjects.begin() + 14 + numSmall, &small[numSmall]); //add new small to vector
            numSmall++; //increase small vehicles
        }
        if (numSmall % 2 == 1 && numMed < MAX_MED_VEHICLES){
            allGameObjects.insert(allGameObjects.begin() + 14 + numSmall + numMed, &med[numMed]); //add new med to vector
            numMed++; //increase med vehicles
        }
        Mix_PlayChannel(-1, complete, 0); //play sound
    }
}



/**=====================================================**
processVehicles Function

This function moves and animates the vehicle objects.

It also checks for vehicles that were reset and ensures
that their new starting position is not colliding with
any other vehicle objects.
**======================================================**/
void Game::processVehicles()
{
    ///Check all the small vehicles
    for (int i = 0; i < numSmall; i++)
    {
        //If the vehicle moved offscreen
        if (small[i].active == false) {
            int clearance = 75; //Start the clearance at 50. This will increase if there's no spot to place the vehicle.

            //Loop through all the small vehicles until an open offscreen location is found.
            do {

                //Set the random position offscreen to the left or right depending on lane
                if (small[i].getY() == 400) {
                    small[i].randomPosition(SCREEN_WIDTH, SCREEN_WIDTH + clearance, small[i].getY(), small[i].getY(), 1, 1);
                } else {
                    small[i].randomPosition(-1 * clearance, -50, small[i].getY(), small[i].getY(), 1, 1);
                }

                clearance += 10; //Increase the clearance in case there is no open spot to place the vehicle

            } while (vehicleCollide(small[i].getX(), small[i].getY(), 50)); //If there is a collision, try for another spot.

            small[i].active = true; //Set the vehicle active.
        }
    }

    ///Check all the medium vehicles
    for (int i = 0; i < numMed; i++)
    {
        //If the vehicle moved offscreen
        if (med[i].active == false) {
            int clearance = 90; //Start the clearance at 50. This will increase if there's no spot to place the vehicle.

            //Loop through all the small vehicles until an open offscreen location is found.
            do {

                //Set the random position offscreen to the left or right depending on lane
                if (med[i].getY() == 400) {
                    med[i].randomPosition(SCREEN_WIDTH, SCREEN_WIDTH + clearance, med[i].getY(), med[i].getY(), 1, 1);
                } else {
                    med[i].randomPosition(-1 * clearance, -75, med[i].getY(), med[i].getY(), 1, 1);
                }

                clearance += 10; //Increase the clearance in case there is no open spot to place the vehicle

            } while (vehicleCollide(med[i].getX(), med[i].getY(), 75)); //If there is a collision, try for another spot.

            med[i].active = true; //Set the vehicle active.
        }
    }
}



/**=====================================================**
checkCollisions Function

This function checks for collisions between the player
object and other game objects.

If the player is on a log or boat, the movement is
modified accordingly.

If the player is in the water, or is hit by a vehicle,
the player loses a life.
**======================================================**/
void Game::checkCollisions()
{

    //Check if the player is on a boat
    for (int i = 0; i < 3; i++)
    {
        if (player.getX() + 20 >= boat[i].getX() && player.getX() + 30 <= boat[i].getX() + 75 && player.getY() == boat[i].getY())
        {
            player.translate(-1 * BOAT_SPEED, 0);
            player.setDest(player.getDestX() - 1 * BOAT_SPEED, 0);

            //Prevent player from riding offscreen
            if (player.getX() < 0)
            {
                player.setPosition(0, player.getY());
                player.setDest(player.getDestX() + 1 * BOAT_SPEED, 0);
            }
            player.onBoat = true;
        }
    }

    //Check if the player is on a log on upper row
    for (int i = 0; i < 3; i++)
    {
        if (player.getX() + 20 >= logs[i].getX() && player.getX() + 30 <= logs[i].getX() + 125 && player.getY() == logs[i].getY())
        {
            player.translate(UPPER_LOG_SPEED, 0); //move the player the speed of the log
            player.setDest(player.getDestX() + UPPER_LOG_SPEED, 0); //change the distance to travel to include log speed

            //Prevent player from riding offscreen
            if (player.getX() + 50 > SCREEN_WIDTH)
            {
                player.setPosition(SCREEN_WIDTH - 50, player.getY());
                player.setDest(player.getDestX() - 1 * UPPER_LOG_SPEED, 0);
            }
            player.onUpperLog = true;
        }
    }

    //Check if the player is on a log on lower row
    for (int i = 3; i < 7; i++)
    {
        if (player.getX() + 20 >= logs[i].getX() && player.getX() + 30 <= logs[i].getX() + 125 && player.getY() == logs[i].getY())
        {
            player.translate(LOWER_LOG_SPEED, 0);
            player.setDest(player.getDestX() + LOWER_LOG_SPEED, 0);

            //Prevent player from riding offscreen
            if (player.getX() + 50 > SCREEN_WIDTH)
            {
                player.setPosition(SCREEN_WIDTH - 50, player.getY());
                player.setDest(player.getDestX() - 1 * LOWER_LOG_SPEED, 0);
            }
            player.onLowerLog = true;
        }
    }

    ///Check to see if squashed
    if (player.getY() >= 350) //If the player is on the road
    {
        for (int i = 0; i < numSmall; i++)
        {
            //Lose life if collision with small vehicle
            if (player.getY() == small[i].getY() && player.getX() + 40 > small[i].getX() && player.getX() + 10 < small[i].getX() + 50) loseLife();
        }
        for (int i = 0; i < numMed; i++)
        {
            //Lose life if collision with medium vehicle
            if (player.getY() == med[i].getY() && player.getX() + 40 > med[i].getX() && player.getX() + 10 < med[i].getX() + 75) loseLife();
        }

    } else if (player.getY() == 150 && !player.isInMotion()) {  //Player is on upper log strip
        if (!player.onUpperLog) loseLife();                     //and Player is not on a log

    } else if (player.getY() == 200 && !player.isInMotion()) {  //Player is on boat strip
        if (!player.onBoat) loseLife();                         //and Player is not on a boat

    } else if (player.getY() == 250 && !player.isInMotion()){   //Player is on lower log strip
        if (!player.onLowerLog) loseLife();                     //and Player is not on a log
    }


    //Player collected fly
    if (player.getY() == fly.getY() && player.getX() < fly.getX() + 50 && player.getX() + 50 > fly.getX() && squash.getX() != player.getX() && squash.getY() != player.getY())
    {
        score += 100;
        Mix_PlayChannel(-1, landed, 0); //play sound
        fly.setAlpha(0);
        fly.setPosition(0, 0);
    }


    if (player.getY() == 100) // player made it to pad
    {
        Mix_PlayChannel(-1, landed, 0); //play sound
        score += 200; //increase score
        farthestLane = 500; //reset farthest lane
        player.setOccupied(player.getX()/200);//set that space occupied
        player.reset(); //reset player
        fly.setAlpha(255);
        fly.randomPosition(0, SCREEN_WIDTH, 150, 350, 50, 50);
    }
}



/**=====================================================**
loseLife Function

This function is run every time a player loses a life.
It reduces the life counter, replaces the player sprite
with the squashed sprite and plays a sound.
**======================================================**/
void Game::loseLife()
{
    lives -= 1; //Player loses life
    player.setAlpha(0); //Make player invisible
    squash.setPosition(player.getX(), player.getY()); //Put squash animation at player location
    squash.setAlpha(220); //Make squash animation visible
    Mix_PlayChannel(-1, hit, 0); //play squash sound
    if (lives == 0) running = false;
}
