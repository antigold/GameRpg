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

enum class ItemType {
    HEAL,
    WEAPON
};

enum class WeaponType {
    SWORD,
    BOW
};

class Entity {
private:
    EntityType type;
    double attack;
    double hp;
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
    ItemType type;
public:
    Item(const std::string& itemName, ItemType type, std::array<int,2> pos);
    virtual ~Item() override;

    std::string getName() const;
    void setName(const std::string& newName);
    ItemType getItemType() const;
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
    Heal(const std::string& itemName, double amount, ItemType type, std::array<int,2> pos);
    double getHealAmount() const;
    void setHealAmount(double newAmount);
};

class Weapon : public Item {
private:
    double attackPoints;
    WeaponType weaponType;
public:
    Weapon(const std::string& itemName, double attack, ItemType type, WeaponType Wtype, std::array<int,2> pos);
    double getAttackPoints() const;
    void setAttackPoints(double newAttack);
    WeaponType getWeaponType() const;
};
