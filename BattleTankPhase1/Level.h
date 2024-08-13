#pragma once
#include "Map.h"
#include "Status.h"
#include "Player.h"
#include "Base.h"

class Level {

private:

	std::string m_levelID;

	bool m_player1Mode;
	bool m_player2Mode;

	const sf::Vector2u* m_windowResolution;

	sf::RectangleShape m_mainBackground;

	sf::RectangleShape m_mapBackground;
	const sf::Vector2f* m_mapBackgroundSize;
	const sf::Vector2f* m_mapBackgroundPosition;

	const sf::Vector2f* m_blockOffset;

	Map m_map;

	Status m_status;

	Base m_base;

public:

	Level(
		std::string levelId,
		int totalBasicTanks,
		int totalLightBattleTanks,
		int totalDoubleBarrelTanks,
		int totalDestroyerTanks,
		int totalFighterTanks,
		int totalGrassBlocks,
		int totalBrickBlocks,
		int totalSteelBlocks,
		int totalWaterBlocks,
		int totalIceBlocks);

	Level();
	~Level();

	void Initialize(
		const sf::Vector2u* windowResolution,
		const sf::Vector2f* mapBackgroundSize,
		const sf::Vector2f* mapBackgroundPosition,
		const sf::Vector2f* blockOffset,
		int player1Lives,
		int player2Lives);
	
	void Load(
		const sf::Font* gameFont,
		const sf::Vector2f* mapBackgroundPosition,
		const sf::Vector2f* mapBackgroundSize);
	
	void Update(float deltaTimerMilli);
	void Draw(sf::RenderWindow& window);

	void SetPLayerMode(bool& player1Mode, bool& player2Mode);
	void SetPlayer1(Player* player1);
	void SetPlayer2(Player* player2);
	void SetBase(Base& base);

	void Restart();

	bool Completed();
};

