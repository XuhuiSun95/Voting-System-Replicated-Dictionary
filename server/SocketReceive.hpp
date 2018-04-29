#ifndef SOCKETRECEIVE_HPP
#define SOCKETRECEIVE_HPP

#include "SocketEntity.hpp"

class SocketReceive : public SocketEntity {

public:

    static SocketReceive* Instance();
    static void Release();

    void Init(const std::string& ipaddr, const int& port);
    bool Valid();
    std::string GetMessage();

private:

    static SocketReceive* sInstance;

    bool mValid;
    int mRecvSock, mValread;
    char buffer[1024];

    SocketReceive();
    ~SocketReceive();
};

#endif
