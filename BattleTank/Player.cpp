#include <iostream>

#include "Player.h"
#include "Enemy.h"
#include "Math.h"

Player::Player() :
	m_spriteSize(sf::Vector2f(0, 0)),
	m_scale(sf::Vector2f(0, 0)),
	m_movementSpeed(sf::Vector2f(0, 0)),
	m_position(sf::Vector2f(0, 0)),
	m_centre(sf::Vector2f(0, 0)),
	m_direction(0),
	m_fireRateTimer(0),
	m_fireRate(0),
	m_checkDestroy(0)
{
}

void Player::Initialize(const sf::Vector2f& spriteSize, const sf::Vector2f& scale)
{
	m_checkDestroy = 1;

	m_spriteSize = spriteSize;
	m_scale = scale;

	m_movementSpeed = sf::Vector2f(2.5, 2.5);
	m_centre = sf::Vector2f(35, 35);
	m_fireRate = 250;

}

void Player::Load(sf::Texture* playerTextureUp)
{
	m_sprite.setTexture(*playerTextureUp);
	m_sprite.setTextureRect(sf::IntRect(115, 115, m_spriteSize.x, m_spriteSize.y));
	m_sprite.setScale(m_scale);

	m_collisionBox.setSize(sf::Vector2f(m_spriteSize.x, m_spriteSize.y));
	m_collisionBox.setFillColor(sf::Color::Transparent);
	m_collisionBox.setOutlineColor(sf::Color::Black);
	m_collisionBox.setOutlineThickness(1);

	m_collisionBox.setScale(m_sprite.getScale());

	m_direction = 1;
}

void Player::Update(
	sf::RenderWindow& window,
	sf::Texture* playerTextureUp,
	sf::Texture* playerTextureLeft,
	sf::Texture* playerTextureDown,
	sf::Texture* playerTextureRight,
	sf::Texture* bulletTexture,
	const float& deltatimeTimerMilli)
{

	if(m_checkDestroy == 1){
		m_position = m_sprite.getPosition();

		m_collisionBox.setPosition(m_position.x, m_position.y);

		m_fireRateTimer = m_fireRateTimer + deltatimeTimerMilli;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

			m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y - m_movementSpeed.y));
			m_sprite.setTexture(*playerTextureUp);

			m_direction = 1;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

			m_sprite.setPosition(sf::Vector2f(m_position.x - m_movementSpeed.x, m_position.y));
			m_sprite.setTexture(*playerTextureLeft);

			m_direction = 2;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

			m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y + m_movementSpeed.y));
			m_sprite.setTexture(*playerTextureDown);

			m_direction = 3;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

			m_sprite.setPosition(sf::Vector2f(m_position.x + m_movementSpeed.x, m_position.y));
			m_sprite.setTexture(*playerTextureRight);

			m_direction = 4;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_fireRateTimer >= m_fireRate) {

			m_bullets.push_back(Bullet());
			m_bullets[m_bullets.size() - 1].Initialize(sf::Color::Green, m_direction, bulletTexture, m_position, m_centre);

			m_fireRateTimer = 0;
		}

		for (size_t i = 0; i < m_bullets.size(); ++i) {

			m_bullets[i].Update();
		}

		Math::BulletInMap(window, m_bullets);
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	if(m_checkDestroy == 1){
		window.draw(m_sprite);
		window.draw(m_collisionBox);

		for (size_t i = 0; i < m_bullets.size(); ++i) {

			m_bullets[i].Draw(window);
		}
	}
}

Player::~Player()
{
}