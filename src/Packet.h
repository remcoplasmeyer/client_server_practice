/*
 * Packet.h
 *
 *  Created on: Oct 17, 2012
 *      Author: Remco
 */

#ifndef PACKET_H_
#define PACKET_H_
#include <SFML/Network.hpp>
#include <string>
#include "World.h"

/*PACKET PROTOCOL
 * int type					//one variable
 * int protocol				//begin basePacketStruct
 * int sequence
 * int ack
 * int ackbitfield			//end basePacketStruct
 * struct data				//depending on type
 */

//EVERY PACKET MUST HAVE THIS
struct basePacketStruct {
	sf::Uint16 prot;//protocol id, ignore all packets with the wrong protocol
	sf::Uint32 sequence;	//this is the sequence number of our server/packet
	sf::Uint32 ack;						//acknowledgement
	sf::Uint16 id;				//32 bits to ack in bitfield
};


struct connectPacketStruct {
	std::string name;
	short unsigned int clientPort;
};
struct chatPacketStruct {
	std::string clientIP;			//only set at receiving server
	std::string name;				//only set at receiving client
	std::string message;
};

//this packet contains input from the client
struct inputPacketStruct {
	bool jump;
	sf::Uint8 direction;
};

struct statePacketStruct {
	std::string name;				//only set at receiving client
};

//when a new player connects, we have to send him all the data of the current world (or actually the map)
//which is currently just the map name for the client to load
struct newPlayerInitStruct {
	std::string mapName;
	sf::Uint16 playerID;
};

struct movePacketStruct {
	std::string name;				//only set at receiving client
};

struct serverMessageStruct {
	std::string message;
};

//GAMEPLAY PACKETS FROM THE SERVER
struct playerMoveStruct {
	int playerid;
	float x;
	float y;
	float velx;
	float vely;
	sf::Uint8 direction;
	bool jump;
};

//all the packet overloaders
sf::Packet& operator >>(sf::Packet& packet, basePacketStruct& m);
sf::Packet& operator <<(sf::Packet& packet, const basePacketStruct& m);
sf::Packet& operator >>(sf::Packet& packet, connectPacketStruct& m);
sf::Packet& operator <<(sf::Packet& packet, const connectPacketStruct& m);
sf::Packet& operator >>(sf::Packet& packet, chatPacketStruct& m);
sf::Packet& operator <<(sf::Packet& packet, const chatPacketStruct& m);
sf::Packet& operator >>(sf::Packet& packet, newPlayerInitStruct& m);
sf::Packet& operator <<(sf::Packet& packet, const newPlayerInitStruct& m);
sf::Packet& operator >>(sf::Packet& packet, serverMessageStruct& m);
sf::Packet& operator <<(sf::Packet& packet, const serverMessageStruct& m);
sf::Packet& operator >>(sf::Packet& packet, playerMoveStruct& m);
sf::Packet& operator <<(sf::Packet& packet, const playerMoveStruct& m);
sf::Packet& operator >>(sf::Packet& packet, inputPacketStruct& m);
sf::Packet& operator <<(sf::Packet& packet, const inputPacketStruct& m);

enum packetType {
	CONNECTPACKET, NEWPLAYERINITPACKET, CHATPACKET, MOVEPACKET, STATEPACKET, SERVERMESSAGEPACKET, PLAYERINPUTPACKET, PLAYERMOVEPACKET //different types of effects
};

class Packet {
public:
	basePacketStruct basePacket;
	//contains one of the following, according to the type
	int packetType;												//we choose the other struct with this type
	connectPacketStruct connectPacket;
	chatPacketStruct chatPacket;
	movePacketStruct movePacket;
	statePacketStruct statePacket;
	serverMessageStruct serverMessage;
	newPlayerInitStruct newPlayer;
	inputPacketStruct inputPacket;

	playerMoveStruct playerMovePacket;

	sf::Packet sendingPacket;
	sf::IpAddress clientIP;										//always IP of the client, never the server

	Packet();
	Packet(connectPacketStruct connectPacket, basePacketStruct basePacket);
	Packet(chatPacketStruct chatPacket, basePacketStruct basePacket);
	Packet(serverMessageStruct packet, basePacketStruct basePacket);
	Packet(newPlayerInitStruct packet, basePacketStruct basePacket);
	Packet(inputPacketStruct packet, basePacketStruct basePacket);
	Packet(playerMoveStruct packet, basePacketStruct basePacket);
//	Packet(struct movePacketStruct);
//	Packet(struct statePacketStruct);

	sf::Packet getSendingPacket();
	virtual ~Packet();
private:
	void setSendingPacket();
};

#endif /* PACKET_H_ */
