#include <iostream>

#include "Player1.h"
#include "Enemy.h"
#include "Math.h"

Player1::Player1(const sf::Vector2f& movementSpeed) :
	m_spriteSize(sf::Vector2f(0, 0)),
	m_scale(sf::Vector2f(0, 0)),
	m_movementSpeed(movementSpeed),
	m_position(sf::Vector2f(0, 0)),
	m_fireCentre(sf::Vector2f(0, 0)),
	m_direction(0),
	m_fireRateTimer(0),
	m_fireRate(0),
	m_checkDestroy(false)
{
}

const void Player1::TankMoveUp(sf::RenderWindow& window, const sf::Vector2f* mapSize, sf::Texture* playerTextureUp)
{
	m_direction = 1;
	m_sprite.setTexture(*playerTextureUp);

	if (!Math::DidSpriteCollideWithMap(window, mapSize, sf::Vector2f(40, 100), m_scale, m_direction, m_position, m_movementSpeed)) {

		m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y - m_movementSpeed.y));
	}
}

const void Player1::TankMoveLeft(sf::RenderWindow& window, const sf::Vector2f* mapSize, sf::Texture* playerTextureLeft)
{
	m_direction = 2;
	m_sprite.setTexture(*playerTextureLeft);

	if (!Math::DidSpriteCollideWithMap(window, mapSize, sf::Vector2f(40, 100), m_scale, m_direction, m_position, m_movementSpeed)) {

		m_sprite.setPosition(sf::Vector2f(m_position.x - m_movementSpeed.x, m_position.y));

	}
}

const void Player1::TankMoveDown(sf::RenderWindow& window, const sf::Vector2f* mapSize, sf::Texture* playerTextureDown)
{
	m_direction = 3;
	m_sprite.setTexture(*playerTextureDown);

	if (!Math::DidSpriteCollideWithMap(window, mapSize, sf::Vector2f(40, 100), m_scale, m_direction, m_position, m_movementSpeed)) {

		m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y + m_movementSpeed.y));
	}
}

const void Player1::TankMoveRight(sf::RenderWindow& window, const sf::Vector2f* mapSize, sf::Texture* playerTextureRight)
{
	m_direction = 4;
	m_sprite.setTexture(*playerTextureRight);

	if (!Math::DidSpriteCollideWithMap(window, mapSize, sf::Vector2f(40, 100), m_scale, m_direction, m_position, m_movementSpeed)) {

		m_sprite.setPosition(sf::Vector2f(m_position.x + m_movementSpeed.x, m_position.y));
	}
}

void Player1::Initialize(
	const sf::Vector2f* mapSize,
	sf::RenderWindow& window,
	const sf::Vector2f& spriteSize,
	const sf::Vector2f& scale)
{
	m_spriteSize = spriteSize;
	m_scale = scale;

	m_fireCentre = sf::Vector2f(m_spriteSize.x / 2, m_spriteSize.y / 2);
	m_fireRate = 250;

	m_position = sf::Vector2f((window.getSize().x - mapSize->x) / 3, (window.getSize().y - mapSize->y) / 2);
}

void Player1::Load(sf::Texture* playerTextureUp)
{
	m_sprite.setTexture(*playerTextureUp);
	m_sprite.setTextureRect(sf::IntRect(115, 115, m_spriteSize.x, m_spriteSize.y));
	m_sprite.setScale(m_scale);
	m_sprite.setPosition(m_position);

	m_collisionBox.setSize(sf::Vector2f(m_spriteSize.x, m_spriteSize.y));
	m_collisionBox.setFillColor(sf::Color::Transparent);
	m_collisionBox.setOutlineColor(sf::Color::White);
	m_collisionBox.setOutlineThickness(1);
	m_collisionBox.setPosition(m_position);

	m_collisionBox.setScale(m_sprite.getScale());

	m_direction = 1;
}

void Player1::Update(
	sf::RenderWindow& window,
	sf::Texture* playerTextureUp,
	sf::Texture* playerTextureLeft,
	sf::Texture* playerTextureDown,
	sf::Texture* playerTextureRight,
	sf::Texture* bulletTexture,
	const sf::Vector2f* mapSize,
	const float& deltatimeTimerMilli)
{

	if(m_checkDestroy == false){
		m_position = m_sprite.getPosition();

		m_collisionBox.setPosition(m_position.x, m_position.y);

		m_fireRateTimer = m_fireRateTimer + deltatimeTimerMilli;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

			TankMoveUp(window, mapSize, playerTextureUp);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

			TankMoveLeft(window, mapSize, playerTextureLeft);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

			TankMoveDown(window, mapSize, playerTextureDown);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

			TankMoveRight(window, mapSize, playerTextureRight);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_fireRateTimer >= m_fireRate) {

			m_bullets.push_back(Bullet());
			m_bullets[m_bullets.size() - 1].Initialize(sf::Color::Green, m_direction, bulletTexture, m_position, m_fireCentre);

			m_fireRateTimer = 0;
		}

		for (size_t i = 0; i < m_bullets.size(); ++i) {

			m_bullets[i].Update();
		}
	}
}

void Player1::Draw(sf::RenderWindow& window)
{
	if(m_checkDestroy == false){
		window.draw(m_sprite);
		window.draw(m_collisionBox);

		for (size_t i = 0; i < m_bullets.size(); ++i) {

			m_bullets[i].Draw(window);
		}
	}
}

Player1::~Player1()
{
}