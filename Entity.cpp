#include <iostream>
#include <array>
#include <vector>

enum class EntityType {
	PLAYER,
	MOB,
	VOID
};

enum class ItemType {
	HEAL,
	WEAPON
};

enum class WeaponType {
	SWORD,
	BOW
};

class Item {
private:
	std::string name;
	ItemType type; // Assuming ItemType is an enum for different item types
public:
	Item(const std::string& itemName, ItemType type) : name(itemName), type(type) {}
	virtual ~Item() = default;
	std::string getName() const { return name; }
	void setName(const std::string& newName) { name = newName; }
	ItemType getType() const { return type; }
};

class Entity {
private:
	EntityType type;
	double attack;
	double hp;
	std::array<int,2> Position; // Assuming Position is an array of two integers for x and y coordinates
public:
	Entity(EntityType t, double hp, double attack, std::array<int,2> pos) : 
		type(t), hp(hp), attack(attack), Position(pos){}
	double getHp() { return hp; }
	double getAttack() { return attack; }
	void setHp(double newHp) { hp = newHp; }
	void setAttack(double newAttack) { attack = newAttack;}

	void setPosition(int x, int y) {
		if (x < 0 || y < 0) {
			std::cout << "Position cannot be negative. Setting to (0, 0)." << std::endl;
			Position = { 0,0 };
		}
		else {
			Position = { x, y };
		}
	}

	std::array<int, 2> getPosition() {
		return Position; 
	}

	EntityType getType() const { return type; }
	virtual ~Entity() = default; // Virtual destructor for proper cleanup in derived classes
};

class Player : public Entity {
private:
	double defense;
	std::vector<std::unique_ptr<Item>> inventory; // Assuming Item is a class defined elsewhere
	static constexpr size_t INVENTORY_SIZE = 5;
	int xp = 0;
	int level = 1;
public:
	Player() : Entity(EntityType::PLAYER,100, 10,{0,0}), defense(5) {} // Default constructor
	Player(double hp, double attack, double defense,std::array<int,2> pos) : Entity(EntityType::PLAYER,hp, attack,pos),
		defense(defense) {} // Parameterized constructor
	double getDefense() const { return defense; }
	int getXp() const { return xp; }
	void setXp(int newXp) {
		if (newXp < 0) {
			std::cerr << "XP cannot be negative. Setting to 0." << std::endl;
			newXp = 0;
		}
		xp = newXp;
	}
	void setDefense(double newDefense) { 
		if (newDefense < 0) {
			std::cerr << "Defense cannot be negative. Setting to 0." << std::endl;
			newDefense = 0;
		}
		defense = newDefense; 
	}

	void listInventory() {
		std::cout << "Inventory: " << std::endl;
		for (const auto& item : inventory) {
			std::cout << "- " << item->getName() << std::endl;
		}
	}

	void addItem(std::unique_ptr<Item> item) {
		if (inventory.size() < INVENTORY_SIZE) {
			inventory.push_back(std::move(item));
		}
		else {
			std::cerr << "Inventory is full. Cannot add more items." << std::endl;
		}
	}

	void removeItem(const std::string& itemName) {
		auto it = std::remove_if(inventory.begin(), inventory.end(),
			[&itemName](const std::unique_ptr<Item>& item) { return item->getName() == itemName; });
		if (it != inventory.end()) {
			inventory.erase(it, inventory.end());
		}
		else {
			std::cerr << "Item not found in inventory." << std::endl;
		}
	}

	int getLevel() const {
		return level;
	}

	void setLevel(int newLevel) {
		if (newLevel < 0) {
			std::cerr << "Level cannot be negative. Setting to 0." << std::endl;
			newLevel = 0;
		}
		level = newLevel;
	}

	void displayXp() {
		char xpBar[10] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
		int length = sizeof(xpBar) / sizeof(xpBar[0]);
		for (int i = 0; i < xp; i++) {
			if (i >= length) break; // Prevent overflow
			xpBar[i] = '*';
		}
		std::cout << "XP: " << xp << " | Level: " << level << std::endl;
		std::cout << "XP Bar: ";
		for (int i = 0; i < length; i++) {
			std::cout << xpBar[i];
		}
		std::cout << std::endl;
	}

};

class Mob : public Entity {
public:
	Mob() : Entity(EntityType::MOB,50, 5,{0,0}) {} // Default constructor
	Mob(double hp, double attack,std::array<int,2> pos) : Entity(EntityType::MOB,hp, attack,pos) {} // Parameterized constructor
};

class Void : public Entity {
public:
	explicit Void(const std::array<int, 2>& pos = { 0, 0 })
		: Entity(EntityType::VOID, 0, 0, pos) {}
};

class Heal : public Item {
private:
	double healAmount;
public:
	Heal(const std::string& itemName, double amount, ItemType type) : Item(itemName,type), healAmount(amount) {
		if (amount < 0) {
			std::cerr << "Heal amount cannot be negative. Setting to 0." << std::endl;
			healAmount = 0;
		}
	}
	double getHealAmount() const { return healAmount; }
	void setHealAmount(double newAmount) {
		if (newAmount < 0) {
			std::cerr << "Heal amount cannot be negative. Setting to 0." << std::endl;
			newAmount = 0;
		}
		healAmount = newAmount;
	}
};

class Weapon : public Item {
private:
	double attackPoints;
	WeaponType weaponType; // Assuming WeaponType is an enum for different weapon types
public:
	Weapon(const std::string& itemName, double attack, ItemType type,WeaponType Wtype) : Item(itemName,type), attackPoints(attack)
	, weaponType(Wtype) 
	{
		if (attack < 0) {
			std::cerr << "Attack points cannot be negative. Setting to 0." << std::endl;
			attackPoints = 0;
		}
	}
	double getAttackPoints() const { return attackPoints; }
	void setAttackPoints(double newAttack) {
		if (newAttack < 0) {
			std::cerr << "Attack points cannot be negative. Setting to 0." << std::endl;
			newAttack = 0;
		}
		attackPoints = newAttack;
	}
	WeaponType getWeaponType() const { return weaponType; }
};
