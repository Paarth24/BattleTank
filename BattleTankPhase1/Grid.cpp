#include "Grid.h"

Grid::Grid(sf::Vector2i gridSize):
	m_gridSize(gridSize),
	m_hLines(nullptr),
	m_vLines(nullptr)
{
}

void Grid::Initialize(
	sf::Vector2f mapBackgroundSize,
	sf::Vector2f mapBackgroundPosition,
	sf::Vector2f blockOffset)
{
	m_hLines = new sf::RectangleShape[m_gridSize.x + 1];
	m_vLines = new sf::RectangleShape[m_gridSize.y + 1];

	for (int i = 0; i < m_gridSize.x + 1; ++i) {

		m_hLines[i].setSize(sf::Vector2f(mapBackgroundSize.x, 1));
		m_hLines[i].setFillColor(sf::Color::Red);
		m_hLines[i].setPosition(sf::Vector2f(mapBackgroundPosition.x, mapBackgroundPosition.y + (blockOffset.x * i)));
	}

	for (int i = 0; i < m_gridSize.y + 1; ++i) {

		m_vLines[i].setSize(sf::Vector2f(1, mapBackgroundSize.y));
		m_vLines[i].setFillColor(sf::Color::Red);
		m_vLines[i].setPosition(sf::Vector2f(mapBackgroundPosition.x + (blockOffset.y * i), mapBackgroundPosition.y));
	}
}

void Grid::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_gridSize.x + 1; ++i) {

		window.draw(m_hLines[i]);
	}

	for (int i = 0; i < m_gridSize.y + 1; ++i) {

		window.draw(m_vLines[i]);
	}
}

Grid::~Grid()
{
	delete[] m_hLines;
	delete[] m_vLines;
}