#pragma once

#include "SFML/Graphics.hpp"

class Base {

public:

	sf::Sprite m_sprite;

	sf::RectangleShape m_collisionBox;

	sf::Vector2f m_scale;
	sf::Vector2f m_spriteSize;
	sf::Vector2f m_position;


public:

	Base(const sf::Vector2f& size);
	~Base();

	void Initialize(
		const sf::Vector2f* mapSize,
		const sf::Vector2f* blockOffset,
		const sf::RenderWindow& window);

	void Load(sf::Texture* birdTexture);
	void Update();
	void Draw(sf::RenderWindow& window);
};

