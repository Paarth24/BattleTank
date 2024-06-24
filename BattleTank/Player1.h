#pragma once

#include "Bullet.h"

#include <vector>

class Player1 {

public:

	sf::Sprite m_sprite;
	std::vector<Bullet> m_bullets;

	bool m_checkDestroy;
	sf::Vector2f m_movementSpeed;

private:

	sf::Vector2f m_spriteSize;

	sf::Vector2f m_scale;

	sf::Vector2f m_position;
	sf::Vector2f m_fireCentre;

	sf::RectangleShape m_collisionBox;

	int m_direction;

	float m_fireRateTimer;
	float m_fireRate;

public:
	
	Player1(const sf::Vector2f& movementSpeed);
	~Player1();

	void Initialize(
		const sf::Vector2f* mapSize,
		const sf::Vector2f* mapOrigin,
		const sf::Vector2f* blockOffset,
		sf::RenderWindow& window,
		const sf::Vector2f& spriteSize,
		const sf::Vector2f& scale);

	void Load(sf::Texture* playerTextureUp);

	void Update(
		sf::RenderWindow& window,
		sf::Texture* playerTextureUp,
		sf::Texture* playerTextureLeft,
		sf::Texture* playerTextureDown,
		sf::Texture* playerTextureRight,
		sf::Texture* bulletTexture,
		const sf::Vector2f* mapSize,
		const float& deltatimeTimerMilli);

	void Draw(sf::RenderWindow& window);

	const void TankMoveUp(const sf::Vector2f* mapOrigin, const sf::Vector2f* mapSize, sf::Texture* playerTextureUp);
	const void TankMoveLeft(const sf::Vector2f* mapOrigin, const sf::Vector2f* mapSize, sf::Texture* playerTextureLeft);
	const void TankMoveDown(const sf::Vector2f* mapOrigin, const sf::Vector2f* mapSize, sf::Texture* playerTextureDown);
	const void TankMoveRight(const sf::Vector2f* mapOrigin, const sf::Vector2f* mapSize, sf::Texture* playerTextureRight);
};

