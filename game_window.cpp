#include "game_window.h"

Game_Window::Game_Window() {
    //Store all textures within data structure to not fall out of scope
    sf::Texture debug;
    if (debug.loadFromFile("files/images/debug.png")) {
        textures["debug"] = debug;
    }

    sf::Texture digits;
    if (digits.loadFromFile("files/images/digits.png")) {
        textures["digits"] = digits;
    }

    sf::Texture face_happy;
    if (face_happy.loadFromFile("files/images/face_happy.png")) {
        textures["face_happy"] = face_happy;
    }

    sf::Texture face_lose;
    if (face_lose.loadFromFile("files/images/face_lose.png")) {
        textures["face_lose"] = face_lose;
    }

    sf::Texture face_win;
    if (face_win.loadFromFile("files/images/face_win.png")) {
        textures["face_win"] = face_win;
    }

    sf::Texture flag;
    if (flag.loadFromFile("files/images/flag.png")) {
        textures["flag"] = flag;
    }

    sf::Texture leaderboard;
    if (leaderboard.loadFromFile("files/images/leaderboard.png")) {
        textures["leaderboard"] = leaderboard;
    }

    sf::Texture mine;
    if (mine.loadFromFile("files/images/mine.png")) {
        textures["mine"] = mine;
    }

    sf::Texture number_1;
    if (number_1.loadFromFile("files/images/number_1.png")) {
        textures["number_1"] = number_1;
    }

    sf::Texture number_2;
    if (number_2.loadFromFile("files/images/number_2.png")) {
        textures["number_2"] = number_2;
    }

    sf::Texture number_3;
    if (number_3.loadFromFile("files/images/number_3.png")) {
        textures["number_3"] = number_3;
    }

    sf::Texture number_4;
    if (number_4.loadFromFile("files/images/number_4.png")) {
        textures["number_4"] = number_4;
    }

    sf::Texture number_5;
    if (number_5.loadFromFile("files/images/number_5.png")) {
        textures["number_5"] = number_5;
    }

    sf::Texture number_6;
    if (number_6.loadFromFile("files/images/number_6.png")) {
        textures["number_6"] = number_6;
    }

    sf::Texture number_7;
    if (number_7.loadFromFile("files/images/number_7.png")) {
        textures["number_7"] = number_7;
    }

    sf::Texture number_8;
    if (number_8.loadFromFile("files/images/number_8.png")) {
        textures["number_8"] = number_8;
    }

    sf::Texture pause;
    if (pause.loadFromFile("files/images/pause.png")) {
        textures["pause"] = pause;
    }

    sf::Texture play;
    if (play.loadFromFile("files/images/play.png")) {
        textures["play"] = play;
    }

    sf::Texture tile_hidden;
    if (tile_hidden.loadFromFile("files/images/tile_hidden.png")) {
        textures["tile_hidden"] = tile_hidden;
    }

    sf::Texture tile_revealed;
    if (tile_revealed.loadFromFile("files/images/tile_revealed.png")) {
        textures["tile_revealed"] = tile_revealed;
    }

    mine_S.setTexture(textures["mine"]);
    face_happy_S.setTexture(textures["face_happy"]);
    face_win_S.setTexture(textures["face_win"]);
    face_lose_S.setTexture(textures["face_lose"]);
    digits_S.setTexture(textures["digits"]);
    debug_S.setTexture(textures["debug"]);
    pause_S.setTexture(textures["pause"]);
    play_S.setTexture(textures["play"]);
    leaderboard_S.setTexture(textures["leaderboard"]);
    hidden_S.setTexture(textures["tile_hidden"]);
    revealed_S.setTexture(textures["tile_revealed"]);

    tiles.resize(25*16);
}

void Game_Window::initializeMines(const float minecount, const float width, const float height) {
    for (auto & tile : tiles) {
        tile.hasMine = false;
        tile.isRevealed = false;
        tile.hasFlag = false;
        tile.neighbor_mines = 0;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, width*height - 1);
    int placed = 0;

    while (placed < minecount) {
        const int random = distrib(gen);
        if (!tiles[random].hasMine) {
            tiles[random].hasMine = true;
            placed++;
        }
    }
}

void Game_Window::draw(sf::RenderWindow& window, const float width, const float height) {
    //draws the mines tiles
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (tiles[i*width + j].isRevealed) {
                revealed_S.setPosition(j * 32.0f, i * 32.0f);
                window.draw(revealed_S);
            } else {
                hidden_S.setPosition(j * 32.0f, i * 32.0f);
                window.draw(hidden_S);
            }
        }
    }

    face_happy_S.setPosition(width/2.0f * 32 - 32, 32 * (height+0.5));
    window.draw(face_happy_S);

    debug_S.setPosition(width * 32 - 304, (height + 0.5) * 32);
    window.draw(debug_S);

    pause_S.setPosition(width * 32 - 240, (height + 0.5) * 32);
    window.draw(pause_S);

    leaderboard_S.setPosition(width * 32 - 170, (height + 0.5) * 32);
    window.draw(leaderboard_S);

    //STILL NEED TO ADD TIMERS AND COUNTER
}

