#include <iostream>
#include "GameFunction.hpp"
#include "Entity.hpp"

void MoveRight(Entity* entity, Board& board) {
    auto pos = entity->getPosition();
    int newX = pos[0];
    int newY = pos[1] + 1;

    if (newY >= BOARD_SIZE)
        newY = 0;

    board.DeleteEntity(pos[0], pos[1]);
    board.setEntity(newX, newY, entity);
	entity->setPosition(newX, newY); // Update entity position after moving
}


void MoveLeft(Entity* entity, Board& board) {
    auto pos = entity->getPosition();
    int newX = pos[0];
    int newY = pos[1] - 1;

    if (newY < 0)
        newY = BOARD_SIZE - 1;

    board.DeleteEntity(pos[0], pos[1]);
    board.setEntity(newX, newY, entity);
	entity->setPosition(newX, newY);
}


void MoveUp(Entity* entity, Board& board) {
	auto pos = entity->getPosition();
	int newX = pos[0] - 1;
	int newY = pos[1];

	if (newX < 0) {
		newX = BOARD_SIZE - 1;
	}
	board.DeleteEntity(pos[0], pos[1]);

	board.setEntity(newX, newY, entity);
	entity->setPosition(newX, newY);
}

void MoveDown(Entity* entity, Board& board) {
	auto pos = entity->getPosition();
	int newX = pos[0] + 1;
	int newY = pos[1];

	if (newX >= BOARD_SIZE) {
		newX = 0;
	}
	board.DeleteEntity(pos[0], pos[1]);

	board.setEntity(newX, newY, entity);
	entity->setPosition(newX, newY);
}