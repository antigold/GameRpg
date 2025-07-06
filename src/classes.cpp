#include "classes.hpp"
#include <iostream>

//|===============================|Class Position|====================================|

Position::Position(int x,int y) : x_(x), y_(y) {}
Position::~Position() {}

int Position::getX() const {return x_;}
int Position::getY() const {return y_;}
void Position::setX(int newX) {x_ = newX;}
void Position::setY(int newY) {y_ = newY;}


//|================================|Class Entity|======================================|
Entity::Entity(EntityType t, double hp, double attack, Position pos) :
    type(t), hp(hp), attack(attack), Pos(pos) {}

Entity::~Entity() = default;

double Entity::getHp() { return hp; }
double Entity::getAttack() { return attack; }
void Entity::setHp(double newHp) { hp = newHp; }
void Entity::setAttack(double newAttack) { attack = newAttack; }
bool Entity::isAlive() const {
    return hp > 0;
}

void Entity::setPosition(int x, int y) {
    if (x < 0 || y < 0) {
        std::cout << "Position cannot be negative. Setting to (0, 0)." << std::endl;
        Pos.setX(0);
        Pos.setY(0);
    } else {
        Pos.setX(x);
        Pos.setY(y);
    }
}

Position Entity::getPosition() {
    return Pos;
}

EntityType Entity::getType() const { return type; }
std::string Entity::getClassName() const {return "Entity";}

//|================================|Class Item|======================================|

Item::Item(const std::string& itemName,Position pos)
    : Entity(EntityType::ITEM, 0, 0, pos), name(itemName) {}

Item::~Item() = default;

std::string Item::getName() const { return name; }
void Item::setName(const std::string& newName) { name = newName; }

//|================================|Class Player|======================================|

Player::Player() : Entity(EntityType::PLAYER, 100, 10, {0,0}), defense(5), xp(0), level(1) {}
Player::Player(double hp, double attack, double defense, Position pos)
    : Entity(EntityType::PLAYER, hp, attack, pos), defense(defense), xp(0), level(1) {}

double Player::getDefense() const { return defense; }
int Player::getXp() const { return xp;}
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

//|================================|Class Mob|======================================|

Mob::Mob(const std::string& name, double hp, double attack, Position pos) : Entity(EntityType::MOB, hp, attack, pos), mobname(name) {}
std::string Mob::getClassName() const { return "Mob"; }
std::string Mob::getMobName() const { return mobname; }
void Mob::setMobName(const std::string& newName) { mobname = newName; }

//|================================|Class Void|======================================|

Void::Void(Position pos) : Entity(EntityType::VOID, 0, 0, pos) {}

//|================================|Class Heal|======================================|

Heal::Heal(const std::string& itemName, double amount, Position pos)
    : Item(itemName,pos), healAmount(amount) {
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
std::string Heal::getClassName() const { return "Heal"; }

//|================================|Class Weapon|======================================|

Weapon::Weapon(const std::string& itemName, double attack, Position pos)
    : Item(itemName,pos), attackPoints(attack) {
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

//|================================|Class Sword|======================================|

Sword::Sword(const std::string& itemName, double attack, Position pos)
    : Weapon(itemName, attack, pos) {}
std::string Sword::getClassName() const { return "Sword"; }
    
//|================================|Class Bow|======================================|
    
Bow::Bow(const std::string& itemName, double attack, double range, Position pos)
    : Weapon(itemName, attack, pos), range(range) {
    if (range < 0) {
        std::cerr << "Range cannot be negative. Setting to 0." << std::endl;
        range = 3; //Default range 
    }
}
double Bow::getRange() const { return range; }
void Bow::setRange(double newRange) {
    if (newRange < 0) {
        std::cerr << "Range cannot be negative. Setting to 0." << std::endl;
        newRange = 3; //Default range 
    }
    range = newRange;
}
std::string Bow::getClassName() const { return "Bow"; }
