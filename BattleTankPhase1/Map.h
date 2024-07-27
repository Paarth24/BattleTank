#pragma once

#include "Grid.h"
#include "Block.h"

class Map {

private:

	sf::Vector2i m_gridRowColumn;

	const sf::Vector2f* m_mapBackgroundSize;
	const sf::Vector2f* m_mapBackgroundPosition;

	sf::Vector2f m_blockOffset;
	
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

	void BoundaryCollision();
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
};