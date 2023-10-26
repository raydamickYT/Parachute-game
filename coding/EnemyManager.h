#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

class ParachuteGame;

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Player.h"
#include "Enemy.h"
class EnemyManager
{
public:
    EnemyManager(ParachuteGame& gameManager);
    void SpawnEnemies(float enemiesSpawnedEachRound);
    void Update(float deltaTime);
    void Render(sf::RenderWindow &window);
    void EnemyCollision(Vector2f playerpos);
    void EnemyReset(float enemiesSpawnedEachRound);
    void CheckEnemiesAtBottom(sf::RenderWindow &window);
    void UpdatePos(float deltaTime);

    //bool gameEnded = false;
    //int score = 0;
    std::vector<Vector2f> enemyPositions;
    std::vector<Vector2f> enemyVelocities;
    std::vector<sf::Sprite> enemies;

    Enemy enemyStats;

private:
    bool enemiesSpawned = false;

    Player playerClass;
    ParachuteGame& gameManager;

    std::vector<Vector2f> enemySwayAccelerations;
    // ... Add other necessary attributes
};

#endif
