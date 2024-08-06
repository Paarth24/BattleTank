#include "Enemy.h"

Enemy::Enemy() :
	m_id("id")
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize(
	std::string id,
	const sf::Vector2f* blockOffset,
	const sf::Vector2f* mapBackgroundPosition)
{
	m_id = id;
	m_blockOffset = blockOffset;

	if (m_id == "Basic" || m_id == "LightBattle" || m_id == "DoubleBarrel") {

		m_lives = 1;
	}
	else {

		m_lives = 3;
	}

	m_position = sf::Vector2f(
		3 * m_blockOffset->y + mapBackgroundPosition->x,
		0 * m_blockOffset->x + mapBackgroundPosition->y);

	m_sprite.setPosition(m_position);

	m_direction = "up";
	m_movementSpeed = sf::Vector2f(2, 2);

	m_bulletFireRate = 500;
}

void Enemy::Load(std::string fileName)
{
	if (m_texture.loadFromFile(fileName)) {

		m_sprite.setTexture(m_texture);
	}
}

void Enemy::Update(std::vector<Bullet>& enemyNormalBulletVector, std::vector<Bullet>& enemyArmourBulletVector, float deltaTimerMilli)
{
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
