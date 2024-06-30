#pragma once

#include "SFML/Graphics.hpp"

class Bullet {

public:

	sf::Sprite m_bulletSprite;

	sf::RectangleShape m_collisionBox;

private:
	
	sf::Vector2f m_position;
	sf::Vector2f m_spriteSize;
	sf::Vector2f m_scale;

	int m_playerDirectionCheck;

public:

	Bullet();
	~Bullet();

	void Initialize(
		const sf::Color& color,
		int& playerDirection,
		sf::Texture* playerBulletTexture,
		const sf::Vector2f& playerPosition,
		const sf::Vector2f* blockOffset,
		const sf::Vector2f& playerCentre);

	void Load();
	void Update(const float& deltatimeTimerMilli);
	void Draw(sf::RenderWindow& window);

	bool IfBulletOutOfWindow(const sf::Vector2f* mapOrigin, const sf::Vector2f* mapSize);

	void BulletShootUp(const float& deltatimeTimerMilli);
	void BulletShootLeft(const float& deltatimeTimerMilli);
	void BulletShootDown(const float& deltatimeTimerMilli);
	void BulletShootRight(const float& deltatimeTimerMilli);
};

