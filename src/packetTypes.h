#ifndef packetTypes_h
#define packetTypes_h
#include "MessageIdentifiers.h"
#include "GetTime.h"
#include <string>

enum packetIdentifiers {
	CHAT_PACKET = ID_USER_PACKET_ENUM,
	INIT_CONNECTOR_PACKET = ID_USER_PACKET_ENUM+1
};


/* list of all our packets and what they contain */

#pragma pack(push, 1)
//base of all (most?) packets
struct basePacket {
	int type;							// type of packet, see enum above in this file
	RakNet::Time timeStamp;				// Put the system time in here returned by RakNet::GetTime()
};

struct initConnectorPacket {
	basePacket base;
	std::string mapJSON;
};

#pragma pack(pop)
#endif // packetTypes_h
