#pragma once
#define TILES
#include <SFML/Graphics.hpp>
#include "Texture.h"
#include "Buildings.h"
//#include "BuildingsImplementation.h"
#include <vector>

class Tiles{
private:
public:
    Texture texture;
    int tiles_col;
    int tiles_row;
    int **TileContainer;                            //TileContainer is for the actual tile things occupying the tiles
    sf::VertexArray **tiles;

    sf::Sprite **sprites;

    BuildingContainers BuildingCatalogue;
    TileEntity ** *TileEntities;

    /*std::vector<Rail*> arrayRails;
    std::vector<DefaultHouse*> arrayDefaultHouse;
    std::vector<ExtraHouse*>  arrayExtraHouse;*/


    Tiles(int col, int row){            //Row is for X-axis, Col is for Y-axis
        tiles_col = col;
        tiles_row = row;


        tiles = new sf::VertexArray*[tiles_col];
        TileEntities = new TileEntity**[tiles_col];
        sprites = new sf::Sprite*[tiles_col];


        for (int i = 0; i < tiles_col; i++){


            tiles[i] = new sf::VertexArray[tiles_row];
            TileEntities[i] = new TileEntity*[tiles_row];
            sprites[i] = new sf::Sprite[tiles_row];

            int x = 0-i; int y = 0+i;
            for (int j = 0; j < tiles_row; j++){
                tiles[i][j] = sf::VertexArray(sf::Quads, 4);

                //The head of the quad
                tiles[i][j][0].position = sf::Vector2f(50+50*x,     0+25*y);    tiles[i][j][0].color = sf::Color(0,255,180);  
                tiles[i][j][1].position = sf::Vector2f(100+50*x,    25+25*y);   tiles[i][j][1].color = sf::Color(0,193,166); 
                tiles[i][j][2].position = sf::Vector2f(50+50*x,     50+25*y);   tiles[i][j][2].color = sf::Color(120,250,233);
                tiles[i][j][3].position = sf::Vector2f(0+50*x,      25+25*y);   tiles[i][j][3].color = sf::Color(0,193,166);



                //tiles[i][j][0].texCoords = sf::Vector2f(400,   213);
                //tiles[i][j][1].texCoords = sf::Vector2f(800,   413);
                //tiles[i][j][2].texCoords = sf::Vector2f(400,   613);
                //tiles[i][j][3].texCoords = sf::Vector2f(0,     413);
                

                /*tiles[i][j][4].position = sf::Vector2f(0+50*x,      25+25*y); tiles[i][j][4].color = sf::Color(0, 112, 67);
                tiles[i][j][5].position = sf::Vector2f(50+50*x,     50+25*y);   tiles[i][j][5].color = sf::Color(0, 112, 67);
                tiles[i][j][6].position = sf::Vector2f(50+50*x,     100+25*y);  tiles[i][j][6].color = sf::Color(0, 112, 67);
                tiles[i][j][7].position = sf::Vector2f(0+50*x,      75+25*y);   tiles[i][j][7].color = sf::Color(0, 112, 67);

                tiles[i][j][8].position = sf::Vector2f(50+50*x,     50+25*y);   tiles[i][j][8].color = sf::Color(71, 228, 165);
                tiles[i][j][9].position = sf::Vector2f(100+50*x,    25+25*y);   tiles[i][j][9].color = sf::Color(71, 228, 165);
                tiles[i][j][10].position = sf::Vector2f(100+50*x,   75+25*y);   tiles[i][j][10].color = sf::Color(71, 228, 165);
                tiles[i][j][11].position = sf::Vector2f(50+50*x,    100+25*y);  tiles[i][j][11].color = sf::Color(71, 228, 165);*/

                x++; y++;

                TileEntities[i][j] = addDefaultTile();
            }
        }
    }
    

    bool TileBoundary(int x, int y, int row, int col){

        if(y >= -(x/2)+25 +(row*50) &&         // Top left boundary
           y >= (x/2) - 25 +(col*50) &&        // Top right boundary
           y <= x/2 + 25 +(col*50) &&          // Bottom left boundary
           y <= (-x/2) + 75 +(row*50)){         // Bottom right boundary
            return true;
        }
        else{
            return false;
        }
    }


    bool TotalTileBoundary(int x, int y, int row, int col){
        if(y >= -(x/2) + 25 && y >= (x/2) - 25 && y <= (x/2) - 25+(50*col) && y <= -(x/2) + 25 + (50*row)){
            return true;
        }
        else{
            return false;
        }
    }


    void findTile(sf::Vector2f mouseCursor, int &row, int &col){
        for(int i = 0; i < tiles_col; i++){
            for(int j = 0;j < tiles_row; j++){
                if(TileBoundary(mouseCursor.x, mouseCursor.y, j, i)){
                    row = j; col = i;
                }
            }
        }
    }

    sf::Vector2f getCenterPoint(int topY, int topX, int botY, int botX){    //Gets the center point of the tile
        
        float topPoint = topX*25 + topY*25;
        float rightPoint = (botX*50-topY*50)+100;
        float leftPoint = (topX*50-botY*50);
        float botPoint = botX*25 + botY*25 + 50;


        float pointX = (rightPoint-leftPoint)/2;
        float pointY = (botPoint-topPoint)/2;

        return sf::Vector2f(leftPoint+pointX, topPoint+pointY);
    }



    void setColor(int x, int y, sf::Color c){
        for (int i = 0; i < 4; i++){
            tiles[y][x][i].color = c;
        }
    }




    void draw(sf::RenderWindow &window){
        for(int i = 0; i < tiles_col; i++){
            for(int j = 0; j < tiles_row; j++){
                if(TileEntities[i][j]->getID() != 0){
                    window.draw(tiles[i][j]);
                }
                else{
                    window.draw(tiles[i][j]);
                }
            }
        }
        for(int i = 0; i < tiles_col; i++){
            for(int j = 0; j < tiles_row; j++){
                window.draw(sprites[i][j]);
            }
        }
    }
};