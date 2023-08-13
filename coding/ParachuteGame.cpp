#include "ParachuteGame.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>

// this will initialise the game window with the name that is between the brackets.
ParachuteGame::ParachuteGame()
    : window(sf::VideoMode(800, 600), "Game & Watch Parachute")
// playerPosition(Vector2f(100.0f, 400.0f))
{
}

void ParachuteGame::Run()
{
    Initialize();
    // I'm using a clock to calculate my delta time
    //  this delta time is later used for physics calculations.
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        float dtSeconds = deltaTime.asSeconds();

        Update(dtSeconds);
        enemyClass.CheckEnemiesAtBottom(window);
        Render();

        playerClass.PlayerInput(dtSeconds, window);
    }
}

// this is sort of like the start function in unity. it's only called at the start of the game
void ParachuteGame::Initialize()
{

    // SpawnEnemies(enemiesSpawnedEachRound);
    enemyClass.SpawnEnemies(enemiesSpawnedEachRound);
    if (!BackgroundTexture.loadFromFile("images/Background.png"))
    {
        std::cout << "could not load the backgroundimage" << std::endl;
    }
    if (!GameOverScreen.loadFromFile("images/GameOver.jpg"))
    {
        std::cout << "could not load the backgroundimage" << std::endl;
    }

    Background.setTexture(BackgroundTexture);
    Background.setScale(window.getSize().x / BackgroundTexture.getSize().x + .15f, window.getSize().y / BackgroundTexture.getSize().y + .15f);

    GameOver.setTexture(GameOverScreen);
    GameOver.setPosition(window.getSize().x / 15, window.getSize().y / 8);
    GameOver.setScale(window.getSize().x / GameOverScreen.getSize().x + .15f, window.getSize().y / GameOverScreen.getSize().y + .15f);
}

// this is just like the update function in unity. I give it a delta time float since some functions called in here need it.
void ParachuteGame::Update(float deltaTime)
{
    playerClass.Update(deltaTime);

    if (enemyClass.enemiesMissedScore >= 3)
    {
        enemyClass.gameEnded = true;
    }
    // Calculate frame time
    sf::Clock clock;
    sf::Time frameTime = clock.restart();
    float frameSeconds = frameTime.asSeconds();
    // Update the enemies position.
    enemyClass.Update(deltaTime);
    enemyClass.EnemyCollision(playerClass.playerPosition);

    // Update enemy positions
    if (enemyClass.enemies.size() == 0 && !enemyClass.gameEnded)
    {
        // std::cout << enemiesSpawned << std::endl;
        enemyClass.SpawnEnemies(enemiesSpawnedEachRound);
        enemiesSpawned = true;
    }
    else
    {
        enemiesSpawned = false;
    }
}

// this function handles all the rendering.
void ParachuteGame::CheckEnemiesAtBottom()
{
    // check if enemies have reached the bottom and delete them if so
    float screenHeight = window.getSize().y;

    // I used auto here and in other if statements/loops, because it automatically detects and assigns a data type to my variable.
    // this makes it slightly more flexible and easy to handle. This only works with initialized variables.
    //  this for loop works by initialising the var it, then it sets the condition which is if "it" has reached the end of the list.
    //  it'll keep looping till the condition is met.
    for (auto it = enemyClass.enemies.begin(); it != enemyClass.enemies.end();)
    {
        sf::Sprite &enemy = *it;
        // I made a float that gives me the position of the bottom of my enemy, I also subtracted 100 because I thought it looked ugly if they instantly disappear and reappear.
        float enemyBottom = enemy.getPosition().y - 100;

        if (enemyBottom >= screenHeight)
        {
            it = enemyClass.enemies.erase(it);
            enemyClass.enemiesMissedScore += 1;
        }
        else
        {
            // if the enemy hasn't hit the ground, it'll move on to the next enemy in the list.
            ++it;
        }
    }
}

// this is the function that renders all the sprites/texts
void ParachuteGame::Render()
{
    window.clear();
    if (!enemyClass.gameEnded)
    {
        window.draw(Background);
        playerClass.Render(window);
    }
    else
    {

        window.draw(GameOver);
    }

    // setup the score font
    sf::Font font;
    if (!font.loadFromFile("Fonts/Minecraft.ttf"))
    {
        std::cout << "Could not load the font" << std::endl;
    }

    // code for the score (how many enemies you've caught)
    // here we set the texture of the text (what'll be displayed basically), the font, what we want to display
    // the text size/ color and where we want it to be displayed
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(enemyClass.score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    sf::Text EnemiesMissedScoreText;
    EnemiesMissedScoreText.setFont(font);
    EnemiesMissedScoreText.setString("Enemies Missed: " + std::to_string(enemyClass.enemiesMissedScore));
    EnemiesMissedScoreText.setCharacterSize(24);
    EnemiesMissedScoreText.setFillColor(sf::Color::Red);
    EnemiesMissedScoreText.setPosition(10, 30);

    // const is used here to indicate that the value of var "enemy" can not be adjusted during the loop. it's basically read only
    // for each iteration in the for loop, "enemy" takes the value of the current element in enemies vector.
    // this for loop will keep going through the enemies list until it reaches the end.
    enemyClass.Render(window);

    window.draw(scoreText);
    window.draw(EnemiesMissedScoreText);

    window.display();
}