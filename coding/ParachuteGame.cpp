#include "ParachuteGame.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>

// this will initialise the game window with the name that is between the brackets.
ParachuteGame::ParachuteGame()
    : window(sf::VideoMode(800, 600), "Game & Watch Parachute"),
      playerPosition(Vector2f(100.0f, 400.0f))
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
        CheckEnemiesAtBottom();
        Render();
        ProcessInput();
    }
} 

// this is sort of like the start function in unity. it's only called at the start of the game
void ParachuteGame::Initialize()
{
    SpawnEnemies(enemiesSpawnedEachRound);
    // laad assets, set up game objects, etc.
    if (!playerTexture.loadFromFile("images/Player2.png"))
    {
        std::cout << "could not load the Playerimage" << std::endl;
    }
    if (!BackgroundTexture.loadFromFile("images/Background.png"))
    {
        std::cout << "could not load the backgroundimage" << std::endl;
    }
    if (!GameOverScreen.loadFromFile("images/GameOver.jpg"))
    {
        std::cout << "could not load the backgroundimage" << std::endl;
    }

    // setting up the player sprite so it displays properly
    player.setTexture(playerTexture);

    // setting up the player position to be in the middle (ish) and the scale to be reasonable
    playerPosition = Vector2f(100, 400);
    player.setPosition(playerPosition.x, playerPosition.y);
    player.setScale(1.5, 1.5);

    Background.setTexture(BackgroundTexture);
    Background.setScale(window.getSize().x / BackgroundTexture.getSize().x + .15f, window.getSize().y / BackgroundTexture.getSize().y + .15f);

    GameOver.setTexture(GameOverScreen);
    GameOver.setPosition(window.getSize().x / 15, window.getSize().y / 8);
    GameOver.setScale(window.getSize().x / GameOverScreen.getSize().x + .15f, window.getSize().y / GameOverScreen.getSize().y + .15f);
}

// this is just like the update function in unity. I give it a delta time float since some functions called in here need it.
void ParachuteGame::Update(float deltaTime)
{
    if (enemiesMissedScore >= 3)
    {
        gameEnded = true;
    }
    // Calculate frame time
    sf::Clock clock;
    sf::Time frameTime = clock.restart();
    float frameSeconds = frameTime.asSeconds();
    // Update the enemies position.
    UpdateEnemies(deltaTime);

    // update the player position based on the the frametimes. I used this because I tried to make the player movement a lot smoother, for some reason its not working.
    // I gave up on it since it's not a huge bother and the game works fine without the smooth movement.
    playerPosition += playerVelocity * frameSeconds;
    player.setPosition(playerPosition.x, playerPosition.y);

    // check if the player and enemy are colliding. if true, the enemy will be removed from both the list and the screen.
    //  you can add further logic after that (like score, end game)
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        sf::Sprite &enemy = enemies[i];
        Vector2f enemyPosition(enemy.getPosition().x, enemy.getPosition().y);

        if (Physics::circleCol(playerRadius, playerPosition, enemyRadius, enemyPosition))
        {
            // Collision occurred, handle accordingly
            enemies.erase(enemies.begin() + i);
            enemyPositions.erase(enemyPositions.begin() + i);
            enemyVelocities.erase(enemyVelocities.begin() + i);
            score += 1;
            // ...
        }
    }

    // Update enemy positions
    if (enemies.size() == 0 && !gameEnded)
    {
        // std::cout << enemiesSpawned << std::endl;
        SpawnEnemies(enemiesSpawnedEachRound);
        enemiesSpawned = true;
    }
    else
    {
        enemiesSpawned = false;
    }
}

// script for the player input
void ParachuteGame::ProcessInput()
{
    
    // there was an attempt to make the player speed up and slow down, but due to it's jittery movement it's not really noticable.


    const float acceleration = 2.0f;
    const float deceleration = 5.0f;

    sf::Event event;
    //while (window.pollEvent(event))
    //{
        //std::cout << "window open" << std::endl;
        // close window
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        //else if (event.type == sf::Event::KeyPressed)
        //{
            // movement Left. I used A and D aswell in this case since my keyboard doesn't have arrow keys
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                playerPosition.x -= acceleration;
            }
            // movement Right.
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                playerPosition.x += acceleration;
            }
            else
            {
                if (playerVelocity.x > 0)
                {
                    playerVelocity.x -= deceleration;
                    if (playerVelocity.x < 0)
                    {
                        playerVelocity.x = 0;
                    }
                }
                else if (playerVelocity.x < 0)
                {
                    playerVelocity.x += deceleration;
                    if (playerVelocity.x > 0)
                    {
                        playerVelocity.x = 0;
                    }
                }
            }
        //}
        // make sure the player is within the set screen bounds.
        const float playerWidth = player.getGlobalBounds().width;
        const float screenWidth = window.getSize().x;
        // check if the player is at the left side of the sceen
        if (playerPosition.x < 0.0f)
        {
            // if so, set the player position to 0 (it wont move further the left because of this)
            playerPosition.x = 0.0f;
        }
        // do the same thing but this time on the other side of the screen.
        else if (playerPosition.x > screenWidth - playerWidth)
        {
            playerPosition.x = screenWidth - playerWidth;
        }
    //}
}

// function that is called when I want the game to spawn enemies.
void ParachuteGame::SpawnEnemies(int numEnemies)
{
    // because I want the enemies only to spawn when the last one is gone,
    // I made a bool that is false when there are no enemies on the field and is false when there aree enemies on the field
    enemiesSpawned = true;
    enemyPositions.clear();
    enemyVelocities.clear();

    // Spawn enemies
    for (int i = 0; i < numEnemies; ++i)
    {
        sf::Sprite enemy;
        if (!EnemyTexture.loadFromFile("images/Enemy.png"))
        {
            std::cout << "Could not load the enemy texture" << std::endl;
        }

        enemy.setTexture(EnemyTexture);
        enemy.setScale(1.5f, 1.5f);

        // Generate random position within the screen bounds
        float xPos = rand() % 700;
        float yPos = -100;

        enemy.setPosition(xPos, yPos);

        // Random X/Y velocity between -50 and 49
        //static_cast<> is used to convert a certain value to a different type. in this case a float
        //std::rand() generates a random value between 0-1. by adding % 100 we make that value into a value between 0-99.
        //finally by subtracting 50 we get a value between -50 and 49
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

// this function will update the enemy position.
void ParachuteGame::UpdateEnemies(float deltaTime)
{
    // first it goes through the enemy list
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        // then it calculates a custom velocity for falling down
        const float gravity = 9.8f * 50;
        enemyVelocities[i].y += gravity * deltaTime;
        enemyPositions[i] = enemyPositions[i] + enemyVelocities[i] * deltaTime;


        enemies[i].setPosition(enemyPositions[i].x, enemyPositions[i].y);

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

// this is the function that renders all the sprites/texts
void ParachuteGame::Render()
{
    window.clear();

    if (!gameEnded)
    {
        window.draw(Background);
        window.draw(player);
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
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    sf::Text EnemiesMissedScoreText;
    EnemiesMissedScoreText.setFont(font);
    EnemiesMissedScoreText.setString("Enemies Missed: " + std::to_string(enemiesMissedScore));
    EnemiesMissedScoreText.setCharacterSize(24);
    EnemiesMissedScoreText.setFillColor(sf::Color::Red);
    EnemiesMissedScoreText.setPosition(10, 30);

    // const is used here to indicate that the value of var "enemy" can not be adjusted during the loop. it's basically read only
    // for each iteration in the for loop, "enemy" takes the value of the current element in enemies vector.
    // this for loop will keep going through the enemies list until it reaches the end.
    for (const auto &enemy : enemies)
    {
        window.draw(enemy);
    }

    window.draw(scoreText);
    window.draw(EnemiesMissedScoreText);

    window.display();
}