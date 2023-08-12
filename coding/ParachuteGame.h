#ifndef PARACHUTE_GAME_H
#define PARACHUTE_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class ParachuteGame
{
public:
    ParachuteGame();


    void Run();

private:
    //setup for all the functions used in this script
    void Render();
    void Initialize();
    void ProcessInput(float dt);
    void CheckEnemiesAtBottom();
    void Update(float deltaTime);
    void SpawnEnemies(int numEnemies);
    void UpdateEnemies(float deltaTime);

    bool gameEnded = false;
    int score = 0;
    int enemiesMissedScore = 0;
    float movementSpeed = 10;
    float enemiesSpawnedEachRound = 1;
    float playerRadius = 20, enemyRadius = 50;
    bool enemiesSpawned = false;

    sf::RenderWindow window;

    sf::Texture playerTexture;
    sf::Sprite player;
    Vector2f playerPosition;
    Vector2f playerAcceleration;
    Vector2f playerVelocity;

    sf::Texture BackgroundTexture;
    sf::Sprite Background;
    sf::Texture GameOverScreen;
    sf::Sprite GameOver;

    sf::Texture EnemyTexture;
    std::vector<sf::Sprite> enemies;
    std::vector<Vector2f> enemyPositions;
    std::vector<Vector2f> enemySwayAccelerations;
    std::vector<Vector2f> enemyVelocities;
};

#endif
