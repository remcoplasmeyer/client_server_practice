#ifndef CLIENT_viewHandler_h
#define CLIENT_viewHandler_h

namespace CLIENT {
class resourceLoader;
} /* End of namespace CLIENT */

namespace CLIENT {

class viewHandler {

 public:

    void loadResources();

 public:


    /**
     * @element-type resourceLoader
     */
    resourceLoader *myresourceLoader;
};

} /* End of namespace CLIENT */

#endif // CLIENT_viewHandler_h
