#include "Player.h"
#include "ParachuteGame.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>

Player::Player()
{
    // Initialization logic
    if (!playerTexture.loadFromFile("images/Player2.png"))
    {
        std::cout << "could not load the Playerimage" << std::endl;
    }

    // setting up the player sprite so it displays properly
    player.setTexture(playerTexture);

    // setting up the player position to be in the middle (ish) and the scale to be reasonable
    playerPosition = initialPlayerPosition;
    player.setPosition(playerPosition.x, playerPosition.y);
    player.setScale(1.5, 1.5);
}

void Player::Update(float deltaTime)
{
    // Update logic
    sf::Clock frameClock;
    sf::Time frameTime = frameClock.restart();
    float frameSeconds = frameTime.asSeconds();

    playerPosition += playerVelocity * deltaTime;
    player.setPosition(playerPosition.x, playerPosition.y);
}

void Player::Render(sf::RenderWindow &window)
{
    window.draw(player);
}
void Player::PlayerReset()
{
    // reset everything
    playerPosition = initialPlayerPosition;
}

void Player::PlayerInput(float deltaTime, sf::RenderWindow &window)
{
    const float accelerationAmount = 2000.0f;

    // player friction
    const float frictionAmount = 1000.0f;

    // forces applied to player
    const float gravity = 0.0f;
    const float dragCoefficient = 0.80f;

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

    // Gravity affects vertical velocity, we don't want it to do that so gravity is set to 0. 
    //but if we wanted to we could use the gravity to drop the player.
    playerVelocity.y += gravity * deltaTime;

    bool leftKey = sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool rightKey = sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    float screenWidth = window.getSize().x;
    float playerWidth = player.getGlobalBounds().width;

    if (leftKey && !rightKey)
    {
        playerAcceleration.x = -accelerationAmount;
    }
    else if (rightKey && !leftKey)
    {
        playerAcceleration.x = accelerationAmount;
    }
    else if (!rightKey && !leftKey)
    {
        //ternary operator, a handy little operator that allows you to return a value within a line
        // > 0 checks if playervelocity is greater than 0. ? starts a sort of if statement, so if it's true: it'll return a 1 else it'll return a -1.
        playerAcceleration.x = -frictionAmount * (playerVelocity.x > 0 ? 1 : -1) - dragCoefficient * playerVelocity.x;
    }

    playerVelocity.x += playerAcceleration.x * deltaTime;

    if (playerPosition.x < 0.0f)
    {
        playerPosition.x = 0.0f;
        playerVelocity.x = 0;
    }
    else if (playerPosition.x > screenWidth - playerWidth)
    {
        playerPosition.x = screenWidth - playerWidth;
        playerVelocity.x = 0;
    }
}
