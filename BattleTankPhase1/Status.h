#pragma once
#include <SFML/Graphics.hpp>

class Status {

	const sf::Vector2u* m_windowResolution;
	const sf::Vector2f* m_mapBackgroundPosition;
	const sf::Vector2f* m_mapBackgroundSize;

	int m_totalEnemyTanks;

	sf::Texture m_enemyTankSymbolTexture;
	sf::Sprite* m_enemyTankSymbols;

	sf::Text m_player1IdText;
	sf::Text m_player1LivesText;

	sf::Texture m_player1LivesTexture;
	sf::Sprite m_player1LivesSprite;
	int m_player1Lives;

	sf::Text m_player2IdText;
	sf::Text m_player2LivesText;

	sf::Texture m_player2LivesTexture;
	sf::Sprite m_player2LivesSprite;
	int m_player2Lives;

	sf::Texture m_levelNumberTexture;
	sf::Sprite m_levelNumberSprite;

	sf::Text m_levelIdText;

public:
	
	Status();
	~Status();

	void Initialize(
		const sf::Vector2u* windowResolution,
		const sf::Vector2f* mapBackgroundPosition,
		const sf::Vector2f* mapBackgroundSize,
		std::string& levelID,
		int player1Lives,
		int player2Lives,
		int totalEnemyTanks);

	void Load(const sf::Font* gameFont, const sf::Vector2f* blockOffset);
	void Update(int remainingEnemies, int remainingPlayer1Lives, int remainingPlayer2Lives);
	void Draw(sf::RenderWindow& window, bool player2Mode);

private:

	void InitializeEnemyTankSymbol();
	void LoadEnemyTankSymbol(const sf::Vector2f* blockOffset);
	void DrawEnemyTankSymbol(sf::RenderWindow& window);
};