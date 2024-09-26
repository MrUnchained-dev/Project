//#include "Header Files/Tiles.h"
#include "Header files/BuildingsImplementation.h"
#include "Header Files/Camera.h"
#include "Header Files/TrainAlgorithm.h"
#include "Header Files/UserInterface.h"
#include "Header Files/ContainerID.h"

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

template <typename figure>
sf::Vector2f getBottomCenterPoint (figure &object) {
    sf::FloatRect bounds = object.getLocalBounds();
    sf::Vector2f botcenterpoint(bounds.getSize().x/2.0f, bounds.getSize().y);
    
    return botcenterpoint;
}

template <typename figure>
sf::Vector2f getCenterPoint (figure &object) {
    sf::FloatRect bounds = object.getBounds();
    sf::Vector2f botcenterpoint(bounds.left + 50.0f, bounds.top + 25.0f);
    
    return botcenterpoint;
}

int main(){


    sf::ContextSettings settings;
    settings.antialiasingLevel = 32;
    sf::RenderWindow window(sf::VideoMode(1600, 800), "My window", sf::Style::Default, settings);
    sf::View view(sf::Vector2f(400, 400), sf::Vector2f(1600,800));


    //UI design




    
    int AxisX = 30, AxisY = 30;
    Tiles Map(AxisY,AxisX);              // Initialize the tiles
    UserInterface ui;                    // Initialize the user interface buttons
    Camera camera;                       // Initialize the camera class
    Texture texture;                     // Initialize the texture class

    sf::Texture hellokitty;
    if (!hellokitty.loadFromFile("Images/hellokitty.png")){
        std::cout << "Error in loading file!" << std::endl;
    }

    sf::Sprite train;
    train.setTexture(hellokitty);
    train.setScale(sf::Vector2f(0.12f, 0.12f));
    train.setOrigin(getBottomCenterPoint(train).x, getBottomCenterPoint(train).y);
    train.setPosition(getCenterPoint(Map.tiles[10][15]));
    

    // Initialize all variables/objects needed for program 
    sf::Vector2f worldPosition;
    bool buttonPressed = false;
    int containerID = 0;                        // Used for checking if the mouse has hovered away from the pressed button upon release of said button
    while(window.isOpen()){
        sf::Event event;
        
        

        // The camera movement here including in the else if condition makes sure that even if the mouse is moved over other buttons while button is pressed, it will
        // count as camera movement and nothing else

        if(camera.CameraMoveMode){
            camera.CameraMovement(view, window);
        }

        else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

            if(!ui.mouseOverButtons(window) && buttonPressed == false){
                camera.CameraMovement(view, window);
            }
            
            else{
                if(ui.mouseOverEditMap(window)){
                    ui.ButtonEditMap.setFillColor(sf::Color(0, 253, 236));
                    containerID = ID_ButtonEditMap;
                }
                buttonPressed = true;   
            }
        }


        while (window.pollEvent(event)){
        
            switch(event.type){


                
                case sf::Event::KeyPressed:
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                        std::cout << worldPosition.y << ", " << worldPosition.x << std::endl;
                        //std::cout << "I have been pressed";
                        Storage::changeNetCash(50);
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseMoved:
                    worldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    
                    break;

                case sf::Event::MouseButtonReleased:
                    ui.ButtonEditMap.setFillColor(sf::Color(0, 253, 166));
                    camera.InitialCameraPos = false;

                    if(!camera.CameraMoveMode){

                        if(ui.mouseOverEditMap(window) && ID_ButtonEditMap == containerID){
                            //std::cout << "Edit mode!" << std::endl;

                            ui.EditMode(window, view, event, Map);

                        }

                        if(containerID == 0 && Map.TotalTileBoundary(worldPosition.x, worldPosition.y, Map.tiles_row, Map.tiles_col)){
                            int i = 0; int j = 0;
                            Map.findTile(worldPosition, j, i);
                            std::cout << "Tile: [" << i << "][" << j << "]" << std::endl;
                        }
                    }
                    containerID = 0;
                    buttonPressed = false;
                    camera.CameraMoveMode = false;
                    break;
                
                case sf::Event::MouseWheelScrolled:
                    Zoom(view, event);
                    break;
            }
        }

        //Map.tiles[0][0][0].texCoords = sf::Vector2f(2000 + 1000,  130);
        //Map.tiles[0][1][1].texCoords = sf::Vector2f(3000 + 1000,  2033);
        //Map.tiles[1][0][2].texCoords = sf::Vector2f(2000 + 1000,  2533);
        //Map.tiles[1][1][3].texCoords = sf::Vector2f(1000 + 1000,  2033);
        window.clear();



        Map.draw(window);
        //train_algorithm(train, Map);
        window.draw(train);
        ui.draw(window);

        //resources.setString(std::to_string(Storage::showCash()));
        //window.draw(ui.text.cashUI); 
        window.setView(view);
        window.display();
    }

    return 0;
}
