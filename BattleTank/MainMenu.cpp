#include "MainMenu.h"
#include "Math.h"

MainMenu::MainMenu(const Resource& resource, const sf::Vector2f mapSize):
	m_resource(resource),
	m_mapSize(mapSize),
	m_bird(sf::Vector2f(0.05, 0.05), sf::Vector2f(75, 75)),
	m_player1((sf::Vector2f(1, 1))),
	m_player2((sf::Vector2f(1, 1))),
	m_level1(resource, m_mapSize, m_player1, m_player2, m_bird),
	m_player1Mode(false),
	m_player2Mode(false),
	m_level1Play(false)
{
}

void MainMenu::Initialize(sf::RenderWindow& window)
{
	m_gameNameTopText.setString("Battle");
	m_gameNameTopText.setCharacterSize(150);
	m_gameNameTopText.setFillColor(sf::Color::White);
	m_gameNameTopText.setPosition((window.getSize().x - 560) / 2, 78);

	m_gameNameBottomText.setString("Tank");
	m_gameNameBottomText.setCharacterSize(150);
	m_gameNameBottomText.setFillColor(sf::Color::White);
	m_gameNameBottomText.setPosition((window.getSize().x - 389) / 2, 78 * 3);

	m_1playerText.setString("1 Player");
	m_1playerText.setPosition((window.getSize().x - 302) / 2, (window.getSize().y + 33) / 2);
	m_1playerText.setFillColor(sf::Color::White);
	m_1playerText.setCharacterSize(60);

	m_1playerTextClickBox.setSize(sf::Vector2f(274, 31));
	m_1playerTextClickBox.setPosition(m_1playerText.getPosition() + sf::Vector2f(0, 33));
	m_1playerTextClickBox.setFillColor(sf::Color::Transparent);
	m_1playerTextClickBox.setOutlineColor(sf::Color::White);
	m_1playerTextClickBox.setOutlineThickness(1);

	m_2playerText.setString("2 Player");
	m_2playerText.setPosition((window.getSize().x - 302) / 2, ((window.getSize().y + 33) / 2) + (33 * 2));
	m_2playerText.setFillColor(sf::Color::White);
	m_2playerText.setCharacterSize(60);;

	m_2playerTextClickBox.setSize(sf::Vector2f(302, 33));
	m_2playerTextClickBox.setPosition(m_2playerText.getPosition() + sf::Vector2f(0, 33));
	m_2playerTextClickBox.setFillColor(sf::Color::Transparent);
	m_2playerTextClickBox.setOutlineColor(sf::Color::White);
	m_2playerTextClickBox.setOutlineThickness(1);

	m_constructionText.setString("Construction");
	m_constructionText.setPosition((window.getSize().x - 302) / 2, ((window.getSize().y + 33) / 2) + (33 * 4));
	m_constructionText.setFillColor(sf::Color::White);
	m_constructionText.setCharacterSize(60);;

	m_constructionTextClickBox.setSize(sf::Vector2f(424, 31));
	m_constructionTextClickBox.setPosition(m_2playerText.getPosition() + sf::Vector2f(0, 33 * 3));
	m_constructionTextClickBox.setFillColor(sf::Color::Transparent);
	m_constructionTextClickBox.setOutlineColor(sf::Color::White);
	m_constructionTextClickBox.setOutlineThickness(1);

	m_player1.Initialize(
		&m_mapSize,
		window,
		sf::Vector2f(84, 84),
		sf::Vector2f(1.3, 1.3));

	m_player2.Initialize(
		&m_mapSize,
		window,
		sf::Vector2f(84, 84),
		sf::Vector2f(1.3, 1.3));

	m_bird.Initialize(&m_mapSize, window);

	m_level1.Initialize(window);
}

void MainMenu::Load()
{
	m_gameNameTopText.setFont(m_resource.gameFont);
	m_gameNameBottomText.setFont(m_resource.gameFont);

	m_1playerText.setFont(m_resource.gameFont);
	m_2playerText.setFont(m_resource.gameFont);
	m_constructionText.setFont(m_resource.gameFont);

	m_player1.Load(&m_resource.playertextureUp);
	m_player2.Load(&m_resource.playertextureUp);

	m_bird.Load(&m_resource.birdTexture);

	m_level1.Load();
}

void MainMenu::Update(sf::RenderWindow& window, float& deltatimeTimerMilli)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_level1Play == false) {

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (Math::TextClicked(mousePosition, m_1playerText)) {

			m_level1Play = true;
			m_player1Mode = true;
			m_level1.Player1ModeOrPlayer2Mode(m_player1Mode, m_player2Mode);
			m_level1.Player1AndPlayer2(m_player1, m_player2);
			m_level1.BaseBird(m_bird);
		}

		else if (Math::TextClicked(mousePosition, m_2playerText)) {

			m_level1Play = true;
			m_player2Mode = true;
			m_level1.Player1ModeOrPlayer2Mode(m_player1Mode, m_player2Mode);
			m_level1.Player1AndPlayer2(m_player1, m_player2);
			m_level1.BaseBird(m_bird);
		}
	}

	if (m_level1Play == true) {

		m_level1.Update(window, deltatimeTimerMilli);
	}
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	if (m_level1Play == false) {
		
		window.draw(m_gameNameTopText);
		window.draw(m_gameNameBottomText);

		window.draw(m_1playerText);
		window.draw(m_2playerText);
		window.draw(m_constructionText);

		window.draw(m_1playerTextClickBox);
		window.draw(m_2playerTextClickBox);
		window.draw(m_constructionTextClickBox);
	}

	if (m_level1Play == true) {

		m_level1.Draw(window);
	}
}

MainMenu::~MainMenu()
{
}