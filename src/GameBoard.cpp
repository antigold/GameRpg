#include "GameBoard.hpp"
#include "Entity.hpp"
#include <iostream> 

Board::Board() {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = nullptr;
}

Board::~Board() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] != nullptr && board[i][j]->getType() != EntityType::PLAYER) {
                delete board[i][j];
            }
            board[i][j] = nullptr;
        }
    }
}


void Board::setEntity(int x, int y, Entity* entity) {
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        board[x][y] = entity;
        if (entity != nullptr) {
            entity->setPosition(x, y);
        }
    } else {
        std::cerr << "Position invalide (" << x << ", " << y << ")" << std::endl;
    }
}

void Board::DeleteEntity(int x, int y) {
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        if (board[x][y] != nullptr && board[x][y]->getType() != EntityType::PLAYER) {
            delete board[x][y]; // supprimer uniquement si ce n’est pas un joueur
        }
        board[x][y] = nullptr;
    }
}


EntityType Board::getEntityType(int x, int y) const {
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        if (board[x][y] == nullptr) {
            return EntityType::VOID;
        }
        return board[x][y]->getType();
    }
    return EntityType::VOID;
}

void Board::DrawBoard(SDL_Renderer* renderer) const {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            SDL_Rect cell = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };

            switch (getEntityType(i, j)) {
            case EntityType::VOID:
                SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
                break;
            case EntityType::PLAYER:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                break;
            case EntityType::MOB:
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                break;
            default:
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                break;
            }

            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

void Board::DrawInfo(SDL_Renderer* renderer, Player* player) const {
    if (!player) return;

    SDL_Rect infoBox = {
        BOARD_SIZE * TILE_SIZE, 0,
        900 - BOARD_SIZE * TILE_SIZE, 608
    };

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &infoBox);
}

void Board::renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (!surface) return;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect destRect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void Board::renderPlayerInfo(SDL_Renderer* renderer, TTF_Font* font, Player* player) {
    if (!player) return;

    SDL_Color white = {255, 255, 255, 255};
    int x = BOARD_SIZE * TILE_SIZE + 10;
    int y = 10;

    auto pos = player->getPosition();
    std::ostringstream oss;

    oss << "Position: (" << pos[0] << ", " << pos[1] << ")";
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();

    oss << "HP: " << player->getHp();
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();

    oss << "Attack: " << player->getAttack();
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();

    oss << "Defense: " << player->getDefense();
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();

    oss << "XP: " << player->getXp() << " | Level: " << player->getLevel();
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();

    renderText(renderer, font, "Inventory:", x, y, white);
    y += 30;

    const auto& inventory = player->getInventory();
    if (inventory.empty()) {
        renderText(renderer, font, " - (Empty)", x + 10, y, white);
    } else {
        for (const auto& item : inventory) {
            renderText(renderer, font, " - " + item->getName(), x + 10, y, white);
            y += 25;
        }
    }
}

