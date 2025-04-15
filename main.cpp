#include "game_window.h"
#include "welcome_window.h"

int main() {
    //First, read rowCount and colCount since all the windows and sizes are based on that
    std::ifstream config("files/config.cfg");

    if (!config.is_open()) {
        std::cerr << "Config file did not open" << std::endl;
        return -1;
    }

    float colCount = 0.0f;
    float rowCount = 0.0f;
    float num_of_mines = 0.0f;

    config >> colCount;
    config >> rowCount;
    config >> num_of_mines;

    sf::RenderWindow window(sf::VideoMode(colCount * 32, (rowCount * 32) + 100), "Minesweeper", sf::Style::Close);
    Welcome_Window welcome_window;
    welcome_window.setText(welcome_window.getWelcome(), (colCount*32)/2,(rowCount*32)/2-150);
    welcome_window.setText(welcome_window.getEnter(), (colCount*32)/2,(rowCount*32)/2-75);
    welcome_window.setText(welcome_window.getUser(), (colCount*32)/2,(rowCount*32)/2-45);

    int letters = 0;
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
                return 1;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter && letters > 0) {
                    window.close();
                }

                if (event.key.code == sf::Keyboard::Backspace && letters > 0) {
                    welcome_window.removeText();
                    welcome_window.setText(welcome_window.getUser(), (colCount*32)/2,(rowCount*32)/2-45);
                    letters--;
                }
            }

            if (event.type == sf::Event::TextEntered && letters < 10) {
                char letter = static_cast<char>(event.text.unicode);
                if (std::isalpha(static_cast<unsigned char>(letter))) {
                    if (letters == 0) {
                        letter = std::toupper(letter);
                    } else {
                        letter = std::tolower(letter);
                    }
                    welcome_window.addText(letter);
                    welcome_window.setText(welcome_window.getUser(), (colCount*32)/2,(rowCount*32)/2-45);
                    letters++;
                }
            }
        }

        window.clear(sf::Color::Blue);
        welcome_window.draw(window);
        window.display();
    }

    sf::RenderWindow Gamewindow(sf::VideoMode(colCount * 32.0f, (rowCount * 32.0f) + 100.0f), "Minesweeper", sf::Style::Close);
    Game_Window game_window;
    game_window.initializeMines(num_of_mines, colCount, rowCount);

    while (Gamewindow.isOpen()) {
        sf::Event gameEvent;
        while(Gamewindow.pollEvent(gameEvent)) {
            if(gameEvent.type == sf::Event::Closed) {
                Gamewindow.close();
                return 1;
            }
        }

        Gamewindow.clear(sf::Color::White);
        game_window.draw(Gamewindow, colCount, rowCount);
        Gamewindow.display();
    }


    return 0;
}