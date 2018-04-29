#include "SocketReceive.hpp"

SocketReceive* SocketReceive::sInstance = nullptr;

SocketReceive* SocketReceive::Instance() {

    if(sInstance==nullptr)
        sInstance = new SocketReceive();

    return sInstance;
}

void SocketReceive::Release() {

    delete sInstance;
    sInstance = nullptr;
}

void SocketReceive::Init(const std::string& ipaddr, const int& port) {

    SocketEntity::Init(ipaddr, port);

    if(SocketEntity::Valid()) {

        SocketEntity::Address(INADDR_ANY);

        if(bind(SocketEntity::Sockfd(), (struct sockaddr *)SocketEntity::AddressRef(), sizeof(SocketEntity::Address()))<0) {
            std::cout << "Bind Failed" << std::endl;
            return;
        }

        if(listen(SocketEntity::Sockfd(), 1)<0) {
            std::cout << "Listen Failed" << std::endl;
            return;
        }
        
        mValid = true;
    }
}

bool SocketReceive::Valid() {

    return mValid;
}

std::string SocketReceive::GetMessage() {


    if(mValread==0) {

        if(mRecvSock!=-1)
            close(mRecvSock);
        int addrlen = sizeof(SocketEntity::Address());
        mRecvSock = accept(SocketEntity::Sockfd(), (struct sockaddr *)SocketEntity::AddressRef(), (socklen_t *)&addrlen);
        mValread = -1;
        return "-1";
    }

    mValread = read(mRecvSock, buffer, 1024);
    std::string message = buffer;
    memset(buffer, 0, sizeof(buffer));

    return message;
}

SocketReceive::SocketReceive() {

    memset(buffer, 0, sizeof(buffer));
    mValid = false;
    mValread = 0;
    mRecvSock = -1;
}

SocketReceive::~SocketReceive() {
}
