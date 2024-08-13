#include "Level.h"

Level::Level(
	std::string levelId,
	int totalBasicTanks,
	int totalLightBattleTanks,
	int totalDoubleBarrelTanks,
	int totalDestroyerTanks,
	int totalFighterTanks,
	int totalGrassBlocks,
	int totalBrickBlocks,
	int totalSteelBlocks,
	int totalWaterBlocks,
	int totalIceBlocks) :
	m_levelID(levelId),
	m_player1Mode(false),
	m_player2Mode(false),
	m_windowResolution(nullptr),
	m_mapBackgroundSize(nullptr),
	m_mapBackgroundPosition(nullptr),
	m_blockOffset(nullptr),
	m_map(
		levelId,
		totalBasicTanks,
		totalLightBattleTanks,
		totalDoubleBarrelTanks,
		totalDestroyerTanks,
		totalFighterTanks,
		totalGrassBlocks,
		totalBrickBlocks,
		totalSteelBlocks,
		totalWaterBlocks,
		totalIceBlocks)
{
}

Level::Level():
	m_levelID(""),
	m_player1Mode(false),
	m_player2Mode(false),
	m_windowResolution(nullptr),
	m_mapBackgroundSize(nullptr),
	m_mapBackgroundPosition(nullptr),
	m_blockOffset(nullptr),
	m_map(m_levelID, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
{
}

void Level::SetPLayerMode(bool& player1Mode, bool& player2Mode)
{
	m_player1Mode = player1Mode;
	m_player2Mode = player2Mode;
	m_map.SetPLayerMode(player1Mode, player2Mode);
}

void Level::SetPlayer1(Player* player1)
{
	m_map.SetPlayer1(player1);
}

void Level::SetPlayer2(Player* player2)
{
	m_map.SetPlayer2(player2);
}

void Level::SetBase(Base& base)
{
	m_base = base;
	m_map.SetBase(m_base);
}

void Level::Restart()
{
	m_map.Restart();
}

bool Level::Completed()
{
	return m_map.Cleared();
}

void Level::Initialize(
	const sf::Vector2u* windowResolution,
	const sf::Vector2f* mapBackgroundSize,
	const sf::Vector2f* mapBackgroundPosition,
	const sf::Vector2f* blockOffset,
	int player1Lives,
	int player2Lives)
{
	m_windowResolution = windowResolution;
	m_mapBackgroundSize = mapBackgroundSize;
	m_mapBackgroundPosition = mapBackgroundPosition;

	m_blockOffset = blockOffset;

	m_mainBackground.setSize(sf::Vector2f(*m_windowResolution));
	m_mainBackground.setFillColor(sf::Color(105, 105, 105));

	m_mapBackground.setSize(*m_mapBackgroundSize);
	m_mapBackground.setPosition(*m_mapBackgroundPosition);
	m_mapBackground.setFillColor(sf::Color::Black);

	m_map.Initialize(m_mapBackgroundSize, m_mapBackgroundPosition, m_blockOffset);
	m_status.Initialize(
		m_windowResolution,
		m_mapBackgroundPosition,
		m_mapBackgroundSize,
		m_levelID,
		player1Lives,
		player2Lives,
		m_map.GetTotalEnemyTank());
}

void Level::Load(
	const sf::Font* gameFont,
	const sf::Vector2f * mapBackgroundPosition,
	const sf::Vector2f* mapBackgroundSize)
{
	m_map.Load(gameFont, mapBackgroundPosition, mapBackgroundSize);
	m_status.Load(gameFont, m_blockOffset);
}

void Level::Update(float deltaTimerMilli)
{
	m_map.Update(deltaTimerMilli);
	m_status.Update(m_map.GetRemainingEnemyTanks(), m_map.GetPlayer1Lives(), m_map.GetPlayer2Lives());
}

void Level::Draw(sf::RenderWindow& window)
{
	window.draw(m_mainBackground);
	window.draw(m_mapBackground);
	
	m_map.Draw(window);
	m_status.Draw(window, m_player2Mode);
}


Level::~Level()
{
}