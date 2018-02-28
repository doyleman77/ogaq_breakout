#pragma once

#include "entity.hpp"
#include "ball.hpp"

class Brick : public Entity
{
public:
    Brick(SDL_Texture* texture, int x, int y);
    ~Brick();
    void update(uint32_t delta, Ball* ball);
    void draw(SDL_Renderer* renderer);
    bool collision_test(Ball* ball);
private:

};
