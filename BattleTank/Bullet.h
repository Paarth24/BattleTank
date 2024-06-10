#pragma once

#include "SFML/Graphics.hpp"

class Bullet {

public:

	sf::Sprite m_bulletSprite;

	sf::RectangleShape m_collisionBox;

private:
	
	sf::Vector2f m_position;

	int m_playerDirectionCheck;

public:

	Bullet();
	~Bullet();

	void Initialize(
		const sf::Color& color,
		int& playerDirection,
		sf::Texture* playerBulletTexture,
		const sf::Vector2f& playerPosition,
		const sf::Vector2f& playerCentre);

	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);

	void BulletShootUp();
	void BulletShootLeft();
	void BulletShootDown();
	void BulletShootRight();
};

