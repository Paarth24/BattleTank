#include <iostream>

#include "Enemy.h"

Enemy::Enemy(
	const sf::Vector2f& spriteSize,
	const sf::Vector2f& scale
) :
	m_spriteSize(spriteSize),
	m_scale(scale),
	m_fireRateTimer(0),
	m_fireRate(0),
	m_enemyDirection(0)
{
}

void Enemy::Initialize()
{
}

void Enemy::Load()
{
	if (m_textureUp.loadFromFile("assets/enemy/enemyTexture/enemyTankUp.png") &&
		m_textureLeft.loadFromFile("assets/enemy/enemyTexture/enemyTankLeft.png") &&
		m_textureDown.loadFromFile("assets/enemy/enemyTexture/enemyTankDown.png") &&
		m_textureRight.loadFromFile("assets/enemy/enemyTexture/enemyTankRight.png")
		) {

		std::cout << "Enemy loaded successfully" << std::endl;

		m_sprite.setTexture(m_textureUp);
		m_sprite.setTextureRect(sf::IntRect(115, 115, m_spriteSize.x, m_spriteSize.y));
		m_sprite.setScale(m_scale);

		m_collisionBox.setSize(sf::Vector2f(m_spriteSize.x, m_spriteSize.y));
		m_collisionBox.setFillColor(sf::Color::Transparent);
		m_collisionBox.setOutlineColor(sf::Color::Black);
		m_collisionBox.setOutlineThickness(1);

		m_collisionBox.setScale(m_sprite.getScale());
	}
}

void Enemy::Update()
{
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	window.draw(m_collisionBox);
}

Enemy::~Enemy()
{
}