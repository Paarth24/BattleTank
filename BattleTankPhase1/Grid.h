#pragma once
#include <SFML/Graphics.hpp>

class Grid {

private:

	sf::Vector2i m_gridSize;

	sf::RectangleShape* m_hLines;
	sf::RectangleShape* m_vLines;

public:

	Grid(sf::Vector2i gridSize);
	~Grid();

	void Initialize(
		sf::Vector2f mapBackgroundSize,
		sf::Vector2f mapBackgroundPosition,
		sf::Vector2f blockOffset);

	void Draw(sf::RenderWindow& window);
};

