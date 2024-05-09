#include "Level1.h"

Level1::Level1()
{
}


void Level1::Initialize()
{
	player.Initialize(sf::Vector2f(70, 70), sf::Vector2f(2, 2));
	enemy.Initialize(sf::Vector2f(70, 70), sf::Vector2f(2, 2));
}

void Level1::Load()
{
	resource.Load();

	player.Load(&resource.playertextureUp);
	enemy.Load(&resource.enemytextureDown);
}

void Level1::Update(const float& deltatimeTimerMilli)
{
	player.Update(
		&resource.playertextureUp,
		&resource.playertextureLeft,
		&resource.playertextureDown,
		&resource.playertextureRight,
		&resource.bulletTexture,
		enemy.m_sprite,
		deltatimeTimerMilli
		);

	enemy.Update(
		&resource.enemytextureUp,
		&resource.enemytextureLeft,
		&resource.enemytextureDown,
		&resource.enemytextureRight,
		&resource.bulletTexture,
		deltatimeTimerMilli);
}

void Level1::Draw(sf::RenderWindow& window)
{
	player.Draw(window);
	enemy.Draw(window);
}

Level1::~Level1()
{
}