#include <iostream>
#include <random>

#include "Enemy.h"
#include "Math.h"

Enemy::Enemy(const sf::Vector2f& movementSpeed) :
	m_spriteSize(sf::Vector2f(0, 0)),
	m_scale(sf::Vector2f(0, 0)),
	m_movementSpeed(movementSpeed),
	m_fireRateTimer(0),
	m_fireRate(0),
	m_direction(0),
	m_checkDestroy(false)
{
}

const void Enemy::TankMoveUp(
	const sf::Vector2f* mapOrigin,
	const sf::Vector2f* mapSize,
	sf::Texture* playerTextureUp,
	const float& deltatimeTimerMilli)
{
	m_direction = 1;
	m_sprite.setTexture(*playerTextureUp);

	sf::Vector2f position = sf::Vector2f(m_position.x, m_position.y - m_movementSpeed.y);

	if (position.y > mapOrigin->y && position.y < mapOrigin->y + mapSize->y) {

		m_sprite.setPosition(position);
		m_collisionBox.setPosition(m_position);
	}
	else {

		m_direction = (rand() % 4 - 1 + 1) + 1;
	}
}

const void Enemy::TankMoveLeft(
	const sf::Vector2f* mapOrigin,
	const sf::Vector2f* mapSize,
	sf::Texture* playerTextureLeft,
	const float& deltatimeTimerMilli)
{
	m_direction = 2;
	m_sprite.setTexture(*playerTextureLeft);

	sf::Vector2f position = sf::Vector2f(m_position.x - m_movementSpeed.x, m_position.y);

	if (position.x > mapOrigin->x && position.x < mapOrigin->x + mapSize->x) {

		m_sprite.setPosition(position);
		m_collisionBox.setPosition(m_position);
	}
	else {

		m_direction = (rand() % 4 - 1 + 1) + 1;
	}
}

const void Enemy::TankMoveDown(
	const sf::Vector2f* mapOrigin,
	const sf::Vector2f* mapSize,
	sf::Texture* playerTextureDown,
	const float& deltatimeTimerMilli)
{
	m_direction = 3;
	m_sprite.setTexture(*playerTextureDown);

	sf::Vector2f position = sf::Vector2f(m_position.x, m_position.y + m_movementSpeed.y);

	if (position.y > mapOrigin->y && position.y < mapOrigin->y + mapSize->y - m_spriteSize.y * m_scale.y) {

		m_sprite.setPosition(position);
		m_collisionBox.setPosition(m_position);
	}
	else {

		m_direction = (rand() % 4 - 1 + 1) + 1;
	}

}

const void Enemy::TankMoveRight(
	const sf::Vector2f* mapOrigin,
	const sf::Vector2f* mapSize,
	sf::Texture* playerTextureRight,
	const float& deltatimeTimerMilli)
{
	m_direction = 4;
	m_sprite.setTexture(*playerTextureRight);

	sf::Vector2f position = sf::Vector2f(m_position.x + m_movementSpeed.x, m_position.y);

	if (position.x > mapOrigin->x && position.x < mapOrigin->x + mapSize->x - m_spriteSize.x * m_scale.x) {

		m_sprite.setPosition(position);
		m_collisionBox.setPosition(m_position);
	}
	else {

		m_direction = (rand() % 4 - 1 + 1) + 1;
	}

}

void Enemy::Initialize(
	const sf::Vector2f* mapOrigin,
	const sf::Vector2f* blockOffset,
	const sf::Vector2f& spriteSize)
{
	m_direction = 3;

	m_spriteSize = spriteSize;
	m_scale = sf::Vector2f(2 * blockOffset->x / m_spriteSize.x, 2 * blockOffset->y / m_spriteSize.y);;

	m_fireCentre = sf::Vector2f((m_spriteSize.x * m_scale.x) / 2, m_spriteSize.y * m_scale.y);
	m_position = sf::Vector2f(mapOrigin->x + (2* blockOffset->x), mapOrigin->y + (0 * blockOffset->y));

	m_sprite.setPosition(m_position);
	m_collisionBox.setPosition(m_position);

	m_fireRate = 500;
}

void Enemy::Load(sf::Texture* enemyTextureDown)
{
	m_sprite.setTexture(*enemyTextureDown);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_spriteSize.x, m_spriteSize.y));
	m_sprite.setScale(m_scale);

	m_collisionBox.setSize(sf::Vector2f(m_spriteSize.x * m_scale.x, m_spriteSize.y * m_scale.y));
	m_collisionBox.setFillColor(sf::Color::Transparent);
	m_collisionBox.setOutlineColor(sf::Color::White);
	m_collisionBox.setOutlineThickness(1);
}

void Enemy::Update(
	sf::RenderWindow& window,
	sf::Texture* enemyTextureUp,
	sf::Texture* enemyTextureLeft,
	sf::Texture* enemyTextureDown,
	sf::Texture* enemyTextureRight,
	sf::Texture* bulletTexture,
	const sf::Vector2f* mapSize,
	const sf::Vector2f* blockOffset,
	const float& deltatimeTimerMilli)
{
	if(m_checkDestroy == false){

		sf::Vector2u windowSize = window.getSize();
		sf::Vector2f mapOrigin = sf::Vector2f((windowSize.x - mapSize->x) / 3, (windowSize.y - mapSize->y) / 2);

		m_position = m_sprite.getPosition();
		m_fireRateTimer = m_fireRateTimer + deltatimeTimerMilli;

		if (m_direction == 1) {
			
			m_fireCentre = sf::Vector2f((m_spriteSize.x * m_scale.x) / 2, 0);
			TankMoveUp(&mapOrigin, mapSize, enemyTextureUp, deltatimeTimerMilli);
		}
		else if (m_direction == 2) {

			m_fireCentre = sf::Vector2f(0, (m_spriteSize.y * m_scale.y) / 2);
			TankMoveLeft(&mapOrigin, mapSize, enemyTextureLeft, deltatimeTimerMilli);
		}
		else if (m_direction == 3) {

			m_fireCentre = sf::Vector2f((m_spriteSize.x * m_scale.x) / 2, m_spriteSize.y * m_scale.y);
			TankMoveDown(&mapOrigin, mapSize, enemyTextureDown, deltatimeTimerMilli);
		}
		else if (m_direction == 4) {

			m_fireCentre = sf::Vector2f(m_spriteSize.x * m_scale.x, (m_spriteSize.y * m_scale.y) / 2);
			TankMoveRight(&mapOrigin, mapSize, enemyTextureRight, deltatimeTimerMilli);
		}

		if (m_fireRateTimer >= m_fireRate) {

			m_bullets.push_back(Bullet());
			m_bullets[m_bullets.size() - 1].Initialize(sf::Color::Red, m_direction, bulletTexture, m_position, blockOffset, m_fireCentre);

			m_fireRateTimer = 0;
		}

		for (size_t i = 0; i < m_bullets.size(); ++i) {

			if (!m_bullets[i].IfBulletOutOfWindow(&mapOrigin, mapSize)) {

				m_bullets[i].Update(deltatimeTimerMilli);
			}
			else {
				m_bullets.erase(m_bullets.begin() + i);
			}
		}
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	if (m_checkDestroy == false) {

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