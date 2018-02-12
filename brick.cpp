#include "brick.hpp"

Brick::Brick(SDL_Texture* texture, int x, int y) : Entity(texture)
{
    this->texture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &collision_box.w, &collision_box.h);
    this->x = x;
    this->y = y;
    collision_box.x = x;
    collision_box.y = y;
}

Brick::~Brick()
{

}

bool Brick::collision_test(Ball* other)
{
    SDL_Rect A = get_collision_box();
    SDL_Rect B = other->get_collision_box();

    if(SDL_HasIntersection(&A, &B)) return true;

    else return false;
}

void Brick::update(uint32_t delta, Ball* ball)
{
    //
    if(collision_test(ball))
    {
        /// hit off bottom;
        if(ball->get_collision_box().y + ball->get_collision_box().h > collision_box.y + collision_box.h)
        {
            ///temporary solution to remove;
            collision_box.x += 10000;
            ball->reflect_y();
            return;
        }
        /// hit off top
        if(ball->get_collision_box().y < collision_box.y)
        {
            collision_box.x += 10000;
            ball->reflect_y();
            return;
        }
        /// hit off left
        if(ball->get_collision_box().x < collision_box.x)
        {
            collision_box.x += 10000;
            ball->reflect_x();
            return;
        }
        /// hit off right
        if(ball->get_collision_box().x + ball->get_collision_box().w > collision_box.x + collision_box.w)
        {
            collision_box.x += 10000;
            ball->reflect_x();
            return;
        }
    }
}

void Brick::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &collision_box);
}


