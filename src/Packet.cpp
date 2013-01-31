/*
 * Packet.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: Remco
 */

#include "Packet.h"
#include <iostream>

sf::Packet& operator >>(sf::Packet& packet, basePacketStruct& m) {
	return packet >> m.prot >> m.sequence >> m.ack >> m.id;
}
sf::Packet& operator <<(sf::Packet& packet, const basePacketStruct& m) {
	return packet << m.prot << m.sequence << m.ack << m.id;
}
sf::Packet& operator >>(sf::Packet& packet, connectPacketStruct& m) {
	return packet >> m.name >> m.clientPort;
}
sf::Packet& operator <<(sf::Packet& packet, const connectPacketStruct& m) {
	return packet << m.name << m.clientPort;
}
sf::Packet& operator >>(sf::Packet& packet, chatPacketStruct& m) {
	return packet >> m.clientIP >> m.name >> m.message;
}
sf::Packet& operator <<(sf::Packet& packet, const chatPacketStruct& m) {
	return packet << m.clientIP << m.name << m.message;
}
sf::Packet& operator >>(sf::Packet& packet, newPlayerInitStruct& m) {
	return packet >> m.mapName >> m.playerID;
}
sf::Packet& operator <<(sf::Packet& packet, const newPlayerInitStruct& m) {
	return packet << m.mapName << m.playerID;
}
sf::Packet& operator >>(sf::Packet& packet, serverMessageStruct& m) {
	return packet >> m.message;
}
sf::Packet& operator <<(sf::Packet& packet, const serverMessageStruct& m) {
	return packet << m.message;
}
sf::Packet& operator >>(sf::Packet& packet, playerMoveStruct& m) {
	return packet >> m.playerid >> m.x >> m.y >> m.velx >> m.vely >> m.direction >> m.jump;
}
sf::Packet& operator <<(sf::Packet& packet, const playerMoveStruct& m) {
	return packet << m.playerid << m.x << m.y << m.velx << m.vely << m.direction << m.jump;
}
sf::Packet& operator >>(sf::Packet& packet, inputPacketStruct& m) {
	return packet >> m.jump >> m.direction;
}
sf::Packet& operator <<(sf::Packet& packet, const inputPacketStruct& m) {
	return packet << m.jump << m.direction;
}
sf::Packet& operator >>(sf::Packet& packet, requestPlayerPacketStruct& m) {
	return packet >> m.playerID;
}
sf::Packet& operator <<(sf::Packet& packet, const requestPlayerPacketStruct& m) {
	return packet << m.playerID;
}
sf::Packet& operator >>(sf::Packet& packet, newPlayerPacketStruct& m) {
	return packet >> m.name >> m.playerID;
}
sf::Packet& operator <<(sf::Packet& packet, const newPlayerPacketStruct& m) {
	return packet << m.name << m.playerID;
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

Packet::Packet(inputPacketStruct packet, basePacketStruct basePacket) {
	this->basePacket = basePacket;
	this->inputPacket = packet;
	packetType = PLAYERINPUTPACKET;
	setSendingPacket();
}

Packet::Packet(playerMoveStruct packet, basePacketStruct basePacket) {
	this->basePacket = basePacket;
	this->playerMovePacket = packet;
	packetType = PLAYERMOVEPACKET;
	setSendingPacket();
}

Packet::Packet(requestPlayerPacketStruct packet, basePacketStruct basePacket) {
	this->basePacket = basePacket;
	this->requestPlayerPacket = packet;
	packetType = REQUESTPLAYERPACKET;
	setSendingPacket();
}
Packet::Packet(newPlayerPacketStruct packet, basePacketStruct basePacket) {
	this->basePacket = basePacket;
	this->newPlayerPacket = packet;
	packetType = NEWPLAYERPACKET;
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
	case PLAYERINPUTPACKET:
		sendingPacket << inputPacket;
		break;
	case PLAYERMOVEPACKET:
		sendingPacket << playerMovePacket;
		break;
	case REQUESTPLAYERPACKET:
		sendingPacket << requestPlayerPacket;
		break;
	case NEWPLAYERPACKET:
		sendingPacket << newPlayerPacket;
		break;
	}
}


