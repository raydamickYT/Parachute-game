#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class Player
{
public:
    Player();
    void Update(float deltaTime);
    void Render(sf::RenderWindow &window);
    void PlayerInput(float deltaTime, sf::RenderWindow &window);
    float playerRadius = 20;
    Vector2f playerPosition;
    // ... Add other necessary methods

private:
    sf::Texture playerTexture;
    sf::Sprite player;
    Vector2f playerAcceleration;
    Vector2f playerVelocity;
    // ... Add other necessary attributes
};

#endif
