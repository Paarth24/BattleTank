#include "Resource.h"
#include "Level1.h"
#include "MainMenu.h"

#include <iostream>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Battle Tank", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    sf::Clock clock;
    //--------------------Resources--------------------
    Resource resource;
    resource.Load();
    //--------------------Resources--------------------

    MainMenu mainMenu(resource, sf::Vector2f(int(0.43334 * sf::VideoMode::getDesktopMode().width), int(0.7703704 * sf::VideoMode::getDesktopMode().height)));
    mainMenu.Initialize(window);

    mainMenu.Load();

    while (window.isOpen())
    {
        sf::Time deltaTimeTimer = clock.restart();
        float deltatimeTimerMilli = deltaTimeTimer.asMilliseconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        mainMenu.Update(window, deltatimeTimerMilli);

        window.clear(sf::Color::Black);
        mainMenu.Draw(window);
        window.display();
    }

    return 0;
}