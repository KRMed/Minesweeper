#include "welcome_window.h"

Welcome_Window::Welcome_Window(){
    if (!font.loadFromFile("files/images/font.ttf")){
      throw std::runtime_error("Could not low font from file");
    }

    welcome_message.setFont(font);


}