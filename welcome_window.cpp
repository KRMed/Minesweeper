#include "welcome_window.h"

Welcome_Window::Welcome_Window(){
    //Checking that the file opens properly
    if (!font.loadFromFile("files/font.ttf")) {
        throw std::runtime_error("Could not low font from file");
    }

    //Defining attributes of welcome_message text object
    welcome_message.setFont(font);
    welcome_message.setString("WELCOME TO MINESWEEPER!");
    welcome_message.setCharacterSize(24);
    welcome_message.setStyle(sf::Text::Underlined);
    welcome_message.setStyle(sf::Text::Bold);
    welcome_message.setFillColor(sf::Color::White);

    //Defining attributes of enter_name text object
    enter_name.setFont(font);
    enter_name.setString("Enter your name:");
    enter_name.setCharacterSize(20);
    enter_name.setStyle(sf::Text::Bold);
    enter_name.setFillColor(sf::Color::White);

    //Defining attributes of user_name text object
    user_name.setFont(font);
    user_name.setString("|");
    user_name.setCharacterSize(18);
    user_name.setStyle(sf::Text::Bold);
    user_name.setFillColor(sf::Color::Yellow);
}

void Welcome_Window::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void Welcome_Window::draw(sf::RenderWindow &window) const {
    window.draw(welcome_message);
    window.draw(enter_name);
    window.draw(user_name);
}

void Welcome_Window::addText(char letter) {
    name.push_back(letter);
    user_name.setString(name + "|");
}

void Welcome_Window::removeText() {
    name.pop_back();
    user_name.setString(name + "|");
}



