#include <iostream>

#include "Resource.h"

void Resource::Load()
{
	if (grassTexture.loadFromFile("assets/world/map blocks/grass.png") &&
		brickTexture.loadFromFile("assets/world/map blocks/brick.png") &&
		steelTexture.loadFromFile("assets/world/map blocks/steel.png") &&
		waterTexture.loadFromFile("assets/world/map blocks/water.png")) {

		std::cout << "Map blocks loaded successfully" << std::endl;;
	}

	if (baseTexture.loadFromFile("assets/base/baseTexture.png")) {

		std::cout << "Base loaded successfully" << std::endl;
	}
	if (
		player1textureUp.loadFromFile("assets/player1/player1Texture/yellow/up1.png") &&
		player1textureLeft.loadFromFile("assets/player1/player1Texture/yellow/left1.png") &&
		player1textureDown.loadFromFile("assets/player1/player1Texture/yellow/down1.png") &&
		player1textureRight.loadFromFile("assets/player1/player1Texture/yellow/right1.png")
		) {

		std::cout << "Player loaded successfully" << std::endl;
	}

	if (enemytextureUp.loadFromFile("assets/enemy/enemyTexture/red/up1.png") &&
		enemytextureLeft.loadFromFile("assets/enemy/enemyTexture/red/left1.png") &&
		enemytextureDown.loadFromFile("assets/enemy/enemyTexture/red/down1.png") &&
		enemytextureRight.loadFromFile("assets/enemy/enemyTexture/red/right1.png")
		) {

		std::cout << "Enemy loaded successfully" << std::endl;
	}

	if (bulletTexture.loadFromFile("assets/bullet/bulletTexture/bullet.png")) {

		std::cout << "Bullet loaded successfully" << std::endl;
	}

	if (gameFont.loadFromFile("assets/fonts/gameFont.ttf")) {

		std::cout << "GameOver font loaded successfully" << std::endl;
	}
}