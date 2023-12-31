#include "Snake.h"

Snake::Snake() {
	color = sf::Color::Green;
	Unit head(color, UNIT_SIZE, int(GRID_HEIGHT / 2) * UNIT_SIZE);
	body = { head };
	length = 1;
	direction = right;
}

std::list<Unit>& Snake::getBody() {
	return body;
}

int Snake::getLength() const {
	return length;
}

directions Snake::getDirection() const {
	return direction;
}

void Snake::setDirection(directions direction) {
	this->direction = direction;
}

void Snake::draw(sf::RenderWindow& window) {
	for (Unit& unit : body) {
		unit.draw(window);
	}
}

// add next position, return true if game over (snake runs into self or out of bounds)
bool Snake::step() {
	Unit& previous = body.front();
	Unit next(color);
	switch (direction) {
	case left:
		next.setPosition(previous.getX() - UNIT_SIZE, previous.getY());
		break;
	case right:
		next.setPosition(previous.getX() + UNIT_SIZE, previous.getY());
		break;
	case up:
		next.setPosition(previous.getX(), previous.getY() - UNIT_SIZE);
		break;
	case down:
		next.setPosition(previous.getX(), previous.getY() + UNIT_SIZE);
		break;
	}
	bool runIntoSelf = touching(next);
	bool outOfBounds = next.getX() < 0 || next.getY() < UNIT_SIZE || next.getX() > WINDOW_WIDTH - UNIT_SIZE || next.getY() > WINDOW_HEIGHT - UNIT_SIZE;
	if (!runIntoSelf && !outOfBounds) {
		body.push_front(next);
		length++;
		return false;
	}
	return true;
}

// return snake is touching other
bool Snake::touching(Unit& other) {
	for (Unit& unit : body) {
		if (unit.getX() == other.getX() && unit.getY() == other.getY())
			return true;
	}
	return false;
}

// only move if valid, return true if game over (run into self, out of bounds or fills grid)
bool Snake::move(bool eatApple) {
	bool invalidPosition = step();
	if (!invalidPosition && !eatApple) {
		body.pop_back();
		length--;
	}
	return invalidPosition || length == GRID_WIDTH * GRID_HEIGHT; //snake fills grid
}