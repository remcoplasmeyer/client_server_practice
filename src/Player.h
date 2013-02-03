#ifndef Player_h
#define Player_h
#include <string>


class Player {

 public:

    void respawn();

    void checkIntersection();

    void newOperation();

 public:
    int id;
    std::string name;

};

#endif // Player_h
