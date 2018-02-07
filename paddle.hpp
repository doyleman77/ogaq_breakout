#pragma once
#include "SDL2/SDL.h"
#include "entity.hpp"

class Paddle : public Entity
{
public:
    void update(uint32_t delta, const SDL_Rect& screen, int direction);
    void draw(SDL_Renderer* renderer);

    ///movement handlers
    void move_left();
    void move_right();

    Paddle(SDL_Texture* texture);
    ~Paddle();
private:
    void move(uint32_t delta, const SDL_Rect& screen, int direction);
};
