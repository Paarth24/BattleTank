#include "GrassBlock.h"
#include <iostream>

GrassBlock::GrassBlock():
	m_checkDestroy(false),
	m_id(""),
	m_size(sf::Vector2f(16, 16)),
	m_scale(sf::Vector2f(5.25, 2.5)),
	m_position(sf::Vector2f(0, 0)),
	m_gridIndex(sf::Vector2i(0, 0))

{
}

void GrassBlock::Initialize(const sf::Vector2f* mapOrigin, const sf::Vector2f* blockOffset)
{
	m_position = sf::Vector2f(mapOrigin->x + (m_gridIndex.x * blockOffset->x), mapOrigin->y + (m_gridIndex.y * blockOffset->y));

	m_sprite.setScale(m_scale);
	m_sprite.setPosition(m_position);
}

void GrassBlock::Load(const sf::Texture* grassTexture)
{
	m_sprite.setTexture(*grassTexture);
}

void GrassBlock::Update()
{
}

void GrassBlock::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

GrassBlock::~GrassBlock()
{
}