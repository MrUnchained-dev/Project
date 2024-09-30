#define INVENTORY
#pragma once
#include "Texture.h"
#include <vector>
#include <SFML/Graphics.hpp>

class ItemInventory{
public:
    int ItemID;
    sf::Sprite item;
    
    sf::RectangleShape ItemHitbox;
    ItemInventory(sf::Sprite sprite, int nr){
        ItemHitbox.setSize(sf::Vector2f(150.0f, 150.0f));
        ItemHitbox.setOrigin(sf::Vector2f(0, 150.0f));
        ItemHitbox.setFillColor(sf::Color(0,0,0,32));
        ItemID = nr;
        item = sprite;
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
        ItemsList.push_back(ItemInventory(texture.getInventoryItemTexture(DefaultHouseID), DefaultHouseID));
        ItemsList[ItemsList.size()-1].setPosition(25 + (ItemsList.size()-1)*175, 775);

        ItemsList.push_back(ItemInventory(texture.getInventoryItemTexture(RailID_100), RailID_100));
        ItemsList[ItemsList.size()-1].setPosition(25 + (ItemsList.size()-1)*175, 775);

        active = false;

        inventoryBackground.setSize(sf::Vector2f(1600, 200));
        inventoryBackground.setOrigin(sf::Vector2f(0, 200));
        inventoryBackground.setPosition(sf::Vector2f(0, 800));
        inventoryBackground.setFillColor(sf::Color(224,224,224,200));
    }

    void addItemToInventory(sf::Sprite sprite, int id){
        ItemsList.push_back(ItemInventory(sprite, id));
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
        
        if(storedWorldPosition != sf::Mouse::getPosition(window)){
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
};