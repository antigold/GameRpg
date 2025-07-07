#define SDL_MAIN_HANDLED
#include <iostream>
#include "main.hpp"
#include "input.cpp"

int main(int argc, char *argv[]) {

	Board board;
	Player* player = new Player(kDefault_pos);
    Mob* Mob1 = new Mob("Teto",Stats(50,5),kDefault_pos);
    Mob* Mob2 = new Mob("Miku",Stats(50,5),kDefault_pos);
    Item* Sword_ = new Sword("Sword",5,kDefault_pos);
    Item* Bow_ = new Bow("Bow",2,5,kDefault_pos);
    Heal* Heal_ = new Heal("Heal",20,kDefault_pos);

	board.setEntity(Position(kBoardSize/2,kBoardSize/2), player);
    board.setEntity(Position(2,16), Heal_);
    
    Position randomPos = generateRandomPosition(kBoardSize, board);
    Position randomPos2 = generateRandomPosition(kBoardSize, board);
    Position randomPosItem = generateRandomItemPosition(kBoardSize, board);
    Position randomPosBow = generateRandomItemPosition(kBoardSize, board);
    
    board.setEntity(Position(randomPos.getX(),randomPos.getY()), Mob1);
    board.setEntity(Position(randomPos2.getX(), randomPos2.getY()), Mob2);
    board.setEntity(Position(randomPosItem.getX(), randomPosItem.getY()), Sword_);
    board.setEntity(Position(randomPosBow.getX(), randomPosBow.getY()), Bow_);

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

    SDL_Surface* HealSurface = IMG_Load("assets/images/Heal_potion.png");
    if (!HealSurface) {
        std::cerr << "Failed to load heal image: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(MobSurface);
        SDL_FreeSurface(BowSurface);
        SDL_FreeSurface(SwordSurface);
        TTF_CloseFont(font);
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

    SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, PlayerSurface);
    SDL_Texture* swordTexture = SDL_CreateTextureFromSurface(renderer, SwordSurface);
    SDL_Texture* bowTexture = SDL_CreateTextureFromSurface(renderer, BowSurface);
    SDL_Texture* mobTexture = SDL_CreateTextureFromSurface(renderer, MobSurface);
    SDL_Texture* healTexture = SDL_CreateTextureFromSurface(renderer, HealSurface);
    SDL_FreeSurface(PlayerSurface); // libère la surface après avoir créé la texture
    SDL_FreeSurface(SwordSurface);
    SDL_FreeSurface(BowSurface);
    SDL_FreeSurface(MobSurface);
    SDL_FreeSurface(HealSurface);


    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT){
                quit = 1;
            }
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
		board.DrawBoard(renderer, playerTexture,swordTexture,bowTexture,mobTexture,healTexture);
		board.DrawInfo(renderer, player);
        board.renderPlayerInfo(renderer,font,player,board);
		SDL_RenderPresent(renderer);
        SDL_Delay(80);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    delete player;
    delete Mob1;
    delete Mob2;
    delete Sword_;
    delete Bow_;
    delete Heal_;

    return 0;
}