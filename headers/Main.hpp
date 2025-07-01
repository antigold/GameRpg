#include <iostream>
#include <vector>
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include "input.cpp"
#include "GameFunction.hpp"
#include "EntitySpawn.hpp"


const std::array<int, 2> DEFAULT_POS = {0, 0};

int SDL_initialization() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    return 0;

    TTF_Font* font = TTF_OpenFont("assets/fonts/IMPACT.ttf", 20);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface* PlayerSurface = IMG_Load("assets/images/Miku_forgor.png");
    if (!PlayerSurface) {
        std::cerr << "Failed to load player image: " << IMG_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface* SwordSurface = IMG_Load("assets/images/minecraft_sword.jpg");
    if (!SwordSurface) {
        std::cerr << "Failed to load sword image: " << IMG_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface* BowSurface = IMG_Load("assets/images/Minecraft_bow.jpg");
    if (!BowSurface) {
        std::cerr << "Failed to load bow image: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(SwordSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface* MobSurface = IMG_Load("assets/images/Fatass.jpg");
    if (!MobSurface) {
        std::cerr << "Failed to load mob image: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(BowSurface);
        SDL_FreeSurface(SwordSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
}


