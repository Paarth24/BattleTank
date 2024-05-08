#include "Player.h"
#include "Enemy.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Battle Tank");
    window.setFramerateLimit(240);

    sf::Clock clock;

    Player player(sf::Vector2f(70, 70), sf::Vector2f(2, 2));
    Enemy enemy(sf::Vector2f(70, 70), sf::Vector2f(2, 2));

    player.Initialize();
    enemy.Initialize();

    player.Load();
    enemy.Load();

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

        player.Update(deltatimeTimerMilli);
        enemy.Update();

        window.clear(sf::Color::Red);
        player.Draw(window);
        enemy.Draw(window);
        window.display();
    }

    return 0;
}