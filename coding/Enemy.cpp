#include "Enemy.h"
#include "Vector2.h"
#include "Player.h"

#include <iostream>

Enemy::Enemy()
{
    // Initialization logic here...
}
void Enemy::SpawnEnemies(float enemiesSpawnedEachRound)
{
    // because I want the enemies only to spawn when the last one is gone,
    // I made a bool that is false when there are no enemies on the field and is false when there aree enemies on the field
    enemiesSpawned = true;
    enemyPositions.clear();
    enemyVelocities.clear();

    // Spawn enemies
    for (int i = 0; i < enemiesSpawnedEachRound; ++i)
    {
        sf::Sprite enemy;
        if (!enemyTexture.loadFromFile("images/Enemy.png"))
        {
            std::cout << "Could not load the enemy texture" << std::endl;
        }

        enemy.setTexture(enemyTexture);
        enemy.setScale(1.5f, 1.5f);

        // Generate random position within the screen bounds
        float xPos = rand() % 700;
        float yPos = -100;

        enemy.setPosition(xPos, yPos);

        // Random X/Y velocity between -50 and 49
        // static_cast<> is used to convert a certain value to a different type. in this case a float
        // std::rand() generates a random value between 0-1. by adding % 100 we make that value into a value between 0-99.
        // finally by subtracting 50 we get a value between -50 and 49
        float initialVelX = static_cast<float>(std::rand() % 100 - 50);
        float initialVelY = static_cast<float>(std::rand() % 100 - 50);

        // add them to a list to check if they're all dead later
        //  this is where I got stuck.
        // fix: the enemypositions and velocity lists weren't cleared, so every time it went to update all enemies in the list
        // it had to run through 70 or more enemies, causing the enemies not to spawn. Make sure to empty these two out at the start of the function.
        enemies.push_back(enemy);
        enemyPositions.push_back(Vector2f(xPos, yPos));
        enemyVelocities.push_back(Vector2f(initialVelX, initialVelY));
    }
}

void Enemy::Update(float deltaTime)
{
    if (enemiesMissedScore >= 3)
    {
        gameEnded = true;
    }

    // this changes how fast the enemies fall to the ground. Higher is faster
    const float gravity = 9.8f * 30;

    // how far the enemy sways from left to right
    const float swayAmount = 1.0f;
    // how often the enemy sways from left to right
    const float swayFrequency = 6.0f;

    // Stores accumulated time
    static float timeAccumulator = 0.0f;
    timeAccumulator += deltaTime;

    for (size_t i = 0; i < enemies.size(); ++i)
    {
        // Apply gravity for vertical movement
        enemyVelocities[i].y += gravity * deltaTime;

        // sway enemy left and right based on sine wave and accumulated time
        enemyPositions[i].x += swayAmount * sin(swayFrequency * timeAccumulator);

        // Update the enemy's vertical position based on its velocity
        enemyPositions[i].y += enemyVelocities[i].y * deltaTime;

        // Set the new position
        enemies[i].setPosition(enemyPositions[i].x, enemyPositions[i].y);
    }
}

void Enemy::EnemyCollision(Vector2f playerPosition)
{
    // check if the player and enemy are colliding. if true, the enemy will be removed from both the list and the screen.
    //  you can add further logic after that (like score, end game)
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        sf::Sprite &enemy = enemies[i];
        Vector2f enemyPosition(enemy.getPosition().x, enemy.getPosition().y);

        if (Physics::circleCol(playerClass.playerRadius, playerPosition, enemyRadius, enemyPosition))
        {
            // Collision occurred, handle accordingly
            enemies.erase(enemies.begin() + i);
            enemyPositions.erase(enemyPositions.begin() + i);
            enemyVelocities.erase(enemyVelocities.begin() + i);
            score += 1;
        }
    }
}

void Enemy::CheckEnemiesAtBottom(sf::RenderWindow &window)
{
    // check if enemies have reached the bottom and delete them if so
    float screenHeight = window.getSize().y;

    // I used auto here and in other if statements/loops, because it automatically detects and assigns a data type to my variable.
    // this makes it slightly more flexible and easy to handle. This only works with initialized variables.
    //  this for loop works by initialising the var it, then it sets the condition which is if "it" has reached the end of the list.
    //  it'll keep looping till the condition is met.
    for (auto it = enemies.begin(); it != enemies.end();)
    {
        sf::Sprite &enemy = *it;
        // I made a float that gives me the position of the bottom of my enemy, I also subtracted 100 because I thought it looked ugly if they instantly disappear and reappear.
        float enemyBottom = enemy.getPosition().y - 100;

        if (enemyBottom >= screenHeight)
        {
            it = enemies.erase(it);
            enemiesMissedScore += 1;
        }
        else
        {
            // if the enemy hasn't hit the ground, it'll move on to the next enemy in the list.
            ++it;
        }
    }
}

void Enemy::Render(sf::RenderWindow &window)
{
    for (const auto &enemy : enemies)
    {
        window.draw(enemy);
    }
}
