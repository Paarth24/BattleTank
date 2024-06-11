#include <iostream>
#include <vector>

#include "Math.h"

bool Math:: IfOutOfWindow(sf::RenderWindow& window, const sf::Sprite& sprite) {
	
	if (sprite.getPosition().x > window.getSize().x) {

		return true;
	}
	else if (sprite.getPosition().y > window.getSize().y) {

		return true;
	}
	else if (sprite.getPosition().x < 0) {

		return true;
	}
	else if (sprite.getPosition().y < 0) {

		return true;
	}
	else {
		return false;
	}
}

bool Math::Collision(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
{	
	if (rect1.left <= rect2.left + rect2.width &&
		rect2.left <= rect1.left + rect1.width &&

		rect1.top <= rect2.top + rect2.height &&
		rect2.top <= rect1.top + rect1.height
		) {
		
		return(true);
	}
	else {

		return(false);
	}
}

void Math::BulletInMap(sf::RenderWindow& window, std::vector<Bullet>& bullets)
{
	for (size_t i = 0; i < bullets.size(); ++i) {

		if (bullets[i].m_bulletSprite.getPosition().x > window.getSize().x) {

			bullets.erase(bullets.begin() + i);
		}
		else if (bullets[i].m_bulletSprite.getPosition().y > window.getSize().y) {

			bullets.erase(bullets.begin() + i);
		}
		else if (bullets[i].m_bulletSprite.getPosition().x < 0) {

			bullets.erase(bullets.begin() + i);
		}
		else if (bullets[i].m_bulletSprite.getPosition().y < 0) {

			bullets.erase(bullets.begin() + i);
		}
	}
}

bool Math::TextClicked(const sf::Vector2i& mouseposition, const sf::Text& text) {

	if (mouseposition.x > text.getGlobalBounds().left &&
		mouseposition.x < text.getGlobalBounds().left + text.getGlobalBounds().width &&
		mouseposition.y > text.getGlobalBounds().top &&
		mouseposition.y < text.getGlobalBounds().top + text.getGlobalBounds().height
		) {
		
		return(true);
	}
	else {
		return(false);
	}
}

bool Math::DidSpriteCollideWithMap(
	sf::RenderWindow& window,
	const sf::Vector2f* mapSize,
	const sf::Vector2f& spriteSize,
	const int& spriteDirection,
	const sf::Vector2f& spritePosition,
	const sf::Vector2f& spriteMovementSpeed)
{
	if (spriteDirection == 1) {

		sf::Vector2f position = sf::Vector2f(spritePosition.x, spritePosition.y - spriteMovementSpeed.y);

		if (position.y >= mapSize->y ||	position.y <= (window.getSize().y - mapSize->y) / 2){

			return true;
		}
		else {
			return false;
		}
	}

	if (spriteDirection == 2) {

		sf::Vector2f position = sf::Vector2f(spritePosition.x - spriteMovementSpeed.x, spritePosition.y);

		if (position.x >= mapSize->x || position.x <= (window.getSize().x - mapSize->x) / 3) {

			return true;
		}
		else {
			return false;
		}
	}

	if (spriteDirection == 3) {

		sf::Vector2f position = sf::Vector2f(spritePosition.x, spritePosition.y + spriteSize.y + spriteMovementSpeed.y);

		if (position.y >= mapSize->y || position.y <= (window.getSize().y - mapSize->y) / 2) {

			return true;
		}
		else {
			return false;
		}
	}

	if (spriteDirection == 4) {

		sf::Vector2f position = sf::Vector2f(spritePosition.x + spriteSize.x + spriteMovementSpeed.x, spritePosition.y);

		if (position.x >= mapSize->x || position.x <= (window.getSize().x - mapSize->x) / 3) {

			return true;
		}
		else {
			return false;
		}
	}
}
