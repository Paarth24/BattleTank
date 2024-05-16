#include <iostream>

#include "Level1.h"
#include "Math.h"

Level1::Level1(const Resource& resource):
	m_resource(resource),
	m_enemySpawnTimer(0),
	m_enemySpawnRate(0)
{
}


void Level1::Initialize(sf::RenderWindow& window)
{
	m_enemySpawnRate = 1000;
	
	m_bird.Initialize(window);

	m_player.Initialize(sf::Vector2f(70, 70), sf::Vector2f(2, 2));

	m_enemy.Initialize(sf::Vector2f(70, 70), sf::Vector2f(2, 2));

	m_gameOverText.Initialize();
}

void Level1::Load()
{
	m_bird.Load(&m_resource.birdTexture);

	m_player.Load(&m_resource.playertextureUp);

	m_enemy.Load(&m_resource.enemytextureDown);

	m_gameOverText.Load(&m_resource.gameFont);
}

void Level1::Update(sf::RenderWindow& window, const float& deltatimeTimerMilli)
{
	if (m_player.m_checkDestroy == 0 || m_enemy.m_checkDestroy == 0) {

		m_gameOverText.m_textGameOver.setPosition(
			(window.getSize().x / 2) - (m_gameOverText.m_textGameOver.getGlobalBounds().width / 2),
			(window.getSize().y / 2) - m_gameOverText.m_textGameOver.getGlobalBounds().height*2);

		m_gameOverText.m_textCause.setPosition(
			(window.getSize().x / 2) - (m_gameOverText.m_textCause.getGlobalBounds().width / 2),
			m_gameOverText.m_textGameOver.getPosition().y + m_gameOverText.m_textGameOver.getGlobalBounds().height*2);

	}
	else if (m_player.m_checkDestroy == 1 && m_enemy.m_checkDestroy == 1) {

		m_bird.Update();

		m_player.Update(
			window,
			&m_resource.playertextureUp,
			&m_resource.playertextureLeft,
			&m_resource.playertextureDown,
			&m_resource.playertextureRight,
			&m_resource.bulletTexture,
			deltatimeTimerMilli
			);

		m_enemy.Update(
			window,
			&m_resource.enemytextureUp,
			&m_resource.enemytextureLeft,
			&m_resource.enemytextureDown,
			&m_resource.enemytextureRight,
			&m_resource.bulletTexture,
			deltatimeTimerMilli);

		for (size_t i = 0; i < m_player.m_bullets.size(); ++i) {

			if (Math::Collision(m_bird.m_sprite.getGlobalBounds(), m_player.m_bullets[i].m_bulletSprite.getGlobalBounds())) {

				m_gameOverText.m_textCause.setString("Bird killed by player");

				m_player.m_checkDestroy = 0;

				std::cout << "bird died by player" << std::endl;
			}

			else if (Math::Collision(m_player.m_bullets[i].m_bulletSprite.getGlobalBounds(), m_enemy.m_sprite.getGlobalBounds())) {

				m_gameOverText.m_textCause.setString("enemy killed by player");

				m_player.m_bullets.erase(m_player.m_bullets.begin() + i);
				m_enemy.m_checkDestroy = 0;
			}
		}

		for (size_t i = 0; i < m_enemy.m_bullets.size(); ++i) {

			if (Math::Collision(m_bird.m_sprite.getGlobalBounds(), m_enemy.m_bullets[i].m_bulletSprite.getGlobalBounds())) {

				m_gameOverText.m_textCause.setString("Bird killed by enemy");

				m_player.m_checkDestroy = 0;

				std::cout << "bird died by enemy" << std::endl;

			}
			else if (Math::Collision(m_player.m_sprite.getGlobalBounds(), m_enemy.m_bullets[i].m_bulletSprite.getGlobalBounds())) {

				m_gameOverText.m_textCause.setString("player killed by enemy");

				m_enemy.m_bullets.erase(m_enemy.m_bullets.begin() + i);
				m_player.m_checkDestroy = 0;
			}
		}
	}
}

void Level1::Draw(sf::RenderWindow& window)
{
	if (m_player.m_checkDestroy == 0 || m_enemy.m_checkDestroy == 0) {

		m_gameOverText.Draw(window);
	}

	m_bird.Draw(window);

	m_player.Draw(window);
	m_enemy.Draw(window);

}

Level1::~Level1()
{
}