#pragma once
#include "Map.h"
#include "Player.h"
#include "Base.h"

class Level {

private:

	bool m_player1Mode;
	bool m_player2Mode;

	const sf::Vector2u* m_windowResolution;

	sf::RectangleShape m_mainBackground;

	sf::RectangleShape m_mapBackground;
	const sf::Vector2f* m_mapBackgroundSize;
	const sf::Vector2f* m_mapBackgroundPosition;

	Map m_map;

	Player m_player1;
	Player m_player2;

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

	~Level();

	void Initialize(const sf::Vector2u* windowResolution, const sf::Vector2f* mapBackgroundSize, const sf::Vector2f* mapBackgroundPosition);
	void Load();
	void Update(float deltaTimerMilli);
	void Draw(sf::RenderWindow& window);

private:

	void Lost();
	void Completed();

	void Exit();

public:

	void SetPLayerMode(bool& player1Mode, bool& player2Mode);
	void SetPlayer1(Player& player1);
	void SetPlayer2(Player& player2);
	void SetBase(Base& base);

	inline const sf::Vector2f* GetBlockOffset() const { return m_map.GetBlockOffset(); }
};

