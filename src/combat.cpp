#include <iostream>
#include "combat.hpp"

SDL_Color white = {255, 255, 255, 255};
SDL_Color green = {15,255,0,0};
SDL_Color red = {155,0,0,0};

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (!surface) return;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect destRect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void displayCombat(SDL_Renderer* renderer, TTF_Font* font,
                   SDL_Texture* playerTexture, SDL_Texture* mobTexture,
                   std::shared_ptr<Player> player, std::shared_ptr<Mob> mob,Turn currentTurn) {
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Affiche les sprites
    SDL_Rect playerRect = {100, 200, 128, 128};
    SDL_Rect mobRect = {400, 200, 128, 128};
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);
    SDL_RenderCopy(renderer, mobTexture, NULL, &mobRect);

    // Affiche les HP
    std::string playerHpText = "Player HP: " + std::to_string((int)player->getStats().getHp()) + "/200";
    std::string mobHpText = "Mob HP: " + std::to_string((int)mob->getStats().getHp())+ "/50";
    renderText(renderer,font,"Press A/Q to attack",100,500,white);
    renderText(renderer,font,"Press P to protect",300,500,white);

    if (currentTurn == Turn::MOB){
        renderText(renderer,font,"Enemy is attacking",300,100,red);
    } else {
        renderText(renderer,font,"Player turn",300,100,white);
    }

    SDL_Surface* playerHpSurface = TTF_RenderText_Blended(font, playerHpText.c_str(), green);
    SDL_Surface* mobHpSurface = TTF_RenderText_Blended(font, mobHpText.c_str(), white);

    SDL_Texture* playerHpTexture = SDL_CreateTextureFromSurface(renderer, playerHpSurface);
    SDL_Texture* mobHpTexture = SDL_CreateTextureFromSurface(renderer, mobHpSurface);
    SDL_FreeSurface(playerHpSurface);
    SDL_FreeSurface(mobHpSurface);

    SDL_Rect playerHpRect = {100, 150, 0, 0};
    SDL_QueryTexture(playerHpTexture, NULL, NULL, &playerHpRect.w, &playerHpRect.h);
    SDL_RenderCopy(renderer, playerHpTexture, NULL, &playerHpRect);

    SDL_Rect mobHpRect = {400, 150, 0, 0};
    SDL_QueryTexture(mobHpTexture, NULL, NULL, &mobHpRect.w, &mobHpRect.h);
    SDL_RenderCopy(renderer, mobHpTexture, NULL, &mobHpRect);

    SDL_DestroyTexture(playerHpTexture);
    SDL_DestroyTexture(mobHpTexture);

    SDL_RenderPresent(renderer);
}

void StartFight(Board& board, std::shared_ptr<Player> player, std::shared_ptr<Mob> mob,
                SDL_Renderer* renderer, TTF_Font* font,
                SDL_Texture* playerTexture, SDL_Texture* mobTexture) {

    bool isCombatOver = false;
    Turn currentTurn = Turn::PLAYER;

    SDL_Event e;

    while (!isCombatOver) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                exit(0);
            }
        }
        displayCombat(renderer, font, playerTexture, mobTexture, player, mob,currentTurn);

        if (player->getStats().getHp() <= 0 || mob->getStats().getHp() <= 0) {
            isCombatOver = true;
            break;
        }

        // Gestion du tour
        if (currentTurn == Turn::PLAYER) {
            if (is_key_pressed(SDL_SCANCODE_A)) {
                player->attack(mob);
                player->setPlayerProtecting(false);
                currentTurn = Turn::MOB;
            } else if (is_key_pressed(SDL_SCANCODE_P)) {
                player->setPlayerProtecting(true);
                currentTurn = Turn::MOB;
            }
        } else if (currentTurn == Turn::MOB) {
            if (player->isPlayerProtecting()) {
                player->protect(mob->getStats().getAttack());
            } else {
                mob->attackPlayer(player);
            }
            currentTurn = Turn::PLAYER;
            SDL_Delay(3000);
        }
    }
}

//TODO: regler le combat, le delai, l'IG,l'XP et gain de niveau.


