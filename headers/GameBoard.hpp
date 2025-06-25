#pragma once
#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Entity.hpp"

const int BOARD_SIZE = 19;
const int TILE_SIZE = 32;

class Board {
private:
    Entity* board[BOARD_SIZE][BOARD_SIZE];
public:
    Board();
    ~Board();
    void setEntity(int x, int y, Entity* entity);
    void DeleteEntity(int x, int y);
    Entity* getEntity(int x, int y) const;
    EntityType getEntityType(int x, int y) const;
    void DrawBoard(SDL_Renderer* renderer) const;
    void DrawInfo(SDL_Renderer* renderer, Player* player) const;
    void renderPlayerInfo(SDL_Renderer* renderer, TTF_Font* font, Player* player);
    void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color);
};