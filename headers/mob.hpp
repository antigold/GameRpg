#pragma once
#include <iostream>
#include "classes.hpp"
#include "stats.hpp"
#include "entity.hpp"
#include "player.hpp"

class Player;
class Board;

enum class MobState {
    FREE, // the enemy walk on the board
    CHASE // the enemu chase the nearest player
};

class Mob : public Entity{
private:
    std::string mobname;
    Stats stats;
    Inventory inventory;
    MobState currenState = MobState::FREE;
    Direction patrolDir;
    int stepsLeft;
public:
    Mob(const std::string& name,Stats stats,Position pos);
    std::string getMobName() const;
    void setMobName(const std::string& newName);
    virtual std::string getClassName() const override;
    Stats& getStats();
    const Stats& getStats() const;
    void attackPlayer(std::shared_ptr<Player> player);
    void setState(MobState state);
    void chase(Position target,Board& board);
    void patrol(Board& board);
};