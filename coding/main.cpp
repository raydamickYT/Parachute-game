#include <iostream>
#include <SFML/Graphics.hpp>
#include "CustomPhysics.h"

#include "Entity.h"

int main()
{
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

    Entity player(window.getSize().x / 4, window.getSize().y / 4);
    player.FindImage();

    // dit is de update functie van de main script.
    //  alles wordt via deze functie aangeroepen.
    while (window.isOpen())
    {
        // playerSprite.move(sf::Vector2f(40, 50));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(backgroundSprite);
        player.Update();
        player.DrawTo(window);
        // window.draw(player.Player);
        window.display();
    }
    return 0;
}
