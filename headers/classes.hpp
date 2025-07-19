#pragma once
#include <array>
#include <vector>
#include <memory>
#include <string>
#include "position.hpp"
#include "board.hpp"
#include "player.hpp"
#include "entity.hpp"

class Item : public Entity {
    private:
    std::string name;
    public:
    Item(const std::string& itemName,Position pos);
    virtual ~Item() override;
    
    std::string getName() const;
    void setName(const std::string& newName);
};

class Heal : public Item {
private:
    double healAmount;
public:
    Heal(const std::string& itemName, double healamount,Position pos);
    double getHealAmount() const;
    void setHealAmount(double newAmount);
    virtual std::string getClassName() const override;
};

class Weapon : public Item {
private:
    double attackPoints;
public:
    Weapon(const std::string& itemName, double attack,Position pos);
    double getAttackPoints() const;
    void setAttackPoints(double newAttack);
};

class Sword : public Weapon {
public:
    Sword(const std::string& itemName, double attack, Position pos);
    virtual std::string getClassName() const override;
};

class Bow : public Weapon {
private:
    double range;
public:
    Bow(const std::string& itemName, double attack, double range, Position pos);
    double getRange() const;
    void setRange(double newRange);
    virtual std::string getClassName() const override;
};