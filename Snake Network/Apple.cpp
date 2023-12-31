#include "Apple.h"

Apple::Apple() :Unit(sf::Color::Red) {
	move();
}

// assign random location
void Apple::move() {
	x = static_cast<float>(UNIT_SIZE * ((rand() % (GRID_WIDTH - 1)) + 1));
	y = static_cast<float>(UNIT_SIZE * ((rand() % (GRID_HEIGHT - 1)) + 1));
}