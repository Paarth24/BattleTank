#pragma once

#include <iostream>
#include <vector>

#include "Bullet.h"

class Player {

	bool m_checkDestroy;

	int m_id;
	const sf::Vector2f* m_blockOffset;
	const sf::Vector2f* m_mapBackgroundPosition;

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

	bool m_collisionWithIce;

public:

	Player();
	~Player();

	void Initialize(int id, const sf::Vector2f* mapBackgroundPosition, const sf::Vector2f* blockOffset);
	void Load();
	void Update(std::vector<Bullet>& playerNormalBulletVector, std::vector<Bullet>& playerArmourBulletVector, float deltaTimerMilli);
	void Draw(sf::RenderWindow& window);

private:

	void Move();
	void Shoot(std::vector<Bullet>& playerNormalBulletVector, std::vector<Bullet>& playerArmourBulletVector);

public:

	void SetCollision(bool collision);
	void CollissionWithIceBlock(bool collision);
	void Freeze();
	void SetPowerUp();
	void Destroy();

	void NextLevel();

private:

	void Over();

public:

	inline const bool& GetCheckDestroy() const { return m_checkDestroy; }
	inline const int& GetLives() const { return m_lives; }
	inline const sf::Sprite& GetSprite() const { return m_sprite; }
	inline const std::string& GetDirection() const { return m_direction; }
	inline const sf::Vector2f& GetMovementSpeed() const { return m_movementSpeed; }
};

