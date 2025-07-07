#include "board.hpp"
#include <iostream> 

//|==========================|Class Board|===============================================|

Board::Board() {
    for (int i = 0; i < kBoardSize; ++i)
        for (int j = 0; j < kBoardSize; ++j)
            board[i][j] = nullptr;
}

Board::~Board() {
    for (int i = 0; i < kBoardSize; ++i) {
        for (int j = 0; j < kBoardSize; ++j) {
            if (board[i][j] != nullptr && board[i][j]->getType() != EntityType::PLAYER) {
                delete board[i][j];
            }
            board[i][j] = nullptr;
        }
    }
}

void Board::setEntity(Position pos, Entity* entity) {

    int x = pos.getX();
    int y = pos.getY();

    if (x >= 0 && x < kBoardSize && y >= 0 && y < kBoardSize) {
        board[x][y] = entity;
        if (entity != nullptr) {
            entity->setPosition(Position(x,y));
        }
    } else {
        std::cerr << "Position invalide (" << x << ", " << y << ")" << std::endl;
    }
}

Entity* Board::getEntity(Position pos) const {

    int x = pos.getX();
    int y = pos.getY();

    if (x >= 0 && x < kBoardSize && y >= 0 && y < kBoardSize) {
        return board[x][y];
    }
    return nullptr; // retourne nullptr si la position est invalide
}

void Board::DeleteEntity(Position pos) {

    int x = pos.getX();
    int y = pos.getY();

    if (x >= 0 && x < kBoardSize && y >= 0 && y < kBoardSize) {
        if (board[x][y] != nullptr && board[x][y]->getType() != EntityType::PLAYER) {
            delete board[x][y]; // supprimer uniquement si ce n’est pas un joueur
        }
        board[x][y] = nullptr;
    }
}


EntityType Board::getEntityType(Position pos) const {

    int x = pos.getX();
    int y = pos.getY();

    if (x >= 0 && x < kBoardSize && y >= 0 && y < kBoardSize) {
        if (board[x][y] == nullptr) {
            return EntityType::VOID;
        }
        return board[x][y]->getType();
    }
    return EntityType::VOID;
}

void Board::DrawBoard(SDL_Renderer* renderer,SDL_Texture* PlayerTexture,SDL_Texture* SwordTexture,SDL_Texture* BowTexture, SDL_Texture* MobTexture,SDL_Texture* HealTexture) const {
    for (int i = 0; i < kBoardSize; ++i) {
        for (int j = 0; j < kBoardSize; ++j) {
            SDL_Rect cell = { j * kTilesize, i * kTilesize, kTilesize, kTilesize };

            auto pos = Position(i,j); 

            Entity* entity = getEntity(pos);

            if (entity && getEntityType(pos) == EntityType::ITEM) {
                if (auto* sword = dynamic_cast<Sword*>(entity)) {
                    if (!SwordTexture) {
                        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
                        SDL_RenderFillRect(renderer, &cell);
                    }
                    SDL_RenderCopy(renderer, SwordTexture, nullptr, &cell);
                    sword = nullptr;
                    
                }
                else if (auto* bow = dynamic_cast<Bow*>(entity)) {
                    if (!BowTexture) {
                        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
                        SDL_RenderFillRect(renderer, &cell);
                    }
                    SDL_RenderCopy(renderer, BowTexture, nullptr, &cell);
                    bow = nullptr;
                }
                else if (auto* heal = dynamic_cast<Heal*>(entity)) {
                    if (!HealTexture) {
                        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
                        SDL_RenderFillRect(renderer, &cell);
                    }
                    SDL_RenderCopy(renderer, HealTexture, nullptr, &cell);
                    heal = nullptr;
                }
                else {
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // couleur par défaut pour les items
                }
                continue;
            }

            switch (getEntityType(pos)) {
            case EntityType::PLAYER:
                if (PlayerTexture) {
                    SDL_RenderCopy(renderer, PlayerTexture, nullptr, &cell);
                } else {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // fallback
                    SDL_RenderFillRect(renderer, &cell);
                }
                continue; // éviter de remplir deux fois la case

            case EntityType::MOB:
                if (MobTexture) {
                    SDL_RenderCopy(renderer, MobTexture, nullptr, &cell);
                } else {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                    SDL_RenderFillRect(renderer, &cell);
                }
                continue;
            default:
                SDL_SetRenderDrawColor(renderer, 255, 255, 233, 0); // couleur pour les cases vides
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

    const int boardPixelsize = kBoardSize * kTilesize;

    SDL_Rect infoBox = {
        boardPixelsize, 0,
        900 - boardPixelsize, 608
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

void Board::renderPlayerInfo(SDL_Renderer* renderer, TTF_Font* font, Player* player, Board& board) {
    if (!player) return;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    int x = kBoardSize * kTilesize + 10;
    int y = 10;

    auto pos = player->getPosition();
    std::ostringstream oss;

    oss << "Position: (" << pos.getX() << ", " << pos.getY() << ")";
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();

    oss << "HP: " << player->getStats().getHp();
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();

    oss << "Attack: " << player->getStats().getAttack();
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();

    oss << "Defense: " << player->getStats().getDefense();
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();

    oss << "XP: " << player->getStats().getXp() << " | Level: " << player->getStats().getLevel();
    renderText(renderer, font, oss.str(), x, y, white);
    y += 30; oss.str(""); oss.clear();
    
    renderText(renderer, font, "near Mob:", x , y, white);
    if (IsPlayerNearMob(player,board)) {
        auto mob = getNearMob(player,board);
        oss << " - " << mob->getMobName() << " (HP: " << mob->getStats().getHp() << ")";
        renderText(renderer, font, oss.str(), x + 100, y, red);
    } else {
        renderText(renderer, font, " - None", x + 100, y, white);
    }
    y += 50; oss.str(""); oss.clear();

    renderText(renderer, font, "Inventory:", x, y, white);
    y += 30;

    auto& inventory = player->getInventory();
    const auto& items = inventory.getItems();

    if (items.empty()) {
        renderText(renderer, font, " - (Empty)", x + 10, y, white);
    } else {
        for (const auto& item : items) {
            renderText(renderer, font, " - " + item->getName(), x + 10, y, white);
            y += 25;
        }
    }

}

