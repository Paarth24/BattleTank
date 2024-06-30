#include "SteelBlock.h"

SteelBlock::SteelBlock():
	m_checkDestroy(false),
	m_id(""),
	m_spriteSize(sf::Vector2f(16, 16)),
	m_scale(sf::Vector2f(0, 0)),
	m_position(sf::Vector2f(0, 0)),
	m_gridIndex(sf::Vector2i(0, 0))
{
}

void SteelBlock::Initialize(const sf::Vector2f* mapOrigin, const sf::Vector2f* blockOffset)
{
	m_scale = sf::Vector2f(blockOffset->x / m_spriteSize.x, blockOffset->y / m_spriteSize.y);
	m_position = sf::Vector2f(mapOrigin->x + (m_gridIndex.x * blockOffset->x), mapOrigin->y + (m_gridIndex.y * blockOffset->y));

	m_sprite.setScale(m_scale);
	m_sprite.setPosition(m_position);
}

void SteelBlock::Load(const sf::Texture* steelTexture)
{
	m_sprite.setTexture(*steelTexture);
}

void SteelBlock::Update()
{
}

void SteelBlock::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

SteelBlock::~SteelBlock()
{
}