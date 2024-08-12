#pragma once

#include <iostream>
#include <vector>

#include "Bullet.h"

class Enemy {

	bool m_checkDestroy;

	std::string m_id;
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

	float m_directionRate;
	float m_directionTimer;

	float m_bulletFireRate;
	float m_bulletFireTimer;

	bool m_collisionWithIce;

	bool m_powerUpTaken;

public:

	Enemy();
	~Enemy();

	void Initialize(
		std::string id,
		const sf::Vector2f* mapBackgroundPosition,
		const sf::Vector2f* blockOffset);

	void Load();
	void Update(std::vector<Bullet>& enemyNormalBulletVector, std::vector<Bullet>& enemyArmourBulletVector, float deltaTimerMilli);
	void Draw(sf::RenderWindow& window);

private:

	void Move();
	void Shoot(std::vector<Bullet>& enemyNormalBulletVector, std::vector<Bullet>& enemyArmourBulletVector);
	void Over() { m_checkDestroy = true; }

public:

	void SetCollision(bool collision);
	void CollissionWithIceBlock(bool collision);
	//void Freeze();
	//void SetPowerUp();
	void Destroy();

	inline const bool& const GetCheckDestroy() const { return m_checkDestroy; }
	inline const sf::Sprite& GetSprite() const { return m_sprite; }
	inline const std::string& GetDirection() const { return m_direction; }
	inline const sf::Vector2f& GetMovementSpeed() const { return m_movementSpeed; }
	
};

class BasicTank :public Enemy {};
class LightBattleTank :public Enemy {};
class DoubleBarrelTank : public Enemy {};
class DestroyerTank :public Enemy {};
class FighterTank :public Enemy {};

