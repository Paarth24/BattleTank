#include <iostream>

#include "GameOverText.h"

void GameOverText::Initialize()
{
	m_text.setFillColor(sf::Color::White);

	m_text.setCharacterSize(45);
	m_text.setScale(sf::Vector2f(5, 5));
}

void GameOverText::Load(sf::Font* gameOverFont)
{
	m_text.setFont(*gameOverFont);
}

void GameOverText::Draw()
{
}
