#ifndef WELCOME_WINDOW_H
#define WELCOME_WINDOW_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

class Welcome_Window {
    sf::Text welcome_message;
    sf::Text enter_name;
    sf::Text user_name;
    sf::Font font;
    std::string name;

    public:
        //Inside constructor(Initializing all text objects to have their proper attributes)
        Welcome_Window();

        //Getters to retrieve the text objects
        sf::Text& getWelcome () {
            return welcome_message;
        }
        sf::Text& getEnter () {
            return enter_name;
        }
        sf::Text& getUser () {
            return user_name;
        }

        //Centers texts origins at center of screen and bases it off window width and height
        void setText(sf::Text& text, float x, float y);

        //Takes in the window object to draw all text onto it
        void draw(sf::RenderWindow& window) const;

        //Updates text when there is an alphabetic input
        void addText(char letter);

        //Removes letter when hitting backspace
        void removeText();
};



#endif
