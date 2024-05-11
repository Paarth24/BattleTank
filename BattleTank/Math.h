#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

#include "Bullet.h"

struct Math {

	static bool Collision(const sf::FloatRect& rect1, const sf::FloatRect& rect2);

	static void BulletInMap(sf::RenderWindow& window, std::vector<Bullet>& bullets);
};