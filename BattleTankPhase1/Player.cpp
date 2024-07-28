#include "Player.h"

Player::Player():
	m_id(0),
	m_blockOffset(nullptr),
	m_lives(0),
	m_scale(sf::Vector2f(0, 0)),
	m_position(sf::Vector2f(0, 0)),
	m_direction(""),
	m_movementSpeed(sf::Vector2f(0, 0))
{
}

void Player::Move()
{
	m_position = m_sprite.getPosition();

	if (m_id == 1) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

			if (m_direction != "up") {

				m_direction = "up";
			}
			
			m_position = sf::Vector2f(m_position.x, m_position.y - m_movementSpeed.y);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

			if (m_direction != "left") {

				m_direction = "left";
			}

			m_position = sf::Vector2f(m_position.x - m_movementSpeed.x, m_position.y);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

			if (m_direction != "down") {

				m_direction = "down";
			}

			m_position = sf::Vector2f(m_position.x, m_position.y + m_movementSpeed.y);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

			if (m_direction != "right") {

				m_direction = "right";
			}

			m_position = sf::Vector2f(m_position.x + m_movementSpeed.x, m_position.y);
		}

		m_texture.loadFromFile("assets/player1/player1Texture/yellow/" + m_direction + ".png");
	}
	else {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

			if (m_direction != "up") {

				m_direction = "up";
			}

			m_position = sf::Vector2f(m_position.x, m_position.y - m_movementSpeed.y);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

			if (m_direction != "left") {

				m_direction = "left";
			}

			m_position = sf::Vector2f(m_position.x - m_movementSpeed.x, m_position.y);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

			if (m_direction != "down") {

				m_direction = "down";
			}

			m_position = sf::Vector2f(m_position.x, m_position.y + m_movementSpeed.y);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

			if (m_direction != "right") {

				m_direction = "right";
			}

			m_position = sf::Vector2f(m_position.x + m_movementSpeed.x, m_position.y);
		}

		m_texture.loadFromFile("assets/player2/player2Texture/green/" + m_direction + ".png");
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
}

void Player::Shoot()
{
}

void Player::SetCollision()
{
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

	m_sprite.setTexture(m_texture);

	m_scale = sf::Vector2f(
		m_blockOffset->y / m_texture.getSize().x,
		2 * m_blockOffset->x / m_texture.getSize().y);

	m_sprite.setScale(m_scale);
}

void Player::Update()
{
	Move();
	Shoot();
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

Player::~Player()
{
}