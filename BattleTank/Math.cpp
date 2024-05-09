#include <iostream>

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
