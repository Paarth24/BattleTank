#include <iostream>

#include "GameOverText.h"

void GameOverText::Initialize()
{
	m_text.setFillColor(sf::Color::White);

	m_text.setCharacterSize(225);
}

void GameOverText::Load(sf::Font* gameOverFont)
{
	m_text.setFont(*gameOverFont);
}

void GameOverText::Draw()
{
}
