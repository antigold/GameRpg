#define SDL_MAIN_HANDLED
#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Entity.cpp"


// Ce fichier va generer le plateau de jeu

// |Const variables|***************************************
const int BOARD_SIZE = 19;
const int TILE_SIZE = 32; // Taille de chaque tuile du plateau
//********************************************************

class Board {
private:
	Entity* board[BOARD_SIZE][BOARD_SIZE];
public:
	Board() {
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				board[i][j] = nullptr;
			}
		}
	}
	~Board() {
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {  // Libère du manure
				board[i][j] = nullptr; // Bonne pratique
				delete board[i][j];
			}
		}
	}

	void setEntity(int x, int y, Entity* entity) {
		if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
			board[x][y] = entity;
			if (entity != nullptr) {
				entity->setPosition(x, y);  // Met à jour la position de l'entit�
			}
		} else {
			delete entity;
		}
	}

	void DeleteEntity(int x, int y) {
		if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
			board[x][y] = nullptr;  // Remplace par une entit� de type Void
		}
	}

	EntityType getEntityType(int x, int y) const {
		if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
			if (board[x][y] == nullptr) {
				return EntityType::VOID;
			}
			return board[x][y]->getType();
		}
		return EntityType::VOID;
	};

	void DrawBoard(SDL_Renderer* renderer) const {
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				SDL_Rect cell = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };

				switch (getEntityType(i, j)) {
				case EntityType::VOID:
					SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255); break;
				case EntityType::PLAYER:
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break;
				case EntityType::MOB:
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); break;
				default:
					SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); break;
				}

				SDL_RenderFillRect(renderer, &cell);

				// Dessiner le contour de la cellule
				SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
				SDL_RenderDrawRect(renderer, &cell);
			}
		}
	}

	void DrawInfo(SDL_Renderer* renderer, Player* player) const {
		if (player == nullptr) return;

		SDL_Rect infoBox = {
			BOARD_SIZE * TILE_SIZE, // x = 608
			0,                      // y = 0
			900 - BOARD_SIZE * TILE_SIZE, // largeur = 900 - 608 = 292
			608                    // hauteur = hauteur de la fenêtre
		};

		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // gris foncé
		SDL_RenderFillRect(renderer, &infoBox);
	}

	void renderPlayerInfo(SDL_Renderer* renderer, TTF_Font* font, Player* player) {
    	if (!player) return;
    	SDL_Color white = {255, 255, 255, 255};
    	int x = BOARD_SIZE * TILE_SIZE + 10; // 608 + 10 = 618, marge à droite du plateau
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


	void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color) {
    	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    	if (!surface) return;

    	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    	SDL_Rect destRect = { x, y, surface->w, surface->h };
    	SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    	SDL_FreeSurface(surface);
    	SDL_DestroyTexture(texture);
	}
};