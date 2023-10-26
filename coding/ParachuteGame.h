#ifndef PARACHUTE_GAME_H
#define PARACHUTE_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Player.h"
#include "EnemyManager.h"

class ParachuteGame
{
public:
    ParachuteGame();
    bool gameEnded = false;
    int score = 0;
    int enemiesMissedScore = 0;

    void Run();

private:
    // setup for all the functions used in this script
    void Render();
    void Initialize();
    void ProcessInput(float dt);
    void Update(float deltaTime);
    void HandleGameOverInput();
    void RestartGame();
    float enemiesSpawnedEachRound = 1;

    bool enemiesSpawned = false;

    Player playerClass;
    EnemyManager enemyClass;

    sf::RenderWindow window;

    sf::Texture BackgroundTexture;
    sf::Sprite Background;
    sf::Texture RestartButtonTexture;
    sf::Sprite RestartButton;
    sf::Texture GameOverScreen;
    sf::Sprite GameOver;
};

#endif
