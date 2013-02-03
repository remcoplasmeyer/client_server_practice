#ifndef SERVER_serverSettings_h
#define SERVER_serverSettings_h
#include <string>

namespace SERVER {

class serverSettings {

 public:
    std::string name;
    std::string password;
	int port;
	int maxPlayers;
	int fps;

	serverSettings();
};

} /* End of namespace SERVER */

#endif // SERVER_serverSettings_h
