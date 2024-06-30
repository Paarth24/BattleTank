#pragma once

#include "Resource.h"
#include "Map.h"
#include "Base.h"
#include "Player1.h"
#include "Enemy.h"
#include "GameOverText.h"

#include <vector>

class Level1 {

private:
	
	Resource m_resource;

	Map m_mapPlayer1;
	Map m_mapPlayer2;

	bool m_player1Mode;
	bool m_player2Mode;

	Player1 m_player1;
	Player1 m_player2;

	Base m_base;

	Enemy m_enemy;

	float m_enemySpawnTimer;
	float m_enemySpawnRate;

	GameOverText m_gameOverText;

public:

	sf::Vector2f m_mapSize;
	const sf::Vector2f* m_mapOrigin;
	const sf::Vector2f* m_blockoffset;

public:

	Level1(const Resource& resource, const sf::Vector2f& mapSize, Player1& player1, Player1& player2, Base& base);
	~Level1();

	void Initialize(sf::RenderWindow& window);
	void Load();
	void Update(sf::RenderWindow& window, const float& deltatimeTimerMilli);
	void Draw(sf::RenderWindow& window);

	const void Player1ModeOrPlayer2Mode(bool& player1, bool& player2);
	const void Player1AndPlayer2(const Player1& player1, const Player1& player2);
	const void CreatingBase(const Base& base);

	void UpdatePlayer1Mode(sf::RenderWindow& window, const float& deltatimeTimerMilli);
};

