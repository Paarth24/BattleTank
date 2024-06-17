#include "Map.h"
#include "Math.h"

#include <fstream>

Map::Map(
	const sf::Vector2f& background2Size,
	const int& totalGrassBlocks,
	const int& totalBrickBlocks,
	const int& totalSteelBlocks,
	const int& totalWaterBlocks):
	m_background2Size(background2Size),
	m_grid(sf::Vector2f(25, 25)),
	m_blockOffset(sf::Vector2f(0, 0)),
	m_mapOrigin(sf::Vector2f(0, 0)),
	m_grassBlocks(nullptr),
	m_brickBlocks(nullptr),
	m_steelBlocks(nullptr),
	m_waterBlocks(nullptr),
	m_iceBlocks(nullptr),
	m_totalGrassBlocks(totalGrassBlocks),
	m_totalBrickBlocks(totalBrickBlocks),
	m_totalSteelBlocks(totalSteelBlocks),
	m_totalWaterBlocks(totalWaterBlocks),
	m_totalIceBlocks(0)
{
}

sf::Vector2i Map::StringtoVector2i(std::string string)
{
	int size = string.size();
	std::string gridIndex;
	std::string val;

	std::cout << string.size() << " ";

	for (int i = 0; i < size; ++i) {

		if (string[i] == ';') {

			gridIndex = gridIndex + val;
			break;
		}
		else if (string[i] != ',') {

			val = val + string[i];
		}
		else {

			gridIndex = gridIndex + val;
			val = "";
		}
	}
	int gridIndexX = 0;
	int gridIndexY = 0;

	gridIndexX = (int(gridIndex[0] - int('0')) * 10) + int(gridIndex[1] - int('0'));
	gridIndexY = (int(gridIndex[2] - int('0')) * 10) + int(gridIndex[3] - int('0'));

	return sf::Vector2i(gridIndexX, gridIndexY);
}


void Map::SettingIdForGrassBlocks()
{
	std::ifstream level1Map;
	level1Map.open("assets/world/level1MapGrassBlocks.rmap");


	if (level1Map.is_open()) {

		std::string mapData;

		while (level1Map) {

			char fileChar;
			fileChar = level1Map.get();	

			if (fileChar != ' ') {

				mapData = mapData + fileChar;
			}
			else {

				m_grassMapDataGridIndex.push_back(StringtoVector2i(mapData));

				mapData = "";
			}
		}
	}

	level1Map.close();

	for (int i = 0; i < m_totalGrassBlocks; ++i) {

		m_grassBlocks[i].m_gridIndex = m_grassMapDataGridIndex[i];
	}
}

void Map::SettingIdForBrickBlocks()
{
	for (int i = 0; i < m_totalBrickBlocks; ++i) {

		m_brickBlocks[i].m_gridIndex = sf::Vector2i(1, i);
	}
}

void Map::SettingIdForSteelBlocks()
{
	for (int i = 0; i < m_totalSteelBlocks; ++i) {

		m_steelBlocks[i].m_gridIndex = sf::Vector2i(2, i);
	}
}

void Map::SettingIdForWaterBlocks()
{
	for (int i = 0; i < m_totalWaterBlocks; ++i) {

		m_waterBlocks[i].m_gridIndex = sf::Vector2i(3, i);
	}
}

void Map::InitializeGrassBlocks()
{
	if (m_totalGrassBlocks != m_grassMapDataGridIndex.size()) {

		std::cout << "Number of grid index not equal to allocated memory for grass blocks" << std::endl;
	}
	else {

		for (int i = 0; i < m_totalGrassBlocks; ++i) {

			m_grassBlocks[i].m_id = "grass";
			m_grassBlocks[i].Initialize(&m_mapOrigin, &m_blockOffset);
		}
	}
}

void Map::InitializeBrickBlocks()
{
	for (int i = 0; i < m_totalBrickBlocks; ++i) {

		m_brickBlocks[i].m_id = "brick";
		m_brickBlocks[i].Initialize(&m_mapOrigin, &m_blockOffset);
	}
}

void Map::InitializeSteelBlocks()
{
	for (int i = 0; i < m_totalSteelBlocks; ++i) {

		m_steelBlocks[i].m_id = "steel";
		m_steelBlocks[i].Initialize(&m_mapOrigin, &m_blockOffset);
	}
}

void Map::InitializeWaterBlocks()
{
	for (int i = 0; i < m_totalWaterBlocks; ++i) {

		m_waterBlocks[i].m_id = "water";
		m_waterBlocks[i].Initialize(&m_mapOrigin, &m_blockOffset);
	}
}

void Map::LoadGrassBlocks(const sf::Texture* grassTexture)
{
	for (int i = 0; i < m_totalGrassBlocks; ++i) {

		m_grassBlocks[i].Load(grassTexture);
	}
}

void Map::LoadBrickBlocks(const sf::Texture* brickTexture)
{
	for (int i = 0; i < m_totalBrickBlocks; ++i) {
			
		m_brickBlocks[i].Load(brickTexture);
	}
}

void Map::LoadSteelBlocks(const sf::Texture* steelTexture)
{
	for (int i = 0; i < m_totalSteelBlocks; ++i) {

		m_steelBlocks[i].Load(steelTexture);
	}
}

void Map::LoadWaterBlocks(const sf::Texture* waterTexture)
{
	for (int i = 0; i < m_totalWaterBlocks; ++i) {

		m_waterBlocks[i].Load(waterTexture);
	}
}

void Map::UpdateGrassBlocks()
{
	for (int i = 0; i < m_totalGrassBlocks; ++i) {

		m_grassBlocks[i].Update();
	}
}

void Map::UpdateBrickBlocks()
{
	for (int i = 0; i < m_totalBrickBlocks; ++i) {

		m_brickBlocks[i].Update();
	}
}

void Map::UpdateSteelBlocks()
{
	for (int i = 0; i < m_totalSteelBlocks; ++i) {

		m_steelBlocks[i].Update();
	}
}

void Map::UpdateWaterBlocks()
{
	for (int i = 0; i < m_totalWaterBlocks; ++i) {

		m_waterBlocks[i].Update();
	}
}

void Map::DrawGrassBlocks(sf::RenderWindow& window)
{
	for (int i = 0; i < m_totalGrassBlocks; ++i) {

		m_grassBlocks[i].Draw(window);
	}
}

void Map::DrawBrickBlocks(sf::RenderWindow& window)
{

	for (int i = 0; i < m_totalBrickBlocks; ++i) {

		m_brickBlocks[i].Draw(window);
	}
}

void Map::DrawSteelBlocks(sf::RenderWindow& window)
{
	for (int i = 0; i < m_totalSteelBlocks; ++i) {

		m_steelBlocks[i].Draw(window);
	}
}

void Map::DrawWaterBlocks(sf::RenderWindow& window)
{
	for (int i = 0; i < m_totalWaterBlocks; ++i) {

		m_waterBlocks[i].Draw(window);
	}
}

void Map::Initialize(sf::RenderWindow& window)
{
	m_blockOffset = sf::Vector2f(m_background2Size.x / 25, m_background2Size.y / 25);

	sf::Vector2u windowSize = window.getSize();
	m_mapOrigin = sf::Vector2f((windowSize.x - m_background2Size.x) / 3, (windowSize.y - m_background2Size.y) / 2);

	m_background1.setSize(sf::Vector2f(windowSize.x, windowSize.y));
	m_background1.setFillColor(sf::Color(128, 128, 128));
	m_background1.setPosition(sf::Vector2f(0, 0));

	m_background2.setSize(m_background2Size);
	m_background2.setFillColor(sf::Color::Black);
	m_background2.setPosition(m_mapOrigin);

	m_grassBlocks = new GrassBlock[m_totalGrassBlocks];
	m_brickBlocks = new BrickBlock[m_totalBrickBlocks];
	m_steelBlocks = new SteelBlock[m_totalSteelBlocks];
	m_waterBlocks = new WaterBlock[m_totalWaterBlocks];

	SettingIdForGrassBlocks();
	SettingIdForBrickBlocks();
	SettingIdForSteelBlocks();
	SettingIdForWaterBlocks();

	InitializeGrassBlocks();
	InitializeBrickBlocks();
	InitializeSteelBlocks();
	InitializeWaterBlocks();

	m_grid.Initialize(window, &m_mapOrigin, &m_background2Size);

}

void Map::Load(
	const sf::Texture* grassTexture,
	const sf::Texture* brickTexture,
	const sf::Texture* steelTexture,
	const sf::Texture* waterTexture)
{
	LoadGrassBlocks(grassTexture);
	LoadBrickBlocks(brickTexture);
	LoadSteelBlocks(steelTexture);
	LoadWaterBlocks(waterTexture);

	m_grid.Load();
}

void Map::Update()
{
	UpdateGrassBlocks();
	UpdateBrickBlocks();
	UpdateSteelBlocks();
	UpdateWaterBlocks();

	m_grid.Update();
}

void Map::Draw(sf::RenderWindow& window)
{
	window.draw(m_background1);
	window.draw(m_background2);

	DrawGrassBlocks(window);
	DrawBrickBlocks(window);
	DrawSteelBlocks(window);
	DrawWaterBlocks(window);

	m_grid.Draw(window);
}

Map::~Map()
{
	delete[] m_grassBlocks;
	delete[] m_brickBlocks;
	delete[] m_steelBlocks;
	delete[] m_waterBlocks;
}