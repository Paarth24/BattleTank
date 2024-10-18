#include <fstream>
#include <iostream>

#include "Map.h"

Map::Map(
	std::string& levelId,
	int totalBasicTanks,
	int totalLightBattleTanks,
	int totalDoubleBarrelTanks,
	int totalDestroyerTanks,
	int totalFighterTanks,
	int totalGrassBlocks,
	int totalBrickBlocks,
	int totalSteelBlocks,
	int totalWaterBlocks,
	int totalIceBlocks,
	std::string powerUpId):
	m_levelId(levelId),
	m_gameOver(false),
	m_gameClear(false),
	m_grid(sf::Vector2i(26, 13)),
	m_mapBackgroundSize(nullptr),
	m_mapBackgroundPosition(nullptr),
	m_blockOffset(nullptr),
	m_player1Mode(false),
	m_player2Mode(false),
	m_player1(nullptr),
	m_player2(nullptr),
	m_totalBasicTanks(totalBasicTanks),
	m_basicTanks(nullptr),
	m_basicTankKilled(0),
	m_totalLightBattleTanks(totalLightBattleTanks),
	m_lightBattleTanks(nullptr),
	m_lightBattleTankKilled(0),
	m_totalDoubleBarrelTanks(totalDoubleBarrelTanks),
	m_doubleBarrelTanks(nullptr),
	m_doubleBarrelTankKilled(0),
	m_totalDestroyerTanks(totalDestroyerTanks),
	m_destroyerTanks(nullptr),
	m_destroyerTankKilled(0),
	m_totalFighterTanks(totalFighterTanks),
	m_fighterTanks(nullptr),
	m_fighterTankKilled(0),
	m_totalGrassBlocks(totalGrassBlocks),
	m_grassBlocks(nullptr),
	m_totalBrickBlocks(totalBrickBlocks),
	m_brickBlocks(nullptr),
	m_totalSteelBlocks(totalSteelBlocks),
	m_steelBlocks(nullptr),
	m_totalWaterBlocks(totalWaterBlocks),
	m_waterBlocks(nullptr),
	m_totalIceBlocks(totalIceBlocks),
	m_iceBlocks(nullptr),
	m_remainingEnemyTanks(0),
	m_powerUpId(powerUpId)
{
}

void Map::SetPLayerMode(bool& player1Mode, bool& player2Mode)
{
	m_player1Mode = player1Mode;
	m_player2Mode = player2Mode;
}

void Map::Restart()
{
	m_gameOver = false;
	m_gameClear = false;

	m_playerNormalBulletVector.clear();
	m_playerArmourBulletVector.clear();
	m_enemyNormalBulletVector.clear();
	m_enemyArmourBulletVector.clear();
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
	sf::Vector2f movementSpeed = object1.GetMovementSpeed();

	if (direction == "up") {

		if (sprite.getPosition().y - movementSpeed.y >= m_mapBackgroundPosition->y) {

			return false;
		}
		else {

			return true;
		}
	}
	else if (direction == "left") {

		if (sprite.getPosition().x - movementSpeed.x >= m_mapBackgroundPosition->x) {

			return false;
		}
		else {

			return true;
		}
	}
	else if (direction == "down") {

		if (sprite.getPosition().y + movementSpeed.y <= m_mapBackgroundPosition->y + m_mapBackgroundSize->y - sprite.getGlobalBounds().height) {

			return false;
		}
		else {

			return true;
		}
	}
	else if (direction == "right") {

		if (sprite.getPosition().x + movementSpeed.x <= m_mapBackgroundPosition->x + m_mapBackgroundSize->x - sprite.getGlobalBounds().width) {

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
	sf::Vector2f movementSpeed = object1.GetMovementSpeed();

	sf::FloatRect sprite1Global = object1.GetSprite().getGlobalBounds();
	sf::FloatRect sprite2Global = sprite.getGlobalBounds();

	sf::Vector2f sprite1Position = object1.GetSprite().getPosition();
	sf::Vector2f sprite2Position = sprite.getPosition();

	if (direction == "up") {

		if (sprite1Global.left < sprite2Global.left + sprite2Global.width && sprite1Global.left + sprite1Global.width > sprite2Global.left &&
			sprite1Position.y - movementSpeed.y <= sprite2Position.y + sprite2Global.height && sprite1Position.y - movementSpeed.y >= sprite2Position.y) {

			return true;
		}
		else {

			return false;
		}
	}
	else if (direction == "left") {

		if (sprite1Position.x - movementSpeed.x <= sprite2Position.x + sprite2Global.width && sprite1Position.x - movementSpeed.x >= sprite2Position.x &&
			sprite1Global.top < sprite2Global.top + sprite2Global.height && sprite1Global.top + sprite1Global.height > sprite2Global.top) {

			return true;
		}
		else {

			return false;
		}
	}
	else if (direction == "down") {

		if (sprite1Global.left < sprite2Global.left + sprite2Global.width && sprite1Global.left + sprite1Global.width > sprite2Global.left &&
			sprite1Position.y + movementSpeed.y + sprite1Global.height >= sprite2Position.y && sprite1Position.y + movementSpeed.y <= sprite2Position.y) {

			return true;
		}
		else {

			return false;
		}
	}
	else if (direction == "right") {

		if (sprite1Position.x + sprite1Global.width + movementSpeed.x >= sprite2Position.x && sprite1Position.x <= sprite2Position.x + movementSpeed.x &&
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
	std::cout << m_powerUpId << std::endl;
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

		m_basicTanks[i].Initialize("basic", m_mapBackgroundPosition, m_blockOffset);

		if (i == 0 || i == 1 || i == 2) {

			m_basicTanks[i].SetSpawnRate(0);
		}
		else {

			int random = 5000 + (rand() % 60000);

			m_basicTanks[i].SetSpawnRate(random);
		}
	}
}

void Map::InitializeLightBattleTanks()
{
	for (int i = 0;i < m_totalLightBattleTanks; ++i) {

		m_lightBattleTanks[i].Initialize("lightBattle", m_mapBackgroundPosition, m_blockOffset);

		int random = 5000 + (rand() % 60000);

		m_lightBattleTanks[i].SetSpawnRate(random);
	}
}

void Map::InitializeDoubleBarrelTanks()
{
	for (int i = 0;i < m_totalDoubleBarrelTanks; ++i) {

		m_doubleBarrelTanks[i].Initialize("doubleBarrel", m_mapBackgroundPosition, m_blockOffset);

		int random = 5000 + (rand() % 60000);

		m_doubleBarrelTanks[i].SetSpawnRate(random);
	}
}

void Map::InitializeDestroyerTanks()
{
	for (int i = 0;i < m_totalDestroyerTanks; ++i) {

		m_destroyerTanks[i].Initialize("destroyer", m_mapBackgroundPosition, m_blockOffset);

		int random = 5000 + (rand() % 60000);

		m_destroyerTanks[i].SetSpawnRate(random);
	}
}

void Map::InitializeFighterTanks()
{
	for (int i = 0;i < m_totalFighterTanks; ++i) {

		m_fighterTanks[i].Initialize("fighter", m_mapBackgroundPosition, m_blockOffset);

		int random = 5000 + (rand() % 60000);

		m_fighterTanks[i].SetSpawnRate(random);
	}
}

void Map::LoadBasicTanks()
{
	for (int i = 0;i < m_totalBasicTanks; ++i) {

		m_basicTanks[i].Load();
	}
}

void Map::LoadLightBattleTanks()
{
	for (int i = 0;i < m_totalLightBattleTanks; ++i) {

		m_lightBattleTanks[i].Load();
	}
}

void Map::LoadDoubleBarrelTanks()
{
	for (int i = 0;i < m_totalDoubleBarrelTanks; ++i) {

		m_doubleBarrelTanks[i].Load();
	}
}

void Map::LoadDestroyerTanks()
{
	for (int i = 0;i < m_totalDestroyerTanks; ++i) {

		m_destroyerTanks[i].Load();
	}
}

void Map::LoadFighterTanks()
{
	for (int i = 0;i < m_totalFighterTanks; ++i) {

		m_fighterTanks[i].Load();
	}
}

void Map::UpdateBasicTanks()
{
	for (int i = 0; i < m_totalBasicTanks; ++i) {

		BasicTank* tank = &m_basicTanks[i];

		tank->SetCollision(false);
		//-----------------------------Checking if Basic Tank Collided With Map Boundary-----------------------------
		if (BoundaryCollision(*tank)) {

			tank->SetCollision(true);
			continue;
		}
		//-----------------------------Checking if Basic Tank Collided With Map Boundary-----------------------------
	
		//-----------------------------Checking if Basic Tank Collided With Player1-----------------------------
		if (!m_player1->GetCheckDestroy()) {

			if (ObjectCollision(*tank, m_player1->GetSprite())) {

				tank->SetCollision(true);
				continue;
			}
		}
		//-----------------------------Checking if Basic Tank Collided With Player1-----------------------------

		//-----------------------------Checking if Basic Tank Collided With Player2-----------------------------
		if (m_player2Mode) {

			if (!m_player2->GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_player2->GetSprite())) {

					tank->SetCollision(true);
					continue;
				}
			}
		}
		//-----------------------------Checking if Basic Tank Collided With Player2-----------------------------

		//-----------------------------Checking if Basic Tank Collided With Base-----------------------------
		if (ObjectCollision(*tank, m_base.GetSprite())) {

			tank->SetCollision(true);
			continue;
		}
		//-----------------------------Checking if Basic Tank Collided With Base-----------------------------

		//-----------------------------Checking if Basic Tank Collided With Brick Block-----------------------------		
		bool collision = false;
		
		for (int j = 0; j < m_totalBrickBlocks; ++j) {
				
			if (!m_brickBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_brickBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Basic Tank Collided With Brick Block-----------------------------
	
		//-----------------------------Checking if Basic Tank Collided With Steel Block-----------------------------
		for (int j = 0; j < m_totalSteelBlocks; ++j) {

			if (!m_steelBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_steelBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Basic Tank Collided With Steel Block-----------------------------
		
		//-----------------------------Checking if Basic Tank Collided With Water Block-----------------------------
		for (int j = 0; j < m_totalWaterBlocks; ++j) {

			if (!m_waterBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_waterBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Basic Tank Collided With Water Block-----------------------------

		//-----------------------------Checking if Basic Tank Collided With Ice Block-----------------------------
		for (int j = 0; j < m_totalIceBlocks; ++j) {

			if (!m_iceBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_iceBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Basic Tank Collided With Ice Block-----------------------------
	}
}

void Map::UpdateLightBattleTanks()
{
	for (int i = 0; i < m_totalLightBattleTanks; ++i) {

		LightBattleTank* tank = &m_lightBattleTanks[i];

		tank->SetCollision(false);
		//-----------------------------Checking if Light Battle Tank Collided With Map Boundary-----------------------------
		if (BoundaryCollision(*tank)) {

			tank->SetCollision(true);
			continue;
		}
		//-----------------------------Checking if Light Battle Tank Collided With Map Boundary-----------------------------

		//-----------------------------Checking if Light Battle Tank Collided With Player1-----------------------------
		if (!m_player1->GetCheckDestroy()) {

			if (ObjectCollision(*tank, m_player1->GetSprite())) {

				tank->SetCollision(true);
				continue;
			}
		}
		//-----------------------------Checking if Light Battle Tank Collided With Player1-----------------------------

		//-----------------------------Checking if Light Battle Tank Collided With Player2-----------------------------
		if (m_player2Mode) {

			if (!m_player2->GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_player2->GetSprite())) {

					tank->SetCollision(true);
					continue;
				}
			}
		}
		//-----------------------------Checking if Light Battle Tank Collided With Player2-----------------------------

		//-----------------------------Checking if Light Battle Tank Collided With Base-----------------------------
		if (ObjectCollision(*tank, m_base.GetSprite())) {

			tank->SetCollision(true);
			continue;
		}
		//-----------------------------Checking if Light Battle Tank Collided With Base-----------------------------

		//-----------------------------Checking if Light Battle Tank Collided With Brick Block-----------------------------		
		bool collision = false;

		for (int j = 0; j < m_totalBrickBlocks; ++j) {

			if (!m_brickBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_brickBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Light Battle Tank Collided With Brick Block-----------------------------

		//-----------------------------Checking if Light Battle Tank Collided With Steel Block-----------------------------
		for (int j = 0; j < m_totalSteelBlocks; ++j) {

			if (!m_steelBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_steelBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Light Battle Tank Collided With Steel Block-----------------------------

		//-----------------------------Checking if Light Battle Tank Collided With Water Block-----------------------------
		for (int j = 0; j < m_totalWaterBlocks; ++j) {

			if (!m_waterBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_waterBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Light Battle Tank Collided With Water Block-----------------------------

		//-----------------------------Checking if Light Battle Tank Collided With Ice Block-----------------------------
		for (int j = 0; j < m_totalIceBlocks; ++j) {

			if (!m_iceBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_iceBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Light Battle Tank Collided With Ice Block-----------------------------
	}
}

void Map::UpdateDoubleBarrelTanks()
{
	for (int i = 0; i < m_totalDoubleBarrelTanks; ++i) {

		DoubleBarrelTank* tank = &m_doubleBarrelTanks[i];

		tank->SetCollision(false);
		//-----------------------------Checking if Double Barrel Tank Collided With Map Boundary-----------------------------
		if (BoundaryCollision(*tank)) {

			tank->SetCollision(true);
			continue;
		}
		//-----------------------------Checking if Double Barrel Tank Collided With Map Boundary-----------------------------

		//-----------------------------Checking if Double Barrel Tank Collided With Player1-----------------------------
		if (!m_player1->GetCheckDestroy()) {

			if (ObjectCollision(*tank, m_player1->GetSprite())) {

				tank->SetCollision(true);
				continue;
			}
		}
		//-----------------------------Checking if Double Barrel Tank Collided With Player1-----------------------------

		//-----------------------------Checking if Double Barrel Tank Collided With Player2-----------------------------
		if (m_player2Mode) {

			if (!m_player2->GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_player2->GetSprite())) {

					tank->SetCollision(true);
					continue;
				}
			}
		}
		//-----------------------------Checking if Double Barrel Tank Collided With Player2-----------------------------

		//-----------------------------Checking if Double Barrel Tank Collided With Base-----------------------------
		if (ObjectCollision(*tank, m_base.GetSprite())) {

			tank->SetCollision(true);
			continue;
		}
		//-----------------------------Checking if Double Barrel Tank Collided With Base-----------------------------

		//-----------------------------Checking if Double Barrel Tank Collided With Brick Block-----------------------------		
		bool collision = false;

		for (int j = 0; j < m_totalBrickBlocks; ++j) {

			if (!m_brickBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_brickBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Double Barrel Tank Collided With Brick Block-----------------------------

		//-----------------------------Checking if Double Barrel Tank Collided With Steel Block-----------------------------
		for (int j = 0; j < m_totalSteelBlocks; ++j) {

			if (!m_steelBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_steelBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Double Barrel Tank Collided With Steel Block-----------------------------

		//-----------------------------Checking if Double Barrel Tank Collided With Water Block-----------------------------
		for (int j = 0; j < m_totalWaterBlocks; ++j) {

			if (!m_waterBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_waterBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Double Barrel Tank Collided With Water Block-----------------------------

		//-----------------------------Checking if Double Barrel Tank Collided With Ice Block-----------------------------
		for (int j = 0; j < m_totalIceBlocks; ++j) {

			if (!m_iceBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_iceBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Double Barrel Tank Collided With Ice Block-----------------------------
	}
}

void Map::UpdateDestroyerTanks()
{
	for (int i = 0; i < m_totalDestroyerTanks; ++i) {

		DestroyerTank* tank = &m_destroyerTanks[i];

		tank->SetCollision(false);
		//-----------------------------Checking if Destroyer Tank Collided With Map Boundary-----------------------------
		if (BoundaryCollision(*tank)) {

			tank->SetCollision(true);
			continue;
		}
		//-----------------------------Checking if Destroyer Tank Collided With Map Boundary-----------------------------

		//-----------------------------Checking if Destroyer Tank Collided With Player1-----------------------------
		if (!m_player1->GetCheckDestroy()) {

			if (ObjectCollision(*tank, m_player1->GetSprite())) {

				tank->SetCollision(true);
				continue;
			}
		}
		//-----------------------------Checking if Destroyer Tank Collided With Player1-----------------------------

		//-----------------------------Checking if Destroyer Tank Collided With Player2-----------------------------
		if (m_player2Mode) {

			if (!m_player2->GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_player2->GetSprite())) {

					tank->SetCollision(true);
					continue;
				}
			}
		}
		//-----------------------------Checking if Destroyer Tank Collided With Player2-----------------------------

		//-----------------------------Checking if Destroyer Tank Collided With Base-----------------------------
		if (ObjectCollision(*tank, m_base.GetSprite())) {

			tank->SetCollision(true);
			continue;
		}
		//-----------------------------Checking if Destroyer Tank Collided With Base-----------------------------

		//-----------------------------Checking if Destroyer Tank Collided With Brick Block-----------------------------		
		bool collision = false;

		for (int j = 0; j < m_totalBrickBlocks; ++j) {

			if (!m_brickBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_brickBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Destroyer Tank Collided With Brick Block-----------------------------

		//-----------------------------Checking if Destroyer Tank Collided With Steel Block-----------------------------
		for (int j = 0; j < m_totalSteelBlocks; ++j) {

			if (!m_steelBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_steelBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Destroyer Tank Collided With Steel Block-----------------------------

		//-----------------------------Checking if Destroyer Tank Collided With Water Block-----------------------------
		for (int j = 0; j < m_totalWaterBlocks; ++j) {

			if (!m_waterBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_waterBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Destroyer Tank Collided With Water Block-----------------------------

		//-----------------------------Checking if Destroyer Tank Collided With Ice Block-----------------------------
		for (int j = 0; j < m_totalIceBlocks; ++j) {

			if (!m_iceBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_iceBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Destroyer Tank Collided With Ice Block-----------------------------
	}
}

void Map::UpdateFighterTanks()
{
	for (int i = 0; i < m_totalFighterTanks; ++i) {

		FighterTank* tank = &m_fighterTanks[i];

		tank->SetCollision(false);
		//-----------------------------Checking if Fighter Tank Collided With Map Boundary-----------------------------
		if (BoundaryCollision(*tank)) {

			tank->SetCollision(true);
			continue;
		}
		//-----------------------------Checking if Fighter Tank Collided With Map Boundary-----------------------------

		//-----------------------------Checking if Fighter Tank Collided With Player1-----------------------------
		if (!m_player1->GetCheckDestroy()) {

			if (ObjectCollision(*tank, m_player1->GetSprite())) {

				tank->SetCollision(true);
				continue;
			}
		}
		//-----------------------------Checking if Fighter Tank Collided With Player1-----------------------------

		//-----------------------------Checking if Fighter Tank Collided With Player2-----------------------------
		if (m_player2Mode) {

			if (!m_player2->GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_player2->GetSprite())) {

					tank->SetCollision(true);
					continue;
				}
			}
		}
		//-----------------------------Checking if Fighter Tank Collided With Player2-----------------------------

		//-----------------------------Checking if Fighter Tank Collided With Base-----------------------------
		if (ObjectCollision(*tank, m_base.GetSprite())) {

			tank->SetCollision(true);
			continue;
		}
		//-----------------------------Checking if Fighter Tank Collided With Base-----------------------------

		//-----------------------------Checking if Fighter Tank Collided With Brick Block-----------------------------		
		bool collision = false;

		for (int j = 0; j < m_totalBrickBlocks; ++j) {

			if (!m_brickBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_brickBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Fighter Tank Collided With Brick Block-----------------------------

		//-----------------------------Checking if Fighter Tank Collided With Steel Block-----------------------------
		for (int j = 0; j < m_totalSteelBlocks; ++j) {

			if (!m_steelBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_steelBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Fighter Tank Collided With Steel Block-----------------------------

		//-----------------------------Checking if Fighter Tank Collided With Water Block-----------------------------
		for (int j = 0; j < m_totalWaterBlocks; ++j) {

			if (!m_waterBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_waterBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Fighter Tank Collided With Water Block-----------------------------

		//-----------------------------Checking if Fighter Tank Collided With Ice Block-----------------------------
		for (int j = 0; j < m_totalIceBlocks; ++j) {

			if (!m_iceBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(*tank, m_iceBlocks[j].GetSprite())) {

					tank->SetCollision(true);
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Fighter Tank Collided With Ice Block-----------------------------
	}
}

void Map::DrawBasicTanks(sf::RenderWindow& window)
{
	for (int i = 0;i < m_totalBasicTanks; ++i) {

		m_basicTanks[i].Draw(window);
	}
}

void Map::DrawLightBattleTanks(sf::RenderWindow& window)
{
	for (int i = 0;i < m_totalLightBattleTanks; ++i) {

		m_lightBattleTanks[i].Draw(window);
	}
}

void Map::DrawDoubleBarrelTanks(sf::RenderWindow& window)
{
	for (int i = 0;i < m_totalDoubleBarrelTanks; ++i) {

		m_doubleBarrelTanks[i].Draw(window);
	}
}

void Map::DrawDestroyerTanks(sf::RenderWindow& window)
{
	for (int i = 0;i < m_totalDestroyerTanks; ++i) {

		m_destroyerTanks[i].Draw(window);
	}
}

void Map::DrawFighterTanks(sf::RenderWindow& window)
{
	for (int i = 0;i < m_totalFighterTanks; ++i) {

		m_fighterTanks[i].Draw(window);
	}
}

void Map::InitializeGrassBlocks()
{
	std::ifstream file;
	file.open(m_levelId + "MapGrassBlocks.rmap");

	if (file.is_open()) {

		std::string fileData;
		std::string mapData;

		sf::Vector2i gridIndex;

		for (int i = 0; i < m_totalGrassBlocks; ++i) {

			file >> fileData;

			DecypheringMapBlockData(fileData, mapData);

			gridIndex = StringtoVector2i(mapData);

			m_grassBlocks[i].Initialize(gridIndex, m_mapBackgroundPosition, m_blockOffset);
		}

		file.close();
	}
}

void Map::InitializeBrickBlocks()
{
	std::ifstream file;
	file.open(m_levelId + "MapBrickBlocks.rmap");

	if (file.is_open()) {

		std::string fileData;
		std::string mapData;

		sf::Vector2i gridIndex;

		for (int i = 0; i < m_totalBrickBlocks; ++i) {

			file >> fileData;

			DecypheringMapBlockData(fileData, mapData);

			gridIndex = StringtoVector2i(mapData);

			m_brickBlocks[i].Initialize(gridIndex, m_mapBackgroundPosition, m_blockOffset);
		}

		file.close();
	}
}

void Map::InitializeSteelBlocks()
{
	std::ifstream file;
	file.open(m_levelId + "MapSteelBlocks.rmap");

	if (file.is_open()) {

		std::string fileData;
		std::string mapData;

		sf::Vector2i gridIndex;

		for (int i = 0; i < m_totalSteelBlocks; ++i) {

			file >> fileData;

			DecypheringMapBlockData(fileData, mapData);

			gridIndex = StringtoVector2i(mapData);

			m_steelBlocks[i].Initialize(gridIndex, m_mapBackgroundPosition, m_blockOffset);
		}

		file.close();
	}
}

void Map::InitializeWaterBlocks()
{
	std::ifstream file;
	file.open(m_levelId + "MapWaterBlocks.rmap");

	if (file.is_open()) {

		std::string fileData;
		std::string mapData;

		sf::Vector2i gridIndex;

		for (int i = 0; i < m_totalWaterBlocks; ++i) {

			file >> fileData;

			DecypheringMapBlockData(fileData, mapData);

			gridIndex = StringtoVector2i(mapData);

			m_waterBlocks[i].Initialize(gridIndex, m_mapBackgroundPosition, m_blockOffset);
		}

		file.close();
	}
}

void Map::InitializeIceBlocks()
{
	std::ifstream file;
	file.open(m_levelId + "MapIceBlocks.rmap");

	if (file.is_open()) {

		std::string fileData;
		std::string mapData;

		sf::Vector2i gridIndex;

		for (int i = 0; i < m_totalIceBlocks; ++i) {

			file >> fileData;

			DecypheringMapBlockData(fileData, mapData);

			gridIndex = StringtoVector2i(mapData);

			m_iceBlocks[i].Initialize(gridIndex, m_mapBackgroundPosition, m_blockOffset);
		}

		file.close();
	}
}

void Map::LoadGrassBlocks()
{
	std::string fileName = "world/blocks/textures/grass.png";

	for (int i = 0; i < m_totalGrassBlocks; ++i) {

		m_grassBlocks[i].Load(fileName, m_blockOffset);
	}
}

void Map::LoadBrickBlocks()
{
	std::string fileName = "world/blocks/textures/brick.png";

	for (int i = 0; i < m_totalBrickBlocks; ++i) {

		m_brickBlocks[i].Load(fileName, m_blockOffset);
	}
}

void Map::LoadSteelBlocks()
{
	std::string fileName = "world/blocks/textures/steel.png";

	for (int i = 0; i < m_totalSteelBlocks; ++i) {

		m_steelBlocks[i].Load(fileName, m_blockOffset);
	}
}

void Map::LoadWaterBlocks()
{
	std::string fileName = "world/blocks/textures/water.png";

	for (int i = 0; i < m_totalWaterBlocks; ++i) {

		m_waterBlocks[i].Load(fileName, m_blockOffset);
	}
}

void Map::LoadIceBlocks()
{
	std::string fileName = "world/blocks/textures/ice.png";

	for (int i = 0; i < m_totalIceBlocks; ++i) {

		m_iceBlocks[i].Load(fileName, m_blockOffset);
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
	m_player1->SetCollision(false);

	//-----------------------------Checking if Player1 Collided With Player2-----------------------------
	if (m_player1Mode == false && m_player2Mode == true) {

		if (!m_player2->GetCheckDestroy()) {

			if (ObjectCollision(*m_player1, m_player2->GetSprite())) {

				m_player1->SetCollision(true);
				return;
			}
		}
	}
	//-----------------------------Checking if Player1 Collided With Player2-----------------------------

	//-----------------------------Checking if Player1 Collided With Map Boundary-----------------------------
	if (BoundaryCollision(*m_player1)) {

		m_player1->SetCollision(true);
		return;
	}
	//-----------------------------Checking if Player1 Collided With Map Boundary-----------------------------

	//-----------------------------Checking if Player1 Collided With Base-----------------------------
	if (ObjectCollision(*m_player1, m_base.GetSprite())) {

		m_player1->SetCollision(true);
		return;
	}
	//-----------------------------Checking if Player1 Collided With Base-----------------------------
	
	//-----------------------------Checking if Player1 Collided With Enemies-----------------------------
	bool collision = false;
	
	for (int i = 0; i < m_totalBasicTanks; ++i) {

		if (!m_basicTanks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player1, m_basicTanks[i].GetSprite())) {

				m_player1->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}

	for (int i = 0; i < m_totalLightBattleTanks; ++i) {

		if (!m_lightBattleTanks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player1, m_lightBattleTanks[i].GetSprite())) {

				m_player1->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}

	for (int i = 0; i < m_totalDoubleBarrelTanks; ++i) {

		if (!m_doubleBarrelTanks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player1, m_doubleBarrelTanks[i].GetSprite())) {

				m_player1->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}

	for (int i = 0; i < m_totalDestroyerTanks; ++i) {

		if (!m_destroyerTanks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player1, m_destroyerTanks[i].GetSprite())) {

				m_player1->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}
	
	for (int i = 0; i < m_totalFighterTanks; ++i) {

		if (!m_fighterTanks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player1, m_fighterTanks[i].GetSprite())) {

				m_player1->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}
	//-----------------------------Checking if Player1 Collided With Enemies-----------------------------

	//-----------------------------Checking if Player1 Collided With Brick Block-----------------------------
	for (int i = 0; i < m_totalBrickBlocks; ++i) {
				
		if (!m_brickBlocks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player1, m_brickBlocks[i].GetSprite())) {

				m_player1->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}
	//-----------------------------Checking if Player1 Collided With Brick Block-----------------------------

	//-----------------------------Checking if Player1 Collided With Steel Block-----------------------------
	for (int i = 0; i < m_totalSteelBlocks; ++i) {

		if (!m_steelBlocks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player1, m_steelBlocks[i].GetSprite())) {

				m_player1->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}
	//-----------------------------Checking if Player1 Collided With Steel Block-----------------------------

	//-----------------------------Checking if Player1 Collided With Water Block-----------------------------
	for (int i = 0; i < m_totalWaterBlocks; ++i) {

		if (ObjectCollision(*m_player1, m_waterBlocks[i].GetSprite())) {

			m_player1->SetCollision(true);
			collision = true;
			break;
		}
	}
	if (collision) {

		return;
	}
	//-----------------------------Checking if Player1 Collided With Water Block-----------------------------

	//-----------------------------Checking if Player1 Collided With Ice Block-----------------------------
	for (int i = 0; i < m_totalIceBlocks; ++i) {

		if (ObjectCollision(*m_player1, m_iceBlocks[i].GetSprite())) {

			m_player1->CollissionWithIceBlock(true);
			break;
		}
		else {

			m_player1->CollissionWithIceBlock(false);
		}
	}
	//-----------------------------Checking if Player1 Collided With Ice Block-----------------------------
}

void Map::Player2ModeUpdate()
{
	m_player2->SetCollision(false);

	//-----------------------------Checking if Player2 Collided With Player1-----------------------------
	if (!m_player1->GetCheckDestroy()) {

		if (ObjectCollision(*m_player2, m_player1->GetSprite())) {

			m_player2->SetCollision(true);
			return;
		}
	}
	//-----------------------------Checking if Player2 Collided With Player1-----------------------------

	//-----------------------------Checking if Player2 Collided With Map Boundary-----------------------------
	if (BoundaryCollision(*m_player2)) {

		m_player2->SetCollision(true);
		return;
	}
	//-----------------------------Checking if Player2 Collided With Map Boundary-----------------------------

	//-----------------------------Checking if Player2 Collided With Base-----------------------------
	if (ObjectCollision(*m_player2, m_base.GetSprite())) {

		m_player2->SetCollision(true);
		return;
	}
	//-----------------------------Checking if Player2 Collided With Base-----------------------------

	//-----------------------------Checking if Player2 Collided With Enemies-----------------------------
	bool collision = false;

	for (int i = 0; i < m_totalBasicTanks; ++i) {

		if (!m_basicTanks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player2, m_basicTanks[i].GetSprite())) {

				m_player2->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}

	for (int i = 0; i < m_totalLightBattleTanks; ++i) {

		if (!m_lightBattleTanks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player2, m_lightBattleTanks[i].GetSprite())) {

				m_player2->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}

	for (int i = 0; i < m_totalDoubleBarrelTanks; ++i) {

		if (!m_doubleBarrelTanks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player2, m_doubleBarrelTanks[i].GetSprite())) {

				m_player2->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}

	for (int i = 0; i < m_totalDestroyerTanks; ++i) {

		if (!m_destroyerTanks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player2, m_destroyerTanks[i].GetSprite())) {

				m_player2->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}

	for (int i = 0; i < m_totalFighterTanks; ++i) {

		if (!m_fighterTanks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player2, m_fighterTanks[i].GetSprite())) {

				m_player2->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}
	//-----------------------------Checking if Player2 Collided With Enemies-----------------------------

	//-----------------------------Checking if Player2 Collided With Brick Block-----------------------------
	for (int i = 0; i < m_totalBrickBlocks; ++i) {

		if (!m_brickBlocks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player2, m_brickBlocks[i].GetSprite())) {

				m_player2->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}
	//-----------------------------Checking if Player2 Collided With Brick Block-----------------------------

	//-----------------------------Checking if Player2 Collided With Steel Block-----------------------------
	for (int i = 0; i < m_totalSteelBlocks; ++i) {

		if (!m_steelBlocks[i].GetCheckDestroy()) {

			if (ObjectCollision(*m_player2, m_steelBlocks[i].GetSprite())) {

				m_player2->SetCollision(true);
				collision = true;
				break;
			}
		}
	}
	if (collision) {

		return;
	}
	//-----------------------------Checking if Player2 Collided With Steel Block-----------------------------

	//-----------------------------Checking if Player2 Collided With Water Block-----------------------------
	for (int i = 0; i < m_totalWaterBlocks; ++i) {

		if (ObjectCollision(*m_player2, m_waterBlocks[i].GetSprite())) {

			m_player2->SetCollision(true);
			collision = true;
			break;
		}
	}
	if (collision) {

		return;
	}
	//-----------------------------Checking if Player2 Collided With Water Block-----------------------------

	//-----------------------------Checking if Player2 Collided With Ice Block-----------------------------
	for (int i = 0; i < m_totalIceBlocks; ++i) {

		if (ObjectCollision(*m_player2, m_iceBlocks[i].GetSprite())) {

			m_player2->CollissionWithIceBlock(true);
			break;
		}
		else {

			m_player2->CollissionWithIceBlock(false);
		}
	}
	//-----------------------------Checking if Player2 Collided With Ice Block-----------------------------}
}

void Map::PlayerBulletUpdate()
{
	for (size_t i = 0; i < m_playerNormalBulletVector.size(); ++i) {

		Bullet bullet = m_playerNormalBulletVector[i];

	//-----------------------------Checking if Player Normal Bullet Collided With Map Boundary-----------------------------
		if (BoundaryCollision(bullet)) {

			m_playerNormalBulletVector.erase(m_playerNormalBulletVector.begin() + i);
			continue;
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Map Boundary-----------------------------
		
	//-----------------------------Checking if Player Normal Bullet Collided With Player1-----------------------------
		if (!m_player1->GetCheckDestroy() && bullet.GetId() == "player2") {

			if (ObjectCollision(bullet, m_player1->GetSprite())) {

				m_playerNormalBulletVector.erase(m_playerNormalBulletVector.begin() + i);
				m_player1->Freeze();
				continue;
			}
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Player1-----------------------------

	//-----------------------------Checking if Player Normal Bullet Collided With Player2-----------------------------
		if (m_player2Mode && !m_player2->GetCheckDestroy() && bullet.GetId() == "player1") {

			if (ObjectCollision(bullet, m_player2->GetSprite())) {

				m_playerNormalBulletVector.erase(m_playerNormalBulletVector.begin() + i);
				m_player2->Freeze();
				continue;
			}
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Player2-----------------------------

	//-----------------------------Checking if Player Normal Bullet Collided With Enemy-----------------------------
		bool collision = false;
		
		for (int j = 0; j < m_totalBasicTanks; ++j) {

			if (!m_basicTanks[j].GetCheckDestroy()) {

				if (ObjectCollision(bullet, m_basicTanks[j].GetSprite())) {

					m_playerNormalBulletVector.erase(m_playerNormalBulletVector.begin() + i);
					m_basicTanks[j].Destroy();
					++m_basicTankKilled;
					--m_remainingEnemyTanks;

					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}

		for (int j = 0; j < m_totalLightBattleTanks; ++j) {

			if (!m_lightBattleTanks[j].GetCheckDestroy()) {

				if (ObjectCollision(bullet, m_lightBattleTanks[j].GetSprite())) {

					m_playerNormalBulletVector.erase(m_playerNormalBulletVector.begin() + i);
					m_lightBattleTanks[j].Destroy();
					++m_lightBattleTankKilled;
					--m_remainingEnemyTanks;

					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Enemy-----------------------------

	//-----------------------------Checking if Player Normal Bullet Collided With Brick Block-----------------------------
		for (int j = 0; j < m_totalBrickBlocks; ++j) {

			if (!m_brickBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(bullet, m_brickBlocks[j].GetSprite())) {

					m_playerNormalBulletVector.erase(m_playerNormalBulletVector.begin() + i);
					m_brickBlocks[j].Destroy();

					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Brick Block-----------------------------
	
	//-----------------------------Checking if Player Normal Bullet Collided With Steel Block-----------------------------
		for (int j = 0; j < m_totalSteelBlocks; ++j) {

			if (!m_steelBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(bullet, m_steelBlocks[j].GetSprite())) {

					m_playerNormalBulletVector.erase(m_playerNormalBulletVector.begin() + i);
					
					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Steel Block-----------------------------

	//-----------------------------Checking if Player Normal Bullet Collided With Base-----------------------------
		if (ObjectCollision(bullet, m_base.GetSprite())) {

			m_playerNormalBulletVector.erase(m_playerNormalBulletVector.begin() + i);
			m_base.Destroy();

			collision = true;
			continue;
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Base-----------------------------

	//-----------------------------Checking if Player Normal Bullet Collided With Enemy Normal Bullet-----------------------------
		for (int j = 0; j < m_enemyNormalBulletVector.size(); ++j) {

			if (ObjectCollision(bullet, m_enemyNormalBulletVector[j].GetSprite())) {

				m_playerNormalBulletVector.erase(m_playerNormalBulletVector.begin() + i);
				m_enemyNormalBulletVector.erase(m_enemyNormalBulletVector.begin() + j);

				collision = true;
				break;
			}
		}
		if (collision) {

			continue;
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Enemy Normal Bullet-----------------------------
	
	//-----------------------------Checking if Player Normal Bullet Collided With Enemy Armor Bullet-----------------------------
		for (int j = 0; j < m_enemyArmourBulletVector.size(); ++j) {

			if (ObjectCollision(bullet, m_enemyArmourBulletVector[j].GetSprite())) {

				m_playerNormalBulletVector.erase(m_playerNormalBulletVector.begin() + i);
				m_enemyArmourBulletVector.erase(m_enemyArmourBulletVector.begin() + j);
				
				collision = true;
				break;
			}
		}
		if (collision) {

			continue;
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Enemy Armor Bullet-----------------------------
	}

	for (size_t i = 0; i < m_playerArmourBulletVector.size(); ++i) {

		Bullet bullet = m_playerArmourBulletVector[i];

		//-----------------------------Checking if Player Armor Bullet Collided With Map Boundary-----------------------------
		if (BoundaryCollision(bullet)) {

			m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);
			continue;
		}
		//-----------------------------Checking if Player Armor Bullet Collided With Map Boundary-----------------------------

		//-----------------------------Checking if Player Armor Bullet Collided With Player1-----------------------------
		if (!m_player1->GetCheckDestroy() && bullet.GetId() == "player2") {

			if (ObjectCollision(bullet, m_player1->GetSprite())) {

				m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);
				m_player1->Freeze();
				continue;
			}
		}
		//-----------------------------Checking if Player Armor Bullet Collided With Player1-----------------------------

		//-----------------------------Checking if Player Armor Bullet Collided With Player2-----------------------------
		if (!m_player1->GetCheckDestroy() && bullet.GetId() == "player2") {

			if (ObjectCollision(bullet, m_player2->GetSprite())) {

				m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);
				m_player2->Freeze();
				continue;
			}
		}
		//-----------------------------Checking if Player Armor Bullet Collided With Player2-----------------------------

		//-----------------------------Checking if Player Armor Bullet Collided With Enemy-----------------------------
		bool collision = false;

		for (int j = 0; j < m_totalBasicTanks; ++j) {

			if (!m_basicTanks[j].GetCheckDestroy()) {

				if (ObjectCollision(bullet, m_basicTanks[j].GetSprite())) {

					m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);
					m_basicTanks[j].Destroy();
					++m_basicTankKilled;
					--m_remainingEnemyTanks;

					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}

		for (int j = 0; j < m_totalLightBattleTanks; ++j) {

			if (!m_lightBattleTanks[j].GetCheckDestroy()) {

				if (ObjectCollision(bullet, m_lightBattleTanks[j].GetSprite())) {

					m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);
					m_lightBattleTanks[j].Destroy();
					++m_lightBattleTankKilled;
					--m_remainingEnemyTanks;

					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Player Armor Bullet Collided With Enemy-----------------------------

		//-----------------------------Checking if Player Armor Bullet Collided With Brick Block-----------------------------
		for (int j = 0; j < m_totalBrickBlocks; ++j) {

			if (!m_brickBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(bullet, m_brickBlocks[j].GetSprite())) {

					m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);
					m_brickBlocks[j].Destroy();

					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Player Armor Bullet Collided With Brick Block-----------------------------

		//-----------------------------Checking if Player Armor Bullet Collided With Steel Block-----------------------------
		for (int j = 0; j < m_totalSteelBlocks; ++j) {

			if (!m_steelBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(bullet, m_steelBlocks[j].GetSprite())) {

					m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);

					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Player Armor Bullet Collided With Steel Block-----------------------------

		//-----------------------------Checking if Player Armor Bullet Collided With Base-----------------------------
		if (ObjectCollision(bullet, m_base.GetSprite())) {

			m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);
			m_base.Destroy();

			collision = true;
			continue;
		}
		//-----------------------------Checking if Player Armor Bullet Collided With Base-----------------------------

		//-----------------------------Checking if Player Armor Bullet Collided With Enemy Normal Bullet-----------------------------
		for (int j = 0; j < m_enemyNormalBulletVector.size(); ++j) {

			if (ObjectCollision(bullet, m_enemyNormalBulletVector[j].GetSprite())) {

				m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);

				collision = true;
				break;
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Player Armor Bullet Collided With Enemy Normal Bullet-----------------------------

		//-----------------------------Checking if Player Armor Bullet Collided With Enemy Armor Bullet-----------------------------
		for (int j = 0; j < m_enemyArmourBulletVector.size(); ++j) {

			if (ObjectCollision(bullet, m_enemyArmourBulletVector[j].GetSprite())) {

				m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);

				collision = true;
				break;
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Player Armor Bullet Collided With Enemy Armor Bullet-----------------------------
	}
}

void Map::EnemyBulletUpdate() 
{
	for (size_t i = 0; i < m_enemyNormalBulletVector.size(); ++i) {

		Bullet bullet = m_enemyNormalBulletVector[i];

		//-----------------------------Checking if Enemy Normal Bullet Collided With Map Boundary-----------------------------
		if (BoundaryCollision(bullet)) {

			m_enemyNormalBulletVector.erase(m_enemyNormalBulletVector.begin() + i);
			continue;
		}
		//-----------------------------Checking if Enemy Normal Bullet Collided With Map Boundary-----------------------------

		//-----------------------------Checking if Enemy Normal Bullet Collided With Player1-----------------------------
		if (!m_player1->GetCheckDestroy()) {

			if (ObjectCollision(bullet, m_player1->GetSprite())) {

				m_enemyNormalBulletVector.erase(m_enemyNormalBulletVector.begin() + i);
				m_player1->Destroy();
				continue;
			}
		}
		//-----------------------------Checking if Enemy Normal Bullet Collided With Player1-----------------------------

		//-----------------------------Checking if Enemy Normal Bullet Collided With Player2-----------------------------
		if (!m_player2->GetCheckDestroy() && m_player2Mode) {

			if (ObjectCollision(bullet, m_player2->GetSprite())) {

				m_enemyNormalBulletVector.erase(m_enemyNormalBulletVector.begin() + i);
				m_player2->Destroy();
				continue;
			}
		}
		//-----------------------------Checking if Enemy Normal Bullet Collided With Player2-----------------------------

		//-----------------------------Checking if Enemy Normal Bullet Collided With Brick Block-----------------------------
		bool collision = false;

		for (int j = 0; j < m_totalBrickBlocks; ++j) {

			if (!m_brickBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(bullet, m_brickBlocks[j].GetSprite())) {

					m_enemyNormalBulletVector.erase(m_enemyNormalBulletVector.begin() + i);
					m_brickBlocks[j].Destroy();

					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Enemy Normal Bullet Collided With Brick Block-----------------------------

		//-----------------------------Checking if Enemy Normal Bullet Collided With Steel Block-----------------------------
		for (int j = 0; j < m_totalSteelBlocks; ++j) {

			if (!m_steelBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(bullet, m_steelBlocks[j].GetSprite())) {

					m_enemyNormalBulletVector.erase(m_enemyNormalBulletVector.begin() + i);

					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Enemy Normal Bullet Collided With Steel Block-----------------------------

		//-----------------------------Checking if Enemy Normal Bullet Collided With Base-----------------------------
		if (ObjectCollision(bullet, m_base.GetSprite())) {

			m_enemyNormalBulletVector.erase(m_enemyNormalBulletVector.begin() + i);
			m_base.Destroy();
			continue;
		}
		//-----------------------------Checking if Enemy Normal Bullet Collided With Base-----------------------------
	}

	for (size_t i = 0; i < m_enemyArmourBulletVector.size(); ++i) {

		Bullet bullet = m_enemyArmourBulletVector[i];

		//-----------------------------Checking if Enemy Armour Bullet Collided With Map Boundary-----------------------------
		if (BoundaryCollision(bullet)) {

			m_enemyArmourBulletVector.erase(m_enemyArmourBulletVector.begin() + i);
			continue;
		}
		//-----------------------------Checking if Enemy Armour Bullet Collided With Map Boundary-----------------------------

		//-----------------------------Checking if Enemy Armour Bullet Collided With Player1-----------------------------
		if (!m_player1->GetCheckDestroy()) {

			if (ObjectCollision(bullet, m_player1->GetSprite())) {

				m_enemyArmourBulletVector.erase(m_enemyArmourBulletVector.begin() + i);
				m_player1->Destroy();
				continue;
			}
		}
		//-----------------------------Checking if Enemy Armour Bullet Collided With Player1-----------------------------

		//-----------------------------Checking if Enemy Armour Bullet Collided With Player2-----------------------------
		if (!m_player2->GetCheckDestroy() && m_player2Mode) {

			if (ObjectCollision(bullet, m_player2->GetSprite())) {

				m_enemyArmourBulletVector.erase(m_enemyArmourBulletVector.begin() + i);
				m_player2->Destroy();
				continue;
			}
		}
		//-----------------------------Checking if Enemy Armour Bullet Collided With Player2-----------------------------

		//-----------------------------Checking if Enemy Armour Bullet Collided With Brick Block-----------------------------
		bool collision = false;

		for (int j = 0; j < m_totalBrickBlocks; ++j) {

			if (!m_brickBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(bullet, m_brickBlocks[j].GetSprite())) {

					m_enemyArmourBulletVector.erase(m_enemyArmourBulletVector.begin() + i);
					m_brickBlocks[j].Destroy();

					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Enemy Armour Bullet Collided With Brick Block-----------------------------

		//-----------------------------Checking if Enemy Armour Bullet Collided With Steel Block-----------------------------
		for (int j = 0; j < m_totalSteelBlocks; ++j) {

			if (!m_steelBlocks[j].GetCheckDestroy()) {

				if (ObjectCollision(bullet, m_steelBlocks[j].GetSprite())) {

					m_enemyArmourBulletVector.erase(m_enemyArmourBulletVector.begin() + i);

					collision = true;
					break;
				}
			}
		}
		if (collision) {

			continue;
		}
		//-----------------------------Checking if Enemy Armour Bullet Collided With Steel Block-----------------------------

		//-----------------------------Checking if Enemy Armour Bullet Collided With Base-----------------------------
		if (ObjectCollision(bullet, m_base.GetSprite())) {

			m_enemyArmourBulletVector.erase(m_enemyArmourBulletVector.begin() + i);
			m_base.Destroy();
			continue;
		}
		//-----------------------------Checking if Enemy Armour Bullet Collided With Base-----------------------------
	}
}

void Map::Initialize(
	const sf::Vector2f* mapBackgroundSize,
	const sf::Vector2f* mapBackgroundPosition,
	const sf::Vector2f* blockOffset)
{
	m_mapBackgroundSize = mapBackgroundSize;
	m_mapBackgroundPosition = mapBackgroundPosition;

	m_blockOffset = blockOffset;

	m_gameOverText.setString("Game Over");
	m_gameOverText.setCharacterSize(mapBackgroundSize->x / 7);

	m_gameClearText.setString("Cleared");
	m_gameClearText.setCharacterSize(mapBackgroundSize->x / 7);

	m_grid.Initialize(*m_mapBackgroundSize, *m_mapBackgroundPosition, *m_blockOffset);

	m_basicTanks = new BasicTank[m_totalBasicTanks];
	m_lightBattleTanks = new LightBattleTank[m_totalLightBattleTanks];
	m_doubleBarrelTanks = new DoubleBarrelTank[m_totalDoubleBarrelTanks];
	m_destroyerTanks = new DestroyerTank[m_totalDestroyerTanks];
	m_fighterTanks = new FighterTank[m_totalFighterTanks];

	m_remainingEnemyTanks = m_totalBasicTanks + m_totalLightBattleTanks + m_totalDoubleBarrelTanks + m_totalDestroyerTanks + m_totalFighterTanks;

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

	InitializePowerUps();
}

void Map::Load(
	const sf::Font* gameFont,
	const sf::Vector2f* mapBackgroundPosition,
	const sf::Vector2f* mapBackgroundSize)
{
	m_gameOverText.setFont(*gameFont);
	m_gameOverText.setPosition(sf::Vector2f(
		mapBackgroundPosition->x + ((mapBackgroundSize->x - m_gameOverText.getGlobalBounds().width) / 2),
		mapBackgroundPosition->y + ((mapBackgroundSize->y - m_gameOverText.getGlobalBounds().height) / 2)));

	m_gameClearText.setFont(*gameFont);
	m_gameClearText.setPosition(sf::Vector2f(
		mapBackgroundPosition->x + ((mapBackgroundSize->x - m_gameClearText.getGlobalBounds().width) / 2),
		mapBackgroundPosition->y + ((mapBackgroundSize->y - m_gameClearText.getGlobalBounds().height) / 2)));

	LoadBasicTanks();
	LoadLightBattleTanks();
	LoadDoubleBarrelTanks();
	LoadDestroyerTanks();
	LoadFighterTanks();

	LoadGrassBlocks();
	LoadBrickBlocks();
	LoadSteelBlocks();
	LoadWaterBlocks();
	LoadIceBlocks();
}

void Map::Update(float deltaTimerMilli)
{
	if (!m_base.GetCheckDestroy() && !m_gameOver && !m_gameClear) {

		if (m_player1Mode && !m_player2Mode) {

			if (m_player1->GetLives() == 0) {

				m_gameOver = true;
			}
		}
		else {

			if (m_player1->GetLives() == 0 && m_player2->GetLives() == 0) {

				m_gameOver = true;
			}
		}
		
		if (m_remainingEnemyTanks <= 0) {

			m_gameClear = true;
		}

		//-----------------------------Updating Player Class-----------------------------
		m_player1->Update(m_playerNormalBulletVector, m_playerArmourBulletVector, deltaTimerMilli);

		if (m_player1Mode == false && m_player2Mode == true) {

			m_player2->Update(m_playerNormalBulletVector, m_playerArmourBulletVector, deltaTimerMilli);
		}
		//-----------------------------Updating Player Class-----------------------------

		//-----------------------------Updating Enemy Class-----------------------------
		for (int i = 0; i < m_totalBasicTanks; ++i) {

			m_basicTanks[i].Update(m_enemyNormalBulletVector, m_enemyArmourBulletVector, deltaTimerMilli);
		}
		for (int i = 0; i < m_totalLightBattleTanks; ++i) {

			m_lightBattleTanks[i].Update(m_enemyNormalBulletVector, m_enemyArmourBulletVector, deltaTimerMilli);
		}
		for (int i = 0; i < m_totalDoubleBarrelTanks; ++i) {

			m_doubleBarrelTanks[i].Update(m_enemyNormalBulletVector, m_enemyArmourBulletVector, deltaTimerMilli);
		}
		for (int i = 0; i < m_totalDestroyerTanks; ++i) {

			m_destroyerTanks[i].Update(m_enemyNormalBulletVector, m_enemyArmourBulletVector, deltaTimerMilli);
		}
		for (int i = 0; i < m_totalFighterTanks; ++i) {

			m_fighterTanks[i].Update(m_enemyNormalBulletVector, m_enemyArmourBulletVector, deltaTimerMilli);
		}
		//-----------------------------Updating Enemy Class-----------------------------

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

		UpdateBasicTanks();
		UpdateLightBattleTanks();
		UpdateDoubleBarrelTanks();
		UpdateDestroyerTanks();
		UpdateFighterTanks();

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

	DrawBasicTanks(window);
	DrawLightBattleTanks(window);
	DrawDoubleBarrelTanks(window);
	DrawDestroyerTanks(window);
	DrawFighterTanks(window);

	if (m_player2Mode == true) {

		m_player1->Draw(window);
		m_player2->Draw(window);
	}
	else {

		m_player1->Draw(window);
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

	if (m_gameOver) {

		window.draw(m_gameOverText);
	}

	if(m_gameClear) {

		window.draw(m_gameClearText);
	}
}

Map::~Map()
{
	delete[] m_basicTanks;
	delete[] m_lightBattleTanks;
	delete[] m_doubleBarrelTanks;
	delete[] m_destroyerTanks;
	delete[] m_fighterTanks;

	delete[] m_grassBlocks;
	delete[] m_brickBlocks;
	delete[] m_steelBlocks;
	delete[] m_waterBlocks;
	delete[] m_iceBlocks;
}