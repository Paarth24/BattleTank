#include "Map.h"

Map::Map(const sf::Vector2f& background2Size):
	m_background2Size(background2Size)
{
}

void Map::Initialize(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();

	m_background1.setSize(sf::Vector2f(windowSize.x, windowSize.y));
	m_background1.setFillColor(sf::Color(128, 128, 128));
	m_background1.setPosition(sf::Vector2f(0, 0));

	m_background2.setSize(m_background2Size);
	m_background2.setFillColor(sf::Color::Black);
	m_background2.setPosition(sf::Vector2f((windowSize.x - m_background2Size.x) / 3, (windowSize.y - m_background2Size.y) / 2));
}

void Map::Load()
{
}

void Map::Update()
{
}

void Map::Draw(sf::RenderWindow& window)
{
	window.draw(m_background1);
	window.draw(m_background2);
}

Map::~Map()
{
}