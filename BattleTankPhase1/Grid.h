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

	void Initialize(const sf::Vector2f& blockOffset, const sf::Vector2f& mapBackgroundSize, const sf::Vector2f& mapBackgroundPosition);
	void Draw(sf::RenderWindow& window);
};

