#define SDL_MAIN_HANDLED
#include <iostream>
#pragma once
#include"GameFunction.cpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include "input.cpp"

int main(int argc, char *argv[]) {

	Board board;
	Player* player = new Player(100,50,10,{0,0});
	board.setEntity(BOARD_SIZE/2, BOARD_SIZE/2, player);
    player->addItem(std::make_unique<Weapon>("Sword", 15, ItemType::WEAPON, WeaponType::SWORD));
    player->addItem(std::make_unique<Weapon>("Bow", 10, ItemType::WEAPON, WeaponType::BOW));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("assets/fonts/IMPACT.ttf", 20);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Mini game RPG AlphaTest",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          900, 608, //608x608 pour un plateau de 19x19 avec des tuiles de 32x32
                                          0);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = 1;
			}
		if (is_key_pressed(SDL_SCANCODE_RIGHT)) {
			MoveRight(player, board);
		}
		if (is_key_pressed(SDL_SCANCODE_LEFT)) {
			MoveLeft(player, board);
		}
		if (is_key_pressed(SDL_SCANCODE_UP)) {
			MoveUp(player, board);
		}
		if (is_key_pressed(SDL_SCANCODE_DOWN)) {
			MoveDown(player, board);
		}
		board.DrawBoard(renderer);
		board.DrawInfo(renderer, player);
        board.renderPlayerInfo(renderer,font,player);
		SDL_RenderPresent(renderer);
        SDL_Delay(90);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();


    return 0;
}