#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H
#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <mutex>
using namespace std;

class HighScoreManager {
private:
	sf::TcpSocket* socket;
	sf::Packet packet;
	vector<pair<string, int>> scores;
	std::mutex mtx;
public:
	HighScoreManager(sf::TcpSocket& socket);
	void runGame();
};

#endif