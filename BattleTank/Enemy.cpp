#include <iostream>
#include <random>

#include "Enemy.h"

Enemy::Enemy() :
	m_spriteSize(sf::Vector2f(0, 0)),
	m_scale(sf::Vector2f(0, 0)),
	m_fireRateTimer(0),
	m_fireRate(0),
	m_direction(0),
	m_directionTimer(0),
	m_directionChangeRate(0)
{
}

void Enemy::Initialize(const sf::Vector2f& spriteSize, const sf::Vector2f& scale)
{
	m_spriteSize = spriteSize;
	m_scale = scale;
	m_centre = sf::Vector2f(35, 35);

	m_sprite.setPosition(sf::Vector2f(500, 400));
	m_collisionBox.setPosition(sf::Vector2f(500, 400));
	m_directionChangeRate = 500;

	m_fireRate = 500;
	m_position = sf::Vector2f(500, 400);
}

void Enemy::Load(sf::Texture* enemyTextureDown)
{
	m_sprite.setTexture(*enemyTextureDown);
	m_sprite.setTextureRect(sf::IntRect(115, 115, m_spriteSize.x, m_spriteSize.y));
	m_sprite.setScale(m_scale);

	m_collisionBox.setSize(sf::Vector2f(m_spriteSize.x, m_spriteSize.y));
	m_collisionBox.setFillColor(sf::Color::Transparent);
	m_collisionBox.setOutlineColor(sf::Color::Black);
	m_collisionBox.setOutlineThickness(1);

	m_collisionBox.setScale(m_sprite.getScale());
}

void Enemy::Update(
	sf::Texture* enemyTextureUp,
	sf::Texture* enemyTextureLeft,
	sf::Texture* enemyTextureDown,
	sf::Texture* enemyTextureRight,
	sf::Texture* bulletTexture,
	const float& deltatimeTimerMilli)
{
	m_directionTimer = m_directionTimer + deltatimeTimerMilli;
	m_fireRateTimer = m_fireRateTimer + deltatimeTimerMilli;

	if (m_directionTimer >= m_directionChangeRate) {

		m_direction = (rand() % 4 - 1 + 1) + 1;

		if (m_direction == 1) {

			m_sprite.setTexture(*enemyTextureUp);
			m_directionTimer = 0;
		}
		else if (m_direction == 2) {

			m_sprite.setTexture(*enemyTextureLeft);
			m_directionTimer = 0;
		}
		else if (m_direction == 3) {

			m_sprite.setTexture(*enemyTextureDown);
			m_directionTimer = 0;
		}
		else if (m_direction == 4) {

			m_sprite.setTexture(*enemyTextureRight);
			m_directionTimer = 0;
		}
	}

	if (m_fireRateTimer >= m_fireRate) {
		
		m_bullets.push_back(Bullet());
		m_bullets[m_bullets.size() - 1].Initialize(sf::Color::Red, m_direction, bulletTexture, m_position, m_centre);

		m_fireRateTimer = 0;
	}

	for (size_t i = 0; i < m_bullets.size(); ++i) {

		m_bullets[i].Update();
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	window.draw(m_collisionBox);

	for (size_t i = 0; i < m_bullets.size(); ++i) {

		m_bullets[i].Draw(window);
	}
}

Enemy::~Enemy()
{
}