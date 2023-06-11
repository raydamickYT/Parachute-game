#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
private:
    /* data */
    sf::RectangleShape rect;
    float movementSpeed = .5f;

public:
    Entity(float x, float y)
    {
        rect.setSize(sf::Vector2f(x, y));
    }
    void DrawTo(sf::RenderWindow &window)
    {
        window.draw(rect);
    }
    void ProcessEvent(bool checkPressed)
    {

    }
    void Update()
    {
        sf::Vector2f movement;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            // up = true;
            movement.y -= movementSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            // left = true;
            movement.x -= movementSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            // down = true;
            movement.y += movementSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            // right = true;
            movement.x += movementSpeed;
        }
        rect.move(movement);
    }
};
