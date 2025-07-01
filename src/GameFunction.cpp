#include <iostream>
#include "GameFunction.hpp"
#include "Entity.hpp"
#include "GameBoard.hpp"

void MoveRight(Entity* entity, Board& board) {
    auto pos = entity->getPosition();
    int newX = pos[0];
    int newY = pos[1] + 1;
    if (newY >= BOARD_SIZE) newY = 0;

    if (board.getEntityType(newX, newY) == EntityType::ITEM) {
        Player* player = dynamic_cast<Player*>(entity);
        if (player) {
			CollectItem(player, board, newX, newY);
		}
    }

    board.setEntity(newX, newY, entity);
    board.setEntity(pos[0], pos[1], nullptr);
    entity->setPosition(newX, newY);
}


void MoveLeft(Entity* entity, Board& board) {
    auto pos = entity->getPosition();
    int newX = pos[0];
    int newY = pos[1] - 1;

    if (newY < 0){
        newY = BOARD_SIZE - 1;
	}

	if  (board.getEntityType(newX, newY) == EntityType::ITEM){
		Player* player = dynamic_cast<Player*>(entity);
		if (player) {
			CollectItem(player, board,newX,newY);
		}
	}

    board.setEntity(newX, newY, entity);
	board.setEntity(pos[0], pos[1], nullptr); // Clear old position
	entity->setPosition(newX, newY);
}


void MoveUp(Entity* entity, Board& board) {
	auto pos = entity->getPosition();
	int newX = pos[0] - 1;
	int newY = pos[1];

	if (newX < 0) {
		newX = BOARD_SIZE - 1;
	}

	if  (board.getEntityType(newX, newY) == EntityType::ITEM){
		Player* player = dynamic_cast<Player*>(entity);
		if (player) {
			CollectItem(player, board,newX,newY);
		}
	}
	

	board.setEntity(newX, newY, entity);
	board.setEntity(pos[0], pos[1], nullptr); // Clear old position
	entity->setPosition(newX, newY);
}

void MoveDown(Entity* entity, Board& board) {
	auto pos = entity->getPosition();
	int newX = pos[0] + 1;
	int newY = pos[1];

	if (newX >= BOARD_SIZE) {
		newX = 0;
	}

	if  (board.getEntityType(newX, newY) == EntityType::ITEM){
		Player* player = dynamic_cast<Player*>(entity);
		if (player) {
			CollectItem(player, board,newX,newY);
		}
	}

	board.setEntity(newX, newY, entity);
	board.setEntity(pos[0], pos[1], nullptr); // Clear old position
	entity->setPosition(newX, newY);
}

void CollectItem(Player* player, Board& board, int x, int y) {
    Entity* entity = board.getEntity(x, y);
    Item* item = dynamic_cast<Item*>(entity);
    if (item) {
        board.setEntity(x, y, nullptr); // Remove from board
        player->addItem(std::unique_ptr<Item>(item));
    }
}

bool IsPlayerNearMob(Player* player, Board& board) {
	auto playerPos = player->getPosition();
	for (int x = playerPos[0] - 1; x <= playerPos[0] + 1; ++x) {
		for (int y = playerPos[1] - 1; y <= playerPos[1] + 1; ++y) {
			if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
				Entity* entity = board.getEntity(x, y);
				if (entity && entity->getType() == EntityType::MOB) {
					return true;
				}
			}
		}
	}
	return false;
}

Mob* getNearMob(Player* player, Board& board) {
	auto playerPos = player->getPosition();
	for (int x = playerPos[0] - 1; x <= playerPos[0] + 1; ++x) {
		for (int y = playerPos[1] - 1; y <= playerPos[1] + 1; ++y) {
			if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
				Entity* entity = board.getEntity(x, y);
				if (entity && entity->getType() == EntityType::MOB) {
					return dynamic_cast<Mob*>(entity);
				}
			}
		}
	}
	return nullptr;
}