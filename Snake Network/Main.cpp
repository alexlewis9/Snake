#include <SFML/Network.hpp>
#include "Game Window.h"
#include "High Score Manager.h"
#include <iostream>
using namespace std;

static void createAndRunHighScoreManager(sf::TcpSocket* socket) {
	HighScoreManager highScoreManager(*socket);
	highScoreManager.runGame(); // returns when client disconnected
	delete socket;
}

int main(int argc, char** argv) {

	unsigned short port = 35000;

	if (argc == 1) {
		// server
		sf::TcpListener listener;
		listener.listen(port);

		while (1) {
			sf::TcpSocket* socket = new sf::TcpSocket();
			if (listener.accept(*socket) == sf::Socket::Done) {
				std::thread *threadObj = new std::thread(&createAndRunHighScoreManager, socket);
			}
		}
			
	}
	else {
		// client
		string ipAddress = argv[1];
		bool connectedToServer = true;

		sf::TcpSocket socket;

		sf::Socket::Status status = socket.connect(ipAddress, port);
		if (status != sf::Socket::Done)
		{
			cout << "Error connecting to server";
			connectedToServer = false;
		}

		GameWindow gameWindow(connectedToServer, socket);
		gameWindow.runGame();

	}

	return 0;

}