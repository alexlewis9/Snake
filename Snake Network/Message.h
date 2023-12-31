#ifndef MESSAGE_H
#define MESSAGE_H
#include "Constants.h"
#include <SFML/Network.hpp>
#include <vector>
using namespace std;

struct message {
	int type = -1; // 0 for sending score, 1 for sending name, 2 for sending high scores
	int score = 0;
	string name= "";
	vector<pair<string, int>> highScores{ {{ "", 0 }, { "", 0 }, { "", 0 }, { "", 0 }, { "", 0 }} };
};

sf::Packet& operator <<(sf::Packet& packet, const message& m);
sf::Packet& operator >>(sf::Packet& packet, message& m);

#endif