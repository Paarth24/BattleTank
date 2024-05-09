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

public:

	Level1();
	~Level1();

	void Initialize();
	void Load();
	void Update(const float& deltatimeTimerMilli);
	void Draw(sf::RenderWindow& window);
};

