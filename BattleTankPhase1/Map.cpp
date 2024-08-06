#include <fstream>
#include <iostream>

#include "Map.h"

Map::Map(std::string& levelId,
	int totalBasicTanks,
	int totalLightBattleTanks,
	int totalDoubleBarrelTanks,
	int totalDestroyerTanks,
	int totalFighterTanks,
	int totalGrassBlocks,
	int totalBrickBlocks,
	int totalSteelBlocks,
	int totalWaterBlocks,
	int totalIceBlocks):
	m_levelId(levelId),
	m_gridRowColumn(sf::Vector2i(26, 13)),
	m_grid(m_gridRowColumn),
	m_mapBackgroundSize(nullptr),
	m_mapBackgroundPosition(nullptr),
	m_player1Mode(false),
	m_player2Mode(false),
	m_totalGrassBlocks(totalGrassBlocks),
	m_grassBlocks(nullptr),
	m_totalBrickBlocks(totalBrickBlocks),
	m_brickBlocks(nullptr),
	m_totalSteelBlocks(totalSteelBlocks),
	m_steelBlocks(nullptr),
	m_totalWaterBlocks(totalWaterBlocks),
	m_waterBlocks(nullptr),
	m_totalIceBlocks(totalIceBlocks),
	m_iceBlocks(nullptr)
{
}

void Map::SetPLayerMode(bool& player1Mode, bool& player2Mode)
{
	m_player1Mode = player1Mode;
	m_player2Mode = player2Mode;
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

template<typename T>
bool Map::BoundaryCollision(const T& object1)
{
	sf::Sprite sprite = object1.GetSprite();
	std::string direction = object1.GetDirection();

	if (direction == "up") {

		if (sprite.getPosition().y >= m_mapBackgroundPosition->y) {

			return false;
		}
		else {

			return true;
		}
	}
	else if (direction == "left") {

		if (sprite.getPosition().x >= m_mapBackgroundPosition->x) {

			return false;
		}
		else {

			return true;
		}
	}
	else if (direction == "down") {

		if (sprite.getPosition().y <= m_mapBackgroundPosition->y + m_mapBackgroundSize->y - sprite.getGlobalBounds().height) {

			return false;
		}
		else {

			return true;
		}
	}
	else if (direction == "right") {

		if (sprite.getPosition().x <= m_mapBackgroundPosition->x + m_mapBackgroundSize->x - sprite.getGlobalBounds().width) {

			return false;
		}
		else {

			return true;
		}
	}
}

template<typename T>
inline bool Map::ObjectCollision(const T& object1, const sf::Sprite& sprite)
{
	std::string direction = object1.GetDirection();

	sf::FloatRect sprite1Global = object1.GetSprite().getGlobalBounds();
	sf::FloatRect sprite2Global = sprite.getGlobalBounds();

	sf::Vector2f sprite1Position = object1.GetSprite().getPosition();
	sf::Vector2f sprite2Position = sprite.getPosition();

	if (direction == "up") {

		if (sprite1Global.left < sprite2Global.left + sprite2Global.width && sprite1Global.left + sprite1Global.width > sprite2Global.left &&
			sprite1Position.y <= sprite2Position.y + sprite2Global.height && sprite1Position.y >= sprite2Position.y) {

			return true;
		}
		else {

			return false;
		}
	}
	else if (direction == "left") {

		if (sprite1Position.x <= sprite2Position.x + sprite2Global.width && sprite1Position.x >= sprite2Position.x &&
			sprite1Global.top < sprite2Global.top + sprite2Global.height && sprite1Global.top + sprite1Global.height > sprite2Global.top) {

			return true;
		}
		else {

			return false;
		}
	}
	else if (direction == "down") {

		if (sprite1Global.left < sprite2Global.left + sprite2Global.width && sprite1Global.left + sprite1Global.width > sprite2Global.left &&
			sprite1Position.y + sprite1Global.height >= sprite2Position.y && sprite1Position.y <= sprite2Position.y) {

			return true;
		}
		else {

			return false;
		}
	}
	else if (direction == "right") {

		if (sprite1Position.x + sprite1Global.width >= sprite2Position.x && sprite1Position.x <= sprite2Position.x &&
			sprite1Global.top < sprite2Global.top + sprite2Global.height && sprite1Global.top + sprite1Global.height > sprite2Global.top) {

			return true;
		}
		else {

			return false;
		}
	}
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

void Map::InitializeBasicTanks()
{
	for (int i = 0;i < m_totalBasicTanks; ++i) {

		m_basicTank[i].Initialize("Basic", &m_blockOffset, m_mapBackgroundPosition);
	}
}

void Map::InitializeLightBattleTanks()
{
	for (int i = 0;i < m_totalLightBattleTanks; ++i) {

		m_lightBattleTank[i].Initialize("LightBattle", &m_blockOffset, m_mapBackgroundPosition);
	}
}

void Map::InitializeDoubleBarrelTanks()
{
	for (int i = 0;i < m_totalDoubleBarrelTanks; ++i) {

		m_doubleBarrelTank[i].Initialize("DoubleBarrel", &m_blockOffset, m_mapBackgroundPosition);
	}
}

void Map::InitializeDestroyerTanks()
{
	for (int i = 0;i < m_totalDestroyerTanks; ++i) {

		m_destroyerTank[i].Initialize("Destroyer", &m_blockOffset, m_mapBackgroundPosition);
	}
}

void Map::InitializeFighterTanks()
{
	for (int i = 0;i < m_totalFighterTanks; ++i) {

		m_fighterTank[i].Initialize("Fighter", &m_blockOffset, m_mapBackgroundPosition);
	}
}

void Map::InitializeGrassBlocks()
{
	std::ifstream file;
	file.open("assets/world/" + m_levelId + "/MapGrassBlocks.rmap");

	if (file.is_open()) {

		std::string fileData;
		std::string mapData;

		sf::Vector2i gridIndex;

		for (int i = 0; i < m_totalGrassBlocks; ++i) {

			file >> fileData;

			DecypheringMapBlockData(fileData, mapData);

			gridIndex = StringtoVector2i(mapData);

			m_grassBlocks[i].Initialize(gridIndex, &m_blockOffset, m_mapBackgroundPosition);
		}

		file.close();
	}
}

void Map::InitializeBrickBlocks()
{
	std::ifstream file;
	file.open("assets/world/" + m_levelId + "/MapBrickBlocks.rmap");

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
	std::ifstream file;
	file.open("assets/world/" + m_levelId + "/MapSteelBlocks.rmap");

	if (file.is_open()) {

		std::string fileData;
		std::string mapData;

		sf::Vector2i gridIndex;

		for (int i = 0; i < m_totalSteelBlocks; ++i) {

			file >> fileData;

			DecypheringMapBlockData(fileData, mapData);

			gridIndex = StringtoVector2i(mapData);

			m_steelBlocks[i].Initialize(gridIndex, &m_blockOffset, m_mapBackgroundPosition);
		}

		file.close();
	}
}

void Map::InitializeWaterBlocks()
{
	std::ifstream file;
	file.open("assets/world/" + m_levelId + "/MapWaterBlocks.rmap");

	if (file.is_open()) {

		std::string fileData;
		std::string mapData;

		sf::Vector2i gridIndex;

		for (int i = 0; i < m_totalWaterBlocks; ++i) {

			file >> fileData;

			DecypheringMapBlockData(fileData, mapData);

			gridIndex = StringtoVector2i(mapData);

			m_waterBlocks[i].Initialize(gridIndex, &m_blockOffset, m_mapBackgroundPosition);
		}

		file.close();
	}
}

void Map::InitializeIceBlocks()
{
	std::ifstream file;
	file.open("assets/world/" + m_levelId + "/MapIceBlocks.rmap");

	if (file.is_open()) {

		std::string fileData;
		std::string mapData;

		sf::Vector2i gridIndex;

		for (int i = 0; i < m_totalIceBlocks; ++i) {

			file >> fileData;

			DecypheringMapBlockData(fileData, mapData);

			gridIndex = StringtoVector2i(mapData);

			m_iceBlocks[i].Initialize(gridIndex, &m_blockOffset, m_mapBackgroundPosition);
		}

		file.close();
	}
}

void Map::LoadGrassBlocks()
{
	std::string fileName = "assets/world/mapBlocks/grass.png";

	for (int i = 0; i < m_totalGrassBlocks; ++i) {

		m_grassBlocks[i].Load(fileName, &m_blockOffset);
	}
}

void Map::LoadBrickBlocks()
{
	std::string fileName = "assets/world/mapBlocks/brick.png";

	for (int i = 0; i < m_totalBrickBlocks; ++i) {

		m_brickBlocks[i].Load(fileName, &m_blockOffset);
	}
}

void Map::LoadSteelBlocks()
{
	std::string fileName = "assets/world/mapBlocks/steel.png";

	for (int i = 0; i < m_totalSteelBlocks; ++i) {

		m_steelBlocks[i].Load(fileName, &m_blockOffset);
	}
}

void Map::LoadWaterBlocks()
{
	std::string fileName = "assets/world/mapBlocks/water.png";

	for (int i = 0; i < m_totalWaterBlocks; ++i) {

		m_waterBlocks[i].Load(fileName, &m_blockOffset);
	}
}

void Map::LoadIceBlocks()
{
	std::string fileName = "assets/world/mapBlocks/ice.png";

	for (int i = 0; i < m_totalIceBlocks; ++i) {

		m_iceBlocks[i].Load(fileName, &m_blockOffset);
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

void Map::DrawIceBlocks(sf::RenderWindow& window)
{
	for (int i = 0; i < m_totalIceBlocks; ++i) {

		m_iceBlocks[i].Draw(window);
	}
}

void Map::Player1ModeUpdate()
{
	bool collision = false;

	if (m_player1Mode == false && m_player2Mode == true) {

	//-----------------------------Checking if Player1 Collided With Player2-----------------------------
		if (ObjectCollision(m_player1, m_player2.GetSprite())) {

			collision = true;

		}
	//-----------------------------Checking if Player1 Collided With Player2-----------------------------
	}

	//-----------------------------Checking if Player1 Collided With Map Boundary-----------------------------
	if (!collision) {

		if (BoundaryCollision(m_player1)) {

			collision = true;
		}
	}
	//-----------------------------Checking if Player1 Collided With Map Boundary-----------------------------
	
	//-----------------------------Checking if Player1 Collided With Brick Block-----------------------------
	if (!collision) {

		for (int i = 0; i < m_totalBrickBlocks; ++i) {
				
			if (!m_brickBlocks[i].GetCheckDestroy()) {

				if (ObjectCollision(m_player1, m_brickBlocks[i].GetSprite())) {

					collision = true;
					break;
				}
				else {

					collision = false;
				}
			}
		}
	}
	//-----------------------------Checking if Player1 Collided With Brick Block-----------------------------

	//-----------------------------Checking if Player1 Collided With Steel Block-----------------------------
	if (!collision) {

		for (int i = 0; i < m_totalSteelBlocks; ++i) {

			if (!m_steelBlocks[i].GetCheckDestroy()) {

				if (ObjectCollision(m_player1, m_steelBlocks[i].GetSprite())) {

					collision = true;
					break;
				}
				else {

					collision = false;
				}
			}
		}
	}
	//-----------------------------Checking if Player1 Collided With Steel Block-----------------------------

	//-----------------------------Checking if Player1 Collided With Base-----------------------------
	if (!collision) {

		if (ObjectCollision(m_player1, m_base.GetSprite())) {

			collision = true;
		}
		else {

			collision = false;
		}
	}
	//-----------------------------Checking if Player1 Collided With Base-----------------------------
	
	if (!collision) {

		m_player1.SetCollision(false);
	}
	else {
	
		m_player1.SetCollision(true);
	}
}

void Map::Player2ModeUpdate()
{
	bool collision = false;

	//-----------------------------Checking if Player2 Collided Player1-----------------------------
	if (ObjectCollision(m_player2, m_player1.GetSprite())) {

		collision = true;
	}
	//-----------------------------Checking if Player2 Collided Player1-----------------------------

	//-----------------------------Checking if Player2 Collided With Map Boundary-----------------------------
	if (!collision) {

		if (BoundaryCollision(m_player2)) {

			collision = true;
		}
	}
	//-----------------------------Checking if Player2 Collided With Map Boundary-----------------------------
	
	//-----------------------------Checking if Player2 Collided With Brick Block-----------------------------
	if (!collision) {

		for (int i = 0; i < m_totalBrickBlocks; ++i) {

			if (!m_brickBlocks[i].GetCheckDestroy()) {

				if (ObjectCollision(m_player2, m_brickBlocks[i].GetSprite())) {

					collision = true;
					break;
				}
				else {

					collision = false;
				}
			}
		}
	}
	//-----------------------------Checking if Player2 Collided With Brick Block-----------------------------

	//-----------------------------Checking if Player2 Collided With Steel Block-----------------------------
	if (!collision) {

		for (int i = 0; i < m_totalSteelBlocks; ++i) {

			if (!m_steelBlocks[i].GetCheckDestroy()) {

				if (ObjectCollision(m_player2, m_steelBlocks[i].GetSprite())) {

					collision = true;
					break;
				}
				else {

					collision = false;
				}
			}
		}
	}
	//-----------------------------Checking if Player2 Collided With Steel Block-----------------------------

	//-----------------------------Checking if Player2 Collided With Water Block-----------------------------
	if (!collision) {

		for (int i = 0; i < m_totalWaterBlocks; ++i) {

			if (ObjectCollision(m_player2, m_waterBlocks[i].GetSprite())) {

				collision = true;
				break;
			}
			else {

				collision = false;
			}
		}
	}
	//-----------------------------Checking if Player2 Collided With Water Block-----------------------------
	
	//-----------------------------Checking if Player2 Collided With Ice Block-----------------------------
	if (!collision) {

		for (int i = 0; i < m_totalIceBlocks; ++i) {

			if (ObjectCollision(m_player2, m_iceBlocks[i].GetSprite())) {

				m_player2.CollissionWithIceBlock();
				break;
			}
			else {

				collision = false;
			}
		}
	}
	//-----------------------------Checking if Player2 Collided With Ice Block-----------------------------
	
	//-----------------------------Checking if Player2 Collided With Base-----------------------------
	if (!collision) {

		if (ObjectCollision(m_player2, m_base.GetSprite())) {

			collision = true;
		}
		else {

			collision = false;
		}
	}
	//-----------------------------Checking if Player2 Collided With Base-----------------------------

	if (!collision) {

		m_player2.SetCollision(false);
	}
	else {

		m_player2.SetCollision(true);
	}
}

void Map::PlayerBulletUpdate()
{
	for (size_t i = 0; i < m_playerNormalBulletVector.size(); ++i) {

		bool collision = false;

		Bullet bullet = m_playerNormalBulletVector[i];

	//-----------------------------Checking if Player Normal Bullet Collided With Map Boundary-----------------------------
		if (BoundaryCollision(bullet)) {

			collision = true;
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Map Boundary-----------------------------
		
	//-----------------------------Checking if Player Normal Bullet Collided With Brick Block-----------------------------
		if (!collision) {

			for (int j = 0; j < m_totalBrickBlocks; ++j) {

				if (!m_brickBlocks[j].GetCheckDestroy()) {

					if (ObjectCollision(bullet, m_brickBlocks[j].GetSprite())) {

						collision = true;
						m_brickBlocks[j].SetCheckDestroy(true);
						break;
					}
					else {

						collision = false;
					}
				}
			}
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Brick Block-----------------------------
	
	//-----------------------------Checking if Player Normal Bullet Collided With Steel Block-----------------------------
		if (!collision) {

			for (int j = 0; j < m_totalSteelBlocks; ++j) {

				if (!m_steelBlocks[j].GetCheckDestroy()) {

					if (ObjectCollision(bullet, m_steelBlocks[j].GetSprite())) {

						collision = true;
						break;
					}
					else {

						collision = false;
					}
				}
			}
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Steel Block-----------------------------

	//-----------------------------Checking if Player Normal Bullet Collided With Base-----------------------------
		if (!collision) {

			if (ObjectCollision(bullet, m_base.GetSprite())) {

				collision = true;
				m_base.Destroy();
			}
			else {

				collision = false;
			}
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Base-----------------------------

		if (collision) {

			m_playerNormalBulletVector.erase(m_playerNormalBulletVector.begin() + i);
		}
	}

	for (size_t i = 0; i < m_playerArmourBulletVector.size(); ++i) {

		bool collision = false;

		Bullet bullet = m_playerArmourBulletVector[i];

	//-----------------------------Checking if Player Armour Bullet Collided With Map Boundary-----------------------------
		if (BoundaryCollision(bullet)) {

			collision = true;
			m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);
		}
	//-----------------------------Checking if Player Armour Bullet Collided With Map Boundary-----------------------------

	//-----------------------------Checking if Player Armour Bullet Collided With Brick Block-----------------------------
		if (!collision) {

			for (int j = 0; j < m_totalBrickBlocks; ++j) {

				if (!m_brickBlocks[j].GetCheckDestroy()) {

					if (ObjectCollision(bullet, m_brickBlocks[j].GetSprite())) {

						collision = true;
						m_brickBlocks[j].SetCheckDestroy(true);
						break;
					}
					else {

						collision = false;
					}
				}
			}
		}
	//-----------------------------Checking if Player Armour Bullet Collided With Brick Block-----------------------------
		
	//-----------------------------Checking if Player Armour Bullet Collided With Steel Block-----------------------------
		if (!collision) {

			for (int j = 0; j < m_totalSteelBlocks; ++j) {

				if (!m_steelBlocks[j].GetCheckDestroy()) {

					if (ObjectCollision(bullet, m_steelBlocks[j].GetSprite())) {

						collision = true;
						m_steelBlocks[j].SetCheckDestroy(true);
						break;
					}
					else {

						collision = false;
					}
				}
			}
		}
	//-----------------------------Checking if Player Armour Bullet Collided With Steel Block-----------------------------

	//-----------------------------Checking if Player Armor Bullet Collided With Base-----------------------------
	if (!collision) {

		if (ObjectCollision(bullet, m_base.GetSprite())) {

			collision = true;
			m_base.Destroy();
		}
		else {

			collision = false;
		}
	}
	//-----------------------------Checking if Player Armor Bullet Collided With Base-----------------------------
		if (collision) {

			m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);
		}
	}
}

void Map::EnemyBulletUpdate() 
{
	for (size_t i = 0; i < m_enemyNormalBulletVector.size(); ++i) {

		Bullet bullet = m_enemyNormalBulletVector[i];

		if (BoundaryCollision(bullet)) {

			m_enemyNormalBulletVector.erase(m_enemyNormalBulletVector.begin() + i);
		}
	}

	for (size_t i = 0; i < m_enemyArmourBulletVector.size(); ++i) {

		Bullet bullet = m_enemyArmourBulletVector[i];

		if (BoundaryCollision(bullet)) {

			m_enemyArmourBulletVector.erase(m_enemyArmourBulletVector.begin() + i);
		}
	}
}


void Map::Initialize(const sf::Vector2f* mapBackgroundSize, const sf::Vector2f* mapBackgroundPosition)
{
	m_mapBackgroundSize = mapBackgroundSize;
	m_mapBackgroundPosition = mapBackgroundPosition;

	m_blockOffset = sf::Vector2f(
		mapBackgroundSize->x / m_gridRowColumn.x,
		mapBackgroundSize->y / m_gridRowColumn.y);

	m_grid.Initialize(m_blockOffset, *m_mapBackgroundSize, *m_mapBackgroundPosition);

	m_basicTank = new BasicTank[m_totalBasicTanks];
	m_lightBattleTank = new LightBattleTank[m_totalLightBattleTanks];
	m_doubleBarrelTank = new DoubleBarrelTank[m_totalDoubleBarrelTanks];
	m_destroyerTank = new DestroyerTank[m_totalDestroyerTanks];
	m_fighterTank = new FighterTank[m_totalFighterTanks];

	m_grassBlocks = new GrassBlock[m_totalGrassBlocks];
	m_brickBlocks = new BrickBlock[m_totalBrickBlocks];
	m_steelBlocks = new SteelBlock[m_totalSteelBlocks];
	m_waterBlocks = new WaterBlock[m_totalWaterBlocks];
	m_iceBlocks = new IceBlock[m_totalIceBlocks];

	InitializeBasicTanks();
	InitializeLightBattleTanks();
	InitializeDoubleBarrelTanks();
	InitializeDestroyerTanks();
	InitializeFighterTanks();

	InitializeGrassBlocks();
	InitializeBrickBlocks();
	InitializeSteelBlocks();
	InitializeWaterBlocks();
	InitializeIceBlocks();
}

void Map::Load()
{
	LoadGrassBlocks();
	LoadBrickBlocks();
	LoadSteelBlocks();
	LoadWaterBlocks();
	LoadIceBlocks();
}

void Map::Update(float deltaTimerMilli)
{
	if (!m_base.GetCheckDestroy()) {

		//-----------------------------Updating Player Class-----------------------------
		m_player1.Update(m_playerNormalBulletVector, m_playerArmourBulletVector, deltaTimerMilli);

		if (m_player1Mode == false && m_player2Mode == true) {

			m_player2.Update(m_playerNormalBulletVector, m_playerArmourBulletVector, deltaTimerMilli);
		}
		//-----------------------------Updating Player Class-----------------------------

		//-----------------------------Updating Bullet Class-----------------------------
		for (size_t i = 0; i < m_playerNormalBulletVector.size(); ++i) {

			m_playerNormalBulletVector[i].Update();
		}
		for (size_t i = 0; i < m_playerArmourBulletVector.size(); ++i) {

			m_playerArmourBulletVector[i].Update();
		}
		for (size_t i = 0; i < m_enemyNormalBulletVector.size(); ++i) {

			m_enemyNormalBulletVector[i].Update();
		}
		for (size_t i = 0; i < m_enemyArmourBulletVector.size(); ++i) {

			m_enemyArmourBulletVector[i].Update();
		}
		//-----------------------------Updating Bullet Class-----------------------------

		Player1ModeUpdate();
	
		if (m_player1Mode == false && m_player2Mode == true) {

			Player2ModeUpdate();
		}

		PlayerBulletUpdate();
		EnemyBulletUpdate();
	}
}

void Map::Draw(sf::RenderWindow& window)
{
	m_grid.Draw(window);

	DrawBrickBlocks(window);
	DrawSteelBlocks(window);
	DrawWaterBlocks(window);
	DrawIceBlocks(window);

	if (m_player2Mode == true) {

		m_player1.Draw(window);
		m_player2.Draw(window);
	}
	else {

		m_player1.Draw(window);
	}

	for (size_t i = 0; i < m_playerNormalBulletVector.size(); ++i) {

		m_playerNormalBulletVector[i].Draw(window);
	}
	for (size_t i = 0; i < m_playerArmourBulletVector.size(); ++i) {

		m_playerArmourBulletVector[i].Draw(window);
	}
	for (size_t i = 0; i < m_enemyNormalBulletVector.size(); ++i) {

		m_enemyNormalBulletVector[i].Draw(window);
	}
	for (size_t i = 0; i < m_enemyArmourBulletVector.size(); ++i) {

		m_enemyArmourBulletVector[i].Draw(window);
	}

	m_base.Draw(window);

	DrawGrassBlocks(window);
}

Map::~Map()
{
	delete[] m_grassBlocks;
	delete[] m_brickBlocks;
	delete[] m_steelBlocks;
	delete[] m_waterBlocks;
	delete[] m_iceBlocks;
}