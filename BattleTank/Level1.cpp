#include <iostream>

#include "Level1.h"
#include "Math.h"

Level1::Level1(const Resource& resource, const sf::Vector2f& mapSize, Player1& player1, Player1& player2, Bird& bird):
	m_resource(resource),
	m_mapSize(mapSize),
	m_mapPlayer1(m_mapSize, 0, 113, 4, 0),
	m_mapPlayer2(m_mapSize, 0, 113, 4, 0),
	m_player1Mode(false),
	m_player2Mode(false),
	m_bird(bird),
	m_player1(player1),
	m_player2(player2),
	m_enemy(player1.m_movementSpeed),
	m_enemySpawnTimer(0),
	m_enemySpawnRate(0),
	m_mapOrigin(nullptr),
	m_blockoffset(nullptr)
{
}

const void Level1::Player1ModeOrPlayer2Mode(bool& player1, bool& player2)
{
	m_player1Mode = player1;
	m_player2Mode = player2;
}

const void Level1::Player1AndPlayer2(const Player1& player1, const Player1& player2)
{
	m_player1 = player1;
	m_player2 = player2;
}

const void Level1::BaseBird(const Bird& bird)
{
	m_bird = bird;
}

void Level1::UpdatePlayer1Mode(sf::RenderWindow& window, const float& deltatimeTimerMilli)
{
	if (m_player1.m_checkDestroy == false && m_enemy.m_checkDestroy == false) {

		m_mapPlayer1.Update();

		m_bird.Update();

		m_player1.Update(
			window,
			&m_resource.player1textureUp,
			&m_resource.player1textureLeft,
			&m_resource.player1textureDown,
			&m_resource.player1textureRight,
			&m_resource.bulletTexture,
			&m_mapSize,
			deltatimeTimerMilli
		);


		m_enemy.Update(
			window,
			&m_resource.enemytextureUp,
			&m_resource.enemytextureLeft,
			&m_resource.enemytextureDown,
			&m_resource.enemytextureRight,
			&m_resource.bulletTexture,
			&m_mapSize,
			deltatimeTimerMilli);

		for (size_t i = 0; i < m_player1.m_bullets.size(); ++i) {

			if (Math::Collision(m_bird.m_sprite.getGlobalBounds(), m_player1.m_bullets[i].m_bulletSprite.getGlobalBounds())) {

				std::cout << "bird died by player" << std::endl;
			}
		}

		for (size_t i = 0; i < m_enemy.m_bullets.size(); ++i) {

			if (Math::Collision(m_player1.m_sprite.getGlobalBounds(), m_enemy.m_bullets[i].m_bulletSprite.getGlobalBounds())) {

				m_enemy.m_bullets.erase(m_enemy.m_bullets.begin() + i);
				m_player1.m_checkDestroy = true;
			}

			if (Math::Collision(m_bird.m_sprite.getGlobalBounds(), m_enemy.m_bullets[i].m_bulletSprite.getGlobalBounds())) {

				std::cout << "bird died by enemy" << std::endl;
			}
		}
	}
}

void Level1::Initialize(sf::RenderWindow& window)
{
	m_mapPlayer1.Initialize(window);

	m_mapPlayer2.Initialize(window);

	m_mapOrigin = m_mapPlayer1.GetMapOrigin();
	m_blockoffset = m_mapPlayer1.GetBlockOffset();

	m_enemySpawnRate = 1000;

	m_enemy.Initialize(
		m_mapOrigin,
		m_blockoffset,
		sf::Vector2f(16, 16),
		sf::Vector2f(5.25, 5));

	m_gameOverText.Initialize();

}

void Level1::Load()
{
	m_mapPlayer1.Load(
		&m_resource.grassTexture,
		&m_resource.brickTexture,
		&m_resource.steelTexture,
		&m_resource.waterTexture);

	m_mapPlayer2.Load(
		&m_resource.grassTexture,
		&m_resource.brickTexture,
		&m_resource.steelTexture,
		&m_resource.waterTexture);

	m_enemy.Load(&m_resource.enemytextureDown);

	m_gameOverText.Load(&m_resource.gameFont);
}

void Level1::Update(sf::RenderWindow& window, const float& deltatimeTimerMilli)
{
	if (m_player1.m_checkDestroy == true || m_enemy.m_checkDestroy == true) {
		
		m_gameOverText.m_text.setPosition(
			(window.getSize().x/2) - (m_gameOverText.m_text.getGlobalBounds().width/2),
			(window.getSize().y/2) - (m_gameOverText.m_text.getGlobalBounds().height/2));

		m_gameOverText.m_text.setString("Game Over");
	}
	else {

		if (m_player1Mode) {

			UpdatePlayer1Mode(window, deltatimeTimerMilli);
		}
	}
	if (m_enemy.m_checkDestroy == false) {

		for (size_t i = 0; i < m_player1.m_bullets.size(); ++i) {

			if (Math::Collision(m_player1.m_bullets[i].m_bulletSprite.getGlobalBounds(), m_enemy.m_sprite.getGlobalBounds())) {

				m_player1.m_bullets.erase(m_player1.m_bullets.begin() + i);
				m_enemy.m_checkDestroy = true;
			}
		}
	}
}

void Level1::Draw(sf::RenderWindow& window)
{

	if (m_player1Mode) {

		m_mapPlayer1.Draw(window);
		m_player1.Draw(window);
	}
	m_enemy.Draw(window);
	m_bird.Draw(window);

	if (m_player1.m_checkDestroy == true || m_enemy.m_checkDestroy == true) {

		window.draw(m_gameOverText.m_text);
	}
}

Level1::~Level1()
{
}