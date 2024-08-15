#pragma once
#include <SFML/Graphics.hpp>

class Score {

private:

	const sf::Vector2u* m_windowResolution;

	sf::Texture m_enemyTankTexture;

	sf::Sprite m_basicTankSprite;
	sf::Text m_basicTankScore;;
	int m_basicTankKilled;

	sf::Sprite m_lightBattleTankSprite;
	sf::Text m_lightBattleTankScore;;
	int m_lightBattleKilled;

	sf::Sprite m_doubleBarrelTankSprite;
	sf::Text m_doubleBarrelTankScore;;
	int m_doubleBarrelTankKilled;

	sf::Sprite m_destroyerTankSprite;
	sf::Text m_destroyerTankScore;;
	int m_destroyerTankKilled;

	sf::Sprite m_fighterTankSprite;
	sf::Text m_fighterTankScore;;
	int m_fighterTankKilled;

	sf::Text m_totalScore;

public:

	Score();
	~Score();

	void Initialize(const sf::Vector2u* windowResolution);
	void Load(const sf::Font* gamefont);

	void Update(
		int basicTankKilled,
		int lightBattleTankKilled, 
		int doubleBarrelTankKilled, 
		int destroyerTankKilled, 
		int fighterTankKilled);

	void Draw(sf::RenderWindow& window);
};

