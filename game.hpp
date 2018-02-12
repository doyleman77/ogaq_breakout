#pragma once
#include <map>

#include "SDL2/SDL.h"
#include "paddle.hpp"
#include "ball.hpp"
#include "brick.hpp"

class Game
{
public:
    Game();
    ~Game();
    void run();

    void load_image(std::string path);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    SDL_Rect screen;

    Paddle* paddle;
    Ball* ball;
    bool running;
    long tick_time, current_time;
    bool left_pressed, right_pressed;
    void update(uint32_t delta);
    void handle_input();

    std::map<std::string, SDL_Texture*> texture_library;
    std::vector<Brick*> bricks;
};
