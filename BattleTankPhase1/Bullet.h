#pragma once
#include <SFML/Graphics.hpp>

class Bullet {

private:

	std::string m_id;
	std::string m_type;

	sf::Texture* m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_scale;
	sf::Vector2f m_position;

	std::string m_direction;
	sf::Vector2f m_movementSpeed;

public:

	Bullet(const std::string& id, const std::string& type);
	~Bullet();

	void Initialize(
		sf::Texture* bulletTexture,
		const sf::Vector2f* blockOffset,
		const sf::Vector2f& position,
		const sf::Vector2f& tankSize,
		const std::string& direction);
	void Update();
	void Draw(sf::RenderWindow& window);

private:

	void Move();

public:

	inline const std::string& GetId() const { return m_id; }
	inline const sf::Sprite& GetSprite() const { return m_sprite; }
	inline const std::string& GetDirection() const { return m_direction; }
	inline const sf::Vector2f& GetMovementSpeed() const { return m_movementSpeed; }
};

