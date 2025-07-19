#include <iostream>
#include "mob.hpp"

Mob::Mob(const std::string& name,Stats Stats,Position pos) : Entity(EntityType::MOB,25.0,3.0,pos), mobname(name),
    stats(25.0,3.0,0),
    inventory() {}
std::string Mob::getClassName() const { return "Mob"; }
std::string Mob::getMobName() const { return mobname; }
void Mob::setMobName(const std::string& newName) { mobname = newName; }

Stats& Mob::getStats() {
    return stats;
}

const Stats& Mob::getStats() const {
    return stats;
}

void Mob::attackPlayer(std::shared_ptr<Player> player) {
    double attackAmount = getStats().attack;
    double finalDamage;

    if (player->isPlayerProtecting()) {
        finalDamage = player->protect(attackAmount);
    } else {
        double defense = player->getStats().defense;
        finalDamage = attackAmount * (100.0 / (100.0 + defense));
    }

    double playerHp = player->getStats().hp;
    playerHp -= finalDamage;
    if (playerHp < 0) playerHp = 0;

    player->getStats().hp = playerHp;
}

void Mob::setState(MobState state){
    currenState = state;
}

void Mob::chase(Position target,Board& board){
    Position currentPos = getPosition();
    int dx = (target.x > currentPos.x) ? 1 : (target.x < currentPos.x) ? -1 : 0;
    int dy = (target.y > currentPos.y) ? 1 : (target.y < currentPos.y) ? -1 : 0;

    Position nextPos = {currentPos.x + dx, currentPos.y};
    if (board.isWalkable(nextPos)) {
        setPosition(nextPos);
        return;
    }

    nextPos = {currentPos.x, currentPos.y + dy};
    if (board.isWalkable(nextPos)) {
        setPosition(nextPos);
        return;
    }
}

void Mob::patrol(Board& board){
     if (stepsLeft <= 0) {
        patrolDir = getRandomDirection();
        stepsLeft = rand() % 4 + 1;
    }

    Position next = { getPosition().x + dx(patrolDir), getPosition().y + dy(patrolDir) };

    if (board.isWalkable(next)) {
        setPosition(next);
        stepsLeft--;
    } else {
        stepsLeft = 0;
    }
}