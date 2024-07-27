#pragma once
#include "Map.h"

class Level {

private:

	bool m_player1Mode;
	bool m_player2Mode;

	const sf::Vector2f* m_windowResolution;

	sf::RectangleShape m_mainBackground;

	sf::Vector2f m_mapBackgroundSize;
	sf::Vector2f m_mapBackgroundPosition;
	sf::RectangleShape m_mapBackground;

	Map m_map;

public:

	Level(int totalBrickBlocks);
	~Level();

	void Initialize(const sf::Vector2f* windowResolution);
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);

private:

	void Player1ModeUpdate();
	void Player2ModeUpdate();

	void Lost();
	void Completed();

	void Exit();

public:

	void SetPLayerMode(bool& player1Mode, bool& player2Mode);
};

