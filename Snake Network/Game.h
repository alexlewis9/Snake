#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Apple.h"
#include "Snake.h"

class Game {
private:
	Apple apple;
	Snake snake;
	sf::Time lastUpdate; //elapsed time at last update
	bool gameOver;
	float speed;
public:
	Game();
	int getScore() const;
	void draw(sf::RenderWindow& window);
	void updateDirection(const sf::Keyboard::Scan::Scancode& key);
	bool update(const sf::Time& elapsed, const sf::Keyboard::Scan::Scancode& key);
};

#endif