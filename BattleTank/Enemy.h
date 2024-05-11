#pragma once
#include <vector>

#include "Resource.h"
#include "Bullet.h"

class Enemy {

public:

	sf::Sprite m_sprite;
	std::vector<Bullet> m_bullets;

	float m_checkDestroy;

private:

	sf::Vector2f m_spriteSize;

	sf::Vector2f m_scale;

	sf::Vector2f m_movementSpeed;
	sf::Vector2f m_position;
	sf::Vector2f m_centre;
	
	sf::RectangleShape m_collisionBox;

	sf::Texture m_bulletTexture;

	int m_direction;

	float m_directionTimer;
	float m_directionChangeRate;

	float m_fireRateTimer;
	float m_fireRate;

public:

	Enemy();
	~Enemy();

	void Initialize(const sf::Vector2f& spriteSize, const sf::Vector2f& scale);
	void Load(sf::Texture* enemyTextureDown);

	void Update(
		sf::RenderWindow& window,
		sf::Texture* enemyTextureUp,
		sf::Texture* enemyTextureLeft,
		sf::Texture* enemyTextureDown,
		sf::Texture* enemyTextureRight,
		sf::Texture* bulletTexture,
		const float& deltatimeTimerMilli);

	void Draw(sf::RenderWindow& window);
};

