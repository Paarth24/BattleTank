#include "Level.h"

Level::Level(int totalBrickBlocks) :
	m_player1Mode(false),
	m_player2Mode(false),
	m_windowResolution(nullptr),
	m_mapBackgroundSize(sf::Vector2f(0, 0)),
	m_mapBackgroundPosition(sf::Vector2f(0, 0)),
	m_map(totalBrickBlocks)
{
}

void Level::SetPLayerMode(bool& player1Mode, bool& player2Mode)
{
	m_player1Mode = player1Mode;
	m_player2Mode = player2Mode;
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


void Level::Initialize(const sf::Vector2f* windowResolution)
{
	m_windowResolution = windowResolution;

	m_mainBackground.setSize(*m_windowResolution);
	m_mainBackground.setFillColor(sf::Color(211, 211, 211));

	m_mapBackgroundSize = sf::Vector2f(int(0.5417 * m_windowResolution->x), int(0.963 * m_windowResolution->y));
	m_mapBackgroundPosition = sf::Vector2f(
		(windowResolution->x - m_mapBackgroundSize.x) / 5,
		(windowResolution->y - m_mapBackgroundSize.y) / 2);

	m_mapBackground.setSize(m_mapBackgroundSize);
	m_mapBackground.setPosition(m_mapBackgroundPosition);
	m_mapBackground.setFillColor(sf::Color::Black);

	m_map.Initialize(&m_mapBackgroundSize, &m_mapBackgroundPosition);
}

void Level::Load()
{
	m_map.Load();
}

void Level::Update()
{
	if (m_player1Mode == true && m_player2Mode == false) {

		Player1ModeUpdate();
	}
	else if (m_player1Mode == false && m_player2Mode == true) {

		Player2ModeUpdate();
	}

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