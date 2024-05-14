#include "MainMenu.h"
#include "Math.h"

MainMenu::MainMenu(const Resource& resource):
	m_resource(resource),
	m_level1(resource)
{
}

void MainMenu::Initialize(const sf::RenderWindow& window)
{
	m_playText.setString("Play");
	m_playText.setPosition(0, (window.getSize().y / 4) - (m_playText.getGlobalBounds().height / 2));
	m_playText.setFillColor(sf::Color::White);
	m_playText.setCharacterSize(45);
	m_playText.setScale(sf::Vector2f(5, 5));

	
	m_exitGameText.setString("Exit");
	m_exitGameText.setPosition(0, 2*(window.getSize().y / 4) - (m_exitGameText.getGlobalBounds().height / 2));
	m_exitGameText.setFillColor(sf::Color::White);
	m_exitGameText.setCharacterSize(45);
	m_exitGameText.setScale(sf::Vector2f(5, 5));

	m_playTextClickBox.setSize(sf::Vector2f(570, 125));
	m_playTextClickBox.setPosition(m_playText.getPosition() + sf::Vector2f(5, 100));
	m_playTextClickBox.setFillColor(sf::Color::Transparent);
	m_playTextClickBox.setOutlineColor(sf::Color::Black);
	m_playTextClickBox.setOutlineThickness(1);


	m_exitGameTextClickBox.setSize(sf::Vector2f(500, 125));
	m_exitGameTextClickBox.setPosition(m_exitGameText.getPosition() + sf::Vector2f(5, 100));
	m_exitGameTextClickBox.setFillColor(sf::Color::Transparent);
	m_exitGameTextClickBox.setOutlineColor(sf::Color::Black);
	m_exitGameTextClickBox.setOutlineThickness(1);

	m_level1.Initialize(window);
}

void MainMenu::Load()
{
	m_playText.setFont(m_resource.gameFont);
	m_exitGameText.setFont(m_resource.gameFont);

	m_level1.Load();
}


void MainMenu::Update(sf::RenderWindow& window, float& deltatimeTimerMilli)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_level1Play == false) {

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (Math::TextClicked(mousePosition, m_playText)) {

			m_level1Play = true;
		}

		if (Math::TextClicked(mousePosition, m_exitGameText)) {

			window.close();
		}
	}

	if (m_level1Play == true) {

		m_level1.Update(window, deltatimeTimerMilli);
	}
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	if (m_level1Play == false) {

		window.draw(m_playText);
		window.draw(m_exitGameText);

		window.draw(m_playTextClickBox);
		window.draw(m_exitGameTextClickBox);
	}

	if (m_level1Play == true) {

		m_level1.Draw(window);
	}
}

MainMenu::~MainMenu()
{
}