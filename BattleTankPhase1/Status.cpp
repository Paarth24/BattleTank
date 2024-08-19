#include "Status.h"

#include <iostream>

Status::Status():
	m_totalEnemyTanks(0),
	m_windowResolution(nullptr),
	m_mapBackgroundPosition(nullptr),
	m_mapBackgroundSize(nullptr),
	m_enemyTankSymbols(nullptr),
	m_player1Lives(0),
	m_player2Lives(0)
{
}

void Status::InitializeEnemyTankSymbol()
{
	for (int i = 0; i < m_totalEnemyTanks; ++i) {

		m_enemyTankSymbols[i].setColor(sf::Color::Black);
	}
}

void Status::LoadEnemyTankSymbol(const sf::Vector2f* blockOffset)
{
	sf::Vector2f position = sf::Vector2f(
		(m_windowResolution->x + m_mapBackgroundPosition->x + m_mapBackgroundSize->x) / 2,
		m_mapBackgroundPosition->y);

	for (int i = 0; i < m_totalEnemyTanks; ++i) {

		m_enemyTankSymbols[i].setTexture(m_enemyTankSymbolTexture);

		m_enemyTankSymbols[i].setScale(sf::Vector2f(
			1.1 * blockOffset->y / (2 * m_enemyTankSymbolTexture.getSize().x),
			1.1 * blockOffset->x / m_enemyTankSymbolTexture.getSize().y));

		m_enemyTankSymbols[i].setPosition(sf::Vector2f(
			(i % 5) * 2 * m_enemyTankSymbols[i].getGlobalBounds().width + position.x - (9 * m_enemyTankSymbols[i].getGlobalBounds().width / 2),
			(i / 5) * m_enemyTankSymbols[i].getGlobalBounds().height + position.y));
	}
}

void Status::DrawEnemyTankSymbol(sf::RenderWindow& window)
{
	for (int i = 0; i < m_totalEnemyTanks; ++i) {

		window.draw(m_enemyTankSymbols[i]);
	}
}

void Status::Initialize(
	const sf::Vector2u* windowResolution,
	const sf::Vector2f* mapBackgroundPosition,
	const sf::Vector2f* mapBackgroundSize,
	std::string& levelID,
	int player1Lives,
	int player2Lives,
	int totalEnemyTanks)
{
	m_windowResolution = windowResolution;
	m_mapBackgroundPosition = mapBackgroundPosition;
	m_mapBackgroundSize = mapBackgroundSize;
	m_totalEnemyTanks = totalEnemyTanks;

	m_enemyTankSymbols = new sf::Sprite[m_totalEnemyTanks];

	InitializeEnemyTankSymbol();

	m_player1Lives = player1Lives;
	m_player2Lives = player2Lives;

	m_player1IdText.setString("1 P");
	m_player1IdText.setFillColor(sf::Color::Black);
	m_player1IdText.setCharacterSize(m_mapBackgroundSize->x / 20);

	m_player1LivesText.setString("-" + std::to_string(m_player1Lives));
	m_player1LivesText.setFillColor(sf::Color::Black);
	m_player1LivesText.setCharacterSize(m_mapBackgroundSize->x / 20);

	m_player2IdText.setString("2 P");
	m_player2IdText.setFillColor(sf::Color::Black);
	m_player2IdText.setCharacterSize(m_mapBackgroundSize->x / 20);

	m_player2LivesText.setString("-" + std::to_string(m_player2Lives));
	m_player2LivesText.setFillColor(sf::Color::Black);
	m_player2LivesText.setCharacterSize(m_mapBackgroundSize->x / 20);

	std::string levelNumber;

	for (int i = 0; i < levelID.size(); ++i) {

		char c = levelID[i];

		if (c == '0' ||
			c == '1' ||
			c == '2' ||
			c == '3' ||
			c == '4' ||
			c == '5' ||
			c == '6' ||
			c == '7' ||
			c == '8' ||
			c == '9') {

			levelNumber = levelNumber + c;
		}
	}

	m_levelIdText.setString(levelNumber);
	m_levelIdText.setFillColor(sf::Color::Black);
	m_levelIdText.setCharacterSize(m_mapBackgroundSize->x / 20);
}

void Status::Load(const sf::Font* gameFont, const sf::Vector2f* blockOffset)
{
	if (m_enemyTankSymbolTexture.loadFromFile("enemyup.png")) {

		std::cout << "Enemy tank symbol loaded successfully" << std::endl;

		LoadEnemyTankSymbol(blockOffset);
	}

	m_player1IdText.setFont(*gameFont);
	m_player1IdText.setPosition(sf::Vector2f(
		(m_windowResolution->x + m_mapBackgroundPosition->x + m_mapBackgroundSize->x - m_player1IdText.getGlobalBounds().width) / 2,
		m_mapBackgroundPosition->y + (m_mapBackgroundSize->y / 2)));
	
	if (m_player1LivesTexture.loadFromFile("player1up.png")) {

		m_player1LivesSprite.setTexture(m_player1LivesTexture);

		m_player1LivesSprite.setScale(sf::Vector2f(
			1.5 * m_player1IdText.getGlobalBounds().width / (m_player1LivesTexture.getSize().x * 3),
			1.5 * m_player1IdText.getGlobalBounds().height / m_player1LivesTexture.getSize().y));

		m_player1LivesSprite.setPosition(sf::Vector2f(
			((m_windowResolution->x + m_mapBackgroundPosition->x + m_mapBackgroundSize->x - m_player1IdText.getGlobalBounds().width - m_player1LivesSprite.getGlobalBounds().width) / 2),
			m_mapBackgroundPosition->y + (m_mapBackgroundSize->y / 2) + (2 * m_player1IdText.getGlobalBounds().height)));
	}

	m_player1LivesText.setFont(*gameFont);
	m_player1LivesText.setPosition(sf::Vector2f(
		(m_windowResolution->x + m_mapBackgroundPosition->x + m_mapBackgroundSize->x - m_player1IdText.getGlobalBounds().width + m_player1LivesSprite.getGlobalBounds().width) / 2,
		m_mapBackgroundPosition->y + (m_mapBackgroundSize->y / 2) + (1.5 * m_player1IdText.getGlobalBounds().height)));
	
	m_player2IdText.setFont(*gameFont);
	m_player2IdText.setPosition(sf::Vector2f(
		(m_windowResolution->x + m_mapBackgroundPosition->x + m_mapBackgroundSize->x - m_player2IdText.getGlobalBounds().width) / 2,
		m_mapBackgroundPosition->y + (m_mapBackgroundSize->y / 2) + (5 * m_player2IdText.getGlobalBounds().height)));

	if (m_player2LivesTexture.loadFromFile("player2up.png")) {

		m_player2LivesSprite.setTexture(m_player2LivesTexture);

		m_player2LivesSprite.setScale(sf::Vector2f(
			1.5 * m_player1IdText.getGlobalBounds().width / (m_player1LivesTexture.getSize().x * 3),
			1.5 * m_player1IdText.getGlobalBounds().height / m_player1LivesTexture.getSize().y));

		m_player2LivesSprite.setPosition(sf::Vector2f(
			((m_windowResolution->x + m_mapBackgroundPosition->x + m_mapBackgroundSize->x - m_player1IdText.getGlobalBounds().width - m_player1LivesSprite.getGlobalBounds().width) / 2),
			m_mapBackgroundPosition->y + (m_mapBackgroundSize->y / 2) + (7 * m_player2IdText.getGlobalBounds().height)));
	}

	m_player2LivesText.setFont(*gameFont);
	m_player2LivesText.setPosition(sf::Vector2f(
		(m_windowResolution->x + m_mapBackgroundPosition->x + m_mapBackgroundSize->x - m_player1IdText.getGlobalBounds().width + m_player1LivesSprite.getGlobalBounds().width) / 2,
		m_mapBackgroundPosition->y + (m_mapBackgroundSize->y / 2) + (6.5 * m_player2IdText.getGlobalBounds().height)));

	
	if (m_levelNumberTexture.loadFromFile("levelNumberFlag.png")) {

		m_levelNumberSprite.setTexture(m_levelNumberTexture);

		m_levelNumberSprite.setScale(sf::Vector2f(
			1.5 * m_player1IdText.getGlobalBounds().width / (m_levelNumberTexture.getSize().x * 3),
			1.5 * m_player1IdText.getGlobalBounds().height / m_levelNumberTexture.getSize().y));
		
		m_levelNumberSprite.setPosition(sf::Vector2f(
			((m_windowResolution->x + m_mapBackgroundPosition->x + m_mapBackgroundSize->x - m_player1IdText.getGlobalBounds().width) / 2),
			m_mapBackgroundPosition->y + m_mapBackgroundSize->y - (1.1 * m_levelNumberSprite.getGlobalBounds().height)));
	}

	m_levelIdText.setFont(*gameFont);
	m_levelIdText.setPosition(sf::Vector2f(
		(((m_windowResolution->x + m_mapBackgroundPosition->x + m_mapBackgroundSize->x - m_player1IdText.getGlobalBounds().width) / 2) + m_levelNumberSprite.getGlobalBounds().width),
		m_mapBackgroundPosition->y + m_mapBackgroundSize->y - (2 * m_levelIdText.getGlobalBounds().height)));
}

void Status::Update(int remainingEnemies, int remainingPlayer1Lives, int remainingPlayer2Lives)
{
	m_totalEnemyTanks = remainingEnemies;

	m_player1Lives = remainingPlayer1Lives;
	m_player2Lives = remainingPlayer2Lives;

	m_player1LivesText.setString("-" + std::to_string(m_player1Lives));
	m_player2LivesText.setString("-" + std::to_string(m_player2Lives));
}

void Status::Draw(sf::RenderWindow& window, bool player2Mode)
{
	DrawEnemyTankSymbol(window);

	window.draw(m_player1IdText);
	window.draw(m_player1LivesSprite);
	window.draw(m_player1LivesText);

	if (player2Mode) {

		window.draw(m_player2IdText);
		window.draw(m_player2LivesSprite);
		window.draw(m_player2LivesText);
	}

	window.draw(m_levelNumberSprite);
	window.draw(m_levelIdText);
}

Status::~Status()
{
	delete[] m_enemyTankSymbols;
}