#pragma once
#include <vector>

#include "Resource.h"
#include "Bullet.h"

class Enemy {

public:

	sf::Sprite m_sprite;
	std::vector<Bullet> m_bullets;

	bool m_checkDestroy;

private:

	sf::Vector2f m_spriteSize;

	sf::Vector2f m_scale;

	sf::Vector2f m_movementSpeed;
	sf::Vector2f m_position;
	sf::Vector2f m_fireCentre;
	
	sf::RectangleShape m_collisionBox;

	sf::Texture m_bulletTexture;

	int m_direction;

	float m_fireRateTimer;
	float m_fireRate;

public:

	Enemy(const sf::Vector2f& movementSpeed);
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
		const sf::Vector2f* mapSize,
		const float& deltatimeTimerMilli);

	void Draw(sf::RenderWindow& window);

	bool DidSpriteCollideWithMap(sf::RenderWindow& window, const sf::Vector2f* mapSize);

	const void TankMoveUp(sf::Texture* enemyTextureUp);
	const void TankMoveLeft(sf::Texture* enemyTextureLeft);
	const void TankMoveDown(sf::Texture* enemyTextureDown);
	const void TankMoveRight(sf::Texture* enemyTextureRight);
};

