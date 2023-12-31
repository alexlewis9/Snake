#include <SFML/Network.hpp>
#include "Game Window.h"
#include "High Score Manager.h"
#include <iostream>
using namespace std;

vector<sf::TcpSocket*> sockets;

static void createAndRunHighScoreManager(sf::TcpSocket* socket) {
	HighScoreManager highScoreManager(*socket);
	highScoreManager.runGame();
	// when client disconnected, remove and destroy socket
	int indexOfSocket = -1;
	for (int i = 0; i < sockets.size(); i++) {
		if (sockets[i] == socket) {
			indexOfSocket = i;
		}
	}
	sockets.erase(sockets.begin() + indexOfSocket);
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
				sockets.push_back(socket);
				std::thread *threadObj = new std::thread(&createAndRunHighScoreManager, socket);
			}
		}
			
	}
	else {
		// client
		string ipAddress = argv[1];
		bool connectedToServer = true;

		sf::TcpSocket socket;

		sf::Socket::Status status = socket.connect("10.0.0.22", port);
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