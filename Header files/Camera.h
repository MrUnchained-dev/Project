#pragma once
#define CAMERA
#include <SFML/Graphics.hpp>
#include <iostream>

class Camera{
 private:
    sf::Vector2f storedWorldPosition;
 public:
    bool InitialCameraPos;
    bool CameraMoveMode;

    
    Camera(){
        CameraMoveMode = false;
        InitialCameraPos = false;

    }
    

    void CameraMovement(sf::View &view, const sf::RenderWindow &window){
        if(InitialCameraPos == false){
            storedWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            InitialCameraPos = true;
        }
        if(storedWorldPosition != window.mapPixelToCoords(sf::Mouse::getPosition(window))){
            sf::Vector2f worldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::Vector2f delta = storedWorldPosition - worldPosition;
            
            view.move(delta);

            CameraMoveMode = true;
        }
    }

};






void Zoom(sf::View &view, sf::Event &event){
    sf::Vector2f size = view.getSize();
        if(event.mouseWheelScroll.delta > 0){
            if(size.x >= 324 && size.y >= 162){
                view.setSize(size.x - 12.f, size.y - 6.f);
            }
        }
        if(event.mouseWheelScroll.delta < 0){
            if(size.x <= 2160 && size.y <= 1080){
                view.setSize(size.x + 12.f, size.y + 6.f);
            }
        }
}