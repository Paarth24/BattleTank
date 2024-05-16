#include <iostream>

#include "GameOverText.h"

void GameOverText::Initialize()
{
	m_textGameOver.setString("Game Over");
	m_textGameOver.setFillColor(sf::Color::White);
	m_textGameOver.setCharacterSize(45);
	m_textGameOver.setScale(sf::Vector2f(5, 5));

	m_textCause.setFillColor(sf::Color::White);
	m_textCause.setCharacterSize(35);
	m_textCause.setScale(sf::Vector2f(3, 3));
}

void GameOverText::Load(sf::Font* gameFont)
{
	m_textGameOver.setFont(*gameFont);
	m_textCause.setFont(*gameFont);
}

void GameOverText::Draw(sf::RenderWindow& window)
{
	window.draw(m_textGameOver);
	window.draw(m_textCause);
}
