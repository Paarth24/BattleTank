#include "Bullet.h"
#include <iostream>
#define bulletSpeed 2

Bullet::Bullet() :
	m_position(sf::Vector2f(0, 0)),
	m_size(sf::Vector2f(30, 30)),
	m_scale(sf::Vector2f(1.428, 1.5)),
	m_playerDirectionCheck(0)
{
}

bool Bullet::IfBulletOutOfWindow(const sf::Vector2f* mapOrigin, const sf::Vector2f* mapSize)
{
	if (m_position.x > mapOrigin->x && m_position.x < mapOrigin->x + mapSize->x - m_size.x * m_scale.x &&
		m_position.y > mapOrigin->y && m_position.y < mapOrigin->y + mapSize->y - m_size.y * m_scale.y) {
		
		return false;
	}
	else {

		return true;
	}
}

void Bullet::BulletShootUp()
{
	m_bulletSprite.setPosition(m_position.x, m_position.y - bulletSpeed);
	m_collisionBox.setPosition(m_position.x, m_position.y - bulletSpeed);
}

void Bullet::BulletShootLeft()
{
	m_bulletSprite.setPosition(m_position.x - bulletSpeed, m_position.y);
	m_collisionBox.setPosition(m_position.x - bulletSpeed, m_position.y);
}

void Bullet::BulletShootDown()
{
	m_bulletSprite.setPosition(m_position.x, m_position.y + bulletSpeed);
	m_collisionBox.setPosition(m_position.x, m_position.y + bulletSpeed);
}

void Bullet::BulletShootRight()
{
	m_bulletSprite.setPosition(m_position.x + bulletSpeed, m_position.y);
	m_collisionBox.setPosition(m_position.x + bulletSpeed, m_position.y);
}

void Bullet::Initialize(
	const sf::Color& color,
	int& tankDirection,
	sf::Texture* playerBulletTexture,
	const sf::Vector2f& playerPosition,
	const sf::Vector2f& fireCentre)
{	
	m_bulletSprite.setTexture(*playerBulletTexture);
	m_bulletSprite.setColor(color);
	m_bulletSprite.setTextureRect(sf::IntRect(0, 0, m_size.x, m_size.y));
	m_bulletSprite.setScale(m_scale);

	m_collisionBox.setSize(sf::Vector2f(m_size.x * m_scale.x, m_size.y* m_scale.y));
	m_collisionBox.setFillColor(sf::Color::Transparent);
	m_collisionBox.setOutlineColor(sf::Color::White);
	m_collisionBox.setOutlineThickness(1);

	m_playerDirectionCheck = tankDirection;

	if (tankDirection == 1) {

		m_position = sf::Vector2f(
			playerPosition.x + fireCentre.x - (m_size.x * m_scale.x) / 2,
			playerPosition.y + fireCentre.y);

		m_bulletSprite.setPosition(m_position);
	}

	else if (tankDirection == 2) {

		m_position = sf::Vector2f(
			playerPosition.x + fireCentre.x,
			playerPosition.y + fireCentre.y - (m_size.y * m_scale.y) / 2);

		m_bulletSprite.setPosition(m_position);
	}

	else if (tankDirection == 3) {

		m_position = sf::Vector2f(
			playerPosition.x + fireCentre.x - (m_size.x * m_scale.x) / 2,
			playerPosition.y + fireCentre.y);

		m_bulletSprite.setPosition(m_position);
	}

	else if (tankDirection == 4) {

		m_position = sf::Vector2f(
			playerPosition.x + fireCentre.x,
			playerPosition.y + fireCentre.y - (m_size.y * m_scale.y) / 2);

		m_bulletSprite.setPosition(m_position);
	}
}

void Bullet::Load()
{
}

void Bullet::Update()
{	
	m_position = m_bulletSprite.getPosition();

	if (m_playerDirectionCheck == 1) {

		BulletShootUp();
	}

	else if (m_playerDirectionCheck == 2) {

		BulletShootLeft();
	}

	else if (m_playerDirectionCheck == 3) {

		BulletShootDown();
	}

	else if (m_playerDirectionCheck == 4) {

		BulletShootRight();
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