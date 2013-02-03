#ifndef SERVER_Server_h
#define SERVER_Server_h

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

	Server();
	void tick();

 public:

    serverSettings *settings;
    World *currentWorld;
    packetsHandler *packethandler;
};

} /* End of namespace SERVER */

#endif // SERVER_Server_h
