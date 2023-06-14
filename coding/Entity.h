#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "CustomPhysics.h"

class Entity
{
private:
    /* data */

    float movementSpeed = .5f;
    CustomPhysics::Vector2f pos;

public:
    sf::Texture playerText;
    sf::Clock clock;
    CustomPhysics::Vector2f enemPos = CustomPhysics::Vector2f(100, 200);
    CustomPhysics::Vector2f playerPos = CustomPhysics::Vector2f(0.0, 800);
    float newYPos = enemPos.y;

    sf::Sprite Player;
    Entity(float x, float y)
    {
    }
    void RandomNumbers();
    void Gravity(CustomPhysics::Vector2f);
    void DrawTo(sf::RenderWindow &window);
    void ProcessEvent(bool checkPressed);
    void FindRandomLocation();
    void Update();
    void FindImage();
    void Acceleration(CustomPhysics::Vector2f position);
};
