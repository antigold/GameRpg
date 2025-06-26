#pragma once
#include <array>
#include <vector>
#include <memory>
#include <string>

enum class EntityType {
    PLAYER,
    MOB,
    ITEM,
    VOID
};

class Entity {
private:
    EntityType type;
    double hp;
    double attack;
    std::array<int,2> Position;
public:
    Entity(EntityType t, double hp, double attack, std::array<int,2> pos);
    virtual ~Entity();

    double getHp();
    double getAttack();
    void setHp(double newHp);
    void setAttack(double newAttack);

    void setPosition(int x, int y);
    std::array<int, 2> getPosition();

    EntityType getType() const;
};

class Item : public Entity {
private:
    std::string name;
public:
    Item(const std::string& itemName,std::array<int,2> pos);
    virtual ~Item() override;

    std::string getName() const;
    void setName(const std::string& newName);
};

class Player : public Entity {
private:
    double defense;
    std::vector<std::unique_ptr<Item>> inventory;
    static constexpr size_t INVENTORY_SIZE = 5;
    int xp;
    int level;
public:
    Player();
    Player(double hp, double attack, double defense, std::array<int,2> pos);

    double getDefense() const;
    int getXp() const;
    void setXp(int newXp);
    void setDefense(double newDefense);

    const std::vector<std::unique_ptr<Item>>& getInventory() const;
    void listInventory();
    void addItem(std::unique_ptr<Item> item);
    void removeItem(const std::string& itemName);

    int getLevel() const;
    void setLevel(int newLevel);

    void displayXp();
};

class Mob : public Entity {
public:
    Mob();
    Mob(double hp, double attack, std::array<int,2> pos);
};

class Void : public Entity {
public:
    explicit Void(const std::array<int, 2>& pos = {0, 0});
};

class Heal : public Item {
private:
    double healAmount;
public:
    Heal(const std::string& itemName, double healamount,std::array<int,2> pos);
    double getHealAmount() const;
    void setHealAmount(double newAmount);
};

class Weapon : public Item {
private:
    double attackPoints;
public:
    Weapon(const std::string& itemName, double attack,std::array<int,2> pos);
    double getAttackPoints() const;
    void setAttackPoints(double newAttack);
};

class Sword : public Weapon {
public:
    Sword(const std::string& itemName, double attack, std::array<int,2> pos);
};

class Bow : public Weapon {
private:
    double range;
public:
    Bow(const std::string& itemName, double attack, double range, std::array<int,2> pos);
    double getRange() const;
    void setRange(double newRange);
};
