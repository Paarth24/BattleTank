#pragma once
#include <SFML/Graphics.hpp>

class Block {

private:

	bool m_checkDestroy;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

public:

	Block();
	~Block();

	void Initialize(const sf::Vector2i& gridIndex, const sf::Vector2f* mapBackgroundPosition, const sf::Vector2f* blockOffset);
	void Load(const std::string& fileName, const sf::Vector2f* blockOffset);
	void Draw(sf::RenderWindow& window);

	const void Destroy() { m_checkDestroy = true; }

	inline const sf::Sprite& GetSprite() const { return m_sprite; }
	inline const bool& GetCheckDestroy() const { return m_checkDestroy; }
};

class BrickBlock :public Block {};
class SteelBlock :public Block {};
class WaterBlock :public Block {};
class GrassBlock :public Block {};
class IceBlock :public Block {};

