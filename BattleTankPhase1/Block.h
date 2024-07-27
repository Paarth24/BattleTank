#pragma once
#include <SFML/Graphics.hpp>

class Block {

private:

	sf::Texture m_texture;
	sf::Sprite m_sprite;

public:

	Block();
	~Block();

	void Initialize(const sf::Vector2i& gridIndex, const sf::Vector2f* blockOffset, const sf::Vector2f* mapBackgroundPosition);
	void Load(const std::string& fileName, const sf::Vector2f* blockOffset);
	void Draw(sf::RenderWindow& window);
};

class BrickBlock :public Block {

private:

	bool m_checkDestroy;

public:

	void Destroy();
};

class SteelBlock :public Block {

private:

	bool m_checkDestroy;

public:

	void Destroy();
};

class WaterBlock :public Block {};
class GrassBlock :public Block {};
class IceBlock :public Block {};

