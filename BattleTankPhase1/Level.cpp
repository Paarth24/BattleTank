#include "Level.h"

Level::Level(int totalBrickBlocks) :
	m_player1Mode(false),
	m_player2Mode(false),
	m_windowResolution(nullptr),
	m_mapBackgroundSize(nullptr),
	m_mapBackgroundPosition(nullptr),
	m_map(totalBrickBlocks)
{
}

void Level::SetPLayerMode(bool& player1Mode, bool& player2Mode)
{
	m_player1Mode = player1Mode;
	m_player2Mode = player2Mode;
	m_map.SetPLayerMode(player1Mode, player2Mode);
}

void Level::SetPlayer1(Player& player1)
{
	m_player1 = player1;
	m_map.SetPlayer1(m_player1);
}

void Level::SetPlayer2(Player& player2)
{
	m_player2 = player2;
	m_map.SetPlayer2(m_player2);
}

void Level::Player1ModeUpdate()
{
}

void Level::Player2ModeUpdate()
{
}

void Level::Lost()
{
}

void Level::Completed()
{
}

void Level::Exit()
{
}


void Level::Initialize(const sf::Vector2f* windowResolution, const sf::Vector2f* mapBackgroundSize, const sf::Vector2f* mapBackgroundPosition)
{
	m_windowResolution = windowResolution;
	m_mapBackgroundSize = mapBackgroundSize;
	m_mapBackgroundPosition = mapBackgroundPosition;

	m_mainBackground.setSize(*m_windowResolution);
	m_mainBackground.setFillColor(sf::Color(211, 211, 211));

	m_mapBackground.setSize(*m_mapBackgroundSize);
	m_mapBackground.setPosition(*m_mapBackgroundPosition);
	m_mapBackground.setFillColor(sf::Color::Black);

	m_map.Initialize(m_mapBackgroundSize, m_mapBackgroundPosition);
}

void Level::Load()
{
	m_map.Load();
}

void Level::Update()
{
	m_map.Update();
}

void Level::Draw(sf::RenderWindow& window)
{
	window.draw(m_mainBackground);
	window.draw(m_mapBackground);
	
	m_map.Draw(window);
}


Level::~Level()
{
}