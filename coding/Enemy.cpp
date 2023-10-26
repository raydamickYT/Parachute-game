#include "Enemy.h"
#include "Vector2.h"
#include "Player.h"

#include <iostream>

Enemy::Enemy()
{
    // initializing the enemy
    std::cout << "test message" << std::endl;
    if (!enemyTexture.loadFromFile("images/Enemy.png"))
    {
        std::cout << "Could not load the enemy texture" << std::endl;
    }
}
sf::Sprite Enemy::InstantiateEnemy()
{
    sf::Sprite EnemySprite;

    EnemySprite.setTexture(enemyTexture);
    EnemySprite.setScale(1.5f, 1.5f);

    // Generate random position within the screen bounds
    // reason why this is hardcoded right now is because the screen size is aswell. If I were to ever make this into a program with a variable screen size
    // I'd defintely use the actual window size to calc this.
    xPos = 100 + rand() % 400;
    yPos = -100;

    EnemySprite.setPosition(xPos, yPos);
    return EnemySprite;
}
