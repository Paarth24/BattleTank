#pragma once

#include "SFML/Graphics.hpp"

class GameOverText {

public:

	sf::Text m_text;

	void Initialize();
	void Load(sf::Font* gameOverFont);
	void Draw();
};
