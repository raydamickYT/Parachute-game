#define SDL_MAIN_HANDLED
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

#include "ParachuteGame.h"
#include "Vector2.h"

int main()
{
    ParachuteGame Game;

    Game.Run();

    return 0;
}