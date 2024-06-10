#include "Map.h"

Map::Map()
{
}

void Map::Initialize(const sf::Vector2f& size)
{
	m_background1.setSize(sf::Vector2f(1920, 1080));
	m_background1.setFillColor(sf::Color(128, 128, 128));
	m_background1.setPosition(sf::Vector2f(0, 0));

	m_background2.setSize(size);
	m_background2.setFillColor(sf::Color::Black);
	m_background2.setPosition(sf::Vector2f((1920 - size.x) / 3, (1080 - size.y) / 2));
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