#define USERINTERFACE
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <string>

#include "Texture.h"
#include "Tiles.h"
#include "Camera.h"

class TextUI{
private:
    sf::Font font;
    sf::Text cashUI;
    sf::Text gemsUI;
public:

    TextUI(){
        if(!font.loadFromFile("Font/Lato-Regular.ttf")){
            std::cout << "Loading the font failed!" << std::endl;
        }

        cashUI.setFont(font);
        cashUI.setString(std::to_string(Storage::showCash()));
        cashUI.setPosition(sf::Vector2f(10.0f, 0.f));
        cashUI.setFillColor(sf::Color::White);

        gemsUI.setFont(font);
        gemsUI.setString(std::to_string(Storage::showGems()));
        gemsUI.setPosition(sf::Vector2f(200.0f, 0.f));
        gemsUI.setFillColor(sf::Color::White);
    }

    void updateText(){
        cashUI.setString(std::to_string(Storage::showCash()));
        gemsUI.setString(std::to_string(Storage::showGems()));
    }

    void draw(sf::RenderWindow &window){
        updateText();
        window.draw(cashUI);
        window.draw(gemsUI);
    }
};


class UserInterface{
private:
    sf::View uiView;
    Texture textures;
    Camera camera;
    TextUI text;

public:
    sf::RectangleShape ButtonEditMap;
    sf::RectangleShape ReverseButtonEditMap;

    UserInterface(){
        uiView = sf::View(sf::Vector2f(800.0f, 400.0f), sf::Vector2f(1600.0f,800.0f));
        ButtonEditMap = sf::RectangleShape(sf::Vector2f(100.0f, 100.0f));
        ButtonEditMap.setPosition(1500.0f, 200.0f);
        ButtonEditMap.setFillColor(sf::Color(0, 253, 166));


        ReverseButtonEditMap = sf::RectangleShape(sf::Vector2f(100.0f, 100.0f));
        ReverseButtonEditMap.setPosition(1500.0f, 200.0f);
        ReverseButtonEditMap.setFillColor(sf::Color(255, 225, 170));
    }

    void draw(sf::RenderWindow &window){
        window.setView(uiView);
        window.draw(ButtonEditMap);
        text.draw(window);
    }

    void draw(sf::RenderWindow &window, sf::RectangleShape button){
        window.setView(uiView);
        window.draw(button);
    }


    bool mouseOverButtons(const sf::RenderWindow &window){
        return ButtonEditMap.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
    }


    bool mouseOverButton(const sf::RenderWindow &window, sf::RectangleShape button){
        return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
    }


    bool mouseOverEditMap(const sf::RenderWindow &window){
        return ButtonEditMap.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
    }


    void EditMode(sf::RenderWindow &window, sf::View &view, sf::Event &event, Tiles &map){
        bool holdMode = false;
        bool holdModeFailed = false;
        bool sleepMode = false;
        int buttonPressed = 0;

        int hoveringX, hoveringY;
        int initialX, initialY;
        int y = 0; int x = 0;

        std::vector<int> *arrayTilesX = nullptr;
        std::vector<int> *arrayTilesY = nullptr;

        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        map.findTile(worldPos, x, y);

        while(window.isOpen()){
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !holdMode && !holdModeFailed){

            
                    if(mouseOverButton(window, ReverseButtonEditMap) && !camera.CameraMoveMode){
                        //std::cout << " I have ben called";
                        ReverseButtonEditMap.setFillColor(sf::Color(255, 240, 210));
                        buttonPressed = 1;
                    }

                    else if(!map.TileEntities[y][x]->getID() && !buttonPressed){
                        camera.CameraMovement(view, window);}


                    else if(map.TileEntities[y][x]->getID() && !buttonPressed){
                        initialX = x; initialY = y;
                        hoveringX = x; hoveringY = y;

                        

                        // Sequence under checks whether if the mouse is still pointing at the same tile or not after the sleeping sequence
                            // Sleep sequence is to simulate the feeling of holding down left key until it is selected
                        sleepMode = true;
                        sf::sleep(sf::milliseconds(300));
                        sleepMode = false;

                        worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        int tempY, tempX;
                        map.findTile(worldPos, tempX, tempY);

                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && x == tempX && y == tempY){
                            //map.setColor(x,y, sf::Color(180, 255, 255));
                            map.TileEntities[y][x]->colorTileOccupation(map, sf::Color(180, 255, 255));
                            holdMode = true;
                        }
                        else{
                            //map.setColor(initialX, initialY, sf::Color(255, 255, 255));
                            holdModeFailed = true;}}
                    }   


                if(holdMode && (hoveringX != x || hoveringY != y)){
                    map.TileEntities[initialY][initialX]->tileOccupation(map, window, x, y, hoveringX, hoveringY, arrayTilesX, arrayTilesY);
                }


            while (window.pollEvent(event)){
                switch(event.type){

                    case sf::Event::KeyPressed:
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                                placeRail(map, window);
                            }
                            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                                placeDefaultHouse(map, window);
                            }
                            break;
                    case sf::Event::MouseMoved:
                            if(sleepMode){
                                break;
                            }
                            worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                            map.findTile(worldPos, x, y);
                            break;


                    case sf::Event::Closed:
                            window.close();
                            break;


                    case sf::Event::MouseButtonReleased:

                            //std::cout << "Mouse pressed: Tile: [" << y << "][" << x << "], ID: " << map.TileEntities[y][x]->getID() << std::endl;
                            //std::cout << "Object id: " << map.TileEntities[y][x]->objectID << ", ID: " << map.TileEntities[y][x]->getID() << std::endl;

                            if(camera.InitialCameraPos){
                                camera.CameraMoveMode = false;
                                camera.InitialCameraPos = false;
                                break;
                            }

                            // If the mouse button is being released upon the editButton (buttonPressed = 1 means that it was already pressed on it)
                            if(buttonPressed == 1 && mouseOverButton(window, ReverseButtonEditMap)){
                                ReverseButtonEditMap.setFillColor(sf::Color(255, 225, 170));
                                buttonPressed = 2;
                                break;
                            }
                            // If the mouse button is released upon anything else that is not the editButton
                            else{
                                ReverseButtonEditMap.setFillColor(sf::Color(255, 225, 170));
                                buttonPressed = 0;
                            }


                            holdModeFailed = false;
                            if(holdMode == true && map.TileEntities[y][x]->getID() >= 0){

                                map.TileEntities[initialY][initialX]->placeEntity(map, window, arrayTilesX, arrayTilesY);

                            }

                            holdMode = false;
                            map.sprites[y][x].setColor(sf::Color::White);
                            //map.setColor(x, y, sf::Color(255,255,255));
                            break;


                    case sf::Event::MouseWheelScrolled:
                            Zoom(view, event);
                            break;


                    default:
                            break;}}

            if(buttonPressed == 2) {
                
                break;}

            //for(int i = 0; i <= 1; i++){
            //    for(int j = 0; j <= 1; j++){             
//
            //        map.tiles[i][j][0].texCoords = sf::Vector2f(2000 + 1000*j - 1000*i,  1533 - 500*(i-j));
            //        map.tiles[i][j][1].texCoords = sf::Vector2f(3000 + 1000*j - 1000*i,  2033 - 500*(i-j));
            //        map.tiles[i][j][2].texCoords = sf::Vector2f(2000 + 1000*j - 1000*i,  2533 - 500*(i-j));
            //        map.tiles[i][j][3].texCoords = sf::Vector2f(1000 + 1000*j - 1000*i,  2033 - 500*(i-j));
            //                    
            //    }
            //}
            //map.tiles[0][0][0].texCoords = sf::Vector2f(2000,  1533);
            //map.tiles[0][0][1].texCoords = sf::Vector2f(3000,  2033);
            //map.tiles[0][0][2].texCoords = sf::Vector2f(2000,  2533);
            //map.tiles[0][0][3].texCoords = sf::Vector2f(1000,  2033);

            map.tiles[0][0][0].texCoords = sf::Vector2f(2000,  1533);
            map.tiles[0][0][1].texCoords = sf::Vector2f(3000,  2033);
            map.tiles[0][0][2].texCoords = sf::Vector2f(2000,  2533);
            map.tiles[0][0][3].texCoords = sf::Vector2f(1000,  2033);




            
            window.clear();

            map.draw(window);
            
            draw(window, ReverseButtonEditMap);

            window.setView(view);
            window.display();
        }
    }
};

