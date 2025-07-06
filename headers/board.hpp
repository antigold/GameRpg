#pragma once
#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "game_function.hpp"

const int kBoardSize = 19;
const int kTilesize = 32;

class Board {
private:
    Entity* board[kBoardSize][kBoardSize];
public:
    Board();
    ~Board();
    void setEntity(Position pos, Entity* entity);
    void DeleteEntity(Position pos);
    Entity* getEntity(Position pos) const;
    EntityType getEntityType(Position pos) const;
    void DrawBoard(SDL_Renderer* renderer,SDL_Texture* PlayerTexture,SDL_Texture* SwordTexture,SDL_Texture* BowTexture, SDL_Texture* MobTexture,SDL_Texture* HealTexture) const;
    void DrawInfo(SDL_Renderer* renderer, Player* player) const;
    void renderPlayerInfo(SDL_Renderer* renderer, TTF_Font* font, Player* player,Board& board);
    void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color);
};
