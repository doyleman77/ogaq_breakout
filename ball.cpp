#include "ball.hpp"
#include <iostream>


Ball::Ball(SDL_Texture* tex) : Entity(tex)
{
    std::default_random_engine re{time(nullptr)};
    std::uniform_real_distribution<> dist(-1,1);

    acceleration_x = acceleration_y = velocity_x = velocity_y = 0;

    texture = tex;
    SDL_QueryTexture(texture, NULL, NULL, &collision_box.w, &collision_box.h);

    x = collision_box.x = 640/2 - collision_box.w/2;
    y = collision_box.y = 380/2 - collision_box.h/2;
    acceleration_x = dist(re)/16.0;
    acceleration_y = dist(re)/16.0;

    acceleration_x = 0.01;
    acceleration_y = -0.005;
    std::cout << acceleration_x << " " << acceleration_y << std::endl;
}

Ball::~Ball()
{
}


void Ball::move(uint32_t delta, const SDL_Rect& screen, Paddle& paddle)
{
    x += (velocity_x * delta) + (acceleration_x * delta * delta / 2);
    y += (velocity_y * delta) + (acceleration_y * delta * delta / 2);

    if (x < 0) acceleration_x = -acceleration_x;
    if (x > screen.w - collision_box.w)
    {
        acceleration_x = -acceleration_x;
    }
    if (y < 0) acceleration_y = -acceleration_y;
    if (y > screen.h - collision_box.h)
    {
        acceleration_y = -acceleration_y;
    }

    collision_box.x = (int)x;
    collision_box.y = (int)y;

    SDL_Rect other = paddle.get_collision_box();

    if( SDL_HasIntersection(&collision_box, &other) )
    {
        acceleration_y *= -1;


        acceleration_x += paddle.get_velocity_x()/16; /// this will be changed by pixels/second
        acceleration_y += paddle.get_velocity_y()/16;
        std::cout << "Hurray!" << " " << acceleration_x << std::endl;

    }
}

void Ball::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &collision_box);
}

// changing this is annoying & therefore broken. fix me.
void Ball::update(uint32_t delta, const SDL_Rect& screen, Paddle& paddle)
{
    move(delta, screen, paddle);
}

bool Ball::collision_test()
{


}

void Ball::reflect_x()
{
    acceleration_x *= -1;
}

void Ball::reflect_y()
{
    acceleration_y *= -1;
}
