#include "Status.h"

#include <iostream>

Status::Status():
	m_totalEnemyTanks(0),
	m_enemyTankSymbols(nullptr)
{
}

void Status::InitializeEnemyTankSymbol()
{
}

void Status::LoadEnemyTankSymbol()
{
	for (int i = 0; i < m_totalEnemyTanks; ++i) {

		m_enemyTankSymbols[i].setTexture(m_enemyTankSymbolTexture);
	}
}

void Status::UpdateEnemyTankSymbol()
{

}

void Status::DrawEnemyTankSymbol(sf::RenderWindow& window)
{
	for (int i = 0; i < m_totalEnemyTanks; ++i) {

		window.draw(m_enemyTankSymbols[i]);
	}
}

void Status::Initialize(int totalEnemyTanks)
{
	m_totalEnemyTanks = totalEnemyTanks;

	m_enemyTankSymbols = new sf::Sprite[m_totalEnemyTanks];

	InitializeEnemyTankSymbol();
}

void Status::Load()
{
	if (m_enemyTankSymbolTexture.loadFromFile("assets/enemy/enemyTexture/up.png")) {

		std::cout << "Enemy tank symbol loaded successfully" << std::endl;

		LoadEnemyTankSymbol();
	}
}

void Status::Update()
{
	UpdateEnemyTankSymbol();
}

void Status::Draw(sf::RenderWindow& window)
{
	DrawEnemyTankSymbol(window);
}

Status::~Status()
{
	delete[] m_enemyTankSymbols;
}