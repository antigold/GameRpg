#include <iostream>
#include <memory>
#include "GameBoard.cpp"


static void Info(Player* player, std::array<int, 2> position) {
	std::cout << "Player is at position: (" << position[0] << ", " << position[1] << ")" << std::endl;
	std::cout << "Player HP: " << player->getHp() << std::endl;
	std::cout << "Player Attack: " << player->getAttack() << std::endl;
	std::cout << "Player Defense: " << player->getDefense() << std::endl;
	player->listInventory();
	player->displayXp();
}

static void MoveRight(Entity* entity, Board& board) {
	auto pos = entity->getPosition();
	int newX = pos[0];
	int newY = pos[1] + 1;

	if (newX >= BOARD_SIZE) {
		newX = 0; 
	}
	// Supprime l'entité de l'ancienne position
	board.DeleteEntity(pos[0], pos[1]);

	board.setEntity(newX, newY, entity);
}

static void MoveLeft(Entity* entity, Board& board) {
	auto pos = entity->getPosition();
	int newX = pos[0];
	int newY = pos[1] - 1;

	if (newX < 0) {
		newX = BOARD_SIZE - 1;
	}
	// Supprime l'entité de l'ancienne position
	board.DeleteEntity(pos[0], pos[1]);

	board.setEntity(newX, newY, entity);
}

static void MoveUp(Entity* entity, Board& board) {
	auto pos = entity->getPosition();
	int newX = pos[0] - 1;
	int newY = pos[1];

	if (newX < 0) {
		newX = BOARD_SIZE - 1;
	}
	// Supprime l'entité de l'ancienne position
	board.DeleteEntity(pos[0], pos[1]);

	board.setEntity(newX, newY, entity);
}

static void MoveDown(Entity* entity, Board& board) {
	auto pos = entity->getPosition();
	int newX = pos[0] + 1;
	int newY = pos[1];

	if (newX >= BOARD_SIZE) {
		newX = 0;
	}
	// Supprime l'entité de l'ancienne position
	board.DeleteEntity(pos[0], pos[1]);

	board.setEntity(newX, newY, entity);
}

static void Move(Entity* entity, Board& board, int dx, int dy) {
	auto pos = entity->getPosition();
	int newX = (pos[0] + dx + BOARD_SIZE) % BOARD_SIZE;
	int newY = (pos[1] + dy + BOARD_SIZE) % BOARD_SIZE;

	board.DeleteEntity(pos[0], pos[1]);
	board.setEntity(newX, newY, entity);
}

void run() {
	/*
	Board board;
	Player* player = new Player(100,50,10,{0,0});
	std::unique_ptr<Item> item = std::make_unique<Weapon>("Sword", 5, ItemType::WEAPON, WeaponType::SWORD);
	std::cout << "Welcome to the game!" << std::endl;
	std::cout << "Game is running..." << std::endl;
	std::cout << "------------------------" << std::endl;

	board.setEntity(BOARD_SIZE/2, BOARD_SIZE/2, player);
	auto position = player->getPosition();
	DisplayBoard(board);
	player->addItem(std::move(item));
	Info(player, position);
	keyboardInput(player, board);
	position = player->getPosition();
	DisplayBoard(board);
	Info(player, position);
	*/
	Board board;
	Player* player = new Player(100, 50, 10, { 0, 0 });
	std::unique_ptr<Item> item = std::make_unique<Weapon>("Sword", 5, ItemType::WEAPON, WeaponType::SWORD);

	std::cout << "Welcome to the game!" << std::endl;

	//Just to add smth to test///////////////////
	board.setEntity(BOARD_SIZE / 2, BOARD_SIZE / 2, player);
	player->addItem(std::move(item));
	//////////////////////////////////////

	bool isGameRunning = true;

	DisplayBoard(board);

	while (isGameRunning) {
		isGameRunning = false;
	}
}