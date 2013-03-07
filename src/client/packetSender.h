#ifndef CLIENT_packetSender_h
#define CLIENT_packetSender_h
#include "../packetTypes.h"


namespace CLIENT {

class netHandler;

class packetSender {

public:
	netHandler *nethandler;

	packetSender();
	void setNethandler(netHandler *_nethandler);
	void sendClientMovementInput();
	basePacket getBasePacket(int type);
};

} /* End of namespace CLIENT */

#endif // CLIENT_packetSender_h
