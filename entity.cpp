#include "entity.hpp"

Entity::Entity(SDL_Texture* texture)
{


}

Entity::~Entity()
{
}

void Entity::update(uint32_t delta, const SDL_Rect& screen)
{


}

void Entity::draw(SDL_Renderer* renderer)
{


}

void Entity::move(uint32_t delta, const SDL_Rect& screen)
{

}

bool Entity::collision_test()
{

}

SDL_Rect Entity::get_collision_box()
{
    return collision_box;
}

float Entity::get_velocity_x()
{
    return velocity_x;
}

float Entity::get_velocity_y()
{
    return velocity_y;
}
