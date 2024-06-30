#include "Base.h"
#include <iostream>

Base::Base(const sf::Vector2f& size):
	m_scale(sf::Vector2f(0,0)),
	m_spriteSize(size),
	m_position(sf::Vector2f(0, 0))
{
}

void Base::Initialize(
	const sf::Vector2f* mapSize,
	const sf::Vector2f* blockOffset,
	const sf::RenderWindow& window)
{
	m_scale = sf::Vector2f(2 * blockOffset->x / m_spriteSize.x, 2 * blockOffset->y / m_spriteSize.y);

	m_position = sf::Vector2f(
		(window.getSize().x - mapSize->x) / 3 + (mapSize->x / 2) - (m_spriteSize.x * m_scale.x) / 2,
		(window.getSize().y - mapSize->y) / 2 + mapSize->y - (m_spriteSize.y * m_scale.y));

	m_sprite.setScale(m_scale);
	m_sprite.setPosition(m_position);

	m_collisionBox.setSize(sf::Vector2f(m_spriteSize.x * m_scale.x, m_spriteSize.y * m_scale.y));
	m_collisionBox.setFillColor(sf::Color::Transparent);
	m_collisionBox.setOutlineColor(sf::Color::White);
	m_collisionBox.setOutlineThickness(1);
	m_collisionBox.setPosition(m_position);
}

void Base::Load(sf::Texture* birdTexture)
{
	m_sprite.setTexture(*birdTexture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 1500, 1500));
}

void Base::Update()
{
}

void Base::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	window.draw(m_collisionBox);
}

Base::~Base()
{
}