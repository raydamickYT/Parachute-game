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
    playerPosition += playerVelocity * frameSeconds;
    player.setPosition(playerPosition.x, playerPosition.y);
}

void Player::Render(sf::RenderWindow &window)
{
    window.draw(player);
}

void Player::PlayerInput(float deltaTime, sf::RenderWindow &window)
{
    const float accelerationAmount = 2000.0f;
    const float decelerationAmount = 2500.0f;

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        playerAcceleration.x = -accelerationAmount; // Accelerate to the left
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        playerAcceleration.x = accelerationAmount; // Accelerate to the right
    }
    else
    {
        // decelerate the player when no keys are pressed
        if (playerVelocity.x > 0)
        {
            playerAcceleration.x = -decelerationAmount;
        }
        else if (playerVelocity.x < 0)
        {
            playerAcceleration.x = decelerationAmount;
        }
        else
        {
            playerAcceleration.x = 0;
        }
    }

    // Update velocity and position based on acceleration and velocity.
    // delta time is important here, since we dont want different results on different framerates
    playerVelocity.x += playerAcceleration.x * deltaTime;
    playerPosition.x += playerVelocity.x * deltaTime;

    // check if the player has hit the edges of the playing field
    const float playerWidth = player.getGlobalBounds().width;
    const float screenWidth = window.getSize().x;
    if (playerPosition.x < 0.0f)
    {
        playerPosition.x = 0.0f;
        playerVelocity.x = 0; // stop the player if it hits the left edge
    }
    else if (playerPosition.x > screenWidth - playerWidth)
    {
        playerPosition.x = screenWidth - playerWidth;
        playerVelocity.x = 0; // stop the player if it hits the right edge
    }
}
