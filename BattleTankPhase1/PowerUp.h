#pragma once
#include <SFML/Graphics.hpp>

class PowerUp {

private:

	bool m_checkDestroy;
	bool m_spawned;

	std::string m_type;
	const sf::Vector2f* m_blockOffset;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_scale;

	sf::Vector2f m_gridIndex;
	sf::Vector2f m_position;

	float m_spawnTime;
	float m_spawnTimer;

	float m_despawnTime;

public:

	PowerUp();
	~PowerUp();

	void Initialize(
		const sf::Vector2f* mapBackgroundPosition,
		const sf::Vector2f* blockOffset);

	void Load();
	void Update(float deltatimermilli);
	void Draw(sf::RenderWindow& window);

	void SetType(std::string type) { m_type = type; };
	void SetGridIndex(sf::Vector2f gridIndex) { m_gridIndex = gridIndex; }

	const bool GetCheckDestroy() { return m_checkDestroy; }
	const bool IfSpawned() { return m_spawned; }
	const std::string GetType() { return m_type; }
	const sf::Sprite& GetSprite() const { return m_sprite; }

	void Destroy() { m_checkDestroy = true; }
};
