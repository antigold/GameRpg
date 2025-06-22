#pragma once

#ifndef GAMEFUNCTION_HPP
#define GAMEFUNCTION_HPP

#include "Gameboard.hpp"

void MoveRight(Entity* entity, Board& board);
void MoveLeft(Entity* entity, Board& board);
void MoveUp(Entity* entity, Board& board);
void MoveDown(Entity* entity, Board& board);

#endif