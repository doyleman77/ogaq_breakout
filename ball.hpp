#pragma once
#include <ctime>
#include <random>

#include "SDL2/SDL.h"
#include "entity.hpp"
#include "paddle.hpp"


class Ball : public Entity
{
public:
    /// refactor during abstraction with ball/paddle as entities
    void update(uint32_t delta, const SDL_Rect& screen, Paddle& paddle);
    void draw(SDL_Renderer* renderer);
    bool collision_test();
    Ball(SDL_Texture* texture);
    ~Ball();
private:
    void move(uint32_t delta, const SDL_Rect& screen, Paddle& paddle);
};
