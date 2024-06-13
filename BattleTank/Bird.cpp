#include "Bird.h"
#include <iostream>

Bird::Bird(const sf::Vector2f& scale, const sf::Vector2f& size):
	m_scale(scale),
	m_size(size),
	m_position(sf::Vector2f(0, 0))
{
}

void Bird::Initialize(const sf::Vector2f* mapSize, const sf::RenderWindow& window)
{
	m_position = sf::Vector2f(
		(window.getSize().x - mapSize->x) / 3 + (mapSize->x / 2) - m_size.x / 2,
		(window.getSize().y - mapSize->y) / 2 + mapSize->y - m_size.y);

	m_sprite.setScale(m_scale);
	m_sprite.setPosition(m_position);

	m_collisionBox.setSize(m_size);
	m_collisionBox.setFillColor(sf::Color::Transparent);
	m_collisionBox.setOutlineColor(sf::Color::White);
	m_collisionBox.setOutlineThickness(1);
	m_collisionBox.setPosition(m_position);
}

void Bird::Load(sf::Texture* birdTexture)
{
	m_sprite.setTexture(*birdTexture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 1500, 1500));
}

void Bird::Update()
{
}

void Bird::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	window.draw(m_collisionBox);
}

Bird::~Bird()
{
}