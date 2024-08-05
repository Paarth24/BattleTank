#include "Player.h"

Player::Player():
	m_id(0),
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
	m_bulletFireRate(0),
	m_bulletFireTimer(0),
	m_powerUpTaken(false)
{
}

void Player::Move()
{
	m_position = m_sprite.getPosition();

	if (m_id == 1) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

			m_direction = "up";
			
			if (!m_collisionUp) {
				
				m_position = sf::Vector2f(m_position.x, m_position.y - m_movementSpeed.y);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

			m_direction = "left";

			if (!m_collisionLeft) {

				m_position = sf::Vector2f(m_position.x - m_movementSpeed.x, m_position.y);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

			m_direction = "down";

			if (!m_collisionDown) {

				m_position = sf::Vector2f(m_position.x, m_position.y + m_movementSpeed.y);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

			m_direction = "right";

			if (!m_collisionRight) {

				m_position = sf::Vector2f(m_position.x + m_movementSpeed.x, m_position.y);
			}
		}

		m_texture.loadFromFile("assets/player1/player1Texture/yellow/" + m_direction + ".png");
	}
	else {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

			if (m_direction != "up") {

				m_direction = "up";
			}

			if (!m_collisionUp) {

				m_position = sf::Vector2f(m_position.x, m_position.y - m_movementSpeed.y);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

			if (m_direction != "left") {

				m_direction = "left";
			}

			if (!m_collisionLeft) {

				m_position = sf::Vector2f(m_position.x - m_movementSpeed.x, m_position.y);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

			if (m_direction != "down") {

				m_direction = "down";
			}

			if (!m_collisionDown) {

				m_position = sf::Vector2f(m_position.x, m_position.y + m_movementSpeed.y);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

			if (m_direction != "right") {

				m_direction = "right";
			}

			if (!m_collisionRight) {

				m_position = sf::Vector2f(m_position.x + m_movementSpeed.x, m_position.y);
			}
		}

		m_texture.loadFromFile("assets/player2/player2Texture/green/" + m_direction + ".png");
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
}

void Player::Shoot(std::vector<Bullet>& playerNormalBulletVector, std::vector<Bullet>& playerArmourBulletVector)
{

	if (m_bulletFireTimer >= m_bulletFireRate) {

		if (m_id == 1) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {

				if (!m_powerUpTaken) {

					playerNormalBulletVector.push_back(Bullet("player1", "normal"));
					playerNormalBulletVector[playerNormalBulletVector.size() - 1].Initialize(
						&m_bulletTexture,
						m_blockOffset,
						m_position,
						sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height),
						m_direction);
				}
				else {

					playerArmourBulletVector.push_back(Bullet("player1", "armour"));
					playerArmourBulletVector[playerArmourBulletVector.size() - 1].Initialize(
						&m_bulletTexture,
						m_blockOffset,
						m_position,
						sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height),
						m_direction);
				}

				m_bulletFireTimer = 0;
			}
		}
		else {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {

				if (!m_powerUpTaken) {

					playerNormalBulletVector.push_back(Bullet("player2", "normal"));
					playerNormalBulletVector[playerNormalBulletVector.size() - 1].Initialize(
						&m_bulletTexture,
						m_blockOffset,
						m_position,
						sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height),
						m_direction);
				}
				else {

					playerArmourBulletVector.push_back(Bullet("player2", "armour"));
					playerArmourBulletVector[playerArmourBulletVector.size() - 1].Initialize(
						&m_bulletTexture,
						m_blockOffset,
						m_position,
						sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height),
						m_direction);
				}

				m_bulletFireTimer = 0;
			}
		}
	}
}

void Player::SetCollision(bool collision)
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

void Player::CollissionWithIceBlock()
{
}

void Player::Freeze()
{
}

void Player::SetPowerUp()
{
}

void Player::Destroy()
{
}

void Player::Over()
{
}

void Player::Initialize(int id, const sf::Vector2f* blockOffset, const sf::Vector2f* mapBackgroundPosition)
{
	m_id = id;
	m_blockOffset = blockOffset;
	m_lives = 3;

	if (m_id == 1) {

		m_position = sf::Vector2f(
			4 * m_blockOffset->y + mapBackgroundPosition->x,
			24 * m_blockOffset->x + mapBackgroundPosition->y);
	}
	else {

		m_position = sf::Vector2f(
			8 * m_blockOffset->y + mapBackgroundPosition->x,
			24 * m_blockOffset->x + mapBackgroundPosition->y);
	}

	m_sprite.setPosition(m_position);

	m_direction = "up";
	m_movementSpeed = sf::Vector2f(2, 2);

	m_bulletFireRate = 500;
}

void Player::Load()
{
	if (m_id == 1) {

		if (m_texture.loadFromFile("assets/player1/player1Texture/yellow/" + m_direction + ".png")) {

			std::cout << "player1 texture loaded successfully" << std::endl;
		}
	}
	else {

		if (m_texture.loadFromFile("assets/player2/player2Texture/green/" + m_direction + ".png")) {

			std::cout << "player2 texture loaded successfully" << std::endl;
		}
	}

	if (m_bulletTexture.loadFromFile("assets/bullet/bulletTexture/bullet.png")) {

		std::cout << "Bullet Texture loaded successfully" << std::endl;
	}

	m_sprite.setTexture(m_texture);

	m_scale = sf::Vector2f(
		0.8 * m_blockOffset->y / m_texture.getSize().x,
		0.8 * 2 * m_blockOffset->x / m_texture.getSize().y);

	m_sprite.setScale(m_scale);
}

void Player::Update(std::vector<Bullet>& playerNormalBulletVector, std::vector<Bullet>& playerArmourBulletVector, float deltaTimerMilli)
{
	m_bulletFireTimer = m_bulletFireTimer + deltaTimerMilli;

	Move();
	Shoot(playerNormalBulletVector, playerArmourBulletVector);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

Player::~Player()
{
}