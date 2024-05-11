#pragma once

#include "Resource.h"
#include "Player.h"
#include "Enemy.h"

#include <vector>

class Level1 {

private:

	Resource resource;

	Player player;
	Enemy enemy;

	float m_enemySpawnTimer;
	float m_enemySpawnRate;

public:

	Level1();
	~Level1();

	void Initialize();
	void Load();
	void Update(sf::RenderWindow& window, const float& deltatimeTimerMilli);
	void Draw(sf::RenderWindow& window);
};

