#pragma once
#include "SFML/Graphics.hpp"

class Grid {

private:

	sf::Vector2i m_size;

	sf::RectangleShape* m_verticalLineArray;
	sf::RectangleShape* m_horizontalLineArray;

	sf::Vector2f m_lineOffset;

public:

	Grid(const sf::Vector2i& size);
	~Grid();

	void Initialize(sf::RenderWindow& window, const sf::Vector2f* mapOrigin, const sf::Vector2f* mapSize);
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);

	inline const sf::Vector2i* GetSizeOfGrid() const { return &m_size; } 
};

