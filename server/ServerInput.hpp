#ifndef SERVERINPUT_HPP
#define SERVERINPUT_HPP

#include <string>
#include <iostream>

class ServerInput {

public:

    static ServerInput* Instance();
    static void Release();

    int RequestHandler();

private:

    static ServerInput* sInstance;

    ServerInput();
    ~ServerInput();
};

#endif
