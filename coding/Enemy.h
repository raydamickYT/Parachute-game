#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Player.h"

class Enemy
{
public:
    Enemy();
    void SpawnEnemies(float enemiesSpawnedEachRound);
    void Update(float deltaTime);
    void Render(sf::RenderWindow &window);
    void EnemyCollision(Vector2f playerpos);
    void EnemyReset(float enemiesSpawnedEachRound);
    void CheckEnemiesAtBottom(sf::RenderWindow &window);

    float enemyRadius = 50;
    bool gameEnded = false;
    int score = 0;
    int enemiesMissedScore = 0;
    std::vector<Vector2f> enemyPositions;
    std::vector<Vector2f> enemyVelocities;
    std::vector<sf::Sprite> enemies;

private:
    bool enemiesSpawned = false;

    Player playerClass;
    // ParachuteGame GameManager;

    sf::Texture enemyTexture;
    std::vector<Vector2f> enemySwayAccelerations;
    // ... Add other necessary attributes

};

#endif
