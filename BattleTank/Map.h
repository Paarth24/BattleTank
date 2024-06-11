#pragma once
#include "SFML/Graphics.hpp"

class Map {

private:

	sf::RectangleShape m_background1;

	sf::RectangleShape m_background2;
	const sf::Vector2f& m_background2Size;

public:

	Map(const sf::Vector2f& background2Size);
	~Map();

	void Initialize(sf::RenderWindow& window);
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);
};

