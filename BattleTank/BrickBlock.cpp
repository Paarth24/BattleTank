#include "BrickBlock.h"

BrickBlock::BrickBlock():
	m_checkDestroy(false),
	m_id(""),
	m_spriteSize(sf::Vector2f(16, 16)),
	m_scale(sf::Vector2f(0, 0)),
	m_position(sf::Vector2f(0, 0)),
	m_gridIndex(sf::Vector2i(0, 0))
{
}

void BrickBlock::Initialize(const sf::Vector2f* mapOrigin, const sf::Vector2f* blockOffset)
{
	m_scale = sf::Vector2f(blockOffset->x / m_spriteSize.x, blockOffset->y / m_spriteSize.y);

	m_position = sf::Vector2f(mapOrigin->x + (m_gridIndex.x * blockOffset->x), mapOrigin->y + (m_gridIndex.y * blockOffset->y));

	m_sprite.setScale(m_scale);
	m_sprite.setPosition(m_position);
}

void BrickBlock::Load(const sf::Texture* brickTexture)
{
	m_sprite.setTexture(*brickTexture);
}

void BrickBlock::Update()
{
}

void BrickBlock::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

BrickBlock::~BrickBlock()
{
}