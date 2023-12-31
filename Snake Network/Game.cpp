#include "Game.h"

Game::Game() {
    gameOver = false;
    lastUpdate = sf::seconds(0);
    speed = static_cast < float>(0.3);
}

void Game::draw(sf::RenderWindow& window) {
    apple.draw(window);
    snake.draw(window);
}

void Game::updateDirection(const sf::Keyboard::Scan::Scancode& key) {
    switch (key) {
    case sf::Keyboard::Scan::Up:
        if (snake.getDirection() != down)
            snake.setDirection(up);
        break;
    case sf::Keyboard::Scan::Left:
        if (snake.getDirection() != right)
            snake.setDirection(left);
        break;
    case sf::Keyboard::Scan::Right:
        if (snake.getDirection() != left)
            snake.setDirection(right);
        break;
    case sf::Keyboard::Scan::Down:
        if (snake.getDirection() != up)
            snake.setDirection(down);
        break;
    }
}

bool Game::update(const sf::Time& elapsed, const sf::Keyboard::Scan::Scancode& key) {
    if (elapsed - lastUpdate > sf::seconds(speed) && !gameOver) {
        updateDirection(key);
        bool eatApple = false;
        Unit& head = snake.getBody().front();
        if (head.getX() == apple.getX() && head.getY() == apple.getY()) {
            eatApple = true;
            speed = static_cast < float>(speed * 0.97);
            do {
                apple.move();
            } while (snake.touching(apple));
        }
        gameOver = snake.move(eatApple);
        lastUpdate = elapsed;
    }
    return gameOver;
}

int Game::getScore() const {
    return snake.getLength();
}