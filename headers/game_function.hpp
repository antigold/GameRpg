#pragma once
#include "classes.hpp"

#ifndef GAMEFUNCTION_HPP
#define GAMEFUNCTION_HPP

class Board;


void HealPlayer(std::shared_ptr<Player> player,double amount);
void HealPlayerOnItem(std::shared_ptr<Player> player,Board& board,Position pos);
void MoveRight(Entity* entity, Board& board);
void MoveLeft(Entity* entity, Board& board);
void MoveUp(Entity* entity, Board& board);
void MoveDown(Entity* entity, Board& board);
void CollectItem(std::shared_ptr<Player> player, Board& board,Position pos);
bool IsPlayerNearMob(Player* player, Board& board);
Mob* getNearMob(Player* player,Board& board);

#endif