#pragma once

#include "Resource.h"
#include "Player.h"
#include "Enemy.h"
#include "GameOverText.h"

#include <vector>

class Level1 {

private:
	
	Resource m_resource;
	Player m_player;
	Enemy m_enemy;

	float m_enemySpawnTimer;
	float m_enemySpawnRate;

	GameOverText m_gameOverText;

public:

	Level1(const Resource& resource);
	~Level1();

	void Initialize();

	void Load();

	void Update(sf::RenderWindow& window, const float& deltatimeTimerMilli);
	void Draw(sf::RenderWindow& window);
};

