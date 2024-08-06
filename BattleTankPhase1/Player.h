#pragma once

#include <iostream>
#include <vector>

#include "Bullet.h"

class Player {

	int m_id;
	const sf::Vector2f* m_blockOffset;

	sf::Texture m_texture;

	sf::Sprite m_sprite;

	int m_lives;
	sf::Vector2f m_scale;
	sf::Vector2f m_position;

	std::string m_direction;
	sf::Vector2f m_movementSpeed;

	bool m_collisionUp;
	bool m_collisionLeft;
	bool m_collisionDown;
	bool m_collisionRight;

	sf::Texture m_bulletTexture;

	float m_bulletFireRate;
	float m_bulletFireTimer;

	bool m_powerUpTaken;

public:

	Player();
	~Player();

	void Initialize(int id, const sf::Vector2f* blockOffset, const sf::Vector2f* mapBackgroundPosition);
	void Load();
	void Update(std::vector<Bullet>& playerNormalBulletVector, std::vector<Bullet>& playerArmourBulletVector, float deltaTimerMilli);
	void Draw(sf::RenderWindow& window);

private:

	void Move();
	void Shoot(std::vector<Bullet>& playerNormalBulletVector, std::vector<Bullet>& playerArmourBulletVector);

public:

	void SetCollision(bool collision);
	void CollissionWithIceBlock();
	void Freeze();
	void SetPowerUp();
	void Destroy();
	void Over();

	inline const sf::Sprite& GetSprite() const { return m_sprite; }
	inline const std::string& GetDirection() const { return m_direction; }
	inline const sf::Vector2f& GetMovementSpeed() const { return m_movementSpeed; }
};

