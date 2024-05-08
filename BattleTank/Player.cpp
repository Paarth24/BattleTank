#include <iostream>

#include "Player.h"

Player::Player(
	const sf::Vector2f& spriteSize,
	const sf::Vector2f& scale
) :
	m_spriteSize(spriteSize),
	m_scale(scale),
	m_movementSpeed(sf::Vector2f(2.5, 2.5)),
	m_playerPosition(sf::Vector2f(0, 0)),
	m_playerCentre(sf::Vector2f(35, 35)),
	m_playerDirection(0),
	m_fireRateTimer(0),
	m_fireRate(250)
{
}

void Player::Initialize()
{
}

void Player::Load()
{
	if (
		m_textureUp.loadFromFile("assets/player/playerTexture/playerTankUp.png") &&
		m_textureRight.loadFromFile("assets/player/playerTexture/playerTankRight.png") &&
		m_textureDown.loadFromFile("assets/player/playerTexture/playerTankDown.png") &&
		m_textureLeft.loadFromFile("assets/player/playerTexture/playerTankLeft.png") &&
		m_bulletTexture.loadFromFile("assets/bullet/bulletTexture/bullet.png")
		) {

		std::cout << "Player loaded successfully" << std::endl;

		m_sprite.setTexture(m_textureUp);
		m_sprite.setTextureRect(sf::IntRect(115, 115, m_spriteSize.x, m_spriteSize.y));
		m_sprite.setScale(m_scale);

		m_collisionBox.setSize(sf::Vector2f(m_spriteSize.x, m_spriteSize.y));
		m_collisionBox.setFillColor(sf::Color::Transparent);
		m_collisionBox.setOutlineColor(sf::Color::Black);
		m_collisionBox.setOutlineThickness(1);

		m_collisionBox.setScale(m_sprite.getScale());

		m_playerDirection = 1;
	}
}

void Player::Update(const float& deltatimeTimerMilli)
{
	m_playerPosition = m_sprite.getPosition();

	m_collisionBox.setPosition(m_playerPosition.x, m_playerPosition.y);

	m_fireRateTimer = m_fireRateTimer + deltatimeTimerMilli;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

		m_sprite.setPosition(sf::Vector2f(m_playerPosition.x, m_playerPosition.y - m_movementSpeed.y));
		m_sprite.setTexture(m_textureUp);

		m_playerDirection = 1;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

		m_sprite.setPosition(sf::Vector2f(m_playerPosition.x - m_movementSpeed.x, m_playerPosition.y));
		m_sprite.setTexture(m_textureLeft);

		m_playerDirection = 2;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

		m_sprite.setPosition(sf::Vector2f(m_playerPosition.x, m_playerPosition.y + m_movementSpeed.y));
		m_sprite.setTexture(m_textureDown);

		m_playerDirection = 3;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

		m_sprite.setPosition(sf::Vector2f(m_playerPosition.x + m_movementSpeed.x, m_playerPosition.y));
		m_sprite.setTexture(m_textureRight);

		m_playerDirection = 4;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_fireRateTimer >= m_fireRate) {

		bullets.push_back(Bullet());
		bullets[bullets.size() - 1].Initialize(m_playerDirection, &m_bulletTexture, m_playerPosition, m_playerCentre);

		m_fireRateTimer = 0;
	}

	for (size_t i = 0; i < bullets.size(); ++i) {

		bullets[i].Update();
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	window.draw(m_collisionBox);

	for (size_t i = 0; i < bullets.size(); ++i) {

		bullets[i].Draw(window);
	}
}

Player::~Player()
{
}