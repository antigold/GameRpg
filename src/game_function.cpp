#include <iostream>
#include "game_function.hpp"
#include "classes.hpp"
#include "board.hpp"

void HealPlayer(Player* player, double amount) {
	if (amount < 0) {
		return;
	}
	player->setHp(player->getHp() + amount);
}

void HealPlayerOnItem(Player* player, Board& board, Position pos) {
	Entity* entity = board.getEntity(Position(pos.getX(),pos.getY()));
	Heal* healItem = dynamic_cast<Heal*>(entity);
	if (healItem) {
		HealPlayer(player, healItem->getHealAmount());
	}
}

void MoveRight(Entity* entity, Board& board) {
    Player* player = dynamic_cast<Player*>(entity);
    if (!player) return;

    auto pos = player->getPosition();
    int newX = pos.getX();
    int newY = pos.getY() + 1;
    if (newY >= kBoardSize) newY = 0;

	Entity* target = board.getEntity(Position(newX,newY));
	if (auto* heal = dynamic_cast<Heal*>(target)) {
    	HealPlayerOnItem(player, board,Position(newX,newY));
    	delete heal;
	} else if (board.getEntityType(Position(newX,newY)) == EntityType::ITEM) {
    	CollectItem(player, board,Position(newX,newY));
	}

    board.setEntity(Position(newX,newY), player);
    board.setEntity(Position(pos.getX(),pos.getY()), nullptr);
    player->setPosition(newX, newY);
}


void MoveLeft(Entity* entity, Board& board) {
	Player* player = dynamic_cast<Player*>(entity);
    if (!player) return;
    auto pos = player->getPosition();
    int newX = pos.getX();
    int newY = pos.getY() - 1;

    if (newY < 0){
        newY = kBoardSize - 1;
	}

	Entity* target = board.getEntity(Position(newX,newY));
	if (auto* heal = dynamic_cast<Heal*>(target)) {
    	HealPlayerOnItem(player, board,Position(newX,newY));
    	delete heal;
	} else if (board.getEntityType(Position(newX,newY)) == EntityType::ITEM) {
    	CollectItem(player, board,Position(newX,newY));
	}

    board.setEntity(Position(newX,newY), player);
	board.setEntity(Position(pos.getX(),pos.getY()), nullptr); // Clear old position
	player->setPosition(newX, newY);
}


void MoveUp(Entity* entity, Board& board) {
	Player* player = dynamic_cast<Player*>(entity);
    if (!player) return;
	auto pos = player->getPosition();
	int newX = pos.getX() - 1;
	int newY = pos.getY();

	if (newX < 0) {
		newX = kBoardSize - 1;
	}

	Entity* target = board.getEntity(Position(newX,newY));
	if (auto* heal = dynamic_cast<Heal*>(target)) {
    	HealPlayerOnItem(player, board,Position(newX,newY));
    	delete heal;
	} else if (board.getEntityType(Position(newX,newY)) == EntityType::ITEM) {
    	CollectItem(player, board,Position(newX,newY));
	}
	
	board.setEntity(Position(newX,newY), player);
	board.setEntity(Position(pos.getX(),pos.getY()), nullptr); // Clear old position
	player->setPosition(newX, newY);
}

void MoveDown(Entity* entity, Board& board) {
    Player* player = dynamic_cast<Player*>(entity);
    if (!player) return;

    auto pos = player->getPosition();
    int newX = pos.getX() + 1;
    int newY = pos.getY();

    if (newX >= kBoardSize) {
        newX = 0;
    }

    Entity* target = board.getEntity(Position(newX,newY));
	if (auto* heal = dynamic_cast<Heal*>(target)) {
    	HealPlayerOnItem(player, board,Position(newX,newY));
    	delete heal;
	} else if (board.getEntityType(Position(newX,newY)) == EntityType::ITEM) {
    	CollectItem(player, board, Position(newX,newY));
	}


    board.setEntity(Position(newX,newY), player);
    board.setEntity(Position(pos.getX(),pos.getY()), nullptr); // Clear old position
    player->setPosition(newX, newY);
}


void CollectItem(Player* player, Board& board,Position pos) {
    Entity* entity = board.getEntity(Position(pos.getX(),pos.getY()));
    Item* item = dynamic_cast<Item*>(entity);
    if (item) {
        board.setEntity(Position(pos.getX(),pos.getY()), nullptr); // Remove from board
        player->addItem(std::unique_ptr<Item>(item));
    }
}

bool IsPlayerNearMob(Player* player, Board& board) {
	auto playerPos = player->getPosition();
	for (int x = playerPos.getX() - 2; x <= playerPos.getX() + 2; ++x) {
		for (int y = playerPos.getY() - 2; y <= playerPos.getY() + 2; ++y) {
			if (x >= 0 && x < kBoardSize && y >= 0 && y < kBoardSize) {
				Entity* entity = board.getEntity(Position(x,y));
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
	for (int x = playerPos.getX() - 2; x <= playerPos.getY() + 2; ++x) {
		for (int y = playerPos.getX() - 2; y <= playerPos.getY() + 2; ++y) {
			if (x >= 0 && x < kBoardSize && y >= 0 && y < kBoardSize) {
				Entity* entity = board.getEntity(Position(x,y));
				if (entity && entity->getType() == EntityType::MOB) {
					return dynamic_cast<Mob*>(entity);
				}
			}
		}
	}
	return nullptr;
}
