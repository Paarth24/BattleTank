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

	sf::Vector2f m_scale;

	int m_playerDirection;
	sf::Vector2f m_movementSpeed;
	sf::Vector2f m_playerPosition;
	sf::Vector2f m_playerCentre;

	sf::RectangleShape m_collisionBox;

	std::vector<Bullet> bullets;
	sf::Texture m_bulletTexture;

	float m_fireRateTimer;
	float m_fireRate;

public:
	
	Player(const sf::Vector2f& spriteSize, const sf::Vector2f& scale);
	~Player();

	void Initialize();
	void Load();
	void Update(const float& deltatimeTimerMilli);
	void Draw(sf::RenderWindow& window);
};

