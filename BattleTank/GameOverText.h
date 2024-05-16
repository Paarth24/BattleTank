#pragma once

#include "SFML/Graphics.hpp"

class GameOverText {

public:

	sf::Text m_textGameOver;
	sf::Text m_textCause;

	void Initialize();
	void Load(sf::Font* gameFont);
	void Draw(sf::RenderWindow& window);
};
