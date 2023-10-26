#include "ParachuteGame.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>

// this will initialise the game window with the name that is between the brackets.
ParachuteGame::ParachuteGame()
    : window(sf::VideoMode(800, 600), "Game & Watch Parachute")
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

        if (enemyClass.gameEnded)
        {
            HandleGameOverInput();
        }
        else
        {
            playerClass.PlayerInput(dtSeconds, window);
        }
    }
}

// this is sort of like the start function in unity. it's only called at the start of the game
void ParachuteGame::Initialize()
{
    enemyClass.SpawnEnemies(enemiesSpawnedEachRound);
    if (!BackgroundTexture.loadFromFile("images/Background.png"))
    {
        std::cout << "could not load the backgroundimage" << std::endl;
    }
    if (!GameOverScreen.loadFromFile("images/GameOver.jpg"))
    {
        std::cout << "could not load the backgroundimage" << std::endl;
    }
    if (!RestartButtonTexture.loadFromFile("images/Restart.png"))
    {
        std::cout << "could not load the RestartButton image" << std::endl;
    }

    Background.setTexture(BackgroundTexture);
    Background.setScale(window.getSize().x / BackgroundTexture.getSize().x + .15f, window.getSize().y / BackgroundTexture.getSize().y + .15f);

    GameOver.setTexture(GameOverScreen);
    GameOver.setPosition(window.getSize().x / 15, window.getSize().y / 8);
    GameOver.setScale(window.getSize().x / GameOverScreen.getSize().x + .15f, window.getSize().y / GameOverScreen.getSize().y + .15f);

    RestartButton.setTexture(RestartButtonTexture);
    RestartButton.setScale(.2, .2);
    RestartButton.setPosition(window.getSize().x / BackgroundTexture.getSize().x, window.getSize().y- 100);
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
    enemyClass.Update(deltaTime);
    enemyClass.EnemyCollision(playerClass.playerPosition);

    // Update enemy positions
    if (enemyClass.enemies.size() == 0 && !enemyClass.gameEnded)
    {
        enemyClass.SpawnEnemies(enemiesSpawnedEachRound);
        enemiesSpawned = true;
    }
    else
    {
        enemiesSpawned = false;
    }
}
void ParachuteGame::HandleGameOverInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {

        // Check for button click
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (RestartButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
            {
                std::cout << "test" << std::endl;
                RestartGame();
            }
        }
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
    {
        RestartGame();
    }
}
void ParachuteGame::RestartGame()
{
    enemyClass.EnemyReset(enemiesSpawnedEachRound);
    playerClass.PlayerReset();                  
    enemyClass.gameEnded = false;
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
        window.draw(RestartButton);
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