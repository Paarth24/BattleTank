#pragma once
#include "Level.h"

#include <map>

class MainMenu {

private:

	const sf::Vector2u m_windowResolution;
	sf::Vector2f m_mapBackgroundSize;
	sf::Vector2f m_mapBackgroundPosition;

	sf::Vector2f m_blockOffset;
	sf::Vector2i m_gridRowColumn;

	bool m_mousePressed;
	bool m_mouseReleased;

	sf::Font m_gameFont;

	sf::Text m_titleText;
	sf::Text m_player1ModeText;	
	sf::Text m_player2ModeText;
	sf::Text m_constructorModeText;
	sf::Text m_exitText;

	bool m_player1Mode;
	bool m_player2Mode;
	bool m_constructionMode;

	Player m_player1;
	Player m_player2;

	bool m_levelPlay;
	int m_currentLevel;

	Level* m_levels;
	int m_totalLevels;

	Base m_base;

public:

	MainMenu(sf::Vector2u& windowResolution);
	~MainMenu();

	void Initialize();
	void Load();

	void Update(
		const sf::Vector2i& mousePosition,
		float deltaTimerMilli,
		sf::RenderWindow& window);

	void Draw(sf::RenderWindow& window);

private:

	void GettingKey(std::string& string, std::string& key, std::string& val);
	int StringToInt(std::string& string);

	bool MouseReleased();
	bool TextClicked(const sf::Vector2i& mousePosition, const sf::Text& text);

	void SetPlayer1Mode();
	void SetPlayer2Mode();
	void SetConstructorMode();
	void Exit(sf::RenderWindow& window);

	void Restart();
};

