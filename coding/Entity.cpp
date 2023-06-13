#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Entity.h"
#include "CustomPhysics.h"

void Entity::Update()
{
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
    pos += CustomPhysics::Vector2f(movement.x, 0.0);
    Player.setPosition(pos.x, 800);
    CustomPhysics::Physics::circleCol(50.0f, pos, 50.0f , pos);
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