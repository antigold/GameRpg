#pragma once
#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <unordered_map>
#include <memory>
#include "player.hpp"
#include "mob.hpp"
#include "gameStates.hpp"

class Entity;

const int kBoardSize = 19;
const int kTilesize = 32;

/**
 * @class Board
 * @brief this class contains the board and all the entities of the game
 * @param entities Contains all the entities of the board
 */
class Board {
private:
    std::unordered_map<Position,std::shared_ptr<Entity>> entities;
public:

    Board();
    ~Board();

    void setEntity(Position pos, std::shared_ptr<Entity> entity);
    void DeleteEntity(Position pos);
    std::unordered_map<Position,std::shared_ptr<Entity>> getEntities() const;
    bool isWalkable(Position pos) const;

    std::shared_ptr<Entity> getEntityAt(Position pos) const;

    EntityType getEntityType(Position pos) const;

    void DrawBoard(SDL_Renderer* renderer,
                   SDL_Texture* PlayerTexture,
                   SDL_Texture* SwordTexture,
                   SDL_Texture* BowTexture, 
                   SDL_Texture* MobTexture,
                   SDL_Texture* HealTexture) const;

    void DrawInfo(SDL_Renderer* renderer, Player* player) const;
    void renderPlayerInfo(SDL_Renderer* renderer, TTF_Font* font, Player* player,Board& board);
    void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color);
    void drawTitleScreen(SDL_Renderer* renderer, TTF_Font* font);
};

Direction getRandomDirection();
int dx(Direction dir);
int dy(Direction dir);
