#pragma once
#include <SFML/Graphics.hpp>

#include "CustomPhysics.h"

class Entity
{
private:
    /* data */
    sf::RectangleShape rect;

    float movementSpeed = .5f;
    CustomPhysics::Vector2f pos;

public:
    sf::Texture playerText;

    sf::Sprite Player;

    Entity(float x, float y)
    {
        rect.setSize(sf::Vector2f(x, y));
    }
    void DrawTo(sf::RenderWindow &window)
    {
        window.draw(Player);
    }
    void ProcessEvent(bool checkPressed);
    void Update();
    void FindImage();
};
