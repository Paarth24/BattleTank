#include "Bullet.h"
#include <iostream>
#define bulletSpeed 6

Bullet::Bullet() :
	m_position(sf::Vector2f(0, 0)),
	m_spriteSize(sf::Vector2f(30, 30)),
	m_scale(sf::Vector2f(0, 0)),
	m_playerDirectionCheck(0)
{
}

bool Bullet::IfBulletOutOfWindow(const sf::Vector2f* mapOrigin, const sf::Vector2f* mapSize)
{
	if (m_position.x > mapOrigin->x && m_position.x < mapOrigin->x + mapSize->x - m_spriteSize.x * m_scale.x &&
		m_position.y > mapOrigin->y && m_position.y < mapOrigin->y + mapSize->y - m_spriteSize.y * m_scale.y) {
		
		return false;
	}
	else {

		return true;
	}
}

void Bullet::BulletShootUp(const float& deltatimeTimerMilli)
{
	m_bulletSprite.setPosition(m_position.x, m_position.y - bulletSpeed);
	m_collisionBox.setPosition(m_position.x, m_position.y - bulletSpeed);
}

void Bullet::BulletShootLeft(const float& deltatimeTimerMilli)
{
	m_bulletSprite.setPosition(m_position.x - bulletSpeed, m_position.y);
	m_collisionBox.setPosition(m_position.x - bulletSpeed, m_position.y);
}

void Bullet::BulletShootDown(const float& deltatimeTimerMilli)
{
	m_bulletSprite.setPosition(m_position.x, m_position.y + bulletSpeed);
	m_collisionBox.setPosition(m_position.x, m_position.y + bulletSpeed);
}

void Bullet::BulletShootRight(const float& deltatimeTimerMilli)
{
	m_bulletSprite.setPosition(m_position.x + bulletSpeed, m_position.y);
	m_collisionBox.setPosition(m_position.x + bulletSpeed, m_position.y);
}

void Bullet::Initialize(
	const sf::Color& color,
	int& tankDirection,
	sf::Texture* playerBulletTexture,
	const sf::Vector2f& playerPosition,
	const sf::Vector2f* blockOffset,
	const sf::Vector2f& fireCentre)
{	
	m_scale = sf::Vector2f(blockOffset->x / m_spriteSize.x, blockOffset->y / m_spriteSize.y);

	m_bulletSprite.setTexture(*playerBulletTexture);
	m_bulletSprite.setColor(color);
	m_bulletSprite.setTextureRect(sf::IntRect(0, 0, m_spriteSize.x, m_spriteSize.y));
	m_bulletSprite.setScale(m_scale);

	m_collisionBox.setSize(sf::Vector2f(m_spriteSize.x * m_scale.x, m_spriteSize.y* m_scale.y));
	m_collisionBox.setFillColor(sf::Color::Transparent);
	m_collisionBox.setOutlineColor(sf::Color::White);
	m_collisionBox.setOutlineThickness(1);

	m_playerDirectionCheck = tankDirection;

	if (tankDirection == 1) {

		m_position = sf::Vector2f(
			playerPosition.x + fireCentre.x - (m_spriteSize.x * m_scale.x) / 2,
			playerPosition.y + fireCentre.y);

		m_bulletSprite.setPosition(m_position);
	}

	else if (tankDirection == 2) {

		m_position = sf::Vector2f(
			playerPosition.x + fireCentre.x,
			playerPosition.y + fireCentre.y - (m_spriteSize.y * m_scale.y) / 2);

		m_bulletSprite.setPosition(m_position);
	}

	else if (tankDirection == 3) {

		m_position = sf::Vector2f(
			playerPosition.x + fireCentre.x - (m_spriteSize.x * m_scale.x) / 2,
			playerPosition.y + fireCentre.y);

		m_bulletSprite.setPosition(m_position);
	}

	else if (tankDirection == 4) {

		m_position = sf::Vector2f(
			playerPosition.x + fireCentre.x,
			playerPosition.y + fireCentre.y - (m_spriteSize.y * m_scale.y) / 2);

		m_bulletSprite.setPosition(m_position);
	}
}

void Bullet::Load()
{
}

void Bullet::Update(const float& deltatimeTimerMilli)
{	
	m_position = m_bulletSprite.getPosition();

	if (m_playerDirectionCheck == 1) {

		BulletShootUp(deltatimeTimerMilli);
	}

	else if (m_playerDirectionCheck == 2) {

		BulletShootLeft(deltatimeTimerMilli);
	}

	else if (m_playerDirectionCheck == 3) {

		BulletShootDown(deltatimeTimerMilli);
	}

	else if (m_playerDirectionCheck == 4) {

		BulletShootRight(deltatimeTimerMilli);
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(m_bulletSprite);
	window.draw(m_collisionBox);
}



Bullet::~Bullet()
{
}