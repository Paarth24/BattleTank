#pragma once
#include <SFML/Graphics.hpp>

class Base {

private:

	bool m_checkDestroy;
	int m_lives;

	const sf::Vector2f* m_blockOffset;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_position;
	sf::Vector2f m_scale;

	sf::Text m_gameOverText;

public:

	Base();
	~Base();

	void Initialize(
		const sf::Vector2f* blockOffset,
		const sf::Vector2f* mapBackgroundPosition,
		const sf::Vector2f* mapBackgroundSize);

	void Load(
		const sf::Font* gameFont,
		const sf::Vector2f* mapBackgroundPosition,
		const sf::Vector2f* mapBackgroundSize);

	void Draw(sf::RenderWindow& window);

public:

	//void PowerUpUsed();
	void Destroy();

	inline const sf::Sprite& GetSprite() const { return m_sprite; }
	inline const bool GetCheckDestroy() const { return m_checkDestroy; }
};

