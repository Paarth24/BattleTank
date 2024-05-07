#pragma once

#include "Bullet.h"

#include <vector>

class Player {

private:

	sf::Texture m_textureUp;
	sf::Texture m_textureDown;

	sf::Texture m_textureRight;
	sf::Texture m_textureLeft;

	sf::Vector2f m_spriteSize;
	sf::Sprite m_sprite;
	sf::RectangleShape m_collisionBox;

	sf::Vector2i m_scale;

	int m_playerDirection;

	std::vector<Bullet> bullets;

	sf::Vector2f m_movementSpeed;

public:
	
	Player(const sf::Vector2i& scale);
	~Player();

	void Initialize();
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);
};

