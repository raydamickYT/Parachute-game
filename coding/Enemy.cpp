#define SDL_MAIN_HANDLED
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <list>
#include "CustomPhysics.h"
#include "Enemy.h"

#include <chrono>

void  Enemy::SpawnEnemies(sf::RenderWindow &window2)
{
    sf::RectangleShape rect;
    float randomInt = rand() % 700;

    CustomPhysics::Vector2f enemPos = CustomPhysics::Vector2f(randomInt, 100);
    //sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(10, 10));
    rect.setPosition(enemPos.x, enemPos.y);
    
    //enemies.insert(enemies.begin(), rect);
    DrawTo(window2, rect);
}

void Enemy::MoveEnemies(CustomPhysics::Vector2f position){
        //position.y += 10;
}

void Enemy::UpdateEnemies()
{
    //SpawnEnemies();
    // update functie voor de enemies
}
void Enemy::DrawTo(sf::RenderWindow &window, sf::RectangleShape enemy)
{
     window.draw(enemy);
}