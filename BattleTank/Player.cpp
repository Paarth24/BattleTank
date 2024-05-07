#include <iostream>

#include "Player.h"

Player::Player(
	const sf::Vector2i& scale		
):
	m_spriteSize(sf::Vector2f(70, 70)),
	m_scale(scale),
	m_movementSpeed(sf::Vector2f(2.5, 2.5)),	
	m_playerDirection(0)
{
}

void Player::Initialize()
{
}

void Player::Load()
{
	if (
		m_textureUp.loadFromFile("assets/player/playerTankUp.png") &&
		m_textureRight.loadFromFile("assets/player/playerTankRight.png") &&
		m_textureDown.loadFromFile("assets/player/playerTankDown.png") &&
		m_textureLeft.loadFromFile("assets/player/playerTankLeft.png")
		) {

		std::cout << "Player tank loaded successfully" << std::endl;

		std::cout << m_textureUp.getSize().x << std::endl;
		std::cout << m_textureUp.getSize().y << std::endl;

		m_sprite.setTexture(m_textureUp);
		m_sprite.setTextureRect(sf::IntRect(115, 115, m_spriteSize.x, m_spriteSize.y));
		m_sprite.setScale(m_scale.x, m_scale.y);

		m_collisionBox.setSize(sf::Vector2f(m_spriteSize.x, m_spriteSize.y));
		m_collisionBox.setFillColor(sf::Color::Transparent);
		m_collisionBox.setOutlineColor(sf::Color::Black);
		m_collisionBox.setOutlineThickness(1);

		m_collisionBox.setScale(m_sprite.getScale());
	}
}

void Player::Update()
{
	sf::Vector2f position = m_sprite.getPosition();

	m_collisionBox.setPosition(position.x, position.y);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

		m_sprite.setPosition(sf::Vector2f(position.x, position.y - m_movementSpeed.y));
		m_sprite.setTexture(m_textureUp);

		m_playerDirection = 1;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

		m_sprite.setPosition(sf::Vector2f(position.x - m_movementSpeed.x, position.y));
		m_sprite.setTexture(m_textureLeft);

		m_playerDirection = 2;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

		m_sprite.setPosition(sf::Vector2f(position.x, position.y + m_movementSpeed.y));
		m_sprite.setTexture(m_textureDown);

		m_playerDirection = 3;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

		m_sprite.setPosition(sf::Vector2f(position.x + m_movementSpeed.x, position.y));
		m_sprite.setTexture(m_textureRight);

		m_playerDirection = 4;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

		bullets.push_back(Bullet());
		bullets[bullets.size() - 1].Initialize(m_playerDirection);
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