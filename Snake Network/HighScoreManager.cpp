#include "High Score Manager.h"
#include "Message.h"

HighScoreManager::HighScoreManager(sf::TcpSocket& socket) {
	this->socket = &socket;
}

static bool sortBySecond(const pair<string, int>& a, const pair<string, int>& b) {
	return a.second > b.second;
}

void HighScoreManager::runGame() {
	while (1) {
		message msg;
		sf::Socket::Status status = socket->receive(packet);
		if (status == sf::Socket::Disconnected) {
			break;
		}
		packet >> msg;
		packet.clear();
		// recieve score
		if (msg.type == 0) {
			// read high scores from file
			ifstream inStream;
			inStream.open("C:/Users/alexl/source/repos/Snake Network/scores.txt");
			scores.assign(5, { "", 0 });
			for (int i = 0; i < 5; i++) {
				inStream >> scores[i].first;
				inStream >> scores[i].second;
			}
			inStream.close();
			if (msg.score > scores[4].second) { // if score is high score
				mtx.lock();
				scores[4].second = msg.score;
				// send message to get name
				msg.type = 1;
				packet << msg;
				socket->send(packet);
				packet.clear();
				sf::Socket::Status status = socket->receive(packet);
				if (status == sf::Socket::Disconnected) {
					mtx.unlock();
					break;
				}
				// get name
				packet >> msg;
				packet.clear();
				scores[4].first = msg.name;
				sort(scores.begin(), scores.end(), &sortBySecond);
				// write high scores to file
				ofstream outStream;
				outStream.open("C:/Users/alexl/source/repos/Snake Network/scores.txt");
				for (int i = 0; i < 5; i++) {
					outStream << scores[i].first + " " + to_string(scores[i].second) << endl;
				}
				outStream.close();
				mtx.unlock();
			}
			// send high scores
			msg.type = 2;
			msg.highScores = scores;
			packet << msg;
			socket->send(packet);
			packet.clear();
		}
	}
}