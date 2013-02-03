#ifndef CLIENT_Client_h
#define CLIENT_Client_h

namespace CLIENT {
class guiHandler;
class inputHandler;
class gameHandler;
class viewHandler;
class clientSettings;
} /* End of namespace CLIENT */

namespace CLIENT {

class Client {

 public:

	Client();
    void tick();

 public:

    guiHandler *guiHandler;
    inputHandler *inputHandler;
    gameHandler *gameHandler;

    viewHandler *view;
    clientSettings *myclientSettings;
};

} /* End of namespace CLIENT */

#endif // CLIENT_Client_h
