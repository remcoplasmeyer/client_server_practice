#ifndef packetTypes_h
#define packetTypes_h
#include "MessageIdentifiers.h"
#include "GetTime.h"
#include <string>
#include "RakString.h"

enum packetIdentifiers {
	CHAT_PACKET = ID_USER_PACKET_ENUM,
	INIT_CONNECTOR_PACKET = ID_USER_PACKET_ENUM+1,
	PLAYERMOVE_PACKET = ID_USER_PACKET_ENUM+2,
	NEWPLAYER_PACKET = ID_USER_PACKET_ENUM+3
};


/* list of all our packets and what they contain */

#pragma pack(push, 1)
//base of all (most?) packets
struct basePacket {
	unsigned char useTimeStamp; // Assign ID_TIMESTAMP to this
	RakNet::Time timeStamp; // Put the system time in here returned by RakNet::GetTime() or some other method that returns a similar value
	unsigned char typeId; // Your type here
};

struct initConnectorPacket {
	basePacket base;
	RakNet::RakString mapJSON;				//JSON of the .map
	unsigned long uniqueid;					//player's unique id
};

//sent by server to all players, when a new player connects
struct newPlayerPacket {
	basePacket base;
	unsigned long uniqueid;
	RakNet::RakString name;
};

struct playerMovePacket {
	basePacket base;
	unsigned long uniqueid;
	float x;
	float y;
	float velx;
	float vely;
	int inputDirection;
	bool inputJump;
};

#pragma pack(pop)
#endif // packetTypes_h
