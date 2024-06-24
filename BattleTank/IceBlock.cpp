#include "IceBlock.h"

IceBlock::IceBlock():
	m_checkDestroy(false),
	m_id(""),
	m_size(sf::Vector2f(16, 16)),
	m_scale(sf::Vector2f(5.25, 2.5)),
	m_position(sf::Vector2f(0, 0)),
	m_gridIndex(sf::Vector2i(0, 0))
{
}

void IceBlock::Initialize(const sf::Vector2f* mapOrigin, const sf::Vector2f* blockOffset)
{
}

void IceBlock::Load(const sf::Texture* grassTexture)
{
}

void IceBlock::Update()
{
}

void IceBlock::Draw(sf::RenderWindow& window)
{
}

IceBlock::~IceBlock()
{
}