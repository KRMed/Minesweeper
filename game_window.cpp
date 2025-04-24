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
    flag_S.setTexture(textures["flag"]);
    digits_S.setTexture(textures["digits"]);
    debug_S.setTexture(textures["debug"]);
    pause_S.setTexture(textures["pause"]);
    play_S.setTexture(textures["play"]);
    leaderboard_S.setTexture(textures["leaderboard"]);
    hidden_S.setTexture(textures["tile_hidden"]);
    revealed_S.setTexture(textures["tile_revealed"]);
    number_1_S.setTexture(textures["number_1"]);
    number_2_S.setTexture(textures["number_2"]);
    number_3_S.setTexture(textures["number_3"]);
    number_4_S.setTexture(textures["number_4"]);
    number_5_S.setTexture(textures["number_5"]);
    number_6_S.setTexture(textures["number_6"]);
    number_7_S.setTexture(textures["number_7"]);
    number_8_S.setTexture(textures["number_8"]);


    tiles.resize(25*16);
}

void Game_Window::initializeMines(const float minecount, const float width, const float height) {
    lose = false;
    win = false;
    truepause = false;
    pause = false;
    seconds = 0;
    flagNum = minesNum;
    elapsed_before = std::chrono::seconds(0);

    //start time
    start = std::chrono::system_clock::now();

    tiles.resize(width*height);

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

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int current = (i*width) + j;
            tiles[current].neighbors.clear();
            int mine_count = 0;

            //Check 8 tiles around
            for (int vi = -1; vi <= 1; vi++) {
                for (int hi = -1; hi <= 1; hi++) {
                    //if center tile skip
                    if (vi == 0 && hi == 0) {
                        continue;
                    }

                    int current_i = i + vi;
                    int current_j = j + hi;

                    if (current_i >= 0 && current_i < height && current_j >= 0 && current_j < width) {
                        int neighbor_num = current_i * width + current_j;
                        tiles[current].neighbors.push_back(neighbor_num);

                        if (tiles[neighbor_num].hasMine) {
                            mine_count++;
                        }
                    }
                }
            }

            tiles[current].neighbor_mines = mine_count;
        }
    }
}

void Game_Window::draw(sf::RenderWindow& window, const float width, const float height) {
    //draws the mines tiles
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            if (!lose) {
                face_happy_S.setPosition(width/2.0f * 32 - 32, 32 * (height+0.5));
                window.draw(face_happy_S);

            } else {
                face_lose_S.setPosition(width/2.0f * 32 - 32, 32 * (height+0.5));
                window.draw(face_lose_S);
            }

            if (win) {
                face_win_S.setPosition(width/2.0f * 32 - 32, 32 * (height+0.5));
                window.draw(face_win_S);
            }

            if (tiles[i*width + j].isRevealed) {

                revealed_S.setPosition(j * 32.0f, i * 32.0f);
                window.draw(revealed_S);

                if (tiles[i*width + j].hasMine) {
                    mine_S.setPosition(j * 32.0f, i * 32.0f);
                    window.draw(mine_S);
                    lose = true;
                }

                else {
                    if (tiles[i*width + j].neighbor_mines == 1) {
                        number_1_S.setPosition(j * 32.0f, i * 32.0f);
                        window.draw(number_1_S);
                    }
                    if (tiles[i*width + j].neighbor_mines == 2) {
                        number_2_S.setPosition(j * 32.0f, i * 32.0f);
                        window.draw(number_2_S);
                    }
                    if (tiles[i*width + j].neighbor_mines == 3) {
                        number_3_S.setPosition(j * 32.0f, i * 32.0f);
                        window.draw(number_3_S);
                    }
                    if (tiles[i*width + j].neighbor_mines == 4) {
                        number_4_S.setPosition(j * 32.0f, i * 32.0f);
                        window.draw(number_4_S);
                    }
                    if (tiles[i*width + j].neighbor_mines == 5) {
                        number_5_S.setPosition(j * 32.0f, i * 32.0f);
                        window.draw(number_5_S);
                    }
                    if (tiles[i*width + j].neighbor_mines == 6) {
                        number_6_S.setPosition(j * 32.0f, i * 32.0f);
                        window.draw(number_6_S);
                    }
                    if (tiles[i*width + j].neighbor_mines == 7) {
                        number_7_S.setPosition(j * 32.0f, i * 32.0f);
                        window.draw(number_7_S);
                    }
                    if (tiles[i*width + j].neighbor_mines == 8) {
                        number_8_S.setPosition(j * 32.0f, i * 32.0f);
                        window.draw(number_8_S);
                    }
                }
            }

            if (!tiles[i*width + j].isRevealed) {
                hidden_S.setPosition(j * 32.0f, i * 32.0f);
                window.draw(hidden_S);

                if (debug && tiles[i*width + j].hasMine) {
                    mine_S.setPosition(j * 32.0f, i * 32.0f);
                    window.draw(mine_S);
                }

                if (tiles[i*width + j].hasFlag) {
                    flag_S.setPosition(j * 32.0f, i * 32.0f);
                    window.draw(flag_S);
                }
            }
        }
    }

    //Drawing counter for flag

    if (flagNum < 0) {
        digits_S.setTextureRect(sf::IntRect(10*21, 0, 21, 32));
        digits_S.setPosition(12, 32 * (height + 0.5) + 16);
        window.draw(digits_S);
    }

    str_flagNum = std::to_string(std::abs(flagNum));
    while (str_flagNum.length() < 3) {
        str_flagNum = "0" + str_flagNum;
    }

    for (int i=0; i < str_flagNum.size(); i++) {
        const int digit = str_flagNum[i] - '0';

        digits_S.setTextureRect(sf::IntRect(digit * 21, 0, 21, 32));
        digits_S.setPosition(33 + i * 21, 32 * (height +0.5) + 16);

        window.draw(digits_S);
    }


    seconds = 0;
    if (!pause && !truepause) {
        end = std::chrono::system_clock::now();
        auto elapsed = end - start;
        seconds = (elapsed_before + std::chrono::duration_cast<std::chrono::seconds>(elapsed)).count();
    } else {
        seconds = elapsed_before.count();
    }

    int minutes = seconds / 60;
    digits_S.setTextureRect(sf::IntRect((minutes / 10) * 21, 0, 21, 32));
    digits_S.setPosition((width * 32) - 97, 32 * (height + 0.5) + 16);
    window.draw(digits_S);

    digits_S.setTextureRect(sf::IntRect((minutes % 10) * 21, 0, 21, 32));
    digits_S.setPosition((width * 32) - 76, 32 * (height + 0.5) + 16);
    window.draw(digits_S);

    // Seconds (start at (width * 32) - 54)
    digits_S.setTextureRect(sf::IntRect((seconds / 10) * 21, 0, 21, 32));
    digits_S.setPosition((width * 32) - 54, 32 * (height + 0.5) + 16);
    window.draw(digits_S);

    digits_S.setTextureRect(sf::IntRect((seconds % 10) * 21, 0, 21, 32));
    digits_S.setPosition((width * 32) - 33, 32 * (height + 0.5) + 16);
    window.draw(digits_S);


    debug_S.setPosition(width * 32 - 304, (height + 0.5) * 32);
    window.draw(debug_S);

    if (pause) {
        play_S.setPosition(width * 32 - 240, (height + 0.5) * 32);
        window.draw(play_S);
    } else {
        pause_S.setPosition(width * 32 - 240, (height + 0.5) * 32);
        window.draw(pause_S);
    }

    leaderboard_S.setPosition(width * 32 - 170, (height + 0.5) * 32);
    window.draw(leaderboard_S);
    //STILL NEED TO ADD TIMERS AND COUNTER
}

void Game_Window::updateTiles(int x, int y, int width, int height) {
    if (y <= height * 32) {
        if (tiles[y/32 * width + x/32].hasFlag || tiles[y/32 * width + x/32].isRevealed) {
            return;
        }

        if (tiles[y/32 * width + x/32].hasMine) {
            lose = true;
            end = std::chrono::system_clock::now();
            elapsed_before += std::chrono::duration_cast<std::chrono::seconds>(end - start);
            truepause = true;
            tiles[y/32 * width + x/32].isRevealed = true;
        }

        if (tiles[y/32 * width + x/32].neighbor_mines == 0) {
            revealNeighbors(y/32, x/32, width, height);
        }
        else {
            tiles[y/32 * width + x/32].isRevealed = true;
        }
    }
}

void Game_Window::updatePause(int x, int y) {
    if (truepause) {
        return;
    }
    sf::FloatRect bounds = pause_S.getGlobalBounds();
    if (x >= bounds.left && x < bounds.left + bounds.width && y >= bounds.top && y < bounds.top + bounds.height) {

        if (!pause) {
            end = std::chrono::system_clock::now();
            elapsed_before += std::chrono::duration_cast<std::chrono::seconds>(end - start);
        } else {
            start = std::chrono::system_clock::now();
        }
        pause = !pause;
    }
}

void Game_Window::reset(int x, int y, int width, int height, int mines) {
    sf::FloatRect bounds = face_happy_S.getGlobalBounds();
    if (x >= bounds.left && x < bounds.left + bounds.width && y >= bounds.top && y < bounds.top + bounds.height) {
        initializeMines(mines, width, height);
    }
}

void Game_Window::updateFlag(int x, int y, int width, int height) {
    if (y <= height * 32) {
        tiles[std::floor(y/32) * width + std::floor(x/32)].hasFlag = !tiles[std::floor(y/32) * width + std::floor(x/32)].hasFlag;

        if (tiles[std::floor(y/32) * width + std::floor(x/32)].hasFlag) {
            flagNum--;
        } else {
            flagNum++;
        }
    }
}

bool Game_Window::getPause() const {
    return pause;
}

void Game_Window::updateDebug(int x, int y) {
    sf::FloatRect bounds = debug_S.getGlobalBounds();
    if (x >= bounds.left && x < bounds.left + bounds.width && y >= bounds.top && y < bounds.top + bounds.height) {
        debug = !debug;
    }
}

void Game_Window::revealNeighbors(int x, int y, int width, int height) {
    int index = x * width + y;

    if (x < 0 || x >= height || y < 0 || y >= width || tiles[index].isRevealed || tiles[index].hasFlag || tiles[index].hasMine) {
        return;
    }

    tiles[index].isRevealed = true;

    if (tiles[index].neighbor_mines == 0) {
        for (int vi = -1; vi <= 1; vi++) {
            for (int hi = -1; hi <= 1; hi++) {
                if (vi == 0 && hi == 0) {
                    continue;
                }

                revealNeighbors(x + vi, hi + y, width, height);
            }
        }
    }
}

bool Game_Window::winCheck() {
    for (const auto & tile : tiles) {
        if (!tile.isRevealed && !tile.hasMine) {
            return false;
        }
    }

    end = std::chrono::system_clock::now();
    elapsed_before += std::chrono::duration_cast<std::chrono::seconds>(end - start);

    win = true;
    truepause = true;
    return (win);
}

bool Game_Window::getTruePause() const {
    return truepause;
}

