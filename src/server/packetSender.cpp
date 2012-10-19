/*
 * packetSender.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: Remco
 */

#include "../Log.h"
#include "packetSender.h"
#include "Server.h"
#include "../Player.h"
#include "../Packet.h"
#include <boost/foreach.hpp>
#include <string>
#include <iostream>
#include <map>

void packetSender::setServer(Server *_server) {
	server = _server;
}

void packetSender::addToQueue(Packet packet) {
	packageQueue.push_back(packet);
}

void packetSender::sendToAll(Packet *packet) {
	//we send the packet to all players
	if(!server->players.empty()) {	//if we have players
		typedef std::map<std::string, Player>::iterator it_type;
		for(it_type iterator = server->players.begin(); iterator != server->players.end(); iterator++) {
			Player &player = iterator->second;
			server->serverSocket.send(packet->sendingPacket, player.ip, 1235);
		}
	}
}

void packetSender::sendQueueToAll() {
	for(int i = 0; i < packageQueue.size() ; i++) {
		Packet *packetPtr = &packageQueue[i];
		sendToAll(packetPtr);
		packageQueue.erase(packageQueue.begin() + i);
	}
}

packetSender::packetSender() {

}

packetSender::~packetSender() {
	// TODO Auto-generated destructor stub
}

