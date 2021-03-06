#include "paddle.hpp"
#include <iostream>


Paddle::Paddle(SDL_Texture* tex) : Entity(tex)
{
    texture = tex;
    SDL_QueryTexture(texture, NULL, NULL, &collision_box.w, &collision_box.h);

    x = collision_box.x = 640/2 - collision_box.w/2;
    y = collision_box.y = 380 - collision_box.h - 16;

    acceleration_x = 1.25f;
    velocity_x = velocity_y = 0.0f;
}

Paddle::~Paddle()
{
}

void Paddle::move(uint32_t delta, const SDL_Rect& screen, int direction)
{
    velocity_x += (acceleration_x/delta) * direction;

    if(velocity_x > 2) velocity_x = 2;
    else if(velocity_x < -2) velocity_x = -2;

    x += velocity_x; //(velocity_x * delta) + (acceleration_x * direction * delta * delta / 2);


    if (x < 0) x = velocity_x = 0;
    if (x > screen.w - collision_box.w)
    {
        x = screen.w - collision_box.w;
        velocity_x = 0;
    }

    velocity_x *= .97; // decay (variable?)
    collision_box.x = (int)x;
    collision_box.y = (int)y;
}

void Paddle::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &collision_box);
}

/// changing this is annoying & therefore broken. fix me.
void Paddle::update(uint32_t delta, const SDL_Rect& screen, int direction)
{
    move(delta, screen, direction);
}

