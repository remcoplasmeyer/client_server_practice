#ifndef CLIENT_inputHandler_h
#define CLIENT_inputHandler_h

namespace CLIENT {
class netHandler;
class controlHandler;
} /* End of namespace CLIENT */

namespace CLIENT {

class inputHandler {

 public:


    /**
     * @element-type netHandler
     */
    netHandler *nethandler;

    /**
     * @element-type controlHandler
     */
    controlHandler *controlhandler;
};

} /* End of namespace CLIENT */

#endif // CLIENT_inputHandler_h
