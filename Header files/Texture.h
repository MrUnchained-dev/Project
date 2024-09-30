#define TEXTURES
#pragma once
#include "ContainerID.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>


class Texture{
private:
    std::unordered_map<int, sf::Sprite> renderTexture;

    std::unordered_map<int, sf::Sprite> inventoryItemTexture;

    sf::Texture RailTexture;
    sf::Sprite Rail;

    sf::Texture DefaultHouseTexture;
    sf::Sprite DefaultHouse;

public:

    Texture(){
        if (!RailTexture.loadFromFile("Images/Rail.png")){
            std::cout << "Load failed" << std::endl;
        }
        Rail.setTexture(RailTexture);
        Rail.setOrigin(sf::Vector2f(400, 400));
        Rail.setScale(sf::Vector2f(0.1335f, 0.1335f));

        renderTexture[RailID_100] = Rail;
        inventoryItemTexture[RailID_100] = Rail;

        if (!DefaultHouseTexture.loadFromFile("Images/houseFinal1.png")){
            std::cout << "Load failed" << std::endl;
        }
        
        DefaultHouse.setTexture(DefaultHouseTexture);
        DefaultHouse.setOrigin(sf::Vector2f(2000, 2533));
        DefaultHouse.setScale(sf::Vector2f(0.1f, 0.1f));
        renderTexture[DefaultHouseID] = DefaultHouse;

        DefaultHouse.setScale(sf::Vector2f(0.03f, 0.03f));
        inventoryItemTexture[DefaultHouseID] = DefaultHouse;

    }

    sf::Sprite getTexture(int id){
        if(renderTexture.find(id) != renderTexture.end()){
            return renderTexture[id];
        }
        else{
            return renderTexture[1000];
        }
    }

    sf::Sprite getInventoryItemTexture(int id){
        if(inventoryItemTexture.find(id) != inventoryItemTexture.end()){
            return inventoryItemTexture[id];
        }
        else{
            std::cout << "Couldn't find itemInventoryItem!" << std::endl;
            sf::Sprite fail;
            return fail;
        }
    }
}; 
