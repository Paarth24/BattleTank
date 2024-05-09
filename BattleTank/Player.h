#pragma once

#include "Bullet.h"

#include <vector>

class Player {

private:

	sf::Vector2f m_spriteSize;
	sf::Sprite m_sprite;

	sf::Vector2f m_scale;

	sf::Vector2f m_movementSpeed;
	sf::Vector2f m_position;
	sf::Vector2f m_centre;

	sf::RectangleShape m_collisionBox;

	std::vector<Bullet> m_bullets;

	int m_direction;

	float m_fireRateTimer;
	float m_fireRate;

public:
	
	Player();
	~Player();

	void Initialize(const sf::Vector2f& , const sf::Vector2f& scale);
	void Load(sf::Texture* playerTextureUp);

	void Update(
		sf::Texture* playerTextureUp,
		sf::Texture* playerTextureLeft,
		sf::Texture* playerTextureDown,
		sf::Texture* playerTextureRight,
		sf::Texture* bulletTexture,
		const sf::Sprite& enemySprite,
		const float& deltatimeTimerMilli);

	void Draw(sf::RenderWindow& window);
};

