#pragma once
#include "Level.h"

class MainMenu {

private:

	const sf::Vector2f m_windowResolution;

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

	Level m_level1;
	bool m_level1Play;

public:

	MainMenu(sf::Vector2u& windowResolution);
	~MainMenu();

	void Initialize();
	void Load();

	void Update(
		const sf::Vector2i& mousePosition,
		sf::RenderWindow& window);

	void Draw(sf::RenderWindow& window);

private:

	bool MouseReleased();
	bool TextClicked(const sf::Vector2i& mousePosition, const sf::Text& text);

	void SetPlayer1Mode();
	void SetPlayer2Mode();
	void SetConstructorMode();
	void Exit(sf::RenderWindow& window);
};

