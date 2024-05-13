#include <iostream>

#include "Resource.h"

void Resource::Load()
{
	if (
		playertextureUp.loadFromFile("assets/player/playerTexture/playerTankUp.png") &&
		playertextureLeft.loadFromFile("assets/player/playerTexture/playerTankLeft.png") &&
		playertextureDown.loadFromFile("assets/player/playerTexture/playerTankDown.png") &&
		playertextureRight.loadFromFile("assets/player/playerTexture/playerTankRight.png")
		) {

		std::cout << "Player loaded successfully" << std::endl;
	}

	if (enemytextureUp.loadFromFile("assets/enemy/enemyTexture/enemyTankUp.png") &&
		enemytextureLeft.loadFromFile("assets/enemy/enemyTexture/enemyTankLeft.png") &&
		enemytextureDown.loadFromFile("assets/enemy/enemyTexture/enemyTankDown.png") &&
		enemytextureRight.loadFromFile("assets/enemy/enemyTexture/enemyTankRight.png")
		) {

		std::cout << "Enemy loaded successfully" << std::endl;
	}

	if (bulletTexture.loadFromFile("assets/bullet/bulletTexture/bullet.png")){

		std::cout << "Bullet loaded successfully" << std::endl;
	}

	if (gameFont.loadFromFile("assets/fonts/gameFont.ttf")) {

		std::cout << "GameOver font loaded successfully" << std::endl;
	}
}
