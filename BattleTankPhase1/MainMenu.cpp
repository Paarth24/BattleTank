#include <iostream>
#include <fstream>
#include <cmath>

#include "MainMenu.h"

MainMenu::MainMenu(sf::Vector2u& windowResolution):
	m_windowResolution(windowResolution),
	m_blockOffset(sf::Vector2f(0, 0)),
	m_gridRowColumn(26, 13),
	m_mousePressed(false),
	m_mouseReleased(false),
	m_player1Mode(false),
	m_player2Mode(false),
	m_constructionMode(false),
	m_levels(nullptr),
	m_levelPlay(false),
	m_currentLevel(-1),
	m_totalLevels(2)
{
}


void MainMenu::GettingKey(std::string& line, std::string& key, std::string& val)
{
	int count = 0;

	for (int i = 0; i < line.size(); ++i) {

		if (line[i] == '[' || line[i] == ']') {

			++count;
		}
		else if (count != 2) {

			key = key + line[i];
		}
		else if (count == 2 && line[i] != '=') {

			val = val + line[i];
		}
	}
}

int MainMenu::StringToInt(std::string& string)
{
	int val = 0;

	for (int i = 0; i < string.size(); ++i) {

		val = val + (int(string[i] - '0') * std::pow(10, string.size() - (i + 1)));
	}

	return val;
}

bool MainMenu::MouseReleased()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		m_mousePressed = true;
	}
	else if (m_mousePressed == true) {

		m_mouseReleased = true;
		m_mousePressed = false;
	}
	else{

		m_mouseReleased = false;
	}
	return m_mouseReleased;
}

bool MainMenu::TextClicked(const sf::Vector2i& mousePosition, const sf::Text& text)
{
	sf::Vector2f textSize = sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height);
	sf::Vector2f textPosition = text.getPosition();

	if (mousePosition.x >= textPosition.x && mousePosition.x <= textPosition.x + textSize.x &&
		mousePosition.y >= textPosition.y + textSize.y && mousePosition.y <= textPosition.y + textSize.y + textSize.y) {

		return true;
	}
	else {

		return false;
	}
}

void MainMenu::SetPlayer1Mode()
{
	std::cout << "Player 1 mode set" << std::endl;

	m_player1.Initialize(1, &m_mapBackgroundPosition, &m_blockOffset);
	m_player2.Initialize(1, &m_mapBackgroundPosition, &m_blockOffset);

	m_player1Mode = true;
	m_player2Mode = false;
	m_constructionMode = false;

	m_levelPlay = true;

	for (int i = 0; i < m_totalLevels; ++i) {

		m_levels[i].SetPLayerMode(m_player1Mode, m_player2Mode);
	}

	m_player1.Load();

	m_levels[m_currentLevel].SetPlayer1(&m_player1);
	m_levels[m_currentLevel].SetPlayer2(&m_player1);
}

void MainMenu::SetPlayer2Mode()
{
	std::cout << "Player 2 mode set" << std::endl;

	m_player1.Initialize(1, &m_mapBackgroundPosition, &m_blockOffset);
	m_player2.Initialize(2, &m_mapBackgroundPosition, &m_blockOffset);

	m_player1Mode = false;
	m_player2Mode = true;
	m_constructionMode = false;

	m_levelPlay = true;
	for (int i = 0; i < m_totalLevels; ++i) {

		m_levels[i].SetPLayerMode(m_player1Mode, m_player2Mode);
	}

	m_player1.Load();
	m_player2.Load();

	m_levels[m_currentLevel].SetPlayer1(&m_player1);
	m_levels[m_currentLevel].SetPlayer2(&m_player2);
}

void MainMenu::SetConstructorMode()
{
	std::cout << "Construction mode set" << std::endl;

	m_player1Mode = false;
	m_player2Mode = false;
	m_constructionMode = true;
}

void MainMenu::Exit(sf::RenderWindow& window)
{
	std::cout << "exit" << std::endl;

	window.close();
}

void MainMenu::Restart()
{
	m_player1Mode = false;
	m_player2Mode = false;

	m_currentLevel = 0;

	m_player1.Initialize(1, &m_mapBackgroundPosition, &m_blockOffset);
	m_player2.Initialize(2, &m_mapBackgroundPosition, &m_blockOffset);

	m_base.Initialize(&m_mapBackgroundPosition, &m_mapBackgroundSize, &m_blockOffset);

	m_levels[m_currentLevel].Initialize(
		&m_windowResolution,
		&m_mapBackgroundSize,
		&m_mapBackgroundPosition,
		&m_blockOffset,
		m_player1.GetLives(),
		m_player2.GetLives());

	m_levels[m_currentLevel].Load(&m_gameFont, &m_mapBackgroundPosition, &m_mapBackgroundSize);

	m_base.Load(&m_gameFont, &m_mapBackgroundPosition, &m_mapBackgroundSize);

	m_levels[m_currentLevel].SetBase(m_base);

	for (int i = 0; i < m_totalLevels; ++i) {

		m_levels[i].Restart();
	}
}

void MainMenu::Initialize()
{
	m_titleText.setCharacterSize(m_windowResolution.y / 5);
	m_titleText.setString("Battle Tank");

	m_player1ModeText.setCharacterSize(m_windowResolution.y / 10);
	m_player1ModeText.setString("Player 1");

	m_player2ModeText.setCharacterSize(m_windowResolution.y / 10);
	m_player2ModeText.setString("Player 2");

	m_constructorModeText.setCharacterSize(m_windowResolution.y / 10);
	m_constructorModeText.setString("Construction");

	m_exitText.setCharacterSize(m_windowResolution.y / 10);
	m_exitText.setString("Exit");

	m_mapBackgroundSize = sf::Vector2f(int(0.5417 * m_windowResolution.x), int(0.963 * m_windowResolution.y));
	m_mapBackgroundPosition = sf::Vector2f(
		(m_windowResolution.x - m_mapBackgroundSize.x) / 5,
		(m_windowResolution.y - m_mapBackgroundSize.y) / 2);

	m_blockOffset = sf::Vector2f(
		m_mapBackgroundSize.x / m_gridRowColumn.x,
		m_mapBackgroundSize.y / m_gridRowColumn.y);


	m_base.Initialize(&m_mapBackgroundPosition, &m_mapBackgroundSize, &m_blockOffset);

	m_levels = new Level[m_totalLevels];
	m_currentLevel = 0;

	std::ifstream file;

	for (int i = 0; i < m_totalLevels; ++i) {

		file.open("level" + std::to_string(i + 1) + "MapData.rmap");

		std::string levelId;
		std::string totalBasicTanks;
		std::string totalLightBattleTanks;
		std::string totalDoubleBarrelTanks;
		std::string totalDestroyerTanks;
		std::string totalFighterTanks;
		std::string totalGrassBlocks;
		std::string totalBrickBlocks;
		std::string totalSteelBlocks;
		std::string totalWaterBlocks;
		std::string totalIceBlocks;

		if (file.is_open()) {

			std::string line;

			for (int j = 0; j < 11; ++j) {

				file >> line;

				std::string key;
				std::string val;

				GettingKey(line, key, val);

				if (key == "levelId") {

					levelId = val;
				}
				else if (key == "totalBasicTanks") {

					totalBasicTanks = val;
				}
				else if (key == "totalLightBattleTanks") {

					totalLightBattleTanks = val;
				}
				else if (key == "totalDoubleBarrelTanks") {

					totalDoubleBarrelTanks = val;
				}
				else if (key == "totalDestroyerTanks") {

					totalDestroyerTanks = val;
				}
				else if (key == "totalFighterTanks") {

					totalFighterTanks = val;
				}
				else if (key == "totalGrassBlocks") {

					totalGrassBlocks = val;
				}
				else if (key == "totalBrickBlocks") {

					totalBrickBlocks = val;
				}
				else if (key == "totalSteelBlocks") {

					totalSteelBlocks = val;
				}
				else if (key == "totalWaterBlocks") {

					totalWaterBlocks = val;
				}
				else if (key == "totalIceBlocks") {

					totalIceBlocks = val;
				}
			}

			file.close();
		}

		m_levels[i] = Level(levelId,
			StringToInt(totalBasicTanks),
			StringToInt(totalLightBattleTanks),
			StringToInt(totalDoubleBarrelTanks),
			StringToInt(totalDestroyerTanks),
			StringToInt(totalFighterTanks),
			StringToInt(totalGrassBlocks),
			StringToInt(totalBrickBlocks),
			StringToInt(totalSteelBlocks),
			StringToInt(totalWaterBlocks),
			StringToInt(totalIceBlocks));
	}

	m_levels[m_currentLevel].Initialize(
		&m_windowResolution,
		&m_mapBackgroundSize,
		&m_mapBackgroundPosition,
		&m_blockOffset,
		m_player1.GetLives(),
		m_player2.GetLives());
}

void MainMenu::Load()
{
	if (m_gameFont.loadFromFile("gameFont.ttf")) {

		std::cout << "Game font loaded successfully" << std::endl;

		m_titleText.setFont(m_gameFont);
		m_titleText.setPosition(sf::Vector2f((m_windowResolution.x - m_titleText.getGlobalBounds().width) / 2, 0));

		m_player1ModeText.setFont(m_gameFont);
		m_player1ModeText.setPosition(sf::Vector2f(
			(m_windowResolution.x - m_player1ModeText.getGlobalBounds().width) / 2,
			(m_windowResolution.y - m_player1ModeText.getGlobalBounds().height) / 2));

		m_player2ModeText.setFont(m_gameFont);
		m_player2ModeText.setPosition(sf::Vector2f(
			(m_windowResolution.x - m_player2ModeText.getGlobalBounds().width) / 2,
			((m_windowResolution.y - m_player2ModeText.getGlobalBounds().height) / 2) + 2 * m_player1ModeText.getGlobalBounds().height));

		m_constructorModeText.setFont(m_gameFont);
		m_constructorModeText.setPosition(sf::Vector2f(
			(m_windowResolution.x - m_constructorModeText.getGlobalBounds().width) / 2,
			((m_windowResolution.y - m_constructorModeText.getGlobalBounds().height) / 2) +
			2 * (m_player1ModeText.getGlobalBounds().height + m_player2ModeText.getGlobalBounds().height)));

		m_exitText.setFont(m_gameFont);
		m_exitText.setPosition(sf::Vector2f(
			(m_windowResolution.x - m_exitText.getGlobalBounds().width) / 2,
			((m_windowResolution.y - m_exitText.getGlobalBounds().height) / 2) +
			2 * (m_player1ModeText.getGlobalBounds().height + m_player2ModeText.getGlobalBounds().height + m_constructorModeText.getGlobalBounds().height)));
	}

	m_levels[m_currentLevel].Load(&m_gameFont, &m_mapBackgroundPosition, &m_mapBackgroundSize);

	m_base.Load(&m_gameFont, &m_mapBackgroundPosition, &m_mapBackgroundSize);

	m_levels[m_currentLevel].SetBase(m_base);
}

void MainMenu::Update(
	const sf::Vector2i& mousePosition,
	float deltaTimerMilli,
	sf::RenderWindow& window)
{
	if (m_player1Mode == false && m_player2Mode == false && m_constructionMode == false) {

		if (MouseReleased()) {

			if (TextClicked(mousePosition, m_player1ModeText)) {

				SetPlayer1Mode();
			}

			else if (TextClicked(mousePosition, m_player2ModeText)) {

				SetPlayer2Mode();
			}

			else if (TextClicked(mousePosition, m_constructorModeText)) {

				SetConstructorMode();
			}

			else if (TextClicked(mousePosition, m_exitText)) {

				Exit(window);
			}
		}
	}

	else if (m_player1Mode == true || m_player2Mode == true) {

		m_levels[m_currentLevel].Update(deltaTimerMilli);
	}

	if (m_levels[m_currentLevel].Completed()) {

		++m_currentLevel;

		if (m_currentLevel >= m_totalLevels) {

			Restart();
		}
		else {

			m_player1.NextLevel();
			m_player2.NextLevel();

			m_levels[m_currentLevel].SetPlayer1(&m_player1);
			m_levels[m_currentLevel].SetPlayer2(&m_player2);

			m_levels[m_currentLevel].Initialize(
				&m_windowResolution,
				&m_mapBackgroundSize,
				&m_mapBackgroundPosition,
				&m_blockOffset,
				m_player1.GetLives(),
				m_player2.GetLives());

			m_levels[m_currentLevel].Load(&m_gameFont, &m_mapBackgroundPosition, &m_mapBackgroundSize);

			m_levels[m_currentLevel].SetBase(m_base);
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

		Restart();
	}
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	if (m_player1Mode == false && m_player2Mode == false && m_constructionMode == false) {

		window.draw(m_titleText);
		window.draw(m_player1ModeText);
		window.draw(m_player2ModeText);	
		window.draw(m_constructorModeText);
		window.draw(m_exitText);
	}
	else if(m_levelPlay == true) {

		m_levels[m_currentLevel].Draw(window);
	}
}

MainMenu::~MainMenu()
{
}