#include <iostream>
#include "game_function.hpp"
#include "board.hpp"
#include "combat.hpp"

void HealPlayer(std::shared_ptr<Player> player, int amount) {
	if (amount < 0) {
		return;
	}
	player->getStats().hp += amount;
}

void HealPlayerOnItem(std::shared_ptr<Player> player, Board& board, Position pos) {
	Entity* entity = board.getEntityAt(pos).get();
	Heal* healItem = dynamic_cast<Heal*>(entity);
	if (healItem) {
		HealPlayer(player, healItem->getHealAmount());
	}
}

void MoveRight(Entity* entity, Board& board,
               SDL_Renderer* renderer,
               TTF_Font* font,
               SDL_Texture* playerTexture,
               SDL_Texture* mobTexture) {

    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(board.getEntityAt(entity->getPosition()));
    if (!player) return;

    auto pos = player->getPosition();
    int newX = pos.x;
    int newY = pos.y + 1;
    if (newY >= kBoardSize) newY = 0;

	Position targetpos = Position(newX,newY); // New position

	Entity* target = board.getEntityAt(targetpos).get();
	if (dynamic_cast<Heal*>(target)) {
    	HealPlayerOnItem(player, board,Position(newX,newY));
	} else if (board.getEntityType(targetpos) == EntityType::ITEM) {
    	CollectItem(player,board,targetpos);
	} else if (isMobAt(targetpos,board)){
		std::shared_ptr<Mob> MobTarget = std::dynamic_pointer_cast<Mob>(board.getEntityAt(targetpos));
		StartFight(board,player,MobTarget,renderer,font,playerTexture,mobTexture);
	}

    board.setEntity(targetpos, player);
    board.setEntity(Position(pos.x,pos.y), nullptr);
    player->setPosition(targetpos);
}


void MoveLeft(Entity* entity, Board& board,
               SDL_Renderer* renderer,
               TTF_Font* font,
               SDL_Texture* playerTexture,
               SDL_Texture* mobTexture) {

	std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(board.getEntityAt(entity->getPosition()));
    if (!player) return;
    auto pos = player->getPosition();
    int newX = pos.x;
    int newY = pos.y - 1;

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
		std::shared_ptr<Mob> MobTarget = std::dynamic_pointer_cast<Mob>(board.getEntityAt(targetpos));
		StartFight(board,player,MobTarget,renderer,font,playerTexture,mobTexture);
	}

    board.setEntity(targetpos, player);
	board.setEntity(Position(pos.x,pos.y), nullptr); // Clear old position
	player->setPosition(targetpos);
}


void MoveUp(Entity* entity, Board& board,
               SDL_Renderer* renderer,
               TTF_Font* font,
               SDL_Texture* playerTexture,
               SDL_Texture* mobTexture) {

	std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(board.getEntityAt(entity->getPosition()));
    if (!player) return;
	auto pos = player->getPosition();
	int newX = pos.x - 1;
	int newY = pos.y;

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
		std::shared_ptr<Mob> MobTarget = std::dynamic_pointer_cast<Mob>(board.getEntityAt(targetpos));
		StartFight(board,player,MobTarget,renderer,font,playerTexture,mobTexture);
	}
	
	board.setEntity(targetpos, player);
	board.setEntity(Position(pos.x,pos.y), nullptr); // Clear old position
	player->setPosition(targetpos);
}

void MoveDown(Entity* entity, Board& board,
               SDL_Renderer* renderer,
               TTF_Font* font,
               SDL_Texture* playerTexture,
               SDL_Texture* mobTexture) {

    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(board.getEntityAt(entity->getPosition()));
    if (!player) return;

    auto pos = player->getPosition();
    int newX = pos.x + 1;
    int newY = pos.y;

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
		std::shared_ptr<Mob> MobTarget = std::dynamic_pointer_cast<Mob>(board.getEntityAt(targetpos));
		StartFight(board,player,MobTarget,renderer,font,playerTexture,mobTexture);
	}


    board.setEntity(targetpos, player);
    board.setEntity(Position(pos.x,pos.y), nullptr); // Clear old position
    player->setPosition(targetpos);
}


void CollectItem(std::shared_ptr<Player> player, Board& board,Position pos) {
	Position entity_pos = Position(pos.x,pos.y);
    Entity* entity = board.getEntityAt(entity_pos).get();
    Item* item = dynamic_cast<Item*>(entity);
    if (item) {
        board.setEntity(entity_pos, nullptr); // Remove from board
        player->getInventory().addItem(std::unique_ptr<Item>(item));
    }
}

bool IsPlayerNearMob(Player* player, Board& board) {
	auto playerPos = player->getPosition();
	for (int x = playerPos.x - 2; x <= playerPos.x + 2; ++x) {
		for (int y = playerPos.y - 2; y <= playerPos.y + 2; ++y) {
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
	for (int x = playerPos.x - 2; x <= playerPos.x + 2; ++x) {
		for (int y = playerPos.y - 2; y <= playerPos.y + 2; ++y) {
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