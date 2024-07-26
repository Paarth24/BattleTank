#pragma once
#include <SFML/Graphics.hpp>

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

public:

	MainMenu(sf::Vector2u& windowResolution);
	~MainMenu();

	void Initialize();
	void Load();
	void Update(const sf::Vector2i& mousePosition);
	void Draw(sf::RenderWindow& window);

private:

	bool MouseReleased();
	bool TextClicked(const sf::Vector2i& mousePosition, const sf::Text& text);

	void SetPlayer1Mode();
	void SetPlayer2Mode();
	void SetConstructorMode();
	void Exit();
};

