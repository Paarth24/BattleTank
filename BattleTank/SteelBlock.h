#pragma once
#include "SFML/Graphics.hpp"

class SteelBlock {

private:

	bool m_checkDestroy;

	sf::Vector2f m_spriteSize;
	sf::Vector2f m_scale;
	sf::Vector2f m_position;

public:

	std::string m_id;

	sf::Sprite m_sprite;
	sf::Vector2i m_gridIndex;

public:

	SteelBlock();
	~SteelBlock();

	void Initialize(const sf::Vector2f* mapOrigin, const sf::Vector2f* blockOffset);
	void Load(const sf::Texture* grassTexture);
	void Update();
	void Draw(sf::RenderWindow& window);
};
