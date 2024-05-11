#include <iostream>

#include "Level1.h"
#include "Math.h"

Level1::Level1():
	m_enemySpawnTimer(0),
	m_enemySpawnRate(0)
{
}


void Level1::Initialize()
{
	m_enemySpawnRate = 1000;
	
	player.Initialize(sf::Vector2f(70, 70), sf::Vector2f(2, 2));

	enemy.Initialize(sf::Vector2f(70, 70), sf::Vector2f(2, 2));
}

void Level1::Load()
{
	resource.Load();

	player.Load(&resource.playertextureUp);

	enemy.Load(&resource.enemytextureDown);

}

void Level1::Update(sf::RenderWindow& window, const float& deltatimeTimerMilli)
{
	player.Update(
		window,
		&resource.playertextureUp,
		&resource.playertextureLeft,
		&resource.playertextureDown,
		&resource.playertextureRight,
		&resource.bulletTexture,
		deltatimeTimerMilli
		);

	enemy.Update(
		window,
		&resource.enemytextureUp,
		&resource.enemytextureLeft,
		&resource.enemytextureDown,
		&resource.enemytextureRight,
		&resource.bulletTexture,
		deltatimeTimerMilli);
	
	if (player.m_checkDestroy == 1) {

		for (size_t i = 0; i < enemy.m_bullets.size(); ++i) {

			if (Math::Collision(player.m_sprite.getGlobalBounds(), enemy.m_bullets[i].m_bulletSprite.getGlobalBounds())) {

				enemy.m_bullets.erase(enemy.m_bullets.begin() + i);
				player.m_checkDestroy = 0;
			}
		}
	}

	if (enemy.m_checkDestroy == 1) {

		for (size_t i = 0; i < player.m_bullets.size(); ++i) {

			if (Math::Collision(player.m_bullets[i].m_bulletSprite.getGlobalBounds(), enemy.m_sprite.getGlobalBounds())) {

				player.m_bullets.erase(player.m_bullets.begin() + i);
				enemy.m_checkDestroy = 0;
			}
		}
	}
}

void Level1::Draw(sf::RenderWindow& window)
{
	player.Draw(window);
	enemy.Draw(window);
}

Level1::~Level1()
{
}