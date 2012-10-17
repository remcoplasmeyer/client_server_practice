/*
 * Packet.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: Remco
 */

#include "Packet.h"
#include <iostream>

sf::Packet& operator >>(sf::Packet& packet, basePacketStruct& m) {
	return packet >> m.prot >> m.sequence >> m.ack >> m.ackbitfield;
}

sf::Packet& operator <<(sf::Packet& packet, const basePacketStruct& m) {
	return packet << m.prot << m.sequence << m.ack << m.ackbitfield;
}
//END BASE PACKET

//CONNECT PACKET

sf::Packet& operator >>(sf::Packet& packet, connectPacketStruct& m) {
	return packet >> m.name;
}
sf::Packet& operator <<(sf::Packet& packet, const connectPacketStruct& m) {
	return packet << m.name;
}
//END CONNECT PACKET

//CHAT PACKET

sf::Packet& operator >>(sf::Packet& packet, chatPacketStruct& m) {
	return packet >> m.clientIP >> m.name >> m.message;
}

sf::Packet& operator <<(sf::Packet& packet, const chatPacketStruct& m) {
	return packet << m.clientIP << m.name << m.message;
}
//END CHAT PACKET



Packet::Packet() {
	// TODO Auto-generated constructor stub

}

Packet::~Packet() {
	// TODO Auto-generated destructor stub
}

Packet::Packet(connectPacketStruct connectPacket, basePacketStruct basePacket) {
	this->basePacket = basePacket;
	this->connectPacket = connectPacket;
	packetType = CONNECTPACKET;
}

Packet::Packet(chatPacketStruct chatPacket, basePacketStruct basePacket) {
	this->basePacket = basePacket;
	this->chatPacket = chatPacket;
	packetType = CHATPACKET;
}

sf::Packet Packet::getSendingPacket() {
	sf::Packet sendingPacket;
	sendingPacket << packetType;
	sendingPacket << basePacket;
	switch (packetType) {
	case CONNECTPACKET:
		sendingPacket << connectPacket;
		break;
	case CHATPACKET:
		sendingPacket << chatPacket;
		break;
	}
	return sendingPacket;
}


