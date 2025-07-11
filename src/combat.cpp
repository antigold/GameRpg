#include <iostream>
#include "combat.hpp"

void StartFight(Board& board,std::shared_ptr<Player> player, std::shared_ptr<Mob> mob){

    bool isCombatOver = false;
    Turn currentTurn = Turn::PLAYER;

    while (!isCombatOver) {
        if (player->getStats().getHp() <= 0 || mob->getStats().getHp() <= 0) {
            isCombatOver = true;
            break;
        }

        if (currentTurn == Turn::PLAYER) {
            // Afficher options : attaque (A), défense (P)
            if (is_key_pressed(SDL_SCANCODE_A)) {
                player->attack(mob);
                player->setPlayerProtecting(false);
                currentTurn = Turn::MOB;
                SDL_Delay(300);
            } 
            else if (is_key_pressed(SDL_SCANCODE_P)) {
                player->setPlayerProtecting(true);
                currentTurn = Turn::MOB;
                SDL_Delay(300);
            }
        } 
        else if (currentTurn == Turn::MOB) {
            if (player->isPlayerProtecting()) {
                player->protect(mob->getStats().getAttack());
            } else {
                mob->attackPlayer(player);
            }

            currentTurn = Turn::PLAYER;
            SDL_Delay(300);
        }

        //TODO interface graphique avec pv ect..
    }
}