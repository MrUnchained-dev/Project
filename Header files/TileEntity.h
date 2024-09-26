#pragma once
#define TILEENTITY
#include <SFML/Graphics.hpp>
class Tiles;

class TileEntity{
public:
    int topTileX;
    int topTileY;
    int botTileX;
    int botTileY;
    
    int objectID = 0;
    int ID;
    int getID() {return ID;}
    virtual void whenClick() = 0;
    virtual void colorTileOccupation(Tiles &map, sf::Color color) = 0;
    virtual void tileOccupation(Tiles &map, sf::RenderWindow &window, int x, int y, int &hoveringX, int &hoveringY, std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY) = 0;
    virtual void placeEntity(Tiles &map, sf::RenderWindow &window, std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY) = 0;
};
