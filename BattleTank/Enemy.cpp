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

const void Enemy::TankMoveUp(sf::Texture* enemyTextureUp)
{
	m_sprite.setTexture(*enemyTextureUp);
	m_sprite.setPosition(m_position.x, m_position.y - m_movementSpeed.y);
	m_collisionBox.setPosition(m_position.x, m_position.y - m_movementSpeed.y);
}

const void Enemy::TankMoveLeft(sf::Texture* enemyTextureLeft)
{
	m_sprite.setTexture(*enemyTextureLeft);
	m_sprite.setPosition(m_position.x - m_movementSpeed.x, m_position.y);
	m_collisionBox.setPosition(m_position.x - m_movementSpeed.x, m_position.y);
}

const void Enemy::TankMoveDown(sf::Texture* enemyTextureDown)
{
	m_sprite.setTexture(*enemyTextureDown);
	m_sprite.setPosition(m_position.x, m_position.y + m_movementSpeed.y);
	m_collisionBox.setPosition(m_position.x, m_position.y + m_movementSpeed.y);
}

const void Enemy::TankMoveRight(sf::Texture* enemyTextureRight)
{
	m_sprite.setTexture(*enemyTextureRight);
	m_sprite.setPosition(m_position.x + m_movementSpeed.x, m_position.y);
	m_collisionBox.setPosition(m_position.x + m_movementSpeed.x, m_position.y);
}

void Enemy::Initialize(const sf::Vector2f& spriteSize, const sf::Vector2f& scale)
{
	m_direction = 3;

	m_spriteSize = spriteSize;
	m_scale = scale;
	m_centre = sf::Vector2f(m_spriteSize.x / 2, m_spriteSize.y / 2);

	m_sprite.setPosition(sf::Vector2f(500, 400));
	m_collisionBox.setPosition(sf::Vector2f(500, 400));

	m_fireRate = 500;
	m_position = m_sprite.getPosition();
}

void Enemy::Load(sf::Texture* enemyTextureDown)
{
	m_sprite.setTexture(*enemyTextureDown);
	m_sprite.setTextureRect(sf::IntRect(115, 115, m_spriteSize.x, m_spriteSize.y));
	m_sprite.setScale(m_scale);

	m_collisionBox.setSize(sf::Vector2f(m_spriteSize.x, m_spriteSize.y));
	m_collisionBox.setFillColor(sf::Color::Transparent);
	m_collisionBox.setOutlineColor(sf::Color::White);
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
	const sf::Vector2f* mapSize,
	const float& deltatimeTimerMilli)
{
	if(m_checkDestroy == false){

		m_position = m_sprite.getPosition();
		m_fireRateTimer = m_fireRateTimer + deltatimeTimerMilli;
		
		if (Math::DidSpriteCollideWithMap(
			window,
			mapSize,
			sf::Vector2f(40, 100),
			m_scale,
			m_direction,
			m_position,
			m_movementSpeed)) {

			m_direction = (rand() % 4 - 1 + 1) + 1;
		}

		if (m_direction == 1) {
			
			TankMoveUp(enemyTextureUp);
		}
		else if (m_direction == 2) {

			TankMoveLeft(enemyTextureLeft);
		}
		else if (m_direction == 3) {

			TankMoveDown(enemyTextureDown);
		}
		else if (m_direction == 4) {

			TankMoveRight(enemyTextureRight);
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