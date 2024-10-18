#include "Enemy.h"

Enemy::Enemy() :
	m_checkDestroy(false),
	m_spawned(false),
	m_spawnRate(0),
	m_spawnTimer(0),
	m_id(""),
	m_blockOffset(nullptr),
	m_lives(0),
	m_scale(sf::Vector2f(0, 0)),
	m_position(sf::Vector2f(0, 0)),
	m_direction(""),
	m_movementSpeed(sf::Vector2f(0, 0)),
	m_collisionUp(false),
	m_collisionLeft(false),
	m_collisionDown(false),
	m_collisionRight(false),
	m_directionRate(0),
	m_directionTimer(0),
	m_bulletFireRate(0),
	m_bulletFireTimer(0),
	m_collisionWithIce(false),
	m_freeze(false),
	m_freezeTimer(0)
{
}

void Enemy::Move()
{
	m_position = m_sprite.getPosition();

	bool collided = false;

	if (m_direction == "up") {

		if (!m_collisionUp) {

			m_position = sf::Vector2f(m_position.x, m_position.y - m_movementSpeed.y);
		}
		else {

			collided = true;
		}
	}
	else if (m_direction == "left") {

		if (!m_collisionLeft) {

			m_position = sf::Vector2f(m_position.x - m_movementSpeed.x, m_position.y);
		}
		else {

			collided = true;
		}
	}
	else if (m_direction == "down") {

		if (!m_collisionDown) {

			m_position = sf::Vector2f(m_position.x, m_position.y + m_movementSpeed.y);
		}
		else {

			collided = true;
		}
	}
	else if (m_direction == "right") {

		if (!m_collisionRight) {

			m_position = sf::Vector2f(m_position.x + m_movementSpeed.x, m_position.y);
		}
		else {

			collided = true;
		}
	}

	if (collided && m_directionTimer >= m_directionRate) {

		int random = 1 + (rand() % 4);

		std::string newDirection;
		
		if (random == 1) {

			newDirection = "up";
		}
		else if (random == 2) {

			newDirection = "left";
		}
		else if (random == 3) {

			newDirection = "down";
		}
		else if (random == 4) {

			newDirection = "right";
		}

		if (newDirection != m_direction) {

			m_direction = newDirection;

			m_directionTimer = 0;
		}
	}
	else {

		m_sprite.setPosition(m_position);
	}

	m_texture.loadFromFile("enemy/textures/enemy" + m_direction + ".png");

	m_sprite.setTexture(m_texture);
}

void Enemy::Shoot(std::vector<Bullet>& enemyNormalBulletVector, std::vector<Bullet>& enemyArmourBulletVector)
{
	if (m_bulletFireTimer >= m_bulletFireRate) {

		if (m_id == "basic" || m_id == "lightBattle") {

			enemyNormalBulletVector.push_back(Bullet("enemy", "normal"));
			enemyNormalBulletVector[enemyNormalBulletVector.size() - 1].Initialize(
				&m_bulletTexture,
				m_blockOffset,
				m_position,
				sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height),
				m_direction
				);
		}

		m_bulletFireTimer = 0;
	}
}

void Enemy::SetCollision(bool collision)
{
	if (m_direction == "up") {

		m_collisionUp = collision;
	}
	else if (m_direction == "left") {

		m_collisionLeft = collision;
	}
	else if (m_direction == "down") {

		m_collisionDown = collision;
	}
	else if (m_direction == "right") {

		m_collisionRight = collision;
	}
}

void Enemy::CollissionWithIceBlock(bool collision)
{
	m_collisionWithIce = collision;

	if (collision) {

		m_movementSpeed = sf::Vector2f(m_movementSpeed.x / 2, m_movementSpeed.y / 2);
	}
	else {

		if (m_collisionWithIce) {

			m_movementSpeed = sf::Vector2f(m_movementSpeed.x * 2, m_movementSpeed.y * 2);
			m_collisionWithIce = false;
		}
	}
}

void Enemy::Freeze()
{
	if (m_spawned) {

		m_freeze = true;
		m_freezeTimer = 10000;
	}
}

void Enemy::Destroy()
{
	--m_lives;

	if (m_lives <= 0) {

		Over();
	}
}

void Enemy::Initialize(
	std::string id,
	const sf::Vector2f* mapBackgroundPosition,
	const sf::Vector2f* blockOffset)
{
	m_id = id;
	m_blockOffset = blockOffset;

	if (m_id == "basic" || m_id == "lightBattle" || m_id == "doubleBarrel") {

		m_lives = 1;
	}
	else {

		m_lives = 3;
	}

	int random = 1 + (rand() % 3);

	if (random == 1) {

		random = 2;
	}
	else if (random == 2) {

		random = 6;
	}
	else if (random == 3) {

		random = 10;
	}

	m_position = sf::Vector2f(
		random * m_blockOffset->y + mapBackgroundPosition->x + (m_blockOffset->y / 7),
		0 * m_blockOffset->x + mapBackgroundPosition->y);

	m_sprite.setPosition(m_position);

	m_direction = "down";

	if (m_id == "basic") {

		m_directionRate = 1000;
		m_bulletFireRate = 2500;
		m_movementSpeed = sf::Vector2f(m_blockOffset->x / 20, m_blockOffset->x / 20);
	}
	else if (m_id == "lightBattle") {

		m_directionRate = 500;
		m_bulletFireRate = 1750;
		m_movementSpeed = sf::Vector2f(m_blockOffset->x / 15, m_blockOffset->x / 15);

		m_sprite.setColor(sf::Color::Cyan);
	}
	else if (m_id == "doubleBarrel") {

		m_bulletFireRate = 500;

		m_sprite.setColor(sf::Color(226, 210, 50));
	}
	else if (m_id == "destroyer") {

		m_bulletFireRate = 1000;

		m_sprite.setColor(sf::Color(70, 137, 151));
	}
	else if (m_id == "fighter") {

		m_bulletFireRate = 500;

		m_sprite.setColor(sf::Color::Magenta);
	}
}

void Enemy::Load()
{
	if (m_texture.loadFromFile("enemy/textures/enemydown.png")) {

		m_sprite.setTexture(m_texture);

		m_scale = sf::Vector2f(
			0.8 * m_blockOffset->y / m_texture.getSize().x,
			0.8 * 2 * m_blockOffset->x / m_texture.getSize().y);

		m_sprite.setScale(m_scale);
	}

	m_bulletTexture.loadFromFile("bullet/textures/bullet.png");
}

void Enemy::Update(std::vector<Bullet>& enemyNormalBulletVector, std::vector<Bullet>& enemyArmourBulletVector, float deltaTimerMilli)
{
	if (m_spawnTimer >= m_spawnRate) {

		m_spawned = true;
	}
	if (!m_checkDestroy && m_spawned) {

		m_directionTimer = m_directionTimer + deltaTimerMilli;
		m_bulletFireTimer = m_bulletFireTimer + deltaTimerMilli;

		if (!m_freeze) {

			Move();
			Shoot(enemyNormalBulletVector, enemyArmourBulletVector);

		}
		else {

			m_freezeTimer = m_freezeTimer - deltaTimerMilli;

			if (m_freezeTimer <= 0) {

				m_freeze = false;
			}
		}
	}
	else {

		m_spawnTimer = m_spawnTimer + deltaTimerMilli;
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	if (!m_checkDestroy && m_spawnTimer >= m_spawnRate) {

		window.draw(m_sprite);
	}
}

Enemy::~Enemy()
{
}