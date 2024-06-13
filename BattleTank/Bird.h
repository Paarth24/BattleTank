#pragma once

#include "SFML/Graphics.hpp"

class Bird {

public:

	sf::Sprite m_sprite;

	sf::RectangleShape m_collisionBox;

	sf::Vector2f m_scale;
	sf::Vector2f m_size;
	sf::Vector2f m_position;


public:

	Bird(const sf::Vector2f& scale, const sf::Vector2f& size);
	~Bird();

	void Initialize(const sf::Vector2f* mapSize, const sf::RenderWindow& window);
	void Load(sf::Texture* birdTexture);
	void Update();
	void Draw(sf::RenderWindow& window);
};

