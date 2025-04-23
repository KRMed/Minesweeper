#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include <map>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>

class Game_Window {
    int minesNum = 50;
    std::map<std::string, sf::Texture> textures;
    sf::Sprite mine_S;
    sf::Sprite face_happy_S;
    sf::Sprite face_win_S;
    sf::Sprite face_lose_S;
    sf::Sprite flag_S;
    sf::Sprite digits_S;
    sf::Sprite debug_S;
    sf::Sprite pause_S;
    sf::Sprite play_S;
    sf::Sprite leaderboard_S;
    sf::Sprite hidden_S;
    sf::Sprite revealed_S;
    sf::Sprite number_1_S;
    sf::Sprite number_2_S;
    sf::Sprite number_3_S;
    sf::Sprite number_4_S;
    sf::Sprite number_5_S;
    sf::Sprite number_6_S;
    sf::Sprite number_7_S;
    sf::Sprite number_8_S;
    bool truepause = false;
    bool pause = false;
    bool lose = false;
    bool win = false;
    bool debug = false;

    struct Tile {
        bool hasMine = false;
        bool isRevealed = false;
        bool hasFlag = false;
        int neighbor_mines = 0;
        std::vector<int> neighbors;
    };

    std::vector<Tile> tiles;

public:
    //Constructor
    Game_Window();

    // Functions to affect the tiles
    void initializeMines(float minecount, float width, float height); //Will also be used to reset all the mines
    void draw(sf::RenderWindow& window, float width, float height);
    void updateTiles(int x, int y, int width, int height);
    void updateFlag(int x, int y, int width, int height);
    void updatePause(int x, int y);
    bool getPause() const;
    void reset(int x, int y, int width, int height, int mines);
    void updateDebug(int x, int y);
    void revealNeighbors(int x, int y, int width, int height);
    bool winCheck();
    bool getTruePause() const;
};


#endif
