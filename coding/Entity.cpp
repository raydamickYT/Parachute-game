#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <cmath>

#include "Entity.h"
#include "CustomPhysics.h"

void Entity::Update()
{
    RandomNumbers();
    CustomPhysics::Vector2f movement;

    // movement left/right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        // left = true;
        movement.x -= movementSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        // right = true;
        movement.x += movementSpeed;
    }
    playerPos += CustomPhysics::Vector2f(movement.x, 0.0);
    Player.setPosition(playerPos.x, playerPos.y);

    newYPos = newYPos + 0.1;
    enemPos = CustomPhysics::Vector2f(enemPos.x, newYPos);

    if (CustomPhysics::Physics::circleCol(50.0f, enemPos, 50.0f, playerPos))
    {
        std::cout << "there's collision" << std::endl;
    }
}

void Entity::RandomNumbers()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(1, 10);

    std::cout << dist(gen) << std::endl;
}

void Entity::FindImage()
{
    if (!playerText.loadFromFile("images/Player2.png"))
    {
        std::cout << "could not load the image" << std::endl;
    }

    Player.setTexture(playerText);
    Player.setScale(3.5, 3.5);
}
void Entity::DrawTo(sf::RenderWindow &window)
{
    window.draw(Player);
}

// void Entity::Acceleration(CustomPhysics::Vector2f position)
// {
//     float width = 1080;
//     float time = clock.getElapsedTime().asSeconds();

//     if (position.x < width * 0.05f || position.x > width * 0.95f)
//     {
//         movementSpeed = 0.0f;
//         velocity = 0.0f;

//         position.x = (position.x <= (width * 0.05f)) ? (width * 0.05f) + 2.0f : (width * 0.95f) - 2.0f;
//         Player.setPosition(position.x, position.x);

//         return;
//     }

//     if (Force != 0.0f)
//     {
//         float acceleration = Force / Mass;
//         velocity = velocity + (acceleration * time);

//         if (velocity >= 7.0f)
//         {
//             velocity = 7.0f;
//         }
//         if (velocity < -7.0f)
//         {
//             velocity = -7.0f;
//         }
//         MoveSpeedX = velocity;
//     }

//     if (Force == 0.0f)
//     {
//         float deceleration = 0.05f;
//         bool left = velocity < 0;

//         if (left)
//         {
//             velocity = CustomPhysics::Physics<float>::Min(0, velocity + abs(deceleration));
//         }
//         else if (!left && velocity != 0)
//         {
//             velocity = CustomPhysics::Physics<float>::Max(0, velocity - abs(deceleration));
//         }

//         if (velocity >= 7.0f)
//         {
//             velocity = 7.0f;
//         }
//         if (velocity < -7.0f)
//         {
//             velocity = -7.0f;
//         }

//         MoveSpeedX = velocity;
//     }
// }
