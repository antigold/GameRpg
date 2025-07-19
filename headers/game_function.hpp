#pragma once
#include "classes.hpp"
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include "player.hpp"
#include "mob.hpp"
#include "entity.hpp"
#include "board.hpp"

#ifndef GAMEFUNCTION_HPP
#define GAMEFUNCTION_HPP

class Board;
class Player;
class Mob;


void HealPlayer(std::shared_ptr<Player> player,int amount);
void HealPlayerOnItem(std::shared_ptr<Player> player,Board& board,Position pos);
void MoveRight(Entity* entity, Board& board,
               SDL_Renderer* renderer,
               TTF_Font* font,
               SDL_Texture* playerTexture,
               SDL_Texture* mobTexture);
void MoveLeft(Entity* entity, Board& board,
               SDL_Renderer* renderer,
               TTF_Font* font,
               SDL_Texture* playerTexture,
               SDL_Texture* mobTexture);
void MoveUp(Entity* entity, Board& board,
               SDL_Renderer* renderer,
               TTF_Font* font,
               SDL_Texture* playerTexture,
               SDL_Texture* mobTexture);
void MoveDown(Entity* entity, Board& board,
               SDL_Renderer* renderer,
               TTF_Font* font,
               SDL_Texture* playerTexture,
               SDL_Texture* mobTexture);
               
void CollectItem(std::shared_ptr<Player> player, Board& board,Position pos);
bool IsPlayerNearMob(Player* player, Board& board);
Mob* getNearMob(Player* player,Board& board);
bool isMobAt(Position pos,Board& board);

#endif