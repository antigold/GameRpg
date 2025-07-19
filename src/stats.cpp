#include <iostream>
#include "stats.hpp"

void Stats::checkLvlUp(){
    int threshold = level * 10;
    while (xp >= threshold) {
        xp -= threshold;
        level++;
        maxHp += 5;
        hp = maxHp;
        attack += 2;
        defense += 0.5;
        std::cout << "Level Up !" << std::endl;

        threshold = level * (2 * level);
    }
}

void Stats::gainXp(int amount){
    xp += amount;
    checkLvlUp();
}

int Stats::getXpToNxtLvl(){
    int threshold = level * 10;
    return threshold - xp;
}