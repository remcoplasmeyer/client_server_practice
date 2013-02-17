#ifndef CLIENT_packetReceiver_h
#define CLIENT_packetReceiver_h

namespace CLIENT {

class netHandler;

class packetReceiver {
public:
	netHandler *nethandler;

	packetReceiver();
	void setNethandler(netHandler *_nethandler);

	void receive();
};

} /* End of namespace CLIENT */

#endif // CLIENT_packetReceiver_h
