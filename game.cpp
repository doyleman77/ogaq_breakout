#include "game.hpp"
#include <iostream>

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    screen.w = 640;
    screen.h = 380;


    window = SDL_CreateWindow("OGAQ Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen.w, screen.h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    running = true;
    right_pressed = left_pressed = false;
}

Game::~Game()
{
    delete paddle;
    delete ball;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}

void Game::handle_input()
{
    /// right_pressed = left_pressed = false;
    while (SDL_PollEvent(&event))
    {
        if((event.type == SDL_QUIT) ||
            (event.key.keysym.sym == SDLK_ESCAPE)) running = false;

        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                right_pressed = true;
                break;
            case SDLK_LEFT:
                left_pressed = true;
                break;
            default:
                break;
            }
        }
        else if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                right_pressed = false;
                break;
            case SDLK_LEFT:
                left_pressed = false;
                break;
            }
        }
    }
}

void Game::run()
{
    paddle = new Paddle(texture_library["paddle"]);
    ball = new Ball(texture_library["ball"]);

    tick_time = current_time = 0;
    while (running)
    {

        current_time = SDL_GetTicks();
        handle_input();
        /// update
        while(tick_time < current_time)
        {
            tick_time += 16;
            update(16);
        }
        /// draw
        //clear!
        SDL_RenderClear(renderer);
        paddle->draw(renderer);
        ball->draw(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
}


void Game::update(uint32_t delta)
{

    /// SDL_Delay(16);
    /// update
    int direction = right_pressed - left_pressed;
    paddle->update(delta, screen, direction);
    ball->update(delta, screen, *paddle);

}

void Game::load_image(std::string name)
{
    std::string path = "bin/Debug/assets/images/";
    std::string extension = ".bmp";
    std::string full_path = path + name + extension;
    SDL_Surface* surf = SDL_LoadBMP(full_path.c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_FreeSurface(surf);

    if(!texture_library[name]) texture_library[name] = tex;
    else std::cout <<  "texture name already exists!" << std::endl;
}