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
	sf::Uint16 ack;						//acknowledgement
	sf::Uint32 ackbitfield;				//32 bits to ack in bitfield
};


struct connectPacketStruct {
	std::string name;
};
struct chatPacketStruct {
	std::string clientIP;			//only set at receiving server
	std::string name;				//only set at receiving client
	std::string message;
};

struct statePacketStruct {
	std::string name;				//only set at receiving client
};

//when a new player connects, we have to send him all the data of the current world (or actually the map)
//which is currently just the map name for the client to load
struct newPlayerInitStruct {
	std::string mapName;
};

struct movePacketStruct {
	std::string name;				//only set at receiving client
};

struct serverMessageStruct {
	std::string message;
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

enum packetType {
	CONNECTPACKET, NEWPLAYERINITPACKET, CHATPACKET, MOVEPACKET, STATEPACKET, SERVERMESSAGEPACKET //different types of effects
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

	sf::Packet sendingPacket;
	sf::IpAddress clientIP;										//always IP of the client, never the server

	Packet();
	Packet(connectPacketStruct connectPacket, basePacketStruct basePacket);
	Packet(chatPacketStruct chatPacket, basePacketStruct basePacket);
	Packet(serverMessageStruct packet, basePacketStruct basePacket);
	Packet(newPlayerInitStruct packet, basePacketStruct basePacket);
//	Packet(struct movePacketStruct);
//	Packet(struct statePacketStruct);

	sf::Packet getSendingPacket();
	virtual ~Packet();
private:
	void setSendingPacket();
};

#endif /* PACKET_H_ */
