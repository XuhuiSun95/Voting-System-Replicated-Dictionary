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
    else if(in.compare("Vote,A")==0)
        return 2;
    else if(in.compare("Vote,B")==0)
        return 3;
    else if(in.compare("printDict.")==0)
        return 4;
    else if(in.compare("printLog")==0)
        return 5;
    else if(in.compare("printTable")==0)
        return 6;
    else if(in.compare("debug")==0)
        return 7;
    else 
        return -1;
}

ServerInput::ServerInput() {
}

ServerInput::~ServerInput() {
}
