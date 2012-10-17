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

/*PACKET PROTOCOL
 * int type					//one variable
 * int protocol				//begin basePacketStruct
 * int sequence
 * int ack
 * int ackbitfield			//end basePacketStruct
 * struct data				//depending on type
 */

enum packetType {
	CONNECTPACKET, CHATPACKET, MOVEPACKET, STATEPACKET //different types of effects
};

//EVERY PACKET MUST HAVE THIS
struct basePacketStruct {
	sf::Uint16 prot;//protocol id, ignore all packets with the wrong protocol
	sf::Uint32 sequence;	//this is the sequence number of our server/packet
	sf::Uint16 ack;						//acknowledgement
	sf::Uint32 ackbitfield;				//32 bits to ack in bitfield
};

sf::Packet& operator >>(sf::Packet& packet, basePacketStruct& m);
sf::Packet& operator <<(sf::Packet& packet, const basePacketStruct& m);
struct connectPacketStruct {
	std::string name;
};
sf::Packet& operator >>(sf::Packet& packet, connectPacketStruct& m);
sf::Packet& operator <<(sf::Packet& packet, const connectPacketStruct& m);
struct chatPacketStruct {
	std::string clientIP;			//only set at receiving server
	std::string name;				//only set at receiving client
	std::string message;
};
sf::Packet& operator >>(sf::Packet& packet, chatPacketStruct& m);
sf::Packet& operator <<(sf::Packet& packet, const chatPacketStruct& m);
struct movePacketStruct {
	std::string name;				//only set at receiving client
};

struct statePacketStruct {
	std::string name;				//only set at receiving client
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

	sf::IpAddress clientIP;										//always IP of the client, never the server

	Packet();
	Packet(connectPacketStruct connectPacket, basePacketStruct basePacket);
	Packet(chatPacketStruct chatPacket, basePacketStruct basePacket);
//	Packet(struct movePacketStruct);
//	Packet(struct statePacketStruct);

	sf::Packet getSendingPacket();
	virtual ~Packet();
};

#endif /* PACKET_H_ */
