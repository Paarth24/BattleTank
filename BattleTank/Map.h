#pragma once
#include "SFML/Graphics.hpp"

#include "Grid.h"

#include "GrassBlock.h"
#include "BrickBlock.h"
#include "SteelBlock.h"
#include "WaterBlock.h"
#include "IceBlock.h"

class Map {

private:

	sf::RectangleShape m_background1;

	sf::RectangleShape m_background2;
	const sf::Vector2f& m_background2Size;
	
	sf::Vector2f m_mapOrigin;

	GrassBlock* m_grassBlocks;
	int m_totalGrassBlocks;

	BrickBlock* m_brickBlocks;
	int m_totalBrickBlocks;
	
	SteelBlock* m_steelBlocks;
	int m_totalSteelBlocks;
	
	WaterBlock* m_waterBlocks;
	int m_totalWaterBlocks;
	
	IceBlock* m_iceBlocks;
	int m_totalIceBlocks;

	Grid m_grid;
	
	sf::Vector2f m_blockOffset;

public:

	Map(
		const sf::Vector2f& background2Size,
		const int& totalGrassBlocks,
		const int& totalBrickBlocks,
		const int& totalSteelBlocks,
		const int& totalWaterBlocks);

	~Map();

	void Initialize(sf::RenderWindow& window);

	void Load(
		const sf::Texture* grassTexture,
		const sf::Texture* brickTexture,
		const sf::Texture* steelTexture,
		const sf::Texture* waterTexture);

	void Update();
	void Draw(sf::RenderWindow& window);

	sf::Vector2i StringtoVector2i(std::string string);
	void DecypheringMapData(std::string& mapData);

	void SettingIdForGrassBlocks();
	void SettingIdForBrickBlocks();
	void SettingIdForSteelBlocks();
	void SettingIdForWaterBlocks();

	void InitializeGrassBlocks();
	void InitializeBrickBlocks();
	void InitializeSteelBlocks();
	void InitializeWaterBlocks();

	void LoadGrassBlocks(const sf::Texture* grassTexture);
	void LoadBrickBlocks(const sf::Texture* brickTexture);
	void LoadSteelBlocks(const sf::Texture* steelTexture);
	void LoadWaterBlocks(const sf::Texture* waterTexture);

	void UpdateGrassBlocks();
	void UpdateBrickBlocks();
	void UpdateSteelBlocks();
	void UpdateWaterBlocks();

	void DrawGrassBlocks(sf::RenderWindow& window);
	void DrawBrickBlocks(sf::RenderWindow& window);
	void DrawSteelBlocks(sf::RenderWindow& window);
	void DrawWaterBlocks(sf::RenderWindow& window);
};

