#ifndef SERVER_Server_h
#define SERVER_Server_h

#include "RakPeerInterface.h"
#include "serverSettings.h"
#include <SFML\Network.hpp>

namespace SERVER {
class serverSettings;
} /* End of namespace SERVER */
class World;
namespace SERVER {
class packetsHandler;
} /* End of namespace SERVER */

namespace SERVER {

class Server {

public:
	RakNet::RakPeerInterface *peer;

	RakNet::TimeMS lastUpdatedTime;		//time we last updated
	RakNet::TimeMS currentTime;			//current timestamp
	long sequence;						//nr of loops we've been through
	sf::IpAddress serverIP;

	Server();
	~Server();
	void setupConnection();
	void tick();

public:
	SERVER::serverSettings settings;
	//World currentWorld;
	//SERVER::packetsHandler packethandler;
};

} /* End of namespace SERVER */

#endif // SERVER_Server_h
