#pragma once

#include "Grid.h"
#include "Player.h"
#include "Enemy.h"
#include "Block.h"
#include "Base.h"

class Map {

private:

	std::string m_levelId;

	bool m_gameOver;
	sf::Text m_gameOverText;

	bool m_gameClear;
	sf::Text m_gameClearText;

	bool m_player1Mode;
	bool m_player2Mode;

	const sf::Vector2f* m_mapBackgroundSize;
	const sf::Vector2f* m_mapBackgroundPosition;

	const sf::Vector2f* m_blockOffset;
	
	Player m_player1;
	Player m_player2;

	Base m_base;

	int m_totalBasicTanks;
	BasicTank* m_basicTanks;

	int m_totalLightBattleTanks;
	LightBattleTank* m_lightBattleTanks;

	int m_totalDoubleBarrelTanks;
	DoubleBarrelTank* m_doubleBarrelTanks;
	
	int m_totalDestroyerTanks;
	DestroyerTank* m_destroyerTanks;
	
	int m_totalFighterTanks;
	FighterTank* m_fighterTanks;

	int m_totalGrassBlocks;
	GrassBlock* m_grassBlocks;

	int m_totalBrickBlocks;
	BrickBlock* m_brickBlocks;

	int m_totalSteelBlocks;
	SteelBlock* m_steelBlocks;

	int m_totalWaterBlocks;
	WaterBlock* m_waterBlocks;

	int m_totalIceBlocks;
	IceBlock* m_iceBlocks;

	Grid m_grid;

	std::vector <Bullet> m_playerNormalBulletVector;
	std::vector <Bullet> m_playerArmourBulletVector;
	std::vector <Bullet> m_enemyNormalBulletVector;
	std::vector <Bullet> m_enemyArmourBulletVector;

	int m_remainingEnemyTanks;

public:

	Map(std::string& levelId,
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

	~Map();

	void Initialize(
		const sf::Vector2f* mapBackgroundSize,
		const sf::Vector2f* mapBackgroundPosition,
		const sf::Vector2f* blockOffset);
	
	void Load(
		const sf::Font* gameFont,
		const sf::Vector2f* mapBackgroundPosition,
		const sf::Vector2f* mapBackgroundSize);
	
	void Update(float deltaTimerMilli);
	void Draw(sf::RenderWindow& window);

private:

	void DecypheringMapBlockData(std::string fileData, std::string& mapData);
	sf::Vector2i StringtoVector2i(std::string& mapData);

	template <typename T>
	bool BoundaryCollision(const T& object1);

	template <typename T>
	bool ObjectCollision(const T& object1, const sf::Sprite& sprite);

	void SettingTypeOfPowerUps();
	void SettingGridIdForPowerUps();

	void InitializePowerUps();
	void LoadPowerUps();
	void UpdatePowerUps();
	void DrawPowerUps();

	void InitializeBasicTanks();
	void InitializeLightBattleTanks();
	void InitializeDoubleBarrelTanks();
	void InitializeDestroyerTanks();
	void InitializeFighterTanks();

	void LoadBasicTanks();
	void LoadLightBattleTanks();
	void LoadDoubleBarrelTanks();
	void LoadDestroyerTanks();
	void LoadFighterTanks();

	void UpdateBasicTanks();
	void UpdateLightBattleTanks();
	void UpdateDoubleBarrelTanks();
	void UpdateDestroyerTanks();
	void UpdateFighterTanks();

	void DrawBasicTanks(sf::RenderWindow& window);
	void DrawLightBattleTanks(sf::RenderWindow& window);
	void DrawDoubleBarrelTanks(sf::RenderWindow& window);
	void DrawDestroyerTanks(sf::RenderWindow& window);
	void DrawFighterTanks(sf::RenderWindow& window);

	void InitializeGrassBlocks();
	void InitializeBrickBlocks();
	void InitializeSteelBlocks();
	void InitializeWaterBlocks();
	void InitializeIceBlocks();

	void LoadGrassBlocks();
	void LoadBrickBlocks();
	void LoadSteelBlocks();
	void LoadWaterBlocks();
	void LoadIceBlocks();

	void DrawGrassBlocks(sf::RenderWindow& window);
	void DrawBrickBlocks(sf::RenderWindow& window);
	void DrawSteelBlocks(sf::RenderWindow& window);
	void DrawWaterBlocks(sf::RenderWindow& window);
	void DrawIceBlocks(sf::RenderWindow& window);

	void Player1ModeUpdate();
	void Player2ModeUpdate();

	void PlayerBulletUpdate();
	void EnemyBulletUpdate();

public:

	void SetPLayerMode(bool& player1Mode, bool& player2Mode);
	void Restart();

	inline const Player& GetPlayer1() const { return m_player1; }
	inline const Player& GetPlayer2() const { return m_player2; }

	inline const int GetTotalEnemyTank() const {
		return
			m_totalBasicTanks +
			m_totalLightBattleTanks +
			m_totalDoubleBarrelTanks +
			m_totalDestroyerTanks +
			m_totalFighterTanks;
	}
	inline const int GetRemainingEnemyTanks() const { return m_remainingEnemyTanks; }
	
	inline const void SetPlayer1(Player& player1) { m_player1 = player1; }
	inline const void SetPlayer2(Player& player2) { m_player2 = player2; }
	inline const void SetBase(Base& base) { m_base = base; }

};