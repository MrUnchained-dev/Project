#pragma once
#define TRAINALGORITHM

#include "ContainerID.h"
#include "Tiles.h"
#include <SFML/Graphics.hpp>
#include <random>



// RAIL IDENTIFICATION = RailID_100


//Gear 0 is when the train is stopped
//Gear 1 is when the train is moving to the east
//Gear 2 is when the train is moving to the south
//Gear 3 is when the train is moving to the west
//Gear 4 is when the train is moving to the north
const int STOP = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;
const int NORTH = 4;
static int gear = 0;
static float trainSpeed = 2;
static sf::Vector2i pos(15, 10);

int coinflip(std::vector<int> chosenPath, std::vector<int> paths){
    if(paths.size() == 0){
        return 3;
    }
    std::random_device randomNumber;
    std::mt19937 generate(randomNumber());


    std::discrete_distribution<int> distribute(paths.begin(), paths.end());
    int value = chosenPath[distribute(generate)];
    //std::cout << value << std::endl;
    return value;
}

void train_algorithm(sf::Sprite &sprite, Tiles map){
    static int suspensionTrigger = 0;
    static float movementSuspension = 0.f;
    std::vector<int> paths;
    std::vector<int> chosenPath;

    float deltaX = trainSpeed/10;
    float deltaY = deltaX/2;
    if(suspensionTrigger != 0){
        switch(suspensionTrigger){

            case EAST:
                if(movementSuspension <= 25.0f){
                    movementSuspension += deltaY;
                    sprite.setPosition(sprite.getPosition().x+deltaX, sprite.getPosition().y+deltaY);
                }
                else {movementSuspension = 0.f; suspensionTrigger = 0;} break;


            case SOUTH:
                if(movementSuspension <= 25.0f){
                    movementSuspension += deltaY;
                    sprite.setPosition(sprite.getPosition().x-deltaX, sprite.getPosition().y+deltaY);
                }
                else {movementSuspension = 0.f; suspensionTrigger = 0;} break;


            case WEST:
                if(movementSuspension <= 25.0f){
                    movementSuspension += deltaY;
                    sprite.setPosition(sprite.getPosition().x-deltaX, sprite.getPosition().y-deltaY);
                }
                else {movementSuspension = 0.f; suspensionTrigger = 0;} break;


            case NORTH:
                if(movementSuspension <= 25.0f){
                    movementSuspension += deltaY;
                    sprite.setPosition(sprite.getPosition().x+deltaX, sprite.getPosition().y-deltaY);
                }
                else {movementSuspension = 0.f; suspensionTrigger = 0;} break;
        }
    }
    
    else{
        switch(gear){

            case STOP:{
                break;
            }


            case EAST:{
                if(map.TileEntities[pos.y-1][pos.x]->getID() == RailID_100){
                    paths.push_back(1);
                    chosenPath.push_back(0);
                }

                if(map.TileEntities[pos.y][pos.x+1]->getID() == RailID_100){
                    paths.push_back(1);
                    chosenPath.push_back(1);
                }

                if(map.TileEntities[pos.y+1][pos.x]->getID() == RailID_100){
                    paths.push_back(1);
                    chosenPath.push_back(2);
                }
                

                switch(coinflip(chosenPath, paths)){
                    case 0:
                        gear = NORTH;
                        suspensionTrigger = NORTH;
                        pos.y -= 1;
                        break;
                    case 1:
                        gear = EAST;
                        suspensionTrigger = EAST;
                        pos.x += 1;
                        break;
                    case 2:
                        gear = SOUTH;
                        suspensionTrigger = SOUTH;
                        pos.y += 1;
                        break;
                    case 3:
                        gear = STOP;
                }
                break;
            }


            case SOUTH:{
                if(map.TileEntities[pos.y][pos.x-1]->getID() == RailID_100){
                    paths.push_back(1);
                    chosenPath.push_back(0);
                }

                if(map.TileEntities[pos.y+1][pos.x]->getID() == RailID_100){
                    paths.push_back(1);
                    chosenPath.push_back(1);
                }

                if(map.TileEntities[pos.y][pos.x+1]->getID() == RailID_100){
                    paths.push_back(1);
                    chosenPath.push_back(2);
                }

                switch(coinflip(chosenPath, paths)){
                    case 0:
                        gear = WEST;
                        suspensionTrigger = WEST;
                        pos.x-=1;
                        break;
                    case 1:
                        gear = SOUTH;
                        suspensionTrigger = SOUTH;
                        pos.y += 1;
                        break;
                    case 2:
                        gear = EAST;
                        suspensionTrigger = EAST;
                        pos.x += 1;
                        break;
                    case 3:
                        gear = STOP;
                }
                break;
            }


            case WEST:{
                if(map.TileEntities[pos.y+1][pos.x]->getID() == RailID_100){
                    paths.push_back(1);
                    chosenPath.push_back(0);
                }

                if(map.TileEntities[pos.y][pos.x-1]->getID() == RailID_100){
                    paths.push_back(1);
                    chosenPath.push_back(1);
                }

                if(map.TileEntities[pos.y-1][pos.x]->getID() == RailID_100){
                    paths.push_back(1);
                    chosenPath.push_back(2);
                }

                switch(coinflip(chosenPath, paths)){
                    case 0:
                        gear = SOUTH;
                        suspensionTrigger = SOUTH;
                        pos.y += 1;
                        break;
                    case 1:
                        gear = WEST;
                        suspensionTrigger = WEST;
                        pos.x -= 1;
                        break;
                    case 2:
                        gear = NORTH;
                        suspensionTrigger = NORTH;
                        pos.y -= 1;
                        break;
                    case 3:
                        gear = STOP;
                }
                break;
            }


            case NORTH:{
                if(map.TileEntities[pos.y][pos.x-1]->getID() == RailID_100){
                    paths.push_back(1);
                    chosenPath.push_back(0);
                }

                if(map.TileEntities[pos.y-1][pos.x]->getID() == RailID_100){
                    paths.push_back(1);
                    chosenPath.push_back(1);
                }

                if(map.TileEntities[pos.y][pos.x+1]->getID() == RailID_100){
                    paths.push_back(1);
                    chosenPath.push_back(2);
                }

                switch(coinflip(chosenPath, paths)){
                    case 0:
                        gear = WEST;
                        suspensionTrigger = WEST;
                        pos.x -= 1;
                        break;
                    case 1:
                        gear = NORTH;
                        suspensionTrigger = NORTH;
                        pos.y -= 1;
                        break;
                    case 2:
                        gear = EAST;
                        suspensionTrigger = EAST;
                        pos.x += 1;
                        break;
                    case 3:
                        gear = STOP;
                }
                break;
            }
        }
    }
}










