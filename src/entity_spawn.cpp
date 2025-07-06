#include <iostream>
#include <random>
#include "entity_spawn.hpp"

Position generateRandomPosition(int boardSize, Board& board) { //this is more optimized than the previous version
    std::random_device rd; 
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, boardSize - 1);

    int x = distr(eng);
    int y = distr(eng);

    if (board.getEntityType(Position(x,y)) == EntityType::PLAYER) {
        // Use a loop instead of recursion to avoid ambiguity and stack overflow
        do {
            x = distr(eng);
            y = distr(eng);
        } while (board.getEntityType(Position(x,y)) == EntityType::PLAYER);
    }
    return Position(x,y);
}

Position generateRandomItemPosition(int boatdsize, Board& board) {
    std::random_device rd; 
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, boatdsize - 1);
    int x = distr(eng);
    int y = distr(eng);
    if (board.getEntityType(Position(x,y)) != EntityType::VOID) {
        do {
            x = distr(eng);
            y = distr(eng);
        } while (board.getEntityType(Position(x,y)) != EntityType::VOID);
    }
    
    return Position(x,y);
}