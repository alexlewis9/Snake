#include "Unit.h"

Unit::Unit() {
    color = sf::Color::White;
    x = 0;
    y = 0;
}

Unit::Unit(sf::Color color) {
    this->color = color;
    x = 0;
    y = 0;
}

Unit::Unit(sf::Color color, float x, float y) {
    this->color = color;
    this->x = x;
    this->y = y;
}

float Unit::getX() const {
    return x;
}
float Unit::getY() const{
    return y;
}

void Unit::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

void Unit::draw(sf::RenderWindow& window) const {
    sf::RectangleShape shape(sf::Vector2f(UNIT_SIZE, UNIT_SIZE));
    shape.setPosition(x, y);
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(-5);
    window.draw(shape);
}