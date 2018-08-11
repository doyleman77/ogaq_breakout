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
    for(auto& brick : bricks)
        delete brick;
    for(auto& tex : texture_library)
        SDL_DestroyTexture(tex.second);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}

void Game::handle_input()
{
    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            running = false;

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
            case SDLK_ESCAPE:
                 running = false;
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
    bricks.reserve(20);
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 8; j++)
            bricks.push_back(new Brick(texture_library["brick"], 5+(j*72)+j*8, 32+(i*16)+i*8));
    tick_time = current_time = 0;
    while (running)
    {

        current_time = SDL_GetTicks();
        handle_input();
        /// update
        while(tick_time < current_time)
        {
            tick_time += 16;
            update(1000/16);
        }
        /// draw
        SDL_RenderClear(renderer);
        paddle->draw(renderer);
        ball->draw(renderer);
        for(int i = 0; i < bricks.size(); i++)
            bricks.at(i)->draw(renderer);
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
    for(int i = 0; i < bricks.size(); i++)
        bricks.at(i)->update(delta, ball);
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
