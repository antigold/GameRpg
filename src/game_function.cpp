#include <iostream>
#include "game_function.hpp"
#include "board.hpp"
#include "combat.hpp"

void HealPlayer(std::shared_ptr<Player> player, double amount) {
	if (amount < 0) {
		return;
	}
	player->getStats().setHp(player->getStats().getHp() + amount);
}

void HealPlayerOnItem(std::shared_ptr<Player> player, Board& board, Position pos) {
	Entity* entity = board.getEntityAt(pos).get();
	Heal* healItem = dynamic_cast<Heal*>(entity);
	if (healItem) {
		HealPlayer(player, healItem->getHealAmount());
	}
}

void MoveRight(Entity* entity, Board& board) {
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(board.getEntityAt(entity->getPosition()));
    if (!player) return;

    auto pos = player->getPosition();
    int newX = pos.getX();
    int newY = pos.getY() + 1;
    if (newY >= kBoardSize) newY = 0;

	Position targetpos = Position(newX,newY); // New position

	Entity* target = board.getEntityAt(targetpos).get();
	if (dynamic_cast<Heal*>(target)) {
    	HealPlayerOnItem(player, board,Position(newX,newY));
	} else if (board.getEntityType(targetpos) == EntityType::ITEM) {
    	CollectItem(player, board,targetpos);
	} else if (isMobAt(targetpos,board)){
		StartFight(board);
	}

    board.setEntity(targetpos, player);
    board.setEntity(Position(pos.getX(),pos.getY()), nullptr);
    player->setPosition(targetpos);
}


void MoveLeft(Entity* entity, Board& board) {
	std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(board.getEntityAt(entity->getPosition()));
    if (!player) return;
    auto pos = player->getPosition();
    int newX = pos.getX();
    int newY = pos.getY() - 1;

    if (newY < 0){
        newY = kBoardSize - 1;
	}

	Position targetpos = Position(newX,newY);

	Entity* target = board.getEntityAt(targetpos).get();
	if (dynamic_cast<Heal*>(target)) {
    	HealPlayerOnItem(player, board,targetpos);
	} else if (board.getEntityType(targetpos) == EntityType::ITEM) {
    	CollectItem(player, board,targetpos);
	} else if (isMobAt(targetpos,board)){
		StartFight(board);
	}

    board.setEntity(targetpos, player);
	board.setEntity(Position(pos.getX(),pos.getY()), nullptr); // Clear old position
	player->setPosition(targetpos);
}


void MoveUp(Entity* entity, Board& board) {
	std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(board.getEntityAt(entity->getPosition()));
    if (!player) return;
	auto pos = player->getPosition();
	int newX = pos.getX() - 1;
	int newY = pos.getY();

	if (newX < 0) {
		newX = kBoardSize - 1;
	}

	Position targetpos = Position(newX,newY);

	Entity* target = board.getEntityAt(targetpos).get();
	if (dynamic_cast<Heal*>(target)) {
    	HealPlayerOnItem(player, board,Position(newX,newY));
	} else if (board.getEntityType(targetpos) == EntityType::ITEM) {
    	CollectItem(player, board,targetpos);
	} else if (isMobAt(targetpos,board)){
		StartFight(board);
	}
	
	board.setEntity(targetpos, player);
	board.setEntity(Position(pos.getX(),pos.getY()), nullptr); // Clear old position
	player->setPosition(targetpos);
}

void MoveDown(Entity* entity, Board& board) {
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(board.getEntityAt(entity->getPosition()));
    if (!player) return;

    auto pos = player->getPosition();
    int newX = pos.getX() + 1;
    int newY = pos.getY();

    if (newX >= kBoardSize) {
        newX = 0;
    }

	Position targetpos = Position(newX,newY);

    Entity* target = board.getEntityAt(targetpos).get();
	if (dynamic_cast<Heal*>(target)) {
    	HealPlayerOnItem(player, board,targetpos);
	} else if (board.getEntityType(targetpos) == EntityType::ITEM) {
    	CollectItem(player, board, targetpos);
	} else if (isMobAt(targetpos,board)){
		StartFight(board);
	}


    board.setEntity(targetpos, player);
    board.setEntity(Position(pos.getX(),pos.getY()), nullptr); // Clear old position
    player->setPosition(targetpos);
}


void CollectItem(std::shared_ptr<Player> player, Board& board,Position pos) {
	Position entity_pos = Position(pos.getX(),pos.getY());
    Entity* entity = board.getEntityAt(entity_pos).get();
    Item* item = dynamic_cast<Item*>(entity);
    if (item) {
        board.setEntity(entity_pos, nullptr); // Remove from board
        player->getInventory().addItem(std::unique_ptr<Item>(item));
    }
}

bool IsPlayerNearMob(Player* player, Board& board) {
	auto playerPos = player->getPosition();
	for (int x = playerPos.getX() - 2; x <= playerPos.getX() + 2; ++x) {
		for (int y = playerPos.getY() - 2; y <= playerPos.getY() + 2; ++y) {
			if (x >= 0 && x < kBoardSize && y >= 0 && y < kBoardSize) {
				Entity* entity = board.getEntityAt(Position(x,y)).get();
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
	for (int x = playerPos.getX() - 2; x <= playerPos.getX() + 2; ++x) {
		for (int y = playerPos.getY() - 2; y <= playerPos.getY() + 2; ++y) {
			if (x >= 0 && x < kBoardSize && y >= 0 && y < kBoardSize) {
				Entity* entity = board.getEntityAt(Position(x,y)).get();
				if (entity && entity->getType() == EntityType::MOB) {
					return dynamic_cast<Mob*>(entity);
				}
			}
		}
	}
	return nullptr;
}

bool isMobAt(Position pos, Board& board){
	if (board.getEntityType(pos) == EntityType::MOB){
		return true;
	}
	return false;
}