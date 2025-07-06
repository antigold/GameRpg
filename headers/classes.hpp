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

class Position {
private:
    int x_;
    int y_;
public:
    Position(int x,int y);
    ~Position();
    int getX() const;
    int getY() const;
    void setX(int newX);
    void setY(int newY);
};

class Entity {
private:
    EntityType type;
    double hp;
    double attack;
    Position Pos;
public:
    Entity(EntityType t, double hp, double attack, Position pos);
    virtual ~Entity();

    double getHp();
    double getAttack();
    void setHp(double newHp);
    void setAttack(double newAttack);
    bool isAlive() const;
    virtual std::string getClassName() const;

    void setPosition(Position pos);
    Position getPosition();

    EntityType getType() const;
};

class Item : public Entity {
private:
    std::string name;
public:
    Item(const std::string& itemName,Position pos);
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
    Player(double hp, double attack, double defense, Position pos);

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
private:
    std::string mobname;
public:
    Mob(const std::string& name, double hp, double attack, Position pos);
    std::string getMobName() const;
    void setMobName(const std::string& newName);
    virtual std::string getClassName() const override;
};

class Void : public Entity {
public:
    explicit Void(const Position pos = Position(0,0));
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
