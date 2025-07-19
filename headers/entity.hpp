#pragma once
#include <iostream>
#include "gameStates.hpp"
#include "position.hpp"

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