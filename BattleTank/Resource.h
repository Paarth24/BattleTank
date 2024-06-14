#include "SFML/Graphics.hpp"
#pragma once

struct Resource {

	sf::Texture birdTexture;

	sf::Texture player1textureUp;
	sf::Texture player1textureDown;

	sf::Texture player1textureLeft;
	sf::Texture player1textureRight;

	sf::Texture enemytextureUp;
	sf::Texture enemytextureDown;

	sf::Texture enemytextureLeft;
	sf::Texture enemytextureRight;

	sf::Texture bulletTexture;

	sf::Font gameFont;

	void Load();
};
