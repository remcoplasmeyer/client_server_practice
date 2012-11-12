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
			FILE_LOG(logDEBUG) << player.clientPort;
			int status = server->serverSocket.send(packet->sendingPacket, player.ip, player.clientPort);
		}
	}
}

void packetSender::sendQueueToAll() {
	for(std::vector<Packet>::iterator packageItr = packageQueue.begin(); packageItr != packageQueue.end();) {
		//we do not increment the iterator, because we're popping every element
		Packet* packet;
		packet = &(*packageItr);
		sendToAll(packet);
		packageQueue.erase(packageItr);
	}
}

packetSender::packetSender() {

}

packetSender::~packetSender() {
	// TODO Auto-generated destructor stub
}

