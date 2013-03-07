#include "packetSender.h"
#include "netHandler.h"
#include "Client.h"
#include "gameHandler.h"
#include "../packetTypes.h"
#include "BitStream.h"

namespace CLIENT {

	packetSender::packetSender() {

	}

	void packetSender::setNethandler(netHandler *_nethandler) {
		this->nethandler = _nethandler;
	}

	basePacket packetSender::getBasePacket(int _type) {
		basePacket base;
		base.useTimeStamp = (unsigned char)ID_TIMESTAMP;
		base.typeId = _type;
		base.timeStamp = RakNet::GetTime();
		return base;
	}

	//sends the current client's input when ingame
	void packetSender::sendClientMovementInput() {
		Player *clientPlayer = &this->nethandler->client->gameHandler.currentWorld.players[this->nethandler->client->uniqueid];
		basePacket base = getBasePacket(PLAYERMOVE_INPUT_PACKET);
		playerMoveInputPacket p;
		p.inputDirection = clientPlayer->inputDirection;
		p.inputJump = clientPlayer->inputJump;
		
		RakNet::BitStream s;
		s.Write(base.useTimeStamp);
		s.Write(base.timeStamp);
		s.Write((RakNet::MessageID)base.typeId);
		s.Write(p.inputDirection);
		s.Write(p.inputJump);
		this->nethandler->peer->Send(&s, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 1, this->nethandler->server, false, 0);
	}

} /* End of namespace CLIENT */
