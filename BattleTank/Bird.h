#pragma once

#include "SFML/Graphics.hpp"

class Bird {

public:

	sf::Sprite m_sprite;

	sf::RectangleShape m_collisionBox;

public:

	Bird();
	~Bird();

	void Initialize(const sf::RenderWindow& window);
	void Load(sf::Texture* birdTexture);
	void Update();
	void Draw(sf::RenderWindow& window);
};

