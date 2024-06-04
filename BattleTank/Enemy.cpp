#include <iostream>
#include <random>

#include "Enemy.h"
#include "Math.h"

Enemy::Enemy() :
	m_spriteSize(sf::Vector2f(0, 0)),
	m_scale(sf::Vector2f(0, 0)),
	m_movementSpeed(sf::Vector2f(0, 0)),
	m_fireRateTimer(0),
	m_fireRate(0),
	m_direction(0),
	m_directionTimer(0),
	m_directionChangeRate(0),
	m_checkDestroy(0)
{
}

void Enemy::Initialize(const sf::Vector2f& spriteSize, const sf::Vector2f& scale)
{
	m_checkDestroy = 1;

	m_direction = 3;

	m_spriteSize = spriteSize;
	m_scale = scale;
	m_centre = sf::Vector2f(m_spriteSize.x / 2, m_spriteSize.y / 2);
	m_movementSpeed = sf::Vector2f(2, 2);

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
	sf::RenderWindow& window,
	sf::Texture* enemyTextureUp,
	sf::Texture* enemyTextureLeft,
	sf::Texture* enemyTextureDown,
	sf::Texture* enemyTextureRight,
	sf::Texture* bulletTexture,
	const float& deltatimeTimerMilli)
{
	if(m_checkDestroy == 1){

		m_position = m_sprite.getPosition();
		
		if (Math::WindowCollision(window, m_spriteSize, m_scale, m_direction, m_position, m_movementSpeed)) {

			m_direction = (rand() % 4 - 1 + 1) + 1;

			std::cout << "collision" << std::endl;
		}

		if (m_direction == 1) {

			m_sprite.setTexture(*enemyTextureUp);
			m_sprite.setPosition(m_position.x, m_position.y - m_movementSpeed.y);
			m_collisionBox.setPosition(m_position.x, m_position.y - m_movementSpeed.y);
			m_directionTimer = 0;
		}
		else if (m_direction == 2) {

			m_sprite.setTexture(*enemyTextureLeft);
			m_sprite.setPosition(m_position.x - m_movementSpeed.x, m_position.y);
			m_collisionBox.setPosition(m_position.x - m_movementSpeed.x, m_position.y);
			m_directionTimer = 0;
		}
		else if (m_direction == 3) {

			m_sprite.setTexture(*enemyTextureDown);
			m_sprite.setPosition(m_position.x, m_position.y + m_movementSpeed.y);
			m_collisionBox.setPosition(m_position.x, m_position.y + m_movementSpeed.y);
			m_directionTimer = 0;
		}
		else if (m_direction == 4) {

			m_sprite.setTexture(*enemyTextureRight);
			m_sprite.setPosition(m_position.x + m_movementSpeed.x, m_position.y);
			m_collisionBox.setPosition(m_position.x + m_movementSpeed.x, m_position.y);
			m_directionTimer = 0;
		}

		if (m_fireRateTimer >= m_fireRate) {

			m_bullets.push_back(Bullet());
			m_bullets[m_bullets.size() - 1].Initialize(sf::Color::Red, m_direction, bulletTexture, m_position, m_centre);

			m_fireRateTimer = 0;
		}

		for (size_t i = 0; i < m_bullets.size(); ++i) {

			m_bullets[i].Update();
		}

		Math::BulletInMap(window, m_bullets);
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	if (m_checkDestroy == 1) {

		window.draw(m_sprite);
		window.draw(m_collisionBox);

		for (size_t i = 0; i < m_bullets.size(); ++i) {

			m_bullets[i].Draw(window);
		}
	}
}


Enemy::~Enemy()
{
}