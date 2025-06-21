#define SDL_MAIN_HANDLED
#include <iostream>
#pragma once
#include"GameFunction.cpp"
#include <SDL.h>
#include "input.cpp"

int main(int argc, char *argv[]) {
	Board board;
	Player* player = new Player(100,50,10,{0,0});
	board.setEntity(BOARD_SIZE/2, BOARD_SIZE/2, player);
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Manure game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          608, 608,
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

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
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
		SDL_RenderPresent(renderer);
        SDL_Delay(90);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}