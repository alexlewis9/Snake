#ifndef UNIT_H
#define UNIT_H
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Unit {
private:
	sf::Color color;
protected:
	float x;
	float y;
public:
	Unit();
	Unit(sf::Color color);
	Unit(sf::Color color, float x, float y);
	float getX() const;
	float getY() const;
	void setPosition(float x, float y);
	void draw(sf::RenderWindow& window) const;
};

#endif
