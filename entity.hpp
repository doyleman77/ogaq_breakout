#pragma once
#include "SDL2/SDL.h"

class Entity
{
public:
    Entity(SDL_Texture* texture);
    virtual ~Entity();

    virtual void update(uint32_t delta, const SDL_Rect& screen);
    virtual void draw(SDL_Renderer* renderer);
    virtual bool collision_test();


    SDL_Rect get_collision_box();
    float get_velocity_x();
    float get_velocity_y();

protected:
    virtual void move(uint32_t delta, const SDL_Rect& screen);

    float x, y;
    float acceleration_x, acceleration_y;
    float velocity_x, velocity_y;


    SDL_Rect collision_box;
    SDL_Texture* texture;
};

