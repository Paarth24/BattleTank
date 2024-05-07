#pragma once

#include "SFML/Graphics.hpp"

class Bullet {

private:
	
	sf::RectangleShape m_bulletShape;
	sf::Vector2f m_position;

	int m_playerDirectionCheck;

public:

	Bullet();
	~Bullet();

	void Initialize(int& playerDirection);
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);

	void BulletShootUp();
	void BulletShootLeft();
	void BulletShootDown();
	void BulletShootRight();
};

