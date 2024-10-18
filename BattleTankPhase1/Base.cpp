#include "Base.h"

#include <iostream>

Base::Base():
	m_checkDestroy(false),
	m_lives(0),
	m_blockOffset(nullptr),
	m_position(sf::Vector2f(0, 0)),
	m_scale(sf::Vector2f(0, 0))
{
}

void Base::Destroy()
{
	--m_lives;

	if (m_lives <= 0) {

		m_checkDestroy = true;
	}
}

void Base::Initialize(
	const sf::Vector2f* mapBackgroundPosition,
	const sf::Vector2f* mapBackgroundSize,
	const sf::Vector2f* blockOffset)
{
	m_lives = 1;

	m_blockOffset = blockOffset;

	m_position = sf::Vector2f(
		6 * m_blockOffset->y + mapBackgroundPosition->x,
		24 * m_blockOffset->x + mapBackgroundPosition->y);

	m_sprite.setPosition(m_position);

	m_gameOverText.setString("Game Over");
	m_gameOverText.setCharacterSize(mapBackgroundSize->x / 7);
}

void Base::Load(
	const sf::Font* gameFont,
	const sf::Vector2f* mapBackgroundPosition,
	const sf::Vector2f* mapBackgroundSize)
{
	if (m_texture.loadFromFile("base/textures/base.png")) {

		m_gameOverText.setFont(*gameFont);
		m_gameOverText.setPosition(sf::Vector2f(
			mapBackgroundPosition->x + ((mapBackgroundSize->x - m_gameOverText.getGlobalBounds().width) / 2),
			mapBackgroundPosition->y + ((mapBackgroundSize->y - m_gameOverText.getGlobalBounds().height) / 2)));
	
		std::cout << "Base texture loaded successfully" << std::endl;
		m_sprite.setTexture(m_texture);

		m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

		m_scale = sf::Vector2f(
			m_blockOffset->y / 16,
			2 * m_blockOffset->x / 16);

		m_sprite.setScale(m_scale);
	}
}

void Base::Draw(sf::RenderWindow& window)
{
	if (!m_checkDestroy) {
		
		window.draw(m_sprite);
	}
	else {
	
		window.draw(m_gameOverText);
	}
}

Base::~Base()
{
}