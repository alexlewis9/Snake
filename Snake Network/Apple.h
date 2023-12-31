#ifndef APPLE_H
#define APPLE_H
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Unit.h"

class Apple : public Unit {
public:
	Apple();
	void move();
};

#endif