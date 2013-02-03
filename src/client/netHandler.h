#ifndef CLIENT_netHandler_h
#define CLIENT_netHandler_h

namespace CLIENT {
class packetSender;
class packetReceiver;
} /* End of namespace CLIENT */

namespace CLIENT {

class netHandler {

 public:


    /**
     * @element-type packetSender
     */
    packetSender *packetsender;

    /**
     * @element-type packetReceiver
     */
    packetReceiver *packetreceiver;
};

} /* End of namespace CLIENT */

#endif // CLIENT_netHandler_h
