#pragma once

#include "Resource.h"
#include "Bird.h"
#include "Player.h"
#include "Enemy.h"
#include "GameOverText.h"

#include <vector>

class Level1 {

private:
	
	Resource m_resource;

	bool m_player1Mode;
	bool m_player2Mode;

	Player m_player1;
	Player m_player2;

	Bird m_bird;

	Enemy m_enemy;

	float m_enemySpawnTimer;
	float m_enemySpawnRate;

	GameOverText m_gameOverText;

public:

	Level1(const Resource& resource);
	~Level1();

	void Initialize(const sf::RenderWindow& window);
	void Load();
	void Update(sf::RenderWindow& window, const float& deltatimeTimerMilli);
	void Draw(sf::RenderWindow& window);

	const void Player1ModeOrPlayer2Mode(bool& player1, bool& player2);
	const void Player1AndPlayer2(const Player& player1, const Player& player2);
	const void BaseBird(const Bird& bird);

	void UpdatePlayer1Mode(sf::RenderWindow& window, const float& deltatimeTimerMilli);
};

