/*
 * packetSender.h
 *
 *  Created on: Oct 18, 2012
 *      Author: Remco
 */

#ifndef PACKETSENDER_H_
#define PACKETSENDER_H_
#include "../Packet.h"
#include <vector>
class Server;
/* every server has 1 packetsender
 * it contains the queue of packages and functions to send these
 */

class packetSender {
public:
	std::vector<Packet> packageQueue;			//packageQueue for all players
	Server *server;

	void setServer(Server *server);
	void addToQueue(Packet packet);
	void sendQueueToAll();
	void sendToAll(Packet *packet);
	packetSender();
	~packetSender();
};

#endif /* PACKETSENDER_H_ */
