#pragma once
#include <iostream>

class Stats {
public:
    int hp;
    double attack;
    double defense;
    int xp;
    int level;
    int maxHp = 30;

    Stats(int hp,double attack, double defense = 2,int xp = 0,int level = 1) :
    hp(hp), attack(attack), defense(defense), xp(xp), level(level) {}

    void gainXp(int amount);
    void checkLvlUp();
    int getXpToNxtLvl();

};