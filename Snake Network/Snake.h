#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Unit.h"
#include <list>

class Snake {
private:
	sf::Color color;
	std::list<Unit> body;
	int length;
	directions direction;
public:
	Snake();
	std::list<Unit>& getBody();
	int getLength() const;
	directions getDirection() const;
	void setDirection(directions direction);
	void draw(sf::RenderWindow& window);
	bool step();
	bool touching(Unit& other);
	bool move(bool eatApple);
};

#endif