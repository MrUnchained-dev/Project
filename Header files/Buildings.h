#pragma once
#define BUILDINGS

#include <vector>
#include <iostream>

#include "TileEntity.h"
//#include "Tiles.h"
#include "Storage.h"
#include "ContainerID.h"


class DefaultTile : public TileEntity{
public:
    DefaultTile(){
        ID = 0;
    }

    void whenClick() override{}
    void colorTileOccupation(Tiles &map, sf::Color color) override {}
    void tileOccupation(Tiles &map, sf::RenderWindow &window, int x, int y, int &hoveringX, int &hoveringY, std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY) override{}
    void placeEntity(Tiles &map, sf::RenderWindow &window, std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY) override{}
};

DefaultTile *addDefaultTile(){
    DefaultTile *obj = new DefaultTile;
    return obj;
}




class Rail : public TileEntity{
public:
    Rail() {ID = RailID_100;}
    
    void whenClick() override{}
    void colorTileOccupation(Tiles &map, sf::Color color) override; 
    void tileOccupation(Tiles &map, sf::RenderWindow &window, int x, int y, int &hoveringX, int &hoveringY, std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY) override;
    void placeEntity(Tiles &map, sf::RenderWindow &window, std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY) override;

};





class Decoration : public TileEntity{
public:

};





class Building : public TileEntity{
public:
    int number;
    virtual void redeemCash() = 0;
};


    //Building ID 1000
class DefaultHouse : public Building{
public:
    DefaultHouse(){
        ID = DefaultHouseID;
    }
    void redeemCash() override{
        Storage::changeNetCash(100);
    }
    void whenClick() override{
        redeemCash();
    }

    void colorTileOccupation(Tiles &map, sf::Color color) override;
    void tileOccupation(Tiles &map, sf::RenderWindow &window, int x, int y, int &hoveringX, int &hoveringY, std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY) override;
    void placeEntity(Tiles &map, sf::RenderWindow &window, std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY) override;
};

class ExtraHouse : public Building{
public:
    void redeemCash() override{
        Storage::changeNetCash(50);
    }
    void whenClick() override{
        redeemCash();
    }
    void colorTileOccupation(Tiles &map, sf::Color color) override {};
    void tileOccupation(Tiles &map, sf::RenderWindow &window, int x, int y, int &hoveringX, int &hoveringY, std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY) override{}
    void placeEntity(Tiles &map, sf::RenderWindow &window, std::vector<int> *&arrayTilesX, std::vector<int> *&arrayTilesY) override{}
};
static std::vector<Rail*> arrayRail;
static std::vector<DefaultHouse*> arrayDefaultHouse;
static std::vector<ExtraHouse*>  arrayExtraHouse;

class BuildingContainers{
public:

    DefaultHouse *addDefaultHouse(){
        DefaultHouse *obj = new DefaultHouse;
        arrayDefaultHouse.push_back(obj);
        arrayDefaultHouse[arrayDefaultHouse.size()-1]->objectID = arrayDefaultHouse.size();
        return obj;
    }

    ExtraHouse *addExtraHouse(){
        ExtraHouse *obj = new ExtraHouse;
        arrayExtraHouse.push_back(obj);
        arrayExtraHouse[arrayExtraHouse.size()-1]->objectID = arrayExtraHouse.size();
        return obj;
    }

    Rail *addRail(){
        Rail *obj = new Rail;
        arrayRail.push_back(obj);
        arrayRail[arrayRail.size()-1]->objectID = arrayRail.size();
        return obj;
    }

};
