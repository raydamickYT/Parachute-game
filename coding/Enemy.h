#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <list>

#include "CustomPhysics.h"

class Enemy
{
private:
    /* data */

public:
    std::list<sf::RectangleShape> enemies;

    Enemy(float x, float y)
    {
        //rect.setSize(sf::Vector2f(x, y));
    }
    void MoveEnemies(CustomPhysics::Vector2f position);
    void UpdateEnemies();
    void SpawnEnemies(sf::RenderWindow &window2);
    void DrawTo(sf::RenderWindow &window, sf::RectangleShape enemy);
};
