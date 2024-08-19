#include "MainMenu.h"

int main()
{
    sf::VideoMode windowDimensions = sf::VideoMode::getDesktopMode();
    sf::Vector2u windowResolution = sf::Vector2u(windowDimensions.width, windowDimensions.height);

    sf::RenderWindow window(windowDimensions, "Battle Tank", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::Clock clock;
 
    MainMenu mainMenu(windowResolution);

    mainMenu.Initialize();

    mainMenu.Load();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition();

        sf::Time deltaTimer = clock.restart();

        float deltaTimerMilli = deltaTimer.asMilliseconds();

        mainMenu.Update(mousePosition, deltaTimerMilli, window);

        window.clear();
        mainMenu.Draw(window);
        window.display();
    }

    return 0;
}