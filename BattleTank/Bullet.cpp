#include "Bullet.h"
#define bulletSpeed 2

Bullet::Bullet() :
	m_position(sf::Vector2f(0, 0)),
	m_playerDirectionCheck(0)
{
}

void Bullet::BulletShootUp()
{
	m_bulletShape.setPosition(m_position.x, m_position.y - bulletSpeed);
}

void Bullet::BulletShootLeft()
{
	m_bulletShape.setPosition(m_position.x - bulletSpeed, m_position.y);
}

void Bullet::BulletShootDown()
{
	m_bulletShape.setPosition(m_position.x, m_position.y + bulletSpeed);
}

void Bullet::BulletShootRight()
{
	m_bulletShape.setPosition(m_position.x + bulletSpeed, m_position.y);
}

void Bullet::Initialize(int& playerDirection)
{
	m_bulletShape.setSize(sf::Vector2f(20, 20));
	m_bulletShape.setFillColor(sf::Color::White);

	m_playerDirectionCheck = playerDirection;
	m_bulletShape.setPosition(100, 100);
}

void Bullet::Load()
{
}

void Bullet::Update()
{	
	m_position = m_bulletShape.getPosition();

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
	window.draw(m_bulletShape);
}


Bullet::~Bullet()
{
}