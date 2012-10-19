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
sf::Packet& operator >>(sf::Packet& packet, connectPacketStruct& m) {
	return packet >> m.name;
}
sf::Packet& operator <<(sf::Packet& packet, const connectPacketStruct& m) {
	return packet << m.name;
}
sf::Packet& operator >>(sf::Packet& packet, chatPacketStruct& m) {
	return packet >> m.clientIP >> m.name >> m.message;
}
sf::Packet& operator <<(sf::Packet& packet, const chatPacketStruct& m) {
	return packet << m.clientIP << m.name << m.message;
}
sf::Packet& operator >>(sf::Packet& packet, newPlayerInitStruct& m) {
	return packet >> m.mapName;
}
sf::Packet& operator <<(sf::Packet& packet, const newPlayerInitStruct& m) {
	return packet << m.mapName;
}
sf::Packet& operator >>(sf::Packet& packet, serverMessageStruct& m) {
	return packet >> m.message;
}
sf::Packet& operator <<(sf::Packet& packet, const serverMessageStruct& m) {
	return packet << m.message;
}



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
	setSendingPacket();
}

Packet::Packet(chatPacketStruct chatPacket, basePacketStruct basePacket) {
	this->basePacket = basePacket;
	this->chatPacket = chatPacket;
	packetType = CHATPACKET;
	setSendingPacket();
}

Packet::Packet(serverMessageStruct packet, basePacketStruct basePacket) {
	this->basePacket = basePacket;
	this->serverMessage = packet;
	packetType = SERVERMESSAGEPACKET;
	setSendingPacket();
}

Packet::Packet(newPlayerInitStruct packet, basePacketStruct basePacket) {
	this->basePacket = basePacket;
	this->newPlayer = packet;
	packetType = NEWPLAYERINITPACKET;
	setSendingPacket();
}

void Packet::setSendingPacket() {
	sendingPacket << packetType;
	sendingPacket << basePacket;
	switch (packetType) {
	case CONNECTPACKET:
		sendingPacket << connectPacket;
		break;
	case CHATPACKET:
		sendingPacket << chatPacket;
		break;
	case SERVERMESSAGEPACKET:
		sendingPacket << serverMessage;
		break;
	case NEWPLAYERINITPACKET:
		sendingPacket << newPlayer;
		break;
	}
}


