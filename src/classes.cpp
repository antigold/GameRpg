#include "classes.hpp"
#include <iostream>

//|================================|Class Item|======================================|

Item::Item(const std::string& itemName,Position pos)
    : Entity(EntityType::ITEM, 0, 0, pos), name(itemName) {}

Item::~Item() = default;

std::string Item::getName() const { return name; }
void Item::setName(const std::string& newName) { name = newName; }

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
