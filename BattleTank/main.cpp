#include "Player.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Battle Tank");
    window.setFramerateLimit(240);

    Player player(sf::Vector2i(2, 2));

    player.Initialize();

    player.Load();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.Update();

        window.clear(sf::Color::Red);
        player.Draw(window);
        window.display();
    }

    return 0;
}