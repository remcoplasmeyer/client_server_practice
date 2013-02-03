#ifndef CLIENT_guiHandler_h
#define CLIENT_guiHandler_h

#include <vector>


namespace CLIENT {
namespace GUI {
class guiEntity;
} /* End of namespace CLIENT::GUI */
} /* End of namespace CLIENT */

namespace CLIENT {

class guiHandler {

 public:


    /**
     * @element-type guiEntity
     */
    std::vector< GUI::guiEntity* > guiEntities;
};

} /* End of namespace CLIENT */

#endif // CLIENT_guiHandler_h
