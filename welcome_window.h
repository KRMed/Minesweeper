#ifndef WELCOME_WINDOW_H
#define WELCOME_WINDOW_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <string>



class Welcome_Window {
    sf::Text welcome_message;
    sf::Text enter_name;
    sf::Text user_name;
    sf::Font font;

    public:
        //Inside constructor(Initializing all text objects to have their proper attributes)
        Welcome_Window();

        //Centers texts origins at center of screen and bases it off window width and height
        void setText(sf::Text& text, float x, float y);

        //Takes in the window object to draw all text onto it
        void draw(sf::Window& window);

        //Updates text when there is an alphabetic input
        void updateText(sf::Text& text);
};



#endif
