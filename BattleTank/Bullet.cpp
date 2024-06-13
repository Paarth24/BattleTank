#include "Bullet.h"
#define bulletSpeed 2

Bullet::Bullet() :
	m_position(sf::Vector2f(0, 0)),
	m_playerDirectionCheck(0)
{
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
	int& playerDirection,
	sf::Texture* playerBulletTexture,
	const sf::Vector2f& playerPosition,
	const sf::Vector2f& playerCentre)
{	
	m_bulletSprite.setTexture(*playerBulletTexture);
	m_bulletSprite.setColor(color);
	m_bulletSprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
	m_bulletSprite.setScale(sf::Vector2f(1.4, 1.4));
	m_bulletSprite.setOrigin(sf::Vector2f(21, 21));

	m_collisionBox.setSize(sf::Vector2f(42, 42));
	m_collisionBox.setFillColor(sf::Color::Transparent);
	m_collisionBox.setOutlineColor(sf::Color::White);
	m_collisionBox.setOutlineThickness(1);

	m_playerDirectionCheck = playerDirection;
	m_bulletSprite.setPosition(playerPosition + playerCentre);
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