#include "Resource.h"
#include "Level1.h"
#include "MainMenu.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Battle Tank", sf::Style::Fullscreen);
    window.setFramerateLimit(240);

    sf::Clock clock;
    //--------------------Resources--------------------
    Resource resource;
    resource.Load();
    //--------------------Resources--------------------

    MainMenu mainMenu(resource, sf::Vector2f(1600, 1000));

    mainMenu.Initialize(window);

    mainMenu.Load();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time deltaTimeTimer = clock.restart();
        float deltatimeTimerMilli = deltaTimeTimer.asMilliseconds();

        mainMenu.Update(window, deltatimeTimerMilli);

        window.clear(sf::Color::Black);
        mainMenu.Draw(window);
        window.display();
    }

    return 0;
}