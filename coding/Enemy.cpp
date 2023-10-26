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
        // reason why this is hardcoded right now is because the screen size is aswell. If I were to ever make this into a program with a variable screen size
        // I'd defintely use the actual window size to calc this.
        float xPos = 100 + rand() % 400;
        std::cout << xPos << std::endl;
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

    // Gravity force (increased to compensate for drag)
    const float gravityForce = 9.8f * 60;

    // Drag coefficient
    const float dragCoefficient = 0.5f;

    // Sway force constants
    const float swayAmount = 1000.0f;
    const float swayFrequency = 5.0f;

    // Stores accumulated time
    static float timeAccumulator = 0.0f;
    timeAccumulator += deltaTime;

    for (size_t i = 0; i < enemies.size(); ++i)
    {
        // Apply forces
        Vector2f netForce(0, gravityForce); // start with gravity

        // Sway force (left and right)
        netForce.x = swayAmount * sin(swayFrequency * timeAccumulator);

        // Calculate air friction or drag (opposes the direction of motion)
        Vector2f dragForce = -dragCoefficient * enemyVelocities[i];
        netForce += dragForce;

        // F = ma, or a = F/m. Assuming m=1.
        Vector2f acceleration = netForce;

        // Update velocity based on acceleration
        enemyVelocities[i] += acceleration * deltaTime;

        // Update the enemy's position based on its velocity
        enemyPositions[i] += enemyVelocities[i] * deltaTime;

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

void Enemy::EnemyReset(float enemiesSpawnedEachRound)
{
    enemies.clear();
    enemyVelocities.clear();
    enemyPositions.clear();
    score = 0;
    enemiesMissedScore = 0;
    gameEnded = false;

    // Spawn initial enemies
    SpawnEnemies(enemiesSpawnedEachRound);
}

void Enemy::Render(sf::RenderWindow &window)
{
    for (const auto &enemy : enemies)
    {
        window.draw(enemy);
    }
}
