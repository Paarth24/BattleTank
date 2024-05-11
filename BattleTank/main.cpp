#include "Resource.h"
#include "Level1.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Battle Tank");
    window.setFramerateLimit(240);

    sf::Clock clock;

    Level1 level1;

    level1.Initialize();

    level1.Load();

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

        level1.Update(window, deltatimeTimerMilli);

        window.clear(sf::Color::Red);
        level1.Draw(window);
        window.display();
    }

    return 0;
}