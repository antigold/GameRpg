#pragma once
#include <iostream>
#include "board.hpp"
#include "mob.hpp"
#include "player.hpp"
#include "stats.hpp"
#include "input.h"

class Player;
class Mob;

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

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color);

void displayCombat(SDL_Renderer* renderer, TTF_Font* font,
                   SDL_Texture* playerTexture, SDL_Texture* mobTexture,
                   std::shared_ptr<Player> player, std::shared_ptr<Mob> mob,Turn currentTurn,
                    int selectedIndex);

void DisplayRect(SDL_Renderer* renderer,int x,int y,const std::vector<std::string>& options);

void StartFight(Board& board,std::shared_ptr<Player> player, std::shared_ptr<Mob> mob
                ,SDL_Renderer* renderer, TTF_Font* font,SDL_Texture* Playertexture,SDL_Texture* MobTexture);