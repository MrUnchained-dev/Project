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

void train_algorithm(sf::Sprite &sprite, Tiles map){
    static sf::Vector2i trainPosition(15, 10);
    static int gear = 2;

    static int suspension_trigger = 0;
    static float movement_suspension = 0.f;

    if(suspension_trigger != 0){
        switch(suspension_trigger){
            case 1:
                if(movement_suspension <= 50.0f){
                    movement_suspension += 0.05f;
                    sprite.setPosition(sprite.getPosition().x+0.05f, sprite.getPosition().y-0.025f);
                }
                else {movement_suspension = 0.f; suspension_trigger = 0;} break;

            case 2:
                if(movement_suspension <= 25.0f){
                    movement_suspension += 0.025f;
                    sprite.setPosition(sprite.getPosition().x-0.05f, sprite.getPosition().y+0.025f);
                }
                else {movement_suspension = 0.f; suspension_trigger = 0;} break;
            case 3:
                if(movement_suspension <= 50.0f){
                    movement_suspension += 0.05f;
                    sprite.setPosition(sprite.getPosition().x-0.05f, sprite.getPosition().y-0.025f);
                }
                else {movement_suspension = 0.f; suspension_trigger = 0;} break;
            case 4:
                if(movement_suspension <= 25.0f){
                    movement_suspension += 0.025f;
                    sprite.setPosition(sprite.getPosition().x+0.05f, sprite.getPosition().y-0.025f);
                }
                else {movement_suspension = 0.f; suspension_trigger = 0;} break;
        }
    }

    else{
        switch(gear){

            //Train moving to the east
            case 1:
                //Straight rail
                if(map.TileEntities[trainPosition.y][trainPosition.x+1]->getID() == RailID_100 && map.TileEntities[trainPosition.y][trainPosition.x+2]->getID() == RailID_100){
                    trainPosition.x += 1;
                    suspension_trigger = 1;
                }
                //Rail to the left
                else if(map.TileEntities[trainPosition.y][trainPosition.x+1]->getID() == RailID_100 && map.TileEntities[trainPosition.y-1][trainPosition.x+1]->getID() == RailID_100){
                    gear = 4;
                    trainPosition.x += 1;
                    suspension_trigger = 1;
                }
                //Rail to the right
                else if(map.TileEntities[trainPosition.y][trainPosition.x+1]->getID() == RailID_100 && map.TileEntities[trainPosition.y+1][trainPosition.x+1]->getID() == RailID_100){
                    gear = 4;
                    trainPosition.x += 1;
                    suspension_trigger = 1;
                }
                //No rails
                else{
                    gear = 0;
                    trainPosition.x += 1;
                    suspension_trigger = 1;
                }
                break;


            //Train moving to the south
            case 2:
                //Straight rail
                if(map.TileEntities[trainPosition.y+1][trainPosition.x]->getID() == RailID_100 && map.TileEntities[trainPosition.y+2][trainPosition.x]->getID() == RailID_100){
                    trainPosition.y += 1;
                    suspension_trigger = 2;
                }
                //Rail to the left
                else if(map.TileEntities[trainPosition.y+1][trainPosition.x]->getID() == RailID_100 && map.TileEntities[trainPosition.y+1][trainPosition.x+1]->getID() == RailID_100){
                    gear = 1;
                    trainPosition.y += 1;
                    suspension_trigger = 2;
                }
                //Rail to the right
                else if(map.TileEntities[trainPosition.y+1][trainPosition.x]->getID() == RailID_100 && map.TileEntities[trainPosition.y+1][trainPosition.x-1]->getID() == RailID_100){
                    gear = 3;
                    trainPosition.y += 1;
                    suspension_trigger = 2;
                }
                //No rails
                else{
                    gear = 0;
                    trainPosition.y += 1;
                    suspension_trigger = 2;
                }
                break;

            //Train moving to the west
            case 3:
                //Straight rail
                if(map.TileEntities[trainPosition.y][trainPosition.x-1]->getID() == RailID_100 && map.TileEntities[trainPosition.y][trainPosition.x-2]->getID() == RailID_100){
                    trainPosition.x -= 1;
                    suspension_trigger = 3;
                }
                //Rail to the left
                else if(map.TileEntities[trainPosition.y][trainPosition.x-1]->getID() == RailID_100 && map.TileEntities[trainPosition.y+1][trainPosition.x-1]->getID() == RailID_100){
                    gear = 2;
                    trainPosition.x -= 1;
                    suspension_trigger = 3;
                }
                //Rail to the right
                else if(map.TileEntities[trainPosition.y][trainPosition.x-1]->getID() == RailID_100 && map.TileEntities[trainPosition.y-1][trainPosition.x-1]->getID() == RailID_100){
                    gear = 4;
                    trainPosition.x -= 1;
                    suspension_trigger = 3;
                }
                else{
                    gear = 0;
                    trainPosition.x -= 1;
                    suspension_trigger = 3;
                }
                break;

            //Train moving to the north
            case 4:
                //Straight rail
                if(map.TileEntities[trainPosition.y-1][trainPosition.x]->getID() == RailID_100 && map.TileEntities[trainPosition.y-2][trainPosition.x]->getID() == RailID_100){
                    trainPosition.y -= 1;
                    suspension_trigger = 4;
                }
                //Rail to the left
                else if(map.TileEntities[trainPosition.y-1][trainPosition.x]->getID() == RailID_100 && map.TileEntities[trainPosition.y-1][trainPosition.x-1]->getID() == RailID_100){
                    gear = 3;
                    trainPosition.y -= 1;
                    suspension_trigger = 4;
                }
                //Rail to the right
                else if(map.TileEntities[trainPosition.y-1][trainPosition.x]->getID() == RailID_100 && map.TileEntities[trainPosition.y-1][trainPosition.x+1]->getID() == RailID_100){
                    gear = 1;
                    trainPosition.y -= 1;
                    suspension_trigger = 4;
                }
                else{
                    gear = 0;
                    trainPosition.y -= 1;
                    suspension_trigger = 4;
                }
                break;
        }
    }
}


void ife(Tiles map){
    sf::Vector2i pos;
    int gear = 0;

    switch(gear){

        //Train moving to the east
        case 1:
            if(map.TileEntities[pos.y][pos.x+1]->getID() != RailID_100){

            }
            
            int arr[] = {0, 0, 0};
            int count = 0;
            int highest = 0;
            int lowest = 2;
            for(int i = pos.y-1;i <= pos.y+1; i++){
                if(map.TileEntities[i][pos.x+1]->getID() == RailID_100){
                    if(count < lowest){
                        lowest = count;
                    }
                    highest = count;
                    count++;
                }
            }

            std::random_device randomNumber;
            std::mt19937 generate(randomNumber());
            std::uniform_int_distribution<int> parameters(lowest, highest);

            
            break;

    }
}