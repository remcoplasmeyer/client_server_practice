#include "Client.h"
#include "../Log.h"
#include "inputHandler.h"

int main() {
	CLIENT::Client client;
	return 0;
}

namespace CLIENT {


Client::Client() {
	initHandlers();
	FILE_LOG(logINFO) << "Client opened";
	while(true) {

	}
}

void Client::initHandlers() {
	inputHandler = CLIENT::inputHandler();				//handles user & network input
	inputHandler.nethandler.connect("127.0.0.1", 1234);

	//guiHandler *guiHandler;
    //gameHandler *gameHandler;

    //viewHandler *view;
    //clientSettings *myclientSettings;
}

void Client::tick()
{

}

} /* End of namespace CLIENT */
