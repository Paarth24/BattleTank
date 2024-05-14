#include "Bird.h"
#include <iostream>

Bird::Bird()
{
}

void Bird::Initialize(const sf::RenderWindow& window)
{
	m_sprite.setScale(sf::Vector2f(0.134, 0.134));
	m_sprite.setPosition(sf::Vector2f(window.getSize().x/2 - 100, window.getSize().y - 200));

	m_collisionBox.setSize(sf::Vector2f(200, 200));
	m_collisionBox.setFillColor(sf::Color::Transparent);
	m_collisionBox.setOutlineColor(sf::Color::Black);
	m_collisionBox.setOutlineThickness(1);
	m_collisionBox.setPosition(sf::Vector2f(window.getSize().x/2 - 100, window.getSize().y - 200));
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