#include <iostream>
#include <random>
#include <vector>
#include "EntitySpawn.hpp"

std::vector<int> generateRandomPosition(int boardSize) {
    std::random_device rd; 
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, boardSize - 1);

    int x = distr(eng);
    int y = distr(eng);
    return {x, y};
}