#include "Message.h"

sf::Packet& operator <<(sf::Packet& packet, const message& m)
{
	packet << m.type << m.score << m.name;
	for (int i = 0; i < 5; i++) {
		packet << m.highScores[i].first << m.highScores[i].second;
	}
	return packet;
}

sf::Packet& operator >>(sf::Packet& packet, message& m)
{
	packet >> m.type >> m.score >> m.name;
	for (int i = 0; i < 5; i++) {
		packet >> m.highScores[i].first >> m.highScores[i].second;
	}
	return packet;
}