#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Player.h"

class Enemy
{
public:
    Enemy();
    sf::Sprite InstantiateEnemy();

    float enemyRadius = 50;
    float xPos, yPos;

    sf::Texture enemyTexture;

private:
};

#endif
