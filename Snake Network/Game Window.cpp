#include "Game Window.h"
#include "Message.h"

GameWindow::GameWindow(bool connectedToServer, sf::TcpSocket& socket) {
	this->connectedToServer = connectedToServer; // only do high scores if connected to server
	this->socket = &socket;
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake", sf::Style::Titlebar | sf::Style::Close);

	font.loadFromFile("C:/Windows/Fonts/arial.ttf");

	startGameText.setFont(font);
	startGameText.setFillColor(sf::Color::White);
	startGameText.setCharacterSize(60);
	startGameText.setString("Press any key to play");
	startGameText.setPosition(static_cast<float>((WINDOW_WIDTH - startGameText.getGlobalBounds().width) / 2), static_cast<float>((WINDOW_HEIGHT - startGameText.getGlobalBounds().height) / 2));

	scoreText.setFont(font);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setCharacterSize(40);
	scoreText.setString("Current Score: " + std::to_string(game.getScore()));
	scoreText.setPosition(static_cast<float>((WINDOW_WIDTH - scoreText.getGlobalBounds().width) / 2), 0);

	enterName.setFont(font);
	enterName.setFillColor(sf::Color::White);
	enterName.setCharacterSize(60);
	enterName.setString("Enter name");
	enterName.setPosition(static_cast<float>((WINDOW_WIDTH - enterName.getGlobalBounds().width) / 2), static_cast<float>((WINDOW_HEIGHT - enterName.getGlobalBounds().height) / 2));

	highScoreText.setFont(font);
	highScoreText.setFillColor(sf::Color::White);
	highScoreText.setCharacterSize(50);
	highScoreText.setString("High Scores");
	highScoreText.setPosition(static_cast<float>((WINDOW_WIDTH - highScoreText.getGlobalBounds().width) / 2), static_cast<float>(WINDOW_HEIGHT / 6));

	highScoreNumText.setFont(font);
	highScoreNumText.setFillColor(sf::Color::White);
	highScoreNumText.setCharacterSize(40);

	highScoreNameText.setFont(font);
	highScoreNameText.setFillColor(sf::Color::White);
	highScoreNameText.setCharacterSize(40);

	bufferEat.loadFromFile("C:/Users/alexl/source/repos/Snake Network/eat.wav");
	soundEat.setBuffer(bufferEat);

	bufferEndGame.loadFromFile("C:/Users/alexl/source/repos/Snake Network/gameOver.wav");
	soundEndGame.setBuffer(bufferEndGame);
}

// returns when window closed
void GameWindow::runGame() {
	sf::RectangleShape line(sf::Vector2f(WINDOW_WIDTH, 2));
	line.setPosition(0, UNIT_SIZE);

	message msg;

	std::vector<std::pair<std::string, int>>* scores{};

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (waitingOnName) { // player input name for high score
				if (event.key.scancode == sf::Keyboard::Scan::Enter) {
					// name can not be empty
					if (!name.empty()) {
						waitingOnName = false;
						// send name
						msg.type = 1;
						msg.name = name;
						packet << msg;
						socket->send(packet);
						packet.clear();
						// recieve high scores
						sf::Socket::Status status = socket->receive(packet);
						if (status == sf::Socket::Disconnected) {
							connectedToServer = false;
						}
						packet >> msg;
						if (msg.type == 2) {
							scores = &msg.highScores;
						}
						packet.clear();
					}
				}
				else if (event.key.scancode == sf::Keyboard::Scan::Backspace) {
					name = name.substr(0, name.length() - 1);
				}
				else if (event.type == sf::Event::TextEntered && name.length() < 10)
				{
					if (event.text.unicode > 32 && event.text.unicode < 127)
						name += char(event.text.unicode);
				}
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (!gameRunning) {
					// start game
					if (firstGame) {
						firstGame = false;
						if (connectedToServer)
							startGameText.setPosition(static_cast<float>((WINDOW_WIDTH - startGameText.getGlobalBounds().width) / 2), static_cast<float>(WINDOW_HEIGHT * 5 / 6));
					}
					gameRunning = true;
					game = Game();
					clock.restart();
				}
			}
			// pause game when window loses focus. resume when gain focus again
			else if (event.type == sf::Event::LostFocus) {
				paused = true;
			}
			else if (event.type == sf::Event::GainedFocus) {
				paused = false;
			}

		}

		window.clear();

		if (!gameRunning) {
			if (firstGame) {
				window.draw(startGameText);
			}
			else {
				if (gameOver) {
					soundEndGame.play();
					currentScore = game.getScore();
					// send score
					msg.type = 0;
					msg.score = currentScore;
					packet << msg;
					socket->send(packet);
					packet.clear();
					sf::Socket::Status status = socket->receive(packet);
					if (status == sf::Socket::Disconnected) {
						connectedToServer = false;
					}
					// recieve if need to get name or high scores
					packet >> msg;
					packet.clear();
					if (msg.type == 1) { // need to get name for high score
						name = string();
						waitingOnName = true;
					}
					else if (msg.type == 2) { // high scores
						scores = &msg.highScores;
					}
					gameOver = false;
				}
				if (waitingOnName) {
					// display message for player to input name, display name entered so far
					window.draw(enterName);
					highScoreNameText.setString(name);
					highScoreNameText.setPosition(static_cast<float>((WINDOW_WIDTH - highScoreNameText.getGlobalBounds().width) / 2), static_cast<float>(WINDOW_HEIGHT / 2) + UNIT_SIZE);
					window.draw(highScoreNameText);
				}
				else {
					if (!connectedToServer) {
						startGameText.setPosition(static_cast<float>((WINDOW_WIDTH - startGameText.getGlobalBounds().width) / 2), static_cast<float>((WINDOW_HEIGHT - startGameText.getGlobalBounds().height) / 2));
					}
					window.draw(startGameText);
					if (connectedToServer) {
						window.draw(highScoreText);
						for (int i = 0; i < 5; i++) {
							highScoreNumText.setString(to_string((*scores)[i].second));
							highScoreNumText.setPosition(static_cast<float>(WINDOW_WIDTH * 2 / 3), static_cast<float>(WINDOW_HEIGHT / 3) + i * UNIT_SIZE);
							window.draw(highScoreNumText);
							highScoreNameText.setString((*scores)[i].first);
							highScoreNameText.setPosition(static_cast<float>(WINDOW_WIDTH / 3), static_cast<float>(WINDOW_HEIGHT / 3) + i * UNIT_SIZE);
							window.draw(highScoreNameText);
						}
					}
				}
			}
		}
		else {
			if (!paused) {
				gameOver = game.update(clock.getElapsedTime(), event.key.scancode);
				gameRunning = !gameOver;
			}
			game.draw(window);
			window.draw(line);
			if (game.getScore() > currentScore) {
				currentScore = game.getScore();
				soundEat.play();
			}
			scoreText.setString("Current Score: " + std::to_string(game.getScore()));
			window.draw(scoreText);
		}

		window.display();

	}
}