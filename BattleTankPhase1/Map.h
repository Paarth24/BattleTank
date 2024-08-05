#pragma once

#include "Grid.h"
#include "Player.h"
#include "Block.h"
#include "Base.h"

class Map {

private:

	std::string m_levelId;

	bool m_player1Mode;
	bool m_player2Mode;

	sf::Vector2i m_gridRowColumn;

	const sf::Vector2f* m_mapBackgroundSize;
	const sf::Vector2f* m_mapBackgroundPosition;

	sf::Vector2f m_blockOffset;
	
	Player m_player1;
	Player m_player2;

	Base m_base;

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

public:

	Map(std::string& levelId,
		int totalGrassBlocks,
		int totalBrickBlocks,
		int totalSteelBlocks,
		int totalWaterBlocks,
		int totalIceBlocks);

	~Map();

	void Initialize(const sf::Vector2f* mapBackgroundSize, const sf::Vector2f* mapBackgroundPosition);
	void Load();
	void Update(float deltaTimerMilli);
	void Draw(sf::RenderWindow& window);

private:

	void DecypheringMapBlockData(std::string fileData, std::string& mapData);
	sf::Vector2i StringtoVector2i(std::string& mapData);

	bool BoundaryCollision(const sf::Sprite& sprite, const std::string& direction);

	template <typename T>
	bool ObjectCollision(const T& object1, const sf::Sprite& sprite);

	void SettingTypeOfPowerUps();
	void SettingGridIdForPowerUps();

	void InitializePowerUps();
	void LoadPowerUps();
	void UpdatePowerUps();
	void DrawPowerUps();

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

	inline const sf::Vector2f* GetBlockOffset() const { return &m_blockOffset; }

	inline const void SetPlayer1(Player& player1) { m_player1 = player1; }
	inline const void SetPlayer2(Player& player2) { m_player2 = player2; }
	inline const void SetBase(Base& base) { m_base = base; }
};