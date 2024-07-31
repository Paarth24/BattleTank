#include "Block.h"

#include <iostream>

Block::Block():
	m_checkDestroy(false)
{
}

void Block::Initialize(const sf::Vector2i& gridIndex, const sf::Vector2f* blockOffset, const sf::Vector2f* mapBackgroundPosition)
{
	m_sprite.setPosition(sf::Vector2f(
		gridIndex.x * blockOffset->y + mapBackgroundPosition->x,
		gridIndex.y * blockOffset->x + mapBackgroundPosition->y));
}

void Block::Load(const std::string& fileName, const sf::Vector2f* blockOffset)
{
	if (m_texture.loadFromFile(fileName)) {

		m_sprite.setTexture(m_texture);
		m_sprite.setScale(sf::Vector2f(
			blockOffset->y / m_texture.getSize().x,
			blockOffset->x / m_texture.getSize().y));
	}
}

void Block::Draw(sf::RenderWindow& window)
{
	if (!m_checkDestroy) {

		window.draw(m_sprite);
	}
}

void BrickBlock::Destroy()
{
}

void SteelBlock::Destroy()
{
}

Block::~Block()
{
}