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

	void Initialize(
		const sf::Vector2f* mapOrigin,
		const sf::Vector2f* blockOffset,
		const sf::Vector2f& spriteSize);

	void Load(sf::Texture* enemyTextureDown);

	void Update(
		sf::RenderWindow& window,
		sf::Texture* enemyTextureUp,
		sf::Texture* enemyTextureLeft,
		sf::Texture* enemyTextureDown,
		sf::Texture* enemyTextureRight,
		sf::Texture* bulletTexture,
		const sf::Vector2f* mapSize,
		const sf::Vector2f* blockOffset,
		const float& deltatimeTimerMilli);

	void Draw(sf::RenderWindow& window);

	const void TankMoveUp(
		const sf::Vector2f* mapOrigin,
		const sf::Vector2f* mapSize,
		sf::Texture* playerTextureUp,
		const float& deltatimeTimerMilli);

	const void TankMoveLeft(
		const sf::Vector2f* mapOrigin,
		const sf::Vector2f* mapSize,
		sf::Texture* playerTextureLeft,
		const float& deltatimeTimerMilli);

	const void TankMoveDown(
		const sf::Vector2f* mapOrigin,
		const sf::Vector2f* mapSize,
		sf::Texture* playerTextureDown,
		const float& deltatimeTimerMilli);

	const void TankMoveRight(
		const sf::Vector2f* mapOrigin,
		const sf::Vector2f* mapSize,
		sf::Texture* playerTextureRight,
		const float& deltatimeTimerMilli);
};

