#include "Grid.h"

Grid::Grid(const sf::Vector2f& size):
	m_size(size + sf::Vector2f(1, 1)),
	m_horizontalLineArray(nullptr),
	m_verticalLineArray(nullptr)
{
}

void Grid::Initialize(sf::RenderWindow& window, const sf::Vector2f* mapOrigin, const sf::Vector2f* mapSize)
{
	m_horizontalLineArray = new sf::RectangleShape[m_size.y];
	m_verticalLineArray = new sf::RectangleShape[m_size.x];

	sf::Vector2u windowSize = window.getSize();
	m_lineOffset = sf::Vector2f(mapSize->x / (m_size.x - 1), mapSize->y / (m_size.y - 1));

	for (size_t i = 0; i < m_size.y; ++i) {

		sf::Vector2f position = sf::Vector2f(mapOrigin->x, i * m_lineOffset.y + mapOrigin->y);

		m_horizontalLineArray[i] = sf::RectangleShape(sf::Vector2f(mapSize->x, 1));
		m_horizontalLineArray[i].setFillColor(sf::Color::Red);
		m_horizontalLineArray[i].setPosition(position);
	}

	for (size_t i = 0; i < m_size.x; ++i) {

		sf::Vector2f position = sf::Vector2f(i * m_lineOffset.x + mapOrigin->x, mapOrigin->y);

		m_verticalLineArray[i] = sf::RectangleShape(sf::Vector2f(1, mapSize->y));
		m_verticalLineArray[i].setFillColor(sf::Color::Red);
		m_verticalLineArray[i].setPosition(position);
	}
}

void Grid::Load()
{
}

void Grid::Update()
{
}

void Grid::Draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < m_size.y; ++i) {

		window.draw(m_horizontalLineArray[i]);
	}

	for (size_t i = 0; i < m_size.x; ++i) {

		window.draw(m_verticalLineArray[i]);
	}
}

Grid::~Grid()
{
	delete[] m_horizontalLineArray;
	delete[] m_verticalLineArray;
}