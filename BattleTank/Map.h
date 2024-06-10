#pragma once
#include "SFML/Graphics.hpp"

class Map {

private:

	sf::RectangleShape m_background1;
	sf::RectangleShape m_background2;

public:

	Map();
	~Map();

	void Initialize(const sf::Vector2f& size);
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);
};

