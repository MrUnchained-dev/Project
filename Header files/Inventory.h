#define INVENTORY
#pragma once
#include "Texture.h"
#include <vector>
#include <SFML/Graphics.hpp>

class ItemInventory{
public:
    int ItemID;
    sf::Sprite item;
    TileEntity *itemObject;
    sf::RectangleShape ItemHitbox;

    
    ItemInventory(sf::Sprite sprite, int nr, TileEntity &object){
        ItemHitbox.setSize(sf::Vector2f(150.0f, 150.0f));
        ItemHitbox.setOrigin(sf::Vector2f(0, 150.0f));
        ItemHitbox.setFillColor(sf::Color(0,0,0,32));
        ItemID = nr;
        item = sprite;
        itemObject = &object;
    }
    
    void setPosition(int x, int y){
        ItemHitbox.setPosition(sf::Vector2f(x,y));
        item.setPosition(sf::Vector2f(x+75.0f, y-75.0f));
    }

    void changePosition(int x, int y){
        ItemHitbox.setPosition(ItemHitbox.getPosition().x + x, ItemHitbox.getPosition().y);
        item.setPosition(item.getPosition().x + x, item.getPosition().y);
        
    }
};


class Inventory{
public:

    sf::View inventoryView;
    Texture texture;
    bool active;
    sf::RectangleShape inventoryBackground;
    std::vector<ItemInventory> ItemsList;

    bool initialListPos = false;
    bool pickedItem = false;
    sf::Vector2i storedWorldPosition;
    Inventory(){
        /*ItemsList.push_back(ItemInventory(texture.getInventoryItemTexture(DefaultHouseID), DefaultHouseID));
        ItemsList[ItemsList.size()-1].setPosition(25 + (ItemsList.size()-1)*175, 775);

        ItemsList.push_back(ItemInventory(texture.getInventoryItemTexture(RailID_100), RailID_100));
        ItemsList[ItemsList.size()-1].setPosition(25 + (ItemsList.size()-1)*175, 775);*/

        active = false;

        inventoryBackground.setSize(sf::Vector2f(1600, 200));
        inventoryBackground.setOrigin(sf::Vector2f(0, 200));
        inventoryBackground.setPosition(sf::Vector2f(0, 800));
        inventoryBackground.setFillColor(sf::Color(224,224,224,200));

        inventoryView = sf::View(sf::Vector2f(800.0f, 400.0f), sf::Vector2f(1600.0f,800.0f));
    }

    void addItemToInventory(sf::Sprite sprite, int id, TileEntity &object){
        ItemsList.push_back(ItemInventory(sprite, id, object));
        ItemsList[ItemsList.size()-1].setPosition(25 + (ItemsList.size()-1)*175, 775);
    }

    void deleteItemFromInventory(int indexNr){
        ItemsList[indexNr].itemObject = nullptr;
        ItemsList.erase(ItemsList.begin() + indexNr);

        // Updates list and its positions as well
        setPositionsDefault();
    }

    void draw(sf::RenderWindow &window){
        if(active){
            window.setView(inventoryView);
            window.draw(inventoryBackground);
            for(int i = 0; i < ItemsList.size(); i++){
                window.draw(ItemsList[i].ItemHitbox);
                window.draw(ItemsList[i].item);
            }
        }
    }
    
    void setPositionsDefault(){
        for(int i = 0; i < ItemsList.size(); i++){
            ItemsList[i].setPosition(25 + i*175, 775);
        }
    }





    void moveList(sf::RenderWindow &window){
        if(!initialListPos){
            storedWorldPosition = sf::Mouse::getPosition(window);
            initialListPos = true;
        }
        
        if(storedWorldPosition.x != sf::Mouse::getPosition(window).x){
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            sf::Vector2i delta = pos - storedWorldPosition;
            
            if(!ItemsList.empty() && ItemsList[0].ItemHitbox.getPosition().x + delta.x >= 25){
                for(int i = 0; i < ItemsList.size(); i++){
                    ItemsList[i].changePosition(delta.x, 0);

                }
                storedWorldPosition = pos;
            }

        }        
    }

    void pickedObjectFromInv(Tiles &map, sf::RenderWindow &window, sf::View &view, int itemNr){
        int y = 0; int x = 0;
        int hoveringY = 0; int hoveringX = 0;

        bool firstClick = false;
        std::vector<int> arrayTilesX;
        std::vector<int> arrayTilesY;

        bool functionTerminate = false;

        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        std::cout << "Triggered" << std::endl;
        while(window.isOpen()){
            sf::Event event;

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !inventoryBackground.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))){

                if(!firstClick){
                    hoveringY = y; hoveringX = x;
                    firstClick = true;
                    std::cout << hoveringY << ", " << hoveringX << std::endl;
                }       
                ItemsList[itemNr].itemObject->tileOccupation(map, window, x, y, hoveringX, hoveringY, arrayTilesX, arrayTilesY);
            }
            else{
                for(int i : arrayTilesY){
                    for(int j : arrayTilesX){
                        map.setColor(j, i, sf::Color::White);
                    }
                }
            }
            
            while(window.pollEvent(event)){
                switch(event.type){
                    
                    case sf::Event::Closed:{
                        std::cout << "Window closed" << std::endl;
                        window.close();
                        break;}
                        

                    case sf::Event::MouseMoved:{
                        if(!inventoryBackground.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))){
                            worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                            map.findTile(worldPos, x, y);
                            //std::cout << y << ", " << x << std::endl;
                        }
                        else{
                            std::cout << "Mouse inside" << std::endl;
                        }
                        break;}


                    case sf::Event::MouseButtonReleased:{
                        if(!inventoryBackground.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))){
                            std::cout << "MousebuttonReleased" << std::endl;
                            if(ItemsList[itemNr].itemObject->placeEntity(map, window, arrayTilesX, arrayTilesY)){

                                std::cout << "Class Inventory: The ID of [" << y << "][" << x <<"] should be: " << map.TileEntities[y][x]->ID << std::endl;
                                deleteItemFromInventory(itemNr);
                            }
                            
                        }
                        else{
                            arrayTilesX.clear();
                            arrayTilesY.clear();
                        }
                        functionTerminate = true;
                        firstClick = false;
                        break;}

                    default:{
                        break;}
                }

                if(functionTerminate){
                    break;
                }
            }
            if(functionTerminate){
                initialListPos = false;
                pickedItem = false;
                break;
            }
            window.clear();
            map.draw(window);
            draw(window);
            window.setView(view);
            window.display();
        }
     std::cout << "Class Inventory: Way to exit." << std::endl;
    }
};