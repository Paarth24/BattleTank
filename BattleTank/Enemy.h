#pragma once

#include "Bullet.h"

#include <vector>

class Enemy {

private:

	sf::Texture m_textureUp;
	sf::Texture m_textureDown;

	sf::Texture m_textureRight;
	sf::Texture m_textureLeft;

	sf::Vector2f m_spriteSize;
	sf::Sprite m_sprite;

	sf::Vector2f m_scale;

	sf::Vector2f m_movementSpeed;
	sf::Vector2f m_enemyPosition;
	sf::Vector2f m_enemyCentre;
	
	sf::RectangleShape m_collisionBox;

	std::vector<Bullet> bullets;
	sf::Texture m_bulletTexture;

	int m_enemyDirection;

	float m_fireRateTimer;
	float m_fireRate;

public:

	Enemy(const sf::Vector2f& spriteSize, const sf::Vector2f& scale);
	~Enemy();

	void Initialize();
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);
};

