#pragma once

#ifndef GAMEFUNCTION_HPP
#define GAMEFUNCTION_HPP

#include "classes.hpp"

class Board;

void MoveRight(Entity* entity, Board& board);
void MoveLeft(Entity* entity, Board& board);
void MoveUp(Entity* entity, Board& board);
void MoveDown(Entity* entity, Board& board);
void CollectItem(Player* player, Board& board,Position pos);
bool IsPlayerNearMob(Player* player, Board& board);
Mob* getNearMob(Player* player,Board& board);

#endif