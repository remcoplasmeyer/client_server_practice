#include "../Log.h"
#include "inputHandler.h"
#include "netHandler.h"
#include "controlHandler.h"

/*
	the [inputHandler] handles all input: user input and input from the network
	Also handles sending out packets, as this is input to the network
*/

namespace CLIENT {

	CLIENT::inputHandler::inputHandler() {
		//nethandler = CLIENT::netHandler();
		controlhandler = CLIENT::controlHandler();
	}

	void CLIENT::inputHandler::sendTestPacket() {
		nethandler.sendTestPacket();
	}

	//ran every client loop
	void CLIENT::inputHandler::tick() {
		this->nethandler.receivePackets();
	}

} /* End of namespace CLIENT */
