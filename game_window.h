#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>

class Game_Window {
    int minesNum = 50;
    std::map<std::string, sf::Texture> textures;
    sf::Sprite mine_S;
    sf::Sprite face_happy_S;
    sf::Sprite face_win_S;
    sf::Sprite face_lose_S;
    sf::Sprite digits_S;
    sf::Sprite debug_S;
    sf::Sprite pause_S;
    sf::Sprite play_S;
    sf::Sprite leaderboard_S;
    sf::Sprite hidden_S;
    sf::Sprite revealed_S;

    struct Tile {
        bool hasMine = false;
        bool isRevealed = false;
        bool hasFlag = false;
        int neighbor_mines = 0;
        std::vector<Tile*> neighbors;
    };

    std::vector<Tile> tiles;

public:
    //Constructor
    Game_Window();

    // Functions to affect the tiles
    void reveal();
    void initializeMines(float minecount, float width, float height); //Will also be used to reset all the mines
    void place_flag();
    void check_win();
    void draw(sf::RenderWindow& window, float width, float height);

};


#endif
