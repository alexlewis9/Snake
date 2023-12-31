#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "constants.h"
#include "Game.h"

class GameWindow {
private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Font font;
	sf::Text startGameText;
	sf::Text scoreText;
	sf::Text enterName;
	sf::Text highScoreText;
	sf::Text highScoreNumText;
	sf::Text highScoreNameText;
	sf::SoundBuffer bufferEat;
	sf::SoundBuffer bufferEndGame;
	sf::Sound soundEat;
	sf::Sound soundEndGame;
	Game game;
	bool connectedToServer;
	bool gameRunning = false;
	bool gameOver = false;
	bool firstGame = true;
	bool paused = false;
	bool waitingOnName = false;
	std::string name;
	int currentScore = 1;
	sf::TcpSocket* socket;
	sf::Packet packet;
public:
	GameWindow(bool connectedToServer, sf::TcpSocket& socket);
	void runGame();
};

#endif