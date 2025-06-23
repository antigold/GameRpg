#include <iostream>
#include <random>
#include <vector>
#include "EntitySpawn.hpp"

std::vector<int> generateRandomPosition(int boardSize, Player* player) {
    std::random_device rd; 
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, boardSize - 1);

    int x = distr(eng);
    int y = distr(eng);

    if (x == player->getPosition()[0] && y == player->getPosition()[1]) {
        return {0,0};
    }
    return {x, y};
}

std::vector<int> generateRandomItemPosition(int boatdsize, Player* player) {
    std::random_device rd; 
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, boatdsize - 1);
    int x = distr(eng);
    int y = distr(eng);
    if (x == player->getPosition()[0] && y == player->getPosition()[1]) {
        return {18, 18};
    }
    return {x, y};
}