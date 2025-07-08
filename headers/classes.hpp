#pragma once
#include <array>
#include <vector>
#include <memory>
#include <string>
#include <functional>

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
    bool operator==(const Position& other) const;
};
namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& pos) const {
            return std::hash<int>()(pos.getX()) ^ (std::hash<int>()(pos.getY()) << 1);
        }
    };
}

class Entity {
    private:
    EntityType type;
    double hp;
    double attack;
    Position Pos;
    public:
    Entity(EntityType t, double hp, double attack, Position pos);
    virtual ~Entity();
    
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

class Inventory {
private:
    std::vector<std::unique_ptr<Item>> items;
    static constexpr size_t MAX_INV_SIZE = 5;
public:
    Inventory();
    bool addItem(std::unique_ptr<Item> item);
    void removeItem(const std::string& name);
    void removeFirstItem();
    const std::vector<std::unique_ptr<Item>>& getItems() const;
    size_t getSize() const;
    size_t getMaxSize() const;
    bool isEmpty();
};

class Stats {
private:
    double hp;
    double attack;
    double defense;
    int xp;
    int level;
public:
    Stats(double hp,double attack, double defense = 2,int xp = 0,int level = 1);

    double getHp() const;
    void setHp(double amount);
    double getAttack() const;
    void setAttack(double newAtt);
    double getDefense() const;
    void setDefense(double newDef);
    int getXp() const;
    void setXp(int newXp);
    int getLevel() const;
    void setLevel(int newLvl);
};
class Player : public Entity {
private:
    Stats stats;
    Inventory inventory;
public:
    Player(Position pos);
    Inventory& getInventory();
    Stats& getStats();
    const Stats& getStats() const;
};

class Mob : public Entity {
private:
    std::string mobname;
    Stats stats;
    Inventory inventory;
public:
    Mob(const std::string& name,Stats stats,Position pos);
    std::string getMobName() const;
    void setMobName(const std::string& newName);
    virtual std::string getClassName() const override;
    Stats& getStats();
    const Stats& getStats() const;
    
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
