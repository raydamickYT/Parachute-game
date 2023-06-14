#define SDL_MAIN_HANDLED
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "CustomPhysics.h"
#include "Entity.h"
#include "Enemy.h"

#include <chrono>

using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(1ms);


using namespace std;

int main(int argc, char *argv[])
{
    
    using clock = std::chrono::high_resolution_clock;

    std::chrono::nanoseconds lag(0ns);
    auto time_start = clock::now();

    int width = 1920, height = 1080;
    // window setup for width, height and name of the window
    sf::RenderWindow window(sf::VideoMode(width, height), "ParchuteGame Adam Bausch");
    // background color, for when I'm not rendering a background

    sf::Texture background;
    if (!background.loadFromFile("images/Background.png"))
    {
        std::cout << "could not load the image" << std::endl;
        return 0;
    }
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(background);
    backgroundSprite.setScale(window.getSize().x / background.getSize().x + .5f, window.getSize().y / background.getSize().y + .5f);

    Entity player(window.getSize().x / 20, window.getSize().y / 20);
    Enemy enemies(window.getSize().x / 20, window.getSize().y / 20);
    player.FindImage();

    // dit is de update functie van de main script.
    //  alles wordt via deze functie aangeroepen.
    while (window.isOpen())
    {
        auto delta_time = clock::now() - time_start;
        time_start = clock::now();
        lag += std::chrono::duration_cast<std::chrono::milliseconds>(delta_time);
        // playerSprite.move(sf::Vector2f(40, 50));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        while (lag >= timestep)
        {
            lag -= timestep;

            window.clear();
            window.draw(backgroundSprite);

            player.Update();
            player.DrawTo(window);

            enemies.UpdateEnemies();
            enemies.SpawnEnemies(window);
            // window.draw(player.Player);
            window.display();
        }
        // calculate how close or far we are from the next timestep
        auto alpha = (float)lag.count() / timestep.count();
    }
    return 0;
}
