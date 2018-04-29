#ifndef SOCKETSEND_HPP
#define SOCKETSEND_HPP

#include "SocketEntity.hpp"

class SocketSend : public SocketEntity {

public:

    static SocketSend* Instance();
    static void Release();

    void Init(const std::string& ipaddr, const int& port);
    bool Valid();
    void SendMessage(const std::string& msg);

private:

    static SocketSend* sInstance;

    bool mValid;

    SocketSend();
    ~SocketSend();
};

#endif
