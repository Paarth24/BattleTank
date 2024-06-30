#pragma once

#include "SFML/Graphics.hpp"

#include "Resource.h"
#include "Level1.h"

class MainMenu {

public:

	sf::RectangleShape m_1playerTextClickBox;
	sf::RectangleShape m_2playerTextClickBox;
	sf::RectangleShape m_constructionTextClickBox;

private:
	
	Resource m_resource;

	sf::Text m_gameNameTopText;
	sf::Text m_gameNameBottomText;

	sf::Text m_1playerText;
	sf::Text m_2playerText;
	sf::Text m_constructionText;

	bool m_player1Mode;
	bool m_player2Mode;

	Player1 m_player1;
	Player1 m_player2;

	const sf::Vector2f& m_mapSize;

	Base m_base;

	Level1 m_level1;
	bool m_level1Play;

public:

	MainMenu(const Resource& resource, const sf::Vector2f mapSize);
	~MainMenu();

	void Initialize(sf::RenderWindow& window);
	void Load();
	void Update(sf::RenderWindow& window, float& deltatimeTimerMilli);
	void Draw(sf::RenderWindow& window);
};