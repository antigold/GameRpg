#pragma once

#ifndef GAMEFUNCTION_HPP
#define GAMEFUNCTION_HPP

#include "Entity.hpp"

class Board;

void MoveRight(Player* player, Board& board);
void MoveLeft(Player* player, Board& board);
void MoveUp(Player* player, Board& board);
void MoveDown(Player* player, Board& board);
void CollectItem(Player* player, Board& board,int x, int y);
bool IsPlayerNearMob(Player* player,Board& board);
Mob* getNearMob(Player* player,Board& board);

#endif