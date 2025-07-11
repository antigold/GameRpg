#include <iostream>
#include "board.hpp"
#include "input.h"

enum class GameState {
    FREE, // the player is free to move
    COMBAT, // Combat mode
    TITLE // Titlescreen
    //TODO maybe a pause mode
};

enum class Turn{
    PLAYER,
    MOB
};

void StartFight(Board& board,std::shared_ptr<Player> player, std::shared_ptr<Mob> mob);