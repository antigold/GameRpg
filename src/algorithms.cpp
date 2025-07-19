#include <iostream>
#include "algorithms.hpp"


void InitMobAlgorithm(Board &board,std::shared_ptr<Player> player){

    const auto& entities = board.getEntities();

    for (const auto& [pos, entity] : entities) {
        std::shared_ptr<Mob> mob = std::dynamic_pointer_cast<Mob>(entity);
        if (!mob) {
            continue;
        }

        Position mobPos = mob->getPosition();
        Position playerPos = player->getPosition();
        int distance = std::abs(mobPos.x - playerPos.x) + std::abs(mobPos.y - playerPos.y);

        if (distance <= 5) {
            mob->setState(MobState::CHASE);
            mob->chase(playerPos, board);
        } else {
            mob->setState(MobState::FREE);
            mob->patrol(board);
        }
    }
}

