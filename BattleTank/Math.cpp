#include <iostream>
#include <vector>

#include "Math.h"

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


