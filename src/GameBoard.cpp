#include <iostream>
#include "Actions.cpp"


// Ce fichier va generer le plateau de jeu

// |Const variables|***************************************
const char letter[20] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
	'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T'
};
const int BOARD_SIZE = 20;
const float TILE_SIZE = 32; // Taille de chaque tuile du plateau
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
			for (int j = 0; j < BOARD_SIZE; ++j) {  // Lib�re chaque entit�
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
};


void DisplayLetter() {
	for (int i = 0; i < 20; ++i) {
		std::cout << " " << letter[i] << " ";
	}
	std::cout << std::endl;
}

void DisplayBoard(Board& board) {

	std::cout << "This is the game board" << std::endl;
	std::cout << "------------------------" << std::endl;
	DisplayLetter();

	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			switch (board.getEntityType(i, j)) {
			case EntityType::VOID:
				std::cout << "[ ]"; break;
			case EntityType::PLAYER:
				std::cout << "|P|"; break;
			case EntityType::MOB:
				std::cout << "|M|"; break;
			default:
				std::cout << "[?]"; break;
			}
		}
		std::cout << i << std::endl;
	}
}

void DrawBoard(SDL_Renderer* renderer, const Board& board) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			SDL_Rect cell = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };

			switch (board.getEntityType(i, j)) {
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



