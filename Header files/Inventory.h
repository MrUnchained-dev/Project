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
    Texture texture;
    bool active;
    sf::RectangleShape inventoryBackground;
    std::vector<ItemInventory> ItemsList;

    bool initialListPos = false;
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
    }

    void addItemToInventory(sf::Sprite sprite, int id, TileEntity &object){
        ItemsList.push_back(ItemInventory(sprite, id, object));
        ItemsList[ItemsList.size()-1].setPosition(25 + (ItemsList.size()-1)*175, 775);
    }

    void draw(sf::RenderWindow &window){
        if(active){
            window.draw(inventoryBackground);
            for(int i = 0; i < ItemsList.size(); i++){
                window.draw(ItemsList[i].ItemHitbox);
                window.draw(ItemsList[i].item);
            }
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

    void setPositionsDefault(){
        for(int i = 0; i < ItemsList.size(); i++){
            ItemsList[i].setPosition(25 + i*175, 775);
        }
    }


    void pickedObjectFromInv(Tiles &map, sf::RenderWindow &window, sf::View &view, int itemNr){
        int y = 0; int x = 0;
        int hoveringY; int hoveringX;

        bool firstClick = false;
        std::vector<int> *arrayTilesX = nullptr;
        std::vector<int> *arrayTilesY = nullptr;

        bool functionTerminate = false;

        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        std::cout << "Triggered" << std::endl;
        while(window.isOpen()){
            sf::Event event;
            
            while(window.pollEvent(event)){
                switch(event.type){

                    case sf::Event::MouseButtonPressed:
                        std::cout << "Buttonpressed" << std::endl;
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

                            if(!firstClick){
                                hoveringY = y; hoveringX = x;
                                firstClick = true;
                            }


                            
                            if(!inventoryBackground.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))){
                                ItemsList[itemNr].itemObject->tileOccupation(map, window, x, y, hoveringX, hoveringY, arrayTilesX, arrayTilesY);
                            }  
                        }
                        break;


                    case sf::Event::Closed:
                        std::cout << "Window closed" << std::endl;
                        window.close();
                        break;
                        

                    case sf::Event::MouseMoved:
                        std::cout << "Mouse moved" << std::endl;
                        worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        map.findTile(worldPos, x, y);
                        break;


                    case sf::Event::MouseButtonReleased:
                        std::cout << "MousebuttonReleased" << std::endl;
                        ItemsList[itemNr].itemObject->placeEntity(map, window, arrayTilesX, arrayTilesY);
                        functionTerminate = true;
                        break;
                }

                if(functionTerminate){
                    break;
                }
                window.clear();

                map.draw(window);
                draw(window);
                //ui.drawEditMode(window);
                window.setView(view);
                window.display();
            }
        if(functionTerminate){
            break;
        }
        }
    }
};