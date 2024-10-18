#include "PowerUp.h"

#include <iostream>

PowerUp::PowerUp() :
	m_checkDestroy(false),
	m_spawned(false),
	m_type(""),
	m_blockOffset(nullptr),
	m_gridIndex(sf::Vector2f(0, 0)),
	m_spawnTime(0),
	m_spawnTimer(0),
	m_despawnTime(0)
{
}

void PowerUp::Initialize(
	const sf::Vector2f* mapBackgroundPosition,
	const sf::Vector2f* blockOffset)
{
	m_blockOffset = blockOffset;

	m_gridIndex = sf::Vector2f(1 + (rand() % 12), 0 + (rand() % 24));

	m_spawnTime = 10000 + (rand() % 25000);
	m_despawnTime = 10000;


	m_position = sf::Vector2f(
		m_gridIndex.x * m_blockOffset->y + mapBackgroundPosition->x + (m_blockOffset->y / 4),
		m_gridIndex.y * m_blockOffset->x + mapBackgroundPosition->y + (m_blockOffset->x / 2));

	m_sprite.setPosition(m_position);
}

void PowerUp::Load()
{
	if (m_texture.loadFromFile("powerUps/textures/"+ m_type + ".png")) {

		m_sprite.setTexture(m_texture);

		m_scale = sf::Vector2f(
			m_blockOffset->y / (2 * m_texture.getSize().x),
			m_blockOffset->x / m_texture.getSize().y);

		m_sprite.setScale(m_scale);
	}
}

void PowerUp::Update(float deltatimermilli)
{
	if (!m_spawned) {

		m_spawnTimer = m_spawnTimer + deltatimermilli;
	}
	if (m_spawnTimer >= m_spawnTime) {

		m_spawned = true;
	}

	if (m_spawned && !m_checkDestroy) {

		m_despawnTime = m_despawnTime - deltatimermilli;
	}
	if (m_despawnTime <= 0) {

		m_checkDestroy = true;
	}
}

void PowerUp::Draw(sf::RenderWindow& window)
{
	if (m_spawned && !m_checkDestroy) {

		window.draw(m_sprite);
	}
}

PowerUp::~PowerUp()
{
}

