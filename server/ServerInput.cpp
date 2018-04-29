#include "ServerInput.hpp"

ServerInput* ServerInput::sInstance = nullptr;

ServerInput* ServerInput::Instance() {

    if(sInstance==nullptr)
        sInstance = new ServerInput();

    return sInstance;
}

void ServerInput::Release() {

    delete sInstance;
    sInstance = nullptr;
}

int ServerInput::RequestHandler() {

    std::string in;
    std::cin >> in;
    if(in.compare("start")==0)
        return 0;
    else if(in.compare("stop")==0)
        return 1;
    else 
        return -1;
}

ServerInput::ServerInput() {
}

ServerInput::~ServerInput() {
}
