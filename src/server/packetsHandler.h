#ifndef SERVER_packetsHandler_h
#define SERVER_packetsHandler_h

namespace SERVER {
class packetSender;
class packetReceiver;
} /* End of namespace SERVER */

namespace SERVER {

class packetsHandler {

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

} /* End of namespace SERVER */

#endif // SERVER_packetsHandler_h
