#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

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

	bool m_collisionWithBrickBlock;

public:

	Player();
	~Player();

	void Initialize(int id, const sf::Vector2f* blockOffset, const sf::Vector2f* mapBackgroundPosition);
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);

private:

	void Move();
	void Shoot();

public:

	void SetCollision(bool collision);
	void CollisionWithBrickBlock(bool brickCollision);
	void CollissionWithIceBlock();
	void Freeze();
	void SetPowerUp();
	void Destroy();
	void Over();

	inline const sf::Sprite& GetSprite() { return m_sprite; }
	inline const std::string& GetDirection() { return m_direction; }
	inline const sf::Vector2f& GetMovementSpeed() { return m_movementSpeed; }
};

