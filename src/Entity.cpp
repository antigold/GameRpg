#include "Entity.hpp"
#include <iostream>

Entity::Entity(EntityType t, double hp, double attack, std::array<int,2> pos) :
    type(t), hp(hp), attack(attack), Position(pos) {}

Entity::~Entity() = default;

double Entity::getHp() { return hp; }
double Entity::getAttack() { return attack; }
void Entity::setHp(double newHp) { hp = newHp; }
void Entity::setAttack(double newAttack) { attack = newAttack; }

void Entity::setPosition(int x, int y) {
    if (x < 0 || y < 0) {
        std::cout << "Position cannot be negative. Setting to (0, 0)." << std::endl;
        Position = {0, 0};
    } else {
        Position = {x, y};
    }
}

std::array<int, 2> Entity::getPosition() {
    return Position;
}

EntityType Entity::getType() const { return type; }

Item::Item(const std::string& itemName, ItemType type, std::array<int,2> pos)
    : Entity(EntityType::ITEM, 0, 0, pos), name(itemName), type(type) {}

Item::~Item() = default;

std::string Item::getName() const { return name; }
void Item::setName(const std::string& newName) { name = newName; }
ItemType Item::getItemType() const { return type; }

Player::Player() : Entity(EntityType::PLAYER, 100, 10, {0,0}), defense(5), xp(0), level(1) {}
Player::Player(double hp, double attack, double defense, std::array<int,2> pos)
    : Entity(EntityType::PLAYER, hp, attack, pos), defense(defense), xp(0), level(1) {}

double Player::getDefense() const { return defense; }
int Player::getXp() const { return xp; }
void Player::setXp(int newXp) {
    if (newXp < 0) {
        std::cerr << "XP cannot be negative. Setting to 0." << std::endl;
        newXp = 0;
    }
    xp = newXp;
}

void Player::setDefense(double newDefense) {
    if (newDefense < 0) {
        std::cerr << "Defense cannot be negative. Setting to 0." << std::endl;
        newDefense = 0;
    }
    defense = newDefense;
}

const std::vector<std::unique_ptr<Item>>& Player::getInventory() const {
    return inventory;
}

void Player::listInventory() {
    std::cout << "Inventory: " << std::endl;
    for (const auto& item : inventory) {
        std::cout << "- " << item->getName() << std::endl;
    }
}

void Player::addItem(std::unique_ptr<Item> item) {
    if (inventory.size() < INVENTORY_SIZE) {
        inventory.push_back(std::move(item));
    } else {
        std::cerr << "Inventory is full. Cannot add more items." << std::endl;
    }
}

void Player::removeItem(const std::string& itemName) {
    std::cout << "test" << std::endl;
}

int Player::getLevel() const { return level; }
void Player::setLevel(int newLevel) {
    if (newLevel < 0) {
        std::cerr << "Level cannot be negative. Setting to 0." << std::endl;
        newLevel = 0;
    }
    level = newLevel;
}

void Player::displayXp() {
    char xpBar[10] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
    int length = sizeof(xpBar) / sizeof(xpBar[0]);
    for (int i = 0; i < xp; i++) {
        if (i >= length) break;
        xpBar[i] = '*';
    }
    std::cout << "XP: " << xp << " | Level: " << level << std::endl;
    std::cout << "XP Bar: ";
    for (int i = 0; i < length; i++) {
        std::cout << xpBar[i];
    }
    std::cout << std::endl;
}

Mob::Mob() : Entity(EntityType::MOB, 50, 5, {0,0}) {}
Mob::Mob(double hp, double attack, std::array<int,2> pos) : Entity(EntityType::MOB, hp, attack, pos) {}

Void::Void(const std::array<int, 2>& pos) : Entity(EntityType::VOID, 0, 0, pos) {}

Heal::Heal(const std::string& itemName, double amount, ItemType type, std::array<int,2> pos)
    : Item(itemName, type, pos), healAmount(amount) {
    if (amount < 0) {
        std::cerr << "Heal amount cannot be negative. Setting to 0." << std::endl;
        healAmount = 0;
    }
}

double Heal::getHealAmount() const { return healAmount; }
void Heal::setHealAmount(double newAmount) {
    if (newAmount < 0) {
        std::cerr << "Heal amount cannot be negative. Setting to 0." << std::endl;
        newAmount = 0;
    }
    healAmount = newAmount;
}

Weapon::Weapon(const std::string& itemName, double attack, ItemType type, WeaponType Wtype, std::array<int,2> pos)
    : Item(itemName, type, pos), attackPoints(attack), weaponType(Wtype) {
    if (attack < 0) {
        std::cerr << "Attack points cannot be negative. Setting to 0." << std::endl;
        attackPoints = 0;
    }
}

double Weapon::getAttackPoints() const { return attackPoints; }
void Weapon::setAttackPoints(double newAttack) {
    if (newAttack < 0) {
        std::cerr << "Attack points cannot be negative. Setting to 0." << std::endl;
        newAttack = 0;
    }
    attackPoints = newAttack;
}

WeaponType Weapon::getWeaponType() const { return weaponType; }
