#include <iostream>
#include "SDL2/SDL.h"
#include "game.hpp"

int main(int argc, char** argv)
{
    Game game;
    game.load_image("ball");
    game.load_image("paddle");
    game.run();
    return 0;
}
