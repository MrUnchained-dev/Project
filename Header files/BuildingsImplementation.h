#define BUILDINGSIMPLEMENTATION
#pragma once
#include "Tiles.h"
#include "Texture.h"
#include <SFML/Graphics.hpp>


void DefaultHouse::tileOccupation(
    Tiles &map, sf::RenderWindow &window, int x, int y, int &hoveringX, int &hoveringY,
    std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY){


    if(arrayTilesX == nullptr){                 // Checks whether if the vector is empty (meaning if it's in hold-mode or not)
        int row = botTileY - topTileY + 1;
        arrayTilesX = new std::vector<int>[row];
        arrayTilesY = new std::vector<int>[row];
        
        // Puts the entitiy's tiles in a 2D-pointer vector
        int count = 0;
        for(int i = topTileY; i <= botTileY; i++){
             for(int j = topTileX; j <= botTileX; j++){
                arrayTilesX[count].push_back(j);
                arrayTilesY[count].push_back(i);
            }
            count += 1;
        }
    }

    // Calculates the delta of the current mouse-position vs previous mouse-position
    int deltaY = 0;
    int deltaX = 0;
    if(hoveringY != y){
        deltaY = (-1)*(hoveringY - y);}
    if(hoveringX != x){
        deltaX = (-1)*(hoveringX - x);}



    // Removes pre-updated tile colors
    for(int i = arrayTilesY[0][0]; i <= arrayTilesY[3][3]; i++){
        for(int j = arrayTilesX[0][0]; j <= arrayTilesX[3][3]; j++){
            map.setColor(j, i, sf::Color(255, 255, 255));
        }}


    // Updates the position of the tiles in respect to the delta 
    // and also colors them based on the tile availability (blue for available, red for unavailable)
    for(int i = 0; i <= 3; i++){
        for(int j = 0; j <= 3; j++){
            arrayTilesX[i][j] += deltaX;
            arrayTilesY[i][j] += deltaY;
            if(!map.TileEntities[arrayTilesY[i][j]][arrayTilesX[i][j]]->getID()){
                map.setColor(arrayTilesX[i][j], arrayTilesY[i][j], sf::Color(180, 255, 255));
            }
            else{
                map.setColor(arrayTilesX[i][j], arrayTilesY[i][j], sf::Color(255, 45, 80));
            }}}

    // The previous mouse position becomes the current one and thus this function goes out of scope 
    hoveringX = x; hoveringY = y;   
}


void DefaultHouse::placeEntity(Tiles &map, sf::RenderWindow &window, std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY){
    bool tileCollision = false;
    for(int i = 0; i <= 3; i++){
        for(int j = 0; j <= 3; j++){

            if(map.TileEntities[arrayTilesY[i][j]][arrayTilesX[i][j]]->getID()){
                tileCollision = true; 
                break;
            }

        }
        if(tileCollision){
            break;
        }
    }
     
    if(!tileCollision){
        int correspondingIndex;
        for(int i = 0; i < arrayDefaultHouse.size(); i++){
            if(objectID == arrayDefaultHouse[i]->objectID){
                correspondingIndex = i;
                break;}}
        

        // Replaces the new tiles' entities with itself at the new coords while also decoloring
        for(int i = arrayTilesY[0][0]; i <= arrayTilesY[3][3]; i++){
            for(int j = arrayTilesX[0][0]; j <= arrayTilesX[3][3]; j++){

                delete map.TileEntities[i][j]; 
                map.TileEntities[i][j] = arrayDefaultHouse[correspondingIndex];
                map.setColor(j, i, sf::Color::White);

            }
        }
        
        // Converts the old tiles back into default tiles
        sf::Sprite empty;
        for(int i = topTileY; i <= botTileY; i++){
            for(int j = topTileX; j <= botTileX; j++){
                map.TileEntities[i][j] = nullptr;
                map.TileEntities[i][j] = addDefaultTile();
                map.sprites[i][j] = empty;
            }
        }

        arrayDefaultHouse[correspondingIndex]->topTileX = arrayTilesX[0][0];
        arrayDefaultHouse[correspondingIndex]->topTileY = arrayTilesY[0][0];
        arrayDefaultHouse[correspondingIndex]->botTileX = arrayTilesX[3][3];
        arrayDefaultHouse[correspondingIndex]->botTileY = arrayTilesY[3][3];

        
        sf::Vector2f centerpoint = map.getCenterPoint(arrayDefaultHouse[correspondingIndex]->topTileY, 
                                                      arrayDefaultHouse[correspondingIndex]->topTileX, 
                                                      arrayDefaultHouse[correspondingIndex]->botTileY, 
                                                      arrayDefaultHouse[correspondingIndex]->botTileX);
        
        
        for(int i = topTileY; i <= botTileY; i++){
            for(int j = topTileX; j <= botTileX; j++){
                map.sprites[i][j] = map.texture.getTexture(DefaultHouseID);
                map.sprites[i][j].setPosition(centerpoint.x, centerpoint.y);
            }
        }
    }
    else{

        for(int i = arrayTilesY[0][0]; i <= arrayTilesY[3][3]; i++){
            for(int j = arrayTilesX[0][0]; j <= arrayTilesX[3][3]; j++){
                map.setColor(j, i, sf::Color::White);
            }
        }
        map.sprites[topTileY][topTileX].setColor(sf::Color::White);
    }

    // Since the block has now been placed, the vector holding the tiles of the entity has to be completely removed
    delete[] arrayTilesX;
    delete[] arrayTilesY;
    arrayTilesX = nullptr;
    arrayTilesY = nullptr;
}


void DefaultHouse::colorTileOccupation(Tiles &map, sf::Color color){
    for(int i = topTileY; i <= botTileY; i++){
        for(int j = topTileX; j <= botTileX; j++){
            //map.setColor(j, i, color);
            map.sprites[i][j].setColor(color);
        }
    }
}


void placeDefaultHouse(Tiles&map, sf::RenderWindow &window){
    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    int x = 0; int y = 0;
    map.findTile(worldPos, x, y);

    int topX = x;
    int topY = y;
    int botX = x+3;
    int botY = y+3;

    bool tileCollision = false;

    for(int i = topY; i <= botY; i++){
        for(int j = topX; j <= botX; j++){

            if(map.TileEntities[i][j]->getID()){
                tileCollision = true;
                break;}

        }
    }

    if(!tileCollision){
        map.BuildingCatalogue.addDefaultHouse();

        arrayDefaultHouse[arrayDefaultHouse.size()-1]->topTileX = x;
        arrayDefaultHouse[arrayDefaultHouse.size()-1]->topTileY = y;
        arrayDefaultHouse[arrayDefaultHouse.size()-1]->botTileX = x+3;
        arrayDefaultHouse[arrayDefaultHouse.size()-1]->botTileY = y+3;


        sf::Vector2f centerpoint = map.getCenterPoint(arrayDefaultHouse[arrayDefaultHouse.size()-1]->topTileY, 
                                                      arrayDefaultHouse[arrayDefaultHouse.size()-1]->topTileX, 
                                                      arrayDefaultHouse[arrayDefaultHouse.size()-1]->botTileY, 
                                                      arrayDefaultHouse[arrayDefaultHouse.size()-1]->botTileX);

        //map.sprites[y][x] = map.texture.getTexture(DefaultHouseID);
        //map.sprites[y][x].setPosition(centerpoint.x, centerpoint.y);


        int iCount = 0;
        for(int i = topY; i <= botY; i++){
            int jCount = 0;
            for(int j = topX; j <= botX; j++){
                delete map.TileEntities[i][j];
                map.TileEntities[i][j] = arrayDefaultHouse[arrayDefaultHouse.size()-1];

                map.sprites[i][j] = map.texture.getTexture(DefaultHouseID);
                map.sprites[i][j].setPosition(centerpoint.x, centerpoint.y);

                jCount += 1;
                iCount += 1;
                
            }
        }
        std::cout << "Successful plantation!" << std::endl;
    }
    else{
        std::cout << "No free space" << std::endl;
    }
}


void Rail::tileOccupation(Tiles &map, sf::RenderWindow &window, int x, int y, int &hoveringX, int &hoveringY, std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY){
    if(!map.TileEntities[y][x]->getID()){
        map.setColor(x, y, sf::Color(180, 255, 255));
    }
    else{
        map.setColor(x, y, sf::Color(255, 45, 80));
    }
    map.setColor(hoveringX, hoveringY, sf::Color(255,255,255));
    hoveringX = x; hoveringY = y;
}

// Used for relocation
void Rail::placeEntity(Tiles &map, sf::RenderWindow &window, std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY){

    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    int i = 0; int j = 0;
    map.findTile(worldPos, j, i);

    int correspondingIndex = 0;
    for(int k = 0; k < arrayRail.size(); k++){
        if(arrayRail[k]->objectID == objectID){
            correspondingIndex = k;
            break;
        }
    }

    if(!map.TileEntities[i][j]->getID()){
        // Replaces the new tiles' entities with itself at the new coords while also decoloring
        delete map.TileEntities[i][j]; 
        map.TileEntities[i][j] = nullptr;
        map.TileEntities[i][j] = arrayRail[correspondingIndex];
        map.setColor(j, i, sf::Color::White);

        

        // Frees the previous tile's pointer from the rail object and instead makes it point to a defaultTile object
        map.TileEntities[topTileY][topTileX] = nullptr;
        map.TileEntities[topTileY][topTileX] = addDefaultTile();

        // Replace sprite and set empty sprite at previous location
        map.sprites[i][j] = map.sprites[topTileY][topTileX];
        map.sprites[i][j].setColor(sf::Color::White);
        sf::Sprite empty;
        map.sprites[topTileY][topTileX] = empty;

        // Updates the the rail object's coordinates 
        arrayRail[correspondingIndex]->topTileX = j;
        arrayRail[correspondingIndex]->topTileY = i;
        arrayRail[correspondingIndex]->botTileX = j;
        arrayRail[correspondingIndex]->botTileY = i;
        
        // Set the sprite coordinates
        sf::Vector2f centerpoint = map.getCenterPoint(topTileY, topTileX, botTileY, botTileX);
        map.sprites[i][j].setPosition(centerpoint.x, centerpoint.y);

    }
    else{
        map.setColor(j, i, sf::Color::White);
        map.sprites[topTileY][topTileX].setColor(sf::Color::White);
        std::cout << "Tile Occupied!" << std::endl;
    }
}

void Rail::colorTileOccupation(Tiles &map, sf::Color color){
    int correspondingIndex;
    for(int i = 0; i < arrayRail.size(); i++){
        if(objectID == arrayRail[i]->objectID){
            correspondingIndex = i;
            break;
        }
    }
    //map.setColor(arrayRail[correspondingIndex]->topTileX, arrayRail[correspondingIndex]->topTileY, sf::Color(180,255,255));
    map.sprites[topTileY][topTileX].setColor(sf::Color(180,255,255));
}

void placeRail(Tiles &map, sf::RenderWindow &window){

    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    int y = 0; int x = 0;
    map.findTile(worldPos, x, y); 
    std::cout << "Y:    " << y << ", X:      " << x << std::endl;

    if(!map.TileEntities[y][x]->getID()){
        map.BuildingCatalogue.addRail();

        arrayRail[arrayRail.size()-1]->topTileX = x;
        arrayRail[arrayRail.size()-1]->topTileY = y;
        arrayRail[arrayRail.size()-1]->botTileX = x;
        arrayRail[arrayRail.size()-1]->botTileY = y;


        // Installs sprites
        sf::Vector2f centerpoint = map.getCenterPoint(y,x,y,x);
        map.sprites[y][x] = map.texture.getTexture(100);
        map.sprites[y][x].setPosition(centerpoint.x, centerpoint.y);
    
        // Deletes the standard DefaultTile object that the tile is pointing at
        delete map.TileEntities[y][x];
        map.TileEntities[y][x] = nullptr;
        map.TileEntities[y][x] = arrayRail[arrayRail.size()-1];
    }
    else{
        std::cout << "Tile Occupied!" << std::endl;
    }
}
