#include "Player.h"
#include "ParachuteGame.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>

Player::Player()
{
    // Initialization logic here...
    if (!playerTexture.loadFromFile("images/Player2.png"))
    {
        std::cout << "could not load the Playerimage" << std::endl;
    }

    // setting up the player sprite so it displays properly
    player.setTexture(playerTexture);

    // setting up the player position to be in the middle (ish) and the scale to be reasonable
    playerPosition = Vector2f(100, 400);
    player.setPosition(playerPosition.x, playerPosition.y);
    player.setScale(1.5, 1.5);
}

void Player::Update(float deltaTime)
{
    sf::Clock clock;
    sf::Time frameTime = clock.restart();
    float frameSeconds = frameTime.asSeconds();

    // Update logic...
    // update the player position based on the the frametimes. I used this because I tried to make the player movement a lot smoother, for some reason its not working.
    // I gave up on it since it's not a huge bother and the game works fine without the smooth movement.
    playerPosition += playerVelocity * deltaTime;
    player.setPosition(playerPosition.x, playerPosition.y);
}

void Player::Render(sf::RenderWindow &window)
{
    window.draw(player);
}

void Player::PlayerInput(float deltaTime, sf::RenderWindow &window)
{
    const float accelerationAmount = 2000.0f;

    // friction
    const float frictionAmount = 1000.0f;

    // forces applied to player
    const float gravity = 0.0f; // Simulating gravity, set to 0 for the player as it's not needed
    const float dragCoefficient = 0.80f;

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

    // Gravity affects vertical velocity
    playerVelocity.y += gravity * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        playerAcceleration.x = -accelerationAmount;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        playerAcceleration.x = accelerationAmount;
    }
    else
    {
        // playerVelocity.x > 0 ? 1 : -1, returns a 1 if playervelocity.x is positive (or exactly 0) and a -1 if it's negative.
        playerAcceleration.x = -frictionAmount * (playerVelocity.x > 0 ? 1 : -1) - dragCoefficient * playerVelocity.x;
    }

    playerAcceleration.x -= dragCoefficient * playerVelocity.x;

    playerVelocity.x += playerAcceleration.x * deltaTime;

    const float playerWidth = player.getGlobalBounds().width;
    const float screenWidth = window.getSize().x;
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
