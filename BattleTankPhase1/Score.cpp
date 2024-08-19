#include "Score.h"

Score::Score():
	m_windowResolution(nullptr),
	m_basicTankKilled(0),
	m_lightBattleKilled(0),
	m_doubleBarrelTankKilled(0),
	m_destroyerTankKilled(0),
	m_fighterTankKilled(0)
{
}

void Score::Initialize(const sf::Vector2u* windowResolution)
{
	m_windowResolution = windowResolution;

	m_lightBattleTankSprite.setColor(sf::Color::Cyan);
	m_doubleBarrelTankSprite.setColor(sf::Color(226, 210, 50));
	m_destroyerTankSprite.setColor(sf::Color(70, 137, 151));
	m_fighterTankSprite.setColor(sf::Color::Magenta);
}

void Score::Load(const sf::Font* gamefont)
{
	if (m_enemyTankTexture.loadFromFile("enemyup.png")) {

		m_basicTankScore.setFont(*gamefont);
		m_basicTankScore.setCharacterSize(m_windowResolution->y / 10);
		m_basicTankScore.setString(" - " + std::to_string(m_basicTankKilled));
		m_basicTankScore.setPosition(sf::Vector2f(
			(m_windowResolution->x - (0.5 * m_basicTankScore.getGlobalBounds().width)) / 2,
			0));

		m_basicTankSprite.setTexture(m_enemyTankTexture);
		m_basicTankSprite.setScale(sf::Vector2f(
			m_windowResolution->y / (10 * m_enemyTankTexture.getSize().y),
			m_windowResolution->y / (10 * m_enemyTankTexture.getSize().y)));
		m_basicTankSprite.setPosition(sf::Vector2f(
			m_basicTankScore.getPosition().x - m_basicTankSprite.getGlobalBounds().width,
			m_basicTankScore.getPosition().y));

		m_lightBattleTankScore.setFont(*gamefont);
		m_lightBattleTankScore.setCharacterSize(m_windowResolution->y / 10);
		m_lightBattleTankScore.setString(" - " + std::to_string(m_lightBattleKilled));
		m_lightBattleTankScore.setPosition(sf::Vector2f(
			(m_windowResolution->x - (0.5 * m_lightBattleTankScore.getGlobalBounds().width)) / 2,
			3 * m_basicTankScore.getGlobalBounds().height));

		m_lightBattleTankSprite.setTexture(m_enemyTankTexture);
		m_lightBattleTankSprite.setScale(sf::Vector2f(
			m_windowResolution->y / (10 * m_enemyTankTexture.getSize().y),
			m_windowResolution->y / (10 * m_enemyTankTexture.getSize().y)));
		m_lightBattleTankSprite.setPosition(sf::Vector2f(
			m_lightBattleTankScore.getPosition().x - m_lightBattleTankSprite.getGlobalBounds().width,
			m_lightBattleTankScore.getPosition().y));

		m_doubleBarrelTankScore.setFont(*gamefont);
		m_doubleBarrelTankScore.setCharacterSize(m_windowResolution->y / 10);
		m_doubleBarrelTankScore.setString(" - " + std::to_string(m_doubleBarrelTankKilled));
		m_doubleBarrelTankScore.setPosition(sf::Vector2f(
			(m_windowResolution->x - (0.5 * m_doubleBarrelTankScore.getGlobalBounds().width)) / 2,
			6 * m_basicTankScore.getGlobalBounds().height));

		m_doubleBarrelTankSprite.setTexture(m_enemyTankTexture);
		m_doubleBarrelTankSprite.setScale(sf::Vector2f(
			m_windowResolution->y / (10 * m_enemyTankTexture.getSize().y),
			m_windowResolution->y / (10 * m_enemyTankTexture.getSize().y)));
		m_doubleBarrelTankSprite.setPosition(sf::Vector2f(
			m_doubleBarrelTankScore.getPosition().x - m_doubleBarrelTankSprite.getGlobalBounds().width,
			m_doubleBarrelTankScore.getPosition().y));


		m_destroyerTankScore.setFont(*gamefont);
		m_destroyerTankScore.setCharacterSize(m_windowResolution->y / 10);
		m_destroyerTankScore.setString(" - " + std::to_string(m_destroyerTankKilled));
		m_destroyerTankScore.setPosition(sf::Vector2f(
			(m_windowResolution->x - (0.5 * m_destroyerTankScore.getGlobalBounds().width)) / 2,
			9 * m_basicTankScore.getGlobalBounds().height));

		m_destroyerTankSprite.setTexture(m_enemyTankTexture);
		m_destroyerTankSprite.setScale(sf::Vector2f(
			m_windowResolution->y / (10 * m_enemyTankTexture.getSize().y),
			m_windowResolution->y / (10 * m_enemyTankTexture.getSize().y)));
		m_destroyerTankSprite.setPosition(sf::Vector2f(
			m_destroyerTankScore.getPosition().x - m_destroyerTankSprite.getGlobalBounds().width,
			m_destroyerTankScore.getPosition().y));


		m_fighterTankScore.setFont(*gamefont);
		m_fighterTankScore.setCharacterSize(m_windowResolution->y / 10);
		m_fighterTankScore.setString(" - " + std::to_string(m_fighterTankKilled));
		m_fighterTankScore.setPosition(sf::Vector2f(
			(m_windowResolution->x - (0.5 * m_fighterTankScore.getGlobalBounds().width)) / 2,
			12 * m_basicTankScore.getGlobalBounds().height));

		m_fighterTankSprite.setTexture(m_enemyTankTexture);
		m_fighterTankSprite.setScale(sf::Vector2f(
			m_windowResolution->y / (10 * m_enemyTankTexture.getSize().y),
			m_windowResolution->y / (10 * m_enemyTankTexture.getSize().y)));
		m_fighterTankSprite.setPosition(sf::Vector2f(
			m_fighterTankScore.getPosition().x - m_fighterTankSprite.getGlobalBounds().width,
			m_fighterTankScore.getPosition().y));

		m_totalScore.setFont(*gamefont);
		m_totalScore.setCharacterSize(m_windowResolution->y / 10);

		m_totalScore.setString("Total - " + std::to_string(
			m_basicTankKilled + m_lightBattleKilled + m_doubleBarrelTankKilled + m_destroyerTankKilled + m_fighterTankKilled));

		m_totalScore.setPosition(sf::Vector2f(
			(m_windowResolution->x - m_totalScore.getGlobalBounds().width) / 2,
			m_windowResolution->y - 2 * m_totalScore.getGlobalBounds().height));
	}
}

void Score::Update(
	int basicTankKilled,
	int lightBattleTankKilled,
	int doubleBarrelTankKilled,
	int destroyerTankKilled,
	int fighterTankKilled)
{
	m_basicTankKilled = basicTankKilled;
	m_lightBattleKilled = lightBattleTankKilled;
	m_doubleBarrelTankKilled = doubleBarrelTankKilled;
	m_destroyerTankKilled = destroyerTankKilled;
	m_fighterTankKilled = fighterTankKilled;

	m_basicTankScore.setString(" - " + std::to_string(m_basicTankKilled));
	m_lightBattleTankScore.setString(" - " + std::to_string(m_lightBattleKilled));
	m_doubleBarrelTankScore.setString(" - " + std::to_string(m_doubleBarrelTankKilled));
	m_destroyerTankScore.setString(" - " + std::to_string(m_destroyerTankKilled));
	m_fighterTankScore.setString(" - " + std::to_string(m_fighterTankKilled));

	m_totalScore.setString("Total - " + std::to_string(
		m_basicTankKilled + m_lightBattleKilled + m_doubleBarrelTankKilled + m_destroyerTankKilled + m_fighterTankKilled));
}

void Score::Draw(sf::RenderWindow& window)
{
	window.draw(m_basicTankSprite);
	window.draw(m_basicTankScore);

	window.draw(m_lightBattleTankSprite);
	window.draw(m_lightBattleTankScore);

	window.draw(m_doubleBarrelTankSprite);
	window.draw(m_doubleBarrelTankScore);

	window.draw(m_destroyerTankSprite);
	window.draw(m_destroyerTankScore);

	window.draw(m_fighterTankSprite);
	window.draw(m_fighterTankScore);

	window.draw(m_totalScore);
}

Score::~Score()
{
}