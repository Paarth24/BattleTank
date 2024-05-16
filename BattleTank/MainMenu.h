#pragma once

#include "SFML/Graphics.hpp"

#include "Resource.h"
#include "Level1.h"

class MainMenu {

public:

	sf::RectangleShape m_playTextClickBox;
	sf::RectangleShape m_exitGameTextClickBox;

private:
	
	Resource m_resource;

	sf::Text m_playText;
	sf::Text m_exitGameText;

	Level1 m_level1;
	bool m_level1Play;

public:

	MainMenu(const Resource& resource);
	~MainMenu();

	void Initialize(const sf::RenderWindow& window);
	void Load();
	void Update(sf::RenderWindow& window, float& deltatimeTimerMilli);
	void Draw(sf::RenderWindow& window);
};