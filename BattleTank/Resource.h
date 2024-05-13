#include "SFML/Graphics.hpp"
#pragma once

struct Resource {

	sf::Texture playertextureUp;
	sf::Texture playertextureDown;

	sf::Texture playertextureLeft;
	sf::Texture playertextureRight;

	sf::Texture enemytextureUp;
	sf::Texture enemytextureDown;

	sf::Texture enemytextureLeft;
	sf::Texture enemytextureRight;

	sf::Texture bulletTexture;

	sf::Font gameFont;

	void Load();
};
