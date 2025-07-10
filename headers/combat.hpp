#include <iostream>
#include "board.hpp"

enum class GameState {
    FREE, // the player is free to move
    COMBAT, // Combat mode
    TITLE // Titlescreen
    //TODO maybe a pause mode
};

void StartFight(Board& board);