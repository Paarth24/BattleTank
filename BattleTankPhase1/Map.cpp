#include <fstream>
#include <iostream>

#include "Map.h"

Map::Map(int& totalBrickBlocks):
	m_gridRowColumn(sf::Vector2i(26, 13)),
	m_grid(m_gridRowColumn),
	m_mapBackgroundSize(nullptr),
	m_mapBackgroundPosition(nullptr),
	m_totalBrickBlocks(totalBrickBlocks),
	m_brickBlocks(nullptr)
{
}

void Map::DecypheringMapBlockData(std::string fileData, std::string& mapData)
{
	for (int i = 0; i < fileData.size(); ++i) {

		if (fileData[i] != ';' && fileData[i] != ',') {

			mapData = mapData + fileData[i];
		}
	}
}

sf::Vector2i Map::StringtoVector2i(std::string& mapData)
{
	sf::Vector2i gridIndex = sf::Vector2i(
		(int(mapData[0]) - int('0')) * 10 + int(mapData[1]) - int('0'),
		(int(mapData[2]) - int('0')) * 10 + int(mapData[3]) - int('0'));

	mapData = "";

	return gridIndex;
}

void Map::BoundaryCollision()
{
}

void Map::SpriteCollision()
{
}

void Map::SettingTypeOfPowerUps()
{
}

void Map::SettingGridIdForPowerUps()
{
}

void Map::InitializePowerUps()
{
}

void Map::LoadPowerUps()
{
}

void Map::UpdatePowerUps()
{
}

void Map::DrawPowerUps()
{
}

void Map::InitializeGrassBlocks()
{
	SettingGridIdForGrassBlocks();
}

void Map::InitializeBrickBlocks()
{
	std::ifstream file;
	file.open("assets/world/level1MapBrickBlocks.rmap");

	if (file.is_open()) {

		std::string fileData;
		std::string mapData;

		sf::Vector2i gridIndex;

		for (int i = 0; i < m_totalBrickBlocks; ++i) {

			file >> fileData;

			DecypheringMapBlockData(fileData, mapData);

			gridIndex = StringtoVector2i(mapData);

			m_brickBlocks[i].Initialize(gridIndex, &m_blockOffset, m_mapBackgroundPosition);
		}

		file.close();
	}
}

void Map::InitializeSteelBlocks()
{
	SettingGridIdForSteelBlocks();
}

void Map::InitializeWaterBlocks()
{
	SettingGridIdForWaterBlocks();
}

void Map::InitializeIceBlocks()
{
	SettingGridIdForIceBlocks();
}

void Map::LoadGrassBlocks()
{
}

void Map::LoadBrickBlocks()
{
	std::string fileName = "assets/world/map blocks/brick.png";

	for (int i = 0; i < m_totalBrickBlocks; ++i) {

		m_brickBlocks[i].Load(fileName, &m_blockOffset);
	}
}

void Map::LoadSteelBlocks()
{
}

void Map::LoadWaterBlocks()
{
}

void Map::LoadIceBlocks()
{
}

void Map::UpdateGrassBlocks()
{
}

void Map::UpdateBrickBlocks()
{
}

void Map::UpdateSteelBlocks()
{
}

void Map::UpdateWaterBlocks()
{
}

void Map::UpdateIceBlocks()
{
}

void Map::DrawGrassBlocks(sf::RenderWindow& window)
{
}

void Map::DrawBrickBlocks(sf::RenderWindow& window)
{
	for (int i = 0; i < m_totalBrickBlocks; ++i) {

		m_brickBlocks[i].Draw(window);
	}
}

void Map::DrawSteelBlocks(sf::RenderWindow& window)
{
}

void Map::DrawWaterBlocks(sf::RenderWindow& window)
{
}

void Map::DrawIceBlocks(sf::RenderWindow& window)
{
}

void Map::Initialize(const sf::Vector2f* mapBackgroundSize, const sf::Vector2f* mapBackgroundPosition)
{
	m_mapBackgroundSize = mapBackgroundSize;
	m_mapBackgroundPosition = mapBackgroundPosition;

	m_blockOffset = sf::Vector2f(
		mapBackgroundSize->x / m_gridRowColumn.x,
		mapBackgroundSize->y / m_gridRowColumn.y);

	m_grid.Initialize(m_blockOffset, *m_mapBackgroundSize, *m_mapBackgroundPosition);

	m_brickBlocks = new BrickBlock[m_totalBrickBlocks];

	InitializeGrassBlocks();
	InitializeBrickBlocks();
	InitializeSteelBlocks();
	InitializeWaterBlocks();
	InitializeIceBlocks();
}

void Map::Load()
{
	LoadBrickBlocks();
}

void Map::Update()
{
}

void Map::Draw(sf::RenderWindow& window)
{
	m_grid.Draw(window);

	DrawGrassBlocks(window);
	DrawBrickBlocks(window);
	DrawSteelBlocks(window);
	DrawWaterBlocks(window);
	DrawIceBlocks(window);
}

Map::~Map()
{
	delete[] m_brickBlocks;
}