#ifndef PARACHUTE_GAME_H
#define PARACHUTE_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Player.h"
#include "Enemy.h"

class ParachuteGame
{
public:
    ParachuteGame();

    void Run();
    //int score = 0;
    //int enemiesMissedScore = 0;
    //bool gameEnded = false;

private:
    // setup for all the functions used in this script
    void Render();
    void Initialize();
    void ProcessInput(float dt);
    void CheckEnemiesAtBottom();
    void Update(float deltaTime);
    void SpawnEnemies(int numEnemies);
    float enemiesSpawnedEachRound = 1;
    void UpdateEnemies(float deltaTime);

    float movementSpeed = 10;
    float enemyRadius = 50;
    bool enemiesSpawned = false;

    Player playerClass;
    Enemy enemyClass;
    
    sf::RenderWindow window;

    sf::Texture BackgroundTexture;
    sf::Sprite Background;
    sf::Texture GameOverScreen;
    sf::Sprite GameOver;
};

#endif
