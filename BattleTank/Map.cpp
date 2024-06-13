#include "Map.h"

Map::Map(const sf::Vector2f& background2Size):
	m_background2Size(background2Size),
	m_grid(sf::Vector2f(25, 25)),
	m_blockOffset(sf::Vector2f(m_background2Size.x / 25, m_background2Size.y / 25)),
	m_mapOrigin(sf::Vector2f(0, 0))
{
}

void Map::Initialize(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();
	m_mapOrigin = sf::Vector2f((windowSize.x - m_background2Size.x) / 3, (windowSize.y - m_background2Size.y) / 2);

	m_background1.setSize(sf::Vector2f(windowSize.x, windowSize.y));
	m_background1.setFillColor(sf::Color(128, 128, 128));
	m_background1.setPosition(sf::Vector2f(0, 0));

	m_background2.setSize(m_background2Size);
	m_background2.setFillColor(sf::Color::Black);
	m_background2.setPosition(m_mapOrigin);

	m_grid.Initialize(window, &m_mapOrigin, &m_background2Size);
}

void Map::Load()
{
	m_grid.Load();
}

void Map::Update()
{
	m_grid.Update();
}

void Map::Draw(sf::RenderWindow& window)
{
	window.draw(m_background1);
	window.draw(m_background2);
	m_grid.Draw(window);
}

Map::~Map()
{
}