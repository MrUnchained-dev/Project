#include <iostream>

#include <SFML/Graphics.hpp>


int main(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(800, 800), "My window", sf::Style::Default, settings);
    sf::View view(sf::Vector2f(400,400), sf::Vector2f(400,400));

    sf::RectangleShape white;
    white.setSize(sf::Vector2f(100,100));
    white.setOrigin(50,50);
    white.setPosition(400,400);
    white.setFillColor(sf::Color::White);

    sf::RectangleShape shapeSet;
    shapeSet.setSize(sf::Vector2f(50,50));
    shapeSet.setOrigin(25,25);
    shapeSet.setPosition(400,600);
    shapeSet.setFillColor(sf::Color::Red);
    
    while(window.isOpen()){
        sf::Event event;

        while(window.isOpen()){

            sf::Event event;

            while(window.pollEvent(event)){

                switch(event.type){
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:

                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                            view.move(sf::Vector2f(10,0));
                        }
                        else{
                            view.move(sf::Vector2f(-10,0));
                        }
                        break;
                }
            }

            window.clear();
            window.setView(view);
            window.draw(white);
            window.setView(window.getDefaultView());
            window.draw(shapeSet);
            window.display();
        }
    }

    return 0;
}