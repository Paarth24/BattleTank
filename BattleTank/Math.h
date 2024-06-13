#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

#include "Bullet.h"

struct Math {

	static bool IfOutOfWindow(sf::RenderWindow& window, const sf::Sprite& sprite);
	
	static bool Collision(const sf::FloatRect& rect1, const sf::FloatRect& rect2);

	static void BulletInMap(sf::RenderWindow& window, std::vector<Bullet>& bullets);

	static bool TextClicked(const sf::Vector2i& mouseposition, const sf::Text& text);
};