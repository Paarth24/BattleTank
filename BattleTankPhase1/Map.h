#pragma once

#include "Grid.h"
#include "Player.h"
#include "Block.h"

class Map {

private:

	bool m_player1Mode;
	bool m_player2Mode;

	sf::Vector2i m_gridRowColumn;

	const sf::Vector2f* m_mapBackgroundSize;
	const sf::Vector2f* m_mapBackgroundPosition;

	sf::Vector2f m_blockOffset;
	
	Player m_player1;
	Player m_player2;

	int m_totalBrickBlocks;
	BrickBlock* m_brickBlocks;

	Grid m_grid;

public:

	Map(int& totalBrickBlocks);
	~Map();

	void Initialize(const sf::Vector2f* mapBackgroundSize, const sf::Vector2f* mapBackgroundPosition);
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);

private:

	void DecypheringMapBlockData(std::string fileData, std::string& mapData);
	sf::Vector2i StringtoVector2i(std::string& mapData);

	void BoundaryCollision(const sf::Sprite& sprite);
	void SpriteCollision();

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

	void UpdateGrassBlocks();
	void UpdateBrickBlocks();
	void UpdateSteelBlocks();
	void UpdateWaterBlocks();
	void UpdateIceBlocks();

	void DrawGrassBlocks(sf::RenderWindow& window);
	void DrawBrickBlocks(sf::RenderWindow& window);
	void DrawSteelBlocks(sf::RenderWindow& window);
	void DrawWaterBlocks(sf::RenderWindow& window);
	void DrawIceBlocks(sf::RenderWindow& window);

public:

	void SetPLayerMode(bool& player1Mode, bool& player2Mode);

	inline const sf::Vector2f* GetBlockOffset() const { return &m_blockOffset; }
	inline const void SetPlayer1(Player& player1) { m_player1 = player1; }
	inline const void SetPlayer2(Player& player2) { m_player2 = player2; }
};