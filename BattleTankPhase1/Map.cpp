#include <fstream>
#include <iostream>

#include "Map.h"

Map::Map(int& totalBrickBlocks):
	m_gridRowColumn(sf::Vector2i(26, 13)),
	m_grid(m_gridRowColumn),
	m_mapBackgroundSize(nullptr),
	m_mapBackgroundPosition(nullptr),
	m_player1Mode(false),
	m_player2Mode(false),
	m_totalBrickBlocks(totalBrickBlocks),
	m_brickBlocks(nullptr)
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

bool Map::BoundaryCollision(const sf::Sprite& sprite, const std::string& direction)
{
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

bool Map::SpriteCollision(
	const sf::Sprite& sprite1,
	const sf::Sprite& sprite2,
	const std::string& direction,
	const sf::Vector2f& movementSpeed)
{
	sf::FloatRect sprite1Global = sprite1.getGlobalBounds();
	sf::FloatRect sprite2Global = sprite2.getGlobalBounds();

	sf::Vector2f sprite1Position = sprite1.getPosition();
	sf::Vector2f sprite2Position = sprite2.getPosition();

	if (direction == "up") {

		if (sprite1Global.left < sprite2Global.left + sprite2Global.width && sprite1Global.left + sprite1Global.width > sprite2Global.left &&
			sprite1Position.y - movementSpeed.y <= sprite2Position.y + sprite2Global.height && sprite1Position.y >= sprite2Position.y) {

			return true;
		}
		else {

			return false;
		}
	}
	else if (direction == "left") {

		if (sprite1Position.x - movementSpeed.x <= sprite2Position.x + sprite2Global.width && sprite1Position.x >= sprite2Position.x &&
			sprite1Global.top < sprite2Global.top + sprite2Global.height && sprite1Global.top + sprite1Global.height > sprite2Global.top) {

			return true;
		}
		else {

			return false;
		}
	}
	else if (direction == "down") {

		if (sprite1Global.left < sprite2Global.left + sprite2Global.width && sprite1Global.left + sprite1Global.width > sprite2Global.left &&
			sprite1Position.y + sprite1Global.height + movementSpeed.y >= sprite2Position.y && sprite1Position.y <= sprite2Position.y) {

			return true;
		}
		else {

			return false;
		}
	}
	else if (direction == "right") {

		if (sprite1Position.x + sprite1Global.width + movementSpeed.x >= sprite2Position.x && sprite1Position.x <= sprite2Position.x &&
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

void Map::InitializeGrassBlocks()
{
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
}

void Map::InitializeWaterBlocks()
{
}

void Map::InitializeIceBlocks()
{
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

void Map::Player1ModeUpdate()
{
	bool collision = false;

	if (m_player1Mode == false && m_player2Mode == true) {

	//-----------------------------Checking if Player1 Collided With Player2-----------------------------
		if (SpriteCollision(m_player1.GetSprite(), m_player2.GetSprite(), m_player1.GetDirection(), m_player1.GetMovementSpeed())) {

			collision = true;

		}
	//-----------------------------Checking if Player1 Collided With Player2-----------------------------
	}

	//-----------------------------Checking if Player1 Collided With Map Boundary-----------------------------
	if (BoundaryCollision(m_player1.GetSprite(), m_player1.GetDirection()) && !collision) {

		collision = true;
	}
	//-----------------------------Checking if Player1 Collided With Map Boundary-----------------------------
	
	//-----------------------------Checking if Player1 Collided With Brick Block-----------------------------
	else if (!collision) {

		for (int i = 0; i < m_totalBrickBlocks; ++i) {
				
			if (!m_brickBlocks[i].GetCheckDestroy()) {

				if (SpriteCollision(m_player1.GetSprite(), m_brickBlocks[i].GetSprite(), m_player1.GetDirection(), m_player1.GetMovementSpeed())) {

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
	if (SpriteCollision(m_player2.GetSprite(), m_player1.GetSprite(), m_player2.GetDirection(), m_player2.GetMovementSpeed())) {

		collision = true;
	}
	//-----------------------------Checking if Player2 Collided Player1-----------------------------

	//-----------------------------Checking if Player2 Collided With Map Boundary-----------------------------
	if (BoundaryCollision(m_player2.GetSprite(), m_player2.GetDirection()) && !collision) {

		collision = true;
	}
	//-----------------------------Checking if Player2 Collided With Map Boundary-----------------------------
	
	//-----------------------------Checking if Player2 Collided With Brick Block-----------------------------
	else if (!collision) {

		for (int i = 0; i < m_totalBrickBlocks; ++i) {

			if (!m_brickBlocks[i].GetCheckDestroy()) {

				if (SpriteCollision(m_player2.GetSprite(), m_brickBlocks[i].GetSprite(), m_player2.GetDirection(), m_player2.GetMovementSpeed())) {

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
		if (BoundaryCollision(bullet.GetSprite(), bullet.GetDirection())) {

			collision = true;
		}
	//-----------------------------Checking if Player Normal Bullet Collided With Map Boundary-----------------------------
		
	//-----------------------------Checking if Player Normal Bullet Collided With Brick Block-----------------------------
		else if (!collision) {

			for (int j = 0; j < m_totalBrickBlocks; ++j) {

				if (!m_brickBlocks[j].GetCheckDestroy()) {

					if (SpriteCollision(bullet.GetSprite(), m_brickBlocks[j].GetSprite(), bullet.GetDirection(), bullet.GetMovementSpeed())) {

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

		if (collision) {

			m_playerNormalBulletVector.erase(m_playerNormalBulletVector.begin() + i);
		}
	}

	for (size_t i = 0; i < m_playerArmourBulletVector.size(); ++i) {

		bool collision = false;

		Bullet bullet = m_playerArmourBulletVector[i];

	//-----------------------------Checking if Player Armour Bullet Collided With Map Boundary-----------------------------
		if (BoundaryCollision(bullet.GetSprite(), bullet.GetDirection())) {

			collision = true;
			m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);
		}
	//-----------------------------Checking if Player Armour Bullet Collided With Map Boundary-----------------------------

	//-----------------------------Checking if Player Armour Bullet Collided With Brick Block-----------------------------
		else if (!collision) {

			for (int j = 0; j < m_totalBrickBlocks; ++j) {

				if (!m_brickBlocks[j].GetCheckDestroy()) {

					if (SpriteCollision(bullet.GetSprite(), m_brickBlocks[j].GetSprite(), bullet.GetDirection(), bullet.GetMovementSpeed())) {

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
		
		if (collision) {

			m_playerArmourBulletVector.erase(m_playerArmourBulletVector.begin() + i);
		}
	}
}

void Map::EnemyBulletUpdate() 
{
	for (size_t i = 0; i < m_enemyNormalBulletVector.size(); ++i) {

		if (BoundaryCollision(m_enemyNormalBulletVector[i].GetSprite(), m_enemyNormalBulletVector[i].GetDirection())) {

			m_enemyNormalBulletVector.erase(m_enemyNormalBulletVector.begin() + i);
		}
	}

	for (size_t i = 0; i < m_enemyArmourBulletVector.size(); ++i) {

		if (BoundaryCollision(m_enemyArmourBulletVector[i].GetSprite(), m_enemyArmourBulletVector[i].GetDirection())) {

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

void Map::Update(float deltaTimerMilli)
{
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

void Map::Draw(sf::RenderWindow& window)
{
	m_grid.Draw(window);

	DrawGrassBlocks(window);
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
}

Map::~Map()
{
	delete[] m_brickBlocks;
}