#pragma once
#include "SFML/Graphics.hpp"

class IceBlock {

private:

	bool m_checkDestroy;

	sf::Vector2f m_size;
	sf::Vector2f m_scale;
	sf::Vector2f m_position;

public:

	std::string m_id;

	sf::Sprite m_sprite;
	sf::Vector2i m_gridIndex;

public:

	IceBlock();
	~IceBlock();

	void Initialize(const sf::Vector2f* mapOrigin, const sf::Vector2f* blockOffset);
	void Load(const sf::Texture* grassTexture);
	void Update();
	void Draw(sf::RenderWindow& window);
};
