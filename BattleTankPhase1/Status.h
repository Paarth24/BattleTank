#pragma once
#include <SFML/Graphics.hpp>

class Status {

	int m_totalEnemyTanks;

	sf::Texture m_enemyTankSymbolTexture;
	sf::Sprite* m_enemyTankSymbols;

public:
	
	Status();
	~Status();

	void Initialize(int totalEnemyTanks);
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);

private:

	void InitializeEnemyTankSymbol();
	void LoadEnemyTankSymbol();
	void UpdateEnemyTankSymbol();
	void DrawEnemyTankSymbol(sf::RenderWindow& window);
};