#include "Bullet.h"

Bullet::Bullet(const std::string& id, const std::string& type):
	m_id(id),
	m_type(type),
	m_texture(nullptr),
	m_scale(sf::Vector2f(0, 0)),
	m_position(sf::Vector2f(0, 0)),
	m_direction(""),
	m_movementSpeed(sf::Vector2f(0, 0))
{
}

void Bullet::Move()
{
	m_position = m_sprite.getPosition();

	if (m_direction == "up") {

		m_position = sf::Vector2f(m_position.x, m_position.y - m_movementSpeed.y);
	}
	else if (m_direction == "left") {

		m_position = sf::Vector2f(m_position.x - m_movementSpeed.x, m_position.y);
	}
	else if (m_direction == "down") {

		m_position = sf::Vector2f(m_position.x, m_position.y + m_movementSpeed.y);
	}
	else if (m_direction == "right") {

		m_position = sf::Vector2f(m_position.x + m_movementSpeed.x, m_position.y);
	}

	m_sprite.setPosition(m_position);
}

void Bullet::Initialize(sf::Texture* bulletTexture, const sf::Vector2f* blockOffset, const sf::Vector2f& position, const std::string& direction)
{
	m_texture = bulletTexture;
	m_sprite.setTexture(*bulletTexture);
		
	if (m_id == "player1") {

		m_sprite.setColor(sf::Color::Yellow);
	}
	else if (m_id == "player2") {

		m_sprite.setColor(sf::Color::Green);
	}
	else {

		m_sprite.setColor(sf::Color::Red);
	}
	
	m_scale = sf::Vector2f(blockOffset->y / (2 * m_texture->getSize().x), blockOffset->x / m_texture->getSize().y);
	m_sprite.setScale(m_scale);

	m_position = position;
	m_sprite.setPosition(position);

	if (m_type == "normal") {

		m_movementSpeed = sf::Vector2f(3, 3);
	}
	else {

		m_movementSpeed = sf::Vector2f(5, 5);
	}

	m_direction = direction;
}

void Bullet::Update()
{
	Move();
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

Bullet::~Bullet()
{
}